/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/IO/SystemFile.h>
#include <AzCore/IO/FileIO.h>
#include <AzCore/Casting/numeric_cast.h>
#include <AzCore/Debug/Profiler.h>

#include <AzCore/PlatformIncl.h>
#include <AzCore/Utils/Utils.h>

#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>

namespace AZ::IO
{

const char* SystemFile::GetNullFilename()
{
    return "/dev/null";
}

namespace UnixLikePlatformUtil
{
    // Platform specific helpers
    bool CanCreateDirRecursive(char* dirPath);
}

namespace
{
    //=========================================================================
    //  Internal utility to create a folder hierarchy recursively without
    //  any additional string copies.
    //  If this function fails (returns false), the error will be available
    //   via errno on Unix platforms
    //=========================================================================
    bool CreateDirRecursive(char* dirPath)
    {
        if (!UnixLikePlatformUtil::CanCreateDirRecursive(dirPath))
        {
            // Our current platform has told us we have failed
            return false;
        }

        int result = mkdir(dirPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (result == 0)
        {
            return true;    // Created without error
        }
        else if (result == -1)
        {
            // If result == -1, the error is stored in errno
            // http://pubs.opengroup.org/onlinepubs/007908799/xsh/mkdir.html
            result = errno;
        }

        if (result == ENOTDIR || result == ENOENT)
        {
            // try to create our parent hierarchy
            for (size_t i = strlen(dirPath); i > 0; --i)
            {
                if (dirPath[i] == '/' || dirPath[i] == '\\')
                {
                    char delimiter = dirPath[i];
                    dirPath[i] = 0; // null-terminate at the previous slash
                    bool ret = CreateDirRecursive(dirPath);
                    dirPath[i] = delimiter; // restore slash
                    if (ret)
                    {
                        // now that our parent is created, try to create again
                        return mkdir(dirPath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
                    }
                    return false;
                }
            }
            // if we reach here then there was no parent folder to create, so we failed for other reasons
        }
        else if (result == EEXIST)
        {
            struct stat s;
            if (stat(dirPath, &s) == 0)
            {
                return s.st_mode & S_IFDIR;
            }
        }
        return false;
    }
}

namespace Platform
{
    AZ::u64 ModificationTime(const char* fileName)
    {
        struct stat statResult;
        if (stat(fileName, &statResult) != 0)
        {
            return 0;
        }
        return aznumeric_cast<AZ::u64>(statResult.st_mtime);
    }

    SystemFile::SizeType Length(const char* fileName)
    {
        SizeType len = 0;

        SystemFile f;
        if (f.Open(fileName, SystemFile::SF_OPEN_READ_ONLY))
        {
            len = f.Length();
            f.Close();
        }

        return len;
    }

    bool Delete(const char* fileName)
    {
        int result = remove(fileName);
        if (result != 0)
        {
            return false;
        }

        return true;
    }

    bool Rename(const char* sourceFileName, const char* targetFileName, bool overwrite)
    {
        int result = rename(sourceFileName, targetFileName);
        if (result)
        {
            return false;
        }

        return true;
    }

#if !(AZ_TRAIT_SYSTEMFILE_UNIX_LIKE_PLATFORM_IS_WRITEABLE_DEFINED_ELSEWHERE)
    bool IsWritable(const char* sourceFileName)
    {
        return (access(sourceFileName, W_OK) == 0);
    }
#endif // !(AZ_TRAIT_SYSTEMFILE_UNIX_LIKE_PLATFORM_IS_WRITEABLE_DEFINED_ELSEWHERE)

    bool SetWritable(const char* sourceFileName, bool writable)
    {
        struct stat s;
        if (stat(sourceFileName, &s) == 0)
        {
            int permissions = (s.st_mode & S_IRWXU) | (s.st_mode & S_IRWXO) | (s.st_mode & S_IRWXG);
            if (writable)
            {
                if (s.st_mode & S_IWUSR)
                {
                    // file is already writeable
                    return true;
                }
                return chmod(sourceFileName, permissions | S_IWUSR) == 0;
            }
            else
            {
                if (s.st_mode & S_IWUSR)
                {
                    return chmod(sourceFileName, permissions & ~(S_IWUSR)) == 0;
                }
                else
                {
                    // file is already read-only
                    return true;
                }
            }
        }
        return false;
    }

    bool CreateDir(const char* dirName)
    {
        if (dirName)
        {
            char dirPath[AZ_MAX_PATH_LEN];
            if (strlen(dirName) > AZ_MAX_PATH_LEN)
            {
                return false;
            }
            azstrcpy(dirPath, AZ_MAX_PATH_LEN, dirName);
            bool success = CreateDirRecursive(dirPath);
            return success;
        }
        return false;
    }

    bool DeleteDir(const char* dirName)
    {
        AZ_PROFILE_SCOPE(AzCore, "SystemFile::DeleteDir(util) - %s", dirName);

        if (dirName)
        {
            return rmdir(dirName) == 0;
        }
        return false;
    }
} // namespace AZ::IO::Platform
} // namespace AZ::IO

namespace AZ::IO::PosixInternal
{
    int Dup(int fileDescriptor)
    {
        return dup(fileDescriptor);
    }

    int Dup2(int fileDescriptorSource, int fileDescriptorDestination)
    {
        return dup2(fileDescriptorSource, fileDescriptorDestination);
    }

    int Pipe(int(&pipeFileDescriptors)[2], int, OpenFlags pipeFlags)
    {
        return pipe2(pipeFileDescriptors, static_cast<int>(pipeFlags));
    }
} // namespace AZ::IO::PosixInternal

namespace AZ::IO
{
    // FileDescriptorCapturer UnixLike Impl
    void FileDescriptorCapturer::Start(int pipeSize)
    {
        if (m_redirectToPipe)
        {
            // Capturer is already in progress
            return;
        }
        if (m_sourceDescriptor == -1)
        {
            // Source file descriptor isn't set.
            return;
        }
        int pipeCreated = PosixInternal::Pipe(m_pipe, pipeSize, PosixInternal::OpenFlags::NonBlock);

        if (pipeCreated == -1)
        {
            return;
        }

        // Duplicate the original source descriptor to restore in Stop
        m_dupSourceDescriptor = PosixInternal::Dup(m_sourceDescriptor);

        // Duplicate the write end of the pipe onto the original source descriptor
        // This causes the writes to the source descriptor to redirect to the pipe
        if (PosixInternal::Dup2(m_pipe[WriteEnd], m_sourceDescriptor) == -1)
        {
            // Failed to redirect the source descriptor to the pipe
            PosixInternal::Close(m_dupSourceDescriptor);
            PosixInternal::Close(m_pipe[WriteEnd]);
            PosixInternal::Close(m_pipe[ReadEnd]);
            // Reset pipe descriptor to -1
            m_pipe[WriteEnd] = -1;
            m_pipe[ReadEnd] = -1;
            m_dupSourceDescriptor = -1;
            return;
        }

        m_redirectToPipe = true;
    }

    void FileDescriptorCapturer::Flush(const OutputRedirectVisitor& redirectCallback)
    {
        if (!redirectCallback)
        {
            return;
        }
        constexpr int PipeBufferSize = DefaultPipeSize;
        AZStd::array<AZStd::byte, PipeBufferSize> capturedBytes;

        int bytesRead{};
        do
        {
            // Pump the read end of the pipe until it is empty
            // and invoke the visitor for each call
            bytesRead = PosixInternal::Read(m_pipe[ReadEnd],
                AZStd::ranges::data(capturedBytes), static_cast<int>(AZStd::ranges::size(capturedBytes)));
            if (bytesRead > 0)
            {
                redirectCallback(AZStd::span(AZStd::ranges::data(capturedBytes), bytesRead));
            }

        } while (bytesRead > 0);
    }

    void FileDescriptorCapturer::Stop(const OutputRedirectVisitor& redirectCallback)
    {
        // Close the write end of the pipe before flushing
        // This is required in order to not block the thread when reading from the pipe
        if (m_pipe[WriteEnd] != -1)
        {
            PosixInternal::Close(m_pipe[WriteEnd]);
            m_pipe[WriteEnd] = -1;
        }

        // Invoke the visitor with the output in the pipe
        Flush(redirectCallback);
        // Closes the pipe and resets the descriptor
        Reset();
    }
} // namespace AZ::IO

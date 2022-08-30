/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "StyledTracePrintFLogPanel.h"

#include <QAction>
#include <QDateTime>
#include <QTimer>

#pragma optimize("", off)

namespace AzToolsFramework
{
    namespace LogPanel
    {
        // some tweakables
        static int s_delayBetweenStyledTraceprintfUpdates = 50; // milliseconds between pumping the traceprintf messages, lower will eat more performance but be more responsive

        StyledTracePrintFLogPanel::StyledTracePrintFLogPanel(QWidget* parent)
            : StyledLogPanel(parent)
        {
        }

        QWidget* StyledTracePrintFLogPanel::CreateTab(const TabSettings& settings)
        {
            return aznew StyledTracePrintFLogTab(settings, this);
        }

        StyledTracePrintFLogTab::StyledTracePrintFLogTab(const TabSettings& settings, QWidget* parent)
            : StyledLogTab(settings, parent)
        {
            LogTraceRequests::Bus::Handler::BusConnect();

            m_alreadyQueuedDrainMessage = false;

            // add clear to context menu:
            QAction* actionClear = new QAction(tr("Clear"), this);
            connect(actionClear, &QAction::triggered, this, &StyledTracePrintFLogTab::Clear);
            addAction(actionClear);

            AZ::Debug::TraceMessageBus::Handler::BusConnect();
        }

        void StyledTracePrintFLogTab::Clear()
        {
            auto pModel = qobject_cast<Logging::LogTableModel*>(model());
            if (pModel)
            {
                pModel->Clear();
            }
        }

        bool StyledTracePrintFLogTab::OnAssert(const char* message)
        {
            if ((GetSettings().m_filterFlags & TabSettings::FilterType::FILTER_ERROR) != TabSettings::FilterType::FILTER_NONE)
            {
                LogTraceMessage(Logging::LogLine::TYPE_ERROR, "ASSERT", message);
            }

            return false;
        }
        bool StyledTracePrintFLogTab::OnException(const char* message)
        {
            if ((GetSettings().m_filterFlags & TabSettings::FilterType::FILTER_ERROR) != TabSettings::FilterType::FILTER_NONE)
            {
                LogTraceMessage(Logging::LogLine::TYPE_ERROR, "EXCEPTION", message);
            }

            return false;
        }

        bool StyledTracePrintFLogTab::OnError(const char* window, const char* message)
        {
            if ((GetSettings().m_filterFlags & TabSettings::FilterType::FILTER_ERROR) != TabSettings::FilterType::FILTER_NONE)
            {
                LogTraceMessage(Logging::LogLine::TYPE_ERROR, window, message);
            }
            return false;
        }

        bool StyledTracePrintFLogTab::OnWarning(const char* window, const char* message)
        {
            if ((GetSettings().m_filterFlags & TabSettings::FilterType::FILTER_WARNING) != TabSettings::FilterType::FILTER_NONE)
            {
                LogTraceMessage(Logging::LogLine::TYPE_WARNING, window, message);
            }
            return false;
        }

        bool StyledTracePrintFLogTab::OnPrintf(const char* window, const char* message)
        {
            if (
                ((GetSettings().m_filterFlags & TabSettings::FilterType::FILTER_DEBUG) != TabSettings::FilterType::FILTER_NONE) &&
                (azstricmp(window, "debug") == 0)
                )
            {
                LogTraceMessage(Logging::LogLine::TYPE_DEBUG, window, message);
            }
            else if ((GetSettings().m_filterFlags & TabSettings::FilterType::FILTER_NORMAL) != TabSettings::FilterType::FILTER_NONE &&
                (azstricmp(window, "debug") != 0))
            {
                LogTraceMessage(Logging::LogLine::TYPE_MESSAGE, window, message);
            }
            return false;
        }

        //bool StyledTracePrintFLogTab::OnPreError(const char* window, const char* /*fileName*/, int /*line*/, const char* /*func*/, const char* message)
        //{
        //    LogTraceMessage(Logging::LogLine::TYPE_ERROR, window, message);

        //    return false;
        //}

        //bool StyledTracePrintFLogTab::OnPreWarning(const char* window, const char* /*fileName*/, int /*line*/, const char* /*func*/, const char* message)
        //{
        //    LogTraceMessage(Logging::LogLine::TYPE_WARNING, window, message);

        //    return false;
        //}

        bool StyledTracePrintFLogTab::OnOutput(const char* window, const char* message)
        {
            if (azstricmp(window, "all") == 0)
            {
                LogTraceMessage(Logging::LogLine::TYPE_MESSAGE, window, message);
            }
            return false;
        }

        void StyledTracePrintFLogTab::LogTraceMessage(Logging::LogLine::LogType type, const char* window, const char* message, bool alwaysShowMessage)
        {
            // note:  This is responding to a TraceMessageBus message
            // as such, the mutex is already locked but we could be called from any thread at all, so we buffer the lines.

            // is it for this window?
            // empty window discriminator string signifies that this OnLog receives ALL
            // hard coded "All" in the dialog to mean the same

            const TabSettings& settings = GetSettings();
            bool isMyWindowAll = (!settings.m_window.length()) || (azstricmp(settings.m_window.c_str(), "All") == 0);

            bool filterMatch = ((type & settings.m_filterFlags) != TabSettings::FilterType::FILTER_NONE);

            if (filterMatch || isMyWindowAll || ((window) && (azstricmp(window, settings.m_window.c_str()) == 0)))
            {
                if (alwaysShowMessage || (settings.m_textFilter.length() == 0 || strstr(message, settings.m_textFilter.c_str())))
                {
                    {
                        AZStd::lock_guard<AZStd::mutex> lock(m_bufferedLinesMutex);
                        m_bufferedLines.push(Logging::LogLine(message, window ? window : "", type, QDateTime::currentMSecsSinceEpoch()));
                    }

                    // if we've already queued a timer tick, don't queue another one:
                    bool wasQueued = m_alreadyQueuedDrainMessage.exchange(true, AZStd::memory_order_acq_rel);
                    if (!wasQueued)
                    {
                        // this code is likely running in a listener thread, which cannot invoke
                        // QTimer::singleShot and must instead place a message on the message queue.
                        QMetaObject::invokeMethod(this, "ScheduleDrainMessages", Qt::QueuedConnection);
                    }
                }
            }
        }

        // metaMethod to invoke when you are in a non-Qt thread and need
        // to schedule messages to be drained.
        void StyledTracePrintFLogTab::ScheduleDrainMessages()
        {
            // this is invoked on the actual thread of the UI, so it can call timer::singleShot.
             QTimer::singleShot(s_delayBetweenStyledTraceprintfUpdates, this, &StyledTracePrintFLogTab::DrainMessages);
        }

        // we only tick when there's queue to drain.
        void StyledTracePrintFLogTab::DrainMessages()
        {
            m_alreadyQueuedDrainMessage = false;

            bool wasAtMaxScroll = IsAtMaxScroll();
            auto pModel = qobject_cast<Logging::LogTableModel*>(model());
            if (!pModel)
            {
                return;
            }

            Logging::LogLine currentLine;
            bool openedQuery = false;
            bool foundLine = false;
            do
            {
                {
                    AZStd::lock_guard<AZStd::mutex> lock(m_bufferedLinesMutex);
                    if (m_bufferedLines.empty())
                    {
                        foundLine = false;
                    }
                    else
                    {
                        foundLine = true;
                        currentLine = AZStd::move(m_bufferedLines.front());
                        m_bufferedLines.pop();
                    }
                }

                if (foundLine)
                {
                    if (!openedQuery)
                    {
                        openedQuery = true;
                    }

                    pModel->AppendLine(currentLine);
                }
            } while (foundLine); // keep doing this as long as there's line in the buffer.

            if (openedQuery)
            {
                pModel->CommitLines();
                if (wasAtMaxScroll)
                {
                    scrollToBottom();
                }
            }
        }

        StyledTracePrintFLogTab::~StyledTracePrintFLogTab()
        {
            LogTraceRequests::Bus::Handler::BusDisconnect();
            AZ::Debug::TraceMessageBus::Handler::BusDisconnect();
        }

    } // namespace LogPanel
} // namespace AzToolsFramework

#include "UI/Logging/moc_StyledTracePrintFLogPanel.cpp"


#pragma optimize("", on)

/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 *
 * For complete copyright and license terms please see the LICENSE at the root of this
 * distribution (the "License"). All use of this software is governed by the License,
 * or, if provided, by the license below or the license accompanying this file. Do not
 * remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *
 */
#pragma once

#if !defined(Q_MOC_RUN)
#include <ScreenWidget.h>
#include <ProjectInfo.h>

#include <QQueue>
#endif

QT_FORWARD_DECLARE_CLASS(QPaintEvent)
QT_FORWARD_DECLARE_CLASS(QFrame)
QT_FORWARD_DECLARE_CLASS(QStackedWidget)
QT_FORWARD_DECLARE_CLASS(QLayout)

namespace O3DE::ProjectManager
{
    QT_FORWARD_DECLARE_CLASS(ProjectBuilderController);
    QT_FORWARD_DECLARE_CLASS(ProjectButton);

    class ProjectsScreen
        : public ScreenWidget
    {

    public:
        explicit ProjectsScreen(QWidget* parent = nullptr);
        ~ProjectsScreen();

        ProjectManagerScreen GetScreenEnum() override;
        QString GetTabText() override;
        bool IsTab() override;

    protected:
        void NotifyCurrentScreen() override;
        void ProjectBuildDone();

    protected slots:
        void HandleNewProjectButton();
        void HandleAddProjectButton();
        void HandleOpenProject(const QString& projectPath);
        void HandleEditProject(const QString& projectPath);
        void HandleCopyProject(const QString& projectPath);
        void HandleRemoveProject(const QString& projectPath);
        void HandleDeleteProject(const QString& projectPath);

        void SuggestBuildProject(const ProjectInfo& projectInfo);
        void QueueBuildProject(const ProjectInfo& projectInfo);

        void paintEvent(QPaintEvent* event) override;

    private:
        QFrame* CreateFirstTimeContent();
        QFrame* CreateProjectsContent(QString buildProjectPath = "", ProjectButton** projectButton = nullptr);
        ProjectButton* CreateProjectButton(ProjectInfo& project, QLayout* flowLayout, bool processing = false);
        void ResetProjectsContent();
        bool ShouldDisplayFirstTimeContent();

        void StartProjectBuild(const ProjectInfo& projectInfo);
        QList<ProjectInfo>::iterator RequiresBuildProjectIterator(const QString& projectPath);
        bool BuildQueueContainsProject(const QString& projectPath);
        bool WarnIfInBuildQueue(const QString& projectPath);

        QAction* m_createNewProjectAction = nullptr;
        QAction* m_addExistingProjectAction = nullptr;
        QPixmap m_background;
        QFrame* m_firstTimeContent = nullptr;
        QFrame* m_projectsContent = nullptr;
        QStackedWidget* m_stack = nullptr;
        QList<ProjectInfo> m_requiresBuild;
        QQueue<ProjectInfo> m_buildQueue;
        ProjectBuilderController* m_currentBuilder = nullptr;

        inline constexpr static int s_contentMargins = 80;
        inline constexpr static int s_spacerSize = 20;
    };

} // namespace O3DE::ProjectManager

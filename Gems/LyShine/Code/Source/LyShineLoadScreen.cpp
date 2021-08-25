/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "LyShineLoadScreen.h"

#if AZ_LOADSCREENCOMPONENT_ENABLED

#include <IRenderer.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Component/ComponentApplicationBus.h>
#include <LyShine/Bus/UiCanvasBus.h>
#include <LyShine/Animation/IUiAnimation.h>

namespace LyShine
{
    void LyShineLoadScreenComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serialize = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serialize->Class<LyShineLoadScreenComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void LyShineLoadScreenComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.emplace_back(AZ_CRC("LyShineLoadScreenService", 0xBB5EAB17));
    }

    void LyShineLoadScreenComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.emplace_back(AZ_CRC("LyShineLoadScreenService", 0xBB5EAB17));
    }

    void LyShineLoadScreenComponent::Init()
    {
    }

    void LyShineLoadScreenComponent::Activate()
    {
        LoadScreenNotificationBus::Handler::BusConnect();
    }

    void LyShineLoadScreenComponent::Deactivate()
    {
        LoadScreenUpdateNotificationBus::Handler::BusDisconnect();
        LoadScreenNotificationBus::Handler::BusDisconnect();
    }

    bool LyShineLoadScreenComponent::NotifyGameLoadStart(bool usingLoadingThread)
    {
        // LyShine does not support the loading thread yet.
        if (usingLoadingThread)
        {
            return false;
        }
        //TODO: gEnv->pRenderer is always null, fix the logic below
        AZ_ErrorOnce(nullptr, false, "NotifyGameLoadStart needs to be removed/ported to use Atom");
        return false;
#if 0
        if (!gEnv || gEnv->pRenderer || !gEnv->pLyShine)
        {
            return false;
        }

        AZ_Assert(!m_isPlaying, "LyShineLoadScreen was somehow started before the engine loaded.");
        if (m_isPlaying)
        {
            return false;
        }

        if (!m_gameCanvasEntityId.IsValid())
        {
            // Load canvas.
            m_gameCanvasEntityId = loadFromCfg("game_load_screen_uicanvas_path", "game_load_screen_sequence_to_auto_play");
        }

        m_isPlaying = m_gameCanvasEntityId.IsValid();

        if (m_isPlaying)
        {
            LoadScreenUpdateNotificationBus::Handler::BusConnect();
        }

        return m_isPlaying;
#endif
    }

    bool LyShineLoadScreenComponent::NotifyLevelLoadStart(bool usingLoadingThread)
    {
        // LyShine does not support the loading thread yet.
        if (usingLoadingThread)
        {
            return false;
        }

        AZ_ErrorOnce(nullptr, false, "NotifyLevelLoadStart needs to be removed/ported to use Atom");
        return false;
        //TODO: gEnv->pRenderer is always null, fix the logic below
#if 0
        if (!gEnv || gEnv->pRenderer || !gEnv->pLyShine)
        {
            return false;
        }

        AZ_Assert(!m_isPlaying, "LyShineLoadScreen was not stopped before another level load started.");
        AZ_Assert(!m_gameCanvasEntityId.IsValid(), "LyShineLoadScreen game load canvas was not unloaded before a level load started.");
        if (m_isPlaying || m_gameCanvasEntityId.IsValid())
        {
            return false;
        }

        if (!m_levelCanvasEntityId.IsValid())
        {
            // Load canvas.
            m_levelCanvasEntityId = loadFromCfg("level_load_screen_uicanvas_path", "level_load_screen_sequence_to_auto_play");
        }

        m_isPlaying = m_levelCanvasEntityId.IsValid();

        if (m_isPlaying)
        {
            LoadScreenUpdateNotificationBus::Handler::BusConnect();
        }

        return m_isPlaying;
#endif
    }

    void LyShineLoadScreenComponent::NotifyLoadEnd()
    {
        Reset();
    }

    void LyShineLoadScreenComponent::UpdateAndRender([[maybe_unused]] float deltaTimeInSeconds)
    {
        AZ_Assert(m_isPlaying, "LyShineLoadScreenComponent should not be connected to LoadScreenUpdateNotificationBus while not playing");
        AZ_ErrorOnce(nullptr, m_isPlaying && gEnv && gEnv->pLyShine, "UpdateAndRender needs to be removed/ported to use Atom");

        //TODO: gEnv->pRenderer is always null, fix the logic below
#if 0
        if (m_isPlaying && gEnv && gEnv->pLyShine && gEnv->pRenderer)
        {
            AZ_Assert(GetCurrentThreadId() == gEnv->mMainThreadId, "UpdateAndRender should only be called from the main thread");

            // update the animation system
            gEnv->pLyShine->Update(deltaTimeInSeconds);

            // Render.
            gEnv->pRenderer->SetViewport(0, 0, gEnv->pRenderer->GetOverlayWidth(), gEnv->pRenderer->GetOverlayHeight());

            gEnv->pRenderer->BeginFrame();
            gEnv->pLyShine->Render();
            gEnv->pRenderer->EndFrame();
        }
#endif
    }

    void LyShineLoadScreenComponent::LoadThreadUpdate([[maybe_unused]] float deltaTimeInSeconds)
    {
        AZ_Assert(false, "LyShine does not support running on the loading thread yet.")
    }

    void LyShineLoadScreenComponent::LoadThreadRender()
    {
        AZ_Assert(false, "LyShine does not support running on the loading thread yet.")
    }

    void LyShineLoadScreenComponent::Reset()
    {
        LoadScreenUpdateNotificationBus::Handler::BusDisconnect();

        m_isPlaying = false;

        if (gEnv && gEnv->pLyShine)
        {
            AZ::Entity* canvasEntity = nullptr;

            // Release the game canvas.
            if (m_gameCanvasEntityId.IsValid())
            {
                EBUS_EVENT_RESULT(canvasEntity, AZ::ComponentApplicationBus, FindEntity, m_gameCanvasEntityId);
                if (canvasEntity)
                {
                    gEnv->pLyShine->ReleaseCanvas(m_gameCanvasEntityId, false);
                    gEnv->pLyShine->OnLoadScreenUnloaded();
                }
            }

            // Release the level canvas.
            if (m_levelCanvasEntityId.IsValid())
            {
                EBUS_EVENT_RESULT(canvasEntity, AZ::ComponentApplicationBus, FindEntity, m_levelCanvasEntityId);
                if (canvasEntity)
                {
                    gEnv->pLyShine->ReleaseCanvas(m_levelCanvasEntityId, false);
                    gEnv->pLyShine->OnLoadScreenUnloaded();
                }
            }
        }

        m_gameCanvasEntityId.SetInvalid();
        m_levelCanvasEntityId.SetInvalid();

        // Reset CVars so they're not carried over to other levels
        auto ClearCvar = [](const char* cvarName)
        {
            if (gEnv && gEnv->pConsole)
            {
                if (ICVar* var = gEnv->pConsole->GetCVar(cvarName))
                {
                    var->Set("");
                }
            }
        };

        ClearCvar("level_load_screen_uicanvas_path");
        ClearCvar("level_load_screen_sequence_to_auto_play");
    }

    AZ::EntityId LyShineLoadScreenComponent::loadFromCfg(const char* pathVarName, const char* autoPlayVarName)
    {
        ICVar* pathVar = gEnv->pConsole->GetCVar(pathVarName);
        AZStd::string path = pathVar ? pathVar->GetString() : "";
        if (path.empty())
        {
            // No canvas specified.
            Reset();
            return AZ::EntityId();
        }

        AZ::EntityId canvasId = gEnv->pLyShine->LoadCanvas(path);
        AZ_Warning("LoadScreenComponent", canvasId.IsValid(), "Can't load canvas: %s", path.c_str());
        if (!canvasId.IsValid())
        {
            // Error loading canvas.
            Reset();
            return AZ::EntityId();
        }

        EBUS_EVENT_ID(canvasId, UiCanvasBus, SetKeepLoadedOnLevelUnload, true);

        // Set the load screen draw order so it renders in front of other canvases that may load during the level load
        EBUS_EVENT_ID(canvasId, UiCanvasBus, SetDrawOrder, std::numeric_limits<int>::max());

        ICVar* autoPlayVar = gEnv->pConsole->GetCVar(autoPlayVarName);
        AZStd::string sequence = autoPlayVar ? autoPlayVar->GetString() : "";
        if (sequence.empty())
        {
            // Nothing to auto-play.
            return canvasId;
        }

        IUiAnimationSystem* animSystem = nullptr;
        EBUS_EVENT_ID_RESULT(animSystem, canvasId, UiCanvasBus, GetAnimationSystem);
        if (!animSystem)
        {
            // Nothing can be auto-played.
            return canvasId;
        }

        animSystem->PlaySequence(sequence.c_str(), nullptr, false, false);

        return canvasId;
    }

} // namespace LyShine

#endif // AZ_LOADSCREENCOMPONENT_ENABLED


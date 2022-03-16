/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <ScriptCanvas/Libraries/Spawning/DespawnNodeable.h>

namespace ScriptCanvas::Nodeables::Spawning
{
    DespawnNodeable::DespawnNodeable([[maybe_unused]] const DespawnNodeable& rhs)
    {
        // this method is required by Script Canvas, left intentionally blank to avoid copying m_despawnedTicketList
    }

    DespawnNodeable& DespawnNodeable::operator=([[maybe_unused]] const DespawnNodeable& rhs)
    {
        // this method is required by Script Canvas, left intentionally blank to avoid copying m_despawnedTicketList
        return *this;
    }

    void DespawnNodeable::OnInitializeExecutionState()
    {
        if (!AZ::TickBus::Handler::BusIsConnected())
        {
            AZ::TickBus::Handler::BusConnect();
        }
    }

    void DespawnNodeable::OnDeactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        m_despawnedTicketList.clear(); // clears any cached SpawnTickets that may remain so everything despawns
        m_despawnedTicketList.shrink_to_fit();
    }

    void DespawnNodeable::OnTick([[maybe_unused]] float delta, [[maybe_unused]] AZ::ScriptTimePoint timePoint)
    {
        AZStd::vector<AzFramework::EntitySpawnTicket> swappedDespawnedTicketList;
        {
            AZStd::lock_guard lock(m_mutex);
            swappedDespawnedTicketList.swap(m_despawnedTicketList);
        }

        for (const auto& spawnTicket : swappedDespawnedTicketList)
        {
            CallOnDespawn(spawnTicket);
        }
    }

    void DespawnNodeable::RequestDespawn(AzFramework::EntitySpawnTicket spawnTicket)
    {
        if (!spawnTicket.IsValid())
        {
            AZ_Error("DespawnNodeable", false, "EntitySpawnTicket used for despawning is invalid (make sure the slot is connected).")
            return;
        }

        auto despawnCompleteCB = [this, spawnTicket]([[maybe_unused]] AzFramework::EntitySpawnTicket::Id ticketId)
        {
            AZStd::lock_guard lock(m_mutex);
            // SpawnTicket instance is cached instead of SpawnTicketId to simplify managing its lifecycle on Script Canvas
            // and to provide easier access to it in OnDespawn callback
            m_despawnedTicketList.push_back(spawnTicket);
        };

        AzFramework::DespawnAllEntitiesOptionalArgs optionalArgs;
        optionalArgs.m_completionCallback = AZStd::move(despawnCompleteCB);
        AzFramework::SpawnableEntitiesInterface::Get()->DespawnAllEntities(spawnTicket, AZStd::move(optionalArgs));
    }
} // namespace ScriptCanvas::Nodeables::Spawning

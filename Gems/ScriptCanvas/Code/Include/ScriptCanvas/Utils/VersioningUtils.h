/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/std/containers/unordered_map.h>
#include <AzCore/std/containers/unordered_set.h>
#include <AzCore/std/utils.h>

#include <ScriptCanvas/Core/Core.h>
#include <ScriptCanvas/Core/Endpoint.h>
#include <ScriptCanvas/Variable/VariableCore.h>

namespace AZ
{
    class EntityId;
}

namespace ScriptCanvas
{
    class Datum;
    class Graph;
    class Slot;

    using ReplacementEndpointPairs = AZStd::unordered_set<AZStd::pair<Endpoint, Endpoint>>;
    using ReplacementConnectionMap = AZStd::unordered_map<AZ::EntityId, ReplacementEndpointPairs>;

    struct NodeUpdateSlotReport
    {
        AZStd::unordered_set<SlotId> m_deletedOldSlots;
        AZStd::unordered_map<SlotId, AZStd::vector<SlotId>> m_oldSlotsToNewSlots;

        bool IsEmpty() const;
    };

    struct GraphUpdateSlotReport
    {
        AZStd::unordered_set<Endpoint> m_deletedOldSlots;
        AZStd::unordered_map<Endpoint, AZStd::vector<Endpoint>> m_oldSlotsToNewSlots;

        AZStd::vector<Endpoint> Convert(const Endpoint& oldEndpoint) const;

        bool IsEmpty() const;
    };

    void MergeUpdateSlotReport(const AZ::EntityId& scriptCanvasNodeId, GraphUpdateSlotReport& report, const NodeUpdateSlotReport& source);

    AZStd::vector<AZStd::pair<Endpoint, Endpoint>> CollectEndpoints(const AZStd::vector<AZ::Entity*>& connections, bool logEntityNames = false);

    void UpdateConnectionStatus(Graph& graph, const GraphUpdateSlotReport& report);

    class VersioningUtils
    {
    public:
        static void CopyOldValueToDataSlot(Slot* newSlot, const VariableId& oldVariableReference, const Datum* oldDatum);

        static void CreateRemapConnectionsForSourceEndpoint(const Graph& graph, const Endpoint& oldSourceEndpoint, const Endpoint& newSourceEndpoint, ReplacementConnectionMap&);
        static void CreateRemapConnectionsForTargetEndpoint(const Graph& graph, const Endpoint& oldTargetEndpoint, const Endpoint& newTargetEndpoint, ReplacementConnectionMap&);
    };
}

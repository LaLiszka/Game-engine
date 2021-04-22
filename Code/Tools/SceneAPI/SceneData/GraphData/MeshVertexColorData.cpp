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

#include <SceneAPI/SceneData/GraphData/MeshVertexColorData.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace AZ
{
    AZ_TYPE_INFO_SPECIALIZE(SceneAPI::DataTypes::Color, "{937E3BF8-5204-4D40-A8DA-C8F083C89F9F}");

    namespace SceneData
    {
        namespace GraphData
        {
            void MeshVertexColorData::Reflect(ReflectContext* context)
            {
                SerializeContext* serializeContext = azrtti_cast<SerializeContext*>(context);
                if (serializeContext)
                {
                    serializeContext->Class<MeshVertexColorData>()->Version(1);
                }

                BehaviorContext* behaviorContext = azrtti_cast<BehaviorContext*>(context);
                if (behaviorContext)
                {
                    behaviorContext->Class<MeshVertexColorData>()
                        ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                        ->Attribute(AZ::Script::Attributes::Module, "scene")
                        ->Method("GetCustomName", [](const MeshVertexColorData& self) { return self.GetCustomName().GetCStr(); })
                        ->Method("GetCount", &MeshVertexColorData::GetCount )
                        ->Method("GetColor", &MeshVertexColorData::GetColor);

                    behaviorContext->Class<AZ::SceneAPI::DataTypes::Color>("MeshVertexColor")
                        ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                        ->Attribute(AZ::Script::Attributes::Module, "scene")
                        ->Property("red", BehaviorValueGetter(&AZ::SceneAPI::DataTypes::Color::red), nullptr)
                        ->Property("green", BehaviorValueGetter(&AZ::SceneAPI::DataTypes::Color::green), nullptr)
                        ->Property("blue", BehaviorValueGetter(&AZ::SceneAPI::DataTypes::Color::blue), nullptr)
                        ->Property("alpha", BehaviorValueGetter(&AZ::SceneAPI::DataTypes::Color::alpha), nullptr);
                }
            }

            void MeshVertexColorData::CloneAttributesFrom(const IGraphObject* sourceObject)
            {
                IMeshVertexColorData::CloneAttributesFrom(sourceObject);
                if (const auto* typedSource = azrtti_cast<const MeshVertexColorData*>(sourceObject))
                {
                    SetCustomName(typedSource->GetCustomName());
                }
            }

            const AZ::Name& MeshVertexColorData::GetCustomName() const
            {
                return m_customName;
            }

            void MeshVertexColorData::SetCustomName(const char* name)
            {
                m_customName = name;
            }
            void MeshVertexColorData::SetCustomName(const AZ::Name& name)
            {
                m_customName = name;
            }

            size_t MeshVertexColorData::GetCount() const
            {
                return m_colors.size();
            }

            const AZ::SceneAPI::DataTypes::Color& MeshVertexColorData::GetColor(size_t index) const
            {
                AZ_Assert(index < m_colors.size(), "Invalid index %i for mesh vertex color.", index);
                return m_colors[index];
            }

            void MeshVertexColorData::ReserveContainerSpace(size_t size)
            {
                m_colors.reserve(size);
            }

            void MeshVertexColorData::AppendColor(const AZ::SceneAPI::DataTypes::Color& color)
            {
                m_colors.push_back(color);
            }

            void MeshVertexColorData::GetDebugOutput(AZ::SceneAPI::Utilities::DebugOutput& output) const
            {
                output.Write("Colors", m_colors);
                output.Write("ColorsCustomName", m_customName.GetCStr());
            }
        } // GraphData
    } // SceneData
} // AZ

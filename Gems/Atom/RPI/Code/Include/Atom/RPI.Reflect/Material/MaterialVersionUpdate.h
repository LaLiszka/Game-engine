/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/RTTI/ReflectContext.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/std/containers/map.h>
#include <AzCore/std/string/string.h>
#include <AzCore/Name/Name.h>
#include <Atom/RPI.Reflect/Material/MaterialPropertiesLayout.h>
#include <Atom/RPI.Reflect/Material/MaterialPropertyValue.h>

namespace AZ
{
    namespace RPI
    {
        class MaterialAsset;

        // This class contains a toVersion and a list of actions to specify what operations were performed to upgrade a materialType.
        class MaterialVersionUpdate
        {
            friend class MaterialVersionUpdates;

        private:
            class PropertyHelper;

        public:
            AZ_TYPE_INFO(AZ::RPI::MaterialVersionUpdate, "{B36E7712-AED8-46AA-AFE0-01F8F884C44A}");

            static void Reflect(ReflectContext* context);

            struct Action
            {
                AZ_TYPE_INFO(AZ::RPI::MaterialVersionUpdate::Action, "{A1FBEB19-EA05-40F0-9700-57D048DF572B}");
                static void Reflect(ReflectContext* context);

                using ArgsMap = AZStd::unordered_map<AZ::Name, MaterialPropertyValue>;
                AZ::Name m_operation;
                ArgsMap m_argsMap;

                //! Generic structure for arbitrary version update actions that maps nicely to json.
                //! The operation type is stored as a string under the "op" key.
                //! All other entries depend on which "op" is being used, see the @ref Action()
                //! constructor for details.
                //! Note that we are somewhat hijacking the MaterialPropertyValue class here: not
                //! every argument will be an actual material property value, some will be generic
                //! strings like the "op" string or they could be property names for example. But
                //! when the arg *does* happen to represent a property value it is convenient to
                //! rely on the associated JsonMaterialPropertyValueSerializer to load the value.
                //! Since MaterialPropertyValue has the option of holding a string type, we can use
                //! it for all cases.
                //! Lastly, note that we don't use an unordered_map to keep json deserialization
                //! (and the associated unit tests) deterministic.
                using ActionDefinition = AZStd::map<AZStd::string, MaterialPropertyValue>;

                Action() = default;

                //! Main constructor for creating a material version update Action from within c++ code.
                //! @param operation The operation type for this action, supported are
                //!                   - rename,
                //!                   - setValue.
                //! @param args The specific arguments for the chosen operation type:
                //!              - rename operation: {"from":"oldPropertyName", "to":"newPropertyName"},
                //!              - setValue operation: {"name":"myInt", "value":100}.
                //!                In the case where the property also has 'rename' version updates,
                //!                any of the names can be used in 'setValue'.
                Action(
                    const AZ::Name& operation,
                    const AZStd::initializer_list<AZStd::pair<AZ::Name, MaterialPropertyValue>>& args);

                //! Constructor to facilitate loading from parsed json data.
                //! The operation type is given as a string under the "op" key, the remaining items
                //! define the operation's arguments as in the main constructor.
                //! (e.g. {"op":"rename", "from":"oldPropertyName", "to":"newPropertyName"}).
                Action(const ActionDefinition& fullActionDefinition);
                //! Initializer list version of @ref Action(ActionDefinition&) to facilitate literal construction in c++ code.
                Action(const AZStd::initializer_list<AZStd::pair<AZStd::string, MaterialPropertyValue>>& fullActionDefinition);

                void AddArg(const AZ::Name& key, const MaterialPropertyValue& argument);
                MaterialPropertyValue GetArg(const AZ::Name& key) const;
                //! Helper function for the common case where an AZStd::string value is requested as an AZ::Name.
                AZ::Name GetArgAsName(const AZ::Name& key) const;
                size_t GetArgCount() const;

                //! Validates our internal consistency.
                //! Runs additional checks if @p propertyHelper is provided (e.g. type checking for 'setValue' actions).
                bool Validate(
                    const PropertyHelper* propertyHelper = nullptr,
                    AZStd::function<void(const char*)> onError = nullptr) const;

                bool HasExpectedNumArguments(
                    size_t expectedNum, const char* expectedArgs, AZStd::function<void(const char*)> onError) const;

                //! Checks for the existence of an argument of type T with name @p expectedArgName.
                //! @arg T_str String describing the expected type T, used in error messages via @p onError.
                template <typename T>
                bool HasExpectedArgument(
                    const char* expectedArgName, const char* T_str, AZStd::function<void(const char*)> onError) const;
                //! Checks for the existence of an argument with name @p expectedArgName, regardless
                //! of its type.
                bool HasExpectedArgumentAnyType(
                    const char* expectedArgName, AZStd::function<void(const char*)> onError) const;

                bool operator==(const Action& other) const;
            };

            explicit MaterialVersionUpdate() = default;
            explicit MaterialVersionUpdate(uint32_t toVersion);

            uint32_t GetVersion() const;
            void SetVersion(uint32_t toVersion);

            using Actions = AZStd::vector<Action>;
            const Actions& GetActions() const;
            //! Add the given action. Optionally, @p sourceDataResolver may be given to resolve a
            //! MaterialPropertyValue from a source type into an asset-ready type (e.g. from an
            //! image filename string to an ImageAsset).
            void AddAction(
                const Action& action,
                AZStd::function<MaterialPropertyValue(const Name&, const MaterialPropertyValue&)> sourceDataResolver = nullptr);

        private:
            //! Helper class for resolving potentially-renamed properties and their types.
            class PropertyHelper
            {
            public:
                //! @param applyAllPropertyRenames Callback that applies the property renames of
                //!        all version updates to its argument and returns true if a change was made.
                //! @param materialPropertiesLayout Material properties layout with all property
                //!        names already updated to the latest version.
                PropertyHelper(
                    AZStd::function<bool(AZ::Name&)> applyAllPropertyRenames,
                    const MaterialPropertiesLayout* materialPropertiesLayout);

                //! Tries to cast @p value in-place to its expected type based on its @p propertyId
                //! and our MaterialPropertiesLayout.
                //! @return True iff the cast was successful
                bool CastToExpectedType(
                    const Name& propertyId,
                    MaterialPropertyValue& value,
                    AZStd::function<void(const char*)> onError = nullptr) const;

                //! Apply the property renames of all material version updates to the given @p propertyId.
                bool ApplyAllPropertyRenames(AZ::Name& propertyId) const;

            private:
                const MaterialPropertiesLayout* m_materialPropertiesLayout;
                AZStd::function<bool(AZ::Name&)> m_applyAllPropertyRenames;
            };


            //! Possibly renames @p propertyId based on the material version update actions.
            //! @return True iff the property was renamed
            bool ApplyPropertyRenames(AZ::Name& propertyId) const;

            //! Possibly changes or adds values in @p rawProperties based on the material version update actions.
            //! @return True iff a property was set
            bool ApplySetValues(
                AZStd::vector<AZStd::pair<Name, MaterialPropertyValue>>& rawProperties,
                const PropertyHelper& propertyHelper,
                AZStd::function<void(const char*)> onError) const;

            //! Validates the internal consistency of our update actions
            //! @param propertyHelper Perform in-depth validation including property names and type check
            //!        if provided. If set to nullptr, we only check for internal consistency.
            bool ValidateActions(
                const PropertyHelper* propertyHelper, AZStd::function<void(const char*)> onError) const;

            uint32_t m_toVersion;
            Actions m_actions;
        };

        class MaterialVersionUpdates
        {
        public:
            AZ_TYPE_INFO(AZ::RPI::MaterialVersionUpdates, "{91EBA78E-83F6-4EA5-916A-A3C81B08137C}");

            static void Reflect(ReflectContext* context);

            MaterialVersionUpdates() = default;

            void AddVersionUpdate(const MaterialVersionUpdate& versionUpdate);

            size_t GetVersionUpdateCount() const;

            const MaterialVersionUpdate& GetVersionUpdate(size_t i) const;

            //! Validate our updates against a MaterialTypeAsset with version @p materialTypeVersion
            //! and updated properties layout @p materialPropertiesLayout.
            //! @param materialPropertiesLayout The property layout that was already updated
            //!        to use the latest property names (e.g. using @ref ApplyPropertyRenames()).
            bool ValidateUpdates(
                uint32_t materialTypeVersion,
                const MaterialPropertiesLayout* materialPropertiesLayout,
                AZStd::function<void(const char*)> onError) const;

            //! Apply rename actions to the given @p propertyId if applicable.
            //! @return True iff the @p propertyId was renamed
            bool ApplyPropertyRenames(AZ::Name& propertyId) const;

            //! Apply our version updates to the given material asset.
            //! @return True iff any changes were made
            bool ApplyVersionUpdates(MaterialAsset& materialAsset, AZStd::function<void(const char*)> reportError) const;

        private:
            MaterialVersionUpdate::PropertyHelper MakePropertyHelper(const MaterialPropertiesLayout* materialPropertiesLayout) const;

            using MaterialVersionUpdateList = AZStd::vector<MaterialVersionUpdate>;
            MaterialVersionUpdateList m_versionUpdates;
        };

    } // namespace RPI
} // namespace AZ

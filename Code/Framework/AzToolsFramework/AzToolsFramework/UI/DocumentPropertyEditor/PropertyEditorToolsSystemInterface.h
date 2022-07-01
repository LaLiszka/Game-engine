/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzToolsFramework/UI/DocumentPropertyEditor/PropertyHandlerWidget.h>

namespace AzToolsFramework
{
    //! Interface for UI-level features of the Document Property Editor
    //! such as registering property handler widgets.
    class PropertyEditorToolsSystemInterface
    {
    public:
        AZ_RTTI(PropertyEditorToolsSystemInterface, "{4E45141B-D612-4DCB-A644-A874EE9A7A52}");

        virtual ~PropertyEditorToolsSystemInterface() = default;

        using PropertyHandlerInstance = AZStd::unique_ptr<PropertyHandlerWidgetInterface>;
        using PropertyHandlerInstanceFactory = AZStd::function<PropertyHandlerInstance()>;

        //! Metadata used to determine the handler to instantiate for a given DPE node.
        //! This is typically automatically generated by the templated RegisterHandler.
        struct HandlerData
        {
            //! The name of the handler, used for determining which set of handlers to match against.
            AZStd::string_view m_name;
            //! A factory functor that constructs an instance of this handler.
            PropertyHandlerInstanceFactory m_factory;
            //! A functor that returns true if this handler should be created for a given node.
            //! The first registered handler that returns true for this will be provided when calling
            //! GetPropertyHandlerForNode.
            AZStd::function<bool(const AZ::Dom::Value&)> m_shouldHandleNode;
            //! Determines whether this handler should be in the "default" pool and match against editors
            //! with no "Type" attribute explicitly specified. The first default handler that returns true
            //! from m_shouldHandleNode will be selected (if any).
            //! Care should be taken to not provide overly general handlers as default handlers.
            bool m_isDefaultHandler;
        };
        //! A persistent ID for a given property handler.
        using PropertyHandlerId = HandlerData*;
        //! An invalid or nonexistent ID for a property handler.
        static constexpr PropertyHandlerId InvalidHandlerId = nullptr;

        //! Looks up the property handler for a given node.
        //! Currently, only PropertyEditor nodes are supported.
        virtual PropertyHandlerId GetPropertyHandlerForNode(const AZ::Dom::Value node) = 0;
        //! Creates a PropertyHandlerInstance given a property handler ID.
        //! Any number of handler instances can be created for a given handler ID.
        //! This operation will fail if the ID is InvalidHandlerId.
        virtual PropertyHandlerInstance CreateHandlerInstance(PropertyHandlerId handlerId) = 0;
        //! Registers a property handler. For standard types that implement PropertyHandlerWidgetInterface,
        //! the templated helper may be used to automatically create HandlerData for a given type.
        virtual PropertyHandlerId RegisterHandler(HandlerData handlerData) = 0;
        //! Unregisters a previously registered property handler.
        virtual void UnregisterHandler(PropertyHandlerId handlerId) = 0;

        template<class, class = void>
        static constexpr bool IsDefaultHandler = false;

        template<class T>
        static constexpr bool IsDefaultHandler<T, AZStd::void_t<typename T::IsDefaultHandler>> = T::IsDefaultHandler();

        //! Registers a factory for a given type of PropertyHandlerWidgetInterface.
        //! This type must implement `static const AZStd::string_view GetHandlerName()`
        //! and may implement `static bool ShouldHandleNode(const AZ::Dom::Value& node)`
        template<typename HandlerType>
        void RegisterHandler()
        {
            HandlerData handlerData;
            handlerData.m_name = HandlerType::GetHandlerName();
            handlerData.m_shouldHandleNode = [](const AZ::Dom::Value& node) -> bool
            {
                return HandlerType::ShouldHandleNode(node);
            };
            handlerData.m_factory = []
            {
                return AZStd::make_unique<HandlerType>();
            };
            handlerData.m_isDefaultHandler = IsDefaultHandler<HandlerType>;
            RegisterHandler(AZStd::move(handlerData));
        }
    };
} // namespace AzToolsFramework

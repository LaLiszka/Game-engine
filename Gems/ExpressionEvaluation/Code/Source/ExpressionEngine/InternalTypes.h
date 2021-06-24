/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <ExpressionEvaluation/ExpressionEngine/ExpressionTypes.h>

namespace ExpressionEvaluation
{
    namespace InternalTypes
    {
        // General operations of the expression tree that are handled internally.
        enum InternalOperatorId
        {
            Primitive = 0,
            Variable,
            OpenParen,
            CloseParen
        };

        namespace Interfaces
        {
            static const ExpressionParserId InternalParser = 0;
        }
    }

    class ExpressionResultStack
        : public AZStd::stack<ExpressionResult>
    {
    public:
        AZ_CLASS_ALLOCATOR(ExpressionResultStack, AZ::SystemAllocator, 0);

        ExpressionResult PopAndReturn()
        {
            if (empty())
            {
                return ExpressionResult();
            }

            auto result = top();
            pop();
            return result;
        }
    };
}

#pragma once

#include <cstddef>

#include "fca_bitset.h"

namespace FCA
{
    class ConceptInterface
    {
    public:
        virtual const BitSet& Extent() const = 0;
        virtual BitSet& Extent() = 0;
        virtual size_t ExtentSize() const = 0;

        virtual const BitSet& Intent() const = 0;
        virtual BitSet& Intent() = 0;
        virtual size_t IntentSize() const = 0;

        virtual ~ConceptInterface() throw() { ;; }
    };
};

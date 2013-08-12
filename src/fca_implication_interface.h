#pragma once

#include <cstddef>

#include "fca_bitset.h"

namespace FCA
{
    class ImplicationInterface
    {
    public:
        virtual const BitSet& Premise() const = 0;
        virtual BitSet& Premise() = 0;
        virtual size_t PremiseSize() const = 0;

        virtual const BitSet& Conclusion() const = 0;
        virtual BitSet& Conclusion() = 0;
        virtual size_t ConclusionSize() const = 0;

        virtual void Complete() = 0;

        virtual ~ImplicationInterface() throw() { ;; }
    };
};

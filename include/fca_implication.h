#pragma once

#include "fca_implication_interface.h"
#include "fca_bitset.h"

namespace FCA
{
    class Implication : public ImplicationInterface
    {
    public:
        Implication();
        Implication(const Implication& impl);
        explicit Implication(const size_t& baseSize);
        Implication(const BitSet& premise, const BitSet& conclusion);
        explicit Implication(const BitSet& bs);

        const BitSet& Premise() const;
        BitSet& Premise();
        size_t PremiseSize() const;

        const BitSet& Conclusion() const;
        BitSet& Conclusion();
        size_t ConclusionSize() const;

        void Complete();

        virtual ~Implication() throw() { ;; }

    protected:
        BitSet premise;
        BitSet conclusion;
    };
};

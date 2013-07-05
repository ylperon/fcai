# pragma once

# include "fca_implication_interface.h"
# include "fca_bitset.h"

namespace FCA
{
    class Implication : public FCA::ImplicationInterface
    {
    public:
        Implication();
        Implication(const Implication& impl);
        explicit Implication(const size_t& baseSize);
        Implication(const BitSet& premise, const BitSet& conclusion);
        explicit Implication(const BitSet& bs);

        virtual ~Implication() throw() { ;; }

    protected:
        BitSet premise;
        BitSet conclusion;
    };
};

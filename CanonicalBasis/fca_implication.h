# pragma once

# ifndef FCA_IMPLICATION_H_
# define FCA_IMPLICATION_H_

# include "fca_implication_interface.h"
# include "fca_bitset.h"

namespace FCA
{
    class Implication : public FCA::ImplicationInterface
    {
    public:
        Implication();
        Implication(const Implication& impl);
        Implication(const size_t& sizePremise, const size_t& sizeConclusion);
        explicit Implication(const size_t& size);
        Implication(const BitSet& premise, const BitSet& conclusion);
        explicit Implication(const BitSet& bs);

        virtual const BitSet& Premise() const;
        virtual BitSet& Premise();
        virtual size_t SizePremise() const;

        virtual const BitSet& Conclusion() const;
        virtual BitSet& Conclusion();
        virtual size_t SizeConclusion() const;

        virtual void Complete();

        virtual ~Implication() throw() { ;; }

    protected:
        BitSet mPremise;
        BitSet mConclusion;
    };
};

# endif //FCA_IMPLICATION_H_
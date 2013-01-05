# pragma once

# ifndef FCA_IMPLICATION_INTERFACE_H_
# define FCA_IMPLICATION_INTERFACE_H_

# include <cstddef>

namespace FCA
{
    class BitSet;

    class ImplicationInterface
    {
    public:
        virtual const BitSet& Premise() const;
        virtual BitSet& Premise();
        virtual size_t SizePremise() const;

        virtual const BitSet& Conclusion() const;
        virtual BitSet& Conclusion();
        virtual size_t SizeConclusion() const;

        virtual void Complete();

        virtual ~ImplicationInterface() throw() { ;; }
    };
};

# endif //FCA_IMPLICATION_INTERFACE_H_
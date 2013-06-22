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
        virtual const BitSet& Premise() const = 0;
        virtual BitSet& Premise() = 0;
        virtual size_t SizePremise() const = 0;

        virtual const BitSet& Conclusion() const = 0;
        virtual BitSet& Conclusion() = 0;
        virtual size_t SizeConclusion() const = 0;

        virtual void Complete() = 0;

        virtual ~ImplicationInterface() throw() { ;; }
    };
};

# endif //FCA_IMPLICATION_INTERFACE_H_
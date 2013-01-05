# pragma once

# ifndef FCA_CONCEPT_INTERFACE_H_
# define FCA_CONCEPT_INTERFACE_H_

# include <cstddef>

namespace FCA
{
    class BitSet;

    class ConceptInterface
    {
    public:
        virtual const BitSet& Extent() const = 0;
        virtual BitSet& Extent() = 0;
        virtual size_t SizeExtent() const = 0;

        virtual const BitSet& Intent() const = 0;
        virtual BitSet& Intent() = 0;
        virtual size_t SizeIntent() const = 0;

        virtual ~ConceptInterface() throw() { ;; }
    };
};

# endif //FCA_CONCEPT_INTERFACE_H_
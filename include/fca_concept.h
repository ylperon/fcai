# pragma once

# ifndef FCA_CONCEPT_H_
# define FCA_CONCEPT_H_

# include "fca_concept_interface.h"
# include "fca_bitset.h"

namespace FCA
{
    class Concept : public ConceptInterface
    {
    public:
        Concept() {}
        Concept(const Concept& c);
        Concept(const size_t objSize, const size_t attrSize);
        Concept(const BitSet &extent, const BitSet& intent);

        virtual const BitSet& Extent() const;
        virtual BitSet& Extent();
        virtual size_t SizeExtent() const;

        virtual const BitSet& Intent() const;
        virtual BitSet& Intent();
        virtual size_t SizeIntent() const;

        virtual ~Concept() throw() { ;; }

    protected:
        BitSet mExtent;
        BitSet mIntent;
    };
};

# endif //FCA_CONCEPT_H_
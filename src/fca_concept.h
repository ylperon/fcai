#pragma once

#include "fca_concept_interface.h"

namespace FCA
{
    class Concept : public ConceptInterface
    {
    public:
        Concept() {}
        Concept(const Concept& c);
        Concept(const size_t objSize, const size_t attrSize);
        Concept(const BitSet &extent, const BitSet& intent);

        const BitSet& Extent() const;
        BitSet& Extent();
        size_t ExtentSize() const;

        const BitSet& Intent() const;
        BitSet& Intent();
        size_t IntentSize() const;

        virtual ~Concept() throw() { ;; }

    protected:
        BitSet extent;
        BitSet intent;
    };
};

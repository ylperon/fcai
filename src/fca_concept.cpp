#include "fca_concept.h"

using namespace FCA;

Concept::Concept(const Concept& c)
    : extent(c.extent),
      intent(c.intent) {}

Concept::Concept(const size_t objSize, const size_t attrSize)
    : extent(objSize),
      intent(attrSize) {}

Concept::Concept(const BitSet &extent, const BitSet& intent)
    : extent(extent),
      intent(intent) {}

const BitSet& Concept::Extent() const
{
    return extent;
}

BitSet& Concept::Extent()
{
    return extent;
}

size_t Concept::ExtentSize() const
{
    return extent.count();
}

const BitSet& Concept::Intent() const
{
    return intent;
}

BitSet& Concept::Intent()
{
    return intent;
}

size_t Concept::IntentSize() const
{
    return intent.count();
}

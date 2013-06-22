# include "fca_concept.h"

using namespace FCA;

Concept::Concept(const Concept& c) 
    : mExtent(c.mExtent),
    mIntent(c.mIntent) {}

Concept::Concept(const size_t objSize, const size_t attrSize)
    : mExtent(objSize),
    mIntent(attrSize) {}

Concept::Concept(const BitSet &extent, const BitSet& intent)
    : mExtent(extent),
    mIntent(intent) {}

const BitSet& Concept::Extent() const
{
    return mExtent;
}

BitSet& Concept::Extent()
{
    return mExtent;
}

size_t Concept::SizeExtent() const
{
    return mExtent.count();
}

const BitSet& Concept::Intent() const
{
    return mIntent;
}

BitSet& Concept::Intent()
{
    return mIntent;
}

size_t Concept::SizeIntent() const
{
    return mIntent.count();
}
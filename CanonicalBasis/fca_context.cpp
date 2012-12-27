# include "fca_context.h"

# include <stdexcept>

# include "fca_bitset.h"

using namespace FCA;

Context::Context() : mObjSize(0),
                     mAttrSize(0) {}

Context::Context(const Context &cxt) : mObjSize(cxt.mObjSize), 
                                        mAttrSize(cxt.mAttrSize), 
                                        mTable(cxt.mTable), 
                                        mTableTr(cxt.mTableTr) {}

Context::Context(const size_t &objSize, 
                 const size_t &attrSize) : mObjSize(objSize),
                                           mAttrSize(attrSize)
{
    mTable.resize(objSize);
    for (std::vector<BitSet>::iterator it = mTable.begin();
         it != mTable.end(); ++it)
    {
        it->resize(attrSize);
    }

    mTableTr.resize(attrSize);
    for (std::vector<BitSet>::iterator it = mTableTr.begin();
         it != mTableTr.end(); ++it)
    {
        it->resize(attrSize);
    }
}

Context::Context(const std::vector<std::vector<bool> > &table)
    : mObjSize(table.size())
{
    mAttrSize = table.empty() ? 0 : table.front().size();

    mTable.resize(mObjSize);
    for (std::vector<BitSet>::iterator it = mTable.begin();
         it != mTable.end(); ++it)
    {
        it->resize(mAttrSize);
    }

    mTableTr.resize(mAttrSize);
    for (std::vector<BitSet>::iterator it = mTableTr.begin();
         it != mTableTr.end(); ++it)
    {
        it->resize(mAttrSize);
    }

    for (size_t objInd = 0; objInd < mObjSize; ++objInd)
    {
        for (size_t attrInd = 0; attrInd < mAttrSize; ++attrInd)
        {
            if (table[objInd][attrInd])
            {
                mTable[objInd].set(attrInd);
                mTableTr[attrInd].set(objInd);
            }
        }
    }
}

Context::Context(const std::vector<BitSet> &table)
    : mObjSize(table.size()),
      mTable(table)
{
    mAttrSize = table.empty() ? 0 : table.front().size();    

    mTableTr.resize(mAttrSize);
    for (std::vector<BitSet>::iterator it = mTableTr.begin();
         it != mTableTr.end(); ++it)
    {
        it->resize(mAttrSize);
    }

    for (size_t objInd = 0; objInd < mObjSize; ++objInd)
    {
        for (size_t attrInd = 0; attrInd < mAttrSize; ++attrInd)
        {
            if (table[objInd].test(attrInd))
            {                
                mTableTr[attrInd].set(objInd);
            }
        }
    }
}

Context &Context::operator=(const Context &cxt)
{
    if (&cxt == this)
    {
        return *this;
    }

    mObjSize = cxt.mObjSize;
    mAttrSize = cxt.mAttrSize;
    mTable = cxt.mTable;
    mTableTr = cxt.mTableTr;

    return *this;
}

void Context::Set(const size_t &objInd, const size_t &attrInd, const bool &val)
{
    CheckRangeAndThrowError(objInd, mObjSize, "object index out of range in Context::Set");
    CheckRangeAndThrowError(attrInd, mAttrSize,  "attribute index out of range in Context::Set");

    if (val)
    {
        mTable[objInd].set(attrInd);
        mTableTr[attrInd].set(objInd);
    }
    else
    {
        mTable[objInd].reset(attrInd);
        mTableTr[attrInd].reset(objInd);
    }
}

bool Context::Get(const size_t &objInd, const size_t &attrInd) const
{
    CheckRangeAndThrowError(objInd, mObjSize, "object index out of range in Context::Get");
    CheckRangeAndThrowError(attrInd, mAttrSize, "attribute index out of range in Context::Get");

    return mTable[objInd].test(attrInd);
}

const BitSet& Context::Intent(const size_t &objInd) const
{
    CheckRangeAndThrowError(objInd, mObjSize, "object index out of range in Context::Intent");

    return mTable[objInd];
}

const BitSet& Context::Extent(const size_t &attrInd) const
{
    CheckRangeAndThrowError(attrInd, mAttrSize, "attribute index out of range in Context::Extent");

    return mTableTr[attrInd];
}

BitSet Context::DrvtAttr(const BitSet &current) const
{
    CheckSetSizeAndThrowError(current.size(), mAttrSize, "wrong set size in Context::DrvtAttr");

    BitSet res(mObjSize);
    for (size_t objInd = 0; objInd < mObjSize; ++objInd)
    {
        if (current.is_subset_of(mTable[objInd]))
        {
            res.set(objInd);
        }
    }

    return res;
}

BitSet Context::ClosureAttr(const BitSet &current) const
{
    CheckSetSizeAndThrowError(current.size(), mAttrSize, "wrong set size in Context::ClosureAttr");

    return DrvtObj(DrvtAttr(current));
}

BitSet Context::DrvtObj(const BitSet &current) const
{
    CheckSetSizeAndThrowError(current.size(), mObjSize, "wrong set size in Context::DrvtObj");

    BitSet res(mAttrSize);
    for (size_t attrInd = 0; attrInd < mAttrSize; ++attrInd)
    {
        if (current.is_subset_of(mTableTr[attrInd]))
        {
            res.set(attrInd);
        }
    }

    return res;
}

BitSet Context::ClosureObj(const BitSet &current) const
{
    CheckSetSizeAndThrowError(current.size(), mObjSize, "wrong set size in Context::ClosureObj");

    return DrvtAttr(DrvtObj(current));
}
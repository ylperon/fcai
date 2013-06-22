# include "fca_ganter.h"

//=====================================================================================================================
//========================================Specialization of templates for FCA::LinClosure============================================
//=====================================================================================================================

template <>
FCA::BitSet FCA::NextClosure<FCA::LinClosure>(const FCA::BitSet &current, const std::vector<FCA::ImplicationInd> &implications)
{
    const size_t attrNum = current.size();
    FCA::BitSet res = current;

    size_t ind = attrNum;
    bool success = false;

    std::vector<size_t> premiseCount;
    std::vector<std::vector<size_t> > list(attrNum);
    size_t prevImplSetSize = 0;

    do
    {
        --ind;
        if (!res.test(ind))
        {
            BitSet tmp = res;
            tmp.set(ind);
            
            if (FCA::LinClosure::Apply(tmp, implications, premiseCount, list, prevImplSetSize, tmp, ind))
            {
                res = tmp;
                success = true;
            }
        }
        else
        {
            res.reset(ind);
        }
    }
    while (!success && ind != 0);

    return res;
}

static FCA::BitSet NextClosure(const FCA::BitSet &current, const std::vector<FCA::ImplicationInd> &implications,
                               std::vector<size_t> &premiseCount, std::vector<std::vector<size_t> > &list, size_t &prevImplSetSize)
{
    const size_t attrNum = current.size();
    FCA::BitSet res = current;

    size_t ind = attrNum;	
    bool success = false;	

    do
    {
        --ind;
        if (!res.test(ind))
        {
            FCA::BitSet tmp = res;
            tmp.set(ind);
            
            if (FCA::LinClosure::Apply(tmp, implications, premiseCount, list, prevImplSetSize, tmp, ind))
            {
                res = tmp;
                success = true;
            }
        }
        else
        {
            res.reset(ind);
        }
    }
    while (!success && ind != 0);

    return res;
}

template <>
std::vector<FCA::ImplicationInd> FCA::ComputeDGBasis<FCA::LinClosure>(const FCA::Context &context)
{
    const size_t attrNum = context.getAttributesCnt();

    std::vector<ImplicationInd> implications;
    BitSet current(attrNum);
    current.reset();
    BitSet baseSet(attrNum);	
    baseSet.set();

    std::vector<size_t> premiseCount;
    std::vector<std::vector<size_t> > list(attrNum);
    size_t prevImplSetSize = 0;

    while (current != baseSet)
    {
        BitSet tmpSet = context.closeAttr(current);
        if (current != tmpSet)
        {
            implications.push_back(ImplicationInd(current, tmpSet));
        }

        current = ::NextClosure(current, implications, premiseCount, list, prevImplSetSize);
    }

    return implications;
}

//=====================================================================================================================
//====================================Specialization of templates for FCA::LinClosureImproved=========================================
//=====================================================================================================================

template <>
FCA::BitSet FCA::NextClosure<FCA::LinClosureImproved>(const FCA::BitSet &current, const std::vector<FCA::ImplicationInd> &implications)
{
    const size_t attrNum = current.size();
    BitSet res = current;

    size_t ind = attrNum;	
    bool success = false;	

    std::vector<BitSet> list(attrNum);
    size_t implSize = 0;

    do
    {
        --ind;
        if (!res.test(ind))
        {
            BitSet tmp = res;
            tmp.set(ind);
            
            if (FCA::LinClosureImproved::Apply(tmp, implications, list, implSize, tmp, ind))
            {
                res = tmp;
                success = true;
            }
        }
        else
        {
            res.reset(ind);
        }
    }
    while (!success && ind != 0);

    return res;
}

static FCA::BitSet NextClosure(const FCA::BitSet &current, const std::vector<FCA::ImplicationInd> &implications,
                               std::vector<FCA::BitSet> &list, size_t &prevImplSetSize)
{
    FCA::BitSet res = current;

    size_t ind = res.size();	
    bool success = false;		

    do
    {
        --ind;
        if (!res.test(ind))
        {
            FCA::BitSet tmp = res;
            tmp.set(ind);
            
            if (FCA::LinClosureImproved::Apply(tmp, implications, list, prevImplSetSize, tmp, ind))
            {
                res = tmp;
                success = true;
            }
        }
        else
        {
            res.reset(ind);
        }
    }
    while (!success && ind != 0);

    return res;
}

template <>
std::vector<FCA::ImplicationInd> FCA::ComputeDGBasis<FCA::LinClosureImproved>(const FCA::Context &context)
{
    const size_t attrNum = context.getAttributesCnt();

    std::vector<ImplicationInd> implications;
    BitSet current(attrNum);
    current.reset();
    BitSet baseSet(attrNum);		
    baseSet.set();

    std::vector<BitSet> list(attrNum);
    size_t prevImplSetSize = 0;

    while (current != baseSet)
    {
        BitSet tmpSet = context.closeAttr(current);
        if (current != tmpSet)
        {
            implications.push_back(ImplicationInd(current, tmpSet));
        }

        current = ::NextClosure(current, implications, list, prevImplSetSize);
    }

    return implications;
}
# include "fca_ganter_optimized.h"

//=====================================================================================================================
//========================================Specialization of templates for FCA::LinClosure============================================
//=====================================================================================================================

template <>
std::vector<FCA::ImplicationInd> FCA::ComputeDGBasisOptimized<FCA::LinClosure>(const FCA::Context &context)
{
    const size_t attrNum = context.getAttributesCnt();

    std::vector<ImplicationInd> implications;
    BitSet aSet(attrNum);
    aSet.reset();
    BitSet pSet(attrNum);	
    pSet.reset();
    size_t ind = 0;
    bool success = true;

    std::vector<size_t> premiseCount;
    std::vector<std::vector<size_t> > list(attrNum);
    size_t prevImplSetSize = 0;

    //algorithm begin

    while (success)
    {
        BitSet pSetClosure = context.closeAttr(pSet);
        if (pSetClosure != pSet)
        {
            implications.push_back(ImplicationInd(pSet, pSetClosure));
        }

        if (IsPrefixIdentical(pSetClosure, pSet, ind))
        {
            aSet = pSetClosure;
            ind = attrNum;
        }

        success = false;
        do
        {
            --ind;
            if (!aSet.test(ind))
            {
                BitSet tmpSet = aSet;
                tmpSet.set(ind);
                
                if (FCA::LinClosure::Apply(tmpSet, implications, premiseCount, list, prevImplSetSize, pSet, ind))
                {
                    success = true;
                }
            }
            else
            {
                aSet.reset(ind);
            }
        }
        while (!success && ind != 0);
    }

    //algorithm end	
    return implications;
}

//=====================================================================================================================
//====================================Specialization of templates for FCA::LinClosureImproved=========================================
//=====================================================================================================================

template <>
std::vector<FCA::ImplicationInd> FCA::ComputeDGBasisOptimized<FCA::LinClosureImproved>(const FCA::Context &context)
{
    const size_t attrNum = context.getAttributesCnt();

    std::vector<ImplicationInd> implications;
    BitSet aSet(attrNum);
    aSet.reset();
    BitSet pSet(attrNum);	
    pSet.reset();
    size_t ind = 0;
    bool success = true;	

    std::vector<BitSet> list(attrNum);
    size_t prevImplSetSize = 0;

    //algorithm begin

    while (success)
    {
        BitSet pSetClosure = context.closeAttr(pSet);
        if (pSetClosure != pSet)
        {
            implications.push_back(ImplicationInd(pSet, pSetClosure));
        }

        if (IsPrefixIdentical(pSetClosure, pSet, ind))
        {
            aSet = pSetClosure;
            ind = attrNum;
        }

        success = false;
        do
        {
            --ind;
            if (!aSet.test(ind))
            {
                BitSet tmpSet = aSet;
                tmpSet.set(ind);
                
                if (FCA::LinClosureImproved::Apply(tmpSet, implications, list, prevImplSetSize, pSet, ind))
                {
                    success = true;
                }
            }
            else
            {
                aSet.reset(ind);
            }
        }
        while (!success && ind != 0);
    }

    //algorithm end	
    return implications;
}
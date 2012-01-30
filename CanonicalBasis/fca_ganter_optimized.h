# pragma once

# ifndef FCA_GANTER_OPTIMIZED_H_
# define FCA_GANTER_OPTIMIZED_H_

# include <vector>

# include "fca_datastructures.h"

namespace FCA
{
    /*
       Optimized Ganter algorithm
      */
    template <typename CloseFunction>
    std::vector<ImplicationInd> ComputeDGBasisOptimized(const Context &context);
};

//=====================================================================================================================
//==========================================Realization of templates==========================================================
//=====================================================================================================================

template <typename CloseFunction>
std::vector<FCA::ImplicationInd> FCA::ComputeDGBasisOptimized(const FCA::Context &context)
{
    const size_t attrNumber = context.getAttributesCnt();

    std::vector<ImplicationInd> implications;
    BitSet aSet(attrNumber);
    aSet.reset();
    BitSet pSet(attrNumber);	
    pSet.reset();
    size_t ind = 0;
    bool success = true;

    //algorithm begin

    while (success)
    {
        BitSet pSetClosure = context.closeAttr(pSet);
        if (pSetClosure != pSet)
        {
            implications.push_back(ImplicationInd(pSet, pSetClosure));
        }

        if (IsPrefixIdentical(pSet, pSetClosure, ind))
        {
            aSet = pSetClosure;
            ind = attrNumber;
        }

        success = false;
        do
        {
            --ind;
            if (!aSet.test(ind))
            {
                BitSet tmpSet = aSet;
                tmpSet.set(ind);
                
                if (CloseFunction::Apply(tmpSet, implications, pSet, ind))
                {
                    success = true;
                }
            }
            else
                aSet.reset(ind);
        }
        while (!success && ind != 0);
    }

    //algorithm end	
    return implications;
}

//=====================================================================================================================
//========================================Specialization of templates for FCA::LinClosure============================================
//=====================================================================================================================

# include "fca_linclosure.h"

namespace FCA
{
    template <>
    std::vector<ImplicationInd> ComputeDGBasisOptimized<LinClosure>(const Context &context);
};

//=====================================================================================================================
//====================================Specialization of templates for FCA::LinClosureImproved=========================================
//=====================================================================================================================

# include "fca_linclosure_improved.h"

namespace FCA
{
    template <>
    std::vector<ImplicationInd> ComputeDGBasisOptimized<LinClosureImproved>(const Context &context);
};

# endif //FCA_GANTER_OPTIMIZED_H_
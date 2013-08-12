# pragma once

# ifndef FCA_GANTER_H_
# define FCA_GANTER_H_

# include <vector>

# include "fca_datastructures.h"

namespace FCA
{
    template <typename CloseFunction>
    BitSet NextClosure(const BitSet &current, const std::vector<ImplicationInd> &implications);

    /*
       Ganter algorithm
        */
    template <typename CloseFunction>
    std::vector<ImplicationInd> ComputeDGBasis(const Context &context);
};

//=====================================================================================================================
//==========================================Realization of templates==========================================================
//=====================================================================================================================

template <typename CloseFunction>
FCA::BitSet FCA::NextClosure(const FCA::BitSet &current, const std::vector<FCA::ImplicationInd> &implications)
{
    const size_t attrNum = current.size();
    BitSet res = current;

    size_t ind = attrNum;	
    bool success = false;

    do
    {
        --ind;
        if (!res.test(ind))
        {
            BitSet tmp = res;
            tmp.set(ind);
            
            if (CloseFunction::Apply(tmp, implications, tmp, ind))
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

template <typename CloseFunction>
std::vector<FCA::ImplicationInd> FCA::ComputeDGBasis(const FCA::Context &context)
{
    const size_t attrNumber = context.getAttributesCnt();

    std::vector<ImplicationInd> implications;
    BitSet current(attrNumber);
    current.reset();
    BitSet baseSetBool(attrNumber);
    baseSetBool.set();

    while (current != baseSetBool)
    {
        BitSet tmpSet = context.closeAttr(current);
        if (current != tmpSet)
        {			
            implications.push_back(ImplicationInd(current, tmpSet));
        }

        current = FCA::NextClosure<CloseFunction>(current, implications);
    }

    return implications;
}

//=====================================================================================================================
//========================================Specialization of templates for FCA::LinClosure============================================
//=====================================================================================================================

# include "fca_linclosure.h"

namespace FCA
{
    template <>
    BitSet NextClosure<LinClosure>(const BitSet &current, const std::vector<ImplicationInd> &implications);

    template <>
    std::vector<ImplicationInd> ComputeDGBasis<LinClosure>(const Context &context);
};

//=====================================================================================================================
//====================================Specialization of templates for FCA::LinClosureImproved=========================================
//=====================================================================================================================

# include "fca_linclosure_improved.h"

namespace FCA
{
    template <>
    BitSet NextClosure<LinClosureImproved>(const BitSet &current, const std::vector<ImplicationInd> &implications);

    template <>
    std::vector<ImplicationInd> ComputeDGBasis<LinClosureImproved>(const Context &context);
};


# endif //FCA_GANTER_H
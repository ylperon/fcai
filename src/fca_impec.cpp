# include "fca_impec.h"

# include "fca_utility.h"

std::vector<FCA::ImplicationInd> FCA::ComputeProperBasis(const FCA::Context &context)
{
    size_t attrNumber = context.getAttributesCnt();
    std::vector<FCA::ImplicationInd> res;

    ImplicationInd implEmpty;
    implEmpty.Premise().resize(attrNumber);
    implEmpty.Premise().reset();
    implEmpty.Conclusion() = context.closeAttr(implEmpty.Premise());

    res.push_back(implEmpty);

    for (size_t attrCur = 0; attrCur < attrNumber; ++attrCur)
    {		
        std::vector<ImplicationInd> jot = res;

        for (size_t implCur = 0; implCur < jot.size(); ++implCur)
        {
            const BitSet &implCurPrms = jot[implCur].Premise();
            BitSet implCurPrmsUntdAttrCur = implCurPrms;
            implCurPrmsUntdAttrCur.set(attrCur);

            BitSet z = context.closeAttr(implCurPrmsUntdAttrCur);
            z -= implCurPrmsUntdAttrCur;			

            if (!z.none())
            {
                std::vector<bool> remove(jot.size(), false);
                for (size_t implInd = 0; implInd < jot.size(); ++implInd)
                {
                    if (implCurPrms.is_proper_subset_of(jot[implInd].Premise()))							
                    {
                        BitSet tmp = jot[implInd].Premise() - implCurPrms;
                        if (tmp.is_subset_of(z))
                        {
                            remove[implInd] = true;
                        }						
                    }
                }
                RemoveElements(remove, implCur, jot, implCur);
                implCur--;

                for (size_t implInd = 0; implInd < res.size(); ++implInd)
                    if (res[implInd].Premise().is_proper_subset_of(implCurPrmsUntdAttrCur))
                    {
                        z -= res[implInd].Conclusion();
                    }
            }

            ImplicationInd implToAdd(implCurPrmsUntdAttrCur, z);
            res.push_back(implToAdd);
        }
    }

    std::vector<FCA::ImplicationInd> resWithoutEmptySets;
    for (size_t implCur = 0; implCur < res.size(); ++implCur)
        if (!res[implCur].Premise().none() && !res[implCur].Conclusion().none() && res[implCur].Premise() != res[implCur].Conclusion())
        {
            res[implCur].Conclusion() -= res[implCur].Premise();
            resWithoutEmptySets.push_back(res[implCur]);
        }

    return resWithoutEmptySets;
}
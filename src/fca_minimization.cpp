# include "fca_minimization.h"

# include "fca_closure.h"
# include "fca_linclosure_improved.h"

std::vector<FCA::ImplicationInd> FCA::MinimizeBasis(const std::vector<FCA::ImplicationInd> &implSet)
{
    if (implSet.empty())
    {
        return implSet;
    }

    const size_t implSetSize = implSet.size();
    std::vector<ImplicationInd> tmp = implSet;

    for (size_t implCur = 0; implCur < implSetSize; ++implCur)
    {
        tmp[implCur].Conclusion() |= tmp[implCur].Premise();
    }	

    for (int implCur = static_cast<int>(implSetSize) - 1; implCur >= 0; --implCur)
    {
        ImplicationInd impl = tmp[implCur];		
        tmp[implCur] = tmp.back();
        tmp.pop_back();

        Closure::Apply(impl.Premise(), tmp, impl.Premise());
        if (impl.Premise().is_proper_subset_of(impl.Conclusion()))
        {
            tmp.push_back(impl);
        }
    }

    return tmp;
}

std::vector<FCA::ImplicationInd> FCA::MinimalCover(const std::vector<FCA::ImplicationInd> &implSet)
{
    if (implSet.empty())
    {
        return implSet;
    }

    const size_t attrNum = implSet.front().Premise().size();
    const size_t implSetSize = implSet.size();
    std::vector<ImplicationInd> tmp = implSet;

    for (size_t implCur = 0; implCur < implSetSize; ++implCur)
    {
        tmp[implCur].Conclusion() |= tmp[implCur].Premise();
    }

    std::vector<BitSet> list(attrNum);
    size_t prevImplSetSize = 0;

    for (size_t implCur = 0; implCur < implSetSize; ++implCur)
    {
        ImplicationInd impl = tmp[implCur];		

        LinClosureImproved::Apply(impl.Conclusion(), tmp, list, prevImplSetSize, impl.Conclusion());
        tmp[implCur] = impl;
    }

    for (int implCur = static_cast<int>(implSetSize) - 1; implCur >= 0; --implCur)
    {
        ImplicationInd impl = tmp[implCur];		
        tmp[implCur] = tmp.back();
        tmp.pop_back();

        Closure::Apply(impl.Premise(), tmp, impl.Premise());
        if (impl.Premise().is_proper_subset_of(impl.Conclusion()))
        {
            tmp.push_back(impl);
        }
    }

    return tmp;
}
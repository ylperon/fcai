# include <stdexcept>

# include "fca_closure.h"

bool FCA::Closure::Apply(const FCA::BitSet &current, const std::vector<FCA::ImplicationInd> &implications, FCA::BitSet &res, size_t prefLen)
{
    if (!implications.empty() && (implications.front().Premise().size() != current.size() || implications.front().Conclusion().size() != current.size()))
        throw std::invalid_argument("size of premise and consclusion must agreed with size of current");

    const size_t attrNum = current.size();
    const size_t implNum = implications.size();

    std::vector<bool> used(implNum, false);
    BitSet oldClosure(attrNum);
    oldClosure.set();
    BitSet newClosure = current;	

    while (oldClosure != newClosure)
    {
        oldClosure = newClosure;

        for (size_t implInd = 0; implInd < implNum; ++implInd)
            if (!used[implInd] && implications[implInd].Premise().is_subset_of(newClosure))
            {
                newClosure |= implications[implInd].Conclusion();

                if (!IsPrefixIdentical(newClosure, current, prefLen))
                {
                    return false;
                }

                used[implInd] = true;
            }
    }

    res = newClosure;
    return true;
}

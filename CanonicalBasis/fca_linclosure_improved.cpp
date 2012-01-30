# include <stdexcept>

# include "fca_linclosure_improved.h"

bool FCA::LinClosureImproved::Apply(const BitSet &current, const std::vector<FCA::ImplicationInd> &implications, BitSet &res, size_t prefLen)
{	
    if (!implications.empty() && (implications.front().Premise().size() != current.size() || implications.front().Conclusion().size() != current.size()))
        throw std::invalid_argument("size of premise and consclusion must agreed with size of current");

    const size_t attrNum = current.size();
    const size_t implNum = implications.size();	

    BitSet emptyBitSet(implNum);
    emptyBitSet.reset();

    std::vector<BitSet> list(attrNum, emptyBitSet);	

    //initialization	
    
    for (size_t implInd = 0; implInd < implNum; ++implInd)
    {				
        for (size_t attrInd = 0; attrInd < attrNum; ++attrInd)		
            if (implications[implInd].Premise().test(attrInd))
            {					
                list[attrInd].set(implInd);
            }		
    }

    //end of initialization

    //algorithmic part

    BitSet oldImpl(implNum);
    oldImpl.reset();
    BitSet newImpl(implNum);
    BitSet applyingImpl(implNum);	
    BitSet oldClosure(attrNum);
    oldClosure.reset();
    BitSet newClosure(current);	

    while (oldClosure != newClosure)
    {
        oldClosure = newClosure;
        BitSet tmp = newClosure;
        tmp.flip();

        applyingImpl.set();		
        for (size_t attrInd = 0; attrInd < attrNum; ++attrInd)
            if (tmp.test(attrInd))
            {
                applyingImpl -= list[attrInd];
            }

        newImpl = applyingImpl - oldImpl;		
        oldImpl = applyingImpl;

        for (size_t implInd = 0; implInd < implNum; ++implInd)
            if  (newImpl.test(implInd))
            {
                newClosure |= implications[implInd].Conclusion();

                if (!IsPrefixIdentical(newClosure, current, prefLen))
                {
                    return false;
                }
            }
    }

    //end of algorithmic part

    res = newClosure;
    return true;
}

bool FCA::LinClosureImproved::Apply(const BitSet &current, const std::vector<FCA::ImplicationInd> &implications,
                                    std::vector<BitSet> &list, size_t &prevImplSetSize, BitSet &res, const size_t prefLen)
{
    if (!implications.empty() && (implications.front().Premise().size() != current.size() || implications.front().Conclusion().size() != current.size()))
        throw std::invalid_argument("size of premise and consclusion must agreed with size of current");

    const size_t attrNum = current.size();
    const size_t implNum = implications.size();		

    //initialization

    if (prevImplSetSize != implNum)
    {
        for (size_t i = 0; i < attrNum; ++i)
            list[i].resize(implNum);
    
        for (size_t implInd = prevImplSetSize; implInd < implNum; ++implInd)
        {				
            for (size_t attrInd = 0; attrInd < attrNum; ++attrInd)		
                if (implications[implInd].Premise().test(attrInd))
                {					
                    list[attrInd].set(implInd);
                }		
        }

        prevImplSetSize = implNum;
    }

    //end of initialization

    //algorithmic part

    BitSet oldImpl(implNum);
    oldImpl.reset();
    BitSet newImpl(implNum);
    BitSet applyingImpl(implNum);	
    BitSet oldClosure(attrNum);
    oldClosure.reset();
    BitSet newClosure(current);	

    while (oldClosure != newClosure)
    {
        oldClosure = newClosure;
        BitSet tmp = newClosure;
        tmp.flip();

        applyingImpl.set();		
        for (size_t attrInd = 0; attrInd < attrNum; ++attrInd)
            if (tmp.test(attrInd))
            {
                applyingImpl -= list[attrInd];
            }

        newImpl = applyingImpl - oldImpl;		
        oldImpl = applyingImpl;

        for (size_t implInd = 0; implInd < implNum; ++implInd)
            if  (newImpl.test(implInd))
            {
                newClosure |= implications[implInd].Conclusion();

                if (!IsPrefixIdentical(newClosure, current, prefLen))
                {
                    return false;
                }
            }
    }

    //end of algorithmic part

    res = newClosure;
    return true;
}
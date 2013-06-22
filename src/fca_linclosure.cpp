# include <stdexcept>

# include "fca_linclosure.h"

bool FCA::LinClosure::Apply(const FCA::BitSet &current, const std::vector<FCA::ImplicationInd> &implications, FCA::BitSet &res, size_t prefLen)
{
    if (!implications.empty() && (implications.front().Premise().size() != current.size() || implications.front().Conclusion().size() != current.size()))
        throw std::invalid_argument("size of premise and consclusion must agreed with size of current");

    const size_t attrNum = current.size();
    const size_t implNum = implications.size();

    BitSet newdep(current);
    std::vector<size_t> count(implNum);
    std::vector<std::vector<size_t> > list(attrNum);

    //initialization
    
    for (size_t implInd = 0; implInd < implNum; ++implInd)
    {			
        count[implInd] = implications[implInd].Premise().count();		

        for (size_t attrInd = 0; attrInd < attrNum; ++attrInd)			
            if (implications[implInd].Premise().test(attrInd))		
            {
                list[attrInd].push_back(implInd);			
            }
    }

    std::vector<size_t> update;	
    std::vector<bool> use(attrNum, false);

    for (size_t i = 0; i < attrNum; ++i)
        if (current.test(i))		
        {
            use[i] = true;
            update.push_back(i);					
        }

    //end initialization

    //computation

    while (!update.empty())
    {
        size_t ind = update.back();
        update.pop_back();

        for (size_t i = 0; i < list[ind].size(); ++i)			
        {
            size_t impInd = list[ind][i];
            --count[impInd];

            if (count[impInd] == 0)
            {
                BitSet add = implications[impInd].Conclusion() - newdep;
                newdep |= add;

                if (!IsPrefixIdentical(newdep, current, prefLen))
                    return false;

                for (size_t attrInd = 0; attrInd < attrNum; ++attrInd)				
                    if (add.test(attrInd) && !use[attrInd])					
                    {
                        update.push_back(attrInd);											
                        use[attrInd] = true;
                    }
            }
        }		
    }

    //end computation

    res = newdep;
    return true;
}

bool FCA::LinClosure::Apply(const BitSet &current, const std::vector<FCA::ImplicationInd> &implications, std::vector<size_t> &premiseCount,
                            std::vector<std::vector<size_t> > &list, size_t &prevImplSetSize, BitSet &res, const size_t prefLen)
{
    if (!implications.empty() && (implications.front().Premise().size() != current.size() || implications.front().Conclusion().size() != current.size()))
        throw std::invalid_argument("size of premise and consclusion must agreed with size of current");

    const size_t attrNum = current.size();
    const size_t implNum = implications.size();

    //initialization
    
    if (prevImplSetSize != implNum)
    {
        premiseCount.resize(implNum);

        for (size_t implInd = prevImplSetSize; implInd < implNum; ++implInd)
        {			
            premiseCount[implInd] = implications[implInd].Premise().count();		
            for (size_t attrInd = 0; attrInd < attrNum; ++attrInd)			
                if (implications[implInd].Premise().test(attrInd))		
                {					
                    list[attrInd].push_back(implInd);			
                }
        }

        prevImplSetSize = implNum;
    }

    BitSet newdep(current);
    std::vector<size_t> update;	
    std::vector<bool> use(attrNum, false);

    for (size_t i = 0; i < attrNum; ++i)
        if (current.test(i))		
        {
            use[i] = true;
            update.push_back(i);					
        }

    std::vector<size_t> count = premiseCount;

    //end initialization

    //computation

    while (!update.empty())
    {
        size_t ind = update.back();
        update.pop_back();

        for (size_t i = 0; i < list[ind].size(); ++i)			
        {
            size_t impInd = list[ind][i];
            --count[impInd];

            if (count[impInd] == 0)
            {
                BitSet add = implications[impInd].Conclusion() - newdep;
                newdep |= add;

                if (!IsPrefixIdentical(newdep, current, prefLen))
                    return false;

                for (size_t attrInd = 0; attrInd < attrNum; ++attrInd)				
                    if (add.test(attrInd) && !use[attrInd])					
                    {
                        update.push_back(attrInd);											
                        use[attrInd] = true;
                    }
            }
        }		
    }

    //end computation

    res = newdep;
    return true;
}
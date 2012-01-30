# include "fca_implications.h"

# include <map>

FCA::Implication FCA::Convert(const FCA::ImplicationInd &impl, const std::vector<FCA::Attribute> &baseSet)
{
    return Implication(Convert(impl.Premise(), baseSet), Convert(impl.Conclusion(), baseSet));	
}

std::vector<FCA::Implication> FCA::Convert(const std::vector<FCA::ImplicationInd> &impl, const std::vector<FCA::Attribute> &baseSet)
{	
    std::vector<Implication> res;

    for (size_t i = 0; i < impl.size(); ++i)
        res.push_back(Convert(impl[i], baseSet));

    return res;
}

void FCA::Convert(const std::vector<FCA::Attribute> &current, const std::vector<FCA::Attribute> &attributes, const std::vector<FCA::Implication> &implications,
                    BitSet &cCurrent, std::vector<FCA::ImplicationInd> &cImplications)
{
    const size_t attrNum = attributes.size();
    const size_t implNum = implications.size();

    std::map<std::string, size_t> indexer;
    for (size_t i = 0; i < attrNum; ++i)
        indexer[attributes[i]] = i;
    
    cImplications.reserve(implNum);
    cCurrent.resize(attrNum);		
    cCurrent.reset();	

    for (size_t i = 0; i < current.size(); ++i)
        cCurrent.set(indexer[current[i]]);	

    FCA::ImplicationInd implTmp;

    implTmp.Premise().resize(attrNum);			
    implTmp.Conclusion().resize(attrNum);		

    for (size_t i = 0; i < implNum; ++i)
    {					
        implTmp.Premise().reset();
        implTmp.Conclusion().reset();	

        for (size_t j = 0; j < implications[i].Premise().size(); ++j)
            implTmp.Premise().set(indexer[implications[i].Premise()[j]]);
        for (size_t j = 0; j < implications[i].Conclusion().size(); ++j)
            implTmp.Conclusion().set(indexer[implications[i].Conclusion()[j]]);

        cImplications.push_back(implTmp);
    }
}
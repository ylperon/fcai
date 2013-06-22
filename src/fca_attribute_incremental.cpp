# include "fca_attribute_incremental.h"

# include "fca_bitset.h"
# include "fca_context.h"
# include "fca_implications.h"

//templates!
# include "fca_closure.h"

# include <algorithm>

namespace 
{
    class Preclosed
    {
    public:
        Preclosed() : concept(false) {}
        Preclosed(const FCA::BitSet &extent, const FCA::BitSet &intent) :
            premise(FCA::BitSet(intent.size())), extent(extent), intent(intent), concept(true) {}        
        Preclosed(const FCA::BitSet &premise, const FCA::BitSet &extent, const FCA::BitSet &intent) :
            premise(premise), extent(extent), intent(intent), concept(false) {}

        bool concept;
        FCA::BitSet premise;
        FCA::BitSet extent;
        FCA::BitSet intent;       

        bool isConcept() const
        {
            return concept;
        }

        bool operator <(const Preclosed &a) const
        {
            /*if (intent.is_subset_of(a.intent))
            {
                return true;
            }
            else if (a.intent.is_subset_of(intent))
            {
                return false;
            }*/

            if (concept)
            {
                if (a.concept)
                {
                    return intent < a.intent;
                }
                else
                {
                    return intent < a.premise;
                }
            }
            else
            {
                if (a.concept)
                {
                    return premise < a.intent;
                }
                else
                {
                    return premise < a.premise;
                }
            }
        }
    };

    void ProcessStableConcept(const Preclosed &p, const size_t attrCur, const FCA::BitSet &attrCurExtent,
                              const FCA::Context &cxt, const FCA::BitSet &attributesCur, 
                              std::vector<size_t> &newStable, std::vector<Preclosed> &newPreclosed)
    {        
        FCA::BitSet newExtent = p.extent & attrCurExtent;
        FCA::BitSet premise = p.intent;
        premise.set(attrCur);

        bool closed = true;
        for (size_t i = 0; i < newStable.size(); ++i)
        {
            Preclosed &newStableCur = newPreclosed[newStable[i]];
            if (newStableCur.premise.is_subset_of(premise) 
                && !newStableCur.intent.is_subset_of(premise))
            {
                closed = false;
                return;
            }            
        }      

        FCA::BitSet conclusion = cxt.closeAttr(premise) & attributesCur;        

        if (premise == conclusion)
        {
            newPreclosed.push_back(Preclosed(newExtent, premise));
        }
        else
        {
            newPreclosed.push_back(Preclosed(premise, newExtent, conclusion));
            newStable.push_back(newPreclosed.size() - 1);
        }
    }

    void ProcessModifiedImplication(const size_t pCur, const size_t attrCur, 
                                    Preclosed &p, std::vector<size_t> &minMod, 
                                    std::vector<size_t> &nonMinMod, std::vector<Preclosed> &newPreclosed)
    {
        p.intent.set(attrCur);
        for (size_t i = 0; i < minMod.size(); ++i)
        {
            Preclosed &impl = newPreclosed[minMod[i]];
            if (impl.premise.is_subset_of(p.premise))
            {
                p.premise.set(attrCur);                
                nonMinMod.push_back(pCur);
                return;
            }
        }

        newPreclosed.push_back(p);
        minMod.push_back(newPreclosed.size() - 1);
    }

    void ProcessModifiedConcept(const size_t pCur, const size_t attrCur, 
                                Preclosed &p, std::vector<size_t> &minMod, std::vector<size_t> &modConcepts, 
                                std::vector<Preclosed> &newPreclosed)
    {
        bool isPreclosed = true;
        for (size_t i = 0; i < minMod.size(); ++i)
        {
            Preclosed &impl = newPreclosed[minMod[i]];

            if (impl.premise.is_subset_of(p.intent))
            {
                isPreclosed = false;
                break;
            }
        }        

        if (isPreclosed)
        {
            Preclosed impl(p.intent, p.extent, p.intent);
            impl.intent.set(attrCur);
            newPreclosed.push_back(impl);
            minMod.push_back(newPreclosed.size() - 1);
        }        

        p.intent.set(attrCur);
        modConcepts.push_back(pCur);
    }

    //close function template!
    void AddAttribute(const size_t attrCur, const FCA::Context &cxt, std::vector<Preclosed> &preclosed,
                      std::vector<FCA::ImplicationInd> &basis)
    {
        FCA::BitSet attrCurExtent = cxt.getAttrExtentAsBitSetByIndex(attrCur);
        std::vector<size_t> oldStable;//newPreclosed indices
        std::vector<size_t> newStable;//newPreclosed indices
        std::vector<size_t> minMod;//newPreclosed indices
        std::vector<size_t> nonMinMod;//preclosed indices
        std::vector<size_t> modExtra;//preclosed indices
        std::vector<Preclosed> newPreclosed;

        FCA::BitSet attributesCur(cxt.getAttributesCnt());
        for (size_t i = 0; i <= attrCur; ++i)
        {
            attributesCur.set(i);
        }

        for (size_t i = 0; i < preclosed.size(); ++i)
        {
            Preclosed &preclosedCur = preclosed[i];
            if (preclosedCur.extent.is_subset_of(attrCurExtent))
            {
                if (preclosedCur.isConcept())
                {
                    ProcessModifiedConcept(i, attrCur, preclosed[i], minMod, modExtra, newPreclosed);
                }
                else
                {
                    ProcessModifiedImplication(i, attrCur, preclosed[i], minMod, nonMinMod, newPreclosed);                    
                }
            }
            else
            {
                newPreclosed.push_back(preclosed[i]);
                if (preclosedCur.isConcept())
                {
                    ProcessStableConcept(preclosed[i], attrCur, attrCurExtent, cxt, attributesCur, newStable, newPreclosed);                    
                }
                else
                {
                    oldStable.push_back(newPreclosed.size() - 1);
                }
            }
        }
     
        std::vector<FCA::ImplicationInd> implSet(oldStable.size() + newStable.size() 
                                                 + minMod.size() + nonMinMod.size());
        size_t shift = 0;
        for (size_t i = 0; i < oldStable.size(); ++i)
        {            
            implSet[i + shift].Premise() = newPreclosed[oldStable[i]].premise;
            implSet[i + shift].Conclusion() = newPreclosed[oldStable[i]].intent;
        }
        shift += oldStable.size();
        for (size_t i = 0; i < newStable.size(); ++i)
        {            
            implSet[i + shift].Premise() = newPreclosed[newStable[i]].premise;
            implSet[i + shift].Conclusion() = newPreclosed[newStable[i]].intent;
        }
        shift += newStable.size();
        for (size_t i = 0; i < minMod.size(); ++i)
        {
            implSet[i + shift].Premise() = newPreclosed[minMod[i]].premise;
            implSet[i + shift].Conclusion() = newPreclosed[minMod[i]].intent;
        }
        shift += minMod.size();
        for (size_t i = 0; i < nonMinMod.size(); ++i)
        {
            implSet[i + shift].Premise() = preclosed[nonMinMod[i]].premise;
            implSet[i + shift].Conclusion() = preclosed[nonMinMod[i]].intent;
        }

        size_t useless = 0;
        for (size_t i = shift; i < implSet.size(); ++i)
        {
            FCA::BitSet conclusion = implSet[i].Conclusion();
            implSet[i].Conclusion().reset();
            FCA::BitSet premise = implSet[i].Premise();

            FCA::Closure::Apply(premise, implSet, premise);

            if (premise != conclusion)
            {
                modExtra.push_back(nonMinMod[i - shift]);
                preclosed[nonMinMod[i - shift]].premise = premise;
                implSet[i].Conclusion() = conclusion;
            }
            else
            {
                implSet[i].Premise().reset();
                ++useless;
            }
        }

        if (attrCur == cxt.getAttributesCnt() - 1 && !implSet.empty())
        {                    
            size_t lastNonEmpty = implSet.size() - 1;
            for (size_t i = shift; i <= lastNonEmpty; ++i)
            {
                if (implSet[i].Premise().none())
                {
                    for (size_t j = lastNonEmpty; j > i; --j)
                    {
                        if (!implSet[j].Premise().none())
                        {
                            implSet[i] = implSet[j];
                            lastNonEmpty = j - 1;
                            break;
                        }
                    }
                }                
            }

            implSet.resize(implSet.size() - useless);
            basis = implSet;
        }        

        std::vector<Preclosed> modExtraSorted(modExtra.size());
        for (size_t i = 0; i < modExtra.size(); ++i)
        {
            modExtraSorted[i] = preclosed[modExtra[i]];
        }

        std::sort(modExtraSorted.begin(), modExtraSorted.end());

        preclosed = newPreclosed;
        preclosed.insert(preclosed.end(), modExtraSorted.begin(), modExtraSorted.end());
        //sort(preclosed.begin(), preclosed.end());
    }
};

# include <iostream>

void PrintsBitSet(const FCA::BitSet &s)
{
    for (size_t i = 0; i < s.size(); ++i)
    {
        std::cout << (s.test(i) ? "1" : "0");
    }
}

void PrintPreclosed(const Preclosed &p)
{
    PrintsBitSet(p.premise);
    std::cout << " | ";
    PrintsBitSet(p.extent);
    std::cout << " | ";
    PrintsBitSet(p.intent);
    std::cout << " | ";
    std::cout << (p.isConcept() ? "true" : "false") << std::endl;
}

std::vector<FCA::ImplicationInd> FCA::ComputeDGBasisAttrIncremental(const FCA::Context &cxt)
{
    std::vector<Preclosed> preclosed;
    const size_t attrNum = cxt.getAttributesCnt();
    const size_t objNum = cxt.getObjectsCnt();

    FCA::BitSet allObj(objNum);
    allObj.set();
    preclosed.push_back(Preclosed(allObj, FCA::BitSet(attrNum)));

    std::vector<FCA::ImplicationInd> basis;

    for (size_t attrCur = 0; attrCur < attrNum; ++attrCur)
    {
        AddAttribute(attrCur, cxt, preclosed, basis);
        
        /*std::cout << "Attribute " << attrCur + 1 << std::endl;
        std::cout << "-----------------------------------------------------" << std::endl;
        for (size_t i = 0; i < preclosed.size(); ++i)
        {
            PrintPreclosed(preclosed[i]);
        }        */
        //for (size_t i = 0; i < preclosed.size() - 1; ++i)
        //{
        //    const Preclosed &x = preclosed[i];
        //    for (size_t j = i + 1; j < preclosed.size(); ++j)
        //    {
        //        const Preclosed &y = preclosed[j];
        //        bool flag = false/*y.intent.is_proper_subset_of(x.intent)*/;
        //        if (x.concept)
        //        {
        //            if (y.concept)
        //            {
        //                flag |= y.intent.is_proper_subset_of(x.intent);
        //            }
        //            else
        //            {
        //                flag |= y.premise.is_proper_subset_of(x.intent);
        //            }
        //        }
        //        else
        //        {
        //            if (y.concept)
        //            {
        //                flag |= y.intent.is_proper_subset_of(x.premise);
        //            }
        //            else
        //            {
        //                flag |= y.premise.is_proper_subset_of(x.premise);
        //            }
        //        }

        //        if (flag)
        //        {
        //            /*std::cout << "ERROR" << std::endl; */
        //            std::cout << "Attribute " << attrCur << std::endl;
        //            PrintPreclosed(x);
        //            PrintPreclosed(y);
        //            return basis;
        //        }
        //    }
        //}
    }

    return basis;
}
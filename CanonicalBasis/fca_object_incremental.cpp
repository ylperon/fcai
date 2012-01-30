# include "fca_object_incremental.h"

# include "fca_utility.h"

static inline bool IsSubsumedBy(const FCA::ImplicationInd &implA, const FCA::ImplicationInd &implB)
{
    return implB.Premise().is_subset_of(implA.Premise()) && (implA.Conclusion() - implA.Premise()).is_subset_of(implB.Conclusion());
}

static bool IsNew(const FCA::ImplicationInd &impl, std::vector<FCA::ImplicationInd> &implications)
{
    if (impl.Conclusion().is_subset_of(impl.Premise()))
    {
        return false;
    }

    const size_t implicationsSize = implications.size();
    for (size_t implCur = 0; implCur < implicationsSize; ++implCur)
    {
        if (IsSubsumedBy(impl, implications[implCur]))
        {
            return false;
        }		
    }

    return true;
}

static bool RemoveSubsumed(const FCA::ImplicationInd &impl, std::vector<FCA::ImplicationInd> &implSet)
{
    const size_t implSetSize = implSet.size();

    bool canBeSubsumed = true;
    std::vector<bool> remove(implSetSize, false);
    for (size_t i = 0; i < implSetSize; ++i)
    {
        FCA::ImplicationInd &implCur = implSet[i];
        if (canBeSubsumed && IsSubsumedBy(impl, implCur))
        {
            return false;
        }
        else if (IsSubsumedBy(implCur, impl))		
        {
            remove[i] = true;
            canBeSubsumed =  false;
        }
    }

    size_t tmp = 0;
    RemoveElements(remove, tmp, implSet, tmp);
    return true;
}

static bool RemoveSubsumedAndMaximise(FCA::ImplicationInd &impl, std::vector<FCA::ImplicationInd> &implSet)
{
    if (impl.Conclusion().is_subset_of(impl.Premise()))
    {
        return false;
    }

    const size_t implSetSize = implSet.size();

    bool canBeSubsumed = true;
    std::vector<bool> remove(implSetSize, false);
    for (size_t i = 0; i < implSetSize; ++i)
    {
        FCA::ImplicationInd &implCur = implSet[i];
        if (canBeSubsumed && implCur.Premise().is_subset_of(impl.Premise()))
        {
            if ((impl.Conclusion() - impl.Premise()).is_subset_of(implCur.Conclusion()))
            {
                return false;
            }
            else
            {
                impl.Conclusion() |= implCur.Conclusion();
            }
        }
        else if (IsSubsumedBy(implCur, impl))		
        {
            remove[i] = true;
            canBeSubsumed =  false;
        }
    }

    size_t tmp = 0;
    RemoveElements(remove, tmp, implSet, tmp);
    return true;
}

static bool RemoveSubsumedAndMaximiseAll(FCA::ImplicationInd &impl, std::vector<FCA::ImplicationInd> &implSet)
{
    assert(!impl.Conclusion().is_subset_of(impl.Premise()));	

    const size_t implSetSize = implSet.size();
    
    std::vector<bool> remove(implSetSize, false);
    for (size_t i = 0; i < implSetSize; ++i)
    {
        FCA::ImplicationInd &implCur = implSet[i];
        if (implCur.Premise() == impl.Premise())
        {
            implCur.Conclusion() |= impl.Conclusion();
            return false;
        }
        else if (implCur.Premise().is_subset_of(impl.Premise()))
        {
            if ((impl.Conclusion() - impl.Premise()).is_subset_of(implCur.Conclusion()))
            {
                return false;
            }
            else
            {
                impl.Conclusion() |= implCur.Conclusion();
            }
        }
        else if (impl.Premise().is_subset_of(implCur.Premise()))		
        {
            if ((implCur.Conclusion() - implCur.Premise()).is_subset_of(impl.Conclusion()))
            {
                remove[i] = true;
            }
            else
            {
                implCur.Conclusion() |= impl.Conclusion();
            }
        }
    }

    size_t tmp = 0;
    RemoveElements(remove, tmp, implSet, tmp);
    return true;
}

static void UpdateBasis(const FCA::BitSet &curObjIntent, const size_t attrNum, std::vector<FCA::ImplicationInd> &basis)
{
    std::vector<FCA::ImplicationInd> valid;
    std::vector<FCA::ImplicationInd> invalid;
    const size_t basisSize = basis.size();

    //std::cout << "dividing basis into valid and invalid subsets" << std::endl;

    for (size_t i = 0; i < basisSize; ++i)
    {
        FCA::ImplicationInd &curImpl = basis[i];
        if (!curImpl.Premise().is_subset_of(curObjIntent) || curImpl.Conclusion().is_subset_of(curObjIntent))
        {
            valid.push_back(curImpl);
        }
        else
        {
            invalid.push_back(curImpl);
        }
    }

    //std::cout << "first processing of invalid implications" << std::endl;

    std::vector<FCA::ImplicationInd> newValid;
    const size_t invalidSize = invalid.size();
    for (size_t i = 0; i < invalidSize; ++i)
    {
        FCA::ImplicationInd newImpl(invalid[i].Premise(), invalid[i].Conclusion() & curObjIntent);
        if (IsNew(newImpl, valid) && RemoveSubsumed(newImpl, newValid))
        {
            newValid.push_back(newImpl);
        }
    }

    //std::cout << "second processing of invalid implications" << std::endl;

    valid.insert(valid.end(), newValid.begin(), newValid.end());
    newValid.clear();
    for (size_t implCur = 0; implCur < invalidSize; ++implCur)
    {
        for (size_t attrCur = 0; attrCur < attrNum; ++attrCur)
        {
            if (!curObjIntent.test(attrCur))
            {
                FCA::ImplicationInd newImpl(invalid[implCur]);
                newImpl.Premise().set(attrCur);
                newImpl.Conclusion().set(attrCur);	

                if (RemoveSubsumedAndMaximise(newImpl, valid) && RemoveSubsumedAndMaximiseAll(newImpl, newValid))
                {
                    newValid.push_back(newImpl);
                }
            }
        }
    }

    basis.clear();
    basis.insert(basis.end(), valid.begin(), valid.end());
    basis.insert(basis.end(), newValid.begin(), newValid.end());
}

std::vector<FCA::ImplicationInd> FCA::ObjIncremental(const FCA::Context &context)
{
    size_t attrNum = context.getAttributesCnt();
    size_t objNum = context.getObjectsCnt();
    std::vector<FCA::ImplicationInd> res;
    FCA::ImplicationInd implFirst;
    implFirst.Premise().resize(attrNum);
    implFirst.Premise().reset();
    implFirst.Conclusion().resize(attrNum);
    implFirst.Conclusion().set();
    res.push_back(implFirst);

    for (size_t objCur = 0; objCur < objNum; ++objCur)
    {
        FCA::BitSet curObjIntent = context.getObjIntentAsBitSetByIndex(objCur);		
        //std::cout << "object " << objCur << " processing" << std::endl;
        UpdateBasis(curObjIntent, attrNum, res);
        //std::cout << "basis size is " << res.size() << std::endl;
    }

    return res;
}
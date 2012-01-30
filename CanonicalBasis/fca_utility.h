# pragma once

# ifndef FCA_UTILITY_H_
# define FCA_UTILITY_H_

namespace FCA
{
    template <typename T>
    void RemoveElements(const std::vector<bool> &remove, const size_t elementInd, std::vector<T> &a, size_t &elementNextInd);
};

//=====================================================================================================================
//==========================================Realization of templates==========================================================
//=====================================================================================================================

template <typename T>
void FCA::RemoveElements(const std::vector<bool> &remove, const size_t elementInd, std::vector<T> &a, size_t &elementNextInd)
{	
    std::vector<bool> freePos = remove;
    const size_t aSize = a.size();	
    size_t aSizeNew = 0;
    size_t indToFill = 0;
    elementNextInd = 0;

    for (size_t i = 0; i < aSize; ++i)
        if (!freePos[i])
        {
            if (i <= elementInd)
            {
                elementNextInd++;
            }

            aSizeNew++;
            for (; indToFill < aSize && !freePos[indToFill]; ++indToFill);
            if (indToFill < i)
            {
                a[indToFill] = a[i];
                freePos[i] = true;
                freePos[indToFill] = false;				
            }
        }		

    a.resize(aSizeNew);
}

# endif //FCA_UTILITY_H_
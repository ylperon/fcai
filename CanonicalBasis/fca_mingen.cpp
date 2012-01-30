# include "fca_mingen.h"

# include <queue>

# include "test_functions.h"
# include <iostream>

static bool IsMinGen(FCA::BitSet a, const FCA::BitSet aClosed, const FCA::Context &cxt)
{
    const size_t attrNum = cxt.getAttributesCnt();

    for (size_t i = 0; i < attrNum; ++i)
    {
        if (a.test(i))
        {
            a.reset(i);

            if (cxt.closeAttr(a) == aClosed)
            {
                return false;
            }

            a.set(i);
        }
    }

    return true;
}

std::vector<FCA::ImplicationInd> FCA::MinGen1(const FCA::Context &cxt)
{
    std::vector<FCA::ImplicationInd> basis;
    std::queue<std::pair<FCA::ImplicationInd, size_t> > q;

    const size_t attrNum = cxt.getAttributesCnt();
    BitSet emptySet(attrNum);
    emptySet.reset();
    q.push(std::make_pair(FCA::ImplicationInd(emptySet, cxt.closeAttr(emptySet)), 0u));

    while (!q.empty())
    {
        std::pair<FCA::ImplicationInd, size_t> a = q.front();
        q.pop();

        /*FCA::Implication implTmp = Convert(a.first, cxt.getAttributes());
        std::cout << "implication: ";
        for (size_t i = 0; i < implTmp.Premise().size(); ++i)
            std::cout << implTmp.Premise()[i] + (i + 1 == implTmp.Premise().size() ? " --> " : ", ");
        for (size_t i = 0; i < implTmp.Conclusion().size(); ++i)
            std::cout << implTmp.Conclusion()[i] + (i + 1 == implTmp.Conclusion().size() ? "" : ", ");*/
        /*std::cout << "implication from q: ";
        for (size_t i = 0; i < attrNum; ++i)
        {
            if (a.first.Premise().test(i))
            {
                std::cout << i << " ";
            }
        }
        std::cout << "--> ";
        for (size_t i = 0; i < attrNum; ++i)
        {
            if (a.first.Conclusion().test(i))
            {
                std::cout << i << " ";
            }
        }
        std::cout << std::endl;*/

        if (a.first.Premise() != a.first.Conclusion())
        {
            basis.push_back(a.first);

            /*std::cout << "added to basis" << std::endl;*/
        }

        for (size_t i = a.second; i < attrNum; ++i)
        {
            /*std::cout << i << std::endl;*/

            BitSet minGen = a.first.Premise();
            minGen.set(i);
            BitSet minGenClosed = cxt.closeAttr(minGen);

            /*std::cout << "implication in cycle: ";
            for (size_t j = 0; j < attrNum; ++j)
            {
                if (minGen.test(j))
                {
                    std::cout << j << " ";
                }
            }
            std::cout << "--> ";
            for (size_t j = 0; j < attrNum; ++j)
            {
                if (minGenClosed.test(j))
                {
                    std::cout << j << " ";
                }
            }
            std::cout << std::endl;*/

            if (IsMinGen(minGen, minGenClosed, cxt))
            {
                /*std::cout << "mingen" << std::endl;*/
                q.push(std::make_pair(FCA::ImplicationInd(minGen, minGenClosed), i + 1));
            }
            minGen.reset(i);
        }
    }

    return basis;
}
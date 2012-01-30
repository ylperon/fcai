# pragma once

# ifndef FCA_DEFINITIONS_H_
# define FCA_DEFINITIONS_H_

# include <vector>
# include <string>

# include "fca_bitset.h"

namespace FCA
{
    typedef std::string Object;
    typedef std::string Attribute;

    inline bool IsPrefixIdentical(const BitSet &bitSet1, const BitSet &bitSet2, const size_t prefLen)
    {
        bool res = true;

        for (size_t i = 0; i < prefLen; ++i)
            if (bitSet1.test(i) != bitSet2.test(i))
            {
                res = false;
                break;
            }

        return res;
    }

    inline std::vector<Attribute> Convert(const BitSet &current, const std::vector<Attribute> &baseSet)
    {
        std::vector<FCA::Attribute> res;
        for (size_t i = 0; i < current.size(); ++i)
            if (current.test(i))
            {
                res.push_back(baseSet[i]);
            }

        return res;
    }
};

# endif //FCA_DEFINITIONS_H_
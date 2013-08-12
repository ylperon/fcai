# pragma once

# ifndef FCA_LINCLOSURE_IMPROVED_H_
# define FCA_LINCLOSURE_IMPROVED_H_

# include "fca_datastructures.h"

namespace FCA
{
    class LinClosureImproved
    {	
    public:		
        static bool Apply(const BitSet &current, const std::vector<ImplicationInd> &implications, BitSet &res, const size_t prefLen = 0);

        static bool Apply(const BitSet &current, const std::vector<ImplicationInd> &implications,
                          std::vector<BitSet> &list, size_t &prevImplSetSize, BitSet &res, const size_t prefLen = 0);
    };
};

# endif //FCA_LINCLOSURE_IMPROVED_H_
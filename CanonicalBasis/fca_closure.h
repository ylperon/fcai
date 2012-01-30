# pragma once

# ifndef FCA_CLOSURE_H_
# define FCA_CLOSURE_H_

# include "fca_datastructures.h"

namespace FCA
{
    class Closure
    {	
    public:			
        static bool Apply(const BitSet &current, const std::vector<ImplicationInd> &implications, BitSet &res, const size_t prefLen = 0);
    };
}

# endif FCA_CLOSURE_H_
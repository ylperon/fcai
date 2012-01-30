# pragma once

# ifndef FCA_IMPEC_H_
# define FCA_IMPEC_H_

# include <vector>

# include "fca_datastructures.h"

namespace FCA
{
    /*
       Impec algorithm		
       */
    std::vector<ImplicationInd> ComputeProperBasis(const Context &context);
};

# endif //FCA_IMPEC_H_
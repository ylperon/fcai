# pragma once

# ifndef FCA_OBJECT_INCREMENTAL_H_
# define FCA_OBJECT_INCREMENTAL_H_

# include <vector>

# include "fca_datastructures.h"

namespace FCA
{
    /*
       Object incremantal algorithm
       NOTE: does not work right!
       */
    std::vector<ImplicationInd> ObjIncremental(const Context &context);
};

# endif //FCA_OBJECT_INCREMENTAL_H_
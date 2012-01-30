# pragma once

# ifndef FCA_MINIMIZATION_H_
# define FCA_MINIMIZATION_H_

# include <vector>

# include "fca_datastructures.h"

namespace FCA
{
    std::vector<ImplicationInd> MinimalCover(const std::vector<ImplicationInd> &implSet);

    std::vector<ImplicationInd> MinimizeBasis(const std::vector<ImplicationInd> &implSet);
};

# endif //FCA_MINIMIZATION_H_
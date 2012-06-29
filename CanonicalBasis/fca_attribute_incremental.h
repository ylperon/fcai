# pragma once

# ifndef FCA_ATTRIBUTE_INCREMENTAL_H_
# define FCA_ATTRIBUTE_INCREMENTAL_H_

# include "fca_bitset.h"
# include "fca_implications.h"
# include "fca_context.h"

# include <vector>

namespace FCA
{
    std::vector<FCA::ImplicationInd> ComputeDGBasisAttrIncremental(const FCA::Context &cxt);
}

#endif //FCA_ATTRIBUTE_INCREMENTAL_H_
#include "fca_utility.h"

std::vector<std::string> FCA::GetNames(const FCA::BitSet &bs, const std::vector<std::string> &base) {
    std::vector<std::string> res;
    for (size_t i = 0; i < current.size(); ++i) {
        if (current.test(i)) {
            res.push_back(baseSet[i]);
        }
    }
    return res;
}

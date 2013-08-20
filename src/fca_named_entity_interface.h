#pragma once

#include <cstddef>

#include <vector>
#include <string>

#include "fca_bitset.h"

namespace FCA {
    class NamedEntityInterface {
    public:
        virtual void SetObjName(const size_t& objInd, const std::string& name) = 0;
        virtual const std::string& GetObjName(const size_t& objInd) const = 0;

        virtual void SetObjNames(const std::vector<std::string>& names) = 0;
        virtual const std::vector<std::string>& GetObjNames() const = 0;

        virtual void SetAttrName(const size_t& attrInd, const std::string& name) = 0;
        virtual const std::string& GetAttrName(const size_t& attrInd) const = 0;

        virtual void SetAttrNames(const std::vector<std::string>& names) = 0;
        virtual const std::vector<std::string>& GetAttrNames() const = 0;
    };
}

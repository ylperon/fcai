#include "fca_context.h"

#include <cassert>

#include "fca_bitset.h"

using namespace FCA;

Context::Context() : objSize(0),
                     attrSize(0) {
}

Context::Context(const Context& cxt) : objSize(cxt.objSize),
                                       attrSize(cxt.attrSize),
                                       table(cxt.table),
                                       tableTr(cxt.tableTr) {
}

Context::Context(const size_t& objSize,
                 const size_t& attrSize) : objSize(objSize),
                                           attrSize(attrSize) {
    table.resize(objSize);
    for (BitSetVector::iterator it = table.begin(); it != table.end(); ++it) {
        it->resize(attrSize);
    }
    tableTr.resize(attrSize);
    for (BitSetVector::iterator it = tableTr.begin(); it != tableTr.end(); ++it) {
        it->resize(objSize);
    }
}

Context::Context(const std::vector<std::vector<bool> >& table)
    : objSize(table.size())
{
    attrSize = table.empty() ? 0 : table.front().size();
    this->table.resize(objSize);
    for (BitSetVector::iterator it = this->table.begin(); it != this->table.end(); ++it) {
        it->resize(attrSize);
    }
    tableTr.resize(attrSize);
    for (BitSetVector::iterator it = tableTr.begin(); it != tableTr.end(); ++it) {
        it->resize(objSize);
    }

    for (size_t objInd = 0; objInd < objSize; ++objInd) {
        for (size_t attrInd = 0; attrInd < attrSize; ++attrInd) {
            if (table[objInd][attrInd]) {
                this->table[objInd].set(attrInd);
                tableTr[attrInd].set(objInd);
            }
        }
    }
}

Context::Context(const BitSetVector& table)
    : objSize(table.size()),
      table(table) {
    attrSize = table.empty() ? 0 : table.front().size();

    tableTr.resize(attrSize);
    for (BitSetVector::iterator it = tableTr.begin(); it != tableTr.end(); ++it) {
        it->resize(objSize);
    }

    for (size_t objInd = 0; objInd < objSize; ++objInd) {
        for (size_t attrInd = 0; attrInd < attrSize; ++attrInd) {
            if (table[objInd].test(attrInd)) {
                tableTr[attrInd].set(objInd);
            }
        }
    }
}

Context& Context::operator=(const Context& cxt) {
    if (&cxt == this) {
        return *this;
    }

    objSize = cxt.objSize;
    attrSize = cxt.attrSize;
    table = cxt.table;
    tableTr = cxt.tableTr;
    return *this;
}

void Context::Set(const size_t& objInd, const size_t& attrInd, const bool& val) {
    assert(objInd < objSize);
    assert(attrInd < attrSize);
    if (val) {
        table[objInd].set(attrInd);
        tableTr[attrInd].set(objInd);
    } else {
        table[objInd].reset(attrInd);
        tableTr[attrInd].reset(objInd);
    }
}

bool Context::Get(const size_t& objInd, const size_t& attrInd) const {
    assert(objInd < objSize);
    assert(attrInd < attrSize);
    return table[objInd].test(attrInd);
}

const BitSet& Context::Intent(const size_t& objInd) const {
    assert(objInd < objSize);
    return table[objInd];
}

const BitSet& Context::Extent(const size_t& attrInd) const {
    assert(attrInd < attrSize);
    return tableTr[attrInd];
}

BitSet Context::DrvtAttr(const BitSet& current) const {
    assert(current.size() == attrSize);
    BitSet res(objSize);
    for (size_t objInd = 0; objInd < objSize; ++objInd) {
        if (current.is_subset_of(table[objInd])) {
            res.set(objInd);
        }
    }
    return res;
}

BitSet Context::ClosureAttr(const BitSet& current) const {
    assert(current.size() == attrSize);
    return DrvtObj(DrvtAttr(current));
}

BitSet Context::DrvtObj(const BitSet& current) const {
    assert(current.size() == objSize);
    BitSet res(attrSize);
    for (size_t attrInd = 0; attrInd < attrSize; ++attrInd) {
        if (current.is_subset_of(tableTr[attrInd])) {
            res.set(attrInd);
        }
    }
    return res;
}

BitSet Context::ClosureObj(const BitSet& current) const {
    assert(current.size() == objSize);
    return DrvtAttr(DrvtObj(current));
}

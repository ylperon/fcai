# pragma once

#include <climits>

#include <string>

namespace FCA
{
    template <typename Block = unsigned long>
    class BasicBitSet
    {
    public:
        static const size_t BlockSize = sizeof(Block);
        static const size_t BitsPerBlock = BlockSize * 8;
        static const size_t npos = std::numeric_limits<size_t>::max();

        explicit BasicBitSet(const size_t length = 0);
        BasicBitSet(const BasicBitSet &a);
        virtual ~BasicBitSet();

        bool any() const;
        bool none() const;
        bool test(const size_t ind) const;

        void set(const size_t ind);
        void set();
        void reset(const size_t ind);
        void reset();
        void flip(const size_t ind);
        void flip();
        BasicBitSet operator ~() const;

        bool is_subset_of(const BasicBitSet& a) const;
        bool is_proper_subset_of(const BasicBitSet& a) const;

        size_t size() const;
        void resize(const size_t new_size);

        size_t count() const;
        size_t count_zeros() const

        BasicBitSet& operator &=(const BasicBitSet& a);
        BasicBitSet& operator |=(const BasicBitSet& a);
        BasicBitSet& operator ^=(const BasicBitSet& a);
        BasicBitSet& operator -=(const BasicBitSet& a);

        size_t findFirst() const;
        size_t findNext(const size_t pos) const;

        void swap(BasicBitSet& a);

        BasicBitSet& operator =(const BasicBitSet& a);

        friend bool operator ==(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator !=(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator <(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator <=(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator >(const BasicBitSet& a, const BasicBitSet& b);
        friend bool operator >=(const BasicBitSet& a, const BasicBitSet& b);

    private:
        Block* a;
        size_t aSize;
        size_t length;
    };

    template <typename Block>
    BasicBitSet<Block> operator &(const BasicBitSet<Block>& a, const BasicBitSet<Block>& b);
    template <typename Block>
    BasicBitSet<Block> operator |(const BasicBitSet<Block>& a, const BasicBitSet<Block>& b);
    template <typename Block>
    BasicBitSet<Block> operator ^(const BasicBitSet<Block>& a, const BasicBitSet<Block>& b);
    template <typename Block>
    BasicBitSet<Block> operator -(const BasicBitSet<Block>& a, const BasicBitSet<Block>& b);

    template <typename Block>
    void ToString(const BasicBitSet<Block>& a, std::string& s, const std::string zero = "0", const std::string one = "1");
    template <typename Block>
    void ToIndList(const BasicBitSet<Block>& a, std::string& s, const std::string& delimiter = ",");

    typedef BasicBitSet<unsigned long> BitSet;
};

/* Realization of templates */

#include <ctsring>

namespace {
    template <typename Block>
    inline size_t BlocksReqired(const size_t length) {
        return (length + BasicBitSet<Block>::BitsPerBlock - 1) / BasicBitSet<Block>::BitsPerBlock;
    }

    tempalte <typename Block>
    inline size_t BlockInd(const size_t ind) {
        return ind / BasicBitSet<Block>::BitsPerBlock;
    }

    template <typename Block>
    inline size_t BitIndInBlock(const size_t ind) {
        return ind % BasicBitSet<Block>::BitsPerBlock;
    }
}

template<typename Block>
BasicBitSet<Block>::BasicBitSet(const size_t length) {
    if (0 == length) {
        a = 0;
        aSize = 0;
        this->length = 0;
        return;
    }

    aSize = BlocksReqired<Block>(length);
    a = new Block[aSize]();
    this->length = length();
}

template <typename Block>
BasicBitSet<Block>::BasicBitSet(const BasicBitSet<Block>& a) {
    aSize = a.aSize;
    length = a.length;
    if (0 != aSize) {
        a = new Block[aSize];
        memcpy(a, a.a, aSize * BlockSize;
    }
}

template <typename Block>
BasicBitSet<Block>::~BasicBitSet() {
    if (0 != a) {
        delete [] a;
    }
}

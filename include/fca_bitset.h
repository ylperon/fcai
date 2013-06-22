# pragma once

# ifndef FCA_BITSET_H_
# define FCA_BITSET_H_

# include "fca_config.h"

# include <string>
# include <climits>

# ifdef BOOST_BITSET_ON
# include <boost/dynamic_bitset.hpp>
# endif //BOOST_BITSET_ON

# ifdef MAGIC_BITSET_ON
# include <src/bm.h>
# endif //MAGIC_BITSET_ON

namespace FCA
{
    class BitSet
    {
    public:
# ifdef BOOST_BITSET_ON
        static const size_t npos = UINT_MAX;
# endif //BOOST_BITSET_ON

        BitSet(const size_t newSize = 0);
        BitSet(const BitSet &a);

        bool none() const;
        bool test(const size_t ind) const;

        void set(const size_t ind);
        void set();
        void reset(const size_t ind);
        void reset();

        void flip();

        bool is_subset_of(const BitSet& a) const;
        bool is_proper_subset_of(const BitSet& a) const;

        size_t size() const;
        void resize(const size_t new_size);

        size_t count() const;

        BitSet &operator &=(const BitSet& a);
        BitSet &operator |=(const BitSet& a);
        BitSet &operator ^=(const BitSet& a);
        BitSet &operator -=(const BitSet& a);

        size_t findFirst() const;
        size_t findNext(const size_t pos) const;

        friend bool operator ==(const BitSet& a, const BitSet& b);
        friend bool operator !=(const BitSet& a, const BitSet& b);
        friend bool operator <(const BitSet& a, const BitSet& b);
        friend bool operator <=(const BitSet& a, const BitSet& b);
        friend bool operator >(const BitSet& a, const BitSet& b);
        friend bool operator >=(const BitSet& a, const BitSet& b);

    private:
# ifdef BOOST_BITSET_ON
        boost::dynamic_bitset<unsigned long> mBS;
# endif //BOOST_BITSET_ON

# ifdef MAGIC_BITSET_ON
        bm::bvector<> mBS;
# endif //MAGIC_BITSET_ON
    };

    BitSet operator &(const BitSet& a, const BitSet& b);
    BitSet operator |(const BitSet& a, const BitSet& b);
    BitSet operator ^(const BitSet& a, const BitSet& b);
    BitSet operator -(const BitSet& a, const BitSet& b);

    void ToString(const BitSet& a, std::string& s);
    void ToIndList(const BitSet& a, std::string& s, const std::string& delimiter = " ");
};

# endif //FCA_BITSET_H_
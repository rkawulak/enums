//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Vicente J. Botet Escriba 2011.
// Distributed under the Boost
// Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Based on the boost/array.hpp implementation
//
// See http://www.boost.org/libs/enums for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_ENUMS_ENUM_SET_HPP
#define BOOST_ENUMS_ENUM_SET_HPP

#include <boost/enums/enum_traits.hpp>
#include <bitset>
#include <iostream>
#include <boost/functional/hash.hpp>

#include <boost/config.hpp>


namespace boost {
  namespace enums {

    template<typename enum_type, 
             typename traits=enum_traits<enum_type> >
    class enum_set
    {
    public:
      BOOST_CONSTEXPR enum_set()
      {
      }
      BOOST_CONSTEXPR enum_set(enum_type setting)
      {
        set(setting);
      }
      BOOST_CONSTEXPR enum_set(unsigned long long val)
      {
      }
      enum_set &operator&=(const enum_set &rhs)
      {
        bits &= rhs.bits;
        return *this;
      }
      enum_set &operator|=(const enum_set &rhs)
      {
        bits |= rhs.bits;
        return *this;
      }
      enum_set &operator^=(const enum_set &rhs)
      {
        bits ^= rhs.bits;
        return *this;
      }
      enum_set &operator<<=(const enum_set &rhs)
      {
        bits <<= rhs.bits;
        return *this;
      }
      enum_set &operator>>=(const enum_set &rhs)
      {
        bits >>= rhs.bits;
        return *this;
      }
      std::size_t count() const
      {
        return bits.count();
      }
      BOOST_CONSTEXPR std::size_t size() const
      {
        return bits.size();
      }
      BOOST_CONSTEXPR bool operator[](enum_type testing) const
      {
        return bits.test(to_bit(testing));
      }
      //reference operator[](std::size_t pos);            // for b[i];
      enum_set &set()
      {
        bits.set();
        return *this;
      }
      enum_set &set(enum_type setting, bool value = true)
      {
        bits.set(to_bit(setting), value);
        return *this;
      }
      enum_set &reset()
      {
        bits.reset();
        return *this;
      }
      enum_set &reset(enum_type resetting)
      {
        bits.reset(to_bit(resetting));
        return *this;
      }
      enum_set &flip()
      {
        bits.flip();
        return *this;
      }
      enum_set &flip(enum_type flipping)
      {
        bits.flip(to_bit(flipping));
        return *this;
      }
      unsigned long to_ulong() const
      {
        return bits.to_ulong();
      }
      unsigned long long to_ullong() const
      {
        return bits.to_ulong();
      }
      enum_set operator~() const
      {
        return enum_set(*this).flip();
      }
      bool all() const
      {
        return bits.all();
      }
      bool any() const
      {
        return bits.any();
      }
      bool none() const
      {
        return bits.none();
      }
      enum_set operator<<(std::size_t pos) const 
      {
        enum_set r = *this;
        r <<= pos;
        return r;
      }
      enum_set operator>>(std::size_t pos) const
      {
        enum_set r = *this;
        r >>= pos;
        return r;
      }

    private:
      
      static std::size_t to_bit(enum_type value)
      {
        return traits::pos(value);
      }
      
      std::bitset<traits::size> bits;
      
    public:
      
      std::bitset<traits::size> detail_bits() { return bits; }
    };

    // enum_set operators:
    template <typename enum_type, typename traits> 
    enum_set<enum_type,traits> operator&(const enum_set<enum_type,traits>& x, const enum_set<enum_type,traits>& y)
    {
      enum_set<enum_type,traits> r = x;
      r &= y;
      return r;
    } 


    template <typename enum_type,  typename traits >
    enum_set<enum_type,traits> operator|(const enum_set<enum_type,traits>& x, const enum_set<enum_type,traits>& y)
    {
      enum_set<enum_type,traits> r = x;
      r |= y;
      return r;
    } 

    template <typename enum_type,  typename traits >
    enum_set<enum_type,traits> operator^(const enum_set<enum_type,traits>& x, const enum_set<enum_type,traits>& y)
    {
      enum_set<enum_type,traits> r = x;
      r ^= y;
      return r;
    } 
    

    template <class charT, class ch_traits, typename enum_type,  typename traits >
    std::basic_istream<charT, ch_traits>&
    operator>>(std::basic_istream<charT, ch_traits>& is, enum_set<enum_type,traits>& x)
    {
      return is >> x.detail_bits();
    }
    

    template <class charT, class ch_traits, typename enum_type,  typename traits >
    std::basic_ostream<charT, ch_traits>&
    operator<<(std::basic_ostream<charT, ch_traits>& os, const enum_set<enum_type,traits>& x) 
    {
      return os << x.detail_bits();
    }

    
  } /* namespace enums */

  template <typename enum_type, typename traits > 
  struct hash<enums::enum_set<enum_type,traits> >
  : public std::unary_function<enums::enum_set<enum_type,traits>, std::size_t>
  {
    std::size_t operator()(const enums::enum_set<enum_type,traits>& bs) const
    {
      return hash<std::bitset<traits::size> >(bs.detail_bits());
    }
  };

} /* namespace boost */


#endif /*BOOST_ENUMS_ENUM_SET_HPP*/

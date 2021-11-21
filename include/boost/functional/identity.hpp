/*=============================================================================
    Copyright (c) 2021 Denis Mikhailov
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).  
==============================================================================*/

#ifndef BOOST_FUNCTIONAL_IDENTITY_HPP_INCLUDED 
#define BOOST_FUNCTIONAL_IDENTITY_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/mpl/if.hpp>

namespace boost
{
    namespace functional { namespace detail {
        template<class T>
        struct move_reference
        {
            #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_DOXYGEN_INVOKED)
            typedef T &&                                                 type;
            #else
            typedef typename ::boost::mpl::if_
                < ::boost::has_move_emulation_enabled<T>
                , ::boost::rv<T>&
                , T & >::type                                            type;
            #endif
        };
    }}

    struct identity
    {
        typedef void is_transparent;

        template<class> struct result;

        template<class F, class T>
        struct result<F(T)>
            : functional::detail::move_reference<T>
        {};
        
        template<class F, class T>
        struct result<F(BOOST_RV_REF(T))>
            : functional::detail::move_reference<T>
        {};
        
        template<class F, class T>
        struct result<F(T&)> {
            typedef T& type;
        };
    
        template<class T>
        BOOST_CONSTEXPR typename result<identity(BOOST_RV_REF(T))>::type operator()( BOOST_RV_REF(T) t ) const BOOST_NOEXCEPT
        {
            return ::boost::move(t);
        }
        
        template<class T>
        BOOST_CONSTEXPR typename result<identity(T&)>::type operator()(T& t) const BOOST_NOEXCEPT
        {
            return t;
        }
    };
} // boost

#endif // BOOST_FUNCTIONAL_IDENTITY_HPP_INCLUDED


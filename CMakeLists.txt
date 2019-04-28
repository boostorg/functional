# Copyright 2019 Sam Day
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
#
# NOTE: CMake support for Boost.functional is currently experimental at best
#       and the interface is likely to change in the future

cmake_minimum_required(VERSION 3.5)
project(BoostFunctional LANGUAGES CXX)

add_library(boost_functional INTERFACE)
add_library(Boost::functional ALIAS boost_functional)

target_include_directories(boost_functional INTERFACE include)

target_link_libraries(boost_functional
        INTERFACE
        Boost::config
        Boost::core
        Boost::function
        Boost::function_types
        Boost::iterator
        Boost::mpl
        Boost::optional
        Boost::preprocessor
        Boost::type_traits
        Boost::typeof
        Boost::utility
        )

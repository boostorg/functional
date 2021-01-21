#!/bin/bash

# Copyright 2020 Rene Rivera, Sam Darwin
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at http://boost.org/LICENSE_1_0.txt)

set -e
export TRAVIS_BUILD_DIR=$(pwd)
export DRONE_BUILD_DIR=$(pwd)
export TRAVIS_BRANCH=$DRONE_BRANCH
export VCS_COMMIT_ID=$DRONE_COMMIT
export GIT_COMMIT=$DRONE_COMMIT
export REPO_NAME=$DRONE_REPO
export PATH=~/.local/bin:/usr/local/bin:$PATH

if [ "$DRONE_JOB_BUILDTYPE" == "boost" ]; then

echo '==================================> INSTALL'

BOOST_BRANCH=develop && [ "$TRAVIS_BRANCH" == "master" ] && BOOST_BRANCH=master || true
cd ..
git clone -b $BOOST_BRANCH https://github.com/boostorg/boost.git boost
cd boost
git submodule update --init tools/build
git submodule update --init libs/config
git submodule update --init tools/boostdep
mkdir -p libs/functional
cp -r $TRAVIS_BUILD_DIR/* libs/functional
python tools/boostdep/depinst/depinst.py -I forward/test -I factory/test -I overloaded_function/test functional
./bootstrap.sh
./b2 headers

echo '==================================> SCRIPT'

echo "using $TOOLSET : : $COMPILER ;" > ~/user-config.jam
cd libs/functional
../../b2 -j 3 test toolset=$TOOLSET cxxstd=$CXXSTD
../../b2 -j 3 forward/test toolset=$TOOLSET cxxstd=$CXXSTD
../../b2 -j 3 factory/test toolset=$TOOLSET cxxstd=$CXXSTD
../../b2 -j 3 overloaded_function/test toolset=$TOOLSET cxxstd=$CXXSTD

fi

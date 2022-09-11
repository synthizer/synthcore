#!/usr/bin/env bash
#
# Build the Synthcore CI for Linux. Respects all the usual environment variables.
set -ex

sudo apt update

# GitHub doesn't give us Ninja
sudo apt-fast install -y ninja-build virtualenv

git submodule update --init --recursive
mkdir -p build
cd build
cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Release
ninja
ninja test

#!/bin/bash

# Print commands and exit on errors
set -xe


apt-get update

apt-get install -y --no-install-recommends --fix-missing\
  autoconf \
  automake \
  bison \
  build-essential \
  ca-certificates \
  cmake \
  cpp \
  curl \
  emacs24 \
  flex \
  git \
  libboost-dev \
  libboost-filesystem-dev \
  libboost-iostreams1.58-dev \
  libboost-program-options-dev \
  libboost-system-dev \
  libboost-test-dev \
  libboost-thread-dev \
  libc6-dev \
  libevent-dev \
  libffi-dev \
  libfl-dev \
  libgc-dev \
  libgc1c2 \
  libgflags-dev \
  libgmp-dev \
  libgmp10 \
  libgmpxx4ldbl \
  libjudy-dev \
  libpcap-dev \
  libreadline6 \
  libreadline6-dev \
  libssl-dev \
  libtool \
  linux-headers-$KERNEL\
  lubuntu-desktop \
  make \
  mktemp \
  pkg-config \
  python \
  python-dev \
  python-ipaddr \
  python-pip \
  python-psutil \
  python-scapy \
  python-setuptools \
  tcpdump \
  unzip \
  vim \
  wget \
  xcscope-el \
  xterm


#Src 
BMV2_COMMIT="b447ac4c0cfd83e5e72a3cc6120251c1e91128ab"  # August 10, 2019
PI_COMMIT="41358da0ff32c94fa13179b9cee0ab597c9ccbcc"    # August 10, 2019
P4C_COMMIT="69e132d0d663e3408d740aaf8ed534ecefc88810"   # August 10, 2019
PROTOBUF_COMMIT="v3.2.0"
GRPC_COMMIT="v1.3.2"

#Get the number of cores to speed up the compilation process
NUM_CORES=`grep -c ^processor /proc/cpuinfo`

# --- Mininet --- #
git clone git://github.com/mininet/mininet mininet
sudo ./mininet/util/install.sh -nwv

# --- Protobuf --- #
git clone https://github.com/google/protobuf.git
cd protobuf
git checkout ${PROTOBUF_COMMIT}
export CFLAGS="-Os"
export CXXFLAGS="-Os"
export LDFLAGS="-Wl,-s"
./autogen.sh
./configure --prefix=/usr
make -j${NUM_CORES}
sudo make install
sudo ldconfig
unset CFLAGS CXXFLAGS LDFLAGS
# Force install python module
cd python
sudo python setup.py install
cd ../..

# --- gRPC --- #
git clone https://github.com/grpc/grpc.git

cd grpc
git checkout ${GRPC_COMMIT}
git submodule update --init --recursive
export LDFLAGS="-Wl,-s"
make -j${NUM_CORES}
sudo make install
sudo ldconfig
unset LDFLAGS
cd ..
# Install gRPC Python Package
sudo pip install grpcio



# --- BMv2 deps (needed by PI) --- #
git clone https://github.com/p4lang/behavioral-model.git
cd behavioral-model
git checkout ${BMV2_COMMIT}
# From bmv2's install_deps.sh, we can skip apt-get install.
# Nanomsg is required by p4runtime, p4runtime is needed by BMv2...
tmpdir=`mktemp -d -p .`
cd ${tmpdir}
bash ../travis/install-thrift.sh
bash ../travis/install-nanomsg.sh
sudo ldconfig
bash ../travis/install-nnpy.sh
cd ..
sudo rm -rf $tmpdir
cd ..


# --- PI/P4Runtime --- #
git clone https://github.com/p4lang/PI.git
cd PI
git checkout ${PI_COMMIT}
git submodule update --init --recursive
./autogen.sh
./configure --with-proto
make -j${NUM_CORES}
sudo make install
sudo ldconfig
cd ..

# --- Bmv2 --- #
cd behavioral-model
./autogen.sh
./configure --enable-debugger --with-pi
make -j${NUM_CORES}
sudo make install
sudo ldconfig
# Simple_switch_grpc target
cd targets/simple_switch_grpc
./autogen.sh
./configure --with-thrift
make -j${NUM_CORES}
sudo make install
sudo ldconfig
cd ../../..



# --- P4C --- #
git clone https://github.com/p4lang/p4c
cd p4c
git checkout ${P4C_COMMIT}
git submodule update --init --recursive
mkdir -p build
cd build
cmake ..
make -j${NUM_CORES}
sudo make install
sudo ldconfig
cd ../..


# Do this last!
#sudo reboot

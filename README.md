
# Casacore

A suite of C++ libraries for radio astronomy data processing.


# Installation

## Debian / Ubuntu

Casacore is now part of Debian and Ubuntu, use apt to search for the package you need:
```bash
$ apt-get update
$ apt-get search casacore

```

## MacOS

Use Homebrew with the `ska-sa` tap to install casacore:

```bash
$ brew tap ska-sa/tap
$ brew install casacore
```

## Docker

We now also publish docker images for each github branch on [quay.io](https://quay.io/repository/casacore/casacore):
```
$ docker pull quay.io/casacore/casacore:master
```

## Building from source

### Getting the source code

The casacore source code is maintained on github.

You can obtain it using:

```
$ git clone https://github.com/casacore/casacore
```

### Requirements

To compile casacore you need to meet the following requirements:

* cmake
* gfortran
* g++
* flex 
* bison
* blas
* lapack
* cfitsio (3.181 or later)
* wcslib (4.20 or later)
* sofa (optional, only for testing casacore measures)
* fftw3
* hdf5 (optional)
* numpy (optional)
* boost-python (optional)
* ncurses (optional)

On Debian / Ubuntu you can install these with:
 ``` 
$ sudo apt-get install build-essential cmake gfortran g++ libncurses5-dev \
    libreadline-dev flex bison libblas-dev liblapacke-dev libcfitsio-dev \
    wcslib-dev libfftw3-dev
```

and the optional libraries:
```
$ sudo apt-get install libhdf5-serial-dev python-numpy \
    libboost-python-dev libpython3.4-dev libpython2.7-dev
```

On CentOS7 you can install these with:
 ```bash 
$ sudo yum install cmake cmake-gui gcc-gfortran gcc-c++ flex bison \
        blas blas-devel  lapack lapack-devel cfitsio cfitsio-devel \
        wcslib wcslib-devel ncurses ncurses-devel readline readline-devel\
        python-devel boost boost-devel fftw fftw-devel hdf5 hdf5-devel\
        numpy boost-python 
```

## Obtaining measures data

Various parts of casacore require measures data, which requires regular
updating. You can obtain the WSRT measures archive from the ASTRON FTP server:

ftp://ftp.astron.nl/outgoing/Measures/

Extract this somewhere on a permanent location on your filesystem.


## Compilation

In the casacore source folder run:
```
mkdir build
cd build
cmake ..
make 
make install
```

there are various flags available to cmake to enable and disable options:
```
$ cmake -DDATA_DIR=/usr/share/casacore/data -DUSE_OPENMP=ON \
    -DUSE_HDF5=ON -DBUILD_PYTHON3=ON -DUSE_THREADS=ON
```

The `DATA_DIR` should point to the location where you extracted the measures
data. Special variables `%CASAROOT%` and `%CASAHOME%` can be used here, which
can be set at run time through the `.casarc` file.

Older versions of CMake may have problems detecting the correct python
libraries and headers, in which case you may need to set them manually. For
example:
```
-DPYTHON3_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.4m.so
-DPYTHON3_INCLUDE_DIR=/usr/include/python3.4
```

To configure Python3 specific settings use:
```
PYTHON3_EXECUTABLE
PYTHON3_LIBRARY
PYTHON3_INCLUDE_DIR
```

If you run into problems with boost libraries, try setting `-DBoost_NO_BOOST_CMAKE=True`. This may be necessary if you have the libraries from NRAO casa in your `PATH` or `LD_LIBRARY_PATH`.


# Documentation

http://casacore.github.io/casacore


# Problems & bugs

If you have any issues compiling or using casacore, please open an issue on
the issue tracker on github.

If you have patches please open a pull request. Your contributions are more
than welcome! But to maintain a high code quality we have written a [contribution
manual](https://github.com/casacore/casacore/blob/master/CONTRIBUTING.md), please read
that first.

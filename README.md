MolSim
===

# Group B #
Members:
* Trouvain, Mira
* Paluca, Denis
* Höbenreich, Jonas

# Code #
* Link:     https://gitlab.lrz.de/denis/psemoldyn_groupb
* Branch:   master
* commit:   5515b42b


# Build and Run Instructions #
## Requirements
- log4cxx

## MolSim program ##

* Compile with

      cmake -DDISABLE_DOXYGEN=ON -DCMAKE_BUILD_TYPE=Debug  -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
      make MolSim -j <1.5 * number of cores>

* run main program with parameters specified in assignment:

      ./MolSim ./inputs/a4_task2_big.xml

* Compile on Cluster (Deactivate log4cxx)

      cmake -DCMAKE_BUILD_TYPE=Release -DCLUSTER=ON -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
      module load xerces-c
      cmake --build . --target MolSim -- -j 20

### General program call

    ./MolSim <PATH_TO_INPUT_FILE>

or for performance testing:

    ./MolSim <PATH_TO_INPUT_FILE> -pt


## Tests ##

* Compile with

      cmake -DDISABLE_DOXYGEN=ON -DCMAKE_BUILD_TYPE=Debug  -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
      make Tests_run -j <1.5 * number of cores>

* run

      ctest

  or

      cd tests/
      ./Tests_run

## Doxygen documentation ##
* Build with

      cmake -DCMAKE_BUILD_TYPE=Debug  -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
      make doc_doxygen

# Input file format #

see [XSD file](src/xml/molsimInput.xsd)


# Media #
[a4_task2_small](https://drive.google.com/file/d/1aw64mb15kDxaAv4R7cmE2Gn9NAlWmGjA/view?usp=sharing)
[a4_task2_big](https://drive.google.com/file/d/1kqHamMl4Mp_a6qN0-M0tA9YjbzNBlqj3/view?usp=sharing)
[a4_task3_liquid_drop](https://drive.google.com/file/d/1uae9d61mVhXXM8lZ0S2nF4SG7qpv-i0j/view?usp=sharing)

# Performance measurements

The OS/hardware the measurements were made on:

* OS: Ubuntu 20.04.1 LTS x86_64
* Kernel: 5.4.0-58-generic
* CPU: Intel® Core™ i5-7200U CPU @ 2.50GHz × 4
* GPU: Mesa Intel® HD Graphics 620 (KBL GT2)
* Memory: 15,6 GiB

check /results for the performance results + gprof

# Misc #
* Compiler used: gcc 9.3.0
* CMake version: 3.16.3
* Google Tests version: 1.10.0
* modules used on cluster:
 1) admin/1.0     4) spack/staging/20.2.2   7) intel-mpi/2019-intel
 2) tempdir/1.0   5) intel/19.0.5           8) xerces-c/3.2.1
 3) lrz/1.0       6) intel-mkl/2019         9) gcc/8.4.0

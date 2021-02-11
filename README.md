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

      cmake -DDISABLE_DOXYGEN=ON -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
      make MolSim -j <1.5 * number of cores>

* run main program with parameters specified in assignment:

      ./MolSim ./inputs/a4_task2_big.xml

* Compile on Cluster (Deactivate log4cxx)

      cmake -DCMAKE_BUILD_TYPE=Release -DCLUSTER=ON -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
      module load xerces-c
      cmake --build . --target MolSim -- -j 20

* Activate Parallelisation with -DOPENMP=ON

      cmake -DCMAKE_BUILD_TYPE=Release -DOPENMP=ON -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
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
[a5_task2_video.avi](https://drive.google.com/file/d/1T6ypf7Qek-owrdILxEOuj4Atf6zmvKLx/view?usp=sharing)
[as5_t4_26.avi](https://drive.google.com/file/d/1HPVTg1iEnUOAUZofZR4p_xkNRUYAX_6l/view?usp=sharing)
[Task 1 membrane](https://drive.google.com/file/d/1mTAT7tAO44DzkyHdFgzboZ6Rsxf0HxSx/view?usp=sharing)

Additional Membrane Simulations:
[Membrane and cube](https://drive.google.com/file/d/1DG6d8Z7FFKXyN2JBhcVh5xnsQOFyBqCZ/view?usp=sharing)
[Membrane lifted on three corners](https://drive.google.com/file/d/1O89fWv2RaxQ0OOwP6AbDQTYlpC8QaymB/view?usp=sharing)

# Performance measurements
The OS/hardware the measurements were made on Linux Cluster (COOL-MUC 2)
        Locks                   Thread Forces
        A4_task2    A5_task2    A4_task2    A5_task2
icpc    3.2         0.45        1.76        0.65
gcc     4.1         0.75        2.03        0.709

# Misc #
* Compiler used: gcc 9.3.0
* CMake version: 3.16.3
* Google Tests version: 1.10.0
* modules used on cluster:
 1) admin/1.0     4) spack/staging/20.2.2   7) intel-mpi/2019-intel
 2) tempdir/1.0   5) intel/19.0.5           8) xerces-c/3.2.1
 3) lrz/1.0       6) intel-mkl/2019         9) gcc/8.4.0

MolSim
===

# Group B #
Members:
* Höbenreich, Jonas
* Paluca, Denis
* Trouvain, Mira

---

# Build and Run Instructions #
## Task: MolSim program ##
* Compile with 

      cmake -DDISABLE_DOXYGEN=ON -DCMAKE_BUILD_TYPE=Debug  -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
      make MolSim -j <1.5 * number of cores>
      
* run 

      ./MolSim eingabe-sonne.txt

## Task: Doxygen documentation ##
* Build with

      cmake -DCMAKE_BUILD_TYPE=Debug  -G "CodeBlocks - Unix Makefiles" {PATH_TO_PROJECT}
      make doc_doxygen

---

# Media #
[Simulation video](https://drive.google.com/file/d/1UxXaNrurPYt-dpr_sanyrpkHd82IDQil/view?usp=sharing)

---

# Misc #
* Compiler used: gcc 9.3.0
* CMake version: 3.16.3
* Google Tests version: 1.10.0


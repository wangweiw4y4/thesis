VisibleSim + Centrality-based leader algorithms
================================

This folder provides codes and scripts used for the evaluation of our work on network centrality.

In this thesis, we proposed a collection of distributed centrality-based leader algorithms, namely the k-BFS SumSweep, ABC-Center and PC2LE (Probabilistic-Counter based Central-Leader Election). We compare our algorithms to existing ones: BARYCENTER [1], MIN-ID [2], TBCE [3], [4] and [5]. We adapted some of these algorithms to make them fit our target system (see thesis document for more details).

## Associated publications

Naz, A., Piranda, B., Goldstein, S. C., & Bourgeois, J. (2015, September). ABC-Center: Approximate-center election in modular robots. In Intelligent Robots and Systems (IROS), 2015 IEEE/RSJ International Conference on (pp. 2951-2957). IEEE.

Naz, A., Piranda, B., Goldstein, S. C., & Bourgeois, J. (2016, March). Approximate-Centroid Election in Large-Scale Distributed Embedded Systems. In Advanced Information Networking and Applications (AINA), 2016 IEEE 30th International Conference on (pp. 548-556). IEEE.

## Mismatch between the algorithm names in the thesis and in the implementation:

The names of algorithms used in the thesis manuscript do not all match the names used in the implementation source code. Here is a mapping (manuscript -> implementation code) if the reader wants to navigate through the code.

* ABC-CenterV1 -> ABC-CenterV1 (originally named ABC-Center)
* ABC-CenterV2 -> ABC-CenterV2 (note that it is also named ABC-Center-Tree sometimes)
* BARYCENTER -> Exact (note that we sometimes rename it Exact or n-BFS in our papers)
* MIN-ID -> Simple
* k-BFS SumSweep -> ExtremumCenter
* k-BFS-SEQ -> RandCenter2
* k-BFS-RAND -> ParallelRandCenter
* PC2LE -> E2ACE
* PC2LE-MC2 -> DEE
* TBCE -> TBCE

## How to have a look to the source code of our algorithms and the ones used for comparisons?

All the algorithm source codes are available the [applicationsSrc/centrality](applicationsSrc/centrality) folder. Here are direct links to the main code of the different algorithms:

* [ABC-CenterV1 (originally named ABC-Center)](applicationsSrc/centrality/abcCenterV1/abcCenterV1.cpp)
* [ABC-CenterV2 (sometimes named ABC-Center-Tree also)](applicationsSrc/centrality/abcCenterV2/abcCenterV2.cpp)
* [BARYCENTER (note that we sometimes rename it Exact or n-BFS in our papers)](applicationsSrc/centrality/exact/exact.cpp)
* [MIN-ID](applicationsSrc/centrality/simple/simple.cpp)
* [k-BFS SumSweep](applicationsSrc/centrality/extremumCenter/extremumCenter.cpp)
* [k-BFS-RAND-SEQ](applicationsSrc/centrality/randCenter2/randCenter2.cpp)
* [k-BFS-RAND-PAR](applicationsSrc/centrality/parallelRandCenter/parallelRandCenter.cpp)
* [PC2LE](applicationsSrc/centrality/e2ace/e2ace.cpp)
* [PC2LE-MC2](applicationsSrc/centrality/dee/dee.cpp)
* [TBCE](applicationsSrc/centrality/tbce/tbce.cpp)

## How to run the algorithms?

1. Compile the algorithms and VisibleSim (the procedure is described below).
2. Run an algorithm
```
./centrality -R -k BB -i -a [simulation seed] -c [xml configuration file] -A [algorithm id] -H [hashfunc id] [parameters] -V [version]

# Possible parameters values are listed below.

# For instance:

## ABC-CenterV2:
./centrality -R -k BB -a 12 -c evaluation/confs/confs/bb/r/100/106.xml -A 4

## k-BFS SumSweep to elect an approximate center node:
/centrality -R -k BB -a 12 -c evaluation/confs/confs/bb/r/100/106.xml -A 10 -V 1

## PC2LE, HyperLogLog counter with Knuth's hash function to elect an approximate center node:
./centrality -R -k BB -a 12 -c evaluation/confs/confs/bb/r/100/106.xml -A 5 -P 3 -H 4 0 -V 1
```

Parameter possible values:
* Simulation seed: any number, "-1" for a randomly generated seed
* Algorithm id:
  * MIN-ID = 1
  * ABC_CENTER_V1 = 3
  * ABC_CENTER_V2 = 4
  * PC2LE = 5
  * TBCE = 6
  * BARYCENTER = 7
  * k-BFS SumSweep = 10 (k = 10, hard coded)
  * PC2LE-MC2 = 12
  * k-BFS-RAND-SEQ = 13 (k = 10, hard coded)
  * k-BFS-RAND-PAR = 14 (k = 10, hard coded)
* Versions:
  * (Approximate) Center node election = 1
  * (Approximate) Centroid node election = 2
* Probabilistic Counters:
  * Flajollet-Martin = 2
  * HyperLogLog = 3
* Hash-function id and parameters. For the parameters, simply input '0' to automatically use the best possible parameters.
  * Affine = 1
  * Affine (h(x) = ax + b, with a and b prime) = 2
  * KNUTH = 3
  * MURMUR3 = 4
  * FNV1 = 5
  * Random numbers = 6

## How to reproduce the evaluation done for the thesis?

1. Compile the algorithms and VisibleSim (the procedure is described below).
2. Launch the evaluation script.
```
cd applicationsBin/centrality/
./evaluation.sh
```
3. Place the binary file of [GraphAnalyzer](https://github.com/nazandre/GraphAnalyzer) in `evaluation/bin`.
4. Extract collected data and plot graphs. Plots are generated in the 'evalulation/plots' folder.
```
cd evaluation
./evaluation.sh
```

## How to compile VisibleSim and its applications?

Applications are implicitely compiled when VisibleSim is compiled.

### Dependencies:
 - Boost C++ Libraries >= 1.47.0 (If using Meld Process only)
 - GLUT
 - GLEW
 - SBCL - to compile Meld programs
 - MUPARSER - to use CSG

### Ubuntu Installation:

1\. Install dependencies:
```shell
sudo apt-get install libboost-all-dev
sudo apt-get install freeglut3-dev
sudo apt-get install libglew-dev
sudo apt-get install sbcl
sudo apt-get install libmuparser-dev
```
2\. `make`

## References

BARYCENTER
[1] Mamei, M., Vasirani, M., and Zambonelli, F. (2005). Self-organizing spatial shapes in mobile particles: The tota approach. Organising Systems, pages 138–153. Springer.

[2] Raynal, M. (2013). Distributed algorithms for message-passing systems, section 4.5, volume 500. Springer.

[3] Kim, C., and Wu, M. (2013). Leader election on tree-based centrality in ad hoc networks. Telecommunication Systems, 52(2):661–670.

[4] Garin, F., Varagnolo, D., and Johansson, K. H. (2012). Distributed estimation of diameter, radius and eccentricities in anonymous networks. IFAC Proceedings Volumes, 45(26):13–18.

[5] Eppstein, D., and Wang, J. (2001). Fast approximation of centrality. In Proceedings of the twelfth annual ACM-SIAM symposium on Discrete algorithms, pages 228–229. Society for Industrial and Applied Mathematics.


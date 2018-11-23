CollectBall QD
==============

CollectBall QD is an adaptation of [CollectBall](https://github.com/doncieux/collectball) to work with __Modular QD__.

## Installation

There is a _Dockerfile_ if you wish to launch the experiment through a docker or to see all the commands necessary for installation.

### Dependencies

Install the following programs and their dependencies : 

* [Sferes2](https://github.com/sferes2/sferes2.git)
* [LibFastSim](https://github.com/jbmouret/libfastsim)
* [NN2](https://github.com/sferes2/nn2)
* [Modular QD](https://github.com/sferes2/modular_QD.git)

### Installation : CollectaBall QD

*Note 1 : Here we decided to overwrite Modular QD wscript with the one from ColectBall QD in order to build only collectball QD and no other experiences.
If you wish to maintain your wscript, just copy-paste the relevant lines instead of overwriting (`collect_varts` and `sferes.create_variants` lines).*

*Note 2 : [...]/ corresponds to the folder where you installed sferes2.*

```BASH
cd [...]/sferes2/exp/modular_QD/scenarii && git clone https://github.com/TBlauwe/IAR-CollectBall-QD.git
cd [...]/sferes2/exp/modular_QD/scenarii && mv IAR-CollectBall-QD/ collectball/
cd [...]/sferes2/exp/modular_QD/ && rm wscript && mv scenarii/collectball/modular_qd_wscript ./wscript
```

### Compilation : CollectaBall QD
See each programs documentation for proper installation and compilation.

```BASH
cd [...]/sferes2/ && ./waf configure --exp=modular_QD --cpp14=yes && ./waf build --exp=modular_QD 
```

### Launching an experiment and viewing the results

To run an experiment, launch one of the executables in : [...]/sferes2/build/exp/modular\_QD/collect\_\*. It will create a directory with the generated results and several stats.

*gen_XX* files contain the best individual(s) of the generation XX. To look at its behavior, launch the following command:

```BASH
./[path-to]/my_executable -o [output_file_name] --load=./[path-to]/gen_XX
```
where `my_executable` is the the program that has generated `gen_XX` and XX the generation number to look at.

## Deploy on GoogleCloud

Links :

* [Quick Start](https://cloud.google.com/cloud-build/docs/quickstart-docker)
* [Deploying](https://cloud.google.com/compute/docs/containers/deploying-containers<Paste>)

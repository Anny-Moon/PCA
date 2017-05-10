# PCA

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.573754.svg)](https://doi.org/10.5281/zenodo.573754)

Welcome to Polymer Chain Analyzer, the toolkit for geometric study of polymer chains.
The project includes:
* PCA library
* Applications
* Tools for visualization

The detail description of the project will come soon in User Manual.

# License
PCA project is distributed under Apache-2.0 license (see LICENSE and NOTICE(comes soon)).

## Cite
To cite the code use it's DOI

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.573754.svg)](https://doi.org/10.5281/zenodo.573754)

Anna Sinelnikova. (2017). Anny-Moon/PCA: First release [Data set]. Zenodo. http://doi.org/10.5281/zenodo.573754

And make a reference to the paper: (comes soon).

# PCA Library
This is the independent core of the project. To install the library run:
```bash
PCA/PCA_lib$ make
```
from the `PCA_lib` folder.

To make the library accessible from any folder on your computer you should run an initialisation session from the root folder `PCA`:
```bash
PCA$ source init_session.sh
```
This you have to do every time when start new terminal session!

There is automatically generated library documentation in `PCA_lib/documentation`.

# Applications
You can find 3 different independent programs in `applications` folder. You can write your own application or change already existent ones. All applications use PCA library. If you did correctly the previous step, then you can copy and put applications in any folder on your computer.
To compile the project do
```bash
myApplication$ make
```
from the folder with your application.

Run the program without arguments and it will tell you about itself and what values it expects:
```bash
myApplication$ ./pca
```
By default there are 2 important points:
* All output files go to folder `results/` which you should have in the folder with application
* All input files should be stored in `PCA/data/` folder. 

These terms can be changed in `main.cpp`.

# Tools for Visualization
There are two kind of tools:
* Matlab functions for visualization chains
* GNUplot script for plotting dependence of observables

Put the tool you want to use in the root of application. Matlab functions works with all applications in `applications`.

## Matlab
If you have Matlab you can call from the workspace:
``` matlab
>> showConfiguration ('myPolymer')
```
for plot the original chain, or:
``` matlab
>> showConfiguration ('myPolymer', 10)
```
for the chain after 10 steps of rescaling procedure.

```matlab
>> makeScalingMovie('myPolymer',5)
```
will make an avi file with scaling procedure, where each frame will be the 5th step of scaling procedure. Skip the second argument for drawing each step of procedure.

## GNUplot
If you have GNUplot you can call
```
myApplication$ gnuplot -e "polymerName='myPolymer'" -e "k=10" plotObservable.gnu
```
for plotting dependence of Observable on scaling step for default value of k. It works for `totalAngle` and  `various_k` projects.

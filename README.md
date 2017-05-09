# PCA
Welcome to Polymer Chain Analyzer, the toolkit for geometric investigation of polymer chains.
The project includes:
* PCA library
* Applications
* Tools for visualization

The detail description of the project will come soon in User Manual.

# License
PCA project is distributed under Apache-2.0 license (see LICENSE and NOTES).

## Cite
DOI:

Reference to the paper:

# PCA Library
This is the independent core of the project. To install the library run:
```bash
$ make
```
from the `PCA_lid` folder.

To make the library accessible from any folder on your computer you should run an initialisation session from root program folder `PCA`:
```bash
$ source init_session.sh
```
This you have to do every time when start new terminal session.

There is automatically generated library documentation in `PCA_lib/documentation`.

# Applications
There are 3 different independent programs in `applications/` folder. You can easily write your own application or change already existent ones. All applications use PCA library. If you did correctly the previous step, then you can copy and put applications in any folder on your computer. By default there are 2 important points:
* All output files go to folder `results/` which you should have in the folder with application
* All input files should be stored in `PCA/data/` folder. 

These terms can be changed in `main.cpp`.

# Tools for Visualization
There are two kind of tools:
* Matlab functions for visualization chains
* GNUplot scripts for plotting dependencies of observables

So you need to instal Matlab or/and GNUplot to be able to use these tools.
Put the tool you want to use in the root of application. Matlab functions works with all applications in `applications/`.
Call:
``` matlab
>> showConfiguration ('myPolymer')
```
for plot the original chain, or:
``` matlab
>> showConfiguration ('myPolymer', 10)
```
for the chain after 10 steps of rescaling steps.

```matlab
>> makeScalingMovie('myPolymer',5)
```
will make an avi file with scaling procedure, where each frame will be the 5th step of scaling procedure. Skip the second argument for drawing each step of procedure.

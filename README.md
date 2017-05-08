# PCA
Welcome to Polymer Chain Analyzer, the toolkit for geometric investigation of polymer chains.
The project includes:
* PCA library
* Applications
* Tools for visualization

## PCA Library
This is the independent core of the project. To install the library run:
```bash
$ make
```
from the `PCA_lid` folder.

To make the library acsessable from any folder on your computer you should run an initialization session from root program folder `PCA`:
```bash
$ source init_session.sh
```
This you have to do every time when start new terminal session.

There is automaticaly generated library documentation in `PCA_lib/documentation`.

## Applications
There are 3 diferent independent programs in `applications/` folder. You can easily write your own apllication or change already existant ones. All applications use PCA library. If you did correctly the previous step, then you can copy and put applications in any folder on your computer. By default there are 2 important poins:
* All output files go to folder `results/` which you should have in the folder with application
* All input files should be stored in `PCA/data/` folder. 
These terms can be changed in `main.cpp`.

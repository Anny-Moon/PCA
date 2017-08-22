"""
Run me like this:
python ./plotter.py <path/fileIn.ext> <configurations>
python ./movieMaker.py data/5dn7_rescaled.pca 30 44 58

If you pass only the first argument then I will
plot the  0-th configuration.
"""

#============ parameters ===============
# Plot
dotSize = 10; # ~40
dotColor = None; #if None then will be random
lineColor = None; #if None then will be random

# Axes
elevation = None;
azimut = None;
axisOnOff ='off';
#=======================================


import matplotlib.pyplot as plt
import Polymer
import EqualAxes
import sys


if(len(sys.argv)<2):
    print(__doc__);
    exit();
fileName = sys.argv[1];
polymer = Polymer.Polymer(fileName);

fig = plt.figure()
ax = fig.gca(projection='3d');
ax.set_aspect('equal');
eqAx = EqualAxes.EqualAxes();

if(len(sys.argv)<3):
    confNum = 0;
    polymer.plot(confNum, ax);
    eqAx.push(polymer.getX(confNum),polymer.getY(confNum),polymer.getZ(confNum));
else:
    for i in range(2,len(sys.argv)):
	confNum = int(sys.argv[i]);
	print('Chain %s has %i atoms.' % (sys.argv[i], polymer.getN(confNum)));
	eqAx.push(polymer.getX(confNum),polymer.getY(confNum),polymer.getZ(confNum));
    if(dotSize==None):
	axMaxRange=eqAx.findMaxRange();
    else:
	axMaxRange=800/dotSize;
	
    for i in range(2,len(sys.argv)):
	confNum = int(sys.argv[i]);
	polymer.plot(confNum,ax, axMaxRange, dotColor, lineColor);
#	polymer.plotOld(confNum, ax);
	
    
eqAx.set(ax);
plt.axis(axisOnOff);
plt.show();
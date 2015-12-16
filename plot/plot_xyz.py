#############################################################################
### Python script for plotting 1D data (x,y) for particle trajectory codes.
###   Data is read from given file.
###   Plot is created using matplotlib.
###   Produces the following plots:
###   1. (x(t) - t), (v(t) - t), 
###   2. (v(t) - x(t))
###   3. 3D Plot of trajectory
###
###   Author: Nikos Tryfonidis
###   The MIT License (MIT)
###   Copyright (c) 2015 Nikos Tryfonidis
###   See LICENSE.txt
#############################################################################


import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

from plot import plot1D

# Read file
t, x, y, z, v_x, v_y, v_z = np.loadtxt("../output/output.txt", unpack=True)

##############################################################
# t, x, v plot (1D) : select desired coordinates
##############################################################
# Plot t, x (plot1d function in plot1D.py)
plot1D(t, x, v_x)

##############################################################
# 3D Trajectory Plot: comes after user closes previous 2 windows
##############################################################
# Plot 3D trajectory
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(x, y, z)
plt.show() 

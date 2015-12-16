#############################################################################
### Python script for plotting 1D data (x,y) for particle trajectory codes.
###   Data is read from given file.
###   Plot is created using matplotlib.
###   Produces the following plots:
###   1. (x(t) - t), (v(t) - t), 
###   2. (v(t) - x(t))
###   
###   Author: Nikos Tryfonidis
###   The MIT License (MIT)
###   Copyright (c) 2015 Nikos Tryfonidis
###   See LICENSE.txt
#############################################################################

import numpy as np
import matplotlib.pyplot as plt

#############################################################################
### Function to be called from external script!
### Plots given t, x, v: x-t, v-t, v-x
#############################################################################
def plot1D (t, x, v):

    # Plot (x(t) - t) and (v(t) - t)
    plt.figure(1)

    # Make (x(t) - t) plot
    plt.subplot(211)
    plt.plot(t, x, linestyle='solid', marker='o', color='black', markersize=3)
    plt.axis([t[0], t[-1], (min(x)+min(x)/4), max(x)+max(x)/4])
    plt.xlabel('t')
    plt.ylabel('x(t)')

    # Make (v_x(t) - t) plot
    plt.subplot(212)
    plt.plot(t, v, color='red')
    plt.axis([t[0], t[-1], (min(v)+min(v)/4), max(v)+max(v)/4])
    plt.xlabel('t')
    plt.ylabel('v(t)')

    # Make subplots look good
    plt.tight_layout()

    # Make v(t) - x(t) plot
    plt.figure(2)
    plt.plot(x, v, color='blue')
    plt.axis([(min(x)+min(x)/4), max(x)+max(x)/4, (min(v)+min(v)/4), max(v)+max(v)/4])
    plt.grid(True)
    plt.xlabel('x(t)')
    plt.ylabel('v(t)')
    plt.title('Phase Space')
        
    # Show Plot
    plt.show()

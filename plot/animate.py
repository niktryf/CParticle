#############################################################################
### Python script for animating particle trajectory output from CParticle.
###   Data is read from given file.
###   Animation is created using matplotlib (animation package).
###   Produces a 3D animation of the particle trajectory.
###
###   Author: Nikos Tryfonidis
###   The MIT License (MIT)
###   Copyright (c) 2015 Nikos Tryfonidis
###   See LICENSE.txt
#############################################################################

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import animation


# Read file
t, x, y, z, v_x, v_y, v_z = np.loadtxt("../output/output.txt", unpack=True)

# Start figure and axes
fig = plt.figure()
l = 0
b = 0
w = 1
h = 1
rect = l, b, w, h
ax = fig.add_axes(rect, projection='3d', axis_bgcolor='white')
### Turn the axis on and off to see the orientation!
ax.axis('off')

#size of output, for number of frames
size = len(t)

# set up lines and points
line, = ax.plot([], [], [], '-', lw=1, color='black', linestyle='solid')      
pt, = ax.plot([], [], [], 'o', markerfacecolor='red', 
        markeredgecolor='black', markeredgewidth=1.0, markersize=6.0)

# prepare the axes limits
ax.set_xlim((min(x), max(x)))
ax.set_ylim((min(y), max(y)))
ax.set_zlim((min(z), max(z)))

# set point-of-view (altitude degrees, azimuth degrees)
ax.view_init(15, 0)

# initialization function
def init():
    line.set_data([], [])
    line.set_3d_properties([])

    pt.set_data([], [])
    pt.set_3d_properties([])
    return pt,

# animation function
def animate(i):
    # Plot whole trajectory up to current point as a line
    xx, yy, zz = x[:i], y[:i], z[:i]
    line.set_data(xx, yy)
    line.set_3d_properties(zz)
    # Plot last point of trajectory as a point
    pt.set_data(xx[-1:], yy[-1:])
    pt.set_3d_properties(zz[-1:])

    # Set altitude degrees, azimuth degrees
    ax.view_init(0, 0)
    fig.canvas.draw()
    return pt,

# Start Animation:
anim = animation.FuncAnimation(fig, animate, init_func=init, frames=size, interval=1, blit=True, repeat=False)
# Show it:
plt.show()

#save animation:
# Set up formatting for the movie files
#plt.rcParams['animation.ffmpeg_path'] = '/usr/bin/ffmpeg'
#FFwriter = animation.FFMpegWriter(fps=60, bitrate=1000)
#anim.save('basic_animation.mp4', writer = FFwriter, extra_args=['-vcodec', 'libx264'])


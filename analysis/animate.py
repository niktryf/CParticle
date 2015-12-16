##############################################################
# 3D Trajectory Animation
##############################################################

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import animation

# Read file
t, x, y, z, v_x, v_y, v_z = np.loadtxt("../output/output.txt", unpack=True)

# Animate 3D trajectory
fig = plt.figure()
ax = fig.add_axes([0, 0, 1, 1], projection='3d', axis_bgcolor='white')
ax.axis('off')

#size of output, for number of frames
size = len(t)

# set up lines and points
line, = ax.plot([], [], [], '-', lw=3, color='black', linestyle='solid')      
pt, = ax.plot([], [], [], 'o', markerfacecolor='red', 
        markeredgecolor='black', markeredgewidth=1.0, markersize=11.0)

# prepare the axes limits
ax.set_xlim((min(x)-1, max(x)+1))
ax.set_ylim((min(y)-1, max(y)+1))
ax.set_zlim((min(z)-1, max(z)+1))

# set point-of-view: specified by (altitude degrees, azimuth degrees)
ax.view_init(15, 0)

# initialization function: plot the background of each frame
def init():
    line.set_data([], [])
    line.set_3d_properties([])

    pt.set_data([], [])
    pt.set_3d_properties([])
    return pt,

# animation function.  This will be called sequentially with the frame number
def animate(i):
    
    xx, yy, zz = x[:i], y[:i], z[:i]
    line.set_data(xx, yy)
    line.set_3d_properties(zz)

    pt.set_data(xx[-1:], yy[-1:])
    pt.set_3d_properties(zz[-1:])

    ax.view_init(15, 45)
    fig.canvas.draw()
    return pt,

# instantiate the animator.
anim = animation.FuncAnimation(fig, animate, init_func=init, frames=size, interval=1, blit=True, repeat=False)

plt.show()


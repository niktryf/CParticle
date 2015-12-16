/******************************************************************
 *** CParticle - Charged Particle Motion in ElectroMagnetic Fields.
 *** Particle trajectory wrapper - returns output array
 *** 
 *** Author: Nikos Tryfonidis, November 2015
 *** The MIT License (MIT)
 *** Copyright (c) 2015 Nikos Tryfonidis
 *** See LICENSE.txt
 *******************************************************************/

#include <math.h>

#include "../headers/struct.h"
#include "../headers/definitions.h"
#include "../headers/solver.h"
#include "../headers/io.h"


/* Calculates the kinetic energy of the particle, 
   which is conserved for motion in a magnetic field.
 */
double kineticEnergy(struct particle p)
{
    return 0.5*p.m*sqrt(p.v.x*p.v.x + p.v.y*p.v.y + p.v.z*p.v.z);
}

/* Calculates the motion of the particle and writes to 
   output array in memory.
 */
double **motion(double **output, struct particle p, struct time t)
{
    int i, j;
    double tt; //"actual" time, for time-dependent fields.

    /*** Solve DEs ***/
    for(i=0;i<t.nOutput;i++) {
        /* Write to output array */
        output = writeToArray(output, i, p, kineticEnergy(p));
        
        /* Call Runge - Kutta for nSteps_Output steps */
        for(j=0;j<t.output_interval;j++) {
            tt = (i*(t.output_interval) + j)*t.dt;
            p = RK4_motion3D (p, t.dt, tt);
        }
    }

    return output;
}

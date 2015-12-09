/******************************************************************
 *** CParticle - Charged Particle Motion in ElectroMagnetic Fields.
 *** Particle trajectory wrapper - returns output array
 *** 
 ******************************************************************/

#include "../headers/struct.h"
#include "../headers/definitions.h"

double **motion(double **array2D, struct particle p, struct time t)
{
    int i, j, k;





    /*** Solve DEs ***/
    for(i=0;i<t.nOutput;i++) {
        /* Write to output array */
        // Positions:
        array2D[i][0] = p.r.x;
        array2D[i][1] = p.r.y;
        array2D[i][2] = p.r.z;
        // Velocities:
        array2D[i][3] = p.v.x;
        array2D[i][4] = p.v.y;
        array2D[i][5] = p.v.z;
        
        /* Call Runge - Kutta for nSteps_Output steps */
        for(j=1;j<=t.output_interval;j++) {
            //t = (i*(t.output_interval) + j)*dt;
            //p = RK4_2nd (p, dt, t);
        }
    }











    return array2D;
}

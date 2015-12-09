/******************************************************************
 *** CParticle - Charged Particle Motion in ElectroMagnetic Fields.
 *** Main source file.
 *** 
 ******************************************************************/

#include <stdio.h>

#include "../headers/struct.h"
#include "../headers/definitions.h"
#include "../headers/io.h"
#include "../headers/memory.h"
#include "../headers/motion.h"

int main(int argc, char *argv[]) {

    struct particle p;
    struct time t;
    double **output;
    
    /*** Read and show input 
         (initial conditions from file
          and charge type - time parameters from command line)
    ***/
    p = readInitialConditions("input.txt");
    cmd_line(argc, argv, &p, &t);
    // Print input data to screen: 
    printInput (p, t);

    /* Allocate memory for output 
       2D array with position and velocity in columns
       (2*N = 6 columns total).
       Consecutive output in rows.
    */
    output = array2D_contiguous (t.nOutput, 2*N);

    /* Begin particle motion */
    output = motion(output, p, t);

    /* Test print output */
    int i, j;
    for (i=0;i<t.nOutput;i++) {
        printf ("%.2f %.2f %.2f\t%.2f %.2f %.2f\n", output[i][0], output[i][1], output[i][2], output[i][3], output[i][4], output[i][5]);

    }



    /* Free output array */
    free_array2D_contiguous(output);

    return 0;
}

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
#include "../headers/fields.h"
#include "../headers/solver.h"

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
    printInput (p, t);

    /* Allocate memory for output 
       2D array with position, velocity and energy in columns
       (2*N + 1 = 7 columns total).
       Consecutive output (frames) in rows.
    */
    output = array2D_contiguous (t.nOutput, 2*N + 1);

    /* Begin particle motion */
    output = motion(output, p, t);

    /* Write output array */
    writeFileOutput (output, t, "output/out.txt");

    /* Free output array */
    free_array2D_contiguous(output);

    return 0;
}

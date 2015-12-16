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

    // Particle data structure:
    struct particle p;
    // Time parameters data structure:
    struct time t;
    // Output storage array:
    double **output;

    /* Read and show input */
    // Initial position and velocity from input file:
    p = readInitialConditions("input.txt");
    // Charge type and time parameters from command line:
    cmd_line(argc, argv, &p, &t);
    // Print input to screen for inspection:
    printInput (p, t);

    /* Allocate memory for output */
    output = array2D_contiguous (t.nOutput, 2*N+1);

    /* Begin particle motion */
    printf("\nRunning...\n");
    output = motion(output, p, t);
    
    /* Write output array */
    printf("\nWriting Output...\n");
    writeFileOutput (output, t, \
                     "output/output.txt", \
                     "output/energy.txt");

    printf("\n...Done!\n");

    /* Free output array */
    free_array2D_contiguous(output);

    return 0;
}

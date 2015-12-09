/******************************************************************
 *** CParticle - Charged Particle Motion in ElectroMagnetic Fields.
 *** File Input/Output Functions.
 *** 
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "../headers/struct.h"
#include "../headers/definitions.h"

#define BUF_LENGTH 100

/* Function that reads particle initial conditions from file 
   and applies them to the particle.
 */
struct particle readInitialConditions(char *filename) 
{
    struct particle p;

    char buf[BUF_LENGTH];

    FILE * inputFile;
    inputFile = fopen(filename, "r");

    while( fgets(buf, BUF_LENGTH, inputFile) != NULL ) {
        /* If scanning Initial Position (r) */
        if (buf[0] == 'r'){
          sscanf(buf, "%c %lf %lf %lf", &buf[0], &p.r.x, &p.r.y, &p.r.z);
        }
        /* If scanning Particle Parameters */
        else if (buf[0] == 'v'){
          sscanf(buf, "%c %lf %lf %lf", &buf[0], &p.v.x, &p.v.y, &p.v.z);
        }
    }
  
  fclose(inputFile);

  return p;

}

/* 
  Function that reads command line arguments and applies 
  particle charge, mass and time parameters 
  (total time, timestep and output interval).
*/
void cmd_line(int argc, char *argv[], struct particle *p, struct time *t)
{
    char charge;

    /* Check number of arguments */
    if(argc != 5) {
      // If not enough given, exit:  
      printf("\nProgram needs 4 command line arguments to run!\n");
      printf( "Usage: %s (particle type - i or e) (time) (timestep) (step interval for output)\n\n", argv[0] );     
      printf("\nExiting...\n\n");   
      exit(-1);
    } 
    else {
        // Get charge (ion or electron)
        sscanf(argv[1],"%c", &charge);
        if( (charge != 'e') && (charge != 'i') ) {
            printf("Warning: Charge should be i (ion) or e (electron)\n");
            printf("Running by default for ion...\n");
            charge = 'i';
        }  
        // Get time parameters 
        sscanf(argv[2],"%lf", &(t->totalTime) );
        sscanf(argv[3],"%lf", &(t->dt) );
        sscanf(argv[4],"%d", &(t->output_interval) );
    }

    /* Calculate total timesteps and number of output */
    t->totalTimeSteps = (t->totalTime)/(t->dt);
    t->nOutput = (t->totalTimeSteps)/(t->output_interval) + 1;
    // + 1: to account for first output (initial conditions)

    /* Apply Particle Charge and Mass */
    if (charge == 'i') {
        p->q = ION_CHARGE;
        p->m = ION_MASS;
    }
    else {
        p->q = ELECTRON_CHARGE;
        p->m = ELECTRON_MASS;
    }
}

/* Prints problem parameters to the screen, at the 
   beginning of the program.
 */
void printInput (struct particle p, struct time t) 
{
    printf("\n###############    Particle Motion in EM Fields    ###############\n");
    printf("# Parameters: \n");
    printf("# \t\tCharge: %f\tMass: %f\n#\n", p.q, p.m);
    printf("# \t\tTotal time: %.2f\ttimestep: %f\n", t.totalTime, t.dt);
    printf("# \t\t%d total timesteps, output every %d steps (%d total output)\n#\n", t.totalTimeSteps, t.output_interval, t.nOutput);
    printf("# Initial particle conditions: \n");
    printf("# \t\tinitial r: (%.3f, %.3f, %.3f)\n", p.r.x, p.r.y, p.r.z);
    printf("# \t\tinitial v: (%.3f, %.3f, %.3f)\n", p.v.x, p.v.y, p.v.z);
    printf("##################################################################\n");
}

/******************************************************************
 *** CParticle - Charged Particle Motion in ElectroMagnetic Fields
 *** Structure definitions.
 *** 
 ******************************************************************/

struct vector3D {
    double x;
    double y;
    double z;
};

struct particle {
    struct vector3D r;
    struct vector3D v;
    double q;
    double m;
};

struct time {
  double totalTime;
  double dt;
  int output_interval;
  int totalTimeSteps;
  int nOutput;
};

/******************************************************************
 *** CParticle - Charged Particle Motion in ElectroMagnetic Fields.
 *** Numerical solution for the equations of motion.
 *** 
 ******************************************************************/

#include "../headers/struct.h"
#include "../headers/fields.h"

/* Returns Right-hand-side of differential equation of motion
   (Force/mass)
 */
struct vector3D RHS(struct particle p, double t) 
{
  struct vector3D F = FLorentz(p, t);

  F.x /= p.m;
  F.y /= p.m;
  F.z /= p.m;

  return F;
}


struct particle RK4_motion3D(struct particle p, double dt, double t)
{
    struct vector3D F, G, k[4], l[4];
    struct particle tmp;

    // Stage 1
    tmp = p;
    F = RHS(tmp, t);

    k[0].x = dt*F.x;
    k[0].y = dt*F.y;
    k[0].z = dt*F.z;

    l[0].x = dt*tmp.v.x;
    l[0].y = dt*tmp.v.y;
    l[0].z = dt*tmp.v.z;

    // Stage 2
    tmp.r.x = p.r.x + 0.5*l[0].x; 
    tmp.r.y = p.r.y + 0.5*l[0].y; 
    tmp.r.z = p.r.z + 0.5*l[0].z;
    tmp.v.x = p.v.x + 0.5*k[0].x; 
    tmp.v.y = p.v.y + 0.5*k[0].y; 
    tmp.v.z = p.v.z + 0.5*k[0].z;
    F = RHS(tmp, t + 0.5*dt);

    k[1].x = dt*F.x;
    k[1].y = dt*F.y;
    k[1].z = dt*F.z;

    l[1].x = dt*(tmp.v.x);
    l[1].y = dt*(tmp.v.y);
    l[1].z = dt*(tmp.v.z);

    // Stage 3
    tmp.r.x = p.r.x + 0.5*l[1].x; 
    tmp.r.y = p.r.y + 0.5*l[1].y; 
    tmp.r.z = p.r.z + 0.5*l[1].z;
    tmp.v.x = p.v.x + 0.5*k[1].x; 
    tmp.v.y = p.v.y + 0.5*k[1].y; 
    tmp.v.z = p.v.z + 0.5*k[1].z;
    F = RHS(tmp, t + 0.5*dt);

    k[2].x = dt*F.x;
    k[2].y = dt*F.y;
    k[2].z = dt*F.z;

    l[2].x = dt*(tmp.v.x);
    l[2].y = dt*(tmp.v.y);
    l[2].z = dt*(tmp.v.z);

    // Stage 4
    tmp.r.x = p.r.x + l[2].x; 
    tmp.r.y = p.r.y + l[2].y; 
    tmp.r.z = p.r.z + l[2].z;
    tmp.v.x = p.v.x + k[2].x; 
    tmp.v.y = p.v.y + k[2].y; 
    tmp.v.z = p.v.z + k[2].z;
    F = RHS(tmp, t + dt);

    k[3].x = dt*F.x;
    k[3].y = dt*F.y;
    k[3].z = dt*F.z;

    l[3].x = dt*(tmp.v.x);
    l[3].y = dt*(tmp.v.y);
    l[3].z = dt*(tmp.v.z);

    /* Calculate new values */
    p.v.x += (1.0/6.0)*(k[0].x + 2*(k[1].x + k[2].x) + k[3].x);
    p.v.y += (1.0/6.0)*(k[0].y + 2*(k[1].y + k[2].y) + k[3].y);
    p.v.z += (1.0/6.0)*(k[0].z + 2*(k[1].z + k[2].z) + k[3].z);

    p.r.x += (1.0/6.0)*(l[0].x + 2*(l[1].x + l[2].x) + l[3].x);
    p.r.y += (1.0/6.0)*(l[0].y + 2*(l[1].y + l[2].y) + l[3].y);
    p.r.z += (1.0/6.0)*(l[0].z + 2*(l[1].z + l[2].z) + l[3].z);
    
    return p;
}


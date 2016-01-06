/******************************************************************
 *** CParticle - Charged Particle Motion in ElectroMagnetic Fields.
 *** Electric and Magnetic Fields, Lorentz Force and cross product.
 *** 
 *** Author: Nikos Tryfonidis, November 2015
 *** The MIT License (MIT)
 *** Copyright (c) 2015 Nikos Tryfonidis
 *** See LICENSE.txt
 *******************************************************************/

#include <math.h>
#include "../headers/struct.h"

/*************************************************
 Electric Field
**************************************************/
/* 
  Gives vector E = E_x(x,y,z,t) + E_y(x,y,z,t) + E_z(x,y,z,t) 
  User must enter the values inside the function
*/

struct vector3D EField (struct vector3D r, double t)
{
  struct vector3D E;

  E.x = 0;
  E.y = 0;
  E.z = 0;

  return E;
}


/*************************************************
 Magnetic Field
**************************************************/
/* 
  Gives vector B = B_x(x,y,z,t) + B_y(x,y,z,t) + B_z(x,y,z,t) 
  User must enter the values inside the function
*/

struct vector3D BField (struct vector3D r, double t)
{
  struct vector3D B;

  B.x = -(1.0/pow(sqrt(r.x*r.x+r.y*r.y+r.z*r.z),5))*3*r.x*r.z;
  B.y = -(1.0/pow(sqrt(r.x*r.x+r.y*r.y+r.z*r.z),5))*3*r.y*r.z;
  B.z = -(1.0/pow(sqrt(r.x*r.x+r.y*r.y+r.z*r.z),5))*(2*r.z*r.z-r.x*r.x-r.y*r.y);

  return B;
}

/*************************************************
 Cross Product
**************************************************/
struct vector3D cross (struct vector3D A, struct vector3D B)
{
  struct vector3D C;
  
  C.x = (A.y)*(B.z) - (A.z)*(B.y);
  C.y = (A.z)*(B.x) - (A.x)*(B.z);
  C.z = (A.x)*(B.y) - (A.y)*(B.x);

  return C;
}

/* 
  Calculates Lorentz force vector from E, B fields at a point, 
  given the particle's position and velocity.
*/

struct vector3D FLorentz (struct particle p, double t)
{
    struct vector3D F, E, B, vxB;

    /* 
      Calculate E, B fields at given point, 
      using functions EField, BField 
    */
    E = EField(p.r, t);
    B = BField(p.r, t);

    /* Calculate cross product of v, B */
    vxB = cross(p.v, B);

    /* Calculate Lorentz Force vector components */
    F.x = p.q*(E.x + vxB.x);
    F.y = p.q*(E.y + vxB.y);
    F.z = p.q*(E.z + vxB.z);

    return F;
}



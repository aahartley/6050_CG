#ifndef PARTICLE_H 
#define PARTICLE_H

#include "Vec2.h"

class Particle
{
public:
    Particle(){}
    Particle(Vec2 a, Vec2 v, Vec2 p, float s, float d, float pr):
             acc(a), vel(v), pos(p), size(s), rho(d), pressure(pr){mass = 2.5f;}

    ~Particle(){}

    void SetAcc(const Vec2 a){acc = a;}
    void SetVel(const Vec2 v){vel = v;}
    void SetPos(const Vec2 p){pos = p;}

    Vec2& GetAcc(){return acc;}
    Vec2& GetVel(){return vel;}
    Vec2& GetPos(){return pos;}
    float& GetSize(){return size;}
    float& GetDens(){return rho;}
    float& GetPress(){return pressure;}
    float& GetMass(){return mass;}



private:
    Vec2 acc, vel, pos;
    float size, rho, pressure, mass;
};





#endif
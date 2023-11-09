#ifndef SPHSOLVER_H
#define SPHSOLVER_H

#include <vector>

#include "Particle.h"

class SPHSolver
{
public:
    SPHSolver(int num, float size);
    ~SPHSolver();

    void GenerateParticles();
    void Integrate();
    void BoundaryCollisions();
    //smoothing kernel
    float W(Vec2 distance, float h);
    Vec2 W_Gradient();
    //calc rho field
    void CalcDensityField();
    Vec2 CalcGradient(float A);

    void PerformSimulation();

    int& GetNum(){return num;}
    std::vector<Particle> GetParticles(){return particles;}


private:
    int num;
    float dt, size;
    std::vector<Particle> particles;

};



#endif
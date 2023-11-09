#include "SPHSolver.h"

SPHSolver::SPHSolver(int num, float size)
{
    this->num = num;
    dt = 0.016;
    size = size;
    particles = std::vector<Particle>(num);
    GenerateParticles();
    CalcDensityField();
}

SPHSolver::~SPHSolver()
{

}

void SPHSolver::GenerateParticles()
{
    for(int i = 0; i < num; i++)
    {
        Particle p(Vec2(0,0), Vec2(0,0), Vec2(250,250), size, 0, 0);
        particles[i] = p;
    }
}

//smoothing kernel
float SPHSolver::W( Vec2 distance, float h)
{
    //cubic spline from Smoothed Particle HydrodynamicsTechniques for the Physics Based Simulation of Fluids and Solids
    //Dan Koschier1, Jan Bender2, Barbara Solenthaler3, and Matthias Teschner4
    //normalization factors: sigma dimensions=2  40/7 *pi *h^2            d=3 8/pi*h^3
    //smmothing length == kernel support radius == h, h == 2 * particle size
    float q = (1.0f/h) * distance.magnitude();
    float sigma_2 = (40.0f/7.0f) * 3.14f * std::pow(h, 2); 

    if(q >= 0 && q <= 1.0f/2.0f) 
        return sigma_2 * 6 * (std::pow(q, 3) - std::pow(q, 2)) + 1;
    else if (q > 1.0f/2.0f && q <= 1) 
        return sigma_2 * 2 * std::pow((1 - q), 3);
    else 
        return 0;

}

Vec2 SPHSolver::W_Gradient()
{
    Vec2 grad;



    return grad;
}

void SPHSolver::CalcDensityField()
{
    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < num; j++)
        {
            if(&particles[i] != &particles[j])
            {
                Vec2 dist = particles[i].GetPos() - particles[j].GetPos();
                particles[i].GetDens() += particles[j].GetMass() * W(dist, size * 2);
            }
        }
    }
}

Vec2 SPHSolver::CalcGradient(float& A)
{
    //forward difference formula
    Vec2 grad;

    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < num; j++)
        {
            A += particles[j].GetMass() * (particles[j].GetMass() / particles[j].GetDensity()) * W_Gradient();
        }
    }

    return grad;
}

void SPHSolver::Integrate()
{
      for(int i = 0; i < num; i++)
    {
        particles[i].SetAcc(Vec2(0,-9.8f));
        particles[i].GetVel() += particles[i].GetAcc() * dt;
        particles[i].GetPos() += particles[i].GetVel() * dt;
    }

}

void SPHSolver::BoundaryCollisions()
{
    
}

void SPHSolver::PerformSimulation()
{
  
    Integrate();

}
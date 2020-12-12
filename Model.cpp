#include "Model.h"


Model::Model(int width, int height, int sphereNumber, float deltaT)
{
    srand(1234);
    boxSizeX = width;
    boxSizeY = height;
    sphereN = sphereNumber;
    dt = deltaT;
    springN = sphereNumber * (sphereNumber - 1) / 2;
    spheres = new Sphere[sphereN];
    springs = new Spring[springN];

    for(int i = 0; i < sphereN; i++)
    {
        spheres[i].radius = 40;
        spheres[i].position = Vector{(2 * spheres[i].radius + 10) * i + spheres[i].radius + 10,  (2 * spheres[i].radius + 10) * i + spheres[i].radius + rand() % (int)spheres[i].radius };
        spheres[i].velocity = Vector{(float) (rand() % 20),(float) (rand() % 20)};
        spheres[i].mass = 100.0;

    }

    int spr = 0;
    for(int i = 0; i < sphereN; i++)
    {
        for(int j = i + 1; j < sphereN; j++)
        {
            springs[spr].first = &spheres[i];
            springs[spr].second = &spheres[j];
            springs[spr].k = 0.01;
            springs[spr].regularLength = 50;
            spr++;
        }
    }

}

Model::~Model()
{
    delete[] spheres;
    delete[] springs;
}

Model::Model()
{
    spheres = nullptr;
    springs = nullptr;
}


Model& Model::operator=(const Model& other)
{
    if (this != &other)
    {
        this->boxSizeX = other.boxSizeX;
        this->boxSizeY = other.boxSizeY;
        this->dt = other.dt;
        this->sphereN = other.sphereN;
        this->springN = other.springN;
        if (spheres != nullptr)
        {
            delete[] spheres;
        }
        if (springs != nullptr)
        {
            delete[] springs;
        }
        spheres = new Sphere[sphereN];
        springs = new Spring[springN];

        for(int i = 0; i < sphereN; i++)
        {
            spheres[i] = other.spheres[i];
        }
        int spr = 0;
        for(int i = 0; i < sphereN; i++)
        {
            for(int j = i + 1; j < sphereN; j++)
            {
                springs[spr] = other.springs[spr];
                springs[spr].first = &spheres[i];
                springs[spr].second = &spheres[j];
                spr++;
            }
        }
    }
    return *this;
}

void Model::Update()
{
    for (int i = 0; i < sphereN; i++)
    {
        CollideSphereWall(i);
    }

    for (int i = 0; i < sphereN; i++)
    {
        for (int j = i + 1; j < sphereN; j++)
        {
            CollideTwoSpheres(i, j);
        }
    }

    for(int i = 0; i < springN; i++)
    {
        ApplySpringsForces(i);
    }


    for(int i = 0; i < sphereN; i++)
    {
        spheres[i].position.X += spheres[i].velocity.X * dt;
        spheres[i].position.Y += spheres[i].velocity.Y * dt;
    }
}

Vector Model::GetSpherePosition(int sphereID)
{
    return spheres[sphereID].position;
}

float Model::GetSphereRadius(int sphereID)
{
    return spheres[sphereID].radius;
}

Segment Model::GetSpringPosition(int springID)
{
    return { (springs[springID].first->position), (springs[springID].second->position)};
}

int Model::GetSpheresNumber()
{
    return sphereN;
}

int Model::GetSpringsNumber()
{
    return springN;
}


bool Model::CheckCollisionTwoSpheres(int sphereID1, int sphereID2)
 {
    if ((spheres[sphereID1].radius + spheres[sphereID2].radius) > (spheres[sphereID1].position - spheres[sphereID2].position).EuclidNorm())
    {
        return true;
    }
    return false;
 }

 void Model::CollideSphereWall(int sphereID)
 {
     if (spheres[sphereID].position.X > boxSizeX - spheres[sphereID].radius || spheres[sphereID].position.X < spheres[sphereID].radius)
     {
         spheres[sphereID].velocity.X = - spheres[sphereID].velocity.X;
     }

     if (spheres[sphereID].position.Y > boxSizeY - spheres[sphereID].radius || spheres[sphereID].position.Y < spheres[sphereID].radius)
     {
         spheres[sphereID].velocity.Y = - spheres[sphereID].velocity.Y;
     }
 }

 void Model::CollideTwoSpheres(int sphereID1, int sphereID2)
 {
     if (sphereID1 != sphereID2 && CheckCollisionTwoSpheres(sphereID1, sphereID2))
     {
         Vector axis = spheres[sphereID1].position - spheres[sphereID2].position;
         float moduleAxis = axis.EuclidNorm();
         float projectionVelocity1 = spheres[sphereID1].velocity.projectionVector(axis);
         float projectionVelocity2 = spheres[sphereID2].velocity.projectionVector(axis);
         float dv = projectionVelocity1 - projectionVelocity2;

         if(dv < 0)
         {
             spheres[sphereID1].velocity = spheres[sphereID1].velocity + axis * -dv * (1 / moduleAxis);
             spheres[sphereID2].velocity = spheres[sphereID2].velocity + axis * dv * (1 / moduleAxis);
         }
      }

 }


void Model::ApplySpringsForces(int springID)
{
    Vector force1 = (springs[springID].second->position - springs[springID].first->position);
    Vector force2 = (springs[springID].first->position - springs[springID].second->position);

    float norm = force1.EuclidNorm();
    force1 = force1 * (1 / norm);
    force2 = force2 * (1 / norm);
    float d = norm - springs[springID].regularLength;
    force1 = force1 * (springs[springID].k * d / (springs[springID].first->mass ));
    force2 = force2 * (springs[springID].k * d / (springs[springID].second->mass ));

    springs[springID].first->velocity = springs[springID].first->velocity + force1;
    springs[springID].second->velocity = springs[springID].second->velocity + force2;
}

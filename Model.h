#pragma once

#include "Geom.h"
#include <iostream>
#include <cstdlib>

struct Sphere
{
    Vector position;
    Vector velocity;
    float radius;
    float mass;
};


struct Spring
{
    Sphere *first;
    Sphere *second;

    float k;
    float regularLength;

};

class Model
{
    public:
        Model();
        Model(int width, int height, int sphereNumber, float deltaT);
        Model& operator=(const Model& other);
        ~Model();
        void Update();
        Vector GetSpherePosition(int sphereID);
        float GetSphereRadius(int sphereID);
        Segment GetSpringPosition(int springID);
        int GetSpheresNumber();
        int GetSpringsNumber();
    private:
        void ApplySpringsForces(int springID);
        void CollideSphereWall(int sphereID);
        bool CheckCollisionTwoSpheres(int sphereID1, int sphereID2);
        void CollideTwoSpheres(int sphereID1, int sphereID2);

        Sphere *spheres;
        Spring *springs;
        int boxSizeX;
        int boxSizeY;
        float dt;
        int sphereN;
        int springN;

};




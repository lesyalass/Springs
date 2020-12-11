#pragma once

class Model
{
    public:
        Model();
        ~Model() = default;
        void Update();
        Vector GetSpherePosition(int sphereID);
        float GetSphereRadius(int sphereID);
        Segment GetSpringPosition(int springID);
        int GetSpheresNumber();
        int GetSpringsNumber();
    private:
        Sphere *spheres;
        Spring *springs;
};

struct Vector
{
    float X;
    float Y;
};

struct Segment
{
    Vector first;
    Vector second;
};

struct Sphere
{
    float Mass;
    Vector position;
    Vector velocity;
    int Radius;
    int redRate;
    int greenRate;
    int blueRate;
    int Gradient;
};

struct Spring
{
    Vector position1;
    Vector position2;
    float k;

};
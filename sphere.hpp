#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "geometry.hpp"
#include "objects.hpp"

class Sphere:public Objects{
public:
    Sphere(Vec3 center, Color color, double lambert, double radius, std::string type);
    
    double getRadius();
    
private:
    double radius;
};

#endif

#ifndef PLANE_HPP
#define PLANE_HPP

#include "geometry.hpp"
#include "objects.hpp"

class Plane:public Objects{
public:
    Plane(Vec3 center, Color color, double lambert,Vec3 normal, std::string type);
    
    Vec3 getNormal();
    
private:
    Vec3 normal;
};

#endif

#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "geometry.hpp"
#include <iostream>

class Objects{
public:
    Objects(Vec3 center, Color color, double lambert, std::string type);
    
    Vec3 getCenter();
    
    Color getColor();
    
    double getLambert();
    
    std::string getType();
    
protected:
    Vec3 center;
    Color color;
    double lambert;
    std::string type;
    
};

#endif

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "geometry.hpp"

class Light{
public:
    Light(Vec3 location, double intensity);
    
    Vec3 getLocation();
    
    double getIntensity();
    
private:
    Vec3 location;
    double intensity;
};

#endif

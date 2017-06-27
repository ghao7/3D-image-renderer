#include "light.hpp"

Light::Light(Vec3 location, double intensity){
    this->location = location;
    this->intensity = intensity;
}

Vec3 Light::getLocation(){
    return location;
}

double Light:: getIntensity(){
    return intensity;
}

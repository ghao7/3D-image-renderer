#include "sphere.hpp"

Sphere::Sphere(Vec3 center, Color color, double lambert,double radius, std::string type):Objects(center,color,lambert, type){
    this->radius = radius;
}

double Sphere::getRadius(){
    return radius;
}

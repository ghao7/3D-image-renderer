#include "plane.hpp"

Plane::Plane(Vec3 center, Color color, double lambert,Vec3 normal, std::string type):Objects(center,color,lambert, type){
    this->normal = normal;
}

Vec3 Plane::getNormal(){
    return normal;
}

#include "objects.hpp"

Objects::Objects(Vec3 center, Color color, double lambert, std::string type){
    this->center = center;
    this->color = color;
    this->lambert = lambert;
    this->type = type;
}

Vec3 Objects::getCenter(){
    return center;
}

Color Objects::getColor(){
    return color;
}

double Objects::getLambert(){
    return lambert;
}

std::string Objects::getType(){
    return type;
}

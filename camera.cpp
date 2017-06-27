#include "camera.hpp"

Camera::Camera(){
    
}

Camera::Camera(Vec3 center, Vec3 normal, double focus, std::vector<int> size, std::vector<double> resolution){
    this->center = center;
    this->normal = normal;
    this->focus = focus;
    this->size = size;
    this->resolution = resolution;
}

Vec3 Camera::getCenter(){
    return center;
}

Vec3 Camera::getNormal(){
    return normal;
}

double Camera::getFocus(){
    return focus;
}

std::vector<int> Camera::getSize(){
    return size;
}

std::vector<double> Camera::getResolution(){
    return resolution;
}

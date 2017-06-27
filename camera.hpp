#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "geometry.hpp"
#include <vector>

class Camera{
public:
    Camera();
    
    Camera(Vec3 center, Vec3 normal, double focus, std::vector<int> size, std::vector<double> resolution);
    
    Vec3 getCenter();
    
    Vec3 getNormal();
    
    double getFocus();
    
    std::vector<int> getSize();
    
    std::vector<double> getResolution();
    
private:
    Vec3 center;
    Vec3 normal;
    double focus;
    std::vector<int> size;
    std::vector<double> resolution;
    
};

#endif

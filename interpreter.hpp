#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>
#include <QImage>
#include <QColor>
#include <QRgb>
#include <math.h>
#include <stdlib.h>
#include <future>
#include "camera.hpp"
#include "light.hpp"
#include "objects.hpp"
#include "parser.hpp"

class Interpreter{
public:
    //default constructor
    Interpreter();
    
    ~Interpreter();
    
    // Given a json file as a std::istream, attempt to parse into an objects
    // return true on succes s, false on failure
    bool parse(std::string json);
    
    //render the image based on the json file
    void render(int threads);
    
    //save the image to a png file
    void saveImage(QString fname);
    
    //find the color for individual pixel
    Color findColor(double x, double y);
    
    std::vector<std::vector<Color>> process(int threadNum, int index, int size_x, int size_y);
    
    Color fromOneLight(double x, double y, Light &light);
    
    //scale color
    void scale();
    
    //find dot product of two vectors
    double dotProduct(const Vec3 &a, const Vec3 &b);
    
    //get unit vector
    Vec3 unitVector(const Vec3 &v);
    
    Color getColor( Objects *obj,const Vec3& intersection, Light light);
    
    bool isCovered(const Vec3 &focus, const Vec3 &end, int index);
    
    bool closer(const Vec3 & focus, const Vec3 & intersection, const Vec3 & closest);
    
    Color negativeColor(Color c);
    
    
private:
    Camera camera;
    std::vector<Light> lights;
    std::vector<Objects * > objects;
    std::vector<std::vector<Color>> imagePanel;

};

#endif

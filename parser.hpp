#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <vector>
#include <QDebug>
#include "camera.hpp"
#include "objects.hpp"
#include "plane.hpp"
#include "light.hpp"
#include "sphere.hpp"
#include "vector"

class Parser{
public:
    //default constructor to take in a json file
    Parser(std::string fileName);
    
    //get camera object
    Camera getCamera();
    
    //get lights
    std::vector<Light> getLights();
    
    //get objects
    std::vector<Objects *> getObjects();
    
    void printJson(QJsonObject jObj);
    
    QJsonObject getJObj();
    
    Vec3 vecFromJObj(QJsonObject obj);
    
    void checkColor(int c);
    
private:
    QJsonObject jObj;
    
};

#endif

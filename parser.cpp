#include "parser.hpp"

Parser::Parser(std::string fileName){
    
    QString str = QString::fromStdString(fileName);
    QFile file(str);
    
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        throw std::exception();
    }

    
    QTextStream qts(&file);
    QString json = qts.readAll();

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error != QJsonParseError::NoError) {
        throw error;
    }
    
    jObj = jsonDoc.object();
}

Camera Parser::getCamera(){
    
    QJsonObject camObj = jObj["camera"].toObject();
    QJsonObject centerObj = camObj["center"].toObject();
    Vec3 center = vecFromJObj(centerObj);
    
    
    QJsonObject normalObj = camObj["normal"].toObject();
    Vec3 normal = vecFromJObj(normalObj);
    
    double focus = camObj["focus"].toDouble();
    
    QJsonArray JSize = camObj["size"].toArray();
    int begin = JSize.at(0).toInt();
    int end = JSize.at(1).toInt();
    if (begin < 0 || end < 0){
        throw std::invalid_argument("Negative size");
    }
    std::vector<int> size;
    size.push_back(begin);
    size.push_back(end);
    
    QJsonArray JResolution = camObj["resolution"].toArray();
    double Rbegin = JResolution.at(0).toDouble();
    double Rend = JResolution.at(1).toDouble();
    if (Rbegin < 0 || Rend < 0){
        throw std::invalid_argument("Negative resolution");
    }
    std::vector<double> resolution;
    resolution.push_back(Rbegin);
    resolution.push_back(Rend);
    
    Camera camera(center,normal,focus,size,resolution);
 
    return camera;
    
}

std::vector<Light> Parser::getLights(){
    std::vector<Light> temp;
    
    QJsonArray lights = jObj["lights"].toArray();
    for (int i = 0; i < lights.size(); i++){
        
        QJsonObject value = lights.at(i).toObject();
        if (value["intensity"].type() != 2){
            throw std::invalid_argument("Intensity is not double");
        }
        double intensity = value["intensity"].toDouble();
        if (intensity < 0){
            throw std::invalid_argument("Negative intensity");
        }
        QJsonObject location = value["location"].toObject();
        
        Vec3 loc = vecFromJObj(location);
        
        Light light(loc,intensity);
        temp.push_back(light);
    }
    
    
    
    return temp;
}

std::vector<Objects *> Parser::getObjects(){
    std::vector<Objects *> temp;
    
    QJsonArray objects = jObj["objects"].toArray();
    
    for (int i = 0; i < objects.size();i++){
        QJsonObject value = objects.at(i).toObject();
        QString str = value["type"].toString();
        QJsonObject center = value["center"].toObject();

        Vec3 cent = vecFromJObj(center);
        
        QJsonObject color = value["color"].toObject();
        int r = color["r"].toInt();
        int g = color["g"].toInt();
        int b = color["b"].toInt();
        checkColor(r);
        checkColor(g);
        checkColor(b);
        
        
        //center
        Color col(r,g,b);
        
        //lambert
        double lam = value["lambert"].toDouble();
        
        if (str == "sphere"){
            double radius = value["radius"].toDouble();
            if (radius < 0){
                throw std::invalid_argument("Negative radius");
            }
            Sphere * sphere = new Sphere(cent,col,lam,radius, "sphere");
            temp.push_back(sphere);
        }else{
            QJsonObject normal = value["normal"].toObject();
            Vec3 norm = vecFromJObj(normal);
            Plane * plane = new Plane(cent,col,lam,norm, "plane");
            
            temp.push_back(plane);
        }
    }
    return temp;
}

Vec3 Parser::vecFromJObj(QJsonObject obj){
    if (obj["x"].type() != 2 || obj["y"].type() != 2 || obj["z"].type() != 2 ){
        throw std::invalid_argument("Not valid value");
    }
    
    double x = obj["x"].toDouble();
    double y = obj["y"].toDouble();
    double z = obj["z"].toDouble();
    
    return Vec3(x,y,z);
}

void Parser::checkColor(int c){
    if (c < 0 || c > 255){
        throw std::invalid_argument("Color value out of range");
    }
}



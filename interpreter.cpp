#include <iostream>
#include "interpreter.hpp"

Interpreter::Interpreter(){
    
}

Interpreter::~Interpreter(){
    for (int i = 0; i < objects.size();i++){
        delete objects[i];
    }
//    for (std::vector<Objects *>::iterator i = objects.begin(); i != objects.end(); ++i) {
//        delete *i;
//    }
//    objects.clear();
}

bool Interpreter::parse(std::string json){
    try {
        Parser p(json);
        this->camera = p.getCamera();
        this->lights = p.getLights();
        this->objects = p.getObjects();
        return true;
    } catch (QJsonParseError &e) {
        std::cerr << "Fail to parse Json file.\n";
    } catch (std::invalid_argument &e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return false;
    
}

void Interpreter::render(int threads){
    int size_x = camera.getSize()[0];
    int size_y = camera.getSize()[1];
    int size = 0;
    std::vector<std::future<std::vector<std::vector<Color>>>> futurePool;
    
    
    for (int i = 0; i < threads; i++){
        auto fu = std::async(std::launch::async, &Interpreter::process,this,threads, i, size_x,size_y);
        futurePool.push_back(std::move(fu));
    }
        
    for (int i = 0; i < threads; i++){
        auto segment = futurePool[i].get();
        size = size + segment.size();
        imagePanel.reserve(size);
        imagePanel.insert(imagePanel.end(), segment.begin(),segment.end());

    }
    scale();
}

std::vector<std::vector<Color>> Interpreter::process(int threadNum, int index, int size_x, int size_y){
    std::vector<std::vector<Color>> segment;
    for (int i = 0; i < size_y/threadNum; i++){
        std::vector<Color> x_axis;
        for (int j = 0; j < size_x; j++){
            
            double x = camera.getResolution()[0]*(j - size_x/2);
            double y = camera.getResolution()[1]*(size_y/threadNum*index + i - size_y/2);
            
            Color c = findColor(x, y);
            x_axis.push_back(c);
        }
        segment.push_back(x_axis);
        
    }
    return segment;
}

Color Interpreter::findColor(double x, double y){
    Color color(0,0,0);
    for (int i = 0; i < lights.size();i++){
        Color c = fromOneLight(x, y, lights[i]);
        color = color + negativeColor(c);
    }
    
    return color;
}

Color Interpreter::negativeColor(Color c){
    int r,g,b;
    if (c.r < 0){
        r = 0;
    }else{
        r = c.r;
    }
    if (c.g < 0){
        g = 0;
    }else{
        g = c.g;
    }
    if (c.b < 0){
        b = 0;
    }else{
        b = c.b;
    }
    
    return Color(r,g,b);
}

Color Interpreter::fromOneLight(double x, double y, Light &light){
    Color color;
    Vec3 focus(camera.getCenter().x,camera.getCenter().y,camera.getFocus()*camera.getNormal().z*(-1));
    double x0 = focus.x, y0 = focus.y, z0 = focus.z;
    double dx = x - x0, dy = y - y0, dz = 0 - z0;
    Vec3 closest;
    int index = -1;
    for (int i = 0; i < objects.size(); i++){
        if (objects[i]->getType() == "sphere"){
            Sphere * s = static_cast<Sphere *>(objects[i]);
            double cx = s->getCenter().x;
            double cy = s->getCenter().y;
            double cz = s->getCenter().z;
            double r = s->getRadius();
            double a = dx * dx + dy*dy + dz*dz;
            double b = 2 * dx * (x0 - cx) + 2 * dy * (y0-cy) + 2 * dz * (z0-cz);
            double c = cx*cx + cy*cy + cz*cz + x0*x0 + y0*y0 + z0*z0 - 2*(cx*x0 + cy*y0 + cz*z0) - r*r;
            double discriminant = b*b - 4*a*c;
            if (discriminant >= 0){
                double t = ((-1)*b - sqrt(discriminant))/(2*a);
                Vec3 intersection(x0 + t*dx, y0 + t*dy, z0 + t*dz);
                if (index == -1){
                    closest = intersection;
                    index = i;
                }else{
                    if (closer(focus, intersection, closest)){
                        closest = intersection;
                        index = i;
                    }
                }
            }
        }else if (objects[i]->getType() == "plane"){
            Plane * p = static_cast<Plane *>(objects[i]);
            Vec3 PRay(dx,dy,dz);
            PRay = unitVector(PRay);
            Vec3 diff(p->getCenter().x - x0, p->getCenter().y - y0, p->getCenter().z - z0);
            double denom = dotProduct(PRay, p->getNormal());
            if (fabs(denom) > 0.001f){
                double numer = dotProduct(p->getNormal(), diff);
                double dist = numer/denom;
                if (dist >= 0){
                    Vec3 intersection(x0 + dist*PRay.x,y0 + dist*PRay.y,z0 + dist*PRay.z);
                    
                    if (index == -1){
                        closest = intersection;
                        index = i;
                    }else{
                        if (closer(focus, intersection, closest)){
                            closest = intersection;
                            index = i;
                        }
                    }
                }
            }
        }
    }
    if (index == -1 || isCovered(closest, light.getLocation(),index)){
        return Color(0,0,0);
    }
    return getColor(objects[index], closest, light);
}

Color Interpreter::getColor( Objects *obj,const Vec3 &intersection, Light light){
    Color color;
    if (obj -> getType() == "sphere"){
        Sphere * s = static_cast<Sphere *>(obj);
        Vec3 normal(intersection.x - s->getCenter().x, intersection.y - s->getCenter().y, intersection.z - s->getCenter().z);
        Vec3 shadow(light.getLocation().x - intersection.x, light.getLocation().y - intersection.y, light.getLocation().z - intersection.z);
        
        normal = unitVector(normal);
        shadow = unitVector(shadow);
        
        double scale = dotProduct(normal, shadow) * s->getLambert() * light.getIntensity();
        color = Color(scale * s->getColor().r,scale * s->getColor().g,scale * s->getColor().b);
    }else{
        Plane * p = static_cast<Plane *>(obj);
        Vec3 shadoww(light.getLocation().x - intersection.x,light.getLocation().y - intersection.y, light.getLocation().z - intersection.z);
        
        Vec3 normal = unitVector(p->getNormal());
        Vec3 shadow = unitVector(shadoww);
        
        double scale = dotProduct(normal, shadow) * p->getLambert() * light.getIntensity();
        color = Color(scale * p->getColor().r,scale * p->getColor().g,scale * p->getColor().b);
    }
    return color;
}

bool Interpreter::closer(const Vec3 &focus, const Vec3 &intersection, const Vec3 &closest){
    double distanceClosest = pow(focus.x - closest.x, 2) + pow(focus.y - closest.y, 2) + pow(focus.z - closest.z,2);
    double distance = pow(focus.x - intersection.x, 2) + pow(focus.y - intersection.y, 2) + pow(focus.z - intersection.z,2);
    return (distance < distanceClosest);
}


bool Interpreter::isCovered(const Vec3 &focus, const Vec3 &end, int index){
    Vec3 d(end.x - focus.x,end.y-focus.y, end.z - focus.z);
    double distance = pow(focus.x-end.x,2) + pow(focus.y-end.y,2) +pow(focus.z-end.z,2);
    
    double x0 = focus.x, y0 = focus.y, z0 = focus.z;
    for (int i = 0; i < objects.size(); i++){
        if (i != index){
            if (objects[i]->getType() == "sphere"){
                Sphere * s = static_cast<Sphere *>(objects[i]);

                double dx = d.x,dy = d.y,dz = d.z;
                double cx = s->getCenter().x;
                double cy = s->getCenter().y;
                double cz = s->getCenter().z;
                double r = s->getRadius();
                double a = dx * dx + dy*dy + dz*dz;
                double b = 2 * dx * (x0 - cx) + 2 * dy * (y0-cy) + 2 * dz * (z0-cz);
                double c = cx*cx + cy*cy + cz*cz + x0*x0 + y0*y0 + z0*z0 - 2*(cx*x0 + cy*y0 + cz*z0) - r*r;
                
                double discriminant = b*b - 4*a*c;
                
                if (discriminant >= 0){
                    double t = ((-1)*b - sqrt(discriminant))/(2*a);
                    Vec3 intersection(x0 + t*dx, y0 + t*dy, z0 + t*dz);
                    double iDistance = pow(intersection.x-end.x,2) + pow(intersection.y-end.y,2) +pow(intersection.z-end.z,2);
                    if (intersection.z >= 0 && iDistance < distance){
                        return true;
                    }
                }
                
            }else{
                Plane * p = static_cast<Plane *>(objects[i]);
                Vec3 PRay(d.x,d.y,d.z);
                PRay = unitVector(PRay);
                Vec3 diff(p->getCenter().x - focus.x, p->getCenter().y - focus.y, p->getCenter().z - focus.z);
                double denom = dotProduct(PRay, p->getNormal());
                if (fabs(denom) > 0.001f){
                    double numer = dotProduct(p->getNormal(), diff);
                    double dist = numer/denom;
                    if (dist >= 0){
                        Vec3 intersection(x0 + dist*PRay.x,y0 + dist*PRay.y,z0 + dist*PRay.z);
                        double iDistance = pow(intersection.x-end.x,2) + pow(intersection.y-end.y,2) + pow(intersection.z-end.z,2);
                        if (intersection.z >= 0 && iDistance < distance){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


double Interpreter::dotProduct(const Vec3 &a,const Vec3 &b){
    double result = a.x*b.x + a.y*b.y + a.z * b.z;
    return result;
}

Vec3 Interpreter::unitVector(const Vec3 &v){
    double a = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    double x = v.x/a;
    double y = v.y/a;
    double z = v.z/a;
    
    return Vec3(x,y,z);
}

void Interpreter::scale(){
    double r = 0;
    double g = 0;
    double b = 0;
    for (int i= 0; i < imagePanel.size();i++){
        for (int j = 0; j < imagePanel[i].size();j++){
            if (r < imagePanel[i][j].r){
                r = imagePanel[i][j].r;
            }
            if (g < imagePanel[i][j].g){
                g = imagePanel[i][j].g;
            }
            if (b < imagePanel[i][j].b){
                b = imagePanel[i][j].b;
            }
        }
    }
    
    double rr,gr,br;
    
    if (r > 255){
        rr = 255/r;
    }else{
        rr = 1;
    }
    if (g > 255){
        gr = 255/g;
    }else{
        gr = 1;
    }
    if (b > 255){
        br = 255/b;
    }else{
        br = 1;
    }
    for (int i= 0; i < imagePanel.size();i++){
        for (int j = 0; j < imagePanel[i].size();j++){
            
            imagePanel[i][j].r = imagePanel[i][j].r*rr + 0.5;
            imagePanel[i][j].g = imagePanel[i][j].g*gr + 0.5;
            imagePanel[i][j].b = imagePanel[i][j].b*br + 0.5;
        
        }
    }
}

void Interpreter::saveImage(QString fname){
    QImage image(imagePanel[0].size(), imagePanel.size(),QImage::Format_RGB888);
    
    for (int i = 0; i < imagePanel.size(); i++){
        for (int j = 0; j < imagePanel[i].size(); j++){
            Color c = imagePanel[i][j];
            QColor qc(c.r,c.g,c.b);
            image.setPixel(j, i, qc.rgb());
        }
    }
    QFile file(fname);
    image.save(&file,"png",100);
}

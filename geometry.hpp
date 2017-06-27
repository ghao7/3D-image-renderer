#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

struct Vec3{
    double x;
    double y;
    double z;
    Vec3(double _x,double _y, double _z){
        x = _x;
        y = _y;
        z = _z;
    }
    
//    Vec3 operator= (const Vec3& other){
//        return Vec3(other.x,other.y,other.z);
//    }
    
    Vec3(){
        
    }
    
    
};

struct Color{
    Color(int x,int y, int z){
        r = x;
        g = y;
        b = z;
    }
    Color(){
        
    }
    Color operator+(const Color&other){
        Color c(r + other.r,g + other.g,b + other.b);
        return c;
    }
    
    bool operator==(const Color & other){
        return (r == other.r && g == other.g && b == other.b);
    }
    
    Color operator* (double x){
        return Color(x*r,g*x,b*x);
    }
    int r;
    int g;
    int b;
};

#endif

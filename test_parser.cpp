#include "catch.hpp"
#include "parser.hpp"
#include "camera.hpp"


TEST_CASE("test parser getCamera", "[parser]"){
    
    {
        //std::string fileName = "/Users/guhao/Dropbox/ECE 3574/project3-guhao6869/tests/scene0.json";
        std::string fileName = "/vagrant/tests/scene0.json";
        Parser p(fileName);
        //p.printJson(p.getJObj());
        
        Camera camera = p.getCamera();
        
        REQUIRE(camera.getFocus() == 10);
        REQUIRE(camera.getCenter().x == 0);
        REQUIRE(camera.getCenter().y == 0);
        REQUIRE(camera.getCenter().y == 0);
        
        REQUIRE(camera.getNormal().x == 0);
        REQUIRE(camera.getNormal().y == 0);
        REQUIRE(camera.getNormal().z == 1);
        
        REQUIRE(camera.getSize()[0] == 256);
        REQUIRE(camera.getSize()[1] == 256);
        
        REQUIRE(camera.getResolution()[0] == 0.01);
        REQUIRE(camera.getResolution()[1] == 0.01);


    }
}


TEST_CASE("test parser getObjects", "[parser]"){
    {
        std::string fileName = "/vagrant/tests/scene0.json";
        Parser p(fileName);
        
        std::vector<Objects *> objects = p.getObjects();
        
        REQUIRE(objects[0]->getCenter().x == 0);
        REQUIRE(objects[0]->getCenter().y == 0);
        REQUIRE(objects[0]->getCenter().z == 5);
        
        REQUIRE(objects[0]->getColor().r == 255);
        REQUIRE(objects[0]->getColor().g == 0);
        REQUIRE(objects[0]->getColor().b == 0);
        
        for (int i = 0; i < objects.size();i++){
            delete objects[i];
        }
    }
    {
        std::string fileName = "/vagrant/tests/scene1.json";
        Parser p(fileName);
        
        std::vector<Objects *> objects = p.getObjects();
        
        REQUIRE(objects[0]->getType() == "sphere");
        REQUIRE(objects[1]->getType() == "plane");
        
        for (int i = 0; i < objects.size();i++){
            delete objects[i];
        }
    }
    
}

TEST_CASE("test parser getlights","[parser]"){
    {
        std::string fileName = "/vagrant/tests/scene0.json";
        Parser p(fileName);
        
        std::vector<Light> lights = p.getLights();
        
        Light first = lights[0];
        REQUIRE(first.getIntensity() == 1);
        REQUIRE(first.getLocation().x == 5);
        REQUIRE(first.getLocation().y == -5);
        REQUIRE(first.getLocation().z == 0);
        
    }
    {
        qDebug() << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        std::string fileName = "/vagrant/tests/scene2.json";
        Parser p(fileName);
        
        std::vector<Light> lights = p.getLights();
        
        Light first = lights[0];
        REQUIRE(first.getIntensity() == 0.6);
        REQUIRE(first.getLocation().x == 0);
        REQUIRE(first.getLocation().y == 0);
        REQUIRE(first.getLocation().z == -10);
        
        first  = lights[1];
        REQUIRE(first.getIntensity() == 0.5);
        REQUIRE(first.getLocation().x == 100);
        REQUIRE(first.getLocation().y == 0);
        REQUIRE(first.getLocation().z == -100);
        
    }
}

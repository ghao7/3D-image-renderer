#include "catch.hpp"
#include "interpreter.hpp"

TEST_CASE("Test render function", "[interpreter]"){
    {
        std::string fileName = "/vagrant/tests/scene1.json";
        Interpreter i;
        i.parse(fileName);
        i.render(1);
        i.saveImage("test.png");
        qDebug() << "should generate a test image";
    }
    {
        std::string fileName = "/vagrant/tests/scene3.json";
        Interpreter i;
        REQUIRE(!i.parse(fileName));
    }
}



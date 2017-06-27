#include "catch.hpp"
#include "objects.hpp"

TEST_CASE("test objects constructor", "[objects]"){
    {
        Vec3 center(1.,2.,3.);
        Color color(255,254,253);
        
        double lam = 4.4;
        
        Objects obj(center, color, lam, "plane");
        
        REQUIRE(obj.getCenter().x == 1.);
        REQUIRE(obj.getCenter().y == 2.);
        REQUIRE(obj.getCenter().z == 3.);
        
        REQUIRE(obj.getColor().r == 255);
        REQUIRE(obj.getColor().g == 254);
        REQUIRE(obj.getColor().b == 253);
        
        REQUIRE(obj.getLambert() == 4.4);
    }
}

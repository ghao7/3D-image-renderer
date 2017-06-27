#include "catch.hpp"
#include "plane.hpp"

TEST_CASE("test plane construtor", "[plane]"){
    {
        Vec3 center(1.,2.,3.);
        Color color(255,254,253);
        
        double lam = 4.4;
        
        Vec3 normal(7.,8.,9.);
        
        Plane plane(center,color,lam,normal, "plane");
        
        REQUIRE(plane.getCenter().x == 1.);
        REQUIRE(plane.getCenter().y == 2.);
        REQUIRE(plane.getCenter().z == 3.);
        
        REQUIRE(plane.getColor().r == 255);
        REQUIRE(plane.getColor().g == 254);
        REQUIRE(plane.getColor().b == 253);
        
        REQUIRE(plane.getLambert() == 4.4);
        
        REQUIRE(plane.getNormal().x == 7.);
        REQUIRE(plane.getNormal().y == 8.);
        REQUIRE(plane.getNormal().z == 9.);
        
    }
}

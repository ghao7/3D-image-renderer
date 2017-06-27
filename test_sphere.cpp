#include "catch.hpp"
#include "sphere.hpp"

TEST_CASE("test sphere constructor","[sphere]"){
    {
        Vec3 center(1.,2.,3.);
        Color color(255,254,253);
        
        double lam = 4.4;
        
        Vec3 normal(7.,8.,9.);
        
        double radius = 11.11;
        
        Sphere sphere(center,color,lam,radius, "sphere");
        
        REQUIRE(sphere.getCenter().x == 1.);
        REQUIRE(sphere.getCenter().y == 2.);
        REQUIRE(sphere.getCenter().z == 3.);
        
        REQUIRE(sphere.getColor().r == 255);
        REQUIRE(sphere.getColor().g == 254);
        REQUIRE(sphere.getColor().b == 253);
        
        REQUIRE(sphere.getLambert() == 4.4);
        
        REQUIRE(sphere.getRadius() == 11.11);
    }
}

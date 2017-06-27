#include "catch.hpp"
#include "light.hpp"

TEST_CASE("test light constructor","[light]"){
    {
        Vec3 center(1.,2.,3.);
        double intensity = 100.1;
        
        Light light(center, intensity);
        
        REQUIRE(light.getLocation().x == 1.);
        REQUIRE(light.getLocation().y == 2.);
        REQUIRE(light.getLocation().z == 3.);
        
        REQUIRE(light.getIntensity() == 100.1);
    }
}

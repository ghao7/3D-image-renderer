#include "catch.hpp"
#include "camera.hpp"
#include "geometry.hpp"
#include <vector>

TEST_CASE("test camera constructor", "[camera]"){
    {
        Vec3 center(1.,2.,3.);
        Vec3 normal(4.,5.,6.);
    
        double focus = 7.;
        std::vector<int> size(1,2);
        std::vector<double> resolution(3.,4.);
    
        Camera camera(center, normal, focus, size, resolution);
        
        REQUIRE(camera.getCenter().x == 1.);
        REQUIRE(camera.getCenter().y == 2.);
        REQUIRE(camera.getCenter().z == 3.);
        
        REQUIRE(camera.getFocus() == 7.);
        REQUIRE(camera.getSize() == size);
        REQUIRE(camera.getResolution() == resolution);

    }
}

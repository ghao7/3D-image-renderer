Project 3 Hao Gu

My program first parse the son file and store each elements into different objects. I store lights into a vector of lights and store objects to a list of objects. Plane and sphere inherit from Objects class so that they can be stored in a same vector.

Next step is calculation. Basically, I go through all the pixels inside a camera plane to find if there is a intersection between the primary ray to the objects. If no intersection is found, the color for that pixel will be set 0,0,0. If intersections are found, then I will determine if the shadow ray coming out of the object to light will be intersected by other objects. If so, color 0,0,0 will be returned. Whenever I found the intersection on the shadow ray is behind the camera, I will let the light through.

For threading implementation, I split the output image in n (the number of threads asked to be implemented) vertical parts, and for each part, I assign one thread to calculate the color for that part of the pixels. I use std::future and std::async to implement threads and use future.get() function to get the pixels containing its color information.

Final, I will parse all the pixels and use qcolor to write individual pixel to a png file.

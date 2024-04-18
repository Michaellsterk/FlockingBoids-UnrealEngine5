Unreal Engine 5 Boids/Flocking Implementation for IMGD4000  
Submission for Michael Sterk  

This project spawns 15 boid actors in random locations within a cube.  
They are each given a random velocity to avoid immediate grouping.  

All 3 rules of boids are implemented.  
Since initial values are randomized and boids is hard to tweak in 3D it can be better to re-run in the engine preview a few times to see different flockings.  

The tweak that I implemented from [http://www.kfish.org/boids/pseudocode.html](http://www.kfish.org/boids/pseudocode.html) was velocity limiting.  
This tweak was also helpful in testing as it allowed for the boid clusters to be more easily followed with the controllable camera.  

Here is my gameplay recording demonstrating the boids/flocking from this code: [https://youtu.be/hNXXWWD4Uek](https://youtu.be/hNXXWWD4Uek)  

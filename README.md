# Boids Simulation

### Background

This is a Boid simulation, an artificial life program which simulates the flocking behaviour of birds/swarming behavior of fish. It is based on the rules defined by by [Craig Reynolds in 1986](http://www.red3d.com/cwr/boids/).

The simulation consists of individual flocking creatures called boids ("bird-oids") which are essentially points in space with vectors indicating their motion. 

The boids' flocking behavior are determined by 3 principles of computational geometry.

Principle | Image
------------ | -------------
**Separation:** steer to avoid crowding local flockmates. | ![Boid Steering](http://www.red3d.com/cwr/boids/images/separation.gif) 
**Alignment:** steer towards the average heading of local flockmates. | ![Boid Alignment](http://www.red3d.com/cwr/boids/images/alignment.gif)
**Cohesion:** steer to move toward the average position of local flockmates. | ![Boid Cohesion](http://www.red3d.com/cwr/boids/images/cohesion.gif)

You can change how much these 3 rules affect the Boids' movement through the GUI to change the overall flocking behavior. 

Additionally this simulation has Predator Boids, which do not abide by the regular flocking rules. They chase regular Boids which get deleted from the program if caught.

The simulation also contains circular Obstacles, which the Boids have movement rules to avoid.

Boids are softly bound to the visualization screen, meaning they can leave the bounds of the screen but quickly return if they do so.

![simulation running](https://i.ibb.co/PGpRZHv/On-Paste-20201218-210541.png)

### Running the Simulation

This simulation requires Cinder to run. Once installed, copy this repository into the Cinder root directory.

To run the simulation simply run the boid-simulation-visualizer or cinder-app-main.cc file. 

You can spawn Boids by using left click and place Obstacles using right click. Spawning regular and Predator boids can be toggled using the GUI and other parameters such as flocking behavior, size, and max speed can also be changed. 

![GUI](https://i.ibb.co/1LWckn7/image.png)

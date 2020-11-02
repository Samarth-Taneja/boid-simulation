#Boids Simulation
###Background
Boids is a type of artificial life program which simulates the flocking behaviour of birds/swarming behavior of fish. It was developed by [Craig Reynolds in 1986](http://www.red3d.com/cwr/boids/).

The simulation consists of individual flocking creatures called boids ("bird-oids") which are essentially points in space with vectors indicating their motion. They can represent birds, fish, drones, or evil penguins if you're working on Tim Burton's Batman Returns movie.
![Penguins Boids](https://i.imgur.com/QK9mF04.gif)

The boids' movements are determined by 3 principles of computational geometry.

Principle | Image
------------ | -------------
**Separation:** steer to avoid crowding local flockmates. | ![Boid Steering](http://www.red3d.com/cwr/boids/images/separation.gif) 
**Alignment:** steer towards the average heading of local flockmates. | ![Boid Alignment](http://www.red3d.com/cwr/boids/images/alignment.gif)
**Cohesion:** steer to move toward the average position of local flockmates. | ![Boid Cohesion](http://www.red3d.com/cwr/boids/images/cohesion.gif)

Computationally, you calculate how much a boid will get moved by each of the three rules, giving you three velocity vectors. Then you add those three vectors to the boid's current velocity to work out its new velocity.

Applying these simple rules for individual boids gives you complex and beautiful simulations like this:
![Boids Example](https://thumbs.gfycat.com/CharmingBleakCattle-small.gif)

###What I'm going to do
For my project I'm going to create a 2D implementation of such a Boids simulation using my own vector math/physics. 

I'm then going to add customizability to the behavior of the Boids (e.g- how much the 3 rules affect the motion of the boids).

To make the simulation more complex, I'll add obstacle detection to the Boids so they have to steer to avoid obstacles created in their virtual environment.

Finally, I'll create "Predator Boids" that the regular boids have to steer away from to simulate natural predators.

###Why I want to do it
The project is going to involve bits of Vector Calculus, Linear Algebra, and Physics working together. I've learnt a lot of those topics recently and want to explore them through code. 

And in general the simulations look really cool and it'll be fun to see how I can experiment with the variables and obtain different results.

###Timeline
#####Week 1:
- Work on vector implementation. Cinder has vectors by default but I suspect I'm either going to have to code my own or extend their implementation to include all the math I need.
- Adding physics. I'll have to code in how vectors of position, velocity, and acceleration all work together for the Boids.
- Basic Boid object and Simulation implementation.
#####Week 2:
- Create Cinder app. Translate computations and Boid objects into visuals in the Cinder app.
- Add custom flock parameters (e.g- how much the 3 rules affect the motion of the boids) to the Cinder to customize the simulation.
- Create Obstacle and Predator Boid object implementations.
#####Week 3:
- Add Obstacle detection and Predator Boid implementation.
- Add Obstacle and Predator Boid creation capabilities to Cinder app.
#####Extras/"Stretch Goals" (time permitting):
- Turn the project from 2D to 3D.
- Add ability to draw lines/shapes in the Cinder App that will become objects for the Boids to avoid in the simulation (instead of predefined objects).
- Add the ability to save data on the Boids movements throughout the course of the simulation.
# flocking_shader
Qin Yang, Ziting Shen, fall 2016

Intended Behaviour of Boids
1. Boid speed cap is scaled with the speed of the goal, and there is a speed floor for boids in case of a static goal

2. Flocks may not be able to flock right upon the goal, as two flocks are simultaneously approaching the goal while trying to avoid each other 

Intended Behaviour of Views
1. In trailing view, view could shake when the flock is turning around, disrupted by a near by predators, or when flying around the goal. It is because when the the direction of velocity of each boid are not in uniformity, these is really not a well-defined "tail" of the flock as a whole, and our heuristic approach sometimes yeild volatile results.

2. In side view, it is intended such that the view "spins" when flocks are around the goal. As the direction of the look is determined by the vector from the centroid of the flock and the goal position. As the flock moves around the goal, the view naturally turns around.

Extra credits:
1. Flapping
2. Two flocks:
	a) Flocks avoid each other, but prioritise chasing 
	b) Regroup after being disrupted by Predators
	c) Tend to slowdown, spread out, and disalign with other boids in flock when in proximity to the goal
3. Shadows - Projected on the tiles
4. Predators - chasing a nearby boid; all boids in its deterence radius avoids it

Key control:
'=': add a boid
'-': delete a boid
'v': default view
'g': side view
't': trailing view; using 'c' to choose which flock to follow
'w': move goal along +y direction
's': move goal along -y direction
'd': move goal along +x direction
'a': move goal along -x direction
'<-': decrease the goal speed
'->': increase the goal speed
'p': pause & single step
'r': resume
'q'/'esc': quit
'u' : add/delete a predator at the midpoint between the centroids of two flocks and the goal
'c'	: When in Tailing View, switch between two flocks
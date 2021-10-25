# Brick Breaker
This project represents a homework for the "Computer Graphics" course.

The aim is to implement a simple Brick Breaker game. My implementation has the following features:

- power-ups (increased platform size, reduced ball speed, anti-dropping shield) and power-downs (decreased platform size, increased ball speed) that are dropped when breaking some of the bricks;
- bricks with different colours, each colour representing the numebr of times it needs to be hit before breaking;
- 3 lives; a life is lost when the ball is "dropped" (meaning the ball touches the bottom edge of the display window);
- upon hitting the platform, the ball's trajectory changes according to its position on the platform: the closer to the center of the platform, the smaller the angle between the Y axis and the trajectory of the ball, and vice versa.

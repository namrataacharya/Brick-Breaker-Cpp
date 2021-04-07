
#Brick Breaker

For my final project, I am going to recreate the game Brick Breaker.
This is a game that was developed by Ali Asaria and released in 1999. Because this
was one of the first games I remember playing religiously as a kid on my dad's Blackberry,
I thought it would be interesting to understand the code and creation of one of the 
most iconic, well known games in the world.

In my version of Brick Breaker, there will be a paddle that moves horizontally
across the screen in response to keyboard input (arrow keys). There will also be a 
ball that is given a random velocity at the start of the game. The game will be 
held within a box on the screen that ball and paddle may not move outside of. 
The game box will also contain different types of bricks in a specified layout. 
The bricks that are easiest to break will by given a lower point value, and the bricks
that are harder to break will be a given a higher point value. For each brick that is
broken, the player's score will be updated and displayed on the screen. Once all the 
bricks are gone, the user will have won the game. The functionality of the paddle will
be made so that if the paddle is moved in the same direction as the the one the ball
bounces in when it comes in contact with the paddle, the speed of the ball will slightly
increase. If the ball hits the paddle and the paddle and ball are moving
in opposite directions at the time of contact, the ball's speed will slightly decrease.
There will be a upper and lower bound on the ball's speed, however. The player will
be given 3 lives before the game ends. If the ball touches the ground of the game box
and is not caught by the paddle, the player will lose a life. 

_Weekly breakdown for what I will accomplish over the course of three weeks:_

**WEEK 1**  
During the first week, I will create the game box, paddle, and ball. I will give
the paddle functionality with keyboard input, and will create movement for the ball.
I will also make it so that they are displayed on the game screen with Cinder.


**WEEK 2**  
During the second week, I will add the different bricks to the game box. I will give them 
different strengths, and will give them an associated point value. I will also implement 
the speed changes based on the ball and paddle movement at the time of contact.
I will also make it that so they are displayed on the game screen with Cinder.

**WEEK 3**  
During the third week, I will make the bricks so that they are breakable. Breaking the bricks 
will change the score, so I will also create a game score display and add the 3 lives game component.
I will also make it so that they are displayed on the game screen with Cinder.

_**STRETCH GOALS**_  
If I finish my project early, I will add mystery boxes that will appear on the screen for
a limited amount of time. If a mystery box is hit, the user will gain some ability that will 
help them rid of bricks faster while boosting the player's score. The mystery box's effects 
will last for a limited amount of time. 




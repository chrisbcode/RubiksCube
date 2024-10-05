# Rubiks.c
I originally made this simple program using C and Code Composer Studio, running it on the MSP430. I'm now using CLion. 
Program can turn a rubiks cube and print out the results, and also executes users commands in UI.
Program is sometimes buggy when using the last 3 of 9 operations (which is when you turn the left, top, right, or bottom sides vertically).
Feel free to drop any comments or suggest changes, thanks for looking at my program / second post.

I'm planning to fix the previously mentioned bug with the last three operations, but also (possibly) implement functions with a more informational purpose, like what side has the most matching color squares, biggest matching color section on a side / sides, etc.
I'm also planning on seeing if it's possible implementing a solve function by using an algorithm like Korf's, Kociemba's or the CFOP algorithm.
Maybe later down the line I'll either add graphics to this project or make a completely seperate project.


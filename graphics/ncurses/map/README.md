# Planed Features
- Shockwave out of an object
- Can reload the map
- An "AI" that runs away from you
- move also diagonaly -> (4*2) Directions
- not just diagonal but make a direct angle to the "Coin"
- Render in chunks, if the map is too big for the screen.
- Implement decent Objekt/Player-System
- More O's to collect "Like coins" -> When collect despawn or move.
- Path-Finding algorithm
- Labyrinth with Start + End

- Refactor it and distribute it in multiple files.


# DONE
- If it detects a wall, it will decide other direction


# INFO
The current "algorithm" is too stupid to find the target.
It reapeats at some places, so i thought to add some "forbidden" Blocks that
may only touched 1/2 times.
 
-- --

sweat spot:
clang -w -o main main.c -lm -lcurses && ./main 25 1 9

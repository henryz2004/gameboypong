![](https://github.com/henryz2004/gameboypong/blob/main/demo.gif)

BY HENGYUAN (HENRY) ZHANG
For CS 2110 @ Georgia Tech

Written in C for the Gameboy emulator.

WELCOME TO
        
```
                 ___
|      |        |   \
|      |        |___/
|___   |   __   |
|   \  |  /  \  |
|___/  |  \__/  |
```

PHYZY THE BLOP IS TRYING TO PLAY PONG BUT HE HAS NO FRIENDS :(.
THAT MEANS HE HAS TO PLAY AGAINST HIMSELF. *SPOILER ALERT: PHYZY WINS*

KEEP THE ORANGE IN BOUNDS AS LONG AS YOU CAN!

CONTROLS:
ENTER - START
UP - MOVE PHYZY COUNTERCLOCKWISE

OTHER CONTROLS (FOR COMPLETENESS BUT YOU ARE NOT SUPPOSED TO USE THESE):
LEFT - DECREASE PHYZY RADIUS
DOWN - MOVE PHYZY CLOCKWISE
RIGHT - INCREASE PHYZY RADIUS


IF YOU HIT THE ORANGE WHILE PHYZY IS MOVING, THE ORANGE WILL
"SPIN" AND DEFLECT WEIRDLY (THIS IS INTENTIONAL).

### How to run
1. Open desktop
2. Run `docker.sh` to pull and run the CS2110 docker image
3. Go to `http://127.0.0.1:6901/` and press Connect
4. Navigate to the `~/host/` directory
5. Run `make mgba` in the root directory of this repository
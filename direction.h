#pragma once

enum Direction {UNKNOWN, RIGHT, LEFT, UP, DOWN};

static Direction inverse(Direction dir)
{
    if(dir == RIGHT)
        return LEFT;
    else if(dir == LEFT)
        return RIGHT;
    else if(dir == UP)
        return DOWN;
    else if(dir == DOWN)
        return UP;
    else
        return UNKNOWN;
}

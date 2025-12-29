#include <stdio.h>
#include "calc.h"

static int sp = 0;
static double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    return 0.0;
}

int stacksize(void) {
    return sp;
}

void clearstack(void) {
    sp = 0;
}


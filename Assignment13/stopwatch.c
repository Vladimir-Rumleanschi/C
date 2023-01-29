/*
make stopwatch
echo "a2a1a1a1b1a1a1q" | ./stopwatch
make stopwatch && echo "a2a1a1a1b1a1a1q" | ./stopwatch

tests:
echo "aaaabaaq" | ./stopwatch > test1-got.txt && diff -w test1-want.txt test1-got.txt
echo "a2a1a1a1b1a1a1q" | ./stopwatch > test2-got.txt && diff -w test2-want.txt test2-got.txt
echo "bxabxabbq" | ./stopwatch > test3-got.txt && diff -w test3-want.txt test3-got.txt
echo "bxa1bxabbq" | ./stopwatch > test4-got.txt && diff -w test4-want.txt test4-got.txt
*/
#include "base.h"

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#endif

static time_t time_start;
static time_t time_end;

// todo: explain Event
typedef enum {
    None,
    PressA,
    PressB,
} Event;

// todo: explain State
typedef void* State(Event);

State reset;
State running;
State stop;

// Starts taking time.
void start_timer(void) {
    time_start = time(NULL);
}

// Ends taking time and returns the number of ms since timer start.
int end_timer(void) {
    time_end = time(NULL);
    double d = difftime(time_end, time_start);
    if (d < 0) return 0;
    return (int)d;
}

void sleep_sec(int sec) {
#if defined(_WIN32) || defined(WIN32)
    Sleep(1000 * sec);
#else
    sleep(sec);
#endif
}

// Transition when receiving event in state reset.
void* reset(Event event) {
    if (event == PressA) {
        printsln("transition to state running");
        start_timer();
        return running;
    }
    return reset;
}

// Transition when receiving event in state running.
void* running(Event event) {
    // todo: implement
    return running;
}

// Transition when receiving event in state stop.
void* stop(Event event) {
    // todo: implement
    return stop;
}

// todo: explain what this function does and whether or not it may fail for any input
void operate_fsm(void) {
    State* state = reset;
    printsln("entering initial state");
    Event e = None;
    while (true) {
        char c = getchar();
        if (c >= '0' && c <= '9') sleep_sec(c - '0');
        switch (c) {
            case 'a': e = PressA; break;
            case 'b': e = PressB; break;
            case 'q': return;
            default: e = None; break;
        }
        if (e != None) state = state(e);
    }
}

int main(void) {
    operate_fsm();
    return 0;
}

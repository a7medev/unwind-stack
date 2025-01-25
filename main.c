#include <stdio.h>

extern int unwind_stack(void **backtrace, int max_frames);

int magicNumber() {
    const int MAX_STACK_FRAMES = 25;
    void *backtrace[MAX_STACK_FRAMES];

    int frames_count = unwind_stack(backtrace, MAX_STACK_FRAMES);

    printf("Found %d frames\n", frames_count);

    for (int i = 0; i < frames_count; i++) {
        printf("frame #%d: %p\n", i, backtrace[i]);
    }

    return 0;
}

int check(int x) {
    return x == magicNumber();
}

int add(int x) {
    if (check(x)) {
        x += 1;
    } else {
        x -= 1;
    }
    return x;
}

int main() {
    int x = 0;
    x = add(x);
    return 0;
}

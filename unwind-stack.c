
#include "unwind-stack.h"

int unwind_stack(void **backtrace, int max_frames)
{
    int frames_count = 0;

    __asm__(
        // Load the first frame pointer and return address
        "      mov x10, x29\n"
        "      mov x11, x30\n"

        // Load input parameters
        "      mov x12, %[backtrace]\n"
        "      mov w13, %w[max_frames]\n"

        // Frames count
        "      mov w14, #0\n"

        // Traverse stack frames
        "loop:\n"
        "      str x11, [x12], #8\n"
        "      ldp x10, x11, [x10]\n"
        "      add w14, w14, #1\n"

        // Break out of the loop if frames count == max frames or frame pointer is NULL.
        // Loop if w13 != w14 && x10 != 0
        "      cmp w13, w14\n"
        "      b.eq Ldone\n"
        "      cbnz x10, loop\n"

        // Store frames count found
        "Ldone:\n"
        "mov %w[frames_count], w14\n"
        : [frames_count] "=r"(frames_count)
        : [backtrace] "r"(backtrace), [max_frames] "r"(max_frames)
        : "x10", "x11", "x12", "w13", "w14");

    return frames_count;
}

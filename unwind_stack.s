.global _unwind_stack
.align 2

_unwind_stack:
    # x0: void **backtrace
    # x1: int max_frames

    # Save registers
    stp x29, x30, [sp, #-16]!

    mov x10, x29
    mov x11, x30

    # Frames count
    mov x12, #0

    # Traverse stack frames
loop:
    str x11, [x0], #8
    ldp x10, x11, [x10]
    add x12, x12, #1

    # Break out of the loop if frames count == max frames or frame pointer is NULL.
    # Loop if x1 != x12 && x10 != 0
    cmp x1, x12
    b.eq exit
    cbnz x10, loop

exit:
    # Store frames count found
    mov x0, x12

    # Load saved registers
    ldp x29, x30, [sp], #16
    ret

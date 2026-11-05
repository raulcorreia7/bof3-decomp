#include "game_00.h"

MATCH void func_8019EE10(void) {
    Actor* work;
    Actor* next;

    g_Task->flags_24          = 1;
    FIELD(u16, g_Task, 0x2Cu) = D_80145EBC;
    g_Task->unk_28            = 2;
    FIELD(u32, g_Task, 0x4Cu) = D_80145EDC;
    g_Task->unk_2B            = 1;
    g_Task->unk_29            = D_80145EB9;
    /* The work pointer cell is re-read once per store; the second read is kept in
     * its own local so both reads stay in the original load-then-store order. */
    work                      = g_Task;
    work->unk_25              = 0x1D;
    next                      = g_Task;
    FIELD(u32, work, 0x70u)   = 0;
    next->unk_26              = 0;
    g_Task->tint.bytes.unk_5D = 0;
    g_Task->tint.bytes.unk_5E = 0;
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->tint.bytes.flags  = 0;
    g_Task->unk_48            = 0;
}

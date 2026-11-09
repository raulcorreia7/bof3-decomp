#include "area030_04.h"

/* Either advances the local AREA030 scratch record from the shared
 * world state or falls back to the game-side helper when the countdown gate is
 * not active. */
MATCH void func_801D2AE0(void) {
    volatile u8* scratch;
    volatile u8* world;

    world = ((volatile u8*)&D_80140000);

    if ((*(s16*)(world + 0x4006u) <= 0) || (world[0x3FC9u] == 0u)) {
        Actor_Clear();
        return;
    }

    scratch                    = (volatile u8*)g_Task;
    *(u32*)((scratch + 0x34u)) = *(u32*)((world + 0x3FFCu));
    *(u32*)((scratch + 0x38u)) = *(u32*)((world + 0x4000u));
    scratch[0x2Au]             = world[0x3FF2u];

    scratch                    = (volatile u8*)g_Task;
    scratch[0x49u]             = world[0x4011u];
    scratch                    = (volatile u8*)g_Task;
    scratch[0x4Au]             = world[0x4012u];
    scratch                    = (volatile u8*)g_Task;
    scratch[0x4Bu]             = world[0x4013u];
    scratch                    = (volatile u8*)g_Task;
    *(u32*)((scratch + 0x50u)) = *(u32*)((world + 0x4018u));
    *(u32*)((scratch + 0x54u)) = *(u32*)((world + 0x401Cu));
    *(u16*)((scratch + 0x58u)) = *(u16*)((world + 0x4020u));
    *(u16*)(scratch + 0x5Au)   = *(u16*)((world + 0x4022u));
    func_8014D290();
}

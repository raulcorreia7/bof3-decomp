#include "engine/slus/slus.h"

/* seeds the scratch work area for the incoming scene: clears work byte 0x5, copies D_80145FBC to byte 0xB,
 * sets byte 0x11C of the local-work block, stores D_80145EC4/8/C at +0x34/+0x38/+0x3C and advances the work byte at
 * 0x1.
 */
MATCH void Area_InitScene(void) {
    Actor* work;

    g_SpadWork->unk_05            = 0;
    g_SpadWork->unk_0B            = D_80145FBC;
    *(u8*)&g_GameState->hp_change = 3; /* FAKE: retail stores the byte. */
    work                          = g_SpadWork;
    /* NOTE: member stores reorder the loads of these three words; the volatile FIELD form matches. */
    FIELD(u32, work, 0x34u)       = D_80145EC4;
    FIELD(u32, work, 0x38u)       = D_80145EC8;
    FIELD(u32, work, 0x3Cu)       = D_80145ECC;
    work->unk_01                  = work->unk_01 + 1;
}

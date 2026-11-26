#include "engine/game/00/game_00.h"

/* func_801C51B0 */
/* Starts the dismount: clears the actor's palette row and requests the dismount animation of the facing. */
MATCH void Area_ClimbDismountBegin(void) {
    Actor* actor;
    u8     slot;
    u32    facing;
    s32    animation;

    actor                                           = TASK(Actor);
    slot                                            = actor->unk_05;
    g_GfxPalettePending                             = 1;
    *(u16*)(MEM_PTR(u8, 0x8003963Eu) + (slot << 6)) = 0;
    facing                                          = actor->direction;
    /* FAKE: barrier keeps saved ra from sinking below actor load. */
    FAKE_BARRIER();
    animation = 52;
    if (facing == FACING_LEFT) {
        animation = 55;
    }
    Script_Request(animation);
}

#include "area189_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4DE0(void) {
    s32    value;
    s32    count;
    Actor* work;
    s32    offset;
    s32    match;
    u8*    flags;

    /* FAKE: the retail frame holds 0x10 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 0x10);

    SetGeomOffset(0xA0, 0xB9);
    SetGeomScreen(0x12C);
    g_AreaCameraAngle.vx     = -0x2EE;
    g_Task->direction        = LOBU(D_8014504B);
    D_801492DC               = ((0x12 - LOBU(D_8014504B)) & 0xF) << 8;
    work                     = g_Task;
    g_AreaScrollTargetX      = work->pos.x.fixed;
    g_AreaCameraOffsetZ      = -0xD80;
    g_AreaScrollTargetY      = work->pos.y.fixed;
    g_AreaCameraRefreshCount = 4;
    match                    = 0;
    g_Task->pos.z.fixed      = func_801F4A04(work->pos.x.fixed, work->pos.y.fixed) << 16;
    Actor_ClearVelocity_801F5F20();
    g_Task->active_flags  = 0;
    g_Task->script_record = 0;
    g_EncounterSteps      = 0;

    value = (rand() & 0x1F) + 0x96;
    count = Party_CountOrder(PARTY_ORDER_FIELD) & BYTE_MASK;
    if (count != 0) {
        offset = 0;
        do {
            if ((func_801C38F4((&g_Game.members[0].character_index)[offset], 3, 0x15) & BYTE_MASK) != 0) {
                break;
            }
            match++;
            offset += BATTLE_PARTY_STRIDE;
        } while (match < count);
        if (match < count) {
            value <<= 1;
        }
    }
    if (count != 0) {
        match  = 0;
        offset = 0;
        do {
            if ((func_801C38F4((&g_Game.members[0].character_index)[offset], 3, 0x14) & BYTE_MASK) != 0) {
                break;
            }
            match++;
            offset += BATTLE_PARTY_STRIDE;
        } while (match < count);
        if (match < count) {
            value >>= 1;
        }
    }
    if (D_8014933C == 0) {
        value <<= 1;
    }
    D_80145FB8 = value;

    flags = g_SceneEventFlags;
    SYS_ClearFlag(flags, 0x75);
    SYS_ClearFlag(flags, 0x76);
    SYS_ClearFlag(flags, 0x8B);
    SYS_ClearFlag(flags, 0x8C);
    SYS_ClearFlag(flags, 0x8D);
    SYS_ClearFlag(flags, 0x8E);
    g_Task->header.step += 1;
}
#else
INCLUDE_ASM(func_801F4DE0);
#endif

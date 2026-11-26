#include "area189_13.h"

/* Start the Desert of Death walk: camera, leader height and the encounter pace from the party equipment. */
MATCH void func_801F4DE0(void) {
    s32 value;
    s32 count;
    s32 i;
    s32 x;
    s32 y;
    u8* flags;

    SetGeomOffset(0xA0, 0xB9);
    SetGeomScreen(0x12C);
    g_AreaCameraAngle.vx     = -0x2EE;
    TASK(Actor)->direction   = LOBU(D_8014504B);
    D_801492DC               = ((0x12 - LOBU(D_8014504B)) & 0xF) << 8;
    g_AreaScrollTargetX      = LOW(TASK(Actor)->pos.x.fixed);
    g_AreaScrollTargetY      = LOW(TASK(Actor)->pos.y.fixed);
    g_AreaCameraOffsetZ      = -0xD80;
    x                        = LOW(TASK(Actor)->pos.x.fixed);
    y                        = LOW(TASK(Actor)->pos.y.fixed);
    g_AreaCameraRefreshCount = 4;
    TASK(Actor)->pos.z.fixed = func_801F4A04(x, y) << 16;
    Actor_ClearVelocity_801F5F20();
    TASK(Actor)->active_flags  = 0;
    TASK(Actor)->script_record = 0;
    g_EncounterSteps           = 0;

    value = (rand() & 0x1F) + 0x96;
    count = Party_CountOrder(PARTY_ORDER_FIELD);
    for (i = 0; i < count; i++) {
        if ((Char_CountEquipped(g_Game.members[i].character_index, EQUIP_GROUP_ACCESSORY, 0x15) & BYTE_MASK) != 0) {
            break;
        }
    }
    if (i < count) {
        value <<= 1;
    }
    for (i = 0; i < count; i++) {
        if ((Char_CountEquipped(g_Game.members[i].character_index, EQUIP_GROUP_ACCESSORY, 0x14) & BYTE_MASK) != 0) {
            break;
        }
    }
    if (i < count) {
        value >>= 1;
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
    TASK(Actor)->header.step += 1;
}

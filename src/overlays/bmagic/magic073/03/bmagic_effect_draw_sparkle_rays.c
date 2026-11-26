#include "magic073_03.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawRays.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawWedges.h"

#include "overlays/bmagic/shared/Effect_SparkleDrawDisc.h"

/* func_801F03E8 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

MATCH void func_801F0454(void) {
    D_801F21F0->header.flags = 0;
    D_801F21F0->header.mode  = 0;
    D_801F21F0->header.step  = 0;
    D_801F21F0->unk_03       = 0;
    D_801F21F0->unk_04       = 0;
}

MATCH u8 func_801F04A4(void) {
    s32 i;
    s32 count;

    count = 0;
    i     = 0;
    do {
        if (!(Battle_SlotIsBlocked((i + 3) & BYTE_MASK) & BYTE_MASK) && g_BattleEnemyBattlers[(i & BYTE_MASK) + 3].header.mode == 6) {
            count++;
        }
        i++;
    } while ((u32)(i & BYTE_MASK) < 8);
    i = 0;
    do {
        if (!(Battle_SlotIsBlocked(i & BYTE_MASK) & BYTE_MASK) && g_Game.members[i & BYTE_MASK].header.mode == 6) {
            count++;
        }
        i++;
    } while ((u32)(i & BYTE_MASK) < 3);
    return count;
}

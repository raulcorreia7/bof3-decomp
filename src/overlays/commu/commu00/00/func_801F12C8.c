#include "commu00_00.h"

/* FAKE: the outer index is spelled `<< 3`; `* 8` lets combine fold the -1 into
 * the table base (D_801457AB-8) and loses the retail addiu/sll pair. */
MATCH s32 func_801F12C8(volatile Actor* slot) {
    g_GameShopStock[slot->unk_1C].item_count = D_801457AB[(g_SaveData.fairy_jobs[slot->unk_05].type - 1) << 3];
    return 0;
}

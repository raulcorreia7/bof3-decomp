#include "commu00_00.h"

/* NOTE: plain views; the volatile declarations elsewhere make the status loads
 * schedule before the raw store that retail keeps ahead of them. */
/* ABI view: the callee truncates its count to u8, but this caller keeps the
 * word result (`move` before the explicit & 0xFF) as retail does. */
extern s32 Fairy_VillageCountFairies(void);

MATCH void Fairy_VillageInit(void) {
    s32 active_count;
    s32 i;

    if (g_GameAreaId != D_80143F04) {
        active_count = Fairy_VillageCountFairies();
        func_801F03D0();
        active_count &= BYTE_MASK;
        D_80145E44                      = 0;
        g_FairyVillagePendingQueueCount = 0;
        g_FairyVillageUpdateCount       = 0;
        if (active_count == 0) {
            for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
                Fairy_JoinVillage();
            }
            D_801455C2 = 0xA;
            D_801455A8 = 0;
            D_801455C3 = 1;
            D_801455C4 = 0;
            D_801455C5 = 0;
            D_801455C6 = 0;
            D_801455AC = g_BattleCount;
            D_801455B0 = g_BattleCount;
            D_801455B4 = g_BattleCount;
            D_801455B8 = g_BattleCount;
            D_801455BC = g_BattleCount;
            D_801455C0 = g_GameAreaId;
        } else {
            Fairy_VillageQueueRooms();
            func_801EF110(active_count);
            func_801EF214();
            func_801EF398();
            func_801EEEF0(active_count);
            func_801EF784();
            func_801EFA50();
            func_801EF52C();
            func_801EFEA8();
            func_801F0320();
        }
    }
    Fairy_VillageBuildJobs();
}

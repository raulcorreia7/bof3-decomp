/* One 0x74-byte entry of D_80143FFC, indexed by the byte argument of func_801CEA10. */
typedef struct PlcharCheckRecord {
    s32 pos_x; /* 0x00 */
    s32 pos_y; /* 0x04 */
    u8  pad_08[2];
    s16 z; /* 0x0A */
    u8  pad_0C[0x74 - 0x0C];
} PlcharCheckRecord;

ASSERT_SIZE(PlcharCheckRecord, 0x74);
ASSERT_OFFSET(PlcharCheckRecord, pos_y, 0x04);
ASSERT_OFFSET(PlcharCheckRecord, z, 0x0A);

extern PlcharCheckRecord D_80143FFC[];

MATCH s32 func_801CEA10(s32 arg0) {
    s32 i;

    for (i = 1; i < g_PartySize; i++) {
        if (func_801BDD58(D_80143FFC[arg0 & 0xFF].pos_x, D_80143FFC[arg0 & 0xFF].pos_y,
                          D_80143FFC[arg0 & 0xFF].z + 0x200, 1, (Actor*)&g_Game.members[i])) {
            return 1;
        }
    }
    return 0;
}

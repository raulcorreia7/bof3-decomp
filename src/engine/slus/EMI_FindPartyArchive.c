#include "engine/slus/slus.h"

MATCH u8 EMI_FindPartyArchive(u8 member_a, u8 member_b, u8 member_c) {
    s32       i;
    s32       j;
    s32       count;
    s32       first;
    s32       last;
    s32       slot;
    s32       found;
    u8        member;
    u8        result;
    u8*       party;
    u8*       loaded;
    u8*       swap;
    u8*       current;
    const u8* archive;

    loaded        = &g_EmiLoadedCharacterIndex;
    party         = D_1F800000;
    *party        = member_a;
    D_1F800000[1] = member_b;
    D_1F800000[2] = member_c;
    if (*loaded != GAME_NONE) {
        for (i = 0; i < 3; i++, party++) {
            member = *party;
            if (member != GAME_NONE) {
                current = &g_EmiLoadedCharacterIndex;
                archive = D_80181B34[*current & EMI_LOADED_INDEX_MASK];
                for (j = 0; j < 3; j++, archive++) {
                    if (member == *archive) {
                        break;
                    }
                }
                if (j >= 3) {
                    break;
                }
            }
        }
        if (i >= 3) {
            return g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK;
        }
    }
    i     = 0;
    count = 0;
    do {
        if (D_1F800000[i] != GAME_NONE) {
            count++;
        }
        i++;
    } while (i < 3);
    swap = &D_1F800000[4];
    for (i = 0; i < 2; i++) {
        for (j = i + 1; j < 3; j++) {
            if (D_1F800000[j] < D_1F800000[i]) {
                *swap         = D_1F800000[i];
                D_1F800000[i] = D_1F800000[j];
                D_1F800000[j] = *swap;
            }
        }
    }
    first = 0;
    last  = 19;
    slot  = 0;
    found = GAME_NONE;
    i     = 0;
    do {
        for (j = (u8)first; j < (u8)last; j++) {
            if (D_1F800000[slot] == D_80181B34[j][i]) {
                if (slot == (u8)count - 1) {
                    found = j;
                    break;
                }
                first = j;
                for (; j < 19; j++) {
                    if (D_1F800000[slot] != D_80181B34[j][i]) {
                        break;
                    }
                }
                last = j;
                slot++;
            }
        }
        result = found;
        i++;
        if (result != GAME_NONE) {
            goto done;
        }
    } while (i < 3);
    SYS_ShowFileNotFound();
done:
    return result;
}

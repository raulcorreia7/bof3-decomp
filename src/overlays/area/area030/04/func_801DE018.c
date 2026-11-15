#include "area030_04.h"

/* Advances the four AREA030 label slots for one frame.  Each slot
 * reloads its row byte and the masked byte its row selects in the slot table;
 * a live row first decrements its dwell counter, then a per-slot mode is chosen
 * from the refresh flag and that counter.  A retiring slot folds its signed
 * growth byte plus the character's height into the shared bar value once the
 * sum reaches the bar limit (also refreshing the bar's clear value), a growing
 * slot advances its row byte and reloads a 12-frame dwell, and any other slot
 * clears both of its bytes.
 *
 * Row bytes and dwell counters live in the byte planes at 0x801E31E0 and
 * 0x801E31E4 (four slots each, one byte per slot); the slot table at 0x801E28F4
 * has 8-byte entries whose leading word points at the row's byte string, and
 * the signed growth byte shared with that stride lives at 0x801E28F8. */
MATCH void func_801DE018(void) {
    s32 i;
    s32 mode;
    u8  v;
    u8  m;
    s8  grow;
    s8  limit;
    s8  span;

    func_801DDFD4();
    for (i = 0; i < 4; i++) {
        v    = D_801E31E0[i];
        m    = (*(u8*)(*(u8**)(D_801E28F4 + i * 8) + v) & 0x7F);
        mode = 0;
        if (v != 0) {
            D_801E31E4[i] = (D_801E31E4[i] - 1);
        }
        if (D_801E31F0 == 1) {
            if (D_801E31E0[i] != 0) {
                if (D_801E31E4[i] < 4) {
                    mode = (m == 1) ? 1 : 2;
                } else {
                    mode = 2;
                }
            } else {
                mode = 1;
            }
        } else if (D_801E31F0 == 0 && D_801E31E4[i] == 0) {
            mode = 2;
            if (m == 0) {
                mode = 1;
            }
        }
        if (mode == 1) {
            v = D_801E31E0[i];
            if ((*(u8*)(*(u8**)(D_801E28F4 + i * 8) + v) & 0x80) != 0) {
                grow  = D_801E28F8[i * 8];
                limit = g_SpawnedActors[0].unk_07;
                span  = g_FishingLureRow->unk_0F;
                if (grow + span >= limit) {
                    g_SpawnedActors[0].unk_07 = (grow + span);
                    g_SpawnedActors[0].unk_0A = g_FishingLureRow->unk_10;
                }
                D_801E31E0[i] = 0;
                D_801E31E4[i] = 0;
            } else {
                D_801E31E0[i] = (v + 1);
                D_801E31E4[i] = 0xC;
            }
        } else if (mode == 2) {
            D_801E31E4[i] = 0;
            D_801E31E0[i] = 0;
        }
    }
}

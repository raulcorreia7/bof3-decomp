#include "engine/slus/slus.h"

/* adds value to the matching key slot, capping at 99;
 * inserts a new slot and flags scratch on success.
 */
MATCH bool Item_Add(s32 category, u8 item, u8 amount, s32 unused) {
    u8  key;
    u8  add;
    u8  limit;
    u8* keys;
    u8* vals;
    s32 i;
    u8  cur;

    key = (item & 0xFF);
    add = (amount & 0xFF);
    if (key == 0) {
        return false;
    }
    if (add == 0) {
        return false;
    }
    limit         = 99;
    D_1F800000[0] = 0;
    keys          = D_801C893C[category & 0xFF];
    vals          = D_801C8950[category & 0xFF];
    i             = 0;
    do {
        if (*keys == key) {
            cur = *vals;
            if ((cur + add) <= limit) {
                *vals = (cur + amount);
                return true;
            }
            *vals = limit;
            return false;
        }
        keys++;
        i++;
        vals++;
    } while ((i & 0xFF) < 128U);
    i    = 0;
    keys = D_801C893C[category & 0xFF];
    vals = D_801C8950[category & 0xFF];
    do {
        if ((*keys == 0) || (*vals == 0)) {
            *keys         = item;
            *vals         = amount;
            D_1F800000[0] = 1;
            return true;
        }
        keys++;
        i++;
        vals++;
    } while ((i & 0xFF) < 128U);
    return false;
}

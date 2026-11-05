#include "engine/slus/slus.h"

typedef struct CopyQuad {
    u32 w[4];
} CopyQuad;

/* Previews equipping item_id in a slot: copies the party record, sets the slot,
 * rebuilds the stats on the copy and returns the four stat values with a flag
 * each (3 lower, 2 higher, 0 equal).
 */
/* func_80164D2C */
MATCH void Char_PreviewEquip(u8 character_id, u8 slot, u8 item_id, u8* flags, u16* values) {
    u8        buf[0xA4];
    u16*      entry_vals[4];
    u16*      buf_vals[4];
    u8*       entry;
    CopyQuad* src;
    CopyQuad* dstbuf = (CopyQuad*)buf;
    s32       i;
    s32       j;

    entry         = (u8*)&g_Characters[(u32)character_id];
    entry_vals[0] = (u16*)(entry + 0x20);
    entry_vals[1] = (u16*)(entry + 0x22);
    entry_vals[2] = (u16*)(entry + 0x26);
    entry_vals[3] = (u16*)(entry + 0x24);
    buf_vals[0]   = (u16*)(buf + 0x20);
    buf_vals[1]   = (u16*)(buf + 0x22);
    buf_vals[2]   = (u16*)(buf + 0x26);
    buf_vals[3]   = (u16*)(buf + 0x24);
    src           = (CopyQuad*)entry;
    do {
        *dstbuf = *src;
        src++;
        dstbuf++;
    } while ((u8*)src != entry + 0xA0);
    *(u32*)dstbuf = *(u32*)src;
    /* FAKE: keep the slot mask after the final copy store. */
    MATCH_BARRIER();
    switch (slot) {
        case EQUIP_SLOT_WEAPON:
            buf[0x0E] = item_id;
            break;
        case EQUIP_SLOT_SHIELD:
            buf[0x0F] = item_id;
            break;
        case EQUIP_SLOT_HELMET:
            buf[0x10] = item_id;
            break;
        case EQUIP_SLOT_ARMOR:
            buf[0x11] = item_id;
            break;
        case EQUIP_SLOT_ACCESSORY_1:
            buf[0x12] = item_id;
            break;
        case EQUIP_SLOT_ACCESSORY_2:
            buf[0x13] = item_id;
            break;
    }
    Char_RebuildStats((Character*)buf);
    for (i = 0; (u32)(u8)i < 4; i++) {
        j         = i & BYTE_MASK;
        flags[j]  = 0;
        values[j] = *buf_vals[j];
        if (*entry_vals[j] < *buf_vals[j])
            flags[j] = 3;
        if (*entry_vals[j] > *buf_vals[j])
            flags[j] = 2;
    }
}

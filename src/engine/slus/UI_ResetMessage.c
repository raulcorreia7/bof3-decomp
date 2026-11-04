#include "engine/slus/slus.h"

/* resets the front-end selection state: clears the area request handshake, keeps only the pending bit of
 * the flags word, consumes one byte from a type-12 resource stream, then requests menu 0 mode 0 and arms the
 * front-end entry.
 */
MATCH void UI_ResetMessage(void) {
    u8* base;
    u8* cursor;
    u8  value;
    u8* stream;

    base = (u8*)&g_UiWindowChannel;
    /* FAKE: opaque base keeps one register for the -4..0x2A record accesses (match.h operand fake-match helper). */
    MATCH_FAKE_OPAQUE(base);
    base[-4]       = 0;
    g_UiWindowStep = 0;
    D_801490A2     = 0;
    D_801490A3     = 0;
    *D_801490BA    = 0;
    *D_801490BB    = 0;
    D_801490AA     = 0;
    stream         = D_801490B0;
    *(u16*)base &= 0x40;
    if (*stream == 0xC) {
        cursor              = *(u8**)(base + 0xC);
        *(u8**)(base + 0xC) = cursor + 1;
        value               = cursor[1];
        *(u8**)(base + 0xC) = cursor + 2;
        base[0x2A]          = value;
    } else {
        D_801490CE = 0;
    }
    D_801490A6[0] = 0;
    D_801490B9    = 0;
    D_801490C8    = 0;
    D_801490B8[0] = 0;
    Menu_ArmPanelTask(0U, 0U);
    D_8014833F = 2;
}

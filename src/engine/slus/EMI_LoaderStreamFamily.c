#include "engine/slus/slus.h"

/* arms the overlay loader for the three-byte family key and waits for
 * the stream to become ready, then re-arms the four-byte key's family slot and
 * waits again.
 */
MATCH void EMI_LoaderStreamFamily(u8 member_a, u8 member_b, u8 member_c, u8 family) {
    if (family == 0) {
        EMI_ArmPartyPlp(member_a, member_b, member_c);
        while (EMI_LoaderIsReady() == 0) {
            CallbackWait(1u);
        }
    }
    EMI_ArmPartyFamily(member_a, member_b, member_c, family);
    while (EMI_LoaderIsReady() == 0) {
        CallbackWait(1u);
    }
}

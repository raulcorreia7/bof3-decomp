#include "engine/slus/slus.h"

/* Loads the character program (family 0 only) and then the character data of the party, waiting for each
 * archive to finish.
 */
MATCH void EMI_LoadPartyArchives(u8 member_a, u8 member_b, u8 member_c, u8 family) {
    if (family == 0) {
        EMI_LoadPartyCode(member_a, member_b, member_c);
        while (EMI_IsReady() == 0) {
            SYS_ThreadWait(1u);
        }
    }
    EMI_LoadParty(member_a, member_b, member_c, family);
    while (EMI_IsReady() == 0) {
        SYS_ThreadWait(1u);
    }
}

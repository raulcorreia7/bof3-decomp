#include "commu00_00.h"

/* FAKE: the load uses the g_SceneEventStep symbol and the store its literal address
 * so each access materializes its own base (retail's two symbolic accesses). */
MATCH void Fairy_ReloadPartyBank(void) {
    u8 variant;

    g_EmiStreamFlags = 0x20;
    EMI_GetArchiveId(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    variant                     = g_SceneEventStep;
    variant                     = variant + 1;
    MEM_PTR(u8, 0x801448ECu)[0] = variant;
}

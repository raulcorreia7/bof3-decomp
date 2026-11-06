#include "commu00_00.h"

/* FAKE: the load uses the g_SaveData.scene_event.step symbol and the store its literal address
 * so each access materializes its own base (retail's two symbolic accesses). */
MATCH void func_801F1824(void) {
    u8 variant;

    g_EmiStreamFlags = 0x20;
    EMI_StreamFamilyArchive(g_SaveData.emi_loaded_character_index & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    variant                     = g_SaveData.scene_event.step;
    variant                     = variant + 1;
    MEM_PTR(u8, 0x801448ECu)[0] = variant;
}

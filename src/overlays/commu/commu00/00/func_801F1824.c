#include "commu00_00.h"

/* FAKE: the load uses the D_801448EC symbol and the store its literal address
 * so each access materializes its own base (retail's two symbolic accesses). */
MATCH void func_801F1824(void) {
    u8 variant;

    g_EmiStreamFlags = 0x20;
    EMI_StreamFamilyArchive(g_SaveData.emi_loaded_character_index & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    variant                     = D_801448EC;
    variant                     = variant + 1;
    MEM_PTR(u8, 0x801448ECu)[0] = variant;
}

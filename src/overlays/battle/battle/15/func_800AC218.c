#include "battle_15.h"

/* Copies an enemy record of the encounter block (ENCOUNTER_ENEMIES, unit_index) into row slot of
 * D_801EB6A4: the two item rows at record +0x2C and +0x30 land unchanged at battler +0x98 and +0x9C (drops[2]),
 * where func_801E531C rolls them. */
INCLUDE_ASM(func_800AC218);

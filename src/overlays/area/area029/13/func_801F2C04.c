#include "area029_13.h"

/* Weighted random actor spawn: picks a row from the D_801F2DCC weights, hides
 * the first eight Actor rows except the pick, places it at the
 * D_801F2DBC/D_801F2DBD coordinate pair with the Area_SampleHeight height, and
 * steps D_80143F22 from D_80145FB8. Byte-identical in area029/063/064/072/073
 * at 0x801F2C04 (one shared body when matched) and a sixth copy in
 * emi/world02/area110/13. Near match: the loops, the flags_00 clear walk and
 * the tail are exact with a pick_weight goto label and the D_801468BC/D_801468C0
 * byte-view stores (the func_801F0718 pattern); first differing instruction is
 * retail 0x801F2C88 sll s0,s1,2 against the pick andi: retail keeps the
 * count*ACTOR_SIZE chain before the rand() call and interleaves its last sll
 * after the x-table load. Resume: a source shape that schedules the offset
 * chain that way; needs D_801468C6 declared next to D_801468BC/D_801468C0 in
 * include/slus/data.h. */
INCLUDE_ASM(func_801F2C04);

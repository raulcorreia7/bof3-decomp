#include "area059_13.h"

/* Area request handler: Game_SetScriptActive, Actor unk_01/unk_77/unk_7E,
 * the g_Actors row index into D_80146867, then D_801448EB/D_801448ED.
 * Near match: split reload statements (rec1/rec2/rec3 = g_ScriptWorkRecord)
 * plus MATCH_REG(s32, action, "a2"), a step local and two MATCH_FAKE_BARRIER
 * lines reproduce retail through 0x801F2F54 and from 0x801F2F60 on (including
 * the li a2 in the first load-delay slot and the [index][li 5][EB][ED] tail).
 * First differing instruction: retail 0x801F2F5C lui v1, %hi(g_Actors) in the
 * second load-delay slot against a nop; the table-address materialization
 * (reload re-materialized at the subu) lands one slot late whatever its
 * register. Resume: hold the g_Actors address in a pinned local whose
 * statement fills that slot, or a flag-profile trial; then func_801F3F48
 * follows with unk_77 = 5, D_801448ED = 3. */
INCLUDE_ASM(func_801F2F34);

#include "area059_13.h"

/* Area request handler: Game_SetScriptActive, Actor unk_01/unk_77/unk_7E,
 * the g_Actors row index into D_80146867, then D_801448EB/D_801448ED.
 * Near match with MATCH_REG(s32, action, "a2") plus two MATCH_FAKE_BARRIER
 * lines pins every register and store order; the first differing instruction
 * is retail 0x801F2F5C (lui v1, %hi(g_Actors) between the g_ScriptWorkRecord
 * reread and the unk_77 store) against a nop: the table-address materialization
 * lands one load-delay slot late. Resume: a source shape whose move of the
 * g_Actors address fills the earlier slot (scheduling residual). */
INCLUDE_ASM(func_801F2F34);

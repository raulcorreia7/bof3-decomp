#include "area059_13.h"

/* Area request handler: Game_SetScriptActive, Actor unk_01/unk_77/unk_7E,
 * the g_Actors row index into D_80146867, then D_801448EB/D_801448ED.
 * Best score 100 (permuter, work/permute/nonmatchings/func_801F2F34): the
 * split-reload shape with a pinned a2 request code, MATCH_FAKE_USE on the
 * table base and two MATCH_FAKE_BARRIER lines matches every instruction;
 * first differing instruction 0x801F2F68 lui a1,%hi(g_ScriptWorkRecord)
 * against lui v0 - the third reload takes v0 instead of a1 and the chain
 * colors follow. Next lever: a source shape whose third reload colors a1
 * (the rec3 pin sinks the table-address materialization out of the second
 * load-delay slot). Then func_801F3F48 follows (unk_77 = 5, D_801448ED = 3). */
INCLUDE_ASM(func_801F2F34);

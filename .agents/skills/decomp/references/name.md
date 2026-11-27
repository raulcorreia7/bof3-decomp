# Name from meaning

Input: the symbols. A name comes from what the thing means in the game, found through its users.
Rules: [names](../../../../docs/naming.md#names).

1. Find every user across all images ([users of a symbol](../../../../docs/toolchain.md#every-user-of-a-symbol)).
   `tools/symbol.py refs <dir>` ranks the address-named units by use.
2. Read what the users do: loop bounds, strides, compares, copies, calls to functions that already
   have names. Search `rg -n 'NAME|0xADDR' config include src` for an existing name.
3. Rank the evidence ([order](../../../../docs/conventions.md#evidence)): disc labels, retail text and
   data, reference notes, visible code behavior. A count, an offset match, a type or a tool's output
   is not evidence.
4. Pick the form: [register](../../../../docs/naming.md#register), [prefix](../../../../docs/naming.md#tags),
   [verb](../../../../docs/naming.md#functions), [selector](../../../../docs/naming.md#variables-parameters-and-members),
   [table](../../../../docs/naming.md#tables). Adjacent symbols read through one base are one record:
   name the record once, then its members by role.
5. Record the evidence in the commit body. Describe a symbol in its `config/symbols/<image>.toml` row's
   `source`. Rename every tracked user in one commit with
   `tools/symbol.py rename` ([recipe](../../../../docs/naming.md#rename-steps)); it writes the row. A function name goes to every copy with
   equal bytes ([shared bodies](refactor.md#shared-bodies)); a parameter name goes to
   the definition and every prototype.

Unknown keeps the address name (`func_<ADDR>`, `D_<ADDR>`, `unk_<OFF>`).

## Natural names

The test: [natural names](../../../../docs/naming.md#functions).

| Don't (mechanical)                                                      | Do (natural), when the users show it                                    | Why                                                                 |
| ----------------------------------------------------------------------- | ----------------------------------------------------------------------- | ------------------------------------------------------------------- |
| `Effect_CopyBattlerCoordsSetTimers`                                     | `Effect_StartAtTarget`                                                  | names the purpose, not the two stores                               |
| `Area_ClearSceneFlag46AndResetMode`                                     | `Area_EndCutscene`                                                      | no flag number, no `And`                                            |
| `Battle_FindSelectableSlotForward`                                      | `Battle_TargetNext` (and `Battle_TargetPrev`)                           | the cursor moving to the next enemy; a family puts the object first |
| `UI_MessageOpenWindow`, `UI_MessageCloseWindow`, `UI_MessageDrawWindow` | `UI_MessageWindowOpen`, `UI_MessageWindowClose`, `UI_MessageWindowDraw` | three on one object sort as a family, under the subject's tag       |
| `g_ShopSelectStep`                                                      | `g_ShopSelectedItem`                                                    | the item, not a step of the code                                    |
| `unk_01`, `state_02`, `step_01` (task header)                           | `mode`, `step`, with `flags` at 0x00                                    | the era names for the first three bytes of every task record        |
| `Struct_801E3C40`, `Record3`                                            | `ShopStock`, `MasterSkill`, `EncounterTable`                            | a type is a game noun                                               |
| `tmp10`, `var_s0`, `new_var`, `value2`, `arg1`                          | `tpage`, `shade`, `row`, `target`                                       | a local says what it holds, in the SDK's or the game's word         |
| `draw_value` behind a `FAKE_REG`, one `delta` reused for three things   | `u16 tpage`; `r`, `g`, `b`                                              | a name never records how the match was reached; fix the type first  |
| `sprite_cell = cell` copies named after the argument                    | the argument itself, or the role the copy plays                         | a copy that exists only for the allocator carries a `FAKE:` note    |
| `0x17`, `STEP_23`, `FLAG_0x40`                                          | `FISHING_STEP_REEL`, `ACTOR_HIDDEN`                                     | a constant is its meaning to the callers, never its value           |

The right column shows the form, not facts: every name still needs its evidence (step 3). When the
evidence shows only the mechanics, use the plainest game verb from the
[verb table](../../../../docs/naming.md#functions) (`Effect_CountDown`, `Actor_Move`). When it
shows nothing, keep the address name: a mechanical name is worse than none, because it looks
finished. A mechanical name already in the tree is a rename candidate; list it as
`needs: name <old> <proposed> <evidence>` when you touch its file.

Report: `named` (old, new, the users that prove it) or `kept` (the address name and the fact that
would promote it: `needs: name <ADDR> <fact>`).

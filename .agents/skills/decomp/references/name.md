# Name from meaning

Input: the symbols. A name comes from what the thing means in the game, found through its users.
Rules: [names](../../../../docs/conventions.md#names).

1. Find every user across all images ([users of a symbol](../../../../docs/toolchain.md#every-user-of-a-symbol)).
   `tools/symbol.py refs <dir>` ranks the address-named units by use; `tools/dups.py shared-names`
   and `split-names` list names that cover several bodies.
2. Read what the users do: loop bounds, strides, compares, copies, calls to functions that already
   have names. Search `rg -n 'NAME|0xADDR' config include src` for an existing name.
3. Rank the evidence ([order](../../../../docs/conventions.md#evidence)): disc labels, retail text and
   data, reference notes, visible code behavior. A count, an offset match, a type or a tool's output
   is not evidence.
4. Pick the form: [register](../../../../docs/conventions.md#register), [prefix](../../../../docs/conventions.md#tags),
   [verb](../../../../docs/conventions.md#functions), [selector](../../../../docs/conventions.md#variables-parameters-and-members),
   [table](../../../../docs/conventions.md#tables). Adjacent symbols read through one base are one record:
   name the record once, then its members by role.
5. Record the evidence where the name lives: the `config/symbols.toml` row's `source`, or a short comment beside
   a member, type or constant. Rename every tracked user in one commit with
   `tools/symbol.py rename` ([recipe](../../../../docs/conventions.md#rename-steps)); it writes the row. A function name goes to every copy with
   equal bytes ([shared bodies](../../../../docs/conventions.md#shared-bodies)); a parameter name goes to
   the definition and every prototype.

Unknown keeps the address name (`func_<ADDR>`, `D_<ADDR>`, `unk_<OFF>`).

## Natural names

Name the thing the way a game programmer of 1997 would type it in their own source: short, plain
game words, the purpose rather than the instructions. Before you keep a name, test it:

- It says what the thing is for in the game: what the player or the engine sees.
- It has at most three words after the tag (`Effect_FollowTarget`, not `Effect_CopyBattlerCoordsSetTimers`).
- Its word order follows [the two orders](../../../../docs/conventions.md#functions): verb first, object
  first for a family of three or more (`Message_WindowOpen`, `Message_WindowClose`).
- It has no `And` and no step list. A function that does two things is named for why it does them.
- It has no storage words: no field names, offsets, flag numbers, widths, `Slot0`, `ByTwo`, `Byte`, `Word`.
- A colleague could guess it before reading the body: `Party_AddItem`, `Battle_EndTurn`, `Shop_Buy`.

| Don't (mechanical)                                                | Do (natural), when the users show it                              | Why                                                                         |
| ----------------------------------------------------------------- | ----------------------------------------------------------------- | --------------------------------------------------------------------------- |
| `Effect_CopyBattlerCoordsSetTimers`                               | `Effect_StartAtTarget`                                            | names the purpose, not the two stores                                       |
| `Effect_CountDownTimerRaiseTicker`                                | `Effect_Wait`                                                     | a countdown that then advances is a wait                                    |
| `Effect_NextStepWhileTickUnderTwo`                                | `Effect_Pause`                                                    | no condition spelled out in the name                                        |
| `Effect_MarkTargetDamagedOnTickerZero`                            | `Effect_Hit`                                                      | the moment the spell lands                                                  |
| `Area_ClearSceneFlag46AndResetMode`                               | `Area_EndCutscene`                                                | no flag number, no `And`                                                    |
| `Area_ResumeScriptAndStopInteraction`                             | `Area_CloseTalk`                                                  | what the player sees                                                        |
| `Battle_FindSelectableSlotForward`                                | `Battle_TargetNext` (and `Battle_TargetPrev`)                     | the cursor moving to the next enemy; a family puts the object first         |
| `Message_OpenWindow`, `Message_CloseWindow`, `Message_DrawWindow` | `Message_WindowOpen`, `Message_WindowClose`, `Message_WindowDraw` | three on one object sort as a family, under the subject's tag               |
| `g_ShopSelectStep`                                                | `g_ShopSelectedItem`                                              | the item, not a step of the code                                            |
| `Scene_SetPartyRyuAdultNinaAdultRei`                              | `Scene_SetPartyRyuNinaRei`                                        | the member list is the fact; ages only when two versions exist in one scene |
| `Boss_EndBattleClearSlot0Flag`                                    | `Boss_Defeat`                                                     | a storage detail is not a meaning                                           |
| `g_ShopItemCountMax`                                              | `g_ShopBuyLimit`                                                  | the rule the player meets                                                   |
| `menu_state_byte_5`, `tmp2`, `val`                                | `cursor`, `page`, `count`, `price`                                | short game words for locals and members                                     |
| `Struct_801E3C40`, `Record3`                                      | `ShopStock`, `MasterSkill`, `EncounterTable`                      | a type is a game noun                                                       |

The right column shows the form, not facts: every name still needs its evidence (step 3). When the
evidence shows only the mechanics, use the plainest game verb from the
[verb table](../../../../docs/conventions.md#functions) (`Effect_CountDown`, `Actor_Move`). When it
shows nothing, keep the address name: a mechanical name is worse than none, because it looks
finished. A mechanical name already in the tree is a rename candidate; list it as
`needs: name <old> <proposed> <evidence>` when you touch its file.

Report: `named` (old, new, the users that prove it) or `kept` (the address name and the fact that
would promote it: `needs: name <ADDR> <fact>`).

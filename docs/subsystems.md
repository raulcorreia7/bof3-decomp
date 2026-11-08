# Subsystems

Which part of `src/` does which job, which records and headers it owns, and how much readability debt it holds. The path rules are in [conventions: files and headers](conventions.md#files-and-headers). The metrics are defined in [tools: quality](../tools/README.md#quality).

## Map

Every `src/` directory belongs to one row. A `Name.h` shared body sits at the folder named in its row.

| Subsystem        | `src/` directories                                           | Main records                                                                                                     | Headers that declare them                                                                                        | Shared helpers                                            |
| ---------------- | ------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------- |
| Executable       | `engine/slus`                                                | `ScratchPad`, `CallbackSlot`, `EMILoaderState`, `InterruptHooks`, `GameRequest`, `Actor`                         | `sys/*.h`, `slus/*.h`, `work/actor.h`, `engine/slus/slus.h`                                                      | `common/util.h`, `common/vector.h`, `psx/*.h`, `psyq/*.h` |
| Game tables      | `engine/game`                                                | `Character`, `Enemy`, `Encounter`, `Item`, `Ability`, `Gene`, `Fairy`, `ActorSlot`, `PaletteFade`, `TextCommand` | `game/*.h`, `game.h`                                                                                             | the executable's helpers                                  |
| Logo             | `logo`                                                       | none of its own                                                                                                  | `logo/logo.h`, `sys/*.h`                                                                                         | `psx/*.h`, `psyq/*.h`                                     |
| Shared bodies    | `shared`                                                     | none                                                                                                             | the `Name.h` bodies themselves, `shared/etc.h`                                                                   | used by two or more overlay groups                        |
| Area             | `overlays/area` (`area<NNN>/<slot>`)                         | `AreaActorDef`, `AreaMapBundle`, `AreaLoad`, `AreaVertex`, `AreaTrail`, `WorldMapMarker`, `Fishing*`             | `world/area.h`, `area/map.h`, `area/fishing.h`, `work/area_spad.h`, `overlays/area/area.h`, `area<NNN>_<slot>.h` | `overlays/area/Actor_*.h`, `Area_*.h`                     |
| Battle           | `overlays/battle` (`battle`, `batl_end`, `batl_ovr`)         | `BattleWork`, `BattleEffect`, `EnemyBattler`, `BattlePanel`, `BattleSelection`, `BattleStatBlock`, `BattleDrops`      | `battle/records.h`, `battle/ram.h`, `battle/handlers.h`, `overlays/battle/battle.h`, `battle_<slot>.h`           | `Battle_*.h` in the image folders                         |
| Battle magic     | `overlays/bmagic` (`magic<NNN>`, `func_*`)                   | `MagicModule`, `BMagicEffectWork`, `TrailPoint`, `BattleHandlerTable6`                                           | `battle/bmagic.h`, `battle/handlers.h`, `overlays/bmagic/bmagic.h`                                               | `overlays/bmagic/Effect_*.h`, `BMagic_*.h`                |
| Boss             | `overlays/boss` (`boss<NNN>`)                                | `BossModule`, `Boss054Funcs`, `Boss055Scripts`                                                                   | `overlays/boss/boss.h`, `battle/records.h`, `boss<NNN>_<slot>.h`                                                 | `overlays/boss/Boss_*.h`                                  |
| Fairy Village    | `overlays/commu` (`commu00` to `commu05`)                    | `FairyVillageData`, `FairyVariant`, `Fairy`, `FairyGift`                                                         | `game/fairy.h`, `commu00_00.h`                                                                                   | `overlays/commu/Commu_*.h`, `Fairy_*.h`                   |
| Menu             | `overlays/menu` (`bate`, `shisu`, `shop`, `sisyou`, `start`) | `MenuPanelTask`, `MenuChoicePanel`, `MenuListRow`, `MenuListPanel`, `SaveFile`, `GameClock`, `MasterSkill`       | `menu/*.h`, `bate_00.h`, `shop_00.h`, `sisyou_00.h`, `start_<slot>.h`                                            | `overlays/menu/Menu_*.h`, `Char_*.h`, `Item_*.h`          |
| Player character | `overlays/plchar`                                            | `Actor`, `ActorFlags`, `ActorRange`                                                                              | `work/actor.h`, `overlays/plchar/plchar.h`                                                                       | `overlays/plchar/Char_*.h`                                |
| Scenario         | `overlays/scenario` (`scena<NN>`, `sce<NN>ef<N>`)            | `SceneState`, `PartyState`, `SceneRequest`, `SceneEffect`, `SceneOverlayHeader`                                  | `work/state.h`, `scenario/*.h`, `overlays/scenario/scenario.h`, `scena<NN>_<slot>.h`                             | `overlays/scenario/Scene_*.h`                             |
| Title            | `overlays/title` (`game`)                                    | `InputFlags`, `GameUIBannerState`                                                                                | `game_01.h`, `sys/gameui.h`                                                                                      | the executable's helpers                                  |

## Debt

The table is generated by `tools/quality.py --markdown --update`, which a scheduled GitHub Action runs daily and sends as the pull request `chore/subsystems-table`. Do not edit it in a feature pull request; `pre-push` writes the current table to `build/subsystems.md` instead. `addr` counts matched functions still named `func_<ADDR>`; `names` counts `D_` and `unk_` tokens and `FIELD(...)` offset accesses in matched bodies.

<!-- quality:begin (tools/quality.py --markdown) -->

| Subsystem        | Matched functions | `addr` | `names` | `casts` | `harmful` | `twins` | `pasted` |
| ---------------- | ----------------: | -----: | ------: | ------: | --------: | ------: | -------: |
| Executable       |               450 |    135 |    1765 |     190 |        45 |       0 |        0 |
| Game tables      |               643 |    570 |    2012 |     153 |        50 |       0 |        0 |
| Logo             |                11 |      0 |      54 |       0 |         0 |       0 |        0 |
| Shared bodies    |                20 |      0 |      18 |       0 |         0 |       0 |        0 |
| Area             |              2315 |   2185 |    3004 |     177 |        31 |      21 |        0 |
| Battle           |               898 |    849 |    2165 |     206 |        81 |       0 |        0 |
| Battle magic     |              1084 |    965 |    2394 |      10 |         0 |       8 |        0 |
| Boss             |               654 |    518 |     574 |       6 |         0 |       4 |        0 |
| Fairy Village    |               151 |    140 |     473 |      17 |         3 |       0 |        0 |
| Menu             |               648 |    575 |    2281 |      58 |        18 |       0 |        0 |
| Player character |               263 |    188 |     260 |       0 |         5 |       0 |        0 |
| Scenario         |               833 |    783 |     889 |      16 |         4 |       6 |        0 |
| Title            |                20 |      0 |      12 |       3 |         0 |       0 |        0 |
| Total            |              7990 |   6908 |   15901 |     836 |       237 |      39 |        0 |

<!-- quality:end -->

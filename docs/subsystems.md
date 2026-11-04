# Subsystems

Which part of `src/` does which job, which records and headers it owns, and how much readability debt it holds. The path rules are in [conventions: files and headers](conventions.md#files-and-headers). The metrics are defined in [tools: quality](../tools/README.md#quality).

## Map

Every `src/` directory belongs to one row. A `Name.h` shared body sits at the folder named in its row.

| Subsystem        | `src/` directories                                           | Main records                                                                                                     | Headers that declare them                                                                                        | Shared helpers                                            |
| ---------------- | ------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------- |
| Executable       | `engine/slus`                                                | `ScratchPad`, `CallbackSlot`, `EmiLoaderState`, `InterruptHooks`, `GameRequest`, `Actor`                         | `sys/*.h`, `slus/*.h`, `work/actor.h`, `engine/slus/slus.h`                                                      | `common/util.h`, `common/vector.h`, `psx/*.h`, `psyq/*.h` |
| Game tables      | `engine/game`                                                | `Character`, `Enemy`, `Encounter`, `Item`, `Ability`, `Gene`, `Fairy`, `ActorSlot`, `PaletteFade`, `TextCommand` | `game/*.h`, `game.h`                                                                                             | the executable's helpers                                  |
| Logo             | `logo`                                                       | none of its own                                                                                                  | `logo/logo.h`, `sys/*.h`                                                                                         | `psx/*.h`, `psyq/*.h`                                     |
| Shared bodies    | `shared`                                                     | none                                                                                                             | the `Name.h` bodies themselves, `shared/etc.h`                                                                   | used by two or more overlay groups                        |
| Area             | `overlays/area` (`area<NNN>/<slot>`)                         | `AreaActorDef`, `AreaMapBundle`, `AreaLoad`, `AreaVertex`, `AreaTrail`, `WorldMapMarker`, `Fishing*`             | `world/area.h`, `area/map.h`, `area/fishing.h`, `work/area_spad.h`, `overlays/area/area.h`, `area<NNN>_<slot>.h` | `overlays/area/Actor_*.h`, `Area_*.h`                     |
| Battle           | `overlays/battle` (`battle`, `batl_end`, `batl_ovr`)         | `BattleWork`, `BattleEffect`, `EnemyBattler`, `BattlePanel`, `BattleSelection`, `BattleStatBlock`, `Spoils`      | `battle/records.h`, `battle/ram.h`, `battle/handlers.h`, `overlays/battle/battle.h`, `battle_<slot>.h`           | `Battle_*.h` in the image folders                         |
| Battle magic     | `overlays/bmagic` (`magic<NNN>`, `func_*`)                   | `MagicModule`, `BmagicEffectWork`, `BmagicTrailPoint`, `BattleHandlerTable6`                                     | `battle/bmagic.h`, `battle/handlers.h`, `overlays/bmagic/bmagic.h`                                               | `overlays/bmagic/Effect_*.h`, `BMagic_*.h`                |
| Boss             | `overlays/boss` (`boss<NNN>`)                                | `BossModule`, `Boss054Funcs`, `Boss055Scripts`                                                                   | `overlays/boss/boss.h`, `battle/records.h`, `boss<NNN>_<slot>.h`                                                 | `overlays/boss/Boss_*.h`                                  |
| Fairy Village    | `overlays/commu` (`commu00` to `commu05`)                    | `FairyVillageData`, `FairyVariant`, `Fairy`, `FairyGift`                                                         | `game/fairy.h`, `commu00_00.h`                                                                                   | `overlays/commu/Commu_*.h`, `Fairy_*.h`                   |
| Menu             | `overlays/menu` (`bate`, `shisu`, `shop`, `sisyou`, `start`) | `MenuPanelTask`, `MenuChoicePanel`, `MenuListRow`, `ShopPanel`, `SaveFile`, `GameClock`, `MasterSkill`           | `menu/*.h`, `bate_00.h`, `shop_00.h`, `sisyou_00.h`, `start_<slot>.h`                                            | `overlays/menu/Menu_*.h`, `Char_*.h`, `Item_*.h`          |
| Player character | `overlays/plchar`                                            | `Actor`, `ActorFlags`, `ActorRange`                                                                              | `work/actor.h`, `overlays/plchar/plchar.h`                                                                       | `overlays/plchar/Char_*.h`                                |
| Scenario         | `overlays/scenario` (`scena<NN>`, `sce<NN>ef<N>`)            | `SceneState`, `PartyState`, `SceneRequest`, `SceneEffect`, `SceneOverlayHeader`                                  | `work/state.h`, `scenario/*.h`, `overlays/scenario/scenario.h`, `scena<NN>_<slot>.h`                             | `overlays/scenario/Scene_*.h`                             |
| Title            | `overlays/title` (`game`)                                    | `InputFlags`, `GameUIBannerState`                                                                                | `game_01.h`, `sys/gameui.h`                                                                                      | the executable's helpers                                  |

## Debt

Totals from `tools/quality.py` on main `7140282c7f`. Rerun it for the current numbers. `addr` counts matched functions still named `func_<ADDR>`; `names` counts `D_` and `unk_` tokens in matched bodies.

| Subsystem        | Matched functions | `addr` | `names` | `casts` | `harmful` | `twins` | `pasted` |
| ---------------- | ----------------: | -----: | ------: | ------: | --------: | ------: | -------: |
| Executable       |               450 |    138 |    2585 |     231 |        45 |       0 |        0 |
| Game tables      |               644 |    574 |    2614 |     175 |        52 |       0 |        0 |
| Logo             |                11 |      0 |      54 |       0 |         0 |       0 |        0 |
| Shared bodies    |                15 |      0 |      12 |       0 |         0 |       0 |        0 |
| Area             |              2132 |   2028 |    4041 |     512 |        34 |      83 |        0 |
| Battle           |               897 |    853 |    2657 |     335 |        82 |       1 |        0 |
| Battle magic     |               755 |    682 |    1702 |     117 |         0 |      61 |        0 |
| Boss             |               627 |    500 |     594 |       6 |         0 |       4 |        4 |
| Fairy Village    |               117 |    107 |     379 |      14 |         9 |       1 |        0 |
| Menu             |               637 |    567 |    2927 |     101 |        18 |       0 |        0 |
| Player character |               253 |    185 |     274 |      19 |         5 |       4 |        0 |
| Scenario         |               733 |    702 |     944 |      42 |        18 |      20 |        0 |
| Title            |                20 |      0 |      11 |       5 |         0 |       0 |        0 |
| Total            |              7291 |   6336 |   18794 |    1557 |       263 |     174 |        4 |

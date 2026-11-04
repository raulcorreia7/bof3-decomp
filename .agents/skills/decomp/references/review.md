# Review

Input: a diff or a range. `check` proves the bytes; this pass is for the reader. Rules:
[docs index](../../../../docs/README.md). Fix what the grant allows; a `needs:` line names the file
and line.

1. Set the diff: `D=$(git diff main...HEAD -- src include config)` (or the range).
2. Run the quality pass below on it, one row at a time, until every row is read.
3. List one finding per line: `file:line class fix`, then the count per class.

## Quality pass

| Check                  | Command                                                                                                  | Fix                                                                                                      |
| ---------------------- | -------------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| Declarations in a `.c` | `git diff main...HEAD -- 'src/**/*.c' \| rg '^\+(extern \|\w[\w *]+\()'`                                 | move to the owning header ([layout](../../../../docs/conventions.md#lowest-scope-wins))                  |
| Duplicate declaration  | `rg -n 'extern .*\bNAME\b' src include` for each new extern                                              | delete the copy; include the owner                                                                       |
| Views and aliases      | `rg '^\+#define \w+ +(func\|D)_[0-9A-F]{8}\b' <<<"$D"`; `rg '^\+.*\*\((u\|s)(8\|16\|32) ?\*\)&' <<<"$D"` | `config/symbols.toml` row with `source`; type the one declaration                                        |
| Cast calls and returns | `rg '^\+.*\(\(\w[\w ]*\(\*\)\(' <<<"$D"`; `rg '^\+.*\(\w+ ?\*+\) ?\w+\(' <<<"$D"`                        | fix the prototype's parameter or return type ([types](../../../../docs/conventions.md#types-and-values)) |
| Includes               | `git diff main...HEAD -- 'src/**/*.c' \| rg '^\+#include'`                                               | a `.c` includes only the headers for the names it uses                                                   |
| Raw retail addresses   | `rg '^\+.*\b0x(80\|1F80)[0-9A-Fa-f]{4,6}\b' <<<"$D"`                                                     | the named global ([values](../../../../docs/conventions.md#values))                                      |
| Mechanical names       | storage words, widths, offsets, counts or addresses in a new name                                        | [storage words](../../../../docs/conventions.md#storage-words), or keep the address name                 |
| Names without facts    | `rg '^\+\w+ = 0x' <<<"$D"`                                                                               | every row has a `source` that cites users                                                                |
| Fragments              | a new `.h` or macro that holds part of a function; `bin/coddog cluster <target>` on touched images       | one game name, whole body ([shared bodies](../../../../docs/conventions.md#shared-bodies))               |
| Accessor macros        | a new macro that reads or writes a typed global                                                          | member access (`g_PARTY_Members[i].hp`)                                                                  |
| Magic values           | new bare numbers in conditions, strides and stores                                                       | a named constant or flag when the users give one meaning                                                 |
| Aids                   | `rg '^\+.*(MATCH_REG\|MATCH_FAKE_PIN\|CLOBBER_\|MATCH_FAKE_OPAQUE)' <<<"$D"`                             | reorder, pointer local or a benign helper first; keep the `FAKE:` note                                   |
| Style                  | mixed declarations, `for` declarations, `_Bool`, anonymous unions, casts a typed declaration removes     | C89 ([language](../../../../docs/conventions.md#language-and-formatting))                                |
| Dead and stale         | stale comments, unused locals and includes near the change                                               | delete                                                                                                   |
| Format                 | `meson compile -C build/meson format-check`                                                              | `meson compile -C build/meson format`                                                                    |

A clean pass says so and names the range it read.

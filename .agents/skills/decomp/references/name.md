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

Report: `named` (old, new, the users that prove it) or `kept` (the address name and the fact that
would promote it: `needs: name <ADDR> <fact>`).

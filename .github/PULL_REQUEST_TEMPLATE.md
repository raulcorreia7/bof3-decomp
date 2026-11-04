<!-- Title: a conventional subject, such as `match(world02): spawn-slot bodies` or `refactor(battle): type the effect target`. -->

## Summary

<!-- One or two sentences: what this PR does in game terms. For a batch, one subsection per topic. -->

## Changes

- Matched: `TARGET@0xADDRESS` → `Name` (or the address name), one line each or a short list.
- Shared bodies: `Name` across <images>.
- Types and names: `old → new`, with the evidence (callers, reads, writes or constants).

## Left

<!-- Near matches and blockers: the row, the first differing instruction, the missing type or name. Write "none" if there are none. -->

## Checks

- `INCLUDE_ASM`: <before> → <after>
- [ ] `meson compile -C build/meson pre-push` passes.
- [ ] `meson compile -C build/meson check` reports 428 images match (needs a disc), or the change does not touch code.
- [ ] No game data, extracted assets, retail executables or SDK objects are included.

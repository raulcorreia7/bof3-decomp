# Reproduce wiki facts

The commands run from the repository root. `bof3` is the CLI that `tools/setup.sh` builds at
`build/rust/release/bof3`, or the binary named by `BOF3_CLI`. The `bof3 assets` commands need the
full build, which `tools/setup.sh` does not make:
`(cd tools/bof3-tools && cargo build --release -p rebof3 --features assets)`; run the binary at
`tools/bof3-tools/target/release/bof3`. `rizin` is 0.9.1 ([matching tools](toolchain.md#matching-tools)). `$DISC` is the extracted disc folder
(`build/disc`) and `$OUT` is a scratch folder. Each block reproduces the facts of one wiki page.
The tools are in [bof3-tools](https://github.com/raulcorreia7/bof3-tools/blob/main/docs/cli.md).

## Battle tables

Facts: [battle](https://raulcorreia7.github.io/bof3-wiki/data/battle.html).

```sh
bof3 emi list "$DISC/BIN/BATTLE/BATTLE.EMI"
bof3 emi extract -e "$DISC/BIN/BATTLE/BATTLE.EMI" -o $OUT/battle
# the 0x80096800 program carries the escape and difficulty bytes
rizin -q -a mips -b 32 -m 0x80096800 \
  -c 'pxb 6 @ 0x800B44F0; pxb 8 @ 0x800B50DC' $OUT/battle/15.bin
# the 0x801D0C00 program carries the drop chances and the dispatch tables
rizin -q -a mips -b 32 -m 0x801D0C00 \
  -c 'pxb 8 @ 0x801D0CB8; pxw 4 @ 0x801D0C04' $OUT/battle/3.bin
```

## Field area records

Facts: [field](https://raulcorreia7.github.io/bof3-wiki/data/field.html).

```sh
bof3 emi list "$DISC/BIN/WORLD00/AREA001.EMI"
bof3 emi extract -e "$DISC/BIN/WORLD00/AREA001.EMI" -o $OUT/area
bof3 assets encounters $OUT/area/10.bin -o $OUT/encounters.json
bof3 assets export terrain $OUT/area/12.bin -o $OUT/area.glb
bof3 assets export message $OUT/area/11.bin -o $OUT/messages.json
```

## Record tables

Facts: [records](https://raulcorreia7.github.io/bof3-wiki/data/records.html).

```sh
bof3 emi list "$DISC/BIN/ETC/GAME.EMI"
bof3 emi extract -e "$DISC/BIN/ETC/GAME.EMI" -o $OUT/game
bof3 assets tables $OUT/game/0.bin -o $OUT/tables
jq '.[0]' $OUT/tables/items.json
```

One extraction of the whole disc writes the same JSON with its hashes:

```sh
bof3 assets extract --only data-table -i "Breath of Fire III (USA).cue" -o $OUT/tables
```

## Write-back pipeline

Facts: [editor guide](https://raulcorreia7.github.io/bof3-wiki/guides/index.html).

```sh
bof3 emi extract BIN/ETC/GAME.EMI -o work/game -J      # entries + emi.json manifest
# edit or import one entry file, then:
bof3 assets import emi BIN/ETC/GAME.EMI --entry 0=work/new0.bin -o work/GAME.EMI
bof3 assets import disc game.cue --file BIN/ETC/GAME.EMI=work/GAME.EMI -o $OUT/patched
```

## Coverage

Facts: [coverage](https://raulcorreia7.github.io/bof3-wiki/appendix/coverage.html), [EMI](https://raulcorreia7.github.io/bof3-wiki/formats/emi.html).

```sh
bof3 assets coverage -i "<cue sheet>"   # round trips per kind
bof3 emi coverage -i $DISC/BIN          # which formats rebuild their own bytes
```

## Palette export

Facts: [graphics](https://raulcorreia7.github.io/bof3-wiki/formats/graphics.html).

```sh
bof3 emi extract -e "$DISC/BIN/WORLD00/AREA001.EMI" -o $OUT/area
bof3 assets export palette $OUT/area/8.bin -o $OUT/palette.json
jq '{words, rows_4bpp, rows_8bpp}' $OUT/palette.json
```

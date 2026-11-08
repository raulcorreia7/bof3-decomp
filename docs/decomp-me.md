# decomp.me

For a scratch on [decomp.me](https://decomp.me/), choose PlayStation and
`gcc2.7.2-psx`. Use these compiler flags:

```
-O2 -G0 -funsigned-char -msoft-float -gcoff -Wa,--aspsx-version=2.56,--expand-div
```

Define `MATCHING` and supply the required declarations
in the scratch context. The scenario `sce10eff/00` uses the additional flags
`-fno-cse-follow-jumps -fno-cse-skip-blocks`. `build/meson/emit/cflags.txt` holds the flags the
project build uses. A scratch is a comparison tool; `meson compile -C build/meson check` verifies the
project build.

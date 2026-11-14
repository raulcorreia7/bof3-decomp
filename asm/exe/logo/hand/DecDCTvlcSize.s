/* DecDCTvlcSize - handwritten original (PsyQ LIBPRESS vlc.o, 8 words).
 * for a size above 1 it stores twice the size into the word at 0x801D7544 and returns
 * the old word; otherwise it branches into func_801D7568, the next function. C89
 * cannot express the `addi` overflow trap on the size or that branch. The words
 * are the original image's (0x20 bytes).
 */
.globl DecDCTvlcSize
.type DecDCTvlcSize, @function
DecDCTvlcSize:
    /* 9D48 801D7548 1D80083C */  lui        $t0, 0x801D
    /* 9D4C 801D754C 44750825 */  addiu      $t0, $t0, 0x7544
    /* 9D50 801D7550 FFFF8120 */  addi       $at, $a0, -0x1
    /* 9D54 801D7554 04002018 */  .word      0x18200004 /* blez $at, 0x801D7568: out of range for gas */
    /* 9D58 801D7558 0000028D */   lw        $v0, 0x0($t0)
    /* 9D5C 801D755C 40080400 */  sll        $at, $a0, 1
    /* 9D60 801D7560 0800E003 */  jr         $ra
    /* 9D64 801D7564 000001AD */   sw        $at, 0x0($t0)

/* __SN_ENTRY_POINT - handwritten original (the PsyQ C runtime entry, 13 words).
 * runs with no stack frame: it clears the BSS, sets $gp and jumps (not calls) to
 * Logo_Main. C89 cannot express a function that sets $gp or ends in a tail jump
 * with no frame. The words are the original image's (0x34 bytes).
 */
.globl __SN_ENTRY_POINT
.type __SN_ENTRY_POINT, @function
__SN_ENTRY_POINT:
    /* F24 801CE724 1F80023C */  lui        $v0, 0x801F
    /* F28 801CE728 30B44224 */  addiu      $v0, $v0, -0x4BD0
    /* F2C 801CE72C 1F80033C */  lui        $v1, 0x801F
    /* F30 801CE730 C0CE6324 */  addiu      $v1, $v1, -0x3140
  .L801CE734:
    /* F34 801CE734 000040AC */  sw         $zero, 0x0($v0)
    /* F38 801CE738 04004224 */  addiu      $v0, $v0, 0x4
    /* F3C 801CE73C 2B084300 */  sltu       $at, $v0, $v1
    /* F40 801CE740 FCFF2014 */  bnez       $at, .L801CE734
    /* F44 801CE744 00000000 */   nop
    /* F48 801CE748 1F801C3C */  lui        $gp, 0x801F
    /* F4C 801CE74C 30B49C27 */  addiu      $gp, $gp, -0x4BD0
    /* F50 801CE750 7F3B0708 */  j          0x801CEDFC
    /* F54 801CE754 00000000 */   nop

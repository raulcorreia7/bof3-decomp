/* stup2 - handwritten original (PsyQ 2MBYTE.OBJ startup code, 9 words).
 * clears the BSS word by word, then falls through into stup1 at 0x8014AA30;
 * it has no epilogue. C89 cannot emit a function that ends by falling into the
 * next one. The words are the original image's (0x24 bytes).
 * The unit goes on with stup1 (hand-written: stack and heap setup) and stup0 (calls SYS_Main), also
 * in the original image: the segment row spans all three, 0xAC bytes in all.
 */
.globl stup2
.type stup2, @function
stup2:
    /* B4A0C 8014AA0C 1980023C */  lui        $v0, 0x8019
    /* B4A10 8014AA10 B8B24224 */  addiu      $v0, $v0, -0x4D48
    /* B4A14 8014AA14 1980033C */  lui        $v1, 0x8019
    /* B4A18 8014AA18 600C6324 */  addiu      $v1, $v1, 0xC60
  .L8014AA1C:
    /* B4A1C 8014AA1C 000040AC */  sw         $zero, 0x0($v0)
    /* B4A20 8014AA20 04004224 */  addiu      $v0, $v0, 0x4
    /* B4A24 8014AA24 2B084300 */  sltu       $at, $v0, $v1
    /* B4A28 8014AA28 FCFF2014 */  bnez       $at, .L8014AA1C
    /* B4A2C 8014AA2C 00000000 */   nop

.globl stup1
.type stup1, @function
stup1:
    /* B4A30 8014AA30 04000224 */  addiu      $v0, $zero, 0x4
    /* B4A34 8014AA34 00000000 */  nop
    /* B4A38 8014AA38 00000000 */  nop
    /* B4A3C 8014AA3C 00000000 */  nop
    /* B4A40 8014AA40 00000000 */  nop
    /* B4A44 8014AA44 1580043C */  lui        $a0, 0x8015
    /* B4A48 8014AA48 B8AA8424 */  addiu      $a0, $a0, -0x5548
    /* B4A4C 8014AA4C 21208200 */  addu       $a0, $a0, $v0
    /* B4A50 8014AA50 0000828C */  lw         $v0, 0x0($a0)
    /* B4A54 8014AA54 0080083C */  lui        $t0, 0x8000
    /* B4A58 8014AA58 25E84800 */  or         $sp, $v0, $t0
    /* B4A5C 8014AA5C 1980043C */  lui        $a0, 0x8019
    /* B4A60 8014AA60 600C8424 */  addiu      $a0, $a0, 0xC60
    /* B4A64 8014AA64 C0200400 */  sll        $a0, $a0, 3
    /* B4A68 8014AA68 C2200400 */  srl        $a0, $a0, 3
    /* B4A6C 8014AA6C 1880033C */  lui        $v1, 0x8018
    /* B4A70 8014AA70 E845638C */  lw         $v1, 0x45E8($v1)
    /* B4A74 8014AA74 00000000 */  nop
    /* B4A78 8014AA78 23284300 */  subu       $a1, $v0, $v1
    /* B4A7C 8014AA7C 2328A400 */  subu       $a1, $a1, $a0
    /* B4A80 8014AA80 25208800 */  or         $a0, $a0, $t0
    /* B4A84 8014AA84 1980013C */  lui        $at, 0x8019
    /* B4A88 8014AA88 B8B23FAC */  sw         $ra, -0x4D48($at)
    /* B4A8C 8014AA8C 19801C3C */  lui        $gp, (0x80190000 >> 16)
    /* B4A90 8014AA90 B4B29C27 */  addiu      $gp, $gp, -0x4D4C
    /* B4A94 8014AA94 21F0A003 */  addu       $fp, $sp, $zero
    /* B4A98 8014AA98 33FB050C */  jal        0x8017ECCC
    /* B4A9C 8014AA9C 04008420 */   addi      $a0, $a0, 0x4
    /* B4AA0 8014AAA0 19801F3C */  lui        $ra, 0x8019
    /* B4AA4 8014AAA4 B8B2FF8F */  lw         $ra, -0x4D48($ra)
    /* B4AA8 8014AAA8 00000000 */  nop


.globl stup0
.type stup0, @function
stup0:
    /* B4AAC 8014AAAC B22A050C */  jal        0x8014AAC8
    /* B4AB0 8014AAB0 00000000 */   nop
    /* B4AB4 8014AAB4 4D000000 */  break      0, 1

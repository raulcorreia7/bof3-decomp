/* func_80178764 - handwritten original (PsyQ libgte msc01.o, the return-zero tail of SquareRoot0).
 * SquareRoot0 branches here (beq at 0x801786FC) to return 0. It is no function of its
 * own, and GCC 2.7.2 writes `move $v0, $zero` for a zero return, not this
 * `addiu`. The words are the original image's (0x14 bytes, with the 3 pad nops).
 * The unit goes on with InvSquareRoot (libgte msc02.o), also in the original image: the
 * segment row spans both, 0x98 bytes in all.
 */
.globl func_80178764
.type func_80178764, @function
func_80178764:
    /* E2764 80178764 0800E003 */  jr         $ra
    /* E2768 80178768 00000224 */   addiu     $v0, $zero, 0x0
    /* E276C 8017876C 00000000 */  nop
    /* E2770 80178770 00000000 */  nop
    /* E2774 80178774 00000000 */  nop

.globl InvSquareRoot
.type InvSquareRoot, @function
InvSquareRoot:
    /* E2778 80178778 00F08448 */  mtc2       $a0, $30
    /* E277C 8017877C 00000000 */  nop
    /* E2780 80178780 00000000 */  nop
    /* E2784 80178784 00F80248 */  mfc2       $v0, $31
    /* E2788 80178788 20000124 */  addiu      $at, $zero, 0x20
    /* E278C 8017878C 1B004110 */  .word      0x1041001B /* beq        $v0, $at, 0x801787FC: out of range for gas */
    /* E2790 80178790 00000000 */   nop
    /* E2794 80178794 19004010 */  .word      0x10400019 /* beqz       $v0, 0x801787FC: out of range for gas */
    /* E2798 80178798 00000000 */   nop
    /* E279C 8017879C 01004830 */  andi       $t0, $v0, 0x1
    /* E27A0 801787A0 FEFF0A24 */  addiu      $t2, $zero, -0x2
    /* E27A4 801787A4 24504A00 */  and        $t2, $v0, $t2
    /* E27A8 801787A8 1F000924 */  addiu      $t1, $zero, 0x1F
    /* E27AC 801787AC 22482A01 */  sub        $t1, $t1, $t2
    /* E27B0 801787B0 43480900 */  sra        $t1, $t1, 1
    /* E27B4 801787B4 E8FF4B21 */  addi       $t3, $t2, -0x18
    /* E27B8 801787B8 03006005 */  bltz       $t3, .L801787C8
    /* E27BC 801787BC 00000000 */   nop
    /* E27C0 801787C0 04606401 */  sllv       $t4, $a0, $t3
    /* E27C4 801787C4 03000010 */  b          .L801787D4
  .L801787C8:
    /* E27C8 801787C8 18000B24 */   addiu     $t3, $zero, 0x18
    /* E27CC 801787CC 22586A01 */  sub        $t3, $t3, $t2
    /* E27D0 801787D0 07606401 */  srav       $t4, $a0, $t3
  .L801787D4:
    /* E27D4 801787D4 C0FF8C21 */  addi       $t4, $t4, -0x40
    /* E27D8 801787D8 40600C00 */  sll        $t4, $t4, 1
    /* E27DC 801787DC 18800D3C */  lui        $t5, 0x8018
    /* E27E0 801787E0 2168AC01 */  addu       $t5, $t5, $t4
    /* E27E4 801787E4 6C64AD85 */  lh         $t5, 0x646C($t5)
    /* E27E8 801787E8 0000C9AC */  sw         $t1, 0x0($a2)
    /* E27EC 801787EC 0000ADAC */  sw         $t5, 0x0($a1)
    /* E27F0 801787F0 01000224 */  addiu      $v0, $zero, 0x1
    /* E27F4 801787F4 0800E003 */  jr         $ra
    /* E27F8 801787F8 00000000 */   nop

/* UI_IconDrawCell - handwritten original (assembly-match, Main-approved).
 * handwritten sprite-quad emitter, called from the battle and shop overlays;
 * the body is included verbatim from the original image (0x2ec bytes).
 * SDK call targets (numeric, as in func_801642F4): SetDrawMode=0x8017C2D8,
 * SetPolyFT4=0x8017A9B8.
 */
.globl UI_IconDrawCell
.type UI_IconDrawCell, @function
UI_IconDrawCell:

    /* CE4D8 801644D8 B0FFBD27 */  addiu      $sp, $sp, -0x50
    /* CE4DC 801644DC 4800B6AF */  sw         $s6, 0x48($sp)
    /* CE4E0 801644E0 6000B693 */  lbu        $s6, 0x60($sp)
    /* CE4E4 801644E4 3400B1AF */  sw         $s1, 0x34($sp)
    /* CE4E8 801644E8 6400B193 */  lbu        $s1, 0x64($sp)
    /* CE4EC 801644EC 4000B4AF */  sw         $s4, 0x40($sp)
    /* CE4F0 801644F0 21A08000 */  addu       $s4, $a0, $zero
    /* CE4F4 801644F4 3800B2AF */  sw         $s2, 0x38($sp)
    /* CE4F8 801644F8 2190A000 */  addu       $s2, $a1, $zero
    /* CE4FC 801644FC 3C00B3AF */  sw         $s3, 0x3C($sp)
    /* CE500 80164500 2198C000 */  addu       $s3, $a2, $zero
    /* CE504 80164504 4400B5AF */  sw         $s5, 0x44($sp)
    /* CE508 80164508 4C00BFAF */  sw         $ra, 0x4C($sp)
    /* CE50C 8016450C 3000B0AF */  sw         $s0, 0x30($sp)
    /* CE510 80164510 1580053C */  lui        $a1, %hi(D_80149C78)
    /* CE514 80164514 789CA524 */  addiu      $a1, $a1, %lo(D_80149C78)
    /* CE518 80164518 0300A288 */  lwl        $v0, 0x3($a1)
    /* CE51C 8016451C 0000A298 */  lwr        $v0, 0x0($a1)
    /* CE520 80164520 0700A388 */  lwl        $v1, 0x7($a1)
    /* CE524 80164524 0400A398 */  lwr        $v1, 0x4($a1)
    /* CE528 80164528 0B00A488 */  lwl        $a0, 0xB($a1)
    /* CE52C 8016452C 0800A498 */  lwr        $a0, 0x8($a1)
    /* CE530 80164530 1B00A2AB */  swl        $v0, 0x1B($sp)
    /* CE534 80164534 1800A2BB */  swr        $v0, 0x18($sp)
    /* CE538 80164538 1F00A3AB */  swl        $v1, 0x1F($sp)
    /* CE53C 8016453C 1C00A3BB */  swr        $v1, 0x1C($sp)
    /* CE540 80164540 2300A4AB */  swl        $a0, 0x23($sp)
    /* CE544 80164544 2000A4BB */  swr        $a0, 0x20($sp)
    /* CE548 80164548 0F00A288 */  lwl        $v0, 0xF($a1)
    /* CE54C 8016454C 0C00A298 */  lwr        $v0, 0xC($a1)
    /* CE550 80164550 1300A388 */  lwl        $v1, 0x13($a1)
    /* CE554 80164554 1000A398 */  lwr        $v1, 0x10($a1)
    /* CE558 80164558 1400A480 */  lb         $a0, 0x14($a1)
    /* CE55C 8016455C 2700A2AB */  swl        $v0, 0x27($sp)
    /* CE560 80164560 2400A2BB */  swr        $v0, 0x24($sp)
    /* CE564 80164564 2B00A3AB */  swl        $v1, 0x2B($sp)
    /* CE568 80164568 2800A3BB */  swr        $v1, 0x28($sp)
    /* CE56C 8016456C 2C00A4A3 */  sb         $a0, 0x2C($sp)
    /* CE570 80164570 FF008232 */  andi       $v0, $s4, 0xFF
    /* CE574 80164574 0C00422C */  sltiu      $v0, $v0, 0xC
    /* CE578 80164578 0E004010 */  beqz       $v0, .L801645B4
    /* CE57C 8016457C 21A8E000 */   addu      $s5, $a3, $zero
    /* CE580 80164580 ADEC050C */  jal        0x8017B2B4
    /* CE584 80164584 00000000 */   nop
    /* CE588 80164588 01000324 */  addiu      $v1, $zero, 0x1
    /* CE58C 8016458C 03004310 */  beq        $v0, $v1, .L8016459C
    /* CE590 80164590 00000000 */   nop
    /* CE594 80164594 ADEC050C */  jal        0x8017B2B4
    /* CE598 80164598 00000000 */   nop
  .L8016459C:
    /* CE59C 8016459C 21280000 */  addu       $a1, $zero, $zero
    /* CE5A0 801645A0 21300000 */  addu       $a2, $zero, $zero
    /* CE5A4 801645A4 1480043C */  lui        $a0, %hi(D_8014598C)
    /* CE5A8 801645A8 8C59848C */  lw         $a0, %lo(D_8014598C)($a0)
    /* CE5AC 801645AC 7C910508 */  j          0x801645F0
    /* CE5B0 801645B0 0F000724 */   addiu     $a3, $zero, 0xF
  .L801645B4:
    /* CE5B4 801645B4 ADEC050C */  jal        0x8017B2B4
    /* CE5B8 801645B8 00000000 */   nop
    /* CE5BC 801645BC 01000324 */  addiu      $v1, $zero, 0x1
    /* CE5C0 801645C0 07004310 */  beq        $v0, $v1, .L801645E0
    /* CE5C4 801645C4 2E000724 */   addiu     $a3, $zero, 0x2E
    /* CE5C8 801645C8 ADEC050C */  jal        0x8017B2B4
    /* CE5CC 801645CC 00000000 */   nop
    /* CE5D0 801645D0 02000324 */  addiu      $v1, $zero, 0x2
    /* CE5D4 801645D4 02004314 */  bne        $v0, $v1, .L801645E0
    /* CE5D8 801645D8 1E000724 */   addiu     $a3, $zero, 0x1E
    /* CE5DC 801645DC 2E000724 */  addiu      $a3, $zero, 0x2E
  .L801645E0:
    /* CE5E0 801645E0 21280000 */  addu       $a1, $zero, $zero
    /* CE5E4 801645E4 1480043C */  lui        $a0, %hi(D_8014598C)
    /* CE5E8 801645E8 8C59848C */  lw         $a0, %lo(D_8014598C)($a0)
    /* CE5EC 801645EC 21300000 */  addu       $a2, $zero, $zero
  .L801645F0:
    /* CE5F0 801645F0 B6F0050C */  jal        0x8017C2D8
    /* CE5F4 801645F4 1000A0AF */   sw        $zero, 0x10($sp)
    /* CE5F8 801645F8 01000424 */  addiu      $a0, $zero, 0x1
    /* CE5FC 801645FC 6839050C */  jal        0x8014E5A0
    /* CE600 80164600 0C000524 */   addiu     $a1, $zero, 0xC
    /* CE604 80164604 1480103C */  lui        $s0, %hi(D_8014598C)
    /* CE608 80164608 8C59108E */  lw         $s0, %lo(D_8014598C)($s0)
    /* CE60C 8016460C 6EEA050C */  jal        0x8017A9B8
    /* CE610 80164610 21200002 */   addu      $a0, $s0, $zero
    /* CE614 80164614 FF00A232 */  andi       $v0, $s5, 0xFF
    /* CE618 80164618 21104202 */  addu       $v0, $s2, $v0
    /* CE61C 8016461C 2118D302 */  addu       $v1, $s6, $s3
    /* CE620 80164620 1A0003A6 */  sh         $v1, 0x1A($s0)
    /* CE624 80164624 220003A6 */  sh         $v1, 0x22($s0)
    /* CE628 80164628 FF008332 */  andi       $v1, $s4, 0xFF
    /* CE62C 8016462C 100002A6 */  sh         $v0, 0x10($s0)
    /* CE630 80164630 200002A6 */  sh         $v0, 0x20($s0)
    /* CE634 80164634 0C00622C */  sltiu      $v0, $v1, 0xC
    /* CE638 80164638 040011A2 */  sb         $s1, 0x4($s0)
    /* CE63C 8016463C 050011A2 */  sb         $s1, 0x5($s0)
    /* CE640 80164640 060011A2 */  sb         $s1, 0x6($s0)
    /* CE644 80164644 080012A6 */  sh         $s2, 0x8($s0)
    /* CE648 80164648 0A0013A6 */  sh         $s3, 0xA($s0)
    /* CE64C 8016464C 120013A6 */  sh         $s3, 0x12($s0)
    /* CE650 80164650 16004010 */  beqz       $v0, .L801646AC
    /* CE654 80164654 180012A6 */   sh        $s2, 0x18($s0)
    /* CE658 80164658 00110300 */  sll        $v0, $v1, 4
    /* CE65C 8016465C 38004424 */  addiu      $a0, $v0, 0x38
    /* CE660 80164660 E8000324 */  addiu      $v1, $zero, 0xE8
    /* CE664 80164664 48004224 */  addiu      $v0, $v0, 0x48
    /* CE668 80164668 0D0003A2 */  sb         $v1, 0xD($s0)
    /* CE66C 8016466C 150003A2 */  sb         $v1, 0x15($s0)
    /* CE670 80164670 F8000324 */  addiu      $v1, $zero, 0xF8
    /* CE674 80164674 0C0004A2 */  sb         $a0, 0xC($s0)
    /* CE678 80164678 140002A2 */  sb         $v0, 0x14($s0)
    /* CE67C 8016467C 1C0004A2 */  sb         $a0, 0x1C($s0)
    /* CE680 80164680 1D0003A2 */  sb         $v1, 0x1D($s0)
    /* CE684 80164684 240002A2 */  sb         $v0, 0x24($s0)
    /* CE688 80164688 ADEC050C */  jal        0x8017B2B4
    /* CE68C 8016468C 250003A2 */   sb        $v1, 0x25($s0)
    /* CE690 80164690 01000324 */  addiu      $v1, $zero, 0x1
    /* CE694 80164694 36004310 */  beq        $v0, $v1, .L80164770
    /* CE698 80164698 0F000224 */   addiu     $v0, $zero, 0xF
    /* CE69C 8016469C ADEC050C */  jal        0x8017B2B4
    /* CE6A0 801646A0 00000000 */   nop
    /* CE6A4 801646A4 DC910508 */  j          0x80164770
    /* CE6A8 801646A8 0F000224 */   addiu     $v0, $zero, 0xF
  .L801646AC:
    /* CE6AC 801646AC 1400622C */  sltiu      $v0, $v1, 0x14
    /* CE6B0 801646B0 19004010 */  beqz       $v0, .L80164718
    /* CE6B4 801646B4 F4FF6224 */   addiu     $v0, $v1, -0xC
    /* CE6B8 801646B8 00110200 */  sll        $v0, $v0, 4
    /* CE6BC 801646BC 78004424 */  addiu      $a0, $v0, 0x78
    /* CE6C0 801646C0 D0000324 */  addiu      $v1, $zero, 0xD0
    /* CE6C4 801646C4 88FF4224 */  addiu      $v0, $v0, -0x78
    /* CE6C8 801646C8 0D0003A2 */  sb         $v1, 0xD($s0)
    /* CE6CC 801646CC 150003A2 */  sb         $v1, 0x15($s0)
    /* CE6D0 801646D0 E0000324 */  addiu      $v1, $zero, 0xE0
    /* CE6D4 801646D4 0C0004A2 */  sb         $a0, 0xC($s0)
    /* CE6D8 801646D8 140002A2 */  sb         $v0, 0x14($s0)
    /* CE6DC 801646DC 1C0004A2 */  sb         $a0, 0x1C($s0)
    /* CE6E0 801646E0 1D0003A2 */  sb         $v1, 0x1D($s0)
    /* CE6E4 801646E4 240002A2 */  sb         $v0, 0x24($s0)
    /* CE6E8 801646E8 ADEC050C */  jal        0x8017B2B4
    /* CE6EC 801646EC 250003A2 */   sb        $v1, 0x25($s0)
    /* CE6F0 801646F0 01000324 */  addiu      $v1, $zero, 0x1
    /* CE6F4 801646F4 1E004310 */  beq        $v0, $v1, .L80164770
    /* CE6F8 801646F8 2E000224 */   addiu     $v0, $zero, 0x2E
    /* CE6FC 801646FC ADEC050C */  jal        0x8017B2B4
    /* CE700 80164700 00000000 */   nop
    /* CE704 80164704 02000324 */  addiu      $v1, $zero, 0x2
    /* CE708 80164708 19004310 */  beq        $v0, $v1, .L80164770
    /* CE70C 8016470C 2E000224 */   addiu     $v0, $zero, 0x2E
    /* CE710 80164710 DC910508 */  j          0x80164770
    /* CE714 80164714 1E000224 */   addiu     $v0, $zero, 0x1E
  .L80164718:
    /* CE718 80164718 A8000424 */  addiu      $a0, $zero, 0xA8
    /* CE71C 8016471C F0000224 */  addiu      $v0, $zero, 0xF0
    /* CE720 80164720 B7000324 */  addiu      $v1, $zero, 0xB7
    /* CE724 80164724 0D0002A2 */  sb         $v0, 0xD($s0)
    /* CE728 80164728 150002A2 */  sb         $v0, 0x15($s0)
    /* CE72C 8016472C FF000224 */  addiu      $v0, $zero, 0xFF
    /* CE730 80164730 0C0004A2 */  sb         $a0, 0xC($s0)
    /* CE734 80164734 140003A2 */  sb         $v1, 0x14($s0)
    /* CE738 80164738 1C0004A2 */  sb         $a0, 0x1C($s0)
    /* CE73C 8016473C 1D0002A2 */  sb         $v0, 0x1D($s0)
    /* CE740 80164740 240003A2 */  sb         $v1, 0x24($s0)
    /* CE744 80164744 ADEC050C */  jal        0x8017B2B4
    /* CE748 80164748 250002A2 */   sb        $v0, 0x25($s0)
    /* CE74C 8016474C 01000324 */  addiu      $v1, $zero, 0x1
    /* CE750 80164750 07004310 */  beq        $v0, $v1, .L80164770
    /* CE754 80164754 2E000224 */   addiu     $v0, $zero, 0x2E
    /* CE758 80164758 ADEC050C */  jal        0x8017B2B4
    /* CE75C 8016475C 00000000 */   nop
    /* CE760 80164760 02000324 */  addiu      $v1, $zero, 0x2
    /* CE764 80164764 02004314 */  bne        $v0, $v1, .L80164770
    /* CE768 80164768 1E000224 */   addiu     $v0, $zero, 0x1E
    /* CE76C 8016476C 2E000224 */  addiu      $v0, $zero, 0x2E
  .L80164770:
    /* CE770 80164770 160002A6 */  sh         $v0, 0x16($s0)
    /* CE774 80164774 01000424 */  addiu      $a0, $zero, 0x1
    /* CE778 80164778 FF008232 */  andi       $v0, $s4, 0xFF
    /* CE77C 8016477C 2110A203 */  addu       $v0, $sp, $v0
    /* CE780 80164780 18004290 */  lbu        $v0, 0x18($v0)
    /* CE784 80164784 28000524 */  addiu      $a1, $zero, 0x28
    /* CE788 80164788 3F004230 */  andi       $v0, $v0, 0x3F
    /* CE78C 8016478C 00784234 */  ori        $v0, $v0, 0x7800
    /* CE790 80164790 6839050C */  jal        0x8014E5A0
    /* CE794 80164794 0E0002A6 */   sh        $v0, 0xE($s0)
    /* CE798 80164798 4C00BF8F */  lw         $ra, 0x4C($sp)
    /* CE79C 8016479C 4800B68F */  lw         $s6, 0x48($sp)
    /* CE7A0 801647A0 4400B58F */  lw         $s5, 0x44($sp)
    /* CE7A4 801647A4 4000B48F */  lw         $s4, 0x40($sp)
    /* CE7A8 801647A8 3C00B38F */  lw         $s3, 0x3C($sp)
    /* CE7AC 801647AC 3800B28F */  lw         $s2, 0x38($sp)
    /* CE7B0 801647B0 3400B18F */  lw         $s1, 0x34($sp)
    /* CE7B4 801647B4 3000B08F */  lw         $s0, 0x30($sp)
    /* CE7B8 801647B8 5000BD27 */  addiu      $sp, $sp, 0x50
    /* CE7BC 801647BC 0800E003 */  jr         $ra
    /* CE7C0 801647C0 00000000 */   nop
.size UI_IconDrawCell, . - UI_IconDrawCell

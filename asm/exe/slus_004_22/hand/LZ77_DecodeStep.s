/* LZ77_DecodeStep - handwritten original (assembly-match, Main-approved).
 * Entry state: the decoder context base 0x800327A0 is pinned in $t0, $ra is
 * parked in $s6, s0-s7 are saved into the context, and the per-mode dispatch
 * is a `jr $t4` through the absolute case-address table at 0x801640C0.
 * C89 cannot express any of these constructs; the body is included verbatim
 * from the original image (154 instructions, 0x268 bytes).
 */
.globl LZ77_DecodeStep
.type LZ77_DecodeStep, @function
LZ77_DecodeStep:
    /* CE064 80164064 0380083C */  lui        $t0, (0x800327A0 >> 16)
    /* CE068 80164068 A0270835 */  ori        $t0, $t0, (0x800327A0 & 0xFFFF)
    /* CE06C 8016406C 00000B8D */  lw         $t3, 0x0($t0)
    /* CE070 80164070 200010AD */  sw         $s0, 0x20($t0)
    /* CE074 80164074 240011AD */  sw         $s1, 0x24($t0)
    /* CE078 80164078 280012AD */  sw         $s2, 0x28($t0)
    /* CE07C 8016407C 2C0013AD */  sw         $s3, 0x2C($t0)
    /* CE080 80164080 300014AD */  sw         $s4, 0x30($t0)
    /* CE084 80164084 340015AD */  sw         $s5, 0x34($t0)
    /* CE088 80164088 380016AD */  sw         $s6, 0x38($t0)
    /* CE08C 8016408C 3C0017AD */  sw         $s7, 0x3C($t0)
    /* CE090 80164090 1C00138D */  lw         $s3, 0x1C($t0)
    /* CE094 80164094 21B01F00 */  addu       $s6, $zero, $ra
    /* CE098 80164098 20001224 */  addiu      $s2, $zero, 0x20
    /* CE09C 8016409C 18000A8D */  lw         $t2, 0x18($t0)
    /* CE0A0 801640A0 10000C8D */  lw         $t4, 0x10($t0)
    /* CE0A4 801640A4 16800D3C */  lui        $t5, (0x801640C0 >> 16)
    /* CE0A8 801640A8 C040AD35 */  ori        $t5, $t5, (0x801640C0 & 0xFFFF)
    /* CE0AC 801640AC 21688D01 */  addu       $t5, $t4, $t5
    /* CE0B0 801640B0 0000AC8D */  lw         $t4, 0x0($t5)
    /* CE0B4 801640B4 00000000 */  nop
    /* CE0B8 801640B8 08008001 */  jr         $t4
    /* CE0BC 801640BC 00FF1124 */   addiu     $s1, $zero, -0x100
  /* jump table: five word targets selected by the jr $t4 above */
    /* CE0C0 801640C0 D4401680 */  .word      0x801640D4
    /* CE0C4 801640C4 48411680 */  .word      0x80164148
    /* CE0C8 801640C8 F8411680 */  .word      0x801641F8
    /* CE0CC 801640CC 30411680 */  .word      0x80164130
    /* CE0D0 801640D0 E0411680 */  .word      0x801641E0
    /* CE0D4 801640D4 0800098D */  lw         $t1, 0x8($t0)
    /* CE0D8 801640D8 00000B8D */  lw         $t3, 0x0($t0)
  .L801640DC:
    /* CE0DC 801640DC 00003491 */  lbu        $s4, 0x0($t1)
    /* CE0E0 801640E0 01002925 */  addiu      $t1, $t1, 0x1
    /* CE0E4 801640E4 10008D32 */  andi       $t5, $s4, 0x10
    /* CE0E8 801640E8 0A00A015 */  bnez       $t5, .L80164114
    /* CE0EC 801640EC 00000000 */   nop
    /* CE0F0 801640F0 19002A15 */  bne        $t1, $t2, .L80164158
    /* CE0F4 801640F4 00000000 */   nop
    /* CE0F8 801640F8 140014AD */  sw         $s4, 0x14($t0)
    /* CE0FC 801640FC B390050C */  jal        0x801642CC
    /* CE100 80164100 04000D24 */   addiu     $t5, $zero, 0x4
    /* CE104 80164104 10000DAD */  sw         $t5, 0x10($t0)
    /* CE108 80164108 00000BAD */  sw         $t3, 0x0($t0)
    /* CE10C 8016410C 0800E001 */  jr         $t7
    /* CE110 80164110 00000224 */   addiu     $v0, $zero, 0x0
  .L80164114:
    /* CE114 80164114 FF000C24 */  addiu      $t4, $zero, 0xFF
    /* CE118 80164118 3C008C16 */  bne        $s4, $t4, .L8016420C
    /* CE11C 8016411C 00000000 */   nop
    /* CE120 80164120 B490050C */  jal        0x801642D0
    /* CE124 80164124 2400118D */   lw        $s1, 0x24($t0)
    /* CE128 80164128 0800E001 */  jr         $t7
    /* CE12C 8016412C 0F000224 */   addiu     $v0, $zero, 0xF
    /* CE130 80164130 801F093C */  lui        $t1, (0x1F800000 >> 16)
    /* CE134 80164134 00002935 */  ori        $t1, $t1, (0x1F800000 & 0xFFFF)
    /* CE138 80164138 0800158D */  lw         $s5, 0x8($t0)
    /* CE13C 8016413C 00000B8D */  lw         $t3, 0x0($t0)
    /* CE140 80164140 69900508 */  j          0x801641A4
    /* CE144 80164144 0F001424 */   addiu     $s4, $zero, 0xF
    /* CE148 80164148 801F093C */  lui        $t1, (0x1F800000 >> 16)
    /* CE14C 8016414C 00002935 */  ori        $t1, $t1, (0x1F800000 & 0xFFFF)
    /* CE150 80164150 00000B8D */  lw         $t3, 0x0($t0)
    /* CE154 80164154 1400148D */  lw         $s4, 0x14($t0)
  .L80164158:
    /* CE158 80164158 00002D91 */  lbu        $t5, 0x0($t1)
    /* CE15C 8016415C E0008C32 */  andi       $t4, $s4, 0xE0
    /* CE160 80164160 25609101 */  or         $t4, $t4, $s1
    /* CE164 80164164 C0600C00 */  sll        $t4, $t4, 3
    /* CE168 80164168 25688D01 */  or         $t5, $t4, $t5
    /* CE16C 8016416C 21A86D01 */  addu       $s5, $t3, $t5
    /* CE170 80164170 0F009432 */  andi       $s4, $s4, 0xF
    /* CE174 80164174 0F008F2E */  sltiu      $t7, $s4, 0xF
    /* CE178 80164178 0D000F14 */  bne        $zero, $t7, .L801641B0
    /* CE17C 8016417C 01002925 */   addiu     $t1, $t1, 0x1
    /* CE180 80164180 08002A15 */  bne        $t1, $t2, .L801641A4
    /* CE184 80164184 00000000 */   nop
    /* CE188 80164188 080015AD */  sw         $s5, 0x8($t0)
    /* CE18C 8016418C B390050C */  jal        0x801642CC
    /* CE190 80164190 0C000D24 */   addiu     $t5, $zero, 0xC
    /* CE194 80164194 10000DAD */  sw         $t5, 0x10($t0)
    /* CE198 80164198 00000BAD */  sw         $t3, 0x0($t0)
    /* CE19C 8016419C 0800E001 */  jr         $t7
    /* CE1A0 801641A0 00000224 */   addiu     $v0, $zero, 0x0
  .L801641A4:
    /* CE1A4 801641A4 00002D91 */  lbu        $t5, 0x0($t1)
    /* CE1A8 801641A8 01002925 */  addiu      $t1, $t1, 0x1
    /* CE1AC 801641AC 21A0B401 */  addu       $s4, $t5, $s4
  .L801641B0:
    /* CE1B0 801641B0 BD90050C */  jal        0x801642F4
    /* CE1B4 801641B4 03009426 */   addiu     $s4, $s4, 0x3
    /* CE1B8 801641B8 C8FF2A15 */  bne        $t1, $t2, .L801640DC
    /* CE1BC 801641BC 00000000 */   nop
    /* CE1C0 801641C0 100000AD */  sw         $zero, 0x10($t0)
    /* CE1C4 801641C4 00000BAD */  sw         $t3, 0x0($t0)
    /* CE1C8 801641C8 B390050C */  jal        0x801642CC
    /* CE1CC 801641CC 801F093C */   lui       $t1, (0x1F800000 >> 16)
    /* CE1D0 801641D0 00002935 */  ori        $t1, $t1, 0x0
    /* CE1D4 801641D4 080009AD */  sw         $t1, 0x8($t0)
    /* CE1D8 801641D8 0800E001 */  jr         $t7
    /* CE1DC 801641DC 00000224 */   addiu     $v0, $zero, 0x0
    /* CE1E0 801641E0 801F093C */  lui        $t1, (0x1F800000 >> 16)
    /* CE1E4 801641E4 00002935 */  ori        $t1, $t1, (0x1F800000 & 0xFFFF)
    /* CE1E8 801641E8 01003525 */  addiu      $s5, $t1, 0x1
    /* CE1EC 801641EC 00000B8D */  lw         $t3, 0x0($t0)
    /* CE1F0 801641F0 91900508 */  j          0x80164244
    /* CE1F4 801641F4 10001424 */   addiu     $s4, $zero, 0x10
    /* CE1F8 801641F8 00000B8D */  lw         $t3, 0x0($t0)
    /* CE1FC 801641FC 1400148D */  lw         $s4, 0x14($t0)
    /* CE200 80164200 801F093C */  lui        $t1, (0x1F800000 >> 16)
    /* CE204 80164204 A4900508 */  j          0x80164290
    /* CE208 80164208 00002935 */   ori       $t1, $t1, (0x1F800000 & 0xFFFF)
  .L8016420C:
    /* CE20C 8016420C E0FF9436 */  ori        $s4, $s4, 0xFFE0
    /* CE210 80164210 FFFF943A */  xori       $s4, $s4, 0xFFFF
    /* CE214 80164214 01009426 */  addiu      $s4, $s4, 0x1
    /* CE218 80164218 F0FF8C26 */  addiu      $t4, $s4, -0x10
    /* CE21C 8016421C 0C008015 */  bnez       $t4, .L80164250
    /* CE220 80164220 00000000 */   nop
    /* CE224 80164224 07002A15 */  bne        $t1, $t2, .L80164244
    /* CE228 80164228 00000000 */   nop
    /* CE22C 8016422C B390050C */  jal        0x801642CC
    /* CE230 80164230 00000BAD */   sw        $t3, 0x0($t0)
    /* CE234 80164234 10000B24 */  addiu      $t3, $zero, 0x10
    /* CE238 80164238 10000BAD */  sw         $t3, 0x10($t0)
    /* CE23C 8016423C 0800E001 */  jr         $t7
    /* CE240 80164240 00000224 */   addiu     $v0, $zero, 0x0
  .L80164244:
    /* CE244 80164244 00002D91 */  lbu        $t5, 0x0($t1)
    /* CE248 80164248 01002925 */  addiu      $t1, $t1, 0x1
    /* CE24C 8016424C 21A08D02 */  addu       $s4, $s4, $t5
  .L80164250:
    /* CE250 80164250 21608902 */  addu       $t4, $s4, $t1
    /* CE254 80164254 23688A01 */  subu       $t5, $t4, $t2
    /* CE258 80164258 0D00A019 */  blez       $t5, .L80164290
    /* CE25C 8016425C 23608A01 */   subu      $t4, $t4, $t2
    /* CE260 80164260 14000CAD */  sw         $t4, 0x14($t0)
    /* CE264 80164264 23A04901 */  subu       $s4, $t2, $t1
    /* CE268 80164268 03004911 */  beq        $t2, $t1, .L80164278
    /* CE26C 8016426C 20A82001 */   add       $s5, $t1, $zero /* handwritten instruction */
    /* CE270 80164270 BD90050C */  jal        0x801642F4
    /* CE274 80164274 00000000 */   nop
  .L80164278:
    /* CE278 80164278 B390050C */  jal        0x801642CC
    /* CE27C 8016427C 08000C24 */   addiu     $t4, $zero, 0x8
    /* CE280 80164280 10000CAD */  sw         $t4, 0x10($t0)
    /* CE284 80164284 00000BAD */  sw         $t3, 0x0($t0)
    /* CE288 80164288 0800E001 */  jr         $t7
    /* CE28C 8016428C 00000224 */   addiu     $v0, $zero, 0x0
  .L80164290:
    /* CE290 80164290 BD90050C */  jal        0x801642F4
    /* CE294 80164294 20A82001 */   add       $s5, $t1, $zero /* handwritten instruction */
    /* CE298 80164298 21483401 */  addu       $t1, $t1, $s4
    /* CE29C 8016429C 04002A11 */  beq        $t1, $t2, .L801642B0
    /* CE2A0 801642A0 100000AD */   sw        $zero, 0x10($t0)
    /* CE2A4 801642A4 37900508 */  j          0x801640DC
    /* CE2A8 801642A8 00000000 */   nop
    /* CE2AC 801642AC 100000AD */  sw         $zero, 0x10($t0)
  .L801642B0:
    /* CE2B0 801642B0 00000BAD */  sw         $t3, 0x0($t0)
    /* CE2B4 801642B4 B390050C */  jal        0x801642CC
    /* CE2B8 801642B8 801F093C */   lui       $t1, (0x1F800000 >> 16)
    /* CE2BC 801642BC 00002935 */  ori        $t1, $t1, 0x0
    /* CE2C0 801642C0 080009AD */  sw         $t1, 0x8($t0)
    /* CE2C4 801642C4 0800E001 */  jr         $t7
    /* CE2C8 801642C8 00000224 */   addiu     $v0, $zero, 0x0
.size LZ77_DecodeStep, . - LZ77_DecodeStep

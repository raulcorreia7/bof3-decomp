/* LZ77_DecodeBegin - origin unresolved (included assembly, byte-preserving).
 * The bounded profile search found no exact C89 match and no machine evidence
 * of hand authorship, so this unit is not counted as asm-original; keep the
 * body verbatim from the original image (0x3c bytes) until C89 matches or
 * provenance supplies proof. The C89 model in LZ77_DecodeBegin.c is for a native build.
 */
.globl LZ77_DecodeBegin
.type LZ77_DecodeBegin, @function
LZ77_DecodeBegin:
    /* CE028 80164028 0380083C */  lui        $t0, (0x800327A0 >> 16)
    /* CE02C 8016402C A0270835 */  ori        $t0, $t0, (0x800327A0 & 0xFFFF)
    /* CE030 80164030 000004AD */  sw         $a0, 0x0($t0)
    /* CE034 80164034 801F093C */  lui        $t1, (0x1F800000 >> 16)
    /* CE038 80164038 00002935 */  ori        $t1, $t1, (0x1F800000 & 0xFFFF)
    /* CE03C 8016403C 06002A25 */  addiu      $t2, $t1, 0x6
    /* CE040 80164040 08000AAD */  sw         $t2, 0x8($t0)
    /* CE044 80164044 00042A25 */  addiu      $t2, $t1, 0x400
    /* CE048 80164048 18000AAD */  sw         $t2, 0x18($t0)
    /* CE04C 8016404C 16800A3C */  lui        $t2, (0x8016432C >> 16)
    /* CE050 80164050 2C434A35 */  ori        $t2, $t2, (0x8016432C & 0xFFFF)
    /* CE054 80164054 1C000AAD */  sw         $t2, 0x1C($t0)
    /* CE058 80164058 100000AD */  sw         $zero, 0x10($t0)
    /* CE05C 8016405C 0800E003 */  jr         $ra
    /* CE060 80164060 0C0000AD */   sw        $zero, 0xC($t0)
.size LZ77_DecodeBegin, . - LZ77_DecodeBegin

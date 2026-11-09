/* Resets the effect's local work record. One definition shared by the bmagic effect modules;
 * every change here must verify every member. */
/* func_801F0A28 (magic003), func_801EFDB0 (magic021), func_801F04F8 (magic053), func_801EFE9C (magic058),
   func_801F04F4 (magic059), func_801F0438 (magic076), func_801F0E24 (magic083), func_801F0620 (magic093),
   func_801EFD04 (magic123), func_801F088C (magic124), func_801F0588 (magic125), func_801F0564 (magic129),
   func_801EF964 (magic146), func_801F03CC (magic169), func_801EF850 (magic213), func_801EF998 (magic219),
   func_801F068C (magic220), func_801EFBDC (magic223), func_801F0338 (magic225), func_801F0BF0 (magic226) */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}

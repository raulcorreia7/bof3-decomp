/* Swap the bytes two pointers address. One definition shared by the shop and
 * start menu overlays; every change here must verify every member.
 */
/* func_801D7E08 (shop), func_801DF464 (shop), func_801E1BB8 (shop), func_801D4A30 (start), func_801D6668 (start), func_801D933C (start), func_801DAC08 (start) */
MATCH void Menu_SwapBytes(u8* first, u8* second) {
    u8 temp;

    MENU_SWAP_BYTES(first, second);
}

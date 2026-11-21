/* Remove Peco from the party and restage the party palettes. */
/* func_801FD558 (scena05), func_801FE30C (scena06), func_801FE334 (scena09), func_801FAE48 (scena11), func_801FD100
   (scena12) */
MATCH void Scene_RemovePeco(void) {
    Party_RemoveMember(CHAR_ID_PECO);
    Party_LoadPalettes();
}

/* Stores the message id the menu choice D_801490C7 selects in g_MessageRequest.
 * One definition shared by the world04 area request overlays: area176 through
 * area185 at 0x801F31FC and area175 at 0x801F3E50. Every change here must verify
 * every member address. */
MATCH void Message_SetAnswerMessage(void) {
    switch (D_801490C7) {
        case 0:
            g_MessageRequest = 0xFA;
            break;
        case 1:
            g_MessageRequest = 0xFB;
            break;
        case 2:
            g_MessageRequest = 0xFC;
            break;
        case 3:
            g_MessageRequest = 0xFD;
            break;
        case 4:
            g_MessageRequest = 0xF9;
            break;
    }
}

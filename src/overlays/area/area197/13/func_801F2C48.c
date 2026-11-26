#include "area197_13.h"

MATCH void func_801F2C48(void) {
    Pos3 from;
    Pos3 to;

    func_801F30E4();
    func_801F3474();

    from.x = TO_COORD(2);
    from.y = TO_COORD(119);
    from.z = TO_COORD(-256);
    to.x   = TO_COORD(5);
    to.y   = TO_COORD(119);
    to.z   = TO_COORD(512);
    func_801F3110(0, 32, &from, &to);
    func_801F34A0(0, 32, &from, &to);

    from.x = TO_COORD(5);
    from.y = TO_COORD(119);
    from.z = TO_COORD(-256);
    to.x   = TO_COORD(10);
    to.y   = TO_COORD(119);
    to.z   = TO_COORD(512);
    func_801F3110(32, 96, &from, &to);
    func_801F34A0(32, 96, &from, &to);

    from.x = TO_COORD(10);
    from.y = TO_COORD(119);
    from.z = TO_COORD(-256);
    to.x   = TO_COORD(13);
    to.y   = TO_COORD(119);
    to.z   = TO_COORD(512);
    func_801F3110(96, 128, &from, &to);
    func_801F34A0(96, 128, &from, &to);

    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 7));
    SELF(Actor)->header.step = 0;
    SELF(Actor)->header.mode++;
}

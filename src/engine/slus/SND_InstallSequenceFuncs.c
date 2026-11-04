#include "engine/slus/slus.h"

/* TODO
 */
MATCH void SND_InstallSequenceFuncs(void) {
    D_8018DB58 = (s32)_SsNoteOn;
    D_8018DB5C = (s32)_SsSetProgramChange;
    D_8018DB64 = (s32)_SsGetMetaEvent;
    D_8018DB60 = (s32)_SsSetPitchBend;
    D_8018DB68 = (s32)_SsSetControlChange;
    D_8018DB74 = (s32)_SsContMainVol;
    D_8018DB78 = (s32)_SsContPanpot;
    D_8018DB7C = (s32)_SsContDamper;
    D_8018DB80 = (s32)_SsContNrpn1;
    D_8018DB84 = (s32)_SsContNrpn2;
    D_8018DB88 = (s32)_SsContRpn1;
    D_8018DB8C = (s32)_SsContRpn2;
    D_8018DB6C = 0;
    D_8018DB90 = 0;
    D_8018DB94 = 0;
    D_8018DB70 = (s32)_SsContDataEntry;
    D_8018DB9C = 0;
    D_8018DBA0 = 0;
    D_8018DBA4 = 0;
    D_8018DBA8 = 0;
    D_8018DBAC = 0;
    D_8018DBB0 = 0;
    D_8018DBB4 = 0;
    D_8018DBB8 = 0;
    D_8018DBBC = 0;
    D_8018DBC0 = 0;
    D_8018DBC4 = 0;
    D_8018DBC8 = 0;
    D_8018DBCC = 0;
    D_8018DBD0 = 0;
    D_8018DBD4 = 0;
    D_8018DBD8 = 0;
    D_8018DBDC = 0;
    D_8018DBE0 = 0;
    D_8018DBE4 = 0;
    D_8018DBE8 = 0;
}

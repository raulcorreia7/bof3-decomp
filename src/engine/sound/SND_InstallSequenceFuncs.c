#include "engine/slus/slus.h"

/* fills the libsnd function table the sequence player dispatches through */
MATCH void SND_InstallSequenceFuncs(void) {
    SsFCALL.noteon                 = _SsNoteOn;
    SsFCALL.programchange          = _SsSetProgramChange;
    SsFCALL.metaevent              = _SsGetMetaEvent;
    SsFCALL.pitchbend              = _SsSetPitchBend;
    SsFCALL.control[CC_NUMBER]     = _SsSetControlChange;
    SsFCALL.control[CC_MAINVOL]    = _SsContMainVol;
    SsFCALL.control[CC_PANPOT]     = _SsContPanpot;
    SsFCALL.control[CC_DAMPER]     = _SsContDamper;
    SsFCALL.control[CC_NRPN1]      = _SsContNrpn1;
    SsFCALL.control[CC_NRPN2]      = _SsContNrpn2;
    SsFCALL.control[CC_RPN1]       = _SsContRpn1;
    SsFCALL.control[CC_RPN2]       = _SsContRpn2;
    SsFCALL.control[CC_BANKCHANGE] = 0;
    SsFCALL.control[CC_EXTERNAL]   = 0;
    SsFCALL.control[CC_RESETALL]   = 0;
    SsFCALL.control[CC_DATAENTRY]  = _SsContDataEntry;
    SsFCALL.ccentry[0]             = 0;
    SsFCALL.ccentry[1]             = 0;
    SsFCALL.ccentry[2]             = 0;
    SsFCALL.ccentry[3]             = 0;
    SsFCALL.ccentry[4]             = 0;
    SsFCALL.ccentry[5]             = 0;
    SsFCALL.ccentry[6]             = 0;
    SsFCALL.ccentry[7]             = 0;
    SsFCALL.ccentry[8]             = 0;
    SsFCALL.ccentry[9]             = 0;
    SsFCALL.ccentry[10]            = 0;
    SsFCALL.ccentry[11]            = 0;
    SsFCALL.ccentry[12]            = 0;
    SsFCALL.ccentry[13]            = 0;
    SsFCALL.ccentry[14]            = 0;
    SsFCALL.ccentry[15]            = 0;
    SsFCALL.ccentry[16]            = 0;
    SsFCALL.ccentry[17]            = 0;
    SsFCALL.ccentry[18]            = 0;
    SsFCALL.ccentry[19]            = 0;
}

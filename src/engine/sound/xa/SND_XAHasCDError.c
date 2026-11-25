#include "engine/slus/slus.h"

/* true when the drive status of the last command has the shell-open bit. */

MATCH bool SND_XAHasCDError(void) {
    if ((g_XACdResult[0] & CdlStatShellOpen) == 0)
        return false;
    return true;
}

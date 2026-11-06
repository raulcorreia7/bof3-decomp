#include "start_09.h"

/* Waits for the memory card to settle, then opens `name` on `port` and hands
 * the descriptor to func_801EFB44. Mode 0x200 reopens the file in mode 1.
 * Returns 0 on success (or when mode is 0) and -1 on failure.
 * K&R definition: the u8 port narrows at each use, as in retail. */
MATCH s32 CardAccessFile(port, name, mode, size, offset)
u8        port;
char*     name;
s32       mode;
s32       size;
s32       offset;
{
    u8  tries;
    u8  retry;
    u8  wait;
    s32 fd;

    tries            = 30;
    retry            = 60;
    wait             = 60;
    fd               = 0;
    g_SaveCardStatus = CARD_EVENT_PENDING;
    do {
        tries--;
        CardPollInfo();
        CardPollSoftwareEvents();
        if (tries == 0) {
            return -1;
        }
    } while ((g_SaveCardStatus == CARD_EVENT_PENDING) | (g_SaveCardStatus == CARD_EVENT_TIMEOUT));

    while (retry != 0) {
        switch (g_SaveCardStatus) {
            case CARD_EVENT_OK:
                CardPollLoad();
                if (g_SaveCardStatus != CARD_EVENT_OK) {
                    return -1;
                }
                if (mode == 0) {
                    return 0;
                }
                fd = CardOpenFile(port, name, mode);
                if (fd == -1) {
                    return -1;
                }
                if (mode == 0x200) {
                    close(fd);
                    fd = CardOpenFile(port, name, 1);
                    if (fd == -1) {
                        g_SaveCardStatus = CARD_EVENT_ERROR;
                        return -1;
                    }
                    CardTransferFile(fd, 1, size, offset);
                } else {
                    CardTransferFile(fd, mode, size, offset);
                }
                return 0;
            case CARD_EVENT_TIMEOUT:
                return -1;
            case CARD_EVENT_NEW:
                /* Retail clears the outer counter before the wait loop. */
                retry = 0;
                while (wait != 0) {
                    func_801EF148();
                    switch (g_SaveCardStatus) {
                        case CARD_EVENT_OK:
                            CardPollLoad();
                            if (g_SaveCardStatus != CARD_EVENT_OK) {
                                return -1;
                            }
                            if (mode == 0) {
                                return 0;
                            }
                            if (CardOpenFile(port, name, mode) == -1) {
                                return -1;
                            }
                            if (mode == 0x200) {
                                close(fd);
                                fd = CardOpenFile(port, name, 1);
                                if (fd != -1) {
                                    CardTransferFile(fd, 1, size, offset);
                                    return 0;
                                }
                                g_SaveCardStatus = CARD_EVENT_ERROR;
                                return -1;
                            } else {
                                CardTransferFile(fd, mode, size, offset);
                            }
                            return 0;
                        case CARD_EVENT_TIMEOUT:
                            return -1;
                    }
                    wait--;
                    if (wait == 0) {
                        return -1;
                    }
                }
                break;
        }
        retry--;
        if (retry == 0) {
            return -1;
        }
    }
    return 0;
}

/* Tests software-card events in order and returns the first active event. */
MATCH s32 func_801EEEC8(void) {
    for (;;) {
        if (TestEvent(g_SysCardSoftwareIoEvent) != 0) {
            return CARD_EVENT_OK;
        }
        if (TestEvent(g_SysCardSoftwareTimeoutEvent) != 0) {
            return CARD_EVENT_TIMEOUT;
        }
        if (TestEvent(g_SysCardSoftwareNewEvent) != 0) {
            return CARD_EVENT_NEW;
        }
        if (TestEvent(g_SysCardSoftwareErrorEvent) != 0) {
            return CARD_EVENT_ERROR;
        }
    }
}

/* Tests hardware-card events in order and returns the first active event. */
/* func_801EEF40 */
MATCH s32 CardTestHardwareEvents(void) { /* func_801EEF40 */
    for (;;) {
        if (TestEvent(g_SysCardHardwareIoEvent) != 0) {
            return CARD_EVENT_OK;
        }
        if (TestEvent(g_SysCardHardwareTimeoutEvent) != 0) {
            return CARD_EVENT_TIMEOUT;
        }
        if (TestEvent(g_SysCardHardwareErrorEvent) != 0) {
            return CARD_EVENT_ERROR;
        }
    }
}

/* Polls the four software-card event descriptors. */
/* func_801EEFA0 */
MATCH void CardPollSoftwareEvents(void) { /* func_801EEFA0 */
    TestEvent(g_SysCardSoftwareIoEvent);
    TestEvent(g_SysCardSoftwareTimeoutEvent);
    TestEvent(g_SysCardSoftwareNewEvent);
    TestEvent(g_SysCardSoftwareErrorEvent);
}

/* Polls the three hardware-card event descriptors. */
/* func_801EEFF8 */
MATCH void CardPollHardwareEvents(void) { /* func_801EEFF8 */
    TestEvent(g_SysCardHardwareIoEvent);
    TestEvent(g_SysCardHardwareTimeoutEvent);
    TestEvent(g_SysCardHardwareErrorEvent);
}

/* Polls card info for up to 60 frames and stores its event result. */
/* func_801EF040 */
MATCH void CardPollInfo(void) { /* func_801EF040 */
    s32 count;
    s32 status;

    count  = 0x3C;
    status = -1;
    do {
        if (_card_info(g_SaveCardPort * 0x10) != 0) {
            count            = 0;
            g_SaveCardStatus = func_801EEEC8();
        } else {
            g_SaveCardStatus = status;
            count -= 1;
        }
    } while (count & BYTE_MASK);
}

/* Retries card load for up to 60 frames and stores its event result. */
/* func_801EF0B4 */
MATCH void CardPollLoad(void) { /* func_801EF0B4 */
    s32 count;
    s32 status;

    count  = 0x3C;
    status = -1;
    do {
        if (_card_load(g_SaveCardPort * 0x10) != 0) {
            g_SaveCardStatus = func_801EEEC8();
            CardPollSoftwareEvents();
            count = (g_SaveCardStatus == CARD_EVENT_PENDING) ? (count - 1) : 0;
        } else {
            g_SaveCardStatus = CARD_EVENT_PENDING;
            count -= 1;
        }
    } while (count & BYTE_MASK);
}

/* Retries card clear for up to 60 frames and stores its event handle. */
MATCH void func_801EF148(void) {
    s32 count;
    s32 status;

    count = 0x3C;
    CardPollHardwareEvents();
    status = -1;
    do {
        if (_card_clear(g_SaveCardPort * 0x10) != 0) {
            count            = 0;
            g_SaveCardStatus = CardTestHardwareEvents();
        } else {
            g_SaveCardStatus = status;
            count -= 1;
        }
    } while (count & BYTE_MASK);
}

/* Clears the selected card and records its event result. */
/* func_801EF1C0 */
MATCH void CardIssueClear(void) { /* func_801EF1C0 */
    s32 result;

    if (_card_clear((*(s32*)&g_SaveCardPort) << 4) != 0) {
        result = func_801EEEC8();
    } else {
        result = CARD_EVENT_ERROR;
    }
    (*(s32*)&g_SaveCardStatus) = result;
}

/* Formats the save-module name for the selected card port. */
/* func_801EF200 */
MATCH s32 CardFormatDevice(void) { /* func_801EF200 */
    char name[16];

    if (g_SaveCardPort == 0) {
        memcpy(name, &D_801EEC04, 6);
    } else {
        memcpy(name, &D_801EEC0C, 6);
    }
    if (format(name) == 1) {
        return 0;
    }
    CardPollInfo();
    return -1;
}

/* Builds the save-frame header and copies blocks for the selected save kind. */

/* func_801EF27C */
MATCH void CardBuildFileHeader(s8 magic_lo, s8 magic_hi, char* kind_name) { /* func_801EF27C */
    u8  i;
    u8* save;

    D_800C1800 = 0x53;
    D_800C1801 = 0x43;
    D_800C1802 = magic_hi;
    D_800C1803 = magic_lo;
    i          = 0;
    save       = MEM_PTR(u8, SAVE_FRAME_ADDR);
    for (; i < 28; i++) {
        save[0x44 + i] = 0;
    }
    strcpy(MEM_PTR(char, SAVE_FRAME_ADDR + 4), kind_name);
    *MEM_PTR(SaveIconPalette, 0x800C1860) = *MEM_PTR(SaveIconPalette, D_801EFE68);
    switch (magic_hi & BYTE_MASK) {
        case 17:
            *MEM_PTR(SaveIconFrame, 0x800C1880) = *MEM_PTR(SaveIconFrame, D_801EFE68 + 0x2C);
            *MEM_PTR(SaveIconFrame, 0x800C1900) = *MEM_PTR(SaveIconFrame, D_801EFE94);
            *MEM_PTR(SaveIconFrame, 0x800C1980) = *MEM_PTR(SaveIconFrame, D_801EFE94);
            break;
        case 18:
            *MEM_PTR(SaveIconFrame, 0x800C1880) = *MEM_PTR(SaveIconFrame, D_801EFE68 + 0x2C);
            *MEM_PTR(SaveIconFrame, 0x800C1900) = *MEM_PTR(SaveIconFrame, D_801EFF54);
            *MEM_PTR(SaveIconFrame, 0x800C1980) = *MEM_PTR(SaveIconFrame, D_801EFF54);
            break;
        case 19:
            *MEM_PTR(SaveIconFrame, 0x800C1880) = *MEM_PTR(SaveIconFrame, D_801EFE68 + 0x2C);
            *MEM_PTR(SaveIconFrame, 0x800C1900) = *MEM_PTR(SaveIconFrame, D_801EFF54);
            *MEM_PTR(SaveIconFrame, 0x800C1980) = *MEM_PTR(SaveIconFrame, D_801F0014);
            break;
    }
}

/* Opens a card file with up to 120 retries; on failure, reports directory capacity. */
/* func_801EF96C */
MATCH s32 CardOpenFile(u8 port, char* name, s32 mode) { /* func_801EF96C */
    char path[0x20];
    s32  total;
    s32  retries;
    s32  fd;

    total = 0;
    if (mode == 0x200) {
        mode = (port << 16) | 0x200;
    }
    if (g_SaveCardPort == 0) {
        memcpy(path, &D_801EEC04, 6);
    } else {
        memcpy(path, &D_801EEC0C, 6);
    }
    strcat(path, name);
    retries = 0;
    do {
        fd = open(path, mode);
        if (fd != -1) {
            return fd;
        }
        VSync(1);
        retries++;
    } while ((retries & BYTE_MASK) < 120U);
    CardPollInfo();
    CardPollSoftwareEvents();
    if (g_SaveCardStatus != CARD_EVENT_OK) {
        g_SaveCardStatus = CARD_EVENT_TIMEOUT;
        return -1;
    }
    if (mode != ((port << 16) | 0x200)) {
        g_SaveCardStatus = CARD_EVENT_ERROR;
        return -1;
    }
    CardScanDirectory(D_801EEC14, 6);
    retries = 0;
    do {
        total += D_8018E990[retries & BYTE_MASK].size;
        if ((total + (port << 13)) > 0x1E000U) {
            g_SaveCardStatus = CARD_EVENT_CAPACITY;
        } else {
            g_SaveCardStatus = CARD_EVENT_ERROR;
        }
        retries++;
    } while ((retries & BYTE_MASK) < 15U);
    return -1;
}

/* Reads or writes a card file, retrying failed transfers for up to 60 frames. */
/* func_801EFB44 */
MATCH s32 CardTransferFile(s32 fd, s32 mode, s32 size, s32 offset) { /* func_801EFB44 */
    /* FAKE: pin the countdown to $s1. */
    MATCH_FAKE_PIN(s32, count, "s1");
    /* FAKE: pin the constant one to $s6. */
    MATCH_FAKE_PIN(s32, one, "s6");
    s32 frame;
    s32 minus_one;
    s32 remain;

    count = 0x3C;
    if (size & 0x7F) {
        size = (size & ~0x7F) + 0x80;
    }
    if (offset & 0x7F) {
        offset &= ~0x7F;
    }
    one       = 1;
    frame     = SAVE_FRAME_ADDR;
    minus_one = -1;

loop:
    if (mode != one) {
        if (mode == 2) {
            goto write_path; /* the mode 2 branch writes the frame */
        }
        remain = count & BYTE_MASK;
        goto check; /* an unknown mode reuses the counter test */
    }
read_path:
    lseek(fd, offset, 0);
    if (read(fd, (void*)(offset + frame), size) != minus_one) {
        close(fd);
        return 0;
    }
    goto retry; /* a failed read polls the card again */

write_path:
    lseek(fd, offset, 0);
    if (write(fd, (void*)(offset + frame), size) != minus_one) {
        close(fd);
        return 0;
    }
    goto retry; /* a failed write polls the card again */

retry:
    CardPollInfo();
    if (g_SaveCardStatus == one) {
        close(fd);
        return -1;
    }
    if ((count & BYTE_MASK) == 0) {
        close(fd);
        return -1;
    }
    count--;
    remain = count & BYTE_MASK;
check:
    if (remain == 0) {
        return 0;
    }
    goto loop; /* the countdown still has frames left */
}

/* Copies matching card-directory entries into the 15-slot table. */
/* func_801EFCA8 */
MATCH s32 CardScanDirectory(char* prefix, u8 length) { /* func_801EFCA8 */
    struct DIRENTRY dir;
    char            pattern[0x80];
    u8              i;
    u8              j;

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 20; j++) {
            D_8018E990[i].name[j] = 0;
        }
        D_8018E990[i].size = 0;
    }
    i = 0;
    if (g_SaveCardPort == 0) {
        memcpy(pattern, &D_801EEC1C, 7);
    } else {
        memcpy(pattern, &D_801EEC24, 7);
    }
    if (firstfile(pattern, &dir) == &dir) {
        do {
            if (strncmp(prefix, D_801EEC2C, 1) == 0 || strncmp(dir.name, prefix, length) == 0) {
                strcpy(D_8018E990[i].name, dir.name);
                D_8018E990[i].size = dir.size;
                i++;
            }
        } while (nextfile(&dir) == &dir);
    }
    return i;
}

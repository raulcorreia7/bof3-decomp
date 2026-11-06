#ifndef SYSTEM_CD_H
#define SYSTEM_CD_H

#include "cd_format.h"
#include "sys/emi.h"
#include "types.h"

/* The main executable's CD and EMI loader runtime: the per-entry loader
 * records, the transfer state, and the step counter that advances one entry.
 * The disc file list layout it reads (DiscLba, the slot ids and the family
 * bases) is the format header cd_format.h. */

/* retail addresses */

/* Both callback initialization and cursor wrap use 24 slots (EMI_LdrStreamInitSlot, EMI_LdrServiceStream). */
#define EMI_CALLBACK_SLOT_COUNT 24

/* The loader's step counter, a word in the bank mapped at 0x80140000 (EMI_LdrLoadVabBody, EMI_LdrLoadVabCues,
 * EMI_LdrLoadSequence). */
#define EMI_LOADER_STEP         (*(volatile u32*)(D_80140000 + 0x646C))

typedef struct EmiActiveLoad {
    u32 active_lba;
    u32 remaining_size;
    u32 load_arg;
    u32 first_word;
    u16 type;
    u8  header_mode;
} EmiActiveLoad;

/* The EXE-side stream entry points are registry rows (EMI_Ldr*). */

/* D_80146468 */
extern volatile u32 g_EmiRequestedSlotId;

/* Disc/read-side helpers. */
void    func_8014FC00(s32 mode);
/* func_80161B24 */
void    SND_StartBgm(u8 bgm_id, u8 cue_level, u8 cue_shape);
/* Loads the archive of the requested BGM selection when it differs from the active one, then starts its cue. */
/* func_80161BBC */
s32     SND_RequestBgm(s32 requested);
/* func_80161F58 */
void    EMI_LoaderInit(void);
/* EXE-side stream entry points. */
/* func_80161FDC */
void    EMI_LoaderStreamInitSlot(u32 slot_id);
/* func_80162160 */
DiscLba EMI_LoaderSlotLba(EmiSlotId slot_id);
/* func_80162178 */
void    EMI_LoaderBeginRead(void);
/* func_801621E8 */
void    EMI_OnCDSync(s32 status, u8* result);
/* func_80162230 */
void    EMI_OnCDReady(u8 status, u8* result);
/* func_80162C14 */
void    EMI_LoaderCopySector(void);
/* func_80162CD8 */
void    EMI_LoaderEndStream(void);
/* func_80162D00 */
s32     EMI_LoaderIsReady(void);
/* func_80162D18 */
void    EMI_LoaderRunCD(void);
/* Starts the key-based CD request for one XA stream file; the key is the file kind in bits 12 and up and an
 * entry count below. Every caller also passes a second word that the loader never reads. */
/* func_801636A0 */
void    SND_StartXAStream(s32 key, s32 unused);
/* func_80163EA0 */
s32     SND_IsXAIdle(void);
/* Arms the loader for a character's family key (three party bytes plus the form flag) and waits for the stream. */
/* func_80166E88 */
void    EMI_LoaderStreamFamily(u8 member_a, u8 member_b, u8 member_c, u8 family);
/* func_8016728C */
void    EMI_StreamFamilyArchive(u8 index, u8 family);

#endif

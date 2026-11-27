#ifndef PSX_MEM_H
#define PSX_MEM_H

#include "types.h"

/* PS1 scratchpad RAM: 0x1F800000-0x1F8003FF. Offsets are byte offsets. */
#define SCRATCH_PAD                        0x1F800000u
#define SCRATCH_PAD_SIZE                   0x400u

/* Address conversion: no memory access occurs. Add const and volatile to the
 * type directly, e.g. MEM_PTR(const volatile u32, address). */
#define MEM_PTR(type, address)             ((type*)(address))

/* Direct object access: an lvalue for an object stored at an address.
 *
 *     MEM(u32, address) = value;
 *     value = MEM(volatile u16, address);
 */
#define MEM(type, address)                 (*MEM_PTR(type, address))

/* BIOS kernel RAM starts at physical address 0x100; offsets are byte offsets from 0x100. */
#define KERNEL_RAM(offset)                 MEM_PTR(u8, 0x00000100u + (u32)(offset))

/* Byte-offset field access while a structure is incomplete or its fields are
 * not yet named. Replace with real struct members once the layout is known.
 *
 *     FIELD_PTR(volatile u16, base, 0x80u)
 *     value = FIELD(u32, work, 0x18u)
 */
#define FIELD_PTR(type, base, byte_offset) MEM_PTR(type, (u8*)(base) + (u32)(byte_offset))
#define FIELD(type, base, byte_offset)     (*FIELD_PTR(type, base, byte_offset))

/* Scratchpad. SP(off) is the absolute address of a byte offset; SP_PTR is a
 * typed pointer to it (no read occurs); SP_REF is an lvalue.
 *
 *     SP_PTR(u8, 0x20u)
 *     SP_REF(u32, 0x20u) = value;
 *
 * Pointer cells: SP_REF(Entity *, 0x44u) is the `Entity *` stored at that
 * offset. It is intentionally NOT volatile: the constant-address codegen
 * (lui + offset load, e.g. `lw v1,68(v1)` for 0x1F800044) matches the original
 * binary, while a volatile cell forces `lui + ori + lw 0`. For a reload on
 * every evaluation, qualify the type (SP_REF(volatile Entity *, ...)) or use
 * MEM directly.
 *
 * A table of cells at the scratchpad base, indexed by cell number (a zero base
 * lets the compiler use an offset load rather than materialize an address):
 *
 *     SP_PTR(Entity *, 0u)[0x11]
 */
#define SP(byte_offset)                    (SCRATCH_PAD + (u32)(byte_offset))
#define SP_PTR(type, byte_offset)          MEM_PTR(type, SP(byte_offset))
#define SP_REF(type, byte_offset)          MEM(type, SP(byte_offset))

/* retail addresses */
/* The scratchpad cell at 0x1F800044: the record whose handler is running. The dispatcher sets it before each
 * handler (Actor_DispatchAll, Party_RunFrame, Battle_UpdateEffects); code that runs another record's handler
 * saves it first and restores it after. Its type follows the mode (Actor on the field, PartyMember for a
 * battler, the effect's own record in a spell effect, FishingState while fishing), so `struct Self` is
 * incomplete. Read SELF(Type)->member; set SELF_SET(record); save through a typed local or SELF(void); a
 * record with no type reads its bytes through the byte view below. A unit that must re-read the cell after
 * every store defines FAKE_DECL_SELF_VOLATILE before its first include. */
#ifdef FAKE_DECL_SELF_VOLATILE
/* D_1F800044 */
extern struct Self* volatile g_Self;
#else
/* D_1F800044 */
extern struct Self* g_Self;
#endif

/* The running record viewed as a Type record. */
#define SELF(type)       ((type*)g_Self)

/* The running record as raw bytes, for a record with no type. */
#define SELF_BYTES       ((u8*)g_Self)

/* Point the cell at a record of any type: the cell holds the record as an untyped pointer. */
#define SELF_SET(record) (g_Self = (void*)(record))

#endif

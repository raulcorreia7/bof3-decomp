#ifndef PSX_MEM_H
#define PSX_MEM_H

#include "types.h"

/* PS1 scratchpad RAM: 0x1F800000-0x1F8003FF. Offsets are byte offsets. */
#define SCRATCH_PAD                         0x1F800000u
#define SCRATCH_PAD_SIZE                    0x400u

/* Address conversion: no memory access occurs. Add const and volatile to the
 * type directly, e.g. MEM_PTR(const volatile u32, address). */
#define MEM_PTR(type, address)              ((type*)(address))

/* Direct object access: an lvalue for an object stored at an address.
 *
 *     MEM(u32, address) = value;
 *     value = MEM(volatile u16, address);
 */
#define MEM(type, address)                  (*MEM_PTR(type, address))

/* BIOS kernel RAM starts at physical address 0x100; offsets are byte offsets from 0x100. */
#define KERNEL_RAM(offset)                  MEM_PTR(u8, 0x00000100u + (u32)(offset))

/* Byte-offset field access while a structure is incomplete or its fields are
 * not yet named. Replace with real struct members once the layout is known.
 *
 *     FIELD_PTR(volatile u16, base, 0x80u)
 *     value = FIELD(u32, work, 0x18u)
 */
#define FIELD_PTR(type, base, byte_offset)  MEM_PTR(type, (u8*)(base) + (u32)(byte_offset))
#define FIELD(type, base, byte_offset)      (*FIELD_PTR(type, base, byte_offset))

/* Fixed-address function pointer. function_type is a function-pointer typedef:
 *
 *     typedef void (*Handler)(void);
 *     FUNCTION_AT(Handler, 0x80123456u)();
 */
#define FUNCTION_AT(function_type, address) ((function_type)(address))

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
#define SP(byte_offset)                     (SCRATCH_PAD + (u32)(byte_offset))
#define SP_PTR(type, byte_offset)           MEM_PTR(type, SP(byte_offset))
#define SP_REF(type, byte_offset)           MEM(type, SP(byte_offset))

/* retail addresses */
/* Scratchpad work pointer at 0x1F800044. Each mode reads it through its own pointee type: a header defines a
 * `g_Task` view macro, `((T *)g_Task)`, for its type. A unit that must re-read the cell
 * after every store defines TASK_VOLATILE before its first include. `struct Task` is incomplete: no
 * member is reachable without a view. TASK_BYTES is the byte view for a record with no type. */
#ifdef TASK_VOLATILE
/* D_1F800044 */
extern struct Task* volatile g_Task;
#else
/* D_1F800044 */
extern struct Task* g_Task;
#endif

#define TASK_BYTES       ((u8*)g_Task)

/* Point the cell at a record of any type: the cell holds the record as an untyped task pointer. */
#define TASK_SET(record) (g_Task = (void*)(record))

#endif

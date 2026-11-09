#ifndef PSX_MEM_H
#define PSX_MEM_H

#include "types.h"

/* PS1 scratchpad RAM: 0x1F800000-0x1F8003FF. */
#define SCRATCH_PAD                         0x1F800000u
#define SCRATCH_PAD_SIZE                    0x400u
#define SCRATCH_PAD_END                     0x1F8003FFu

/* Address conversion: no memory access occurs. */
#define MEM_PTR(type, address)              ((type*)(address))

/* Direct object access: an lvalue for an object stored at an address. */
#define MEM(type, address)                  (*MEM_PTR(type, address))

/* BIOS kernel RAM starts at physical address 0x100; offsets are byte offsets from 0x100. */
#define KERNEL_RAM(offset)                  MEM_PTR(u8, 0x00000100u + (u32)(offset))

/* Byte-offset field access while a structure is incomplete or its fields are not yet named. */
#define FIELD_PTR(type, base, byte_offset)  MEM_PTR(type, (u8*)(base) + (u32)(byte_offset))
#define FIELD(type, base, byte_offset)      (*FIELD_PTR(type, base, byte_offset))

/* Fixed-address function pointer. function_type is a function-pointer typedef. */
#define FUNCTION_AT(function_type, address) ((function_type)(address))

/* Scratchpad. */
#define SP(byte_offset)                     (SCRATCH_PAD + (u32)(byte_offset))
#define SP_PTR(type, byte_offset)           MEM_PTR(type, SP(byte_offset))
#define SP_REF(type, byte_offset)           MEM(type, SP(byte_offset))

/* retail addresses. */
/* Scratchpad work pointer at 0x1F800044. */
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

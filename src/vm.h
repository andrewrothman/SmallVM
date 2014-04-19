#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h> /* int32_t */

#include "opcodes.h"

#define REGISTER_COUNT 5 /* The number of registers */
#define MEMORY_WORD_COUNT 20 /* The number of memory words */

/* A word is just a 32 bit integer */
typedef int32_t word;

/* State struct */
typedef struct
{
    word *registers; /* CPU registers */
    word *memory;    /* RAM */
    word pc;         /* Program counter */
    int usedMemory;  /* A counter for the amount of memory used */
} vm_state;

vm_state *vm_new(void); /* Creates a new virtual machine state */
void vm_close(vm_state *state); /* Close a virtual machine instance */

void vm_execute(vm_state *state, word *instruction); /* Executes an instruction */
void vm_load(vm_state *state, word *instrs, int count); /* Loads instructions into memory */
void vm_run(vm_state *state); /* Runs from the begining of memory */
void vm_error(vm_state *state, char *message, ...); /* Cleans up after an error */

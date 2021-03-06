#ifndef OPCODES_H
#define OPCODES_H

#define OP_SET     0x01 /* Sets a register to a value or to the contents of another register */
#define OP_ADD     0x02 /* Adds two values or register contents */
#define OP_SUB     0x03 /* Subtracts two values or register contents */
#define OP_MULT    0x04 /* Multiplies two values or register contents */
#define OP_DIV     0x05 /* Divides two values or register contents */
#define OP_MOD     0x06 /* Mods two values or register contents */
#define OP_STORE   0x07 /* Stores a value into memory */
#define OP_GET     0x08 /* Get a value from memory */
#define OP_JMP     0x09 /* Jump to another location in memory */
#define OP_IF      0x0A /* Performs the next instruction if the values are equal */
#define OP_IFN     0x0B /* Performs the next instruction if the values are not equal */

#endif /* OPCODES_H */

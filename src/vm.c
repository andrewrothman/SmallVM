#include "vm.h"

vm_state *vm_new(void)
{
    /* Allocate space for vm */
    vm_state *state = (vm_state *) malloc(sizeof(vm_state));
    
    /* Allocate space for the registers and the RAM */
    state->registers = (word *) calloc(REGISTER_COUNT, sizeof(word));
    state->memory = (word *) calloc(MEMORY_WORD_COUNT, sizeof(word));
    state->pc = 0;
    
    /* Initialize anything else the virtual machine struct needs */
    state->usedMemory = 0;
    
    /* Make sure everything is allocated */
    if (!state || !state->registers || !state->memory)
        vm_error(state, "Not enough free memory");
    
    return state;
}

void vm_close(vm_state *state)
{
    int i;
    
    /* Print out the registers */
    
    printf("\nRegisters:\n");
    
    for (i = 0; i < REGISTER_COUNT; i++)
        printf("%c: %#x\n", 65 + i, state->registers[i]);
    
    /* Print out the contents of memory */
    
    printf("\nMemory:\n");
    
    for (i = 0; i < MEMORY_WORD_COUNT; i++)
    {
        word *current = &state->memory[i]; /* Get the word from memory */
        printf("%#x ", *current); /* Print it out in hex format */
    }
    
    printf("\n");
    
    /* Free any pointers in the struct */
    free(state->registers);
    free(state->memory);
    
    /* Free the memory taken up by the struct */
    free(state);
}

void vm_error(vm_state *state, char *message, ...)
{
    va_list args;
    
    fprintf(stderr, "ERROR: ");
    
    /* Print out formatted string and arguments */
    va_start(args, message);
    vfprintf(stderr, message, args);
    va_end(args);
    
    fprintf(stderr, "\n");
    
    /* Close the vm */
    vm_close(state);
    
    /* Exit with error code */
    exit(EXIT_FAILURE);
}

/* Get the value of either a register or a literal */
word *get_value(vm_state *state, word aWord, word *sink)
{
    if (aWord < 0x05) /* A register value */
    {
		if (aWord <= REGISTER_COUNT)
		{
        	return &state->registers[aWord]; /* Return the value of the register */
		}
		else
		{
			vm_error(state, "Register does not exist");
			return NULL;
		}
    }
    else /* A literal value */
    {
        *sink = aWord - 0x05; /* Fix offset and return the value */
        
        return sink;
    }
}

void vm_execute(vm_state *state, word *instruction)
{
    /* Opcode is the word right shifted */
    word opcode = *instruction >> 24;
    /* A argument is the word right shifted and masked */
    word a = (*instruction >> 12) & 2047;
    /* B argument is the word masked */
    word b = *instruction & 2047;
    
    word *valA; /* Declared here to satisfy ANSI C requirements */
    word *valB; /* Declared here to satisfy ANSI C requirements */
    
    /* Allocate memory for the sinks */
    word *sinkA = (word *) malloc(sizeof(word));
    word *sinkB = (word *) malloc(sizeof(word));
    
    /* check if the sinks were allocated */
    if (!sinkA || !sinkB)
        vm_error(state, "Not enough free memory");
    
    /* Get the values from the arguments */
    valA = get_value(state, a, sinkA);
    valB = get_value(state, b, sinkB);
    
    switch (opcode)
	{
        case OP_SET:
        {
            *valA = *valB;
            
            printf("SET %#x %#x\n", a, b);
            
            break;
        }
        case OP_ADD:
        {
            *valA = *valA + *valB;
            
            printf("ADD %#x %#x\n", *valA, *valB);
            
            break;
        }
        case OP_SUB:
        {
            *valA = *valA - *valB;
            
            printf("SUB %#x %#x\n", *valA, *valB);
            
            break;
        }
        case OP_MULT:
        {
            *valA = *valA * *valB;
            
            printf("MULT %#x %#x\n", *valA, *valB);
            
            break;
        }
        case OP_DIV:
        {
            *valA = *valA / *valB;
            
            printf("DIV %#x %#x\n", *valA, *valB);
            
            break;
        }
        case OP_MOD:
        {
            *valA = *valA % *valB;
            
            printf("MOD %#x %#x\n", *valA, *valB);
            
            break;
        }
        case OP_STORE:
        {
            /* Set the memory contents to argument B's value */
            state->memory[*valA + state->usedMemory] = *valB;
            
            printf("STORE %#x %#x\n", *valA, *valB);
            
            break;
        }
        case OP_GET:
        {
            /* Set argument A's value to the memory contents */
            *valA = state->memory[*valB + state->usedMemory];
            
            printf("GET %#x %#x\n", *valA, *valB);
            
            break;
        }
        case OP_JMP:
        {
            /* Set PC to a new location */
            state->pc = *valA - 1; /* Subtract 1 to counteract pc increment */
            
            printf("JMP %#x\n", *valA);
            
            break;
        }
        case OP_IF:
        {
            if (*valA != *valB) /* Check if the values are different */
                state->pc++; /* Skip the next instruction */
            
            printf("IF %#x %#x\n", *valA, *valB);
            
            break;
        }
        case OP_IFN:
        {
            if (*valA == *valB) /* Check if the values are equal */
                state->pc++; /* Skip the next instruction */
            
            printf("IFN %#x %#x\n", *valA, *valB);
            
            break;
        }
        default:
        {
            vm_error(state, "Unknown opcode: %#x", opcode);
            
            break;
        }
    }
    
    /* Free the sinks to avoid a memory leak */
    free(sinkA);
    free(sinkB);
}

void vm_load(vm_state *state, word *instrs, int count)
{
    int i;
    
    for (i = 0; i < count; i++)
    {
        state->memory[i] = instrs[i]; /* Load the program into memory */
        state->usedMemory++; /* Count how much of the memory is taken up */
    }
}

void vm_run(vm_state *state)
{
    /* Run through every word in memory */
    while ((state->pc) < (state->usedMemory))
    {
        vm_execute(state, &state->memory[state->pc]); /* Execute the word */
        
        state->pc++; /* Increment the program counter */
    }
}
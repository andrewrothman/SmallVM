#include "../src/vm.h"

int main(void)
{
    word code[] = {
        0x01000009, /* SET A 4  */
        0x01001007, /* SET B 2  */
        0x02000001, /* ADD A B  */
        0x01002006, /* SET C 1  */
        0x03000002, /* SUB A C  */
        0x04001000  /* MULT B A */
    };
    /* Expected output: A = 5, B = A, C = 1, D = 0, E = 0 */
    
    /* Create a new virtual machine */
    vm_state *state = vm_new();
    
    vm_load(state, code, 6); /* Load the code into memory */
    vm_run(state); /* Run all code in memory */
    
    vm_close(state); /* Free up the VM and close */
    
    return EXIT_SUCCESS;
}


#include "../src/vm.h"

int main(void)
{
    word code[] = {
        0x01000006, /* SET A 1 */
        0x01001006, /* SET B 1 */
        0x02000001, /* ADD A B */
        0x0B000009, /* IFN A 4 */
        0x09007000, /* JMP 2   */
    };
    /* Expected output: A = 4, B = 1, C = 0, D = 0, E = 0 */
    
    /* Create a new virtual machine */
    vm_state *state = vm_new();
    
    vm_load(state, code, 5); /* Load the code into memory */
    vm_run(state); /* Run all code in memory */
    
    vm_close(state); /* Free up the VM and close */
    
    return EXIT_SUCCESS;
}


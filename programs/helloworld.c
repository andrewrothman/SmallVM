#include "../src/vm.h"

int main(void)
{
    word code[] = {
        0x01000007, /* SET A 2 */
        0x01001007, /* SET B 2 */
        0x02000001, /* ADD A B */
    };
    /* Expected output: A = 4, B = 2, C = 0, D = 0, E = 0 */
    
    /* Create a new virtual machine */
    vm_state *state = vm_new();
    
    vm_load(state, code, 3); /* Load the code into memory */
    vm_run(state); /* Run all code in memory */
    
    vm_close(state); /* Free up the VM and close */
    
    return EXIT_SUCCESS;
}
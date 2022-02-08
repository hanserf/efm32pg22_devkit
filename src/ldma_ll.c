#include "src/ldma_ll.h"
#include "src/bsp.h"
#include <em_ldma.h>
#include <stddef.h>
#include <stdint.h>

ldma_ll_irq_cb_t jmp_table[LDMA_IRQ_NUM_IRQS];

/*System common IRQ handler*/

void LDMA_IRQHandler(void) {
    uint32_t pending;
    // Read interrupt source
    pending = LDMA_IntGet();
    // Clear interrupts
    LDMA_IntClear(pending);
    // Check for LDMA error
    if (pending & LDMA_IF_ERROR) {
        // Loop here to enable the debugger to see what has happened
        while (1)
            ;
    }
    /* Find what LDMA Channel has been set and call corresponding IRQ */
    for (ldma_ll_irq_t i = 0; i < LDMA_IRQ_NUM_IRQS; i++) {
        if (pending & (1 << i)) {
            if (jmp_table[i] != NULL) {
                jmp_table[i]();
            }
        }
    }
}
/*Register IRQ functions from other modules into this source */
void ldma_ll_register_irq(ldma_ll_irq_t ch, ldma_ll_irq_cb_t irq_cb) {
    if (ch < LDMA_IRQ_NUM_IRQS) {
        jmp_table[ch] = irq_cb;
    }
}
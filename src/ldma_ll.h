#pragma once
typedef void (*ldma_ll_irq_cb_t)();
typedef enum {
    LDMA_IRQ_PDM,
    LDMA_IRQ_WS2812,
    // Do not remove
    LDMA_IRQ_NUM_IRQS
} ldma_ll_irq_t;

void ldma_ll_register_irq(ldma_ll_irq_t ch, ldma_ll_irq_cb_t irq_cb);
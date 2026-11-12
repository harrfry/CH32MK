#pragma once

#include "ch32v20x.h"

typedef struct {
    GPIO_TypeDef* PORT;
    uint16_t PIN;    
} pin_t;

#define DEFINE_PORT_PINS(P) \
    static const pin_t P##0  = { GPIO##P, (1U << 0)  }; \
    static const pin_t P##1  = { GPIO##P, (1U << 1)  }; \
    static const pin_t P##2  = { GPIO##P, (1U << 2)  }; \
    static const pin_t P##3  = { GPIO##P, (1U << 3)  }; \
    static const pin_t P##4  = { GPIO##P, (1U << 4)  }; \
    static const pin_t P##5  = { GPIO##P, (1U << 5)  }; \
    static const pin_t P##6  = { GPIO##P, (1U << 6)  }; \
    static const pin_t P##7  = { GPIO##P, (1U << 7)  }; \
    static const pin_t P##8  = { GPIO##P, (1U << 8)  }; \
    static const pin_t P##9  = { GPIO##P, (1U << 9)  }; \
    static const pin_t P##10 = { GPIO##P, (1U << 10) }; \
    static const pin_t P##11 = { GPIO##P, (1U << 11) }; \
    static const pin_t P##12 = { GPIO##P, (1U << 12) }; \
    static const pin_t P##13 = { GPIO##P, (1U << 13) }; \
    static const pin_t P##14 = { GPIO##P, (1U << 14) }; \
    static const pin_t P##15 = { GPIO##P, (1U << 15) };

DEFINE_PORT_PINS(A)
DEFINE_PORT_PINS(B)
DEFINE_PORT_PINS(C)
DEFINE_PORT_PINS(D)

#undef DEFINE_PORT_PINS
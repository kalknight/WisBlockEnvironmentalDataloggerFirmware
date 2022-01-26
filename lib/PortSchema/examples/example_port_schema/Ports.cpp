#include "Ports.h"

portSchema getPort(uint8_t port_number) {
    for (uint8_t i = 0; i < (sizeof(all_ports) / sizeof(portSchema)); i++) {
        if (all_ports[i].port_number == port_number) {
            return all_ports[i];
        }
    }
    return PORTERROR;
}
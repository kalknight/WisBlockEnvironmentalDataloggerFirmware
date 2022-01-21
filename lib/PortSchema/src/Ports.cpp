#include "Ports.h"

portSchema getPort(uint8_t port_number) {
    switch (port_number) {
        case 1: {
            return PORT1;
        }
        case 2: {
            return PORT2;
        }
        case 3: {
            return PORT3;
        }
        case 4: {
            return PORT4;
        }
        case 5: {
            return PORT5;
        }
        case 6: {
            return PORT6;
        }
        case 7: {
            return PORT7;
        }
        case 8: {
            return PORT8;
        }
        case 9: {
            return PORT9;
        }
        case 50: {
            return PORT50;
        }
        case 51: {
            return PORT51;
        }
        case 52: {
            return PORT52;
        }
        case 53: {
            return PORT53;
        }
        case 54: {
            return PORT54;
        }
        case 55: {
            return PORT55;
        }
        case 56: {
            return PORT56;
        }
        case 57: {
            return PORT57;
        }
        case 58: {
            return PORT58;
        }
        case 59: {
            return PORT59;
        }
        default: {
            return PORTERROR;
        }
    }
}
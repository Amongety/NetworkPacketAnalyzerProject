#include "include/analizator.h"
#include "include/get_listen_kernel.h"
#include "include/io_kernel.h"

int kernel_listening(struct ifinfo infoPC) {
    int kerlst;
    kerlst = kernel_socket(kerlst, infoPC);
    if(kerlst == -1) return -1;

    if(read_kernel(kerlst) == -1) {
        close(kerlst);
        return -1;
    };

    close(kerlst);
    
    return 0;
}

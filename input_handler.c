
#include "input_handler.h"
#include <stdio.h>
#include <string.h>

#ifdef SERVER_CLIENT
#include <stdlib.h>

void client_app_send(const char *buffer);

void call_input_handler(const char *buffer) {
    client_app_send(buffer);
}

#else
void call_input_handler(const char *buffer) {
    printf("🖨️ Local Output: %s\n", buffer);
}
#endif

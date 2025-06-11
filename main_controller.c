
#include <stdio.h>
#include <string.h>
#include "input_handler.h"

int main() {
    char buffer[1024];

    printf("📝 Enter your message: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    call_input_handler(buffer);
    return 0;
}

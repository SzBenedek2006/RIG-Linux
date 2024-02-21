#include <stdio.h>

#define CSI "\x1b["  // ANSI escape code for Control Sequence Introducer

int main() {
    // Write to stdout (standard output)
    printf("This is written to stdout.\n");

    // Save cursor position for stdout
    printf(CSI "s");

    // Move cursor to a specific position for stderr
    fprintf(stderr, CSI "10;0H"); // Move cursor to row 10, column 0
    fprintf(stderr, "This is written to stderr.\n");

    // Restore cursor position for stdout
    printf(CSI "u");

    // Continue writing to stdout
    printf("Back to stdout.\n");

    return 0;
}

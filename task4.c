#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compress the input file using Run-Length Encoding (RLE)
void compressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("Error: Cannot open file.\n");
        return;
    }

    char current, previous;
    int count = 1;

    previous = fgetc(in); // Read first character

    while ((current = fgetc(in)) != EOF) {
        if (current == previous) {
            count++;
        } else {
            // Write compressed form: character followed by count
            fprintf(out, "%c%d", previous, count);
            previous = current;
            count = 1;
        }
    }
    // Write last sequence
    fprintf(out, "%c%d", previous, count);

    fclose(in);
    fclose(out);
    printf("Compression completed! Output saved to '%s'\n", outputFile);
}

// Function to decompress an RLE-compressed file
void decompressFile(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "r");
    FILE *out = fopen(outputFile, "w");

    if (in == NULL || out == NULL) {
        printf("Error: Cannot open file.\n");
        return;
    }

    char ch;
    int count;

    // Read character followed by number (count)
    while (fscanf(in, "%c%d", &ch, &count) != EOF) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out); // Repeat character
        }
    }

    fclose(in);
    fclose(out);
    printf("Decompression completed! Output saved to '%s'\n", outputFile);
}

// Main function with user menu
int main() {
    int choice;
    char inputFile[50], outputFile[50];

    printf("=== CodTech Internship Task 4: RLE Compression Tool ===\n");
    printf("1. Compress a file\n");
    printf("2. Decompress a file\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    printf("Enter input file name (e.g., input.txt): ");
    scanf("%s", inputFile);
    printf("Enter output file name (e.g., output.txt): ");
    scanf("%s", outputFile);

    if (choice == 1) {
        compressFile(inputFile, outputFile);
    } else if (choice == 2) {
        decompressFile(inputFile, outputFile);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_meaning(char word[]) {
    char command[300];

    // Use curl to fetch JSON response and save it to output.txt
    sprintf(command, "curl -s https://api.dictionaryapi.dev/api/v2/entries/en/%s > output.txt", word);
    system(command);

    // Open the output file
    FILE *file = fopen("output.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[500];
    int found = 0;

    printf("\nMeaning(s) of '%s':\n", word);

    // Read file line by line
    while (fgets(line, sizeof(line), file)) {
        char *definition_start = strstr(line, "\"definition\":");
        if (definition_start) {
            found = 1;

            // Extract the definition part
            char *start = strchr(definition_start, ':') + 3; // Move past ': "'
            char *end = strchr(start, '"');                 // Find closing quote
            if (start && end && start < end) {
                *end = '\0'; // Remove trailing quote
                printf("- %s\n", start);
            }
            break; // Stop after the first definition
        }
    }

    fclose(file);

    if (!found) {
        printf("No definition found!\n");
    }
}

int main() {
    char word[100];

    while (1) {
        printf("\nEnter a word (or type 'exit' to quit): ");
        scanf("%s", word);

        if (strcmp(word, "exit") == 0)
            break;

        get_meaning(word);
    }

    return 0;
}

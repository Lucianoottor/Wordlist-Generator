#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void wordlist_generator_recursive(char *str, int index, int len, FILE *file, const char *char_sets, const char *pattern) {
    if (index == len) {
        if (strstr(str, pattern) != NULL) {
            fprintf(file, "%s\n", str);
        }
        return;
    }

    for (int i = 0; i < strlen(char_sets); i++) {
        char ch = char_sets[i];
        str[index] = ch;
        wordlist_generator_recursive(str, index + 1, len, file, char_sets, pattern);
    }
}

void wordlist_generator(int len_min, int len_max, const char *name, const char *char_sets, const char *pattern) {
    FILE *file = fopen(name, "w");
    if (file == NULL) {
        perror("Error opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char *str = (char *)malloc((len_max + 1) * sizeof(char));
    if (str == NULL) {
        printf("Error on memory allocation.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int len = len_min; len <= len_max; len++) {
        wordlist_generator_recursive(str, 0, len, file, char_sets, pattern);
    }

    free(str);
    fclose(file);
}

int main(int argc, char *argv[]) {
    const char *program_name = "wlsgen";

    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf("Usage: %s <min_length> <max_length> <file_name> <pattern> <level>\n", program_name);
        printf("Options:\n");
        printf("  -h: Display this help message\n");
        return EXIT_SUCCESS;
    }

    if (argc != 6) {
        fprintf(stderr, "Usage: %s <min_length> <max_length> <file_name> <pattern> <level>\n", program_name);
        return EXIT_FAILURE;
    }

    int len_min = atoi(argv[1]);
    int len_max = atoi(argv[2]);
    char *file_name = malloc(strlen(argv[3]) + 1);
    if (file_name == NULL) {
        printf("Error on memory allocation.\n");
        return EXIT_FAILURE;
    }
    strcpy(file_name, argv[3]);
    const char *pattern = argv[4];

    const char *letters = "abcdefghijklmnopqrstuvwxyz";
    const char symbols[] = "!@#$%^&*()_+{}[]|;:,.<>?";
    const char capital_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char numbers[] = "0123456789";

    if (len_min <= 0 || len_max <= 0 || len_min > len_max) {
        fprintf(stderr, "Length of words is not declared correctly.\n");
        free(file_name);
        return EXIT_FAILURE;
    }

    int level = atoi(argv[5]);
    
    const char* char_sets;
    switch (level) {
        case 0:
            char_sets = letters;
            break;
        case 1:
            char_sets = strcat(strcpy((char*)malloc(strlen(letters) + strlen(capital_letters) + 1), letters), capital_letters);
            break;
        case 2:
            char_sets = strcat(strcat(strcpy((char*)malloc(strlen(letters) + strlen(capital_letters) + strlen(numbers) + 2), letters), capital_letters), numbers);
            break;
        case 3:
            char_sets = strcat(strcat(strcat(strcpy((char*)malloc(strlen(letters) + strlen(capital_letters) + strlen(numbers) + strlen(symbols) + 3), letters), capital_letters), numbers), symbols);
            break;
    }

    wordlist_generator(len_min, len_max, file_name, char_sets, pattern);

    free(file_name);

    return EXIT_SUCCESS;
}

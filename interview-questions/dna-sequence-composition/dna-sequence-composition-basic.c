#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SEQUENCES 100
#define MAX_LENGTH 100
#define MAX_PARTS 20

char sequences[MAX_SEQUENCES][MAX_LENGTH];
int sequence_count = 0;

int exists_in_list(const char *seq)
{
    for (int i = 0; i < sequence_count; i++)
    {
        if (strcmp(sequences[i], seq) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void print_decomposition(const char *original, char parts[][MAX_LENGTH], int part_count)
{
    printf("%s = [", original);
    for (int i = 0; i < part_count; i++)
    {
        printf("\"%s\"", parts[i]);
        if (i < part_count - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void find_decompositions(const char *remaining, const char *original,
                         char current_parts[][MAX_LENGTH], int part_count)
{
    int len = strlen(remaining);

    if (len == 0)
    {
        if (part_count >= 2)
        {
            print_decomposition(original, current_parts, part_count);
        }
        return;
    }

    for (int i = 1; i <= len; i++)
    {
        char prefix[MAX_LENGTH];
        strncpy(prefix, remaining, i);
        prefix[i] = '\0';

        if (exists_in_list(prefix) && strcmp(prefix, original) != 0)
        {
            strcpy(current_parts[part_count], prefix);

            find_decompositions(remaining + i, original, current_parts, part_count + 1);
        }
    }
}

void find_composite_sequences()
{
    for (int i = 0; i < sequence_count; i++)
    {
        char current_parts[MAX_PARTS][MAX_LENGTH];
        find_decompositions(sequences[i], sequences[i], current_parts, 0);
    }
}

int main()
{
    strcpy(sequences[sequence_count++], "ATGC");
    strcpy(sequences[sequence_count++], "AT");
    strcpy(sequences[sequence_count++], "GC");
    strcpy(sequences[sequence_count++], "GCTA");
    strcpy(sequences[sequence_count++], "TA");
    strcpy(sequences[sequence_count++], "ATGCTA");
    strcpy(sequences[sequence_count++], "CTAGC");
    strcpy(sequences[sequence_count++], "CT");
    strcpy(sequences[sequence_count++], "AGC");
    strcpy(sequences[sequence_count++], "CTAGCTA");

    printf("Input sequences:\n");
    for (int i = 0; i < sequence_count; i++)
    {
        printf("  %s\n", sequences[i]);
    }
    printf("\nDecompositions:\n");

    find_composite_sequences();

    return 0;
}
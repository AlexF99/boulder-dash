#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "records.h"
#define max_records 10

int *get_records_array()
{
    int i = 0;
    int j = 0;
    int *records = NULL;
    char title[9];
    FILE *records_file = fopen("records.txt", "r");

    if (!records_file || records_file == NULL)
    {
        records_file = fopen("records.txt", "w");
        fprintf(records_file, "records:\n");
    }

    records = calloc(max_records, sizeof(int));

    fscanf(records_file, "%s\n", title);

    while (i < max_records && !feof(records_file))
    {
        fscanf(records_file, "%d:\t%d\n", &j, &records[i]);
        i++;
    }

    fclose(records_file);
    return records;
}

void save_records(int points)
{
    int i, j;
    int *records = get_records_array();
    int *records_copy;
    FILE *records_file = fopen("records.txt", "r+");

    if (!records_file || records_file == NULL)
    {
        fprintf(stderr, "erro ao abrir arquivo de pontuacao\n");
        return;
    }

    records_copy = calloc(max_records, sizeof(int));
    for (i = 0; i < max_records; i++)
        records_copy[i] = records[i];

    for (i = 0; i < max_records; i++)
    {
        if (points > records[i])
        {
            for (j = i; j < max_records - 1; j++)
                records[j + 1] = records_copy[j];
            records[i] = points;
            break;
        }
    }

    fprintf(records_file, "records:\n");
    for (i = 0; i < max_records; i++)
        fprintf(records_file, "%d:\t%d\n", i + 1, records[i]);

    fclose(records_file);
    free(records);
    free(records_copy);
}

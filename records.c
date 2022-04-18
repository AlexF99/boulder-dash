#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "records.h"
#define max_records 10

t_record **get_records_array()
{
    int i = 0;
    t_record **records = NULL;
    char title[9];
    FILE *records_file = fopen("records.txt", "r");

    if (!records_file || records_file == NULL)
    {
        records_file = fopen("records.txt", "w");
        fprintf(records_file, "records:\n");
    }

    // alloca array de records
    records = malloc(max_records * sizeof(t_record *));
    for (i = 0; i < max_records; i++)
        records[i] = (t_record *)calloc(max_records, sizeof(t_record));

    i = 0;
    fscanf(records_file, "%s\n", title);

    while (i < max_records && !feof(records_file))
    {
        fscanf(records_file, "%s\t%d\n", records[i]->username, &records[i]->points);
        i++;
    }

    fclose(records_file);

    return records;
}

void save_records(char *username, int points)
{
    int i, j;
    t_record **records = get_records_array();
    t_record *new_record;
    FILE *records_file = fopen("records.txt", "r+");

    if (!records_file || records_file == NULL)
    {
        fprintf(stderr, "erro ao abrir arquivo de pontuacao\n");
        return;
    }

    new_record = malloc(sizeof(t_record));

    new_record->points = points;
    strcpy(new_record->username, username);

    for (i = 0; i < max_records; i++)
    {
        if (records[i] && records[i] != NULL && new_record->points > records[i]->points)
        {
            for (j = i; j < max_records - 1; j++) {
                if (strlen(records[j+1]->username) > 0)
                    records[j + 1] = records[j];
            }
            records[i] = new_record;
            break;
        }
    }

    fprintf(records_file, "records:\n");
    for (int i = 0; i < max_records; i++)
    {
        if (records[i] && records[i] != NULL)
        {
            fprintf(records_file, "%s\t%d\n", records[i]->username, records[i]->points);
        }
    }
}
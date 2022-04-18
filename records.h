#ifndef _RECORDS_H_
#define _RECORDS_H_
#define max_username_length 20

typedef struct t_record
{
    int points;
    char username[max_username_length];
} t_record;

t_record **get_records_array();

void save_records(char *username, int points);

void free_records_array(t_record **records_array);

#endif
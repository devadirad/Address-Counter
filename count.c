#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _list_hexvals_ {
    int hex;
    struct _list_hexvals_ *next;
} list_hexvals;


typedef struct _ht_hexvals_ {
    int size;
    list_hexvals **table;
    int count;
} ht_hexvals;

ht_hexvals *create_ht(int size)
{
    int i;
    ht_hexvals *table_x;
    if (size<1) return NULL;
    if ((table_x = malloc(sizeof(ht_hexvals))) == NULL) {
        return NULL;
    }
    if ((table_x->table = malloc(sizeof(list_hexvals *) * size)) == NULL) {
        return NULL;
    }
    for(i=0; i<size; i++) table_x->table[i] = NULL;
    table_x->size = size;
    table_x->count = 0;
    
    return table_x;
}


unsigned int hash(ht_hexvals *ht, int hex)
{
    return abs(hex) % 1000;
}



list_hexvals *lookup_hex(ht_hexvals *ht, int hex)
{
    list_hexvals *list;
    unsigned int hashval = hash(ht, hex);
    for(list = ht->table[hashval]; list != NULL; list = list->next) {
        if (hex==list->hex) return list;
    }
    return NULL;
}



int add_hex(ht_hexvals *ht, int hex)
{
    list_hexvals *new_list;
    list_hexvals *current_list;
    unsigned int hashval = hash(ht, hex);
    if ((new_list = malloc(sizeof(list_hexvals))) == NULL) return 0;
    current_list = lookup_hex(ht, hex);
    if (current_list != NULL) return 0;
    new_list->hex = hex;
    new_list->next = ht->table[hashval];
    ht->table[hashval] = new_list;
    ht->count++;
    return 0;
}

void free_table(ht_hexvals *ht)
{
    int i;
    list_hexvals *list, *temp;
    
    if (ht==NULL) return;
    
    for(i=0; i<ht->size; i++) {
        list = ht->table[i];
        while(list!=NULL) {
            temp = list;
            list = list->next;
            free(temp);
        }
    }
    
    free(ht->table);
    free(ht);
}




int count_hex(ht_hexvals *ht)
{
    return ht->count;
}


int main(int argc, char *argv[]) {
    FILE *fp;
    ht_hexvals *mht;
    int size_of_table = 1000;
    int numu;
    char input[100]= "";
    mht = create_ht(size_of_table);
    numu=0;
    
    
    

    fp=fopen(argv[1], "rt");
    if (fp == NULL) {
        printf("error");
        exit(1);
    }
    
    while (!feof(fp)) {
        fgets(input, 59, fp);
        if (isxdigit(input[0]))
        {
            add_hex(mht, (int)strtol(input, NULL, 16));
        }
        else{
            printf("error");
            return 0;
        }
    }
    
    
    numu=count_hex(mht);
    printf("%u\n", numu);
    free_table(mht);
    return 0;
}


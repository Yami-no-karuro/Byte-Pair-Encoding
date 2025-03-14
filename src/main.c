#include <stdio.h>
#include <string.h>

#include "lib/hash_table.h"

int main() 
{
    HashTable *pairs = ht_create();

    char input[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
    int input_len = strlen(input);

    for (int i = 0; i < input_len - 1; i++) {
        char pair[3];

        pair[0] = input[i];
        pair[1] = input[i + 1];
        pair[2] = '\0';

        int pair_count = ht_search(pairs, pair);
        if (pair_count >= 0) {
            ht_delete(pairs, pair);
            pair_count++;
        } else {
            pair_count = 1;
        }
       
        ht_insert(pairs, pair, pair_count);
    }

    const char *most_recurring_pair = ht_most_recurring_key(pairs);
    if (NULL != most_recurring_pair)
        printf("Most recurring pair: %s\n", most_recurring_pair);

    ht_free(pairs);
    return 0;
}

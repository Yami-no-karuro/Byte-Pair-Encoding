#include <stdio.h>
#include <string.h>

#include "lib/hash_table.h"

int main() 
{
    HashTable *pairs = ht_create();

    char input[] = "aabdaaabaccabaaac";
    int input_len = strlen(input);

    for (int i = 0; i < input_len - 1; i++) {
        char pair[3];

        pair[0] = input[i];
        pair[1] = input[i + 1];
        pair[2] = '\0';

        int pair_count = ht_search(pairs, pair);
        if (pair_count >= 0) {
            pair_count++;
        } else {
            pair_count = 0;
        }

        ht_insert(pairs, pair, pair_count);
    }

    printf("aa: %d\n", ht_search(pairs, "aa"));
    printf("ab: %d\n", ht_search(pairs, "ab"));
    printf("bd: %d\n", ht_search(pairs, "bd"));
    printf("ac: %d\n", ht_search(pairs, "ac"));

    ht_free(pairs);
    return 0;
}


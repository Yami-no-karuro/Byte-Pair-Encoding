#include <stdio.h>
#include <string.h>

#include "lib/hash_table.h"

/**
 * Finds the key with the highest occurrence value in the provided hash table.
 * When all the keys occurs just once the function stall.
 *
 * @param table - The hash table to search in.
 * @param pair - The most recurring pair.
 * @return - The key with the highest associated value, or NULL if the table is empty.
 */
void compute_most_recurring_pair(HashTable *table, char **pair)
{
    int max_value = 1;
    for (int i = 0; i < TABLE_SIZE; i++) {

        HashNode *current = table->buckets[i];
        while (current) {
            if (current->value > max_value) {
                max_value = current->value;
                *pair = current->key;
            }

            current = current->next;
        }
    }
}

/**
 * Populates the pairs table.
 *
 * @param table - The hash table to populate.
 * @param input - The input text string.
 */
void compute_pairs_table(HashTable *pairs, char *input)
{
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
}

int main() 
{
    char input[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

    HashTable *pairs = ht_create();
    while(1) {
        compute_pairs_table(pairs, input);

        char *most_recurring_pair = NULL;
        compute_most_recurring_pair(pairs, &most_recurring_pair);

        printf("Most recurring pair: %s\n", most_recurring_pair);
        if (most_recurring_pair == NULL)
            break;
    }

    ht_free(pairs);
    return 0;
}

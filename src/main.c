#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/hash_table.h"

/**
 * Generates the "pairs" table from the provided input string.
 *
 * @param input - The input text string.
 * @return - The pairs table.
 */
HashTable *get_pairs(char *input)
{
    HashTable *pairs = ht_create();

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

    return pairs;
}

/**
 * Finds the key with the highest occurrence value in the provided hash table.
 * When all the keys occurs just once the function will stall on NULL.
 *
 * @param table - The hash table to search in.
 * @return - The key with the highest associated value, or NULL if the table is empty.
 */
char *get_most_recurring_pair(HashTable *table)
{
    char *pair = NULL;
    int max_value = 1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *current = table->buckets[i];
        while (current) {
            if (current->value > max_value) {
                max_value = current->value;
                pair = current->key;
            }

            current = current->next;
        }
    }

    return pair;
}

/**
 * Replace the first occurrence of "search" in "input" with "replace"
 *
 * @param input - The input string
 * @param search - The substring to look for
 * @param replace - The substring to replace search with
 */
char *str_replace(char *input, char *search, char *replace)
{
    int input_len = strlen(input);
    int search_len = strlen(search);
    int replace_len = strlen(replace);

    int new_str_len = (input_len - search_len) + replace_len;

    char *new_str = (char *)malloc((new_str_len + 1) * sizeof(char));
    if (!new_str) {
        printf("Error: Unable to allocate memory for the \"str_replace\" new string.");
        exit(EXIT_FAILURE);
    }

    strcpy(new_str, input);

    char *search_ptr = strstr(input, search);
    if (search_ptr == NULL) {
        free(new_str);
        return NULL;
    }

    int search_offset = search_ptr - input;
    for (int i = 0; i < replace_len; i++)
        new_str[search_offset + i] = replace[i];

    return new_str;
}

int main() 
{
    char input[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";

    while(1) {
        HashTable *pairs = get_pairs(input);
        char *most_recurring_pair = get_most_recurring_pair(pairs);

        if (most_recurring_pair == NULL) {
            free(pairs);
            free(most_recurring_pair);
            break;
        }
    
        char *new_input = str_replace(input, most_recurring_pair, "1");
        printf("%s\n", new_input);

        free(pairs);
        free(most_recurring_pair);
        free(new_input);
        break;
    }

    return 0;
}

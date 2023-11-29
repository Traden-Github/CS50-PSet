// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Custom function prototype
void free_memory(node *ptr);

// TODO: Choose number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// Set globals
unsigned int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    unsigned long sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        sum += tolower(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Cannot load dictionary\n");
        return false;
    }
    char s_word[LENGTH + 1];
    while (fscanf(dict, "%s", s_word) != EOF)
    {
        wordCount++;
        node *s = malloc(sizeof(node));
        if (s == NULL)
        {
            printf("Not enough memory\n");
            return false;
        }

        strcpy(s->word, s_word);
        int index = hash(s_word);
        s->next = table[index];
        table[index] = s;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordCount > 0)
    {
        return wordCount;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        free_memory(table[i]);
    }
    return true;
}

void free_memory(node *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    if (ptr->next == NULL)
    {
        free(ptr);
        return;
    }
    else
    {
        node *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
        free_memory(ptr);
        return;
    }
}

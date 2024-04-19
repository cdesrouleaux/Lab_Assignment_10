#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    char *isword; 
    struct node *next; // horizontally accross (parents)
    struct node *right, *left; // vertically down (children)
};

// Inserts a new word into the first empty slot of the trie structure 
void insert(struct Trie *pTrie, char *word)
{
    struct Trie * t = pTrie; // used to transverse the trie structure
    struct Trie * v;
    int n = 0;
    int flag = 0;

    if(t == NULL) // if null add the word in tree format top down 
    {
        struct Trie * v;
        v = createTrie((sizeof(word)/sizeof(char)));
        for(int i=0; i < (sizeof(word)/sizeof(char)); i++)
        {
            v->isword = word[i];
            v = v->right;
        }
    }
    
    else // if not null find the next empty space to form a tree top down
    {
        // if you find an identical character search through the children for matching characters/words
        while(t != NULL)
        {
            if(strcmp(word[0], t->isword) == 0) // if the parent letter matches check the children for matches
            {
                flag = 1;
                t = t->right;
                // if a child letter matches or is null add it to the right of the tree structure
                if(strcmp(word[n], t->isword) == 0 || t->isword == NULL)                 
                {
                    while (word[n] != '\0')
                    {
                        strcpy(t->isword, word[n]);
                        t = t->right;
                        n++;
                    }
                    break;
                }
            }
            else // if we didn't find a complete match we add the new letters to our left tree structure
            {
                while (word[n] != '\0')
                {
                    strcpy(t->isword, word[n]);
                    t = t->left;
                    n++;
                }
            }
            n++;
            t = t->next;
        }     
    }
        
        // if an identical character is not found as a parent structure start from scratch and initalize it.
        if(flag == 0)
        {
            struct Trie * v;
            v = createTrie((sizeof(word)/sizeof(char)));
            for(int i=0; i < (sizeof(word)/sizeof(char)); i++)
            {
                v->isword = word[i];
                v = v->right;
            }
        }
}     

int count=0;
// recursivly computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie * t = pTrie; // used to transverse the trie structure


    // means were reached the end of our tree leg
    if(pTrie->isword == NULL)
        count++;

    // adds up all 
    else
    {
        struct Trie * new = t;
        for (int i = 0; i < (sizeof(word)/sizeof(char)); i++)
        {    
            if (pTrie->isword != NULL)
                count ++;
            t = t->right;
        }
        numberOfOccurances(new, word);
    }
    return count;  
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    free(pTrie);
    return pTrie;
}

// Initializes a trie structure
struct Trie *createTrie(int numWords)
{
    struct Trie * trie = (struct Trie*)malloc(sizeof(struct Trie) * numWords); // max number of parent nodes in the structure
    struct Trie * t;
    t = trie;

    while(t < numWords)
    {
        trie = NULL;
        t = t->next;
        t = t->right;
        t = t->left;
    }
    return trie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
}

int main(void)
{
    char *inWords[256];

    // read the number of the words in the dictionary
    // int numWords = readDictionary("dictionary.txt", inWords);

    int numWords;
    scanf("%d", numWords);

    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie(numWords);
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
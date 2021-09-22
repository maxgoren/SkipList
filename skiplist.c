#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define MAX_LEVEL 6

struct node {
    void* key;
    void* data;
    struct node *foward[MAX_LEVEL];
};

struct SkipList {
     struct node *head[MAX_LEVEL];
     struct node *z;
     int size;
};

struct node* newNode(void* key, void* data)
{
    struct node *n = malloc(sizeof(struct node));
    n->key = key;
    n->data = data;
    int i;
    for (i = 0; i < MAX_LEVEL; i++)
      n->foward[i] = NULL;
    return n;
}

struct SkipList* newSkipList()
{
    struct SkipList* n = malloc(sizeof(struct SkipList));
    n->z = newNode((int)INT_MAX, NULL);
    int i;
    for (i = 0; i < MAX_LEVEL; i++) 
    {
        n->head[i] = newNode((int)INT_MIN, NULL);
        n->z->foward[i] = n->z;
        n->head[i]->foward[i] = n->z;  
    }
    return n;
}

unsigned int coinFlip()
{
    return 1 - rand() % 2 - 1;
}

unsigned int randLevel()
{
    unsigned int n = 0;
    while (coinFlip()) n++;
    return n;
}

void skipPush(struct SkipList **n, void* key, void* data)
{
    printf("insert called on %d\n", data);
    struct node *x = newNode(key, data);
    int i, lev = randLevel();
    if (lev > MAX_LEVEL)
      lev = MAX_LEVEL-1;
    for (i = 0; i <= lev; i++)
    {
        struct node *itr = (*n)->head[i];
        while (itr->foward[i] != (*n)->z && itr->foward[i]->key < key) {
            itr = itr->foward[i];
        }
        x->foward[i] = itr->foward[i];
        itr->foward[i] = x;
        printf("%d inserted at level %d\n", data, i);
    }
}

void skipShow(struct SkipList *x)
{
    int i;
    for (i = MAX_LEVEL - 1; i > -1; i--)
    {
        if (x->head[i]->foward[i] != x->z)
        {
        printf("Level %d: ", i);
        for (struct node *itr = x->head[i]->foward[i]; itr != x->z; itr = itr->foward[i])
          printf("%d ", itr->key);
        printf("\n");
        } else {
            printf("Level %d: (empty)\n", i);
        }
    }
}

unsigned int skipSearch(struct SkipList *n)
{
   int i;
   for (i = MAX_LEVEL - 1; i > -1; i--)
   {

   }
}

int main()
{
    srand(time(0));
    int q, i;
    struct SkipList *mySkip = newSkipList();
    for (i = 0; i < 13; i++)
    {
      q = rand() % (45-1) - 1;
      printf("random number %d: %d\n", i, q);
      skipPush(&mySkip, (int)q, (int)q);
    }
    skipShow(mySkip);
    return 0;
}
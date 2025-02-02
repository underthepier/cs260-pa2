#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item{
  char *word;
  int weight;
}Item;

int main(void)
{
  Item word1 = {"hello", 5};
  Item word2 = {"poopy", 10};
  Item word3 = {"poop", 18};
  Item word4 = {"poop", 1};
  Item word5 = {"toiletries", 25};
  
  // Item* words[2] = {&word1, &word2};

  // printf("%d\n", strcmp(words[0]->word, words[1]->word));
  // printf("%d\n", strcmp(words[1]->word, words[0]->word));

  char *query = "po";
  char query_compare[128];
  size_t query_len = strlen(query);
  
  strncpy(query_compare, word2.word, query_len);
  query_compare[query_len] = '\0';

  char *v = "é";
  char *ve = "¶";
  char *ver = "Â¶";
  char *inf = "~~~~~";

  int a[3] = {-61, -126, 0};

  printf("%ld\n", strlen(ve));
  printf("%d\n", ve[0]);

  printf("%ld\n", strlen(ver));
  printf("%d\n", ver[0]);

  if((int)ver[0] == -61)
    printf("yes\n");
  



  
}
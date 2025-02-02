#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct item{
  char *word;
  int weight;
}Item;

void mergeSort(Item **array, int n);
void mergeSortRec(Item **array, int start, int stop);
void merge(Item **array, int start, int middle, int stop);

int main(void)
{
  Item word1 = {"bunny", 5};
  Item word2 = {"bucket", 25};
  Item word3 = {"accccccc", 325};
  Item word4 = {"custom", 18};
  Item word5 = {"customizing", 1};


  Item **words;
  words = (Item **)malloc(sizeof(*words) * 5);

  words[0] = &word1;
  words[1] = &word2;
  words[2] = &word3;
  words[3] = &word4;
  words[4] = &word5;
  
  int array_len = 5;
  
  printf("List before:\n");
  for(int i = 0; i<array_len; i++)
  {
    printf("%s\n", words[i]->word);
  }

  printf("\n");
  mergeSort(words, array_len);

  printf("List after:\n");
  for(int i = 0; i<array_len; i++)
  {
    printf("%s\n", words[i]->word);
  }
}

void mergeSort(Item **array, int n)
{
  mergeSortRec(array, 0, n-1);
}

void mergeSortRec(Item **array, int start, int stop)
{

  if(start >= stop)
      return;

  int middle;
  middle = start + floor((stop - start) / 2);
  mergeSortRec(array, start, middle);
  mergeSortRec(array, middle + 1, stop);
  merge(array, start, middle, stop);
}

void merge(Item **array, int start, int middle, int stop)
{

  int a_length = (middle+1) - start;
  int b_length = stop - middle;
  
  //Represent infinity for merge sort as the highest ascii value character unlikely to be used in a word
  char *inf = "~~~~~";
  
  Item **a;
  a = (Item **)malloc((sizeof(*a) * a_length) + 1); //plus one to append infinity

  Item **b;
  b = (Item **)malloc((sizeof(*b) * b_length) + 1);

  int i;
  int j;
  
  for(i = 0; i < a_length; i++)
  {
    a[i] =  array[start+i]->word;
  }

  a[a_length] = inf;

  for(i = 0; i < b_length; i++)
  {
    b[i] =  array[middle+1+i]->word;
  }

  b[b_length] = inf;

  i = 0;
  j = 0;
  
  for(int k = start; k <= stop; k++)
  {
    //Word goes first condition
    if(strcmp(a[i], b[j]) < 0)
    {
      array[k]->word = a[i];
      array[k]->weight = a[i];
      i++;
    }
    else
    {
      array[k]->word = b[j];
      array[k]->weight = b[j];
      j++;
    }
  }

  free(a);
  free(b);

}


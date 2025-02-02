//Working merge sort for numbers

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void mergeSort(float *array, int n);
void mergeSortRec(float *array, int start, int stop);
void merge(float *array, int start, int middle, int stop);

int main(void)
{
  float num[10] = {0,5,8,3,4,15,980,52,36,1};
  int array_len = sizeof(num)/sizeof(num[0]);
  mergeSort(num, array_len);
  for(int i = 0; i<array_len; i++)
  {
    printf("%f\n", num[i]);
  }
}

void mergeSort(float *array, int n)
{
  mergeSortRec(array, 0, n-1);
}

void mergeSortRec(float *array, int start, int stop)
{
  if(start >= stop)
      return;

  int middle;
  middle = start + floor((stop - start) / 2);
  mergeSortRec(array, start, middle);
  mergeSortRec(array, middle + 1, stop);
  merge(array, start, middle, stop);
}

void merge(float *array, int start, int middle, int stop)
{
  int a_length = (middle+1) - start;
  int b_length = stop - middle;

  float *a;
  a = malloc((sizeof(*a) * a_length) + 1 ); //plus one to append infinity

  float *b;
  b = malloc((sizeof(*b) * b_length) + 1);

  int i;
  int j;

  for(i = 0; i < a_length; i++)
  {
    a[i] = array[start+i];
  }

  a[a_length] = INFINITY;


  for(i = 0; i < b_length; i++)
  {
    b[i] = array[middle+1+i];
  }

  b[b_length] = INFINITY;

  i = 0;
  j = 0;

  for(int k = start; k <= stop; k++)
  {
    if(a[i] <= b[j])
    {
      array[k] = a[i];
      i++;
    }
    else
    {
      array[k] = b[j];
      j++;
    }
  }

  free(a);
  free(b);
}
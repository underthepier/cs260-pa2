#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFSIZE 256

typedef struct item{
  char *word;
  int weight;
}Item;

void mergeSort(Item **array, int n, int sort_type);
void mergeSortRec(Item **array, int start, int stop, int sort_type);
void merge(Item **array, int start, int middle, int stop, int sort_type);

int main(int argc, char **argv) {
    char *dictionaryFilePath = argv[1]; //this keeps the path to dictionary file
    char *queryFilePath = argv[2]; //this keeps the path to the file that keeps a list of query wrods, 1 query per line
    
    int wordCount=0; //this variable will keep a count of words in the dictionary, telling us how much memory to allocate
    
    int queryCount=0; //this variable will keep a count of queries in the query file, telling us how much memory to allocate for the query words

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////// read dictionary file /////////////////////////
    ////////////////////////////////////////////////////////////////////////
    
    FILE *fp = fopen(dictionaryFilePath, "r");
    char *line = NULL; //variable to be used for line counting
    size_t lineBuffSize = 0; //variable to be used for line counting
    ssize_t lineSize; //variable to be used for line counting

    //check if the file is accessible, just to make sure...
    if(fp == NULL){
        fprintf(stderr, "Error opening file:%s\n",dictionaryFilePath);
        return -1;
    }

    //First, let's count number of lines. This will help us know how much memory to allocate
    while((lineSize = getline(&line,&lineBuffSize,fp)) !=-1)
    {
        wordCount++;
    }

    //Printing wordCount for debugging purposes. You can remove this part from your submission.
    //printf("%d\n",wordCount);

    /////////////////PAY ATTENTION HERE/////////////////
    //This might be a good place to allocate memory for your data structure, by the size of "wordCount"
    ////////////////////////////////////////////////////
    Item **words;
    words = (Item **)malloc(sizeof(*words) * wordCount);
    for(int i = 0; i < wordCount; i++)
        {
            words[i] = (Item *)malloc(sizeof(Item));
        //    printf("%p\n", words[i]);
        }

    // //Read the file once more, this time to fill in the data into memory
    fseek(fp, 0, SEEK_SET); // rewind to the beginning of the file, before reading it line by line.
    char word[BUFSIZE]; //to be used for reading lines in the loop below
    int weight;

    for(int i = 0; i < wordCount; i++)
    {
        fscanf(fp, "%s %d\n",word,&weight);
        //Let's print them to the screen to make sure we can read input, for debugging purposes. You can remove this part from your submission.

        //printf("%s %d\n",word,weight); 

        /////////////////PAY ATTENTION HERE/////////////////
        //This might be a good place to store the dictionary words into your data structure
        ////////////////////////////////////////////////////

        //Copy the word into Item
        size_t word_size = sizeof(char) * strlen(word);
        // printf("%ld\n", word_size);

        words[i]->word = malloc(word_size + 1);
        strcpy(words[i]->word, word);
        
        //Copy the weight into Item
        words[i]->weight = weight;

        //printf("%s %d\n",words[i]->word,words[i]->weight);
    }
    
    //close the input file
    fclose(fp);
 

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////// read query list file /////////////////////////
    ////////////////////////////////////////////////////////////////////////
    fp = fopen(queryFilePath, "r");

    //check if the file is accessible, just to make sure...
    if(fp == NULL){
        fprintf(stderr, "Error opening file:%s\n",queryFilePath);
        return -1;
    }

    //First, let's count number of queries. This will help us know how much memory to allocate
    while((lineSize = getline(&line,&lineBuffSize,fp)) !=-1)
    {
        queryCount++;
    }
    free(line); //getline internally allocates memory, so we need to free it here so as not to leak memory!!

    //Printing line count for debugging purposes. You can remove this part from your submission.
    //printf("%d\n",queryCount);

    // /////////////////PAY ATTENTION HERE/////////////////
    // //This might be a good place to allocate memory for storing query words, by the size of "queryCount"
    // ////////////////////////////////////////////////////
    char **queries = (char **)malloc(sizeof(*queries) * queryCount);

    fseek(fp, 0, SEEK_SET);// rewind to the beginning of the file, before reading it line by line.
    for(int i = 0; i < queryCount; i++)
    {
        fscanf(fp, "%s\n",word);
        //Let's print them to the screen to make sure we can read input, for debugging purposes. You can remove this part from your submission.
        //printf("%s\n",word);

        /////////////////PAY ATTENTION HERE/////////////////
        //This might be a good place to store the query words in a list like data structure
        ////////////////////////////////////////////////////   
        queries[i] = malloc( (sizeof(char) * strlen(word)) + 1);
        strcpy(queries[i], word);
        //printf("%c\n", queries[i][0]); //debug print
    }
    //close the input file
    fclose(fp);

    ////////////////////////////////////////////////////////////////////////
    ///////////////////////// reading input is done ////////////////////////
    ////////////////////////////////////////////////////////////////////////

    //Now it is your turn to do the magic!!!
    //do search/sort/print, whatever you think you need to do to satisfy the requirements of the assignment!
    //loop through the query words and list suggestions for each query word if there are any
    //don't forget to free the memory before you quit the program!

    /*To facilitate quick lookups, 
    allocate memory to store the indices in "words" 
    that correspond to where strings beginning with a specific char start
    (e.g. strings starting with a 'b' start at index i in "words"). "locations" will store from '!' to 'z' in ascii (inclusive). 
    locations[0] corresponds to '!' and locations[89] corresponds to 'z'
    locations[90] corresponds to 'Â', locations[91] corresponds to '¶' */
    int num_locations = 92;
    int *locations = malloc(sizeof(*locations)*num_locations);

    //initialize locations with -1 to indicate that no word beginning with a specific char exists
    for(int i = 0; i < num_locations; i++)
        locations[i] = -1;

    //wordCount--;
    //Sort words by including 0
    //printf("before merge\n");
    mergeSort(words, wordCount, 0);
    //printf("after merge\n");

    // for(int i = 0; i < wordCount; i++)
    //     printf("%d - %s\n",i, words[i]->word);
    // printf("Word count - %d\n", wordCount);


    //Find where strings that begin with a specific char start in "words" and store the index in "locations"
    int location; //The index in "locations" to check
    for(int i = 0; i < wordCount; i++)
    {
        //Check for special characters
        if(words[i]->word[0] == -61) // 'Â'
            location = 90;
        else if(words[i]->word[0] == -62) // '¶'
            location = 91;
        else
        {
            // printf("here\n");
            //printf("%s\n", words[i]->word);
            location = (words[i]->word[0] - 33);
        }
        
        if(locations[location] == -1)
            locations[location] = i;
    }

    //OUTPUT SPECS:
    // use the following if no word to suggest: printf("No suggestion!\n");
    // use the following to print a single line of outputs (assuming that the word and weight are stored in variables named word and weight, respectively): 
    // printf("%s %d\n",word,weight);
    // if there are more than 10 outputs to print, you should print the top 10 weighted outputs.

    //for query in queries
    int j, start, end;
    char query_compare[40]; //buffer to compare queries with dictionary words
    size_t query_len;
    
    for(int i = 0; i < queryCount; i++)
    {    
        printf("Query word:%s\n", queries[i]);        
        //Search from words[locations[queries[i][0] - 33]] to words[locations[queries[i][0] - 33 + 1]] (or the next position)
        j = ((int)queries[i][0]) - 33;

        if(locations[j] == -1)
        {
            printf("No suggestion!\n");
            continue;
        }
        
        start = locations[j];
        j++;
        
        //Find the end index of the range to search
        while(locations[j] == -1)
            j++;

        end = locations[j];

        //Allocate memory for the suggestions
        int num_matches = end-start+1;
        Item **matches; 
        matches = (Item **)malloc(sizeof(*matches) * num_matches);

        for(int n = 0; n < num_matches; n++)
        {
            matches[n] = (Item *)malloc(sizeof(Item));
        }

        j = 0;
        //Loop through the range and find the suggested words
        for(int k = start; k < end; k++)
        {
            query_len = strlen(queries[i]);
            strncpy(query_compare, words[k]->word, query_len);         
            
            query_compare[query_len] = '\0';

            if(strcmp(queries[i], query_compare) == 0)
            {   
                //Store the suggestion
                matches[j]->word = words[k]->word;
                matches[j]->weight = words[k]->weight;
                //printf("query: %s suggestion: %s\n", queries[i], matches[j]->word);

                j++;
            }

        }
        //Sort the suggestions in descending order of weight (specified by 1); max 10 suggestions          
        mergeSort(matches, j, 1);
      
        if(j > 10)
        {
            for(int l = 0; l < 10; l++)
            {
                printf("%s %d\n", matches[l]->word, matches[l]->weight);
            }
        }
        else if(j==0)
        {
            printf("No suggestion!\n");
        }
        else
        {
            for(int l = 0; l < j; l++)
            {
                printf("%s %d\n", matches[l]->word, matches[l]->weight);
            }            
        }

        for(int n = 0; n < num_matches; n++)
        {
            free(matches[n]);
        }  
        
    }

   // printf("Freeing words\n");
    //Free memory
    for(int i = 0; i < wordCount-1; i++)
    {
        //printf("%s %d\n",words[i]->word,words[i]->weight);
        free(words[i]->word);
        free(words[i]);        
    }

   // printf("Freeing words infinity\n");
    //printf("%s %d\n",words[wordCount]->word,words[wordCount]->weight);
    // free(words[wordCount]); //free the item that stores the "infinity string"

    //printf("Freeing queries\n");
    for(int i = 0; i < queryCount; i++)
        free(queries[i]);

    //printf("Freeing locations\n");
    free(locations);
    //printf("complete\n");
    return 0;
}

void mergeSort(Item **array, int n, int sort_type)
{
  mergeSortRec(array, 0, n-1, sort_type);
}

void mergeSortRec(Item **array, int start, int stop, int sort_type)
{

  if(start >= stop)
      return;

  int middle;
  middle = start + floor((stop - start) / 2);
  mergeSortRec(array, start, middle, sort_type);
  mergeSortRec(array, middle + 1, stop, sort_type);
  merge(array, start, middle, stop, sort_type);

}

void merge(Item **array, int start, int middle, int stop, int sort_type)
{
    int a_length = (middle+1) - start;
    int b_length = stop - middle;
    int i;
    int j;
    
    //Represent infinity for merge sort as a high ascii value character unlikely to be used in a word
    char *inf = "éé";
    
    //Initialize lists
    Item **a;
    a = (Item **)malloc((sizeof(*a) * a_length) + 1); //plus one to append infinity

    for(i = 0; i < (a_length+1); i++)
    {
         a[i] = (Item *)malloc(sizeof(Item));    
    }
    
    Item **b;
    b = (Item **)malloc((sizeof(*b) * b_length) + 1);
    for(i = 0; i < (b_length+1); i++)
    {
         b[i] = (Item *)malloc(sizeof(Item));    
    }

    for(i = 0; i < a_length; i++)
    {
        a[i]->word = array[start+i]->word;
        a[i]->weight = array[start+i]->weight;
    }
    
    a[a_length]->word = inf;
    
    for(i = 0; i < b_length; i++)
    {
        b[i]->word = array[middle+1+i]->word;
        b[i]->weight = array[middle+1+i]->weight;
    }
    
    b[b_length]->word = inf;
    
    i = 0;
    j = 0;
    
    //0 to sort by words, 1 to sort numbers in descending order
    if(sort_type == 0)
    {
        for(int k = start; k <= stop; k++)
        {
            //printf("%s\n", array[k]->word);               
            //Word goes first condition
            if(strcmp(a[i]->word, b[j]->word) <= 0)
            {   
                array[k]->word = a[i]->word;
                array[k]->weight = a[i]->weight;
                i++;
            }
            else
            {
                array[k]->word = b[j]->word;
                array[k]->weight = b[j]->weight;
                j++;
            }
            //printf("%s\n", array[k]->word);   

        }
    }
    else if(sort_type == 1)
    {
        for(int k = start; k <= stop; k++)
        {
            if(a[i]->weight >= b[j]->weight)
            {   
                array[k]->word = a[i]->word;
                array[k]->weight = a[i]->weight;
                i++;
            }
            else
            {
                array[k]->word = b[j]->word;
                array[k]->weight = b[j]->weight;
                j++;
            }            
        }        
    }

    //Free a
    for(i = 0; i < (a_length+1); i++)
    {
         a[i] = (Item *)malloc(sizeof(Item));    
    }

    //Free b
    for(i = 0; i < (b_length+1); i++)
    {
         b[i] = (Item *)malloc(sizeof(Item));    
    }

}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/*
To-Do List
 1. Open given file
    i. command line arg 2
 2. Take in file, scan in 1 of 2 ways
    i. use fgets & strtok to get lines, then sort for words
    ii. use fscanf to scan lines directly
 3. *part 1* Take scanned words, format into a file with length = command line arg 1
    i. doesnt end with space, ends with new line
    ii. formats into "normal" looking text
 4. *part 2* Takes instances of words, sorts them, and displays number of times that instance is found
    i. use qsort to stort
    ii. needs to have some sort of counter, variable or addition of times idk. 
 5. these are in 2 seperate output files, one is .out, other is .words
*/
/*void read(){ 
   char buf[100];
   fgets(buf, sizeof(buf), file);


} */
void dict_factory(char *buf2, FILE *wordsFile){
/*char **wordlist = malloc(sizeof(char*));  pointer to pointer to words 
    int  i, numwords = 0;
    char *testwords[] = { "hello", "there", "folks", "in", "1840" };
    wordlist[0] = strdup( testwords[0]);

     This will show how you can add words to the array of pointers 
    for( i = 1; i < sizeof( testwords ) / sizeof( testwords[ 0 ] ); i++ )
    {
         Expand our array of pointers by one pointer's worth 
        wordlist = realloc( wordlist, (numwords + 1) * sizeof( char * ) );
         Make a duplicate of the word and save the pointer to it 
        wordlist[ numwords ] = strdup( testwords[ i ] );
        numwords++;
    }

    printf( "Added %d words to the array and they are:\n", numwords );
    for( i = 0; i < numwords; i++ )
        printf( "%s\n", wordlist[ i ] );
*/
}


void word_factory(char *buf, int lineLength, FILE *outFile){ /*creates words*/
   static int wordLength;
   static int outputLength;
   static char lineBuf[101] = "";
   static char space[2] = " ";

   if (buf == NULL){
      fprintf(outFile, "%s\n", lineBuf);
      return;
   }

   wordLength = strlen(buf);
   outputLength = strlen(lineBuf);

   if((wordLength + outputLength ) <= lineLength ){ /* concatonates words to buffer, needs to not have space at the end */
      if (outputLength != 0){
         strcat(lineBuf, space);
      }
      strcat(lineBuf, buf);
      /*if((wordLength + outputLength) < lineLength){
         strcat(lineBuf, space);
      }*/
      
   } else {
      fprintf(outFile,"%s\n",lineBuf);
      strcpy(lineBuf, buf);
   }
}

int main(int argc, char **argv){
   char buf[100];
   int lineLength = atoi(argv[1]);
   char lineName[100] = "";
   char lineName2[100] = "";
   char *buf2; 
   FILE *file;
   FILE *outFile;
   FILE *wordsFile;

   sprintf(lineName, "%s.out", argv[2]);
   sprintf(lineName2, "%s.words", argv[2]);
   if(argc != 3){  /*check for proper arg length*/
      printf("Function Lacks Enough Arguments, Use (./file, number of lines, input file)\n");
      exit(1);
   }

   

   file = fopen(argv[2], "r"); /* open file */

   if(file == NULL){
      printf("Could Not Open File, check spelling\n");
   } else {
      outFile = fopen(lineName, "w+");
      wordsFile = fopen(lineName2, "w+");

      while ((fscanf(file, "%s", buf)) > 0) {
         if (buf[0] == '\x03')
         {
          continue; 
         }
         strcpy(buf2,buf);
         word_factory(buf, lineLength, outFile);
         dict_factory(buf2, wordsFile);
      }
      word_factory(NULL,lineLength, outFile);
   }
   return 0;
}



/*for i < strlen(array) 
if string compare == 0 {
   counter = 1
   fprintf(the string, the counter, newline)

} else {
   counter++
   i++
}    {1,1,2,3,4,5,5,5,5,6,6,6,6,7,7,8}
     {1,"",2,3,4,"","","",5,"","","",6,"",7,8}
     if i != NULL, print i and counter*/
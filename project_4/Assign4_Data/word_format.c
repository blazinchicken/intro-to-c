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
void dict_factory(){

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
         word_factory(buf, lineLength, outFile);
         dict_factory();
      }
      word_factory(NULL,lineLength, outFile);
   }
   return 0;
}
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
char **wordlist;
int numwords = 0;

void dict_factory(char *buf2){
   if(numwords == 0){
      wordlist[numwords] = strdup(buf2);
   }
   wordlist = realloc(wordlist, (numwords + 1) * sizeof(char *));
    /*fprintf(wordsFile, "%s\n", wordlist[numwords]);*/
   if(numwords > 0){
      wordlist[numwords] = strdup(buf2);
   }
   numwords++;
}
static int cmp_str(const void *one, const void *two){
   unsigned char oneAdd, twoAdd;
   const unsigned char *onePT;
   const unsigned char *twoPT;
   int oneCapital, twoCapital;
   int comp;


   onePT = *((const unsigned char **) one);
   twoPT = *((const unsigned char **) two);
   
   comp = strcasecmp((const char *)onePT,(const char *)twoPT);
   if(comp != 0){
      return comp;
   }

   do {
      oneCapital = 1;
      twoCapital = 1;

      oneAdd = (unsigned char) *onePT++; /* lower case  = 97-122, upper case = 65 - 90*/
      twoAdd = (unsigned char) *twoPT++;

      if (oneAdd == '\0'){
         return oneAdd - twoAdd;
      }
      if(oneAdd >= 97 && oneAdd <= 122){
         oneAdd = oneAdd - 32;
         oneCapital = 0;
      }
      if(twoAdd >= 97 && twoAdd <= 122){
         twoAdd = twoAdd - 32;
         twoCapital = 0;
      }                                   
      if((oneAdd == twoAdd) && (oneCapital != twoCapital)){
         return twoCapital - oneCapital;
      }


   } while (oneAdd == twoAdd); 
   return oneAdd - twoAdd;
}    


void sort_factory(char **wordlist, int numwords) {
   qsort(wordlist, numwords, sizeof(wordlist[0]), cmp_str);
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
   char buf2[100];
   int i;
   FILE *file;
   FILE *outFile;
   FILE *wordsFile;

   wordlist = malloc(sizeof(char*));

   sprintf(lineName, "%s.out", argv[2]);
   sprintf(lineName2, "%s.words", argv[2]);
   if(argc != 3){  /*check for proper arg length*/
      printf("Function Lacks Enough Arguments, Use (./file, number of lines, input file)\n");
      exit(1);
   }

   

   file = fopen(argv[2], "r"); /* open file */

   if(file == NULL){
      printf("Could Not Open File, check spelling\n");
      exit(1);
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
         dict_factory(buf2);
         
      }
      sort_factory(wordlist, numwords);
      for(i=0;i<numwords;i++){
         fprintf(wordsFile,"%s\n",wordlist[i]);
      }
      word_factory(NULL, lineLength, outFile);
   }
   
   return 0;
}



/*for i < strlen(array) 
if string compare != 0 {
   
   fprintf(the string, the counter, newline)
   counter = 1
   
} else {
   counter++
   i++
}    {1,1,2,3,4,5,5,5,5,6,6,6,6,7,7,8}
     {1,"",2,3,4,"","","",5,"","","",6,"",7,8}
     if i != NULL, print i and counter*/
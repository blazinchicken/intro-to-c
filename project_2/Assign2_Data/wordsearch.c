#include <stdio.h>
#include <string.h>

#define MAX_NUM_WORDS 1000
#define MAX_WORD_LENGTH 50

void Word_List(char words)
  {
int j = 0;
int numWords = 0;
char c;
char word[MAX_WORD_LENGTH];
while((c = fgetc(stdin)) != EOF){
  if(c == '\n')
  {
    word[j] = '\0';
    strcpy(words[numWords],word);
    numWords++;
    j = 0 ;
  }
  else {
    word[j] = c;
    j++;
  }
}
word[j] = '\0';
strcpy(words[numWords], word);
numWords++;

}

int main(void) {
	char buf[50];
	int len;
	int i = 1;
	int half;

	fgets(buf, sizeof(buf), stdin);

	len = strlen(buf);
	half = (len - 1) / 2;
	
	char crossword[half][len];
  char words[MAX_NUM_WORDS][MAX_WORD_LENGTH];
	strcat(crossword[0], buf);

	while(fgets(buf, sizeof(buf), stdin) != NULL && i < half) {
		/*printf("%s", buf); */
		strcat(crossword[i], buf);
		i++;
		memset(&buf, 0, sizeof(buf));

	}
	printf("%s", crossword);
  Word_List(words);
}
/*
int get_charlist()
{
int j = 0
char * lines = strtok(buf,"\n");
char * letter = strtok(lines," ");
while (letter!=NULL){
  j=j+1;
  letter = strtok(NULL," ");
}

}
*/


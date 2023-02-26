#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_COUNT 100

int len = 0;
int half = 0;
char buf[50];
int i = 1;
int k = 0;
int j;
int l;
char **crossword;
char **key;

void setup() {

	fgets(buf, sizeof(buf), stdin);
	len = strlen(buf);
	half = (len - 2) / 2;
	crossword = malloc(half * sizeof(char*));
	for(j = 0; j <= half; j++) {
		crossword[j] = malloc((len+1) * sizeof(char));
	}
	strcat(crossword[0], buf);

	key = malloc(WORD_COUNT * sizeof(char*));
	for(l = 0; l < WORD_COUNT; l++) {
		key[l] = malloc((len+1) * sizeof(char));
	}
}

int main() {
	setup();

	while(fgets(buf, sizeof(buf), stdin) != NULL && i < half) {/* && i < half) {*/
		/*
		if(i == half) {
			strcat(key[0], buf);
			k++;
			memset(&buf, 0, sizeof(buf));
			break;
		}
		*/
		
		strcat(crossword[i], buf);
		printf("%s", crossword[i]);
		i++;
		memset(&buf, 0, sizeof(buf));

	}

	while(fgets(buf, sizeof(buf), stdin) != NULL && k < WORD_COUNT) {
		strcat(key[k], buf);
		printf("%s", key[k]);
		k++;
		memset(&buf, 0, sizeof(buf));
	}	
	
	/*
	printf("%s", crossword[14]);
	printf("%s", key[0]);
	*/


}
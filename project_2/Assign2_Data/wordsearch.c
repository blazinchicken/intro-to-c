#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_COUNT 100

int length = 0;
int gridsize = 0;
int column = 0;
char buf[110];
int i = 1;
int k = 0;
int j;
int l;
char crossword[50][50];

void setup() {
 int row;
 int lineChar;

  for(i = 0; i < 50; i++)
  {
    for(j = 0; j < 50; j++)
    {
      crossword[i][j] = " ";
    }
  }

	fgets(buf, sizeof(buf), stdin);
	length = strlen(buf);
	gridsize = (length) / 2;
	
  for(row = 0; row < gridsize; row++)
  {
    column = 0;
    for(lineChar = 0; lineChar < length; lineChar++)
    {
      if ((lineChar % 2) == 0)
      {
        crossword[row][column] = buf[lineChar];
        column++;
      }
    }
    if(row != (gridsize - 1))
    {
      fgets(buf, sizeof(buf), stdin);
    }
  }
  for(row = 0; row < gridsize; row++){
    printf("%s", crossword[row]); 
  }
}
	
	


	



int main() {
	setup();
  return 0;

	/*while(fgets(buf, sizeof(buf), stdin) != NULL && i < half) {/* && i < half) {*/
		/*
		if(i == half) {
			strcat(key[0], buf);
			k++;
			memset(&buf, 0, sizeof(buf));
			break;
		}
		
		
		strcat(crossword[i], buf);
		printf("%s", crossword[i]);
		i++;
		memset(&buf, 0, sizeof(buf));

	}

	while(fgets(buf, sizeof(buf), stdin) != NULL && k < WORD_COUNT) {
		
	}	
	
	/*
	printf("%s", crossword[14]);
	printf("%s", key[0]);
	*/


}
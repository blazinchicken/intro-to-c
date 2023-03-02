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
char crossSolution[50][50];
int row;
int deltaY[] = {-1,-1,-1,0,0,+1,+1,+1};
int deltaX[] = {-1,0,+1,-1,+1,-1,0,+1};



int singleSearch(char *word, int i){
		for(k=0;k < strlen(word);k++){ /*bugg*/
			if(word[k] != crossword[row + (deltaY[i] * k)][column + (deltaX[i] * k)]){
				return 0;
			}
		}
		return 1;
	}

	void copy(char *word, int i){
		for(k = 0; k < strlen(word); k++){ 
			crossSolution[row + (deltaY[i] * k)][column + (deltaX[i] * k)] = word[k];
		}
	}

void search(char *word){
	
	/*step 1: find first char of word in crossword array
	step 2: check each direction for same chars as word
	step 2a:  check full word in each direction
	step 2b: if full word matches, step 3
	step 3: transfer word to output array of space characters in direct position*/

	for(row = 0;row < gridsize; row++){
		for(column=0;column < gridsize;column++){
			if(crossword[row][column] == word[0]){
			/* step 2: start*/
				
				for(i=0;i < 8; i++){	
					singleSearch(word, i);
					if(singleSearch(word,i) == 1){
						copy(word,i);

					}
				}
			}
		} 
	}
}


void setup() {
 char space = ' ';
 int lineChar;

  for(i = 0; i < 50; i++)
  {
    for(j = 0; j < 50; j++)
    {
      crossword[i][j] = ' ';
	  crossSolution[i][j] = ' ';
    }
  }

	fgets(buf, sizeof(buf), stdin);
	length = strlen(buf) - 1;
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
      } else {
        crossword[row][column] = space;
      }
    }
    if(row != (gridsize - 1))
    {
      fgets(buf, sizeof(buf), stdin);
    }
  }
  for(row = 0; row < gridsize; row++){
   /* printf("%.50s", crossword[row]); */
  }
}


int main() {
	setup();
	while(fgets(buf, sizeof(buf), stdin) != NULL) {
		buf[strlen(buf) - 1] = '\0'; /*remove newline*/ 
		search(buf);

		
	}
	for(row = 0; row < gridsize; row++){
		for(column=0; column < gridsize; column++){
			printf("%c ", crossSolution[row][column]);
		}
		printf("\n"); 
	}	
	
	/*putc*/
  return 0;

	/*while(fgets(buf, sizeof(buf), stdin) != NULL && i < half) { && i < half) {
		
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

	
		
	}	
	
	
	printf("%s", crossword[14]);
	printf("%s", key[0]);
	*/


}
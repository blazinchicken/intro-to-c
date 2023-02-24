#include <stdio.h>
#include <stdlib.h>

#define MAXRANGE 50

char array1[MAXRANGE][MAXRANGE];

int get_array()
{
  int i;
  int j;
  int count = 50;

  for(i = 0;i < count; i++){
    scanf("%c", &array1[i]);
    j++;
  }
  printf("%s", array1);
  printf("%d", j);
}

int main(void)
{
    FILE* f;
    get_array();
}

#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 1
#define RESIZE_FACTOR 2
#define LIMIT 10001

void resize(int** array, int* size);

int main() {
  int size = START_SIZE;
  int* primeTable = malloc(sizeof(int) * size);
  for (int i = 0; i < size; i++) 
    primeTable[i] = i;
  
  int p;
  for (int foundPrimes = 0; foundPrimes < LIMIT; p = 2) {
    while (p <= size) {
      for (int marker = 2 * p; marker < size; marker += p)
        primeTable[marker] = -1;
      while (++p < size && primeTable[p] == -1);
    }
    for (int i = 2, foundPrimes = 0; i < size; i++)
      if (primeTable[i] != -1)
        if (++foundPrimes == LIMIT) {
          printf("%d\n", primeTable[i]);
          free(primeTable);
          exit(0);
        }
    resize(&primeTable, &size);
  }
}

void resize(int** array, int* size) {
  int* oldArray = *array;
  int oldSize = *size;
  int newSize = oldSize * RESIZE_FACTOR;
  int* newArray = malloc(sizeof(int) * newSize);
  for (int i = 0; i < newSize; i++)
    if (i < oldSize)
      newArray[i] = oldArray[i];
    else
      newArray[i] = i;
  
  free(oldArray);
  *array = newArray;
  *size = newSize;
}

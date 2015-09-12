#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 256
#define RESIZE_FACTOR 2
#define LIMIT 10001
#define INVALID 1
typedef unsigned long long indexT;

void resize(char** array, indexT* size);

int main() {
  indexT size = START_SIZE;
  char* primeTable = calloc(size, sizeof(char) * size);

  indexT p = 2;
  for (indexT foundPrimes = 0; foundPrimes < LIMIT; p = 2) {
    while (p <= size) {
      for (indexT marker = 2 * p; marker < size; marker += p)
        primeTable[marker] = INVALID;
      while (++p < size && primeTable[p] == INVALID);
    }
    for (indexT i = 2, foundPrimes = 0; i < size; i++)
      if (primeTable[i] != INVALID)
        if (++foundPrimes == LIMIT) {
          printf("%d\n", i);
          free(primeTable);
          exit(0);
        }
    resize(&primeTable, &size);
  }
}

void resize(char** array, indexT* size) {
  char* oldArray = *array;
  indexT oldSize = *size;
  indexT newSize = oldSize * RESIZE_FACTOR;
  char* newArray = malloc(sizeof(char) * newSize);
  for (indexT i = 2; i < oldSize; i++)
    newArray[i] = oldArray[i];
  
  free(oldArray);
  *array = newArray;
  *size = newSize;
}

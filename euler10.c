#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 6
#define RESIZE_FACTOR 2
#define LIMIT 2000000
#define INVALID 1
typedef unsigned long long indexT;

void resize(char** array, indexT* size);

int main() {
  indexT size = START_SIZE;
  char* primeTable = calloc(size, sizeof(char) * size);

  indexT p = 2;
  for (indexT sumPrimes = 0; ; p = 2) {
    while (p <= size) {
      for (indexT marker = 2 * p; marker < size; marker += p)
        primeTable[marker] = INVALID;
      while (++p < size && primeTable[p] == INVALID);
    }
    for (indexT i = 2, sumPrimes = 0; i < size; i++)
      if (primeTable[i] != INVALID)
        if (i >= LIMIT) {
          printf("%lld\n", sumPrimes);
          free(primeTable);
          exit(0);
        } else sumPrimes += i;
    resize(&primeTable, &size);
  }
}

void resize(char** array, indexT* size) {
  char* oldArray = *array;
  indexT oldSize = *size;
  indexT newSize = oldSize * RESIZE_FACTOR;
  char* newArray = calloc(newSize, sizeof(char) * newSize);
  for (indexT i = 2; i < oldSize; i++)
    newArray[i] = oldArray[i];
  
  free(oldArray);
  *array = newArray;
  *size = newSize;
}

#include <stdio.h>
#include <stdlib.h>
#define START_SIZE 12
#define RESIZE_FACTOR 2
#define LIMIT 10001
typedef unsigned intT;

void resize(intT** array, intT* size);

int main() {
  intT size = START_SIZE;
  intT* primeTable = malloc(sizeof(intT) * size);
  for (intT i = 2; i < size; i++)
    primeTable[i] = i;

  intT p;
  for (intT foundPrimes = 0; foundPrimes < LIMIT; p = 2) {
    while (p <= size) {
      for (intT marker = 2 * p; marker < size; marker += p)
        primeTable[marker] = 0;
      while (++p < size && primeTable[p] == 0);
    }
    for (intT i = 2, foundPrimes = 0; i < size; i++)
      if (primeTable[i] != 0)
        if (++foundPrimes == LIMIT) {
          printf("%d\n", i);
          free(primeTable);
          exit(0);
        }
    resize(&primeTable, &size);
  }
}

void resize(intT** array, intT* size) {
  intT* oldArray = *array;
  intT oldSize = *size;
  intT newSize = oldSize * RESIZE_FACTOR;
  intT* newArray = malloc(sizeof(intT) * newSize);
  for (intT i = 2; i < newSize; i++)
    if (i < oldSize)
      newArray[i] = oldArray[i];
    else
      newArray[i] = i;
  
  free(oldArray);
  *array = newArray;
  *size = newSize;
}

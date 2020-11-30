#include <stdio.h>
#include <stdlib.h> //rand(), srand();
#include <time.h>   //time()
#include <string.h> //memset()
#define SIZE 6
void mkArr(int *arr, int size)
{
  int cnt = 0;
  int *test = new int(size);
  for (size_t i = 0; i < size; i++)
  {
    test[i]=0;
  }
  
  srand(time(NULL));
  while (cnt < size)
  {
    int num = rand() % size;
    if (test[num] == 0)
    {
      test[num] = 1;
      arr[cnt] = num;
      cnt++;
    }
  }
}
int main()
{
  int arr[SIZE];
  mkArr(arr, SIZE);
  for (int i = 0; i < SIZE; i++)
  {
    printf("%d\n", arr[i]);
  }
  return 0;
}
#include <stdio.h>
#include <cs50.h>

void print(int n);

int main(){
  int height = get_int("Height: ");
  print(height);
  return 0;
}

void print(int n){
  if (n <= 0)
    return;
  
  print(n - 1);
  
  for (int i = 0; i < n; ++i)
    printf("#");
  
  printf("\n");
}

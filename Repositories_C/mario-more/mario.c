//1.创建 n 行，当前 i 行。2.第一个 # 前面的空格 n - i 个（这里的循环可以直接复用 mario-less 中的代码） + i 个 # + 固定2个空格 + i 个 #.

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int layer;
    int number_space;
    
    do
    {
        layer = get_int("Layer: ");
    }
    while (layer <= 0 || layer > 8);
    
    for (int i = 1; i <= layer ; i++)
    {
        number_space = layer - i;
        
        for (int j = 1; j <= number_space; j++)
        {
            printf(" ");
        }
        
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }
        
        printf("  ");
        
        for (int h = 1; h <= i; h++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}

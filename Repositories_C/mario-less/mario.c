#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //检查输入值n是否大于0
    int layer;
    int number_space;
    
    do
    {
        layer = get_int("Layer: ");
    }
    while (layer <= 0);
    
    //根据输入值，令最终行数为 n, 目前行为 i, 第一行到 n 进行递增，递增值为1，前面的空格为 n - i。使用嵌套 for loop，外层控制几行，内层控制几个空格和#.
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
        
        printf("\n");
    }
}

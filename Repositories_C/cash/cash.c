#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // 检查输入是否是非整数或负数
    int owed;
    int coins = 0;
    
    do
    {
        owed = get_int("Chande owed: ");
    }while( owed < 0 );
    
    // 计算找零硬币的最少数量。面额 25,10,5,1. 用for 循环遍历，可以用25找就用25，以此类推。
    
    while (owed >= 25)
    {
        owed -= 25;
        coins++;
    }
    
    while( owed >= 10 )
    {
        owed -= 10;
        coins++;
    }
    
    while( owed >= 5 )
    {
        owed -= 5;
        coins++;
    }
    
    while( owed >= 1 )
    {
        owed -= 1;
        coins++;
    }
    
    printf("%i\n",coins);
    return 0;
}

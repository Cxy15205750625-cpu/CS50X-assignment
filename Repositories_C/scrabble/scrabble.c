#include <stdio.h>
#include <cs50.h>
#include <ctype.h>  // toupper
#include <string.h> // strlen

// 将字母与字母对应的值建立映射(array)
int points[26] = {
1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
};
int compute_score(string word);
void result(int s1, int s2);

int main(void)
{
    // 获取两个玩家的输入（字符串）
    string player_1 = get_string("Player1: ");
    string player_2 = get_string("Player2: ");

    //获取输入字符串的值
    int score1 = compute_score(player_1);
    int score2 = compute_score(player_2);

    //compare the values, finally output the result.
    result(score1, score2);

    return 0;
}

// 计算单个玩家的分数
int compute_score(string word)
{
    int score = 0;
    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        char letter = toupper(word[i]);

        // 只处理英文字母
        if (letter >= 'A' && letter <= 'Z')
        {
            int index = letter - 'A';
            score += points[index];
        }
    }

    return score;
}

void result(int s1, int s2)
{
    if (s1 > s2)
    {
        printf("Player1 wins! \n");
    }
    else if (s1 < s2)
    {
        printf("Player2 wins! \n");
    }
    else
    {
        printf("Tie! \n");
    }
}

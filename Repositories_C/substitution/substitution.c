// 1.通过读取命令行参数，建立 A-Z 密钥的连续映射。2.检查密钥是否符合要求。3.检查通过后获取想要加密的文本。4.用一开始建立的映射进行加密
#include <stdio.h>
#include <cs50.h>
#include <string.h> // strlen()
#include <ctype.h>  // isalpha()、toupper()、tolower()
#include <stdbool.h>

bool check(int argc, string argv[]);
void map(char key[]);

int main(int argc, string argv[]){
    if (!check(argc, argv)){
        return false;
    }
    
    map(argv[1]);
    return 0;
}

bool check(int argc, string argv[]){
    // 获取加密规则
    string key = argv[1];
    
    // 1. 检查 argc 是否等于 2
    if (argc != 2)
      {
        printf("Usage: ./substitution key\n");
        return false;
    }

    // 2. 检查 argv[1] 的长度是否等于 26
    int length = strlen(key);
    if (length != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    // 3. 检查 argv[1] 中是否全部为英文字母
    for (int i=0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }
    }

    // 4. 检查是否有重复字母
    bool seen[26] = {false}; // create a bool arrays
    for (int i = 0; i < length; i++)
    {
        int index = toupper(key[i]) - 'A'; // 算下标建立索引，在循环执行26次的时候，每一个字母都有了一个下标。

        if (seen[index])
        {
            printf("Key must not contain repeated characters.\n");
            return false;
        }

        seen[index] = true; // 改索引的布尔值，如果没有重复，则所有的字母都只会被改“1”遍，都变成true，但如果重复了，就说明已经被改成过 true 了，那么就是第二次遇到，所以就有了我们上面的 if 语句.
    }

    // 5. 全部通过后，开始获取明文
    return true;
}

// 将 plaintext 转换为加密后的字符
void map(char key[]){
    string plaintext = get_string("Plaintext: ");
    int length = strlen(plaintext);
    printf("ciphertext: ");

    for (int i = 0; i < length; i++){
        char c = plaintext[i];

	if (isalpha(c)){
	  int index = toupper(c) - 'A';
	  char new_c = key[index];

	  if (isupper(c)){
	    printf("%c", toupper(new_c));
	  }
	  else{
	    printf("%c", tolower(new_c));
	  }
	}
	else{
	  printf("%c", c);
	}	  
    }
    printf("\n");
}

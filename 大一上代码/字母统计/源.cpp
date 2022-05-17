#include <iostream>
using namespace std;
int main()//数组及变量定义;
{
    const int N = 80;
    char buffer[N];
    int k = 0;
    const int NUM = 26;
    int counts[NUM] = { 0 };
    char letters[NUM];
    int i = -1;
    int j = 0;
    int n;
    cin >> n;
    cin.getline(buffer, N);
    do    //循环输入每一行字符
    {
        cin.getline(buffer, N); //获得一行输入字符串
        k = 0;
        while (buffer[k] != '\0')//对于输入的每一行字符，统计字符出现的次数
        {
            if (tolower(buffer[k]) >= 'a' && tolower(buffer[k]) <= 'z')
            {
                i = tolower(buffer[k]) - 'a';
                counts[i]++;
            }
            k++;
        }
        j++;
    } while (j != n);
    if (i == -1)
        cout << "字符串中无字母。" << endl;
    else
    {
        for (i = 0; i < NUM; i++)//输出统计结果
        {
            letters[i] = (char)('a' + i);
            if (counts[i] > 0)
            {
                cout << letters[i] << ":" << counts[i] << endl;
            }
        }
    }
}
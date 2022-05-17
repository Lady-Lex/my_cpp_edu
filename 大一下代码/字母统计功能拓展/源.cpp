//要求：输入一字符串，统计字符种类数（不包括终止符），字符权值以及出现的字符的内容。
#include <iostream>
using namespace std;
int main()
{
    //数组及变量定义;
    const int N = 100;
    char buffer[N];
    int k = 0;
    const int NUM = 127;
    int counts[NUM] = { 0 };
    char letters[NUM];
    int j = 0;
    int n;
    cin >> n;                                        //要输入的行数
    cin.getline(buffer, N);
    do                                               //循环输入每一行字符
    {
        cin.getline(buffer, N);                      //获得一行输入字符串
        k = 0;
        while (buffer[k] != '\0')                    //对于输入的每一行字符，统计字符出现的次数
        {
            counts[buffer[k]]++;
            k++;
        }
        j++;
    } while (j != n);
    for (int i = 0; i < NUM; i++)                        //输出统计结果
    {
        letters[i] = (char)i;
        if (counts[i] > 0)
        {
            cout << letters[i] << ":" << counts[i] << endl;
        }
    }
}
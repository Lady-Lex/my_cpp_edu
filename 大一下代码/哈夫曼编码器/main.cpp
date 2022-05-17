#include<iostream>
#include"Head.h"
using namespace std;

int main()
{
    {
        //1.编码
        cout << "步骤1：编码" << endl;
        const int ArSize = 1000;
        char buffer[ArSize];                              //数组Buffer用来储存输入的字符串
        cout << "请输入原字符串(不能只含一种字符，否则不存在对应的哈夫曼树）：" << endl;
        cin.get(buffer, ArSize).get();                    //读入
        //cout << buffer;
        int k = 0;
        const int NUM = 127;                              //127个ASCII字符
        int counts[NUM] = { 0 };                          //数组counts用来统计所有ASCII字符出现次数
        int Counts[NUM] = { 0 };                          //数组Counts用来统计字符串中出现的字符出现次数
        char letters[NUM];                                //数组letters用来储存所有ASCII字符
        char Letters[NUM];                                //数组Letters用来储存字符串中出现的字符
        k = 0;                                            //循环控制变量
        while (buffer[k] != '\0')                         //对于输入的每一行字符，统计字符出现的次数
        {
            counts[buffer[k]]++;
            k++;
        }
        int C = -1;                                       //计数器，统计字符的种类数
        for (int i = 0; i < NUM; i++)                     //输出统计结果
        {
            letters[i] = (char)i;
            if (counts[i] > 0)
            {
                Counts[++C] = counts[i];
                Letters[C] = letters[i];
                cout << "字符\"" << Letters[C] << "\"的权值:" << Counts[C] << endl;
            }
        }
        //cout << C << endl;                              //以上步骤用于计算字符种类数，权值
        Huffman media;
        media.CreateHTree(Counts, C + 1, Letters);
        media.CreateCodeTable();
        //cout << "哈夫曼树的形状：" << endl;
        //media.print(Counts, 2 * C, 2);
        string Result;
        media.Encode(buffer, Result);
        cout << endl;
        cout << "生成的编码串为：" << endl;
        cout << Result << endl;
        cout << "原字符串的ASCII编码串占据的内存为：" << 8 * k << "bit" << endl;
        cout << "原字符串的哈夫曼编码占据的内存为：" << Result.length() << "bit" << endl;
        system("pause");

        //2.解码
        cout << "步骤2：解码" << endl;
        cout << "请根据已建立的编码表输入有效编码串：" << endl;
        media.CreateCodeTable();
        cin.get(buffer, ArSize).get();
        char result[ArSize];
        media.Decode(buffer, result);
        cout << "对应的原字符串为：" << endl;
        cout << result << endl;
    }
}
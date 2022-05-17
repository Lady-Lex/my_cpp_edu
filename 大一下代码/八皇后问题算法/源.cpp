#include <iostream>
using namespace std;

//递归算法解决八皇后问题。总共有92种解法。

const int Scale = 16;                      //棋盘规模
int position[Scale] = { 0 };              //存储行和列数据的数数组，用下标存储行序数，数组元素的值存储列序数
namespace exact                           //计数器。直接使用count变量似乎会引起二义性冲突，故使用名称空间
{
    static int count = 0;
}

void print();

/*算法实现思想：设置第0行的某个元素为皇后，从下一行开始/寻找/不与/前面所有行的已摆放位置/相冲突/的位置/的列序数，直到遍历所有行。
                当最有一行遍历完后，将会调用search(Scale)，这是将会使计数器加一并结束search(Scale)，并依次结束search(Scale-i) （i=1,2…7),
                至此，一次递归结束。
                重复上述操作，直到遍历0行所有元素。
*/
void search(int row = 0)               
{
    if (row == Scale)
    {
        print();
        ++exact::count;
        return;                           
        //return是必须的，因为用的是递归算法。如果没有return，编译器似乎会在第一次执行完函数体最后一句后终止函数
        //若无return，这里的具体结果为：search(Scale)运行到此处后，继续运行下面的语句，不可能找到正确的位置，故search(Scale)无法再使递归继续，search()第一次递归一次结束，包括search(0)。
    }

    for (int col = 0; col < Scale; col++)
    {
        position[row] = col;
        int _bool = 1;
        for (int prerow = 0; prerow < row; prerow++)              //j不可能等于row，故显然两个皇后一定不同行
        {
            if (position[row] == position[prerow] || row - prerow == position[row] - position[prerow] || row - prerow == position[prerow] - position[row])
                //第一个用于判断两皇后是否在同一列，第二、三个用于判断两皇后是否在同一斜边
            {
                _bool = 0;
                break;
            }
        }
        if (_bool)                         //在当前行中找到一个满足条件的列序数，才能进入下一行的位置搜寻
            search(row + 1);
    }
}

void print()
{
    for (int i = 0; i < Scale; i++)
    {
        for (int j = 0; j < Scale; j++)
        {
            if (j == position[i])
                cout << "1 ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    search();
    cout << "共有" << exact::count << "种摆放方法。" << endl;
    return 0;
}
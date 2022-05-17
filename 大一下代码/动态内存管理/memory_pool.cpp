#include<iostream>
using namespace std;

struct BlockBorder                              //块边界结构
{
	int BlockLength;
	bool free() { return BlockLength > 0 ? true : false; }
	int MemorySize() { return BlockLength > 0 ? BlockLength : -BlockLength; }
	int BlockSize() { return MemorySize() + 2 * sizeof(BlockBorder); }
};

struct FreeBlockHead :public BlockBorder        //空闲块头
{
	FreeBlockHead* prior;                       //指向前一个空闲块
	FreeBlockHead* next;                        //指向后一个空闲块
};

class MemoryPool                                //内存池类
{
public:
	MemoryPool(unsigned int size);              //构造函数
	~MemoryPool();                              //析构函数
	void* Allocate(int size);                   //动态分配内存
	void Free(void* p);                         //释放被分配的内存
private:
	char* m_Base;                               //内存池的基址
	unsigned int m_PoolSize;                    //内存池的空间大小
	FreeBlockHead* m_First;                     //起始空闲块
private:                                        //以下函数需要被其他函数所调用
	void InsertFreeBlock(void* p, int size);    //设置空闲块并插入空闲块链表中
	void SetUsedBorder(void* p, int size);      //设置占用块
	void DeleteFreeBlock(FreeBlockHead* p);     //将空闲块从空闲块链表中删除
	BlockBorder* GetPreBlock(void* p);          //得到已分配的内存地址p所在块的前一内存块地址
	BlockBorder* GetNextBlock(void* p);         //得到已分配的内存地址p所在块的后一内存块地址
	BlockBorder* GetCurrentBlock(void* p);      //得到已分配的内存地址p所在占用块的地址
};



MemoryPool::MemoryPool(unsigned int size)
{
	if(!m_First)
	{
		m_PoolSize = size;

    }
	else
	{
		cout << "失败！内存池只能建里一次！" << endl;
	}
}

MemoryPool::~MemoryPool()
{

}

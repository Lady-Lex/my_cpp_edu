//分析 : 将顺序表的第一个元素与最后一个元素互换，第二个元素与倒数第二个元素互换。
void Sqlist(Sglist A)
{
	for (i = 0; i < ((A.last - 1) / 2); i++_)
		{
			x = A.data[i];
			A.data[i] = A.data[A.last - i - 1];
			A.data[A.last - i - 1] = x;
		}
}
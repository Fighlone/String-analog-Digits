/**************************************************************************************
*			字符串模拟数字及其(有限）四则运算
*			版本1.0
*			开发时间:2020/10/24-2020/10/25
* 开发者留言：
*			尽量别搞奇怪的数字或者其他字符串输入，在下实在没时间完善这个东西，
*			还有使用函数的话尽量使用标准char[CH]的数字字符串，
*	        不要拿"12513"这样的字符串当参数，除了我。
*			另外所有函数是不支持小数的，只有求商函数生成小数，只是应付作业，没空优化实*			在不好意思。
*            算法很烂，输入太大你可能一辈子都等不到答案。
***************************************************************************************/
#include<stdio.h>
#define CH 128 //数字的最大位数

void Negate(char*);
int is_positive(char*);
void Swap(char*, char*);
int Comp(char*, char*);
void Subtraction(char*, char*);//正整数数减法,结果可为负
void Sum(char*, char*);        //整数加法  发现为了交作业的话完全用不到！！！！！
void MultiplyTen(char* digit);//整数乘10
void Quotient(char*, char*);
void Remainder(char*, char*);

void main()
{
	printf("请输入两个整数（请不要输入奇怪的东西)：\n");
	char digit1[CH], digit2[CH], digit3[CH],digit4[CH],digit5[CH];//用字符串模拟数字
	gets_s(digit1, CH);
	gets_s(digit2, CH);
	int w = -1;
	while (digit1[++w] != '\0');
	while (w >= 0) { digit3[w] = digit1[w]; digit4[w] = digit1[w]; digit5[w] = digit1[w--]; };
	Quotient(digit1, digit2);
	Remainder(digit3, digit2);
	Sum(digit4, digit2);
	Subtraction(digit5, digit2);
	printf("两数的商为:%s\n两数的余数为:%s\n两数的和为：%s\n,两数的差为%s\n", digit1, digit3,digit4,digit5);


}

void Negate(char* digit)//取负数 
{
	if (digit[0] == '0' && digit[1] == '\0') //这里曾经出现了一个忘记了小数的bug
		return;
	if (digit[0] == '-') //如果是负数则变成正数
	{
		int i = 0;
		while (digit[i] != '\0') { digit[i] = digit[i + 1]; ++i; }
	}
	else  //如果是正数则变成负数
	{
		int i = -1;
		while (digit[++i] != '\0'); //找到\0的位置
		while (i >= 0) { digit[i + 1] = digit[i--]; }
		digit[0] = '-';
	}
}//完成
int is_positive(char* digit)    //判断是否为正数
{
	if (digit[0] == '-')
		return 0;
	else
		return 1;
}//完成
void Swap(char* digit1, char* digit2)//交换数字值
{
	int i = -1, j = -1;
	while (digit1[++i] != '\0');
	while (digit2[++j] != '\0');
	char temp[CH];
	for (int m = 0; m <= i; ++m)      //此处曾经有一个神奇的bug
	{
		temp[m] = digit1[m];
	}
	for (int m = 0; m <= j; ++m)
	{
		digit1[m] = digit2[m];
	}
	for (int m = 0; m <= i; ++m)
	{
		digit2[m] = temp[m];
	}
}//完成
int Comp(char* digit1, char* digit2)  //比较两个正数的大小 若dig1>=dig2则返回1 
{
	int i = -1, j = -1;
	while (digit1[++i] != '\0');
	while (digit2[++j] != '\0');
	if (i > j) return 1;
	else if (i < j)return 0;
	for (i = 0; i < j; ++i)
	{
		if (digit1[i] < digit2[i]) return 0;//然后一个弱智的bug曾经来源于此
		else if (digit1[i] > digit2[i]) return 1;
	}
	return 1;
}//完成
void Subtraction(char* digit1, char* digit2)   //两个正数的减法 结果存入digit1中
{
	char temp[CH];
	int p = CH - 1;
	int i = -1, j = -1;
	int jinwei = 10;
	while (digit1[++i] != '\0');
	while (digit2[++j] != '\0');
	i--, j--;
	temp[p--] = '\0';
	if (Comp(digit1, digit2)) //第一个数大于第二个数字
	{
		while (i >= 0 && j >= 0)
		{
			if (jinwei / 10 == 1)
			{
				jinwei = digit1[i--] - digit2[j--] + 10;
				temp[p--] = jinwei % 10 + '0';
			}
			else
			{
				jinwei = digit1[i--] - digit2[j--] + 9;
				temp[p--] = jinwei % 10 + '0';
			}
		}
		while (i >= 0)
		{
			if (jinwei / 10 == 1)
			{
				temp[p--] = digit1[i--];
			}
			else
			{
				jinwei = digit1[i--] - '0' + 9;
				temp[p--] = jinwei % 10 + '0';
			}
		}
		p++;
		for (int k = 0; p <= CH - 1; ++p, ++k)
		{
			digit1[k] = temp[p];
		}
		//高位消0
		int m = 0;
		while (digit1[m] == '0') { m++; }
		if (digit1[m] == '\0') { digit1[0] = '0'; digit1[1] = '\0'; return; }
		int n = 0;
		while (digit1[m] != '\0')
		{
			digit1[n] = digit1[m];
			n++, m++;
		}
		digit1[n] = '\0';
	}//完成！
	else //第二个数字绝对值大于第一个数字
	{
		while (i >= 0 && j >= 0)
		{
			if (jinwei / 10 == 1)
			{
				jinwei = digit2[j--] - digit1[i--] + 10;
				temp[p--] = jinwei % 10 + '0';
			}
			else
			{
				jinwei = digit2[j--] - digit1[i--] + 9;
				temp[p--] = jinwei % 10 + '0';
			}
		}
		while (j >= 0)
		{
			if (jinwei / 10 == 1)
			{
				temp[p--] = digit2[j--];
			}
			else
			{
				jinwei = digit2[j--] - '0' + 9;
				temp[p--] = jinwei % 10 + '0';
			}
		}
		p++;
		digit1[0] = '-';
		for (int k = 1; p <= CH - 1; ++p, ++k)
		{
			digit1[k] = temp[p];
		}
		//高位消0
		int m = 1;
		while (digit1[m] == '0') { m++; }
		if (digit1[m] == '\0') { digit1[0] = '0'; digit1[1] = '\0'; return; }
		int n = 1;
		while (digit1[m] != '\0')
		{
			digit1[n] = digit1[m];
			n++, m++;
		}
		digit1[n] = '\0';
	}
} //完成
void Sum(char* digit1, char* digit2) //求和 存入digit1中
{
	char temp[CH];
	int p = CH - 1;
	if (digit1[0] != '-')
	{
		if (digit2[0] != '-')
		{
			int i = -1, j = -1;
			int jinwei = 0;
			while (digit1[++i] != '\0');
			while (digit2[++j] != '\0');
			i--, j--;
			temp[p--] = '\0';
			while (i >= 0 && j >= 0)
			{
				int cur = digit1[i--] + digit2[j--] - 2 * '0' + jinwei;
				temp[p--] = cur % 10 + '0';
				jinwei = cur / 10;
			}
			while (i >= 0)
			{
				int cur = digit1[i--] - '0' + jinwei;
				temp[p--] = cur % 10 + '0';
				jinwei = cur / 10;
			}
			while (j >= 0)
			{
				int cur = digit2[j--] - '0' + jinwei;
				temp[p--] = cur % 10 + '0';
				jinwei = cur / 10;
			}
			if (jinwei > 0)
			{
				temp[p--] = jinwei + '0';
			}
			p++;
			for (int k = 0; p < CH; ++p, ++k) //一包茶一杯烟一个bug找一天
			{
				digit1[k] = temp[p];
			}
		}
		else
		{
			Negate(digit2);
			Subtraction(digit1, digit2);
			Negate(digit2);
		}
	}
	else
	{
		if (digit2[0] == '-')
		{
			Negate(digit1);
			Negate(digit2);
			Sum(digit1, digit2);
			Negate(digit1);
			Negate(digit2);
		}
		else
		{
			Negate(digit1);
			Subtraction(digit1, digit2);//妙
			Negate(digit1);
		}
	}
}//基本完成
void MultiplyTen(char* digit)
{
	if (digit[0] == '0')
		return;
	int last = 0;
	while (digit[++last] != '\0');
	digit[last] = '0';
	digit[last + 1] = '\0';
}//完成
void Quotient(char* digit1, char* digit2)//求商 存入digit1中
{
	//具体思路：暴力减法，看减多少次数。
	if (digit1[0] == '0' || digit2[0] == '0')
		return;
	if (is_positive(digit1) && is_positive(digit2))
	{
		char res[CH] = "0";
		while (1)
		{
			Subtraction(digit1, digit2);
			if (digit1[0] == '0')//整除
			{
				Sum(res, "1");
				int y = -1;
				while (res[++y] != '\0');
				res[y] = '.';
				res[y + 1] = '0';
				res[y + 2] = '0';
				res[y + 3] = '\0';
				Swap(digit1, res);
				return;
			}
			if (is_positive(digit1))
				Sum(res, "1");
			else
				break;
		}
		int last = 0;
		while (res[++last] != '\0');
		res[last++] = '.';
		Sum(digit1, digit2);
		int t = 0;
		MultiplyTen(digit1);
		while (1)
		{
			Subtraction(digit1, digit2);
			if (!is_positive(digit1))
				break;
			++t;
		}
		res[last++] = t + '0';
		Sum(digit1, digit2);
		t = 0;
		MultiplyTen(digit1);
		while (1)
		{
			Subtraction(digit1, digit2);
			if (!is_positive(digit1))
				break;
			++t;
		}
		res[last++] = t + '0';
		Sum(digit1, digit2);
		t = 0;
		MultiplyTen(digit1);
		while (1)
		{
			Subtraction(digit1, digit2);
			if (!is_positive(digit1))
				break;
			++t;
		}
		res[last++] = t + '0';
		res[last--] = '\0';
		int jinwei = 0;
		if (res[last] - '0' >= 5)
			jinwei = 1;
		res[last] = '\0';
		int u = last - 1;
		if (jinwei)
		{
			jinwei += res[u] - '0';
			res[u--] = jinwei % 10 + '0';
			jinwei /= 10;
		}
		if (jinwei)
		{
			jinwei += res[u] - '0';
			res[u--] = jinwei % 10 + '0';
			jinwei /= 10;
		}
		u--;
		while (jinwei)//这个小数四舍五入的进位都到了整数就令人头秃
		{
			if (u >= 0)
			{
				jinwei += res[u] - '0';
				res[u--] = jinwei % 10 + '0';
				jinwei /= 10;
			}
			else
			{
				int r = -1;
				while (res[++r] != '\0');
				res[r + 1] = '\0';
				while (r > 0)
				{
					res[r] = res[r - 1];
				}
				res[0] = '1';
				break;
			}
		}
		Swap(digit1, res);
	}
	else if (!is_positive(digit1) && !is_positive(digit2))
	{
		Negate(digit1);
		Negate(digit2);
		Quotient(digit1, digit2);
		Negate(digit2);
	}
	else
	{
		if (is_positive(digit1))
		{
			Negate(digit2);
			Quotient(digit1, digit2);
			Negate(digit2);
			Negate(digit1);
		}
		else
		{
			Negate(digit1);
			Quotient(digit1, digit2);
			Negate(digit1);
		}
	}
}//就这样把
void Remainder(char* digit1, char* digit2)//求余数 存入digit1中
{
	if (digit2[0] == '0')
		return;
	if (digit1[0] == '0')
	{
		int q = -1;
		while (digit2[++q] != '\0');
		while (q >= 0)
		{
			digit1[q--] = digit2[q];
		}
		return;
	}
	if (is_positive(digit1) && is_positive(digit2))
	{
		while (1)
		{
			Subtraction(digit1, digit2);
			if (digit1[0] == '0')//整除
			{
				return;
			}
			if (!is_positive(digit1))
				break;
		}
		Sum(digit1, digit2);
	}
	else if (!is_positive(digit1) && !is_positive(digit2))
	{
		Negate(digit1);
		Negate(digit2);
		Remainder(digit1, digit2);
		Negate(digit1);
		Sum(digit1, digit2);
		Negate(digit2);
	}
	else
	{
		if (is_positive(digit1))
		{
			Negate(digit2);
			Remainder(digit1, digit2);
			Negate(digit2);
		}
		else
		{
			Negate(digit1);
			Remainder(digit1, digit2);
			Negate(digit1);
			Sum(digit1, digit2);
		}
	}
}

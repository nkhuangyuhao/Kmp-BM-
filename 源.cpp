#include<iostream>
#include<string>
#include<windows.h>
#include"time.h"
#include<cstring>
using namespace std;
int num1 = 0;
int num2 = 0;
int* getNext(string p)
{
	int* next = new int[p.length()];
	next[0] = -1;
	int j = 0;
	int k = -1;
	while (j < (int)p.length() - 1)
	{
		if (k == -1 || p[j] == p[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
	return next;
}
int KMP(string T, string p)
{
	int i = 0;
	int j = 0;
	int* next = getNext(p);
	while (i < (int)T.length() && j < (int)p.length())
	{
		if (j == -1 )
		{
			i++;
			j++;
		}
		else if(T[i] == p[j])
		{
			i++;
			j++;
			num1++;
		}
		else
		{
			j = next[j];
			num1++;
		}

	}
	if (j == (int)p.length())
	{
		return i - j;
	}
	return -1;
}
int Dist(string t, char ch)
{
	int len = t.size();
	int i = len - 1;
	if (ch == t[i])
		return len;
	i--;
	while (i >= 0)
	{
		if (ch == t[i])
			return len - 1 - i;
		else
			i--;
	}
	return len;
}

int BM(string s, string t)
{
	int n = s.size();
	int m = t.size();
	int i = m - 1;
	int j = m - 1;
	while (j >= 0 && i < n)
	{
		if (s[i] == t[j])
		{
			i--;
			j--;
			num2++;
		}
		else
		{
			i += Dist(t, s[i]);
			j = m - 1;
			num2++;
		}
	}
	if (j < 0)
	{
		return i + 1;
	}
	return -1;
}

int main()
{
	string T, p;
	cin >> T >> p;
	double ntime = 0,mtime=0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);
	KMP(T, p);
	QueryPerformanceCounter(&nEndTime);//Í£Ö¹¼ÆÊ±
	ntime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
	cout << KMP(T, p) << ' ' << num1 << endl;
	printf("%f ms", (ntime * 1000));
	LARGE_INTEGER mFreq;
	LARGE_INTEGER mBeginTime;
	LARGE_INTEGER mEndTime;
	QueryPerformanceFrequency(&mFreq);
	QueryPerformanceCounter(&mBeginTime);
	BM(T, p);
	QueryPerformanceCounter(&mEndTime);
	mtime = (double)(mEndTime.QuadPart - mBeginTime.QuadPart) / (double)mFreq.QuadPart;
	cout <<endl<< BM(T, p) << ' ' << num2 << endl;
	printf("%f ms", (mtime * 1000));
	return 0;
}




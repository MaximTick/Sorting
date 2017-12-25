/*Массив С отсортировать по возрастанию, используя алгоритмы сортировок пирамидальной, слиянием, Хоара.*/
#include "stdafx.h"
#include <ctime>             
#include <stdlib.h>
#include <iostream>
using namespace std;
/*Фаза 1: построение пирамиды
На каждом шаге добавляется новый элемент и  'просеивается' на свое место. 
При добавлении:
1. Новый элемент Х помещается в вершину дерева.
2. Из элементов слева и справа выбирается  наи-меньший.
3. Если этот элемент меньше Х, то он меняется ме-стами с Х и выполняется переход к п. 2.
Иначе  конец первой фазы.  
  
Фаза 2: сортировка
 Для того, чтобы отсортировать элементы, надо вы-полнить n шагов просеивания.
 После каждого шага очередной элемент берется с вершины пирамиды и помещается на свое место в
 результирующей последо-вательности. 
На каждом шаге выбирается минимальный из после-дующих узлов пирамиды и помещается в вершину.
И т. д. по цепочке. 
*/

void heapify(int A[], int pos, int n)
{
	int t, tm;
	while (2 * pos + 1 <  n)
	{
		t = 2 * pos + 1;
		if (2 * pos + 2 < n  &&  A[2 * pos + 2] >= A[t])      t = 2 * pos + 2;
		if (A[pos] < A[t]) { tm = A[pos];  A[pos] = A[t];  A[t] = tm;   pos = t; }
		else break;
	}
}
void PiramSort(int A[], int n)
{
	for (int i = n - 1; i >= 0; i--)
		heapify(A, i, n);
	while (n>0)
	{
		int tm = A[0];  A[0] = A[n - 1];  A[n - 1] = tm;
		n--;  heapify(A, 0, n);
	}
}

void InsOrd(int m[], int sm, int em, int e)//сортировка слиянием 
{
	int buf; int i = sm;
	while (i <= em  &&  m[i] <  e)
	{
		if (i - 1 >= sm)
			m[i - 1] = m[i];
		i++;
	}  m[i - 1] = e;
}
int*  Merge(int m[], int sm, int cm, int em)
//процедура слияния
{
	for (int i = 0; i <= sm; i++)
	{
		if (m[i] > m[cm + 1])
		{
			int buf = m[i];  m[i] = m[cm + 1];
			InsOrd(m, cm + 1, em, buf);
		}
	}
	return m;
}

int* SortMerge(int m[], int lm, int sm = 0)
{
	if (lm  > 1)
	{
		SortMerge(m, lm / 2, sm);
		SortMerge(m, lm - int(lm / 2), sm + lm / 2);
		Merge(m, sm, sm + lm / 2 - 1, sm + lm - 1);
	};
	return m;
};

int GetHoarBorder(int A[], int sm, int em)
{
	int i = sm - 1, j = em + 1;
	int brd = A[sm];
	int buf;
	while (i < j)
	{
		while (A[--j]> brd);
		while (A[++i]< brd);
		if (i < j)
		{
			buf = A[j]; A[j] = A[i]; A[i] = buf;
		};
	}
	return j;
}

int* SortHoar(int A[], int sm, int em)
{
	if (sm < em)
	{
		int hb = GetHoarBorder(A, sm, em);
		SortHoar(A, sm, hb);
		SortHoar(A, hb + 1, em);
	}
	return A;
};


int GetRandKey(int reg = 0)     // генерация случайных ключей
{
	if (reg > 0)   srand((unsigned)time(NULL));
	int rmin = 0;   int rmax = 100000;
	return (int)(((double)rand() / (double)RAND_MAX) * (rmax - rmin) + rmin);
}
int main()
{
	setlocale(LC_CTYPE, "Russian");
	const int N = 5000; int k[2 * N], f[2 * N], e[N], ee[N];  clock_t  t1, t2;
	GetRandKey(1);
	int pos = -1;
	for (int i = 0; i < N; i++)
	{
		ee[i] = GetRandKey(0);
		if (ee[i] % 2 == 0)
			f[++pos] = ee[i];
		e[i] = GetRandKey(0);
		if (e[i] % 2 == 1)
			f[++pos] = e[i];
	}
	for (int n = 1000; n <= N; n += 1000)
	{
		cout << "n = " << n << endl;       cout << "SortPiram   ";
		memcpy(k, f, n * sizeof(int)); t1 = clock();
		PiramSort(k, n);     t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl;
		cout << "SortMerge   ";
		memcpy(k, f, n * sizeof(int));
		t1 = clock();   SortMerge(k, n, 0);     t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl;
		cout << "SortHoar   ";
		memcpy(k, f, n * sizeof(int));
		t1 = clock();   SortHoar(k, 0, n - 1);     t2 = clock();
		cout << "Прошло " << t2 - t1 << " тактов времени" << endl;
	}
	return 0;
}



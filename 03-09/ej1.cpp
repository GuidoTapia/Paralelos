#include <iostream>
#include <iomanip>
#include <algorithm>


#define MAX 10000
using namespace std;
int main() {
	int **A,x[MAX],y[MAX];
	A=new int*[MAX];
	A[0]=new int[MAX*MAX];
	for (int i = 1; i < MAX; i++)
		A[i]=&A[0][MAX*i];
	clock_t start, end, start2, end2;
	cout << "Tiempo de ejecucion en primer bucle: ";
	start = clock();
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			y[i] += A[i][j] * x[j];
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << fixed << time_taken << setprecision(5)<<"segundos\nTiempo de ejecucion en segundo bucle: ";
	start2 = clock();
	for (int j = 0; j < MAX; j++)
		for (int i = 0; i < MAX; i++)
			y[i] += A[i][j] * x[j];
	end2 = clock();
	double time_taken2 = double(end2 - start2) / double(CLOCKS_PER_SEC);
	cout << fixed << time_taken2 << setprecision(5) << " segundos " << endl;
}
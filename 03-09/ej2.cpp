#include <iostream>
#include <iomanip>
#include <algorithm>


#define SIZE_1 3200
#define SIZE_2 1000
#define SIZE_3 10000
using namespace std;
int main() {
	int **A,**B,**C;
	A=new int*[SIZE_1];
	B=new int*[SIZE_1];
	C=new int*[SIZE_1];
	A[0]=new int[SIZE_1*SIZE_1];
	B[0]=new int[SIZE_1*SIZE_1];
	C[0]=new int[SIZE_1*SIZE_1];
	for (int i = 1; i < SIZE_1; i++){
		A[i]=&A[0][SIZE_1*i];
		B[i]=&B[0][SIZE_1*i];
		C[i]=&C[0][SIZE_1*i];
	}
	
	clock_t start, end;
	cout << "Tiempo de ejecucion con "<< SIZE_1*SIZE_1 <<" elementos: ";
	start = clock();
	for (int i = 0; i < SIZE_1; i++){
		for (int j = 0; j < SIZE_1; j++){
			int aux=0;
			for (int k = 0; k < SIZE_1; k++){
				aux+=A[i][k]*B[k][j];
			}
			C[i][j]=aux;
		}
	}
	end = clock();
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	cout << fixed << time_taken << setprecision(5)<<"segundos";
}
#include <stdio.h>
#include <iostream>

using namespace std;


void func(_int8 *A, _int8 *B, _int8 *C, _int16 *D) {
	
	__int16 F[8];
	__asm
	{
		mov ESI, B
		movq mm7, [ESI]
		mov ESI, C
		movq mm6, [ESI]

		paddb mm7, mm6 // 8+8 = 8
		//movq[F], mm7

		movq mm0, mm7
		pcmpgtb mm1, mm7
		punpcklbw mm0, mm1
		movq mm6, mm0  //(C+B) first 4

		movq mm0, mm7
		pcmpgtb mm1, mm7
		punpckhbw mm0, mm1
		movq mm7, mm0  //(C+B) last 4

		mov ESI, A
		movq mm0, [ESI]
		pcmpgtb mm1, mm0
		punpcklbw mm0, mm1
		movq mm5, mm0

		mov ESI, A
		movq mm0, [ESI]
		pcmpgtb mm1, mm0
		punpckhbw mm0, mm1
		movq mm4, mm0

		pmullw mm6, mm5 //A*(C+B) first 4
		pmullw mm7, mm4 //A*(C+B) last 4

		//movq[F], mm7
		//movq[F + 2 * 4], mm6

		mov ESI, D
		movq mm5, [ESI]
		mov ESI, D
		movq mm4, [ESI+2*4]

		psubsw mm6, mm5 //first 4
		psubsw mm7, mm4 //last 4

		movq[F], mm6
		movq[F + 2 * 4], mm7
	}

	cout <<"Function result: "<<endl;
	for (int i = 0; i < 8; i++)
	{
		cout << *(F + i) << " ";
	}
	cout << endl;
	cout << "Actual result: "<<endl;
	for (int i = 0; i < 8; i++)
	{
		cout << A[i] * (C[i] + B[i]) - D[i] << " ";
	}
	cout << endl;

}

void test1() {
	cout << "Test1: " << endl;
	__int8 A[8]{ 1, 2, 3, 4, 1, 5, 6, 1 };
	__int8 B[8]{ 22, -3, 2, 0, 23, -13, -11, 5 };
	__int8 C[8]{ 18, -2, 4, 6, 6, 11, 22, 1 };
	__int16 D[8]{ 8, -4, -2, -16, 0, -2, 0, 10 };
	func(A, B, C, D);
	
}

void test2() {
	cout << "Test2: " << endl;
	__int8 A[8]{ 1, 2, 3, 14, 1, 25, 6, 1 };
	__int8 B[8]{ 2, -3, 12, 0, 23, -13, -11, 5 };
	__int8 C[8]{ 0, -12, 4, 6, 6, 2, 22, 1 };
	__int16 D[8]{ 8, -4, -2, -1, 0, -2, 0, 10 };
	func(A, B, C, D);
}


int main() {
	//  F[i]=A[i] *(B[i]) +C[i] )-D[i] , i=1...8;
	test1();
	test2();

    return 0;
}
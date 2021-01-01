#include <stdio.h>
#include <ap_int.h>
#include <ap_fixed.h>

typedef ap_ufixed <10,3> fix ;

void machine(ap_uint<18> inform,fix *Q) ;

int main(int argc, char **argv)
{
	fix Q ;
	ap_uint<18> inform ;
	ap_uint<4> subset, beta, betaV, status ;
	ap_uint<1> flag ;

	inform = 0 ;
	subset = 3 ;

 	printf("Inform #1\n") ;
 	machine(inform, &Q) ;
 	printf("Q = %f\n\n",(float)Q) ;

 	for(int i = 1; i<=15 ;i++)
 	{
 		if(i<=3)
		{
			beta = 14 ;	// 1110
			betaV = 6 ;	// 0110
			status = 0 ; // 0000
			flag = 1 ;
		}
		else if(i<=5)
		{
			beta = 6 ;	// 0110
			betaV = 2 ;	// 0010
			status = 9 ; // 1001
			flag = 0 ;
		}

		else if(i<=12)
		{
			beta = 7 ;	// 0111
			betaV = 3 ;	// 0011
			status = 4 ; // 0100
			flag = 1 ;
		}
		else
		{
			beta = 6 ;	// 0110
			betaV = 2 ;	// 0010
			status = 8 ; // 1000
			flag = 0 ;
		}

 		inform = 1 ;
 		inform = (((((((((inform<<4)|beta)<<4)|betaV)<<4)|status)<<1)|flag)<<4)|subset ;

		printf("Inform #%d\n",i+1) ;
 		machine(inform, &Q) ;
	 	printf("Q = %f\n\n",(float)Q) ;
 	}

	return 0;
}


/*
int main(int argc, char **argv)
{
	unsigned int a, v, b, bv, x1, t1, remain, Oremain ;
	unsigned int beta, betaV ;
	float P1, P2, P3, P4, random, Q, X, T, N ;

	ap_uint<9> inform ;
	ap_uint<4> subset ;

	inform = 0 ;
	subset = 3 ;
 	parameterUpdate(inform, subset, &a, &v, &b, &bv, &x1, &t1, &X, &T, &N, &remain, &Oremain, &P1, &P2, &P3, &P4, &random,&Q) ;

 	printf("Inform #1\n") ;
 	printf("a = %u\n",a) ;
 	printf("v = %u\n",v) ;
 	printf("b = %u\n",b) ;
 	printf("bv = %u\n",bv) ;
 	printf("x1 = %u\n",x1) ;
 	printf("t1 = %u\n",t1) ;
 	printf("remain = %u\n",remain) ;
 	printf("Oremain = %u\n",Oremain) ;
 	printf("P1 = %f\n",P1) ;
 	printf("P2 = %f\n",P2) ;
 	printf("P3 = %f\n",P3) ;
 	printf("P4 = %f\n",P4) ;
 	printf("random = %f\n",random) ;
 	printf("Q = %f\n",Q) ;
 	printf("X = %f\n",X) ;
 	printf("T = %f\n",T) ;
 	printf("N = %f\n\n",N) ;

 	for(int i = 1; i<=15 ;i++)
 	{
 		if(i==1)
		{
			beta = 14 ;	// 1110
			betaV = 6 ;	// 0110
		}
		else if(i==2)
		{
			beta = 6 ;	//0110
			betaV = 2 ;	//0010
		}

		else if(i<=10)
		{
			beta = 7 ;	//0111
			betaV = 2 ;	//0010
		}
		else
		{
			beta = 6 ;	//0110
			betaV = 2 ;	//0010
		}

 		inform = (((1<<4)|beta)<<4)|betaV ;
		parameterUpdate(inform, subset, &a, &v, &b, &bv, &x1, &t1, &X, &T, &N, &remain, &Oremain, &P1, &P2, &P3, &P4, &random,&Q) ;

		printf("Inform #%d\n",i+1) ;
		printf("a = %u\n",a) ;
		printf("v = %u\n",v) ;
		printf("b = %u\n",b) ;
		printf("bv = %u\n",bv) ;
		printf("x1 = %u\n",x1) ;
		printf("t1 = %u\n",t1) ;
	 	printf("remain = %u\n",remain) ;
	 	printf("Oremain = %u\n",Oremain) ;
	 	printf("P1 = %f\n",P1) ;
	 	printf("P2 = %f\n",P2) ;
	 	printf("P3 = %f\n",P3) ;
	 	printf("P4 = %f\n",P4) ;
	 	printf("random = %f\n",random) ;
		printf("X = %f\n",X) ;
		printf("T = %f\n",T) ;
		printf("N = %f\n",N) ;
	 	printf("Q = %f\n\n",Q) ;

 	}

	return 0;
}
*/

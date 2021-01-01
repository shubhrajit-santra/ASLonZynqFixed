#include <stdio.h>
#include <ap_int.h>

void lite_to_stream(ap_uint<9> inform, ap_uint<18> *inform1, ap_uint<18> *inform2,
		ap_uint<18> *inform3, ap_uint<18> *inform4, ap_uint<18> *inform5,
		ap_uint<18> *inform6, ap_uint<18> *inform7, ap_uint<18> *inform8,
		ap_uint<18> *inform9, ap_uint<18> *inform10, ap_uint<18> *inform11) ;

int main(int argc, char **argv)
{
	ap_uint<4> beta, betaV ;
	ap_uint<9> inform ;
	ap_uint<18> inform1, inform2, inform3, inform4, inform5, inform6,
				inform7, inform8, inform9, inform10, inform11 ;

	inform = 0 ;

	printf("Inform #1\n") ;
	lite_to_stream(inform, &inform1, &inform2, &inform3, &inform4, &inform5, &inform6,
			&inform7, &inform8, &inform9, &inform10, &inform11) ;
 	printf("subset = %u\n",(unsigned int)inform1.range(3,0)) ;
 	printf("beta = %u\n",(unsigned int)inform1.range(16,13)) ;
 	printf("betaV = %u\n",(unsigned int)inform1.range(12,9)) ;
 	printf("status = %u\n",(unsigned int)inform1.range(8,5)) ;
 	printf("flag = %u\n",(unsigned int)inform1[4]) ;
 	printf("n = %u\n\n",(unsigned int)inform1[17]) ;

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
			betaV = 4 ;	//0100
		}
		else
		{
			beta = 6 ;	//0110
			betaV = 2 ;	//0010
		}

 		inform = 1 ;
 		inform = (((inform<<4)|beta)<<4)|betaV ;

 		printf("Inform #%d\n",i+1) ;
 		lite_to_stream(inform, &inform1, &inform2, &inform3, &inform4, &inform5, &inform6,
 				&inform7, &inform8, &inform9, &inform10, &inform11) ;

 		if(i==3)
 			inform1 = inform2 ;
 		else if(i==5)
 			inform1 = inform5 ;
 		else if(i==10)
 			inform1 = inform10 ;

 	 	printf("subset = %u\n",(unsigned int)inform1.range(3,0)) ;
 	 	printf("beta = %u\n",(unsigned int)inform1.range(16,13)) ;
 	 	printf("betaV = %u\n",(unsigned int)inform1.range(12,9)) ;
 	 	printf("status = %u\n",(unsigned int)inform1.range(8,5)) ;
 	 	printf("flag = %u\n",(unsigned int)inform1[4]) ;
 	 	printf("n = %u\n\n",(unsigned int)inform1[17]) ;
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

#include <math.h>
#include <hls_math.h>
#include <ap_fixed.h>

typedef ap_ufixed<10,3> fix ;

void compare(fix Q1, fix Q2, fix Q3, fix Q4,
		fix Q5, fix Q6, fix Q7, fix Q8,
		fix Q9, fix Q10, fix Q11,
			 ap_uint<4> *maxQ);


int main(int argc, char **argv)
{

	ap_uint<4> maxQ ;

//	float Q[] = {0.3, 0.9, 0.99, 0.33, 0.67, 0.33, 0.88, 0.9, 0.12, 0.4, 0.77};
//	compare(Q[0], Q[1], Q[2], Q[3],
//			Q[4], Q[5], Q[6], Q[7],
//			Q[8], Q[9], Q[10], &maxQ);
//	printf("Result: %d \r\n", maxQ);

//	float Q[] = {0.3, 0.9, 0.93, 0.33, 0.67, 0.33, 0.88, 0.9, 0.12, 0.9, 0.77};
//	compare(Q[0], Q[1], Q[2], Q[3],
//			Q[4], Q[5], Q[6], Q[7],
//			Q[8], Q[9], Q[10], &maxQ);
//	printf("Result: %d \r\n", maxQ);

	fix Q[] = {0.3, 1.9, 1.93, 1.89, 0.1, 1.9315, 0.88, 1.9387, 0.9, 0.12, 1.91} ;
	compare(Q[0], Q[1], Q[2], Q[3],
			Q[4], Q[5], Q[6], Q[7],
			Q[8], Q[9], Q[10], &maxQ);
	printf("Result: %u\r\n", (unsigned int)maxQ);

	return 0;
}

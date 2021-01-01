#include <math.h>
#include <hls_math.h>
#include <ap_fixed.h>

typedef ap_ufixed<10,3> fix ;

void compare(fix Q1, fix Q2, fix Q3, fix Q4,
		fix Q5, fix Q6, fix Q7, fix Q8,
		fix Q9, fix Q10, fix Q11,
			 ap_uint<4> *maxQ)
{
#pragma HLS INTERFACE s_axilite port=maxQ
#pragma HLS INTERFACE axis register both port=Q1
#pragma HLS INTERFACE axis register both port=Q2
#pragma HLS INTERFACE axis register both port=Q3
#pragma HLS INTERFACE axis register both port=Q4
#pragma HLS INTERFACE axis register both port=Q5
#pragma HLS INTERFACE axis register both port=Q6
#pragma HLS INTERFACE axis register both port=Q7
#pragma HLS INTERFACE axis register both port=Q8
#pragma HLS INTERFACE axis register both port=Q9
#pragma HLS INTERFACE axis register both port=Q10
#pragma HLS INTERFACE axis register both port=Q11

	ap_uint<4> val ;

	if(Q1 >= Q2 && Q1 >= Q3 && Q1 >= Q4 && Q1 >= Q5 &&
	   Q1 >= Q6 && Q1 >= Q7 && Q1 >= Q8 && Q1 >= Q9 &&
	   Q1 >= Q10 && Q1 >= Q11){
		val = 1;
	}
	else if(Q2 >= Q1 && Q2 >= Q3 && Q2 >= Q4 && Q2 >= Q5 &&
	   Q2 >= Q6 && Q2 >= Q7 && Q2 >= Q8 && Q2 >= Q9 &&
	   Q2 >= Q10 && Q2 >= Q11){
		val = 2;
	}
	else if(Q3 >= Q2 && Q3 >= Q1 && Q3 >= Q4 && Q3 >= Q5 &&
	   Q3 >= Q6 && Q3 >= Q7 && Q3 >= Q8 && Q3 >= Q9 &&
	   Q3 >= Q10 && Q3 >= Q11){
		val = 3;
	}
	else if(Q4 >= Q2 && Q4 >= Q3 && Q4 >= Q1 && Q4 >= Q5 &&
	   Q4 >= Q6 && Q4 >= Q7 && Q4 >= Q8 && Q4 >= Q9 &&
	   Q4 >= Q10 && Q4 >= Q11){
		val = 4;
	}
	else if(Q5 >= Q2 && Q5 >= Q3 && Q5 >= Q4 && Q5 >= Q1 &&
	   Q5 >= Q6 && Q5 >= Q7 && Q5 >= Q8 && Q5 >= Q9 &&
	   Q5 >= Q10 && Q5 >= Q11){
		val = 5;
	}
	else if(Q6 >= Q2 && Q6 >= Q3 && Q6 >= Q4 && Q6 >= Q5 &&
	   Q6 >= Q1 && Q6 >= Q7 && Q6 >= Q8 && Q6 >= Q9 &&
	   Q6 >= Q10 && Q6 >= Q11){
		val = 6;
	}
	else if(Q7 >= Q2 && Q7 >= Q3 && Q7 >= Q4 && Q7 >= Q5 &&
	   Q7 >= Q6 && Q7 >= Q1 && Q7 >= Q8 && Q7 >= Q9 &&
	   Q7 >= Q10 && Q7 >= Q11){
		val = 7;
	}
	else if(Q8 >= Q2 && Q8 >= Q3 && Q8 >= Q4 && Q8 >= Q5 &&
	   Q8 >= Q6 && Q8 >= Q7 && Q8 >= Q1 && Q8 >= Q9 &&
	   Q8 >= Q10 && Q8 >= Q11){
		val = 8;
	}
	else if(Q9 >= Q2 && Q9 >= Q3 && Q9 >= Q4 && Q9 >= Q5 &&
	   Q9 >= Q6 && Q9 >= Q7 && Q9 >= Q8 && Q9 >= Q1 &&
	   Q9 >= Q10 && Q9 >= Q11){
		val = 9;
	}
	else if(Q10 >= Q2 && Q10 >= Q3 && Q10 >= Q4 && Q10 >= Q5 &&
	   Q10 >= Q6 && Q10 >= Q7 && Q10 >= Q8 && Q10 >= Q9 &&
	   Q10 >= Q1 && Q10 >= Q11){
		val = 10;
	}
	else{
		val = 11;
	}

	*maxQ = val;
}

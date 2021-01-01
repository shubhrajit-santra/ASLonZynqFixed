#include <hls_math.h>
#include <math.h>
#include <ap_int.h>
#include <ap_fixed.h>

typedef ap_ufixed <10,3> fix ;
typedef ap_ufixed <8,1> fix2 ;
typedef ap_ufixed <11,4> fix3 ;
typedef ap_ufixed <21,14> wordN ;
typedef ap_ufixed <21,14> wordX ;
typedef ap_ufixed <3,1> fix1 ;

fix UCB(wordX X, ap_uint<14> T, wordN N){
	fix d, Q_in ;
	fix2 a ;
	fix3 b, c ;

		a = (fix2) (X/T) ;
		b = (fix3) hls::log(N) ;
		c = (fix3) (b/T) ;
		d = (fix) hls::sqrt(c) ;
		Q_in = (fix) (a + d) ;

		/*
		printf("\na = %f",(float)a) ;
		printf("\nb = %f",(float)b) ;
		printf("\nc = %f",(float)c) ;
		printf("\nd = %f",(float)d) ;
		printf("\nQ_in = %f\n",(float)Q_in) ;
		*/

	return Q_in;
}

void machine(ap_uint<18> inform ,fix *Q){
#pragma HLS INTERFACE axis register both port=inform
#pragma HLS INTERFACE axis register both port=Q

	ap_uint<4> beta, betaV, gamma, gammaV, rem, status, subset ;
	bool sel ;
	ap_uint<3> x, arms, vacant, occupied, common, Vgamma, Ogamma, Orem, Vrem, fails, R ;
	ap_uint<1> t ;

	subset = inform.range(3,0) ;
	status = inform.range(8,5) ;
	betaV = inform.range(12,9) ;
	beta = inform.range(16,13) ;

	static wordX Xs ;
	static ap_uint<14> Ts ;
	static wordN Ns ;

	fix1 reward ;

	if(inform[17]==0)
	{
		Xs = 1 ;
		Ts = 1 ;
		Ns = 11 ;
	}
	else
	{
		gamma = subset & beta ;
		common = gamma[0] + gamma[1] + gamma[2] + gamma[3] ;

		if(common>0)
		{
			if(inform[4]==1)	// if(occupied <= K)	where K = 2
			{
				gammaV = gamma & betaV ;
				Vgamma = gammaV[0] + gammaV[1] + gammaV[2] + gammaV[3] ;

				rem = subset & (~gamma) ;
				R = rem[0] + rem[1] + rem[2] + rem[3] ;

				Ogamma = common - Vgamma ;

				Orem = (rem[0] && status[0]) + (rem[1] && status[1]) + (rem[2] && status[2]) + (rem[3] && status[3]) ;

				Vrem = R - Orem ;

				if ((Orem + Ogamma) <= 2)	// Orem + Ogamma <= K
					x = Vrem + Vgamma ;
				else
					x = 0 ;

				t = 1 ;
			}
			else
			{
				sel = (subset[0] ^ beta[0]) || (subset[1] ^ beta[1]) || (subset[2] ^ beta[2]) || (subset[3] ^ beta[3]) ;

				if (sel==false)	// active-low
					t = 1 ;
				else
				{
					arms = subset[0] + subset[1] + subset[2] + subset[3]  ;

					if(arms == 2)	// arms <= K
						t = 0 ;
					else
					{
						fails = (subset[0] && status[0]) + (subset[1] && status[1]) + (subset[2] && status[2]) + (subset[3] && status[3]) ;

						if(fails > 2)	// fails > K
							t = 1 ;
						else
							t = 0 ;
					}
				}
				x = 0 ;
			}
		}
		else
		{
			x = 0 ;
			t = 0 ;
		}

		Ns += 1 ;

		if(t==1)
		{
			Ts += 1 ;

			if(x==0)
				reward = 0 ;
			else if(x==1)
				reward = 0.25 ;
			else if(x==2)
				reward = 0.5 ;
			else if(x==3)
				reward = 0.75 ;
			else
				reward = 1 ;

			Xs += reward ;
		}
	}

	/*
	printf("x = %u\n",(unsigned int)x) ;
	printf("Xs = %f\n",(float)Xs) ;
	printf("Ts = %u\n",(unsigned int)Ts) ;
	printf("Ns = %u\n",(unsigned int)Ns) ;
	*/

	*Q = UCB(Xs, Ts, Ns);

}

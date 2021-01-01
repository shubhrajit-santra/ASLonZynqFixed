#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "math.h"
#include <time.h>
#include <stdlib.h>
#include "xil_cache.h"
#include "xil_types.h"
#include "xtime_l.h"
#include <sleep.h>

#define A 4
#define S 11

void runAlgorithm();

int main()
{
    init_platform();

    runAlgorithm();

    cleanup_platform();
    return 0;
}

void runAlgorithm()
{

    // double probs[A] = {0.1, 0.2, 0.3, 0.7} ;
    // double probs[A] = {0.65, 0.75, 0.85, 0.95} ;
	// double probs[A] = {0.0, 0.2, 0.9, 0.8} ;
	// double probs[A] = {0.4, 0.5, 0.3, 0.7} ;
	// double probs[A] = {0.4, 0.0, 0.0, 0.7} ;
	 double probs[A] = {0.1, 0.3, 0.5, 0.7} ;
	// double probs[A] = {0.51, 0.52, 0.53, 0.54} ;
	// double probs[A] = {0.11, 0.21, 0.31, 0.41} ;
	// double probs[A] = {0.38, 0.24, 0.77, 0.65} ;

    float x[S] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ;
    unsigned int t[S] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} ;
    unsigned int n = 11 ;

    unsigned int xa[A] = {1,1,1,1} ;
    unsigned int ta[A] = {1,1,1,1} ;
    double pa[A] = {0,0,0,0} ;
    double pr[A] = {0,0,0,0} ;
    unsigned int beta[A] = {0,0,0,0} ;
    unsigned int betaV[A] = {0,0,0,0} ;
    unsigned int gamma[A] = {0,0,0,0} ;
    unsigned int gammaV[A] = {0,0,0,0} ;
    unsigned int rem[A] = {0,0,0,0} ;

    unsigned int subset[S][A] = {
    	   { 0, 0, 1, 1 },
		   { 0, 1, 0, 1 },
		   { 0, 1, 1, 0 },
		   { 0, 1, 1, 1 },
		   { 1, 0, 0, 1 },
		   { 1, 0, 1, 0 },
		   { 1, 0, 1, 1 },
		   { 1, 1, 0, 0 },
		   { 1, 1, 0, 1 },
		   { 1, 1, 1, 0 },
		   { 1, 1, 1, 1 }
    };
    unsigned int K = 2;

    unsigned int selected, arms, vacant, occupied, common, Vgamma, Ogamma ;
	unsigned int Vrem, Orem, R, reward, f, fails ;
    double r = 0;
    float Q[11], maxQ ;

	XTime tprocessorStart, tprocessorEnd ;

	XTime_GetTime(&tprocessorStart) ;
    for(int i=1; i<=10000 ; i++){

    	// usleep(100);

    	// selected = XCompare_Get_maxQ(&compare);

    	// printf("sel = %u \r\n",selected) ;

    	if(i<=11)
    		selected = i;
    	else
    	{
    		maxQ = -1 ;
    		for(int k = 0 ; k<S ;k++)
    		{
    			// XTime_GetTime(&tprocessorStart);
    			Q[k] = (float)x[k]/(float)t[k] + (float)sqrt(((float)log(n))/(float)t[k]) ;
    			// XTime_GetTime(&tprocessorEnd);

    			if(Q[k]>maxQ)
    			{
    				maxQ = Q[k] ;
    				selected = k+1 ;
    			}
    		}
    	}

    	// printf("sel = %u \r\n",selected) ;

    	selected-- ;

    	r = (double) rand()/ (double) RAND_MAX;
        // r = 0.5 ;

    	arms = 0 ;
    	vacant = 0 ;

    	for(int k = 0; k < A ; k++)
    	{
    		beta[k] = subset[selected][k] ;
    		betaV[k] = beta[k] && (r < probs[k]) ;

    		// printf("beta = %u\n", beta[k]) ;
    		// printf("betaV = %u\n", betaV[k]) ;

    		arms += beta[k] ;
    		vacant += betaV[k] ;
    	}

    	occupied = arms - vacant ;

        if(occupied <= K)
        {
        	for(int k = 0; k < A ; k++)
        	{
        		xa[k] += betaV[k] ;
        		ta[k] += beta[k] ;

        		// printf("xa[k] = %u\n", xa[k]) ;
        		// printf("ta[k] = %u\n", ta[k]) ;
        	}
        }


        for(int k = 0; k < A ; k++)
        {
        	pa[k] = (double)xa[k]/(double)ta[k] ;
        	// printf("pa[k] = %f\n", pa[k]) ;
        }

        for(int s = S-1 ; s >= 0 ; s--)
        {
        	common = 0 ;
        	reward = 0 ;
        	f = 0 ;

        	for(int k = 0; k < A ; k++)
        	{
        		gamma[k] = subset[s][k] && beta[k] ;
        		common += gamma[k] ;
        	}

        	if(common>0)
        	{
        		if(occupied <= K)
        		{
        			Vgamma = 0 ;
        			for(int k = 0; k < A ; k++)
					{
						gammaV[k] = gamma[k] && betaV[k] ;
						rem[k] = subset[s][k] - gamma[k] ;

						Vgamma += gammaV[k] ;
					}

        			Ogamma = common - Vgamma ;

        			R = 0 ;

        			for(int k = 0; k < A ; k++)
        			{
        				if(rem[k]==1)
        					pr[R++] = pa[k] ;
        			}

        			if(R != 0)
        				r = (double) rand()/ (double) RAND_MAX ;

        			Orem = 0 ;

        			for(int k = 0; k < R ; k++)
        			{
        				if(r > pr[k])
        					Orem++ ;
        			}

        			Vrem = R - Orem ;

        			if ((Orem + Ogamma) <= K)
        				reward = Vrem + Vgamma ;
        			else
        				reward = 0 ;

        			x[s] += ((float)reward/(float)4) ;
        			t[s] += 1 ;
        			f = 1 ;
        		}

        		else
        		{
        			if (s == selected)
        				f = 1 ;
        			else
        			{
        				arms = 0 ;
        				for(int k = 0; k < A ; k++)
        					arms += subset[s][k] ;

        				if(arms <= K)
        					f = 0 ;
        				else
        				{
        					r = (double) rand()/ (double) RAND_MAX ;

        					fails = 0 ;

        					for(int k = 0; k < A ; k++)
        					{
        						if(subset[s][k] && r > pa[k])
        							fails++ ;
        					}

        					if(fails > K)
        						f = 1 ;
        					else
        						f = 0 ;

        				}
        			}
        			t[s] += f ;
        		}
        	}

        	/*
        	if(s==i || s==i+2 || s==i+5)
        	{
        		reward = 1 ;
				f = 1 ;
        	}
        	else
        	{
        		reward = 0 ;
        		f = 0 ;
        	}

        	x[s] += (double)((double)reward/(double)4) ;
        	t[s] += f ;
			*/
        }
    	n += 1 ;
    }

    XTime_GetTime(&tprocessorEnd);

    double max = 0;
    int index = 0 ;

    for(int k = 0 ; k < S ; k++ )
    {
    	printf("X[%d] = %0.4f		T[%d] = %u \r\n", k, x[k]-1, k, t[k]-1) ;

		if(x[k]>max)
		{
			max = x[k] ;
			index = k ;
		}
    }

    printf("N = %u \r\n", n-11) ;

    printf("Optimal Subset is: {") ;

    for( int k = 0; k < A ; k++ )
    {
		if(subset[index][k]==1)
			printf(" %d",k+1) ;
    }

    printf(" }\n") ;

    double temp ;
    unsigned int temp1 ;
    unsigned int indices[S] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10} ;

    for( int p = 0 ; p < 10 ; p++ )
    {
    	for( int q = 0 ; q < 10-p ; q++ )
    	{
    		if(x[q] < x[q+1])
    		{
    			temp = x[q] ;
				x[q] = x[q+1] ;
				x[q+1] = temp ;

				temp1 = indices[q] ;
				indices[q] = indices[q+1] ;
				indices[q+1] = temp1 ;
    		}
    	}
    }

    printf("Best Subsets Ranking:\n") ;

    unsigned int sel ;

    for(int r=0;r<S;r++)
    {
    	sel = indices[r] ;
    	printf("{") ;
    	for( int k = 0; k < A ; k++ )
		{
    		if(subset[sel][k]==1)
    			printf(" %d",k+1) ;
		}
    	printf(" }\n") ;
    }

    printf("\nPS took %.2f us.\n\n", 1.0 * (tprocessorEnd - tprocessorStart) / (COUNTS_PER_SECOND/1000000));

}

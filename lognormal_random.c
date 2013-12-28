/*
 * =====================================================================================
 *
 *       Filename:  lognormal_random.c
 *
 *    Description:  Generate random numbers with a lognormal distribution
 *
 *        Created:  17/05/2012 13:27:04
 *
 *         Author:  Denis Roussel (denis.roussel@simap.grenoble-inp.fr)
 *
 * =====================================================================================
 */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <time.h>


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  lognormal
 *  Description:  expression of a lognormal distribution
 * =====================================================================================
 */
double lognormal(double x, double mean, double sd)
{
	double sigma = sqrt( log( sd/pow(mean,2) + 1 ) );
	double mu = log( mean ) - pow(sigma,2) / 2;
	return ( exp( - pow((log(x) - mu), 2) / (2*pow(sigma,2)) ) / (x * sigma * sqrt(2 * M_PI) ) );
}				/* ----------  end of function lognormal  ---------- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  xmode_lognormal
 *  Description:  find x for which f(x) is max
 * =====================================================================================
 */
double xmode_lognormal(double mean, double sd)
{
	double sigma = sqrt( log( sd/pow(mean,2) + 1 ) );
	double mu = log( mean ) - pow(sigma,2) / 2;
	return exp(mu - pow(sigma,2));
}				/* ----------  end of function xmode_lognormal  ---------- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
  int main ( int argc, char *argv[] )
{

	// To change if necessary
	// -----------------------
	double mean = 1;
	double sd = 0.5;
	int nrand_max = 1000000;
	// -----------------------

	int nrand = 0;
	double nb_alea1, nb_alea2;

	double y_max = lognormal(xmode_lognormal(mean, sd), mean, sd);
	double y_max_stop = y_max / nrand_max;
	double x = xmode_lognormal(mean, sd);
	double y = y_max;
	
	double step = mean / 100;


	while ( y > y_max_stop )
	{
		x += step;
		y = lognormal(x, mean, sd);
	}

	double x_max = x;
	srand( time(NULL) );

	while ( nrand < nrand_max)
	{
		nb_alea1 = rand()/(double)RAND_MAX * x_max;
		nb_alea2 = rand()/(double)RAND_MAX * y_max;
		y = lognormal(nb_alea1, mean, sd);
		if ( nb_alea2 <= y )
		{
			printf("%f\n", nb_alea1);
			nrand += 1;
		}
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


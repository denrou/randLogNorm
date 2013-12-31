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

double lognormal(double x, double mean, double sd);
double xmode_lognormal(double mean, double sd);


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
	double standard_deviation = 0.5;
	int number_to_generate = 100;
	// -----------------------

	int number_generated = 0;
	double random_number_1, random_number_2;

	double y_max = lognormal(xmode_lognormal(mean, standard_deviation), mean, standard_deviation);
	double y_limit = y_max / number_to_generate;
	double x = xmode_lognormal(mean, standard_deviation);
	double y = y_max;
	
	double step = mean / 100;
	while ( y > y_limit )
	{
		x += step;
		y = lognormal(x, mean, standard_deviation);
	}

	double x_max = x;
	srand( time(NULL) );

	while( number_generated < number_to_generate )
	{
		random_number_1 = rand()/(double)RAND_MAX * x_max;
		random_number_2 = rand()/(double)RAND_MAX * y_max;
		y = lognormal(random_number_1, mean, standard_deviation);
		if ( random_number_2 <= y )
		{
			printf("%f\n", random_number_1);
			number_generated += 1;
		}
	}
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  lognormal
 *  Description:  expression of a lognormal distribution
 * =====================================================================================
 */
double lognormal(double x, double mean, double sd)
{
	double sigma = sqrt(log(sd/pow(mean,2)+1));
	double mu = log(mean)-pow(sigma,2)/2;
	return exp(-pow((log(x)-mu),2)/(2*pow(sigma,2))) / (x*sigma*sqrt(2*M_PI));
}				/* ----------  end of function lognormal  ---------- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  xmode_lognormal
 *  Description:  find x for which f(x) is max
 * =====================================================================================
 */
double xmode_lognormal(double mean, double sd)
{
	double sigma = sqrt(log(sd/pow(mean,2)+1));
	double mu = log(mean)-pow(sigma,2)/2;
	return exp(mu - pow(sigma,2));
}				/* ----------  end of function xmode_lognormal  ---------- */


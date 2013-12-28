#!/bin/bash - 

# ==============================================================================
#       Filename:	sort_histogram.sh
#
#    Description:	From a list of number, sort them in a certain number of
#					category
#
#        Created:	23/05/2012 16:03:23
#
#         Author:	Denis Roussel (denis.roussel@simap.grenoble-inp.fr)
#
# ==============================================================================

set -o nounset								# Treat unset variables as an error

list=$1

STATS=$(mktemp)
awk '
	NR==1{
		min = $1
		max = $1
	}
	{
		if( $1 < min ) min = $1
		if( $1 > max ) max = $1
	}
	END{
		printf( "%f\t%f\t%d\n", min, max, NR )
	}' $list > $STATS
	
nmin=$(cut -f 1 $STATS)
nmax=$(cut -f 2 $STATS)
nnumber=$(cut -f 3 $STATS)
rm $STATS
nclass=$(($nnumber/100))
step=$(echo "($nmax-$nmin)/$nclass" | bc -l)

awk -v nclass=$nclass -v nmin=$nmin -v step=$step '
	BEGIN{
		for( i = 0; i < nclass; i++ )
		{
			class[i] = nmin + i*step
			n[i] = 0
		}
	}
	{ n[int(($1 - nmin)/step)]++ }
	END{
		for( i = 0; i < nclass; i++ )
		{
			if( n[i] > 0 )
				printf( "%f\t%d\n", class[i], n[i] )
		}
	}' $list

#!/bin/bash - 

# ==============================================================================
#       Filename:	sort_histogram.sh
#
#    Description:	From a list of number, sort them in a certain number of
#					category
#
#   Dependancies:	mktemp, awk, cut, echo, bc, rm
#
#        Created:	23/05/2012 16:03:23
#
#         Author:	Denis Roussel
#
# ==============================================================================

set -o nounset								# Treat unset variables as an error

# To change if necessary
# ----------------------
NUMBER_CLASS=100
# ----------------------

TMP_LIST_VALUES=$(mktemp)
$(while read line; do echo "$line" >> $TMP_LIST_VALUES; done < "${1:-/proc/${$}/fd/0}")
# The substitution ${1:-...) takes $1 if defined otherwise the file name of the
# standard input of the own process is used

# Find bonding limits and store it to a temporary file (min_value, max_value and
# number of entries)
TMP_STATS=$(mktemp)
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
	}' $TMP_LIST_VALUES > $TMP_STATS
	
VALUE_MIN=$(cut -f 1 $TMP_STATS)
VALUE_MAX=$(cut -f 2 $TMP_STATS)
NUMBER_VALUES=$(cut -f 3 $TMP_STATS)
STEP=$(echo "($VALUE_MAX-$VALUE_MIN)/$NUMBER_CLASS" | bc -l)

rm $TMP_STATS

# Sort values into different classes
awk -v nclass=$NUMBER_CLASS -v valmin=$VALUE_MIN -v step=$STEP '
	BEGIN{
		for( i = 0; i < nclass; i++ ) {
			class[i] = valmin + i*step
			n[i] = 0
		}
	}
	{ n[int(($1 - valmin)/step)]++ }
	END{
		for( i = 0; i < nclass; i++ )
			printf( "%f\t%d\n", class[i], n[i] )
	}' $TMP_LIST_VALUES
	
rm $TMP_LIST_VALUES

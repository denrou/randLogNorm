# randLogNorm

## Purpose

Create random numbers with a lognormal distribution and verify the PDF

## Files

### lognormal_random.c

Generate random numbers with a lognormal distribution. The mean, standard deviation and the amount of generated number can be changed in the main function of the source code. It is also easy to change the function of distribution from lognormal to whatever.

Here is an example of how to compile the code and execute it (values might be different):

    gcc -o lognormal_random lognormal_random.c -lm
    ./lognormal_random | head
    1.750844
    2.255604
    0.159421
    0.940138
    0.220863
    0.337000
    0.428063
    1.114155
    0.727670
    0.439926

### histogram.sh

take a file with one column of number (typically a file generated by lognormal_random) and sort them in classes. The number of class can be changed inside the code. In the example below, 1,000,000 random numbers have been generated and sorted in 100 classes.

    ./lognormal_random > random_values
    ./histogram.sh random_values | head
    0.052193	469
    0.156355	3173
    0.260517	6518
    0.364680	9024
    0.468842	9775
    0.573004	9418
    0.677166	8808
    0.781328	7849
    0.885490	6657
    0.989653	5938

`./lognormal_random | ./histogram.sh` would have given the same result. We can check the resolution with gnuplot for example:

```
gnuplot -p -e 'plot "< ./lognormal_random | ./histogram.sh" with boxes notitle'
```

![Result of gnuplot command](https://github.com/denrou/randLogNorm/blob/master/result_gnuplot.png)

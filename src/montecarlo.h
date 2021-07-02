#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <time.h>
#include <stdlib.h>

// Return a random number in [lo, hi] interval (inclusive)
#define RANDOM_DOUBLE(lo, hi) lo + ((double) rand() / (double) (RAND_MAX) * (hi - lo))

/**
 * function: monte_carlo_pi
 * Monte Carlo PI computation method implementation
 * @param total_points, Number of random points to be generated
 */
double monte_carlo_pi(unsigned long total_points);

#endif
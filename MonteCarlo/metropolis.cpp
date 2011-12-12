/*******************************************************************************
 * 
 * Implements the Metropolis algorithm on a 3D Ising model.
 * 
 ******************************************************************************/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>

#include "plattice.hpp"


/*******************************************************************************
 * 
 * Configuration
 * 
 ******************************************************************************/

double T = 2.27;                       // relative starting temperature
double kb = 1.3806503 * 10e-23;        // Boltzmann constant
double J = kb;                         // spin coupling constant

int SIZE = 2000;                       // lattice side length
//~ int SIZE = 500;                        // lattice side length
const int EQUI_N = 100;                // equilibrium iterations
const bool DIAG_EQUI = false;          // write equilibrium history to disk

const int ITERATIONS =   20*1000*1000; // single flip iterations
const int DIAG_INTERVAL =     10*1000; // snapshot intervals (for video)
const bool SNAPSHOTS = false;           // make snaphots? (for video)


const unsigned int pickSeed = 1;       // seed for picking random spins
const unsigned int flipSeed = 2;       // seed for acceptance/rejection sampling


/*******************************************************************************
 * 
 * Declarations
 * 
 ******************************************************************************/

inline int spinE(lat_t s1, lat_t s2);
inline int stencilEnergyDiff(lat_t x, lat_t top, lat_t bot,
                                      lat_t left, lat_t right);
inline void singleFlip(Lattice & lat, int i, int j);
inline void systemFlip(Lattice & lat);

double expEnerDiff[5] = {0,0,0,0,0};  // a little performance cheating
inline void cacheExpEnerDiff() {
  for(int i = 0; i < 5; ++i)
    expEnerDiff[i] = exp( -J*(4*i - 8) / (kb*T) );
}


double Etot = 0;
double Mag = 0;


/*******************************************************************************
 * 
 * Main
 * 
 ******************************************************************************/

using namespace std;

int main(int argc, char ** argv) {

  srand(pickSeed);
  srand48(flipSeed);

  // changes passed by command line
  //~ queue<double> changes;
  //~ for(int i = 1; i < argc; ++i) {
    //~ double x; stringstream ss(argv[i]); ss >> x;
    //~ changes.push(x);
  //~ }
  //~ cacheExpEnerDiff();


  Lattice lat(SIZE);

  // initialise all spins to the same value, which defines Etot and Mag
  for(int i = 0; i < lat.size; ++i)
    for(int j = 0; j < lat.size; ++j)
      lat[i][j] = lat_t_inv(1);
  Etot = -2 * lat.size * lat.size;  // *J  actually
  Mag = - lat.size * lat.size;

  ofstream outf("diagnostics", ios::out);

  // wait for equilibrium
  //~ cout << "\nWaiting for equilibrium..."; cout.flush();
  //~ for(int k = 0; k < EQUI_N; ++k) {
//~ 
    //~ if(DIAG_EQUI == true)
      //~ outf << "\n" << (-EQUI_N+k)*lat.size*lat.size
           //~ << "\t" << Etot << "\t" << Mag << "\t" << double(Etot)/Mag;
//~ 
    //~ systemFlip(lat);
//~ 
  //~ }


  //~ if(SNAPSHOTS == true) {
    //~ cout << "\nWriting " << ITERATIONS/DIAG_INTERVAL << " snapshots";
    //~ lat.snapshot(0);
  //~ }
//~ 
  //~ cout << "\nRunning " << ITERATIONS << " iterations";
  double EtotAvg = 0;
  double MagAvg = 0;

  // main loop
  for(int k = 1; k < ITERATIONS; ++k) {

    // apply temperature changes
    if(k % (ITERATIONS / argc) == 0 && changes.size() > 0) {

      //~ T = changes.front(); changes.pop();
      cout << "\n --- T changed to " << T << " ---";
      cacheExpEnerDiff();

    }

    singleFlip(lat, rand() % lat.size, rand() % lat.size);

    EtotAvg += Etot;
    MagAvg += Mag;
    if(k % DIAG_INTERVAL == 0) {

      outf << "\n" << k << "\t" << EtotAvg/DIAG_INTERVAL
           << "\t" << MagAvg/DIAG_INTERVAL << "\t" << double(EtotAvg)/MagAvg;
      EtotAvg = 0;
      MagAvg = 0;

      if(SNAPSHOTS == true)
        lat.snapshot(k/DIAG_INTERVAL);

    }

  }

  return EXIT_SUCCESS;

}


/*******************************************************************************
 * 
 * Flipping functions
 * 
 ******************************************************************************/

// Returns 1 if the spins are equal, -1 otherwise
inline int spinE(lat_t s1, lat_t s2) {
  if(s1 == s2) return 1;
  else return -1;
}

/*
// Returns energy difference < 0 if flip is favorable, > 0 if it's "bad"
inline double stencilEnergyDiff(lat_t x, lat_t top, lat_t bot, 
                                lat_t left, lat_t right) {
  lat_t s = lat_t_inv(x);
  return -1*( spinE(s, top) + spinE(s, bot) + spinE(s, left) + spinE(s, right)
           -(spinE(x, top) + spinE(x, bot) + spinE(x, left) + spinE(x, right)));
}
*/

// Returns energy difference (< 0 if flip is favorable, >= 0 otherwise)
inline int stencilEnergyDiff(lat_t x, lat_t top, lat_t bot,
                                      lat_t left, lat_t right) {
  return 2*(spinE(x, top) + spinE(x, bot) + spinE(x, left) + spinE(x, right));
}


// Flips the lattice spin at position (i,j) if the single flip criterion matches
inline void singleFlip(Lattice & lat, int i, int j) {

  //~ double dE = stencilEnergyDiff(  // use this without cacheExpEnerDiff()
  int dE = stencilEnergyDiff(  // use this with cacheExpEnerDiff()
    lat[i][j],
    lat.top(i,j),
    lat.bottom(i,j),
    lat.left(i,j),
    lat.right(i,j)
  );

  //~ double p = std::min( 1., exp(-J * dE / (kb*T)) );  // without cacheExpEnerDiff()
  double p = std::min( 1., expEnerDiff[ (dE+8)/4 ] );  // with cacheExpEnerDiff()
  if(drand48() < p) {

    lat[i][j] = lat_t_inv(lat[i][j]);
    Etot += dE;  // should be dE*J actually
    Mag += (lat[i][j] == 1) ? (2) : (-2);

  }

}

// Applies a single flip for every lattice element
inline void systemFlip(Lattice & lat) {

  for(int i = 0; i < lat.size; ++i)
    for(int j = 0; j < lat.size; ++j)
      singleFlip(lat, i, j);

}


#include "accumulator.hpp"

#include <boost/random.hpp>

#include <iostream>

using namespace std;

int main()
{
    cout << "Test Accumulator" << endl;
    cout << "----------------" << endl;
    
    accumulator A(2); //bin size in constructor
    
    //first bin
    A << 1;
    A << 1;
    
    //second bin ("multistream" possible)
    A << 1 << 2;
    
    //not yet relevant bin (patrtial)
    A << 5;
    
    //now the third bin is filled
    A << 5;
    
    //lazy eval: mean and error are only calculated if called (are also not stored)
    cout << "mean(): " << A.mean() << endl;
    cout << "error(): " << A.error() << endl;
    
    //count tells how many bins are filled
    cout << "count(): " << A.count() << endl;
    
    //overview of all relevant informations
    cout << "A: " << A << endl;
    
    accumulator B(A);   //copy ctor
    cout << "B: "  << B << endl;
    
    accumulator C(4);
    C = B;  //also asignable (default asignment operator!)
    cout << "C: "  << C << endl;
    
    
    //real world example
    
    typedef boost::mt19937 engine_type;
    typedef boost::uniform_real<double> dist_type;
    typedef boost::variate_generator<boost::mt19937&,dist_type> rng_type;
    
    engine_type eng(42);
    rng_type rng(eng,dist_type(0,1));
    
    accumulator D(1000);
    
    for( int i = 0; i < 10000000; ++i )
    {
        D << rng();
    }
    
    cout << "D: "  << D << endl;
}

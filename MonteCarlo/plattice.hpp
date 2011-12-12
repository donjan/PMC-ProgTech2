/*******************************************************************************
 * 
 * Periodic lattice - header files
 * Written by Donjan Rodic, 7.11.2011
 * 
 ******************************************************************************/

#ifndef LATICE_HPP
#define LATICE_HPP

#include <iostream>
#include <fstream>
#include <vector>

typedef unsigned char uchar;
typedef bool lat_t;                 // must have equivalents to 1 and invertible

inline lat_t lat_t_inv(lat_t x) {   // so that we can have a flexible lat_t
  return !x;
}

class Lattice {
  public:

  std::vector<std::vector<lat_t> > data;
  int size;

  Lattice(int tsize) : size(tsize) {
    data.resize(tsize);
    for(int i = 0; i < tsize; ++i) {
      data[i] = std::vector<lat_t>(tsize);
    }
  }

  std::vector<lat_t> & operator[](int i) {
    if(i >= size) throw "Out of range access for Lattice!";  // only for outer, don't rely on this
    return data[i];
  }

  inline int top(int i, int j) {
    if(j == 0) j = size;
    return data[i][j-1];
  }
  inline int bottom(int i, int j) {
    if(j == size-1) j = -1;
    return data[i][j+1];
  }
  inline int left(int i, int j) {
    if(i == 0) i = size;
    return data[i-1][j];
  }
  inline int right(int i, int j) {
    if(i == size-1) i = -1;
    return data[i+1][j];
  }


  void print(std::string outfile = "output.ppm", int cellsize = 1) {

    std::ofstream out(outfile.c_str(), std::ios_base::binary);
    out << "P6" << std::endl
        << size*cellsize << " " << size*cellsize << std::endl
        << "255" << std::endl;


    for(int j = 0; j < size; ++j)
      for(int ch = 0; ch < cellsize; ++ch)
        for(int i = 0; i < size; ++i)
          for(int cw = 0; cw < cellsize; ++cw) {
            uchar c = 255 * data[i][j];
            out << c << c << c;
          }

    out.close ();

  }

  inline void snapshot(int k) {                                     // for video

    std::stringstream ss;
    //~ ss.clear(); ss.str("");
    ss << std::setw( 7 ) << std::setfill( '0' ) << k;
    this->print("snapshots/" + ss.str() + ".ppm", 1);
    std::cout << "\nWritten snapshots/" + ss.str() + ".ppm";

  }

};

#endif

/*
Copyright 2011. All rights reserved.
Institute of Measurement and Control Systems
Karlsruhe Institute of Technology, Germany

This file is part of libviso2.
Authors: Andreas Geiger

libviso2 is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or any later version.

libviso2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
libviso2; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/

#ifndef MATRIX_H
#define MATRIX_H
#include "StereoEfficientLargeScale.h"
//#ifndef _MSC_VER
//  #include <stdint.h>
//#else
//  typedef __int8            int8_t;
//  typedef __int16           int16_t;
//  typedef __int32           int32_t;
//  typedef __int64           int64_t;
//  typedef unsigned __int8   uint8_t;
//  typedef unsigned __int16  uint16_t;
//  typedef unsigned __int32  uint32_t;
//  typedef unsigned __int64  uint64_t;
//#endif

#define endll endl << endl // double end line definition
  
typedef double PRECION_FLOAT;      // double precision
//typedef float  PRECION_FLOAT;    // single precision

class Matrix {

public:

  // constructor / deconstructor
  Matrix ();                                                  // init empty 0x0 matrix
  Matrix (const int32_t m,const int32_t n);                   // init empty mxn matrix
  Matrix (const int32_t m,const int32_t n,const PRECION_FLOAT* val_); // init mxn matrix with values from array 'val'
  Matrix (const Matrix &M);                                   // creates deepcopy of M
  ~Matrix ();

  // assignment operator, copies contents of M
  Matrix& operator= (const Matrix &M);

  // copies submatrix of M into array 'val', default values copy whole row/column/matrix
  void getData(PRECION_FLOAT* val_,int32_t i1=0,int32_t j1=0,int32_t i2=-1,int32_t j2=-1);

  // set or get submatrices of current matrix
  Matrix getMat(int32_t i1,int32_t j1,int32_t i2=-1,int32_t j2=-1);
  void   setMat(const Matrix &M,const int32_t i,const int32_t j);

  // set sub-matrix to scalar (default 0), -1 as end replaces whole row/column/matrix
  void setVal(PRECION_FLOAT s,int32_t i1=0,int32_t j1=0,int32_t i2=-1,int32_t j2=-1);

  // set (part of) diagonal to scalar, -1 as end replaces whole diagonal
  void setDiag(PRECION_FLOAT s,int32_t i1=0,int32_t i2=-1);

  // clear matrix
  void zero();
  
  // extract columns with given index
  Matrix extractCols (std::vector<int> idx);

  // create identity matrix
  static Matrix eye (const int32_t m);
  void          eye ();

  // create diagonal matrix with nx1 or 1xn matrix M as elements
  static Matrix diag(const Matrix &M);
  
  // returns the m-by-n matrix whose elements are taken column-wise from M
  static Matrix reshape(const Matrix &M,int32_t m,int32_t n);

  // create 3x3 rotation matrices (convention: http://en.wikipedia.org/wiki/Rotation_matrix)
  static Matrix rotMatX(const PRECION_FLOAT &angle);
  static Matrix rotMatY(const PRECION_FLOAT &angle);
  static Matrix rotMatZ(const PRECION_FLOAT &angle);

  // simple arithmetic operations
  Matrix  operator+ (const Matrix &M); // add matrix
  Matrix  operator- (const Matrix &M); // subtract matrix
  Matrix  operator* (const Matrix &M); // multiply with matrix
  Matrix  operator* (const PRECION_FLOAT &s);  // multiply with scalar
  Matrix  operator/ (const Matrix &M); // divide elementwise by matrix (or vector)
  Matrix  operator/ (const PRECION_FLOAT &s);  // divide by scalar
  Matrix  operator- ();                // negative matrix
  Matrix  operator~ ();                // transpose
  PRECION_FLOAT   l2norm ();                   // euclidean norm (vectors) / frobenius norm (matrices)
  PRECION_FLOAT   mean ();                     // mean of all elements in matrix

  // complex arithmetic operations
  static Matrix cross (const Matrix &a, const Matrix &b);    // cross product of two vectors
  static Matrix inv (const Matrix &M);                       // invert matrix M
  bool   inv ();                                             // invert this matrix
  PRECION_FLOAT  det ();                                             // returns determinant of matrix
  bool   solve (const Matrix &M,PRECION_FLOAT eps=1e-20);            // solve linear system M*x=B, replaces *this and M
  bool   lu(int32_t *idx, PRECION_FLOAT &d, PRECION_FLOAT eps=1e-20);        // replace *this by lower upper decomposition
  void   svd(Matrix &U,Matrix &W,Matrix &V);                 // singular value decomposition *this = U*diag(W)*V^T

  // print matrix to stream
  friend std::ostream& operator<< (std::ostream& out,const Matrix& M);

  // direct data access
  PRECION_FLOAT   **val;
  int32_t   m,n;

private:

  void allocateMemory (const int32_t m_,const int32_t n_);
  void releaseMemory ();
  inline PRECION_FLOAT pythag(PRECION_FLOAT a,PRECION_FLOAT b);

};

#endif // MATRIX_H

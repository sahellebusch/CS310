#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
#include <climits>
#include "Matrix.h"
using namespace std;
typedef unsigned int uint;
#define INF UINT_MAX

int minmult( Matrix<uint> &M,
             Matrix<uint> &P, 
             const vector<uint> &d,
             uint i,
             uint j ) 
{   
    if(M.at(i,j) != INF)
    {
        return M.at(i,j);
    }
    if(i == j)
    {
        M.at(i,j) = 0;
        return M.at(i,j);
    }
    for(uint k = i; k<= j-1; k++)
     {
        uint cost = minmult(M, P, d, i, k) 
                  + minmult(M, P, d, k+1, j)
                  + d.at(i-1)*d.at(k)*d.at(j);
           
            if(cost < M.at(i,j))
            {
                M.at(i,j) = cost;
                P.at(i,j) = k;
            }
     }
     return M.at(i,j);
}

void order(uint i, uint j, const Matrix<uint> &P)
{
    if(i == j )
    {
        cout << "A" << i;
    }
    else
    {
        uint k = P.at(i,j);
        cout << "(";
        order(i,k, P);
        order(k+1, j, P);
        cout << ")";
    }
}



int main()
{
  // read n+1 dimensions in from standard input
  vector< uint > d;

  while( ! cin.eof() )
  {
    uint value;
    if( cin >> value && ! cin.eof() )
      d.push_back( value );
  }
  //insert new line for formatting purposes
  cout << endl;
  uint n = d.size() - 1;

  // the memo table
  Matrix< uint > M( n+1, n+1 );

  // a helper matrix to store the splits
  Matrix< uint > P( n+1, n+1 );
  
  for(uint i = n; i > 0; i--)
    {
        for(uint j = n; j > 0; j--)
        {
            M.at(i,j) = INF;
        }
    }
   
  
  uint i = 1;
  uint j = n;  
  cout << minmult(M, P, d, i, j) << endl;

  // dump the memo table
  for( uint i = 1; i <= n; i++ )
  {
    for( uint j = 1; j <= n; j++ )
      if( i > j )
        cout << "     ";
      else
        cout << setw( 5 ) << M.at( i, j );
    cout << endl;
  } 

  // dump the splits table
  cout << "  i\\j ";
  for( uint i = 2; i <= n; i++ )
    cout << setw( 3 ) << i;
  cout << endl;
  cout << "----+";
  for( uint i = 0; i < n; i++ )
    cout << "---";
  cout << endl;
  
  for( uint i = 1; i < n; i++ )
  {
    cout << setw( 3 ) << i << " | ";
    for( uint j = 2; j <= n; j++ )
      if( i >= j )
        cout << "   ";
      else
        cout << setw( 3 ) << P.at( i, j );
    cout << endl;
  }

  //insert new line for formatting purposes
  cout << endl;
  //print the optimal parenthesization
  order( 1, n, P );
  cout << endl;
}

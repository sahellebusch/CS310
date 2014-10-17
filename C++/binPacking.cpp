// lastname_binpacking.cpp
// framework provided by Jon Beck
// completed by: Sean Hellebusch
// non-optimal bin packing from Neapolitan page 422
//
// expects non-sorted float values 0.0 < x <= 1.0 on standard input

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#define EPSILON_ADJUSTER .0001

using namespace std;
typedef unsigned int uint;

// The greater-than operator to use for algorithm sorting
bool gt( double a, double b )
{
  return b < a;
}

int main()
{
  list< double > S; // the items to be packed into bins
  while( ! cin.eof() )
  {
    double value;
    if( cin >> value && ! cin.eof() )
    {
      assert( value > 0.0 && value <= 1.0 );
      S.push_back( value );
    }
  }

  uint n = S.size();
  uint operations = 0;

  vector< vector< double > > bins; // the bins to be packed with items

  // implementation of Neapolitan's algorithm begins here
  S.sort( gt );

  // you complete the algorithm here
	bool packed = false;
	double currentItem;
	double binTotal;
	vector< double > currentBin;
	vector< double > newBin;
	uint binNumber = 0;
	while( !S.empty() )
	{
	 		currentItem = S.front();
	 		S.pop_front();
	 		packed = false;	 		
	 		binNumber = 0;
	 		while( ( binNumber < bins.size() ) && !packed )
	 		{
	 			binTotal = 0.0;	
	 			//get next bin
	 			//go through and find bin total, add if possible
	 			//if you can pack it, set packed to true
				currentBin = bins.at( binNumber );
				for( uint i = 0; i < currentBin.size(); i++ )
				{
					binTotal += currentBin.at(i);
				}
				operations++;
				if( (binTotal + currentItem) <= ( 1.0 + EPSILON_ADJUSTER ) )
				{
					bins.at( binNumber ).push_back( currentItem );
					packed = true;
				}
				binNumber++;
			}
		if( !packed )
		{
				newBin.erase( newBin.begin(), newBin.end() );
				newBin.push_back( currentItem );
				bins.push_back( newBin );
		}
	}
	
  // report on the final contents of the bins
  cout << "The number of bins is " << bins.size() << endl;
  for( vector< vector< double > >::const_iterator bin = bins.begin(); 
       bin != bins.end(); ++bin )
  {
    cout << "The bin contains: ";

    for( vector< double >::const_iterator item = bin->begin();
         item != bin->end(); ++item )
    {
      cout << *item << ' ';
    }
    cout << endl;
  }
  cout << endl;

  cerr << n << ", " << operations << endl;
  return 0;
}

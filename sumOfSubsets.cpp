#include <iostream>
#include <vector>
#include <cassert>
#include <iomanip>
#include <climits>
#include <math.h>
#include <algorithm>

typedef unsigned int uint;
using namespace std;

//////// Function declerations //////////
void sum_of_subsets( uint index, 
					 uint weight, 
					 uint total, 
					 vector<bool> &include, 
					 vector<uint> &w,
					 uint W );
					 
bool promising ( uint index, 
				 uint weight, 
				 uint W, 
				 vector<uint> w,
				 uint total );
				 
/////////////// Main //////////////////
int main()
{
	vector<uint> w;				// vector of weights
	vector<bool> include;		
	uint W;						// the total
	uint index = 0;
	uint weight = 0;			// the current weight of subsets
	uint total = 0;				// the superset total weight
	while( ! cin.eof() )
  {
    uint value;
    if( cin >> value && ! cin.eof() )
      w.push_back( value );
  }
	// instantiate desired sum, W
	W = w.front();
	// get rid of the first elemen, W
	w.erase( w.begin() );
	// instantiate the include vector to false
	for( uint k = 0; k < w.size(); k++ )
		include.push_back(0);
	// calculate the superset total
	for( uint k = 0; k < w.size(); k++ )
		total += w.at(k);
	cout << include.size() << endl;
	cout << w.size() <<	endl;
		
	// calculate the sum of subsets according to CL argument
	sum_of_subsets( index, weight, total, include, w, W );
	
	// report success 	
	return 0;
}

////////// Function Bodies ///////////

void sum_of_subsets( uint index, 
					 uint weight, 
					 uint total, 
					 vector<bool> &include, 
					 vector<uint> &w, 
					 uint W )
{
	if( promising(index, weight, W, w, total) )
	{	
		if( weight == W )
		{	
			for( uint k = 0; k <= include.size(); k++ )
			{
				if(include.at(k))
					cout << w.at(k) << " ";
			}
			cout << endl;
		}
		else
		{	
				include.at(index + 1) = 1;
				sum_of_subsets( index + 1, 
								weight + w.at(index + 1 ), 
								total - w.at(index + 1),
								include, w, W ) ;
				include.at(index + 1) = 0;
				sum_of_subsets( index + 1, 
								weight, 
								total - w.at(index + 1),
								include, w, W );
		}
	}
}

bool promising ( uint index, 
				 uint weight, 
				 uint W, 
				 vector<uint> w,
				 uint total )
{
	return ( weight + total >= W )
		 && ((weight == W) || (weight + w.at(index+1) <= W));
}













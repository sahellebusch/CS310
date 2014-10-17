//Sean Hellebusch

#include <iostream>
#include <vector>
typedef unsigned int uint;
using namespace std;

void mergesort ( vector<int> & S, 
				uint low, 
				uint mid,
				uint high	)
{
	uint i = low;
	uint j = mid +1;
	uint k = 0;
	vector<int> Temp( high - low + 1 );
	
	while ( i <= mid && j <= high )
	{
		if(  S.at( i ) <= S.at ( j ) )
		{
			Temp.at( k ) = S.at( i );
			i++;
		}
		else
		{
			Temp.at( k ) = S.at( j );
			j++;
		}
		k++;
	}
	
	//copies the remaining lower half to Temp
	while( i <= mid )
	{
		Temp.at( k ) = S.at( i );
		i++;
		k++;
	}
	
	//copies remaining uppern half to Temp
	while( j <= high )
	{
		Temp.at( k ) = S.at( j );
		j++;
		k++;
	}
	
	//new merged Temp into original vector
	for( k = 0; k < Temp.size(); k++ )
	{
		S.at( low + k ) = Temp.at( k );
	}
}

void mergesort( vector<int> & S, 
				uint low, 
				uint high )
{
	if( low != high && high < S.size() )
	{
		uint mid = ( low + high ) / 2;
		mergesort( S, low, mid );
		mergesort( S, mid + 1, high );
		mergesort( S, low, mid, high);
	}
}

int main()
{
	uint counter = 0;
	vector<int> S;
	while( ! cin.eof() )
	{
		int value;
		if( cin >> value && ! cin.eof() )
		{
			S.push_back( value );
			counter++;
		}
	}
	
	mergesort( S, 0, S.size() -1 );
	for( vector<int>::const_iterator i = S.begin(); i != S.end(); i++ )
	{
		cout << *i << ' ';
	}
	cout << endl;
	cout << counter << endl;
	return 0;
	
}
	

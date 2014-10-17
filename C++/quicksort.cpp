/**This is a quicksort Algorithm that sorts an
  *array of integers.
  *
  *-Basic operation is the array element comparisons
  * because it happens the most often in the algorithm.
  *-n is n.
  *-I count basic ops by determining the high - low, which counuts by
  * the number of pivotpoints, then count by each time the pivotpoint is
  * is compared to each element.
  * Author: Sean Hellebusch 
  **/

#include <cstdlib>
#include <iostream>
#include <vector>
typedef unsigned int uint;
using namespace std;

/**
  * splits the vector 
  * @param S the array of integers
  * @param low the lowest element of the array
  * @param high the highest element of the array
  * @param pivotpoint the chosen pivot point
  * @param basic_ops counter for basic operations performed
  *
  **/
void partition(vector<int> & S, 
					int low, 
					int high, 
					int & pivotpoint, 
					int &basic_ops )
{
	int pivotitem = S.at(low);
	int j = low;
	int i;
	for(i = low + 1; i <= high; i++)
	{	
		if(S.at(i) < pivotitem)
		{
			basic_ops++;
			j++;
			swap(S[i], S[j]);
		}
	}
	pivotpoint = j;
	swap(S[low], S[pivotpoint]);
}

/**
  * splits the vector 
  * @param S the array of ints
  * @param low the lowest element of the array
  * @param high the highest element of the array
  * @param pivotpoint the chosen pivot point
  * @param basic_ops counter for basic operations performed
  *
  **/
void quicksort(vector<int> & S, 
					int low,
					int high, 
					int &basic_ops )
{
	int pivotpoint = low;
	
	if( high > low)	
	{
		basic_ops += high - low;	
		partition(S, low, high, pivotpoint, basic_ops);
		quicksort(S, low, pivotpoint -1, basic_ops );
		quicksort(S, pivotpoint + 1, high, basic_ops );
	}	
}

int main()
{
	vector<int> S;
	int basic_ops = 0;
	int n = 0;
	while(!cin.eof() )	
	{
		int value;
		if (cin >> value && !cin.eof())
		{
			S.push_back(value);
			n++;
		}
	}
	
	quicksort(S, 0, S.size()-1, basic_ops);
	for(vector<int>::const_iterator i = S.begin(); i != S.end(); i++)
	{
		cout << *i << ' ';
	}
	cout << endl;
	cout << n << ' ' << basic_ops << endl;
	return 0;
}

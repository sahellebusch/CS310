#include <fstream>
#include <iostream>
#include <queue>
#include <iomanip>
#include <map>
#include <string>
#include <cassert>
#include <sstream>

using namespace std;
typedef unsigned int uint;

struct nodetype
{
  // constructor
  nodetype( char symbol, nodetype * left, nodetype * right) :
    symbol( symbol ), left( left ), right( right )
  { }

  char symbol;
  nodetype* left;
  nodetype* right;
};



/* hexSubstring: the hex value of the leaf character
 * method to convert a hex value into
 * a character.
 */
char convertToChar( string &hexSubstring )  
{
	//string foo = hexSubstring;
	stringstream ss;
	ss << std::hex << hexSubstring;

	uint intvalue;
	ss >> intvalue;
	char letter = (char)intvalue;
	return letter;
}


/* root
 * method to build a Huffman decoding tree
 */
void createDecodingTree(  nodetype* &root, 
		 					nodetype* &iter, 
							string &codeSubstring, 
							char leaf )
{
	string code = codeSubstring;
	nodetype* newLeaf = new nodetype( leaf, NULL, NULL );
	uint index = 0;
	uint codeLength = code.length();
	iter = root;
	
	while( codeLength - 1 > 0 )
	{
		if( code.at(index) == '0' )
		{
			if( iter->left == NULL )
			{
				nodetype* newLeft = new nodetype( '\0', NULL, NULL );
				iter->left = newLeft;
				iter = iter->left;
			}
			else{
				iter = iter->left;
			}
		}
		if( code.at(index) == '1' ) 
		{
			if( iter->right == NULL )
			{
				nodetype* newRight = new nodetype( '\0', NULL, NULL );
				iter->right = newRight;
				iter = iter->right;
			}
			else{
				iter = iter->right;
			}
		}
		codeLength--;
		index++;
	}	
	//now make a new leaf based on the last bit
	if( code.at( code.length() - 1 ) == '0' )
		iter->left = newLeaf;
	else{
		iter->right = newLeaf;
	}
}
			

void recursiveDelete( nodetype* root )
{
  if( root != NULL )
  {
    recursiveDelete( root->left );
    recursiveDelete( root->right );
    delete root;
  }
}


int main(int argc, char *argv[] )
{
	assert( argc == 2 );
	const string fileName = argv[1];
	string lineIn;
	string hexSubstring;
	string codeSubstring;
	char leaf;
	nodetype* root = new nodetype( '\0', NULL, NULL );
	nodetype* iter = root;

	ifstream textFileCode( (fileName + ".code").c_str(), ios::in );
	if( !textFileCode )
	{
		cerr << "Cannot open text file for input" << endl;
		return 1;
	}
	
	while( getline( textFileCode, lineIn ) ) 
	{
		hexSubstring = lineIn.substr(0, 2);
		codeSubstring = lineIn.substr(4, lineIn.length() );
		leaf = convertToChar( hexSubstring );
		createDecodingTree( root, iter, codeSubstring, leaf ); 
	}
	textFileCode.close();
	
	ofstream decodedFile;
	string basefilename = fileName;
	decodedFile.open(( basefilename + ".decoded" ).c_str(), ios:: trunc );
	char characterIn;
	char nextLetter;
	iter = root;
	ifstream textFileEncoded( (fileName + ".encoded").c_str(), ios::in );
	if( !textFileEncoded )
	{
		cerr << "Cannot open text file for input" << endl;
		return 1;
	}
	while( textFileEncoded.get( characterIn ) )
	{
		if( characterIn == '0')
		{
			if( iter->left->symbol != '\0' )
			{
				nextLetter = iter->left->symbol;
				decodedFile << nextLetter;
				iter = root;
			}
			else{
				iter = iter->left;
				}
		}
		else{
				if( iter->right->symbol != '\0' )
				{
					nextLetter = iter->right->symbol;
					decodedFile << nextLetter;
					iter = root;
				}
				else{
						iter = iter->right;
					}
			}
		}		
	textFileEncoded.close();
	
	recursiveDelete( root );
	return 0;
}

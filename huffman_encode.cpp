// encode.cpp
// Jon Beck

// A program which reads a text file and produces a Huffman encoding
// of that file. Any characters outside the range (0 .. 127] are ignored

// It expects the base of the filename on the command line

#include <fstream>
#include <iostream>
#include <queue>
#include <iomanip>
#include <map>
#include <string>
#include <cassert>

using namespace std;
typedef unsigned int uint;

// a class for the nodes of the Huffman tree
struct nodetype
{
  // constructor
  nodetype( char symbol, uint frequency, nodetype * left, nodetype * right) :
    symbol( symbol ), frequency( frequency ), left( left ), right( right )
  { }

  char symbol;
  uint frequency;
  nodetype* left;
  nodetype* right;
};

// a class for comparing two nodetype*'s, required by the priority queue syntax
// we need to define comparison as lhs > rhs, so that least will be the
// highest priority
struct compareNodes : public binary_function<nodetype*, nodetype*, bool>
{
  bool operator()(const nodetype* lhs, const nodetype* rhs) const
  {
    return lhs->frequency > rhs->frequency;
  }
};

//////////////////////////////// Function Prototypes //////////////////////

// a recursive postorder tree traversal function
// it builds the Huffman codes as it descends
void traverseAndCreateCodes( nodetype* root,
			     vector< string > & codes,
			     const string & currentCode );

// a postorder tree traversal to deallocate nodes
void recursiveDelete( nodetype* root );

//////////////////////////////// Main ////////////////////////////////////

int main( int argc, char *argv[] )
{
  // convert the C-style command line parameter to a C++-style string,
  // so that we can do concatenation on it
  assert( argc == 2 );
  const string filename = argv[1];

  ifstream textFile( filename.c_str( ), ios::in );
  if( !textFile ) 
  {
    cerr << "Cannot open text file for input" << endl;
    return 1;
  }

  // the letter histogram, indexed by ASCII codes
  map< char, uint >letterCount;

  // the codes, indexed by ASCII values
  vector < string > codes( 0x80 );
  for( uint i = 0; i < 0x80; i++ )
    codes.at( i ) = "";

  // read one character at a time, and increment that character's frequency
  char characterIn;
  while( textFile.get( characterIn )) 
  {
    if( characterIn > 0 && characterIn <= 0x7F )
    {
      if( letterCount.count( characterIn ) == 0 )
        letterCount.insert( pair< char, uint >( characterIn, 1 ));
      else
        letterCount.at( characterIn )++;
    }
  }

  // we'll hold nodes in a priority queue
  priority_queue < nodetype *, vector< nodetype* >, compareNodes > listOfNodes;

  // iterate through the histogram; for each character, put it on the
  // priority queue
  for( map< char, uint >::const_iterator itr = letterCount.begin( );
       itr != letterCount.end( ); itr++ )
  {
    listOfNodes.push( new nodetype( itr->first, itr->second, NULL, NULL ));
  }

  // repeatedly take the first two things off the queue, make a new
  // node to be their parent, and put the parent back into the queue
  while( listOfNodes.size( ) > 1 ) 
  {
    nodetype* newLeft = listOfNodes.top( );
    listOfNodes.pop( );
    nodetype * newRight = listOfNodes.top( );
    listOfNodes.pop( );
    listOfNodes.push( new nodetype( 0, newRight->frequency + newLeft->frequency,
                                    newLeft, newRight ));
  }

  // now the tree is built, so traverse it, building the codes, and
  // store the codes in a vector indexed by character.

  // start at the root, with an empty code
  traverseAndCreateCodes( listOfNodes.top( ), codes, "" );

  // now codes has each character paired with its code, so dump
  // the list out to the output file
  ofstream codeFile;
  string basefilename = filename;
  basefilename.erase( filename.find( '.' ));
  codeFile.open(( basefilename + ".code" ).c_str( ), ios::trunc );

  if( !codeFile ) 
  {
    cerr << "Cannot open code file for output" << endl;
    return 1;
  }

  for( uint i = 1; i < 128; i++ ) 
  {
    if( codes.at( i ) != "" )
      codeFile << hex << setw( 2 ) << setfill( '0' ) << i << ": " << codes.at( i ) << endl;
  }
  codeFile.close( );

  // finally, re-read the input file and encode it to the output file,
  // using the encoding stored in the vector
  textFile.clear( ); // reset the eof flag
  textFile.seekg( 0, ios::beg ); // reset file pointer to the beginning

  ofstream compressedFile;
  compressedFile.open(( basefilename + ".encoded" ).c_str( ), ios::trunc );
  if( !compressedFile ) 
  {
    cerr << "Cannot open compressed file for output" << endl;
    return 1;
  }

  while( textFile.get( characterIn )) 
  {
    compressedFile << codes.at( characterIn );
  }

  textFile.close( );
  compressedFile << endl;
  compressedFile.close( );

  // now need to delete all the nodes we allocated
  recursiveDelete( listOfNodes.top( ) );

  // we're done; report success and quit
  return 0;
}

///////////////////////// Function Bodies ///////////////////////////

void traverseAndCreateCodes( nodetype* root, vector < string > & codes, 
                             const string & currentCode )
{
  // root: current node
  // codes: char-indexed array of Huffman codes
  // currentCode: as we traverse, this is where we build a up a code, 0
  //              for left and 1 for right

  if( root->symbol == 0 ) // if this is an interior node, recurse
  {
    traverseAndCreateCodes( root->left, codes, currentCode + '0' );
    traverseAndCreateCodes( root->right, codes, currentCode + '1' );
  } 
  else // it is a leaf node, so capture the code
  {
    codes.at( root->symbol ) = currentCode;
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


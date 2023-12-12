
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Parser.h"
#include "Graph.h"

std::string help =
R"("
# MIMPIS, LR1 by Mikhaylova Ekaterina #

  Use: MIMPIS_LR1 <inFile> [<outFile>]
     Input file should include line number
       on the first line and boolean functions
     InFile example:
       1
       a*b+!c+d
     Allowed symbols in functions:
       <A-Za-z>, !, +, *, 0, 1
)";


std::ostream &operator<<( std::ostream &stream, std::vector<char> &arr ) { for( auto sym : arr ) stream << sym; return stream; }


void readFileAndMakeGraph( std::string inFileName, std::string outFileName ) {

    std::string readingString = "";
    std::vector<char> symArray;
    int count = 0;
    Parser parser;

    std::ifstream inFile( inFileName );
    if( !inFile.is_open() )  EXIT( "Couldn't open input file '" + inFileName + "'" );

    inFile >> count;
    std::getline( inFile, readingString ); //read end of line
    if( !count ) EXIT( "There is no a number of fuctions in the beginning of file, or it is equal 0" );

    for( size_t i = 0; i < count; i++ ) {
        symArray.clear();
        readingString.clear();

        std::getline( inFile, readingString );
        if( readingString.empty() ) WARNING( "Unexpected end of file" );
        if( !parser.getSymbolArray( readingString, symArray ) ) { symArray.clear(); }  //WARNING( "Line " + std::to_string( i ) + " has an error" );
        Graph graph( symArray );
        if( !outFileName.empty() ) { graph.saveToOutFile( outFileName ); continue; }
        INFO( graph.print ); 
    }

    inFile.close();
}

int main( int ac, char *av[]) {
    if( ac < 2 ) EXIT( "Too few arguments! Please, use: MIMPIS_LR1 <inFile> [<outFile>]" );
    if( !strcmp( av[1], "--help" ) ) {
        std::cout << help;
        return EXIT_SUCCESS;
    }
    std::string infName = av[ 1 ];
    std::string outfName = "";
    if( ac == 3 ) outfName = av[ 2 ];

    readFileAndMakeGraph( infName, outfName );

    return EXIT_SUCCESS;
}
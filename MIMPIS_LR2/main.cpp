
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Parser.h"
#include "Graph.h"

std::string help =
R"("
# MIMPIS, LR2 by Mikhaylova Ekaterina #

  Use: MIMPIS_LR2 <inFile> [<outFile>]
     Input file should include nodes and edges numbers
       on the first line, then nodes and their weight,
       then edges in format <source sink>
     InFile example:
       2 1
       a 0
       b 2
       a b
     Allowed symbols:
       <A-Za-z> <0-9> .
)";


#define EXIT( message ) { std::cout << "\033[1;31mERROR: \033[0m" << message << std::endl; exit(EXIT_FAILURE); }
#define WARNING( message ) { std::cout << "\033[1;33mWARNING: \033[0m" << message << std::endl; }
#define INFO( message ) { std::cout << "\033[1;32mINFO: \033[0m" << message << std::endl; }

#define INFO( printFunction ) { std::cout  << "\033[1;32m"; printFunction( std::cout  ); std::cout  << "\033[0m" << std::endl; }
#define ERROR( message ) { std::cout  << "\033[1;31mERROR: \033[0m" << message; } //doesn't need endl, cause used inside INFO

std::ostream &operator<<( std::ostream &stream, std::vector<char> &arr ) { for( auto sym : arr ) stream << sym; return stream; }


void readFileAndMakeGraph( std::string inFileName, std::string outFileName ) {

    std::string readingString = "";
    std::vector<char> symArray;
    Parser parser;
    Graph graph;

    std::ifstream inFile( inFileName );
    if( !inFile.is_open() )  EXIT( "Couldn't open input file '" + inFileName + "'" );

    if(!parser.readFile( inFile, graph )) EXIT( "Error in the input file" );
   /* if( !nodes ) EXIT( "There is no nodes number in the beginning of file, or it is equal 0" );
    if( !edges ) EXIT( "There is no edges number in the beginning of file, or it is equal 0" );*/



    inFile.close();
}

int main( int ac, char *av[] ) {
    if( ac < 2 ) EXIT( "Too few arguments! Please, use: MIMPIS_LR1 <inFile> [<outFile>]" );
    if( !strcmp( av[ 1 ], "--help" ) ) {
        std::cout << help;
        return EXIT_SUCCESS;
    }
    std::string infName = av[ 1 ];
    std::string outfName = "";
    if( ac == 3 ) outfName = av[ 2 ];

    readFileAndMakeGraph( infName, outfName );

    return EXIT_SUCCESS;
}
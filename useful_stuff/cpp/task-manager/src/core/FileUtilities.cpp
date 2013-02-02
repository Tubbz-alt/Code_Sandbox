#include "FileUtilities.hpp"

using namespace std;

/**
 * Check if the file exists
 */
bool file_exists( string const& filename ){
    return fs::exists( fs::path( filename ) );
}

/**
 * Delete a file
 */
void file_delete( const string& filename ){

    if( file_exists( filename ) == true )
        fs::remove( fs::path(filename));
}


vector<string> string_split( string const& line, const string& pattern ){

    string pre_split = line;
    vector<string> substrs;

    ba::split( substrs, pre_split, ba::is_any_of(pattern));
    return substrs;

}



std::string string_trim( std::string const& in ){
    
    string out = in;
    ba::trim( out );
    return out;
}

    

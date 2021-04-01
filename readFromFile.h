#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

/**
 * Reads in a file and converts each line in the file to a vector of strings
 * 
 * @param filename The file that is to be read
 * @returns A vector of strings of all the data
 */
vector<string> file_to_vector(const string& filename);

/**
 * Takes all the data and extracts the required information
 * (the source airport, number of stops, and the destination airport)
 * 
 * @param vec A vector of strings containing all the data
 * @returns A vector of strings of only the required information
 */
vector<string*> extract_required_info(const vector<string> vec);


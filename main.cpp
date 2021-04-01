#include <iostream>
#include <vector>
#include <string>

#include "readFromFile.h"
#include "Dijkstra.h"

using namespace std;

int main() {
    vector<string> vec = file_to_vector("tests/smallSample.txt");
    vector<string*> all_data = extract_required_info(vec);
    Dijkstra d(all_data);

    // user input 
    cout << "Shortest path or landmark path? ";
    string option;
    getline(std::cin, option);
    if (option == "shortest path") {
        cout << "From: ";
        string from;
        getline(std::cin, from);
        if (!d.getGraph().vertexExists(from)) {
            std::cout << "Error: '" << from << "' isn't in the graph!\n";
            return 1;
        }

        cout << "To: ";
        string to;
        getline(std::cin, to);
        if (!d.getGraph().vertexExists(to)) {
            std::cout << "Error: '" << to << "' isn't in the graph!\n";
            return 1;
        }
        
        vector<Vertex> shortest_path = d.shortestPath(from, to);
        string s = d.printPath(shortest_path, from, to);
        cout << s << endl;


    } else if (option == "landmark path") { // AER (Sochi) -> LIM (Peru) -> DME (Moscow)
        cout << "From: ";
        string from;
        getline(std::cin, from);
        if (!d.getGraph().vertexExists(from)) {
            std::cout << "Error: '" << from << "' isn't in the graph!\n";
            return 1;
        }

        cout << "Stop: ";
        string stop;
        getline(std::cin, stop);
        if (!d.getGraph().vertexExists(stop)) {
            std::cout << "Error: '" << stop << "' isn't in the graph!\n";
            return 1;
        }

        cout << "To: ";
        string to;
        getline(std::cin, to);
        if (!d.getGraph().vertexExists(to)) {
            std::cout << "Error: '" << to << "' isn't in the graph!\n";
            return 1;
        }
        
        vector<Vertex> landmark_path = d.landmarkPath(from, to, stop);
        string s = d.printLandmarkPath(landmark_path, from, stop, to);
        cout << s << endl;

    }
    return 0;
}
#include <string>
#include <vector>
#include <iostream>

#include "../catch/catch.hpp"
#include "../readFromFile.h"
#include "../Dijkstra.h"
#include "../graph.h"
#include "../edge.h"

using namespace std;

TEST_CASE("Verify that file_to_vector works on a small example") {
	vector<string> actual = file_to_vector("tests/smallSample.txt");

    vector<string> expected = {"2B,410,AER,2965,KZN,2966,,3,CR2",
                                "2B,410,AER,2965,KZN,2966,,1,CR2",  
                                "2B,410,ASF,2966,DME,2965,,0,CR2", 
                                "2B,410,ASF,2966,MRV,2965,,0,CR2", 
                                "2B,410,CEK,2968,KGD,4029,,0,CR2", 
                                "2B,410,CEK,2968,DME,4029,,0,CR2", 
                                "2B,410,DME,4029,LIM,2812,,0,CR2", 
                                "2B,410,DME,4029,AER,6156,,0,CR2",
                                "2B,410,DME,4029,UUA,6156,,0,CR2", 
                                "2B,410,EGO,6156,KGD,2812,,1,CR2", 
                                "2I,8359,CUZ,2812,LIM,4029,,0,142", 
                                "141",
                                "2B,410,CEK,2968,LIM,4029,,0,CR2"};

	REQUIRE(expected == actual);
}

TEST_CASE("Verify that extract_required_info works correctly") {
	vector<string> vec = file_to_vector("tests/smallSample.txt");
    vector<string*> actual = extract_required_info(vec);

    vector<string> expected = {"AER,3,KZN",
                                "AER,1,KZN",
                                "ASF,0,DME",
                                "ASF,0,MRV",
                                "CEK,0,KGD",
                                "CEK,0,DME",
                                "DME,0,LIM",
                                "DME,0,AER",
                                "DME,0,UUA",
                                "EGO,1,KGD",
                                "CUZ,0,LIM",
                                "CEK,0,LIM"};

    for (unsigned i = 0; i < expected.size(); i++) {
        REQUIRE(expected[i] == *actual[i]);
    }
}

TEST_CASE("Dijkstra(start, all_data) constructor creates the correct vertices") {
    vector<string> vec = file_to_vector("tests/smallSample.txt");
    vector<string*> all_data = extract_required_info(vec);
    Dijkstra d(all_data);
    const Graph & g = d.getGraph();

    REQUIRE(g.vertexExists("AER"));
    REQUIRE(g.vertexExists("KZN"));
    REQUIRE(g.vertexExists("ASF"));
    REQUIRE(g.vertexExists("MRV"));
    REQUIRE(g.vertexExists("CEK"));
    REQUIRE(g.vertexExists("DME"));
    REQUIRE(g.vertexExists("UUA"));
    REQUIRE(g.vertexExists("EGO"));
    REQUIRE(g.vertexExists("KGD"));
    REQUIRE(g.vertexExists("CUZ"));
    REQUIRE(g.vertexExists("LIM"));
    REQUIRE(g.getVertices().size() == 11);
}

TEST_CASE("Dijkstra(start, all_data) constructor creates the correct edges") {
    vector<string> vec = file_to_vector("tests/smallSample.txt");
    vector<string*> all_data = extract_required_info(vec);
    Dijkstra d(all_data);
    const Graph & g = d.getGraph();

    REQUIRE(g.edgeExists("AER", "KZN"));
    REQUIRE(g.edgeExists("ASF", "DME"));
    REQUIRE(g.edgeExists("ASF", "MRV"));
    REQUIRE(g.edgeExists("CEK", "KGD"));
    REQUIRE(g.edgeExists("CEK", "DME"));
    REQUIRE(g.edgeExists("DME", "LIM"));
    REQUIRE(g.edgeExists("DME", "AER"));
    REQUIRE(g.edgeExists("DME", "UUA"));
    REQUIRE(g.edgeExists("EGO", "KGD"));
    REQUIRE(g.edgeExists("CUZ", "LIM"));
    REQUIRE(g.edgeExists("CEK", "LIM"));
    REQUIRE(g.getEdges().size() == 11);

}

TEST_CASE("Shortest path accurately gets the shortest path") {
    vector<string> vec = file_to_vector("tests/smallSample.txt");
    vector<string*> all_data = extract_required_info(vec);
    Dijkstra d(all_data);
    vector<Vertex> actual = d.shortestPath("CEK", "KZN");

    vector<Vertex> expected = {"KZN","AER","DME","CEK"};

    REQUIRE(expected == actual);
}

TEST_CASE("Shortest path accurately gets the direct flight path") {
    vector<string> vec = file_to_vector("tests/smallSample.txt");
    vector<string*> all_data = extract_required_info(vec);
    Dijkstra d(all_data);
    vector<Vertex> actual = d.shortestPath("AER", "KZN");

    vector<Vertex> expected = {"KZN", "AER"};

    REQUIRE(expected == actual);
}

TEST_CASE("Shortest path accurately gets if there is no path") {
    vector<string> vec = file_to_vector("tests/smallSample.txt");
    vector<string*> all_data = extract_required_info(vec);
    Dijkstra d(all_data);
    vector<Vertex> actual = d.shortestPath("AER", "LIM");

    vector<Vertex> expected = {};

    REQUIRE(expected == actual);

    string s = d.printPath(actual, "AER", "LIM");
    REQUIRE(s == "There is no path from AER -> LIM :(");
}

TEST_CASE("Landmark path accurately gets the shortest path from source to destination with a stop in the middle") {
    vector<string> vec = file_to_vector("tests/smallSample.txt");
    vector<string*> all_data = extract_required_info(vec);
    Dijkstra d(all_data);
    vector<Vertex> actual = d.landmarkPath("CEK", "LIM", "DME"); // note that there is a direct route from CEK -> LIM

    vector<Vertex> expected = {"LIM", "DME", "CEK"};

    REQUIRE(expected == actual);

    string s = d.printLandmarkPath(actual, "CEK", "DME", "LIM");
    REQUIRE(s == "Shortest path from CEK -> DME -> LIM: CEK -> DME -> LIM");
}

TEST_CASE("Landmark path accurately gets the shortest path if there is no path from source to stop") {
   vector<string> vec = file_to_vector("tests/smallSample.txt");
   vector<string*> all_data = extract_required_info(vec);
   Dijkstra d(all_data); 
   vector<Vertex> actual = d.landmarkPath("ASF", "CEK", "DME");

   vector<Vertex> expected = {};

   REQUIRE(expected == actual);

   string s = d.printLandmarkPath(actual, "ASF", "DME", "CEK");
   REQUIRE(s == "There is no path from ASF -> DME -> CEK :(");
}

TEST_CASE("Landmark path accurately gets the shortest path if there is no path from stop to destination") {
   vector<string> vec = file_to_vector("tests/smallSample.txt");
   vector<string*> all_data = extract_required_info(vec);
   Dijkstra d(all_data); 
   vector<Vertex> actual = d.landmarkPath("AER", "KZN", "DME");
   
   vector<Vertex> expected = {};
   
   REQUIRE(expected == actual);
   
   string s = d.printLandmarkPath(actual, "AER", "DME", "KZN");
   REQUIRE(s == "There is no path from AER -> DME -> KZN :(");;
}
#pragma once

#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <queue>

#include "graph.h"
#include "edge.h"
using namespace std;

class Dijkstra {
    public:
        /**
         * Constructor to create a graph with the airports as the vertices, the routes as
         * the edges, and the shortest path as the edge weights.
         * 
         * @param start The starting vertex
         * @param all_data All of the data needed to form the vertices, edges, and edge weights of the graph
         */
        Dijkstra(vector<string*> all_data);

        /**
         * Calulates the shortest path between two vertices.
         * 
         */
        vector<Vertex> shortestPath(Vertex source, Vertex dest);

        /**
         * Returns concatanated string with the shortest path
         * @param dest The destination vertex
         */
        string printPath(vector<Vertex> path, Vertex source, Vertex dest);

        /**
         * *
         * Calls dijkstra's algorithm on source -> stop and stop -> dest 
         * to find landmark path (shortest path between source and dest while 
         * stopping through stop)
         * @param source The starting vertex
         * @param stop The vertex of the stop in the middle
         * @param dest The ending vertex
         * @returns A vector of vertices
         * **/

        vector<Vertex> landmarkPath(Vertex source, Vertex dest, Vertex stop);

        /**
         * Returns concatanated string with the shortest path
         * @param dest The destination vertex
         */
        string printLandmarkPath(vector<Vertex> path, Vertex source, Vertex stop, Vertex destination);

        /**
         * Returns a constant reference to the state space graph.
         * 
         * @returns A constant reference to the state space graph.
         */
        const Graph & getGraph() const;


        /**
         * Struct used to compare edgeweights 
         */
        struct comp {
            bool operator() (const pair<Vertex, int> & a, const pair<Vertex, int> & b) {
                return a.second > b.second;
            }
        };

    private:
        Graph g_;
        map<Vertex, int> vertex_to_val;
};
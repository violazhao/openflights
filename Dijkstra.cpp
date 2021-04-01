#include "Dijkstra.h"

using namespace std;

Dijkstra::Dijkstra(vector<string *> all_data) : g_(true, true)
{
    for (unsigned i = 0; i < all_data.size(); i++)
    {
        vector<string> vec;
        stringstream ss(*all_data[i]);
        while (ss.good())
        {
            string substr;
            getline(ss, substr, ',');
            vec.push_back(substr);
        }

        if (!g_.vertexExists(vec[0]))
        {
            g_.insertVertex(vec[0]);
        }
        if (!g_.vertexExists(vec[2]))
        {
            g_.insertVertex(vec[2]);
        }
        if (!g_.edgeExists(vec[0], vec[2]))
        {
            g_.insertEdge(vec[0], vec[2]);
            g_.setEdgeWeight(vec[0], vec[2], INT_MAX);
        }
        if (g_.getEdgeWeight(vec[0], vec[2]) > stoi(vec[1]))
        {
            g_.setEdgeWeight(vec[0], vec[2], stoi(vec[1]));
        }
    }
}

vector<Vertex> Dijkstra::shortestPath(Vertex source, Vertex dest)
{
    map<Vertex, int> dist;
    map<Vertex, Vertex> prev;
    map<Vertex, bool> visited;
    vector<Vertex> path;
    priority_queue<pair<Vertex, int>, vector<pair<Vertex, int>>, comp> min_heap;

    for (Vertex v : g_.getVertices())
    {
        dist[v] = INT_MAX;
        prev[v] = "";
    }

    dist[source] = 0;
    min_heap.push(make_pair(source, 0));

    while (!min_heap.empty())
    {
        Vertex top = min_heap.top().first;
        min_heap.pop();

        if (top == dest)
        {
            if (top == source || prev[top] != "")
            {
                while (top != "")
                {
                    path.push_back(top);
                    top = prev[top];
                }
            }
            break;
        }
        for (Vertex adj : g_.getAdjacent(top))
        {
            int alt = dist[top] + g_.getEdgeWeight(top, adj);
            if (alt < dist[adj])
            {
                dist[adj] = alt;
                prev[adj] = top;
                min_heap.push(make_pair(adj, dist[adj]));
            }
        }
    }
    return path;
}

string Dijkstra::printPath(vector<Vertex> path, Vertex source, Vertex dest)
{
    if (path.empty())
    {
        string s = "There is no path from " + source + " -> " + dest + " :(";
        return s;
    }
    else
    {
        string str = "Shortest path from " + source + " -> " + dest + ": ";
        stringstream ss("");
        ss << str;
        for (int i = path.size() - 1; i >= 0; i--)
        {
            if (i == 0)
            {
                ss << path[i];
            }
            else
            {
                ss << path[i] + " -> ";
            }
        }
        return ss.str();
    }
}

vector<Vertex> Dijkstra::landmarkPath(Vertex source, Vertex dest, Vertex stop)
{
    vector<Vertex> first = shortestPath(source, stop);
    if (first.empty())
    {
        return first;
    }
    vector<Vertex> second = shortestPath(stop, dest);
    if (second.empty())
    {
        return second;
    }
    // remove the duplicated stop vector
    first.erase(first.begin());
    second.insert(second.end(), first.begin(), first.end());
    return second;
}


string Dijkstra::printLandmarkPath(vector<Vertex> path, Vertex source, Vertex stop, Vertex dest)
{
    if (path.empty())
    {
        string s = "There is no path from " + source + " -> " + stop + " -> " + dest + " :(";
        return s;
    }
    else
    {
        string str = "Shortest path from " + source + " -> " + stop + " -> " + dest + ": ";
        stringstream ss("");
        ss << str;
        for (int i = path.size() - 1; i >= 0; i--)
        {
            if (i == 0)
            {
                ss << path[i];
            }
            else
            {
                ss << path[i] + " -> ";
            }
        }
        return ss.str();
    }
}

const Graph &Dijkstra::getGraph() const
{
    return g_;
}
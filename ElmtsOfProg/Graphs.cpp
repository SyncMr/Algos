#include <iostream>
#include <vector>
using namespace std;

// This is a Bi-Directional Graph
class Graph
{
    private:
        class Vertex; // Forward Declaration

        vector<Vertex> vertices;

        class Edge
        {
            public:
                Vertex& _orig;

                Vertex& _dest;
                uint32_t _weight;

                Edge(Vertex& orig, Vertex& dest, uint32_t weight) : _orig(orig),
                                                                    _dest(dest),
                                                                    _weight(weight) { }

                Vertex& getOrig() { return _orig; }
                Vertex& getDest() { return _dest; }
                uint32_t getWeight() { return _weight; }
        };

        class Vertex
        {
            public:
                uint32_t _id;
                string _data;
                vector<Edge> _edges;

                Vertex(uint32_t id) : _id(id) { }

                void addEdgeToVertex(Edge& edge)
                {
                    _edges.push_back(edge);
                }
        };

    public:
        void addEdge(Vertex& orig, Vertex& dest, uint32_t weight)
        {
            Edge edge(orig, dest, weight);
            orig.addEdgeToVertex(edge);
            dest.addEdgeToVertex(edge);
        }
};


int main()
{
    cout << endl;
    return 0;
}

/*
void bfs(vertex st)
{
    vector <vertex> vertQue;
    vertQue.push(st);
    st.setVisited(true);

    while (!vertQue.empty())
    {
        vertex temp = vertQue.front();
        vertQue.pop();

        for(auto itr = temp.begin(); itr != temp.end(); itr.getNext())
        {
            if (!itr.getVisited())
            {
                vertQue.push(itr);
                temp.setVisted(true);
            }
        }

    }
}

void dfs(vertex st)
{
    st.setVisited(true);

    for (auto itr = st.begin(); itr != st.end(); itr.getNext())
    {
        if (!itr.getVisited())
        {
            dfs(itr);
        }
    }
}
*/


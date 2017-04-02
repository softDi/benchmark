#include <iostream>
#include <random>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/depth_first_search.hpp>

using namespace std;
using namespace boost;

class cVertex
{

};

class cEdge
{
public:
    void Weight( double w )
    {
        myWeight = w;
    }
    int Weight()
    {
        return myWeight;
    }
    void negWeight()
    {
        myWeight = - myWeight;
    }

    int myWeight;
};

typedef adjacency_list<
vecS, vecS,  directedS,
      cVertex, cEdge  > graph_t;
typedef graph_traits< graph_t >::vertex_iterator vit_t;
typedef graph_traits< graph_t >::edge_iterator eit_t;
typedef graph_traits< graph_t >::edge_descriptor ed_t;

graph_t theGraph;

class cPredecessorMap
{
public:

    cPredecessorMap(graph_t& g )
        : myGraph( g )
    {
        p.resize( num_vertices(myGraph) );
    }
    vector<int>::iterator
    begin()
    {
        return p.begin();
    }

    vector<int>
    Path( int start, int end )
    {

        vector<int> path ;
        int next = end;
        while ( next != start )
        {
            path.push_back( next );
            next = p[ next ];
        }
        path.push_back( start );

        // reverse into path from to
        reverse(path.begin(),path.end());

        return path;
    }
private:
    graph_t& myGraph;
    vector<int> p;

};

void Add( int src, int dst, int weight )
{
    theGraph[add_edge( src, dst, theGraph ).first].Weight( weight );
}

void Construct()
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> dis(0,9);
    for( int kvertex = 0; kvertex < 10; kvertex++ )
        add_vertex( theGraph );
    // connect successive vertices with random weights
    for( int kvertex = 1; kvertex < 10; kvertex++ )
        Add( kvertex-1, kvertex, dis( gen ) );
    // connect random edges
    for( int krandom = 0; krandom < 3; krandom++ )
    {
        int v1, v2;
        do
        {
            v1 = dis(gen);
            v2 = dis(gen);
        }
        while( v1 == v2 );
        if( v1 > v2 )
        {
            int tmp;
            tmp = v1;
            v1 = v2;
            v2 = tmp;
        }
        Add( dis(gen), dis(gen), dis( gen ));
    }
}
void Construct2()
{
    for( int kvertex = 0; kvertex < 3; kvertex++ )
        add_vertex( theGraph );

    Add( 0, 1, 1 );
    Add( 0, 2, 2.2 );
    Add( 1, 2, 3.0789 );
}

void ConstructWithCycle()
{
    for( int kvertex = 0; kvertex < 10; kvertex++ )
        add_vertex( theGraph );
    // connect successive vertices with random weights
    for( int kvertex = 1; kvertex < 10; kvertex++ )
        Add( kvertex-1, kvertex, 1 );
    Add( 6, 4, 1 );
    Add( 7, 3, 1.2121 );
    Add( 2, 4, 10.00004545 );

}

void DisplayEdges()
{
    graph_traits<graph_t>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(theGraph); ei != ei_end; ++ei)
    {
        std::cout << "(" << source(*ei, theGraph)
                  << "," << target(*ei, theGraph)
                  << ", w= " << theGraph[ *ei ].Weight()
                  << " )\n ";

    }
    std::cout << std::endl;
}

bool TopSort()
{
    try
    {
        std::vector< int > c;
        topological_sort(theGraph, std::back_inserter(c));
    }
    catch( not_a_dag )
    {
        cout << "not a dag\n";
        return false;
    }
    cout << "top sort OK\n";
    return true;
}
/* Find longest path through the graph
    @param[in] g the graph
    @param[in] start vertex
    @param[in] end vertex
    @param[out] path of vertices
    @param[out] dist length of path
*/
void Longest(
    graph_t& g,
    int start,
    int end,
    vector<int>& path,
    int& dist )
{
    // create copy of graph with negative weights
    graph_t negGraph = g;
    graph_traits<graph_t>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(negGraph); ei != ei_end; ++ei)
    {
        negGraph[ *ei ].negWeight( );
    }

    // find shortest paths through negative weight graph
    int N = num_vertices(negGraph);
    cPredecessorMap pmap( theGraph );
    vector<int> distance(N);
    bellman_ford_shortest_paths(
        negGraph,
        N,
        weight_map(get(&cEdge::myWeight, negGraph))
        .predecessor_map(make_iterator_property_map(pmap.begin(), get(vertex_index, negGraph)))
        .distance_map(&distance[0])
        .root_vertex( start )
    );

    path = pmap.Path(start,end);

    dist = - distance[ end ];
}

class dag_visitor:public default_dfs_visitor
{

public:
    unsigned int * src;
    unsigned int * dst;
    template < typename Edge, typename Graph >
    void back_edge( Edge e, Graph& g)
    {
        *src = source( e, g );
        *dst = target( e, g );
        throw runtime_error("cyclic");
    }
};

void ConvertToDAG( graph_t& g)
{
    dag_visitor vis;
    unsigned int src, dst;
    vis.src = &src;
    vis.dst = &dst;
    bool cyclic = true;
    while( cyclic )
    {
        try
        {
            depth_first_search(g, visitor(vis));
            cyclic = false;
        }
        catch( runtime_error& e )
        {
            cyclic = true;
             cout << "removing " << src << " -> " << dst << endl;
            remove_edge( src, dst, g );
        }
    }

}
int main()
{

    ConstructWithCycle();

    // create copy to be converted to DAG
    graph_t dag( theGraph );
    ConvertToDAG( dag );

    // find longest path from first to last vertex
    vector< int > path;
    int dist;
    Longest( dag, 0, 9, path, dist );

    DisplayEdges();
    cout << "Longest path: ";
    for( int v : path )
        cout << v << " ";
    cout << " length " << dist << endl;


    return 0;
}

#include <iostream>
#include "CGraph.h"
#include "CJASON.h"

using namespace std;



int main()
{
    CJASON airport("JSON/airports.json");
    //airport.print();

    /*for( int i=0;i<airport.generateEdges().size();i++){
        cout<<airport.generateEdges()[i]->src<<endl;
    }*/

    DirectedGraph graph(airport.generateEdges());

    //graph.remove(1,5);
    //graph.remove(1,2);
    //graph.remove(1,4);
    //graph.remove(1,3);
    //graph.remove(10,5446);

    std::cout << "nodos: "<< graph.getNumberNodes() << std::endl;
    std::cout  << "edges: "<< graph.getNumberEdges() << std::endl;
    std::cout  << "density: "<< graph.getDensity() << std::endl;

    graph.printAdjecentList();
    std::cout<<std::endl<<"HOlA"<<std::endl;
    graph.delete_node(7275);
    graph.printAdjecentList();


    return 0;
}
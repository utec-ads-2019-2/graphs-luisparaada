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

<<<<<<< Updated upstream
    Graph graph(airport.generateEdges(), airport.getNumberAirports());
    graph.remove(1,2);
    graph.remove(2,1);
    graph.remove(12,18);
=======
    DirectedGraph graph(airport.generateEdges());

//    graph.removeEdges(1, 5);
//    graph.removeEdges(1, 2);
//    graph.removeEdges(1, 4);
//    graph.removeEdges(1, 3);
//    graph.removeEdges(10,5446);

    std::cout << "nodos: "<< graph.getNumberNodes() << std::endl;
    std::cout  << "edges: "<< graph.getNumberEdges() << std::endl;
    std::cout  << "density: "<< graph.getDensity() << std::endl;
>>>>>>> Stashed changes

    graph.printAdjecentList();


    return 0;
}
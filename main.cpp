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

    Graph graph(airport.generateEdges(), airport.getNumberAirports());
    graph.remove(1,2);
    graph.remove(2,1);
    graph.remove(12,18);

    graph.printAdjecentList();


    return 0;
}
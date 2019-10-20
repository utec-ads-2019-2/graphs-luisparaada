//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CJASON_H
#define GRAPHS_LUISPARAADA_CJASON_H

#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace rapidjson;


class CJASON{
private:
    std::string filename;
    Document d;
    std::vector<Edge*> vec;

    double getDistanceFromCoordenatesHaversine(double lat1, double lon1, double lat2, double lon2);

public:
    CJASON(std::string filename) : filename(filename) {
        FILE* fp = fopen(filename.c_str(), "r"); //mode: rb para windows
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));

        d.ParseStream(is);

        fclose(fp);
    }


    void print(){
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        d.Accept(writer);
        std::cout << buffer.GetString() << std::endl;
    };
    void printIDandDestination();

    int getNumberAirports(){
        return d.Size();
    }

    int maxId(){
        int temp = 0;
        for(auto &ele : vec){
            if(temp < ele->src)
                temp = ele->src;
        }
        return temp;
    }

    std::vector<Edge*> generateEdges(){

        std::map<int, std::pair<double, double>> coordenates;

        //Creo el Edge con el From to Destination

        for(auto itr = d.Begin(); itr != d.End() ; ++itr){
            if (itr->HasMember("Id")) {
                auto idFrom = (*itr)["Id"].GetString();

                auto Long = (*itr)["Longitude"].GetString();
                if(isalpha(Long[0])) Long = "0";

                auto Lat = (*itr)["Latitude"].GetString();
                if(isalpha(Lat[0])) Lat = "0";

                coordenates[std::stoi(idFrom)] = std::make_pair(std::stod(Long),std::stod(Lat));

                const Value& a = (*itr)["destinations"];
                for (SizeType i = 0; i < a.Size(); i++){
                    vec.push_back(new Edge(idFrom,a[i].GetString()));
                }
            } else {
                throw std::invalid_argument( "NO existe el campo Id en un objeto del JASON" );
            }
        }

        //Actualizo la distancia en el Edge

        for(auto &elem : vec){
            //.FIRST -> LONGITUDE
            //.SECOND -> LATITUDE
            elem->weight = getDistanceFromCoordenatesHaversine(coordenates[elem->src].second,coordenates[elem->src].first,coordenates[elem->dest].second,coordenates[elem->dest].first);
        }


        return vec;
    }


};

double CJASON::getDistanceFromCoordenatesHaversine(double lat1, double lon1, double lat2, double lon2) {
    // distance between latitudes and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));

    return rad * c;

    // Algoritmo HARVESINE recopilado de: https://www.geeksforgeeks.org/haversine-formula-to-find-distance-between-two-points-on-a-sphere/
}

void CJASON::printIDandDestination() {
    for(auto itr = d.Begin(); itr != d.End() ; ++itr){
        if (itr->HasMember("Id")) {
            auto idFrom = (*itr)["Id"].GetString();
            std:: cout << "ID -> " << idFrom << std::endl;
            const Value& a = (*itr)["destinations"];
            for (SizeType i = 0; i < a.Size(); i++)
                std::cout << "a[" << i << "] = " << a[i].GetString() << std::endl;

            std::cout << std::endl;
        }
    }
}



#endif //GRAPHS_LUISPARAADA_CJASON_H

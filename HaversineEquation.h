//
// Created by Christian Ledgard on 10/27/19.
//

#ifndef GRAPHS_LUISPARAADA_HAVERSINEEQUATION_H
#define GRAPHS_LUISPARAADA_HAVERSINEEQUATION_H

#include <cmath>
#include "typedef.h"

tipoDouble getDistanceFromCoordenatesHaversine(tipoDouble lat1, tipoDouble lon1, tipoDouble lat2, tipoDouble lon2) {
    // distance between latitudes and longitudes
    tipoDouble dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    tipoDouble dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    tipoDouble a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    tipoDouble rad = 6371;
    tipoDouble c = 2 * asin(sqrt(a));

    return rad * c;

    // Algoritmo HARVESINE recopilado de: https://www.geeksforgeeks.org/haversine-formula-to-find-distance-between-two-points-on-a-sphere/

}


#endif //GRAPHS_LUISPARAADA_HAVERSINEEQUATION_H

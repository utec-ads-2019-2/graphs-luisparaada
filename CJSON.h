//
// Created by Christian Ledgard on 10/18/19.
//

#ifndef GRAPHS_LUISPARAADA_CJSON_H
#define GRAPHS_LUISPARAADA_CJSON_H

#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace rapidjson;


class CJSON{
private:
    std::string filename;
    Document d;

public:
    explicit CJSON(const std::string& filename, const char *const mode = "r") : filename(filename) {

        FILE* fp = fopen(filename.c_str(), mode);
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

    void printIDandDestination(){
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
    };

    int getNumberAirports(){
        return d.Size();
    }

    const Document &getDocument() const {
        return d;
    }


};


#endif //GRAPHS_LUISPARAADA_CJSON_H

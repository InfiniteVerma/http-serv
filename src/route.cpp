#include "route.h"
#include <iostream>

void Route::get(const std::string &path, FUNCTION handler) {
    std::cout << "Route::get called with path " << path << std::endl;
    routes.insert({path, handler});
}

std::string Route::execute(Request request, Response response,
        const std::string &path, const std::string &subPath) {
    
    std::cout << "Route::execute BEGIN " << path << ": subPath :" << subPath << ":" << std::endl;
    // reached here after finding route base url. 
    // Now searching for specific subpath

    for (auto it = routes.begin(); it != routes.end(); ++it) {
        if(it->first == subPath) {
            std::cout << "Found subpath! " << it->first << ":" << std::endl;

            FUNCTION hlr = it->second;
            return hlr(request, response);
        }
    }

    return "{\"msg\" : \"TODO response!\"}";
}

void Route::prettyPrint() {
    std::cout << "Printing routes added to this route object: \n";
    int i = 1;
    for (auto it = routes.begin(); it != routes.end(); ++it) {

        std::cout << i << ": " << it->first << std::endl;
        ++i;
    }
    std::cout << "-------------------------------------------" << std::endl;
}

std::string handle404() { return "{\"msg\" : \"Route not found!\"}"; }

std::string Route::return404() { return handle404(); }

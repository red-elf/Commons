//
// Created by milosvasic on 16.08.22.
//

#ifndef COMMONS_COMMONS_H
#define COMMONS_COMMONS_H

#include <string>

namespace Commons {

    namespace Strings {

        void tokenize(std::string const &str, const char delim, std::list<std::string> &out) {

            size_t start;
            size_t end = 0;

            while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {

                end = str.find(delim, start);
                out.push_back(str.substr(start, end - start));
            }
        }
    }
}

#endif //COMMONS_COMMONS_H

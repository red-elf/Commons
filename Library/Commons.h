//
// Created by milosvasic on 16.08.22.
//

#ifndef COMMONS_COMMONS_H
#define COMMONS_COMMONS_H

#include <string>
#include <fstream>
#include <iostream>

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

    namespace IO {

        auto read_file(std::string_view path) -> std::string {

            constexpr auto read_size = std::size_t(4096);
            auto stream = std::ifstream(path.data());
            stream.exceptions(std::ios_base::badbit);

            auto out = std::string();
            auto buf = std::string(read_size, '\0');
            while (stream.read(&buf[0], read_size)) {

                out.append(buf, 0, stream.gcount());
            }
            out.append(buf, 0, stream.gcount());
            return out;
        }
    }
}

#endif //COMMONS_COMMONS_H

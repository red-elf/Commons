//
// Created by milosvasic on 16.08.22.
//

#ifndef COMMONS_COMMONS_H
#define COMMONS_COMMONS_H

#include <string>
#include <fstream>
#include <iostream>
#include <list>

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

        std::string &eraseBetween(std::string &subject, std::string from, std::string to) {

            std::size_t begin = subject.find(from);
            std::size_t end = subject.find(to);

            if (begin != std::string::npos && end != std::string::npos) {

                return subject.erase(begin, subject.length() - (end - begin + 2));
            }
            return subject;
        }

        std::string eraseAllBetween(std::string &subject, std::string opening, std::string closure) {

            std::string::size_type begin, end;

            while ((begin = subject.find(opening)) != std::string::npos) {

                if (((end = subject.find(closure)) != std::string::npos) && (end > begin)) {

                    subject.erase(begin, end - begin + closure.size());

                } else break;
            }
            return subject;
        }

        std::string removeAfter(std::string str, std::string from) {

            std::string::size_type begin, end;

            while ((begin = str.find(from)) != std::string::npos) {

                end = str.find_last_of('\n');

                if (end != std::string::npos && end > begin) {

                    str.erase(begin, end - begin + 1);

                } else break;
            }
            return str;
        }

        std::string removeComments(std::string str) {

            return eraseAllBetween(str, "/*", "*/");
        }
    }

    namespace IO {

        auto readFile(std::string_view path) -> std::string {

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

        void writeFile(std::string &what, std::string where) {

            std::ofstream out(where);
            out << what;
            out.close();
        }

        void appendToFile(std::string &what, std::string where) {

            std::ofstream out;
            out.open(where, std::ios_base::app);
            out << what;
            out.close();
        }
    }
}

#endif //COMMONS_COMMONS_H

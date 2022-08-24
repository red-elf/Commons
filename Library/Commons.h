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

        std::string trim(

                const std::string &str,
                const std::string &whitespace = " \t"

        ) {

            const auto strBegin = str.find_first_not_of(whitespace);

            if (strBegin == std::string::npos) {

                return ""; // no content
            }

            const auto strEnd = str.find_last_not_of(whitespace);
            const auto strRange = strEnd - strBegin + 1;

            return str.substr(strBegin, strRange);
        }

        std::string reduce(

                const std::string &str,
                const std::string &fill = " ",
                const std::string &whitespace = " \t"

        ) {

            // trim first
            auto result = trim(str, whitespace);

            // replace sub ranges
            auto beginSpace = result.find_first_of(whitespace);

            while (beginSpace != std::string::npos) {

                const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
                const auto range = endSpace - beginSpace;

                result.replace(beginSpace, range, fill);

                const auto newStart = beginSpace + fill.length();
                beginSpace = result.find_first_of(whitespace, newStart);
            }

            return result;
        }

        std::string &eraseBetween(

                std::string &subject,
                const std::string &from,
                const std::string &to

        ) {

            size_t begin = subject.find(from);
            size_t end = subject.find_last_of(to);

            if (std::string::npos != begin && std::string::npos != end && begin <= end) {

                return subject.erase(begin, end - begin + 1);
            }
            return subject;
        }

        std::string eraseAllBetween(

                std::string &subject,
                const std::string &opening,
                const std::string &closure

        ) {

            std::string::size_type begin, end;

            while ((begin = subject.find(opening)) != std::string::npos) {

                if (((end = subject.find(closure)) != std::string::npos) && (end > begin)) {

                    subject.erase(begin, end - begin + closure.size());

                } else break;
            }
            return subject;
        }

        std::string removeAfter(

                std::string str,
                const std::string &from
        ) {

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

        void writeFile(std::string &what, const std::string &where) {

            std::ofstream out(where);
            out << what;
            out.close();
        }

        void appendToFile(std::string &what, const std::string &where) {

            std::ofstream out;
            out.open(where, std::ios_base::app);
            out << what;
            out.close();
        }
    }
}

#endif //COMMONS_COMMONS_H

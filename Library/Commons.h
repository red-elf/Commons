//
// Created by milosvasic on 16.08.22.
//

#ifndef COMMONS_COMMONS_H
#define COMMONS_COMMONS_H

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

namespace Commons {

    namespace Strings {

        void tokenize(std::string const &str, char delim, std::list<std::string> &out);

        void tokenize(std::string const &str, char delim, std::vector<std::string> &out);

        std::string trim(const std::string &str, const std::string &whitespace = " \t");

        std::string reduce(

                const std::string &str,
                const std::string &fill = " ",
                const std::string &whitespace = " \t"
        );

        bool hasEnding(const std::string &fullString, const std::string &ending);

        bool hasBeginning(const std::string &fullString, const std::string &beginning);

        std::string &eraseBetween(std::string &subject, const std::string &from, const std::string &to);

        std::string eraseAllBetween(std::string &subject, const std::string &opening, const std::string &closure);

        std::string removeAfter(std::string str, const std::string &from);

        std::string removeComments(std::string &str);

        std::string capitalize(std::string &what);

        std::string deCapitalize(std::string &what);

        std::string camelcase(std::string &what);
    }

    namespace IO {

        std::string readFile(std::string_view path);

        void writeFile(std::string &what, const std::string &where);

        void appendToFile(std::string &what, const std::string &where);
    }
}

#endif //COMMONS_COMMONS_H

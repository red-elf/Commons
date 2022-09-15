//
// Created by milosvasic on 28.08.22.
//

#include "Commons.h"

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void Commons::Strings::tokenize(const std::string &str, char delim, std::list<std::string> &out) {

    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {

        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

void Commons::Strings::tokenize(const std::string &str, char delim, std::vector<std::string> &out) {

    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {

        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

std::string Commons::Strings::trim(const std::string &str, const std::string &whitespace) {

    const auto strBegin = str.find_first_not_of(whitespace);

    if (strBegin == std::string::npos) {

        return ""; // no content
    }

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string Commons::Strings::reduce(const std::string &str, const std::string &fill, const std::string &whitespace) {

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

bool Commons::Strings::hasEnding(const std::string &fullString, const std::string &ending) {

    if (fullString.length() >= ending.length()) {

        auto compare = fullString
                .compare(fullString.length() - ending.length(), ending.length(), ending);

        return 0 == compare;
    }
    return false;
}

bool Commons::Strings::hasBeginning(const std::string &fullString, const std::string &beginning) {

    if (fullString.length() >= beginning.length()) {

        auto compare = fullString
                .compare(0, beginning.length(), beginning);

        return 0 == compare;
    }
    return false;
}

std::string &Commons::Strings::eraseBetween(std::string &subject, const std::string &from, const std::string &to) {

    size_t begin = subject.find(from);
    size_t end = subject.find_last_of(to);

    if (std::string::npos != begin && std::string::npos != end && begin <= end) {

        return subject.erase(begin, end - begin + 1);
    }
    return subject;
}

std::string Commons::Strings::eraseAllBetween(

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

std::string Commons::Strings::removeAfter(std::string str, const std::string &from) {

    std::string::size_type begin, end;

    while ((begin = str.find(from)) != std::string::npos) {

        end = str.find_last_of('\n');

        if (end != std::string::npos && end > begin) {

            str.erase(begin, end - begin + 1);

        } else break;
    }
    return str;
}

std::string Commons::Strings::removeComments(std::string &str) {

    return eraseAllBetween(str, "/*", "*/");
}

std::string Commons::Strings::capitalize(std::string &what) {

    what[0] = toupper(what[0]);
    return what;
}

std::string Commons::Strings::deCapitalize(std::string &what) {

    what[0] = tolower(what[0]);
    return what;
}

std::string Commons::Strings::camelcase(std::string &what) {

    auto n = what.length();

    int res_ind = 0;

    for (int i = 0; i < n; i++) {

        // check for spaces in the sentence
        if (what[i] == ' ') {

            what[i + 1] = toupper(what[i + 1]);
            continue;

        } else {

            what[res_ind++] = what[i];
        }
    }

    return what.substr(0, res_ind);
}

char Commons::Strings::fileSeparator() {

#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

std::string Commons::Strings::lineBreak() {

    return "\n";
}

std::string Commons::IO::readFile(std::string_view path) {

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

std::ifstream::pos_type Commons::IO::fileSize(const std::string &filename) {

    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void Commons::IO::writeFile(std::string &what, const std::string &where) {

    std::ofstream out(where);
    out << what;
    out.close();
}

bool Commons::IO::writeFileWithResult(std::string &what, const std::string &where) {

    auto expected = what.length();
    writeFile(what, where);
    auto written = fileSize(where);

    return expected == written;
}

void Commons::IO::appendToFile(std::string &what, const std::string &where) {

    std::ofstream out;
    out.open(where, std::ios_base::app);
    out << what;
    out.close();
}

bool Commons::IO::createDirectories(const std::string &path) {

    if (!fs::is_directory(path) || !fs::exists(path)) {

        try {

            if (!fs::create_directories(path)) {

                return false;
            }

        } catch (std::filesystem::filesystem_error &error) {

            return false;
        }
    }
    return true;
}
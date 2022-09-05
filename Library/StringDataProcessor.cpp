//
// Created by milosvasic on 28.08.22.
//

#include <algorithm>
#include "StringDataProcessor.h"

std::string StringDataProcessor::process(std::string &input) {

    for (IProcessor<std::string, std::string> *processor: recipes) {

        input = processor->process(input);
    }
    return input;
}

bool StringDataProcessor::doRegister(IProcessor<std::string, std::string> &what) {

    size_t size = recipes.size();
    recipes.push_back(&what);
    return size != recipes.size();
}

bool StringDataProcessor::doUnregister(IProcessor<std::string, std::string> &what) {

    size_t size = recipes.size();
    recipes.erase(std::remove(recipes.begin(), recipes.end(), &what), recipes.end());
    return size != recipes.size();
}
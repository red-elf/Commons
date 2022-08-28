//
// Created by milosvasic on 28.08.22.
//

#ifndef _STRINGDATAPROCESSOR_H
#define _STRINGDATAPROCESSOR_H

#include "string"
#include "vector"
#include "IProcessor.h"
#include "IRegistration.h"

class StringDataProcessor :
        public IProcessor<std::string, std::string>,
        public IRegistration<IProcessor<std::string, const std::string> *> {

public:

    [[nodiscard]] std::string process(std::string &input) override;

    [[nodiscard]] bool doRegister(IProcessor<std::string, const std::string> *what) override;
    [[nodiscard]] bool doUnregister(IProcessor<std::string , const std::string> *&what) override;

private:

    std::vector<IProcessor<std::string, const std::string> *> recipes;
};


#endif //_STRINGDATAPROCESSOR_H

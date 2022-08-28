//
// Created by milosvasic on 28.08.22.
//

#ifndef COMMONS_1_0_0_IREGISTRATION_H
#define COMMONS_1_0_0_IREGISTRATION_H

template<class T>
class IRegistration {

public:

    virtual const bool doRegister(T &what) = 0;
    virtual const bool doUnregister(T &what) = 0;
};


#endif //COMMONS_1_0_0_IREGISTRATION_H

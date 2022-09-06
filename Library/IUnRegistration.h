//
// Created by milosvasic on 28.08.22.
//

#ifndef COMMONS_1_0_0_IUNREGISTRATION_H
#define COMMONS_1_0_0_IUNREGISTRATION_H

template<class T>
class IUnRegistration {

public:

    virtual ~IUnRegistration() = default;

    virtual bool doUnregister(T &what) = 0;
};


#endif //COMMONS_1_0_0_IUNREGISTRATION_H

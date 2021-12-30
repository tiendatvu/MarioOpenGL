#ifndef I_OBSERVABLE_SUBJECT_H
#define I_OBSERVABLE_SUBJECT_H

#include "ICharacter.h"


class IObservableSubject
{
private:


protected:
    void Notify(const ICharacter *character);

public:
    void AddObserver();
    void RemoveObserver();

};

#endif // !I_OBSERVABLE_SUBJECT_H

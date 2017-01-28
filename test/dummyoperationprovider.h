#ifndef DUMMYOPERATIONPROVIDER_H
#define DUMMYOPERATIONPROVIDER_H

#include <basicoperationprovider.h>

class DummyOperationProvider : public BasicOperationProvider
{
public:
    DummyOperationProvider();

    BasicOperationOutput basic_operation(int p, int r, int q, int t, int s) override;
    int number_of_sites() override;
};
#endif // DUMMYOPERATIONPROVIDER_H

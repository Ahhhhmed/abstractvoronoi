#ifndef BASICOPERATIONPROVIDER_H
#define BASICOPERATIONPROVIDER_H

enum BasicOperationOutput{
    intersection_empty,  // 1
    whole_edge,          // 2a
    segment_prq,         // 2b
    segment_qtp,         // 2c
    segment_interior,    // 2d
    two_components       // 3
};

class BasicOperationProvider
{
public:
    virtual BasicOperationOutput basic_operation(int p,int r,int q,int t,int s) = 0;
    virtual int number_of_sites() = 0;
};

#endif // BASICOPERATIONPROVIDER_H

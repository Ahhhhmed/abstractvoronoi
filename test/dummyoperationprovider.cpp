#include "DummyOperationProvider.h"
#include <tuple>

DummyOperationProvider::DummyOperationProvider()
{

}

BasicOperationOutput DummyOperationProvider::basic_operation(int p, int r, int q, int, int)
{
    std::tuple<int,int,int> v = std::make_tuple(p,r,q);
    if(v == std::make_tuple(0,1,2) || v == std::make_tuple(1,2,0) || v == std::make_tuple(2,0,1)){
        return segment_qtp;
    }
    return segment_prq;
}

int DummyOperationProvider::number_of_sites()
{
    return 3;
}

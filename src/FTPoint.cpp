#include "FTPoint.h"


bool operator == ( const FTPoint &a, const FTPoint &b) 
{
    return((a.elements[0] == b.elements[0]) && (a.elements[1] == b.elements[1]) && (a.elements[2] == b.elements[2]));
}

bool operator != ( const FTPoint &a, const FTPoint &b) 
{
    return((a.elements[0] != b.elements[0]) || (a.elements[1] != b.elements[1]) || (a.elements[2] != b.elements[2]));
}

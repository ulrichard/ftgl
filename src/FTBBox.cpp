#include "FTBBox.h"


FTBBox operator + ( const FTBBox &a, const FTBBox &b) 
{
    FTBBox compositeBox;
    
    compositeBox.lowerX = a.lowerX < b.lowerX? a.lowerX: b.lowerX; 
    compositeBox.lowerY = a.lowerY < b.lowerY? a.lowerY: b.lowerY;
    compositeBox.lowerZ = a.lowerZ < b.lowerZ? a.lowerZ: b.lowerZ; 
    compositeBox.upperX = a.upperX < b.upperX? a.upperX: b.upperX; 
    compositeBox.upperY = a.upperY < b.upperY? a.upperY: b.upperY; 
    compositeBox.upperZ = a.upperZ < b.upperZ? a.upperZ: b.upperZ; 
    
    
    return compositeBox;
}


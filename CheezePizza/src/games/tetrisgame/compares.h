#ifndef Compares_H_
#define Compares_H_




struct IntCompare
{
    bool operator()(int i1, int i2) const
    {    
        return (i1 < i2);  
    };
}; 





#endif
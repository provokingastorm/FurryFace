#ifndef TetrisBlockRotator_H_
#define TetrisBlockRotator_H_


class TetrisBlockRotator
{
public:

    TetrisBlockRotator();
    virtual ~TetrisBlockRotator();

    void RotateProxy( class TetrisBlockProxy & ProxyToRotate ) = 0;

};


#endif
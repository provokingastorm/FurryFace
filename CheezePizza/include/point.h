#ifndef Point_H_
#define Point_H_


struct Point
{
    int X;
    int Y;

    Point( int InX = 0, int InY = 0 ) 
        :   X(InX)
        ,   Y(InY) 
    {
    }

    Point( const Point & InPoint )
    {
        X = InPoint.X;
        Y = InPoint.Y;
    }

    Point& operator=( const Point & InPoint )
    {
        X = InPoint.X;
        Y = InPoint.Y;
        return *this;
    }

    inline bool operator== ( const Point & InPoint ) const
    {
        return ( X == InPoint.X && Y == InPoint.Y );
    }

    inline bool operator!= ( const Point & InPoint ) const
    {
        return ( X != InPoint.X && Y != InPoint.Y );
    }

    inline static Point& Zero()
    {
        static Point ZeroPoint(0, 0);
        return ZeroPoint;
    }

    inline Point operator+ ( const Point & InPoint ) const
    {
          Point NewPoint;
          NewPoint.X = X + InPoint.X;
          NewPoint.Y = Y + InPoint.Y;
          return NewPoint;
    }

    inline Point operator- ( const Point & InPoint ) const
    {
          Point NewPoint;
          NewPoint.X = X - InPoint.X;
          NewPoint.Y = Y - InPoint.Y;
          return NewPoint;
    }

    inline Point operator* ( const Point & InPoint ) const
    {
          Point NewPoint;
          NewPoint.X = X * InPoint.X;
          NewPoint.Y = Y * InPoint.Y;
          return NewPoint;
    }

    inline Point operator/ ( const Point & InPoint ) const
    {
          Point NewPoint;
          NewPoint.X = X / InPoint.X;
          NewPoint.Y = Y / InPoint.Y;
          return NewPoint;
    }

	inline Point& operator+= ( Point & InPoint )
    {
        X += InPoint.X;
        Y += InPoint.Y;
        return *this;
    }

	inline Point& operator-= ( Point & InPoint )
    {
        X -= InPoint.X;
        Y -= InPoint.Y;
        return *this;
    }

	inline Point& operator*= ( Point & InPoint )
    {
        X *= InPoint.X;
        Y *= InPoint.Y;
        return *this;
    }

	inline Point& operator/= ( Point & InPoint )
    {
        X /= InPoint.X;
        Y /= InPoint.Y;
        return *this;
    }

	inline Point& operator+= ( int Scalar )
    {
        X += Scalar;
        Y += Scalar;
        return *this;
    }

	inline Point& operator-= ( int Scalar )
    {
        X -= Scalar;
        Y -= Scalar;
        return *this;
    } 

	inline Point& operator*= ( int Scalar )
    {
        X *= Scalar;
        Y *= Scalar;
        return *this;
    } 

	inline Point& operator/= ( int Scalar )
    {
        X /= Scalar;
        Y /= Scalar;
        return *this;
    } 

    inline friend Point operator- ( const Point & InPoint )
    {
        return Point(-InPoint.X, -InPoint.Y);
    }

};

#endif
#ifndef _DEBUGUTILITIES_H_
#define _DEBUGUTILITIES_H_

#ifndef _CASSERT_H_
#define _CASSERT_H_
#include <cassert>
#endif

#include <Windows.h>


bool AssertDetailed( bool, char *, int, char * );
void CheckIgnoreAssert( bool, char *, int, char * );

/**
 * When the Debug configuration is running, define the assert. This
 * custom assert makes the assert function less awkward. 
 *
 * @remarks Credit goes to Steve Rabin's Article "Squeezing More 
 * Out of Assert" (Page 109 - 114) in Game Programming Gems.
 *
 * @param Expression A boolean expression to be evaluated.
 *
 * @param Description The output text to display if the assert fails.
 *
 * @author Peter Bennett (curlyhairedgreatness@gmail.com)
 */
#if defined(_DEBUG)

#define CPAssert( Expression, Description ) \
{ \
    static bool bIgnoreAsserts; \
    if( !bIgnoreAsserts ) \
    { \
        if( AssertDetailed( Expression, Description, __LINE__, __FILE__ ) ) \
            _asm { int 3 } \
    }\
}

// When the Debug configuration is not running, turn off asserts
#else
#define CPAssert( Expression, Description )

#endif


#if defined(_DEBUG)
#define CPBasicAssert( Expression, Description) \
    if( !Expression) _asm { int 3 } 

// When the Debug configuration is not running, turn off asserts
#else
#define CPBasicAssert( Expression, Description )

#endif



#endif // END #ifndef _DEBUGUTILITIES_H_
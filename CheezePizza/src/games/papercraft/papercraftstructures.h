#ifndef PapercraftStructures_H_
#define PapercraftStructures_H_


// ----------------------------------------------------------------------------
// PapercraftStructures - Enums
// ----------------------------------------------------------------------------


// IMPORTANT: When adding a new player color enum, remember to handle your color in GetPlayerColorFromEnum()
enum EPlayerColor
{
	PC_White	= 0,
	PC_Red		= 1,

	// NOTE: Don't add enums after PC_Max
	PC_Max
};


// ----------------------------------------------------------------------------
// PapercraftStructures - Global Functions
// ----------------------------------------------------------------------------

DWORD GetPlayerColorFromEnum(EPlayerColor ColorEnum);
DWORD GetPlayerColorFromInt(int ColorInt);

#endif

// EOF

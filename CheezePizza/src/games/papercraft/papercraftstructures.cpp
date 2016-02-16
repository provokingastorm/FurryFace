#include "cheezepizza.h"
#include "papercraftstructures.h"


// ----------------------------------------------------------------------------
// PapercraftStructures - Global Functions
// ----------------------------------------------------------------------------


DWORD GetPlayerColorFromEnum(EPlayerColor ColorEnum)
{
	DWORD Color = 0;

	switch(ColorEnum)
	{
	case PC_Red:
		Color = ARGB(255, 255, 0, 0);
		break;

	case PC_White:
	default:
		Color = ARGB(255, 255, 255, 255);
		break;
	}

	return Color;
}


DWORD GetPlayerColorFromInt(int ColorInt)
{
	EPlayerColor ColorEnum = PC_White;

	switch(ColorInt)
	{
	case 0:
		ColorEnum = PC_White;
		break;

	case 1:
		ColorEnum = PC_Red;
		break;

	default:
		ColorEnum = PC_White;
		break;
	}

	return GetPlayerColorFromEnum(ColorEnum);
}

// EOF

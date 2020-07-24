#include "GBUtil.h"

bool TestBit(WORD byte, BYTE index)
{
	return ((byte >> index) & 1) == 1;
}

#include "GBUtil.h"

bool TestBit(WORD byte, BYTE index)
{
	return ((byte >> index) & 1) == 1;
}

BYTE BitSet(BYTE byte, int index)
{
	return byte | (1 << index);
}

BYTE BitToggle(BYTE byte, int index)
{
	return byte ^ (1 << index);
}

BYTE BitReset(BYTE byte, int index)
{
	return byte & ~(1 << index);
}

int BitGetVal(BYTE byte, int index)
{
	return ((byte >> index) & 1);
}

BYTE SwapNibble(BYTE byte)
{
	return ((byte & 0xF) << 4) | ((byte & 0xF0) >> 4);
}

BYTE RotateByte(BYTE byte, int index)
{
	return (byte << index) | (byte >> (8 - index));
}

WORD RotateWord(WORD word, int index)
{
	return (word << index) | (word >> (16 - index));
}

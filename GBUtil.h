#ifndef GBUTIL_H
#define GBUTIL_H

#include "GBDef.h"

bool TestBit(WORD byte, BYTE index);
BYTE BitSet(BYTE byte, int index);
BYTE BitToggle(BYTE byte, int index);
BYTE BitReset(BYTE byte, int index);
int BitGetVal(BYTE byte, int index);
BYTE SwapNibble(BYTE byte);
BYTE RotateByte(BYTE byte, int index);
WORD RotateWord(WORD word, int index);

#endif
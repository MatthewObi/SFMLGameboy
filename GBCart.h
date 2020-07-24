#ifndef GBCART_H
#define GBCART_H

#include "GBDef.h"

struct GBCart
{
	BYTE m_CartridgeMemory[0x200000];

	GBCart();
	void load(const char* path);
};

#endif //GBCART_H
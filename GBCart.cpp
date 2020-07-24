#include "GBCart.h"
#include <memory>

GBCart::GBCart()
{
	std::memset(&m_CartridgeMemory, 0, sizeof(m_CartridgeMemory));
}

void GBCart::load(const char* path)
{
	FILE* f;
	f = fopen(path, "rb");
	fread(m_CartridgeMemory, 1, sizeof m_CartridgeMemory, f);
	fclose(f);
}

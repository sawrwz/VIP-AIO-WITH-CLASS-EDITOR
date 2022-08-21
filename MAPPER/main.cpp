#include "framework.h"
#include "main.h"

INT MainInjector(const wchar_t* ProcessName, unsigned char DecryptedDll[])
{
	//unsigned char decryptedDll[] = rawData;
	if (!Comm::Setup()) {
		return 1;
	}

	Comm::Process process(ProcessName);
	if (!process.Valid()) {

		return 1;
	}

	auto entry = Map::ExtendMap(process, DecryptedDll);
	if (!entry) {
		return 1;
	}
	if (!Hijack::HijackViaHook(process, entry, L"user32.dll", "PeekMessageW")) {
		return 1;
	}

	return 0;
}
#include "stdafx.h"
#include "xono2l.h"
#include "ulterius_controller.h"
#include <thread>

BOOL APIENTRY  DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

_declspec (dllexport)
bool start_acquisition(const char *device_ident) noexcept
{
	try
	{
		if (is_acquiring())
			return false;

#ifdef USE_ULTERIUS
        return UlteriusController::start_acquisition(device_ident);
#else
        return false;
#endif
	}
	catch (...)
	{
		/* We use this evil design only with the intention of not causing
		 * the LabVIEW client to crash. This try-catch block should better
		 * be replaced by an appropriate exception handling mechanism
		 * interplayed between C++ and LabVIEW.
		 */
		return false;
	}
}

_declspec (dllexport)
bool stop_acquisition() noexcept
{
	try
	{
		if (!is_acquiring())
			return true;

#ifdef USE_ULTERIUS
        return UlteriusController::stop_acquisition();
#else
        return false;
#endif
	}
	catch (...)
	{
		/* We use this evil design only with the intention of not causing
		 * the LabVIEW client to crash. This try-catch block should better
		 * be replaced by an appropriate exception handling mechanism
		 * interplayed between C++ and LabVIEW.
		 */
		return false;
	}
}

_declspec (dllexport)
bool is_acquiring() noexcept
{
	try
	{
#ifdef USE_ULTERIUS
        return UlteriusController::is_acquiring();
#else
        return false;
#endif
	}
	catch (...)
	{
		/* We use this evil design only with the intention of not causing
		 * the LabVIEW client to crash. This try-catch block should better
		 * be replaced by an appropriate exception handling mechanism
		 * interplayed between C++ and LabVIEW.
		 */
		return false;
	}
}

_declspec (dllexport)
bool get_data(uint8_t *data, uint32_t *width, uint32_t *height,
              uint32_t *depth, uint32_t *freq) noexcept
{
	try
	{
		if (!is_acquiring())
			return false;

#ifdef USE_ULTERIUS
        return UlteriusController::get_data(data, width, height, depth, freq);
#else
        return false;
#endif
	}
	catch (...)
	{
		/* We use this evil design only with the intention of not causing
		 * the LabVIEW client to crash. This try-catch block should better
		 * be replaced by an appropriate exception handling mechanism
		 * interplayed between C++ and LabVIEW.
		 */
		return false;
	}
}

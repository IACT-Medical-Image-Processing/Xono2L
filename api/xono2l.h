#pragma once

#include <cstdint>

BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID);

//!
//! \brief Attempt to connect to the device specified, and
//! subsequently start a live acquisition
//! \param device_url either the IP address of an Ultrasonix
//! machine or the port of an Epiphan frame-grabber, with "u:"
//! prepended to the former, and "e:" prepended to the latter
//!
//! \return true if no machine is connected, and a connection
//! has been successfully established, and streaming started,
//! false otherwise
//!
_declspec (dllexport)
bool start_acquisition(const char *device_url) noexcept;

//!
//! \brief Attempt to stop the current live acquisition
//!
//! \return true if a live acquisition was on and was
//! successfully stopped, or if no live acquisition was on,
//! false otherwise
//!
_declspec (dllexport)
bool stop_acquisition() noexcept;

//!
//! \brief Check whether a live acquisition is on
//!
//! \return true if a live acquisition is on, false
//! otherwise
//!
_declspec (dllexport)
bool is_acquiring() noexcept;

//!
//! \brief Copy current data on to passed memory, along
//! with the video frame dimensions, ultrasound image depth
//! and used frequency
//!
_declspec (dllexport)
bool get_data(
    uint8_t *data, uint32_t *width, uint32_t *height,
    uint32_t *depth, uint32_t *freq
) noexcept;

#ifdef USE_ULTERIUS

//!
//! \brief Set focus depth to specified value (specified in
//! millimetres)
//!
_declspec (dllexport)
bool set_focus_depth(float focus_depth) noexcept;

//!
//! \brief Get current focus depth (in millimetres)
//!
_declspec (dllexport)
float get_focus_depth() noexcept;

#endif // USE_ULTERIUS

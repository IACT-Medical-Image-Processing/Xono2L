#include "epiphan_controller.h"

#include <iostream>
#include <string>

#ifdef USE_EPIPHAN


EpiphanController::EpiphanController()
	: frame_grabber(NULL)
	, flags(0)
	, buffer(NULL)
{
	// nop
}


EpiphanController::~EpiphanController()
{
	if (is_acquiring())
		stop_acquisition();
}


EpiphanController& EpiphanController::get_instance()
{
	static EpiphanController _controller;
	return _controller;
}


V2U_INT32 EpiphanController::determine_colour(const char *device_ident)
{
    V2U_INT32 colour_space = V2U_GRABFRAME_FORMAT_RGB24;
    std::string device_ident_(device_ident);
    std::string colour_spec = device_ident_.substr(device_ident_.size()-2);
    if (colour_spec.compare("-c"))
        colour_space = V2U_GRABFRAME_FORMAT_RGB24;
    else if (colour_spec.compare("-i"))
        colour_space = V2U_GRABFRAME_FORMAT_I420;
    return colour_space;
}


bool EpiphanController::start_acquisition(const char *device_ident)
{
	if (is_acquiring())
		return true;

	FrmGrab_Init();

	frame_grabber = FrmGrab_Open(device_ident);

	if (frame_grabber == NULL)
	{
		std::cerr << "Could not open " << device_ident << std::endl;
		return false;
	}

	flags |= determine_colour(device_ident);

	// TODO: set ROI more intelligently
	roi.x = 320;
	roi.y = 160;
	roi.width = 1280;
	roi.height = 960;

	return true;
}


bool EpiphanController::stop_acquisition()
{
	if (!is_acquiring())
		return true;

	FrmGrab_Close(frame_grabber);
	frame_grabber = NULL;

	FrmGrab_Deinit();

    return true;
}


bool EpiphanController::is_acquiring()
{
	return !(frame_grabber == NULL);
}


bool EpiphanController::get_data(uint8_t *data, uint32_t *width, uint32_t *height)
{
	if (!is_acquiring())
		return false;

	buffer = FrmGrab_Frame(frame_grabber, flags, &roi);

	if (buffer == NULL)
		return false;

    size_t relevant_data_length = 0;
    if (flags & V2U_GRABFRAME_FORMAT_I420)
        relevant_data_length = buffer->crop.width * buffer->crop.height;
    else if (flags & V2U_GRABFRAME_FORMAT_RGB24)
        relevant_data_length = buffer->imagelen;
	memcpy(data, buffer->pixbuf, relevant_data_length);
	*width = buffer->crop.width;
	*height = buffer->crop.height;

	FrmGrab_Release(frame_grabber, buffer);

	buffer = NULL;

	return true;
}


#endif // USE_EPIPHAN

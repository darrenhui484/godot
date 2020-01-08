/*************************************************************************/
/*  audio_driver_wasapi.cpp                                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2019 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2019 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifdef WASAPI_ENABLED

#include "audio_driver_wasapi.h"

#ifndef PKEY_Device_FriendlyName

#undef DEFINE_PROPERTYKEY
/* clang-format off */
#define DEFINE_PROPERTYKEY(id, a, b, c, d, e, f, g, h, i, j, k, l) \
	const PROPERTYKEY id = { { a, b, c, { d, e, f, g, h, i, j, k, } }, l };
/* clang-format on */

#endif

#define SAFE_RELEASE(memory) \
	if ((memory) != NULL) {  \
		(memory)->Release(); \
		(memory) = NULL;     \
	}

#define REFTIMES_PER_SEC 10000000
#define REFTIMES_PER_MILLISEC 10000

#define CAPTURE_BUFFER_CHANNELS 2

static bool default_render_device_changed = false;
static bool default_capture_device_changed = false;

Error AudioDriverWASAPI::init() {
	return OK;
}

int AudioDriverWASAPI::get_mix_rate() const {
	return 0;
}

AudioDriver::SpeakerMode AudioDriverWASAPI::get_speaker_mode() const {
	return AudioDriver::SpeakerMode::SPEAKER_MODE_STEREO;
}

Array AudioDriverWASAPI::get_device_list() {
	return Array();
}

String AudioDriverWASAPI::get_device() {
	return String();
}

void AudioDriverWASAPI::set_device(String device) {
}

void AudioDriverWASAPI::start() {
}

void AudioDriverWASAPI::lock() {
}

void AudioDriverWASAPI::unlock() {
}

void AudioDriverWASAPI::finish() {
}

Error AudioDriverWASAPI::capture_start() {
	return OK;
}

Error AudioDriverWASAPI::capture_stop() {
	return OK;
}

void AudioDriverWASAPI::capture_set_device(const String &p_name) {
}

Array AudioDriverWASAPI::capture_get_device_list() {
	return Array();
}

String AudioDriverWASAPI::capture_get_device() {
	return String();
}

AudioDriverWASAPI::AudioDriverWASAPI() {
}

#endif

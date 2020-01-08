/*************************************************************************/
/*  audio_driver_alsa.cpp                                                */
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

#include "audio_driver_alsa.h"

#ifdef ALSA_ENABLED

#include <errno.h>

Error AudioDriverALSA::init() {
	return OK;
}

void AudioDriverALSA::start() {
}

int AudioDriverALSA::get_mix_rate() const {
	return 0;
}

AudioDriver::SpeakerMode AudioDriverALSA::get_speaker_mode() const {
	return AudioDriver::SpeakerMode::SPEAKER_MODE_STEREO;
}

Array AudioDriverALSA::get_device_list() {
	return Array();
}

String AudioDriverALSA::get_device() {
	return String();
}

void AudioDriverALSA::set_device(String device) {
}

void AudioDriverALSA::lock() {
}

void AudioDriverALSA::unlock() {
}

void AudioDriverALSA::finish() {
}

AudioDriverALSA::AudioDriverALSA() {}

AudioDriverALSA::~AudioDriverALSA() {}

#endif

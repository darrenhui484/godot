/*************************************************************************/
/*  audio_driver_pulseaudio.cpp                                          */
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

#include "audio_driver_pulseaudio.h"

#ifdef PULSEAUDIO_ENABLED

Error AudioDriverPulseAudio::init() {
	return OK;
}

float AudioDriverPulseAudio::get_latency() {
	return 0.f;
}

void AudioDriverPulseAudio::start() {
}

int AudioDriverPulseAudio::get_mix_rate() const {
	return 0;
}

AudioDriver::SpeakerMode AudioDriverPulseAudio::get_speaker_mode() const {
	return AudioDriver::SpeakerMode::SPEAKER_MODE_STEREO;
}

Array AudioDriverPulseAudio::get_device_list() {
	return Array();
}

String AudioDriverPulseAudio::get_device() {
	return String();
}

void AudioDriverPulseAudio::set_device(String device) {
}

void AudioDriverPulseAudio::lock() {
}

void AudioDriverPulseAudio::unlock() {
}

void AudioDriverPulseAudio::finish() {
}

Error AudioDriverPulseAudio::capture_start() {
	return OK;
}

Error AudioDriverPulseAudio::capture_stop() {
	return OK;
}

void AudioDriverPulseAudio::capture_set_device(const String &p_name) {
}

Array AudioDriverPulseAudio::capture_get_device_list() {
	return Array();
}

String AudioDriverPulseAudio::capture_get_device() {
	return String();
}

AudioDriverPulseAudio::AudioDriverPulseAudio() {}

AudioDriverPulseAudio::~AudioDriverPulseAudio() {}

#endif

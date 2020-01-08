/*************************************************************************/
/*  audio_driver_coreaudio.cpp                                           */
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

#ifdef COREAUDIO_ENABLED

#include "audio_driver_coreaudio.h"

#define kOutputBus 0
#define kInputBus 1

#ifdef OSX_ENABLED
OSStatus AudioDriverCoreAudio::input_device_address_cb(AudioObjectID inObjectID,
	return noErr;
}

OSStatus AudioDriverCoreAudio::output_device_address_cb(AudioObjectID inObjectID,
	return noErr;
}
#endif

Error AudioDriverCoreAudio::init() {
	return OK;
}

void AudioDriverCoreAudio::start(){};

void AudioDriverCoreAudio::stop() {
}

int AudioDriverCoreAudio::get_mix_rate() const {
	return 0;
};

AudioDriver::SpeakerMode AudioDriverCoreAudio::get_speaker_mode() const {
	return AudioDriver::SpeakerMode::SPEAKER_MODE_STEREO;
};

void AudioDriverCoreAudio::lock(){};

void AudioDriverCoreAudio::unlock(){};

bool AudioDriverCoreAudio::try_lock() {
	return false;
}

void AudioDriverCoreAudio::finish() {
}

Error AudioDriverCoreAudio::capture_start() {
	return OK;
}

Error AudioDriverCoreAudio::capture_stop() {
	return OK;
}

#ifdef OSX_ENABLED

Array AudioDriverCoreAudio::get_device_list() {
	return Array();
}

String AudioDriverCoreAudio::get_device() {
	return String();
}

void AudioDriverCoreAudio::set_device(String device) {
}

void AudioDriverCoreAudio::capture_set_device(const String &p_name) {
}

Array AudioDriverCoreAudio::capture_get_device_list() {
	return Array();
}

String AudioDriverCoreAudio::capture_get_device() {
	return String();
}

#endif

AudioDriverCoreAudio::AudioDriverCoreAudio() {}

AudioDriverCoreAudio::~AudioDriverCoreAudio(){};

#endif

/*************************************************************************/
/*  rasterizer_gles2.cpp                                                 */
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

#include "rasterizer_gles2.h"

RasterizerStorage *RasterizerGLES2::get_storage() {
	return NULL;
}

RasterizerCanvas *RasterizerGLES2::get_canvas() {
	return NULL;
}

RasterizerScene *RasterizerGLES2::get_scene() {
	return NULL;
}

Error RasterizerGLES2::is_viable() {
	return OK;
}

void RasterizerGLES2::initialize() {
}

void RasterizerGLES2::begin_frame(double frame_step) {
}

void RasterizerGLES2::set_current_render_target(RID p_render_target) {
}

void RasterizerGLES2::restore_render_target() {
}

void RasterizerGLES2::clear_render_target(const Color &p_color) {
}

void RasterizerGLES2::set_boot_image(const Ref<Image> &p_image, const Color &p_color, bool p_scale) {
}

void RasterizerGLES2::blit_render_target_to_screen(RID p_render_target, const Rect2 &p_screen_rect, int p_screen) {
}

void RasterizerGLES2::output_lens_distorted_to_screen(RID p_render_target, const Rect2 &p_screen_rect, float p_k1, float p_k2, const Vector2 &p_eye_center, float p_oversample) {
}

void RasterizerGLES2::end_frame(bool p_swap_buffers) {
}

void RasterizerGLES2::finalize() {
}

void RasterizerGLES2::make_current() {
}

void RasterizerGLES2::register_config() {
}

RasterizerGLES2::RasterizerGLES2() {
}

RasterizerGLES2::~RasterizerGLES2() {
}

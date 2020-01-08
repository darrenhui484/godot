/*************************************************************************/
/*  rasterizer_storage_gles2.cpp                                         */
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

#include "rasterizer_storage_gles2.h"

GLuint RasterizerStorageGLES2::system_fbo = 0;

/* TEXTURE API */

void RasterizerStorageGLES2::bind_quad_array() const {
}

Ref<Image> RasterizerStorageGLES2::_get_gl_image_and_format(const Ref<Image> &p_image, Image::Format p_format, uint32_t p_flags, Image::Format &r_real_format, GLenum &r_gl_format, GLenum &r_gl_internal_format, GLenum &r_gl_type, bool &r_compressed, bool p_will_need_resize) const {
	return RES();
}

RID RasterizerStorageGLES2::texture_create() {
	return RID();
}

void RasterizerStorageGLES2::texture_allocate(RID p_texture, int p_width, int p_height, int p_depth_3d, Image::Format p_format, VisualServer::TextureType p_type, uint32_t p_flags) {
}

void RasterizerStorageGLES2::texture_set_data(RID p_texture, const Ref<Image> &p_image, int p_layer) {
}

void RasterizerStorageGLES2::texture_set_data_partial(RID p_texture, const Ref<Image> &p_image, int src_x, int src_y, int src_w, int src_h, int dst_x, int dst_y, int p_dst_mip, int p_layer) {
}

Ref<Image> RasterizerStorageGLES2::texture_get_data(RID p_texture, int p_layer) const {
	return NULL;
}

void RasterizerStorageGLES2::texture_set_flags(RID p_texture, uint32_t p_flags) {
}

uint32_t RasterizerStorageGLES2::texture_get_flags(RID p_texture) const {
	return 0;
}

Image::Format RasterizerStorageGLES2::texture_get_format(RID p_texture) const {
	return Image::Format::FORMAT_BPTC_RGBA;
}

VisualServer::TextureType RasterizerStorageGLES2::texture_get_type(RID p_texture) const {
	return VisualServer::TextureType::TEXTURE_TYPE_2D;
}

uint32_t RasterizerStorageGLES2::texture_get_texid(RID p_texture) const {
	return 0;
}

uint32_t RasterizerStorageGLES2::texture_get_width(RID p_texture) const {
	return 0;
}

uint32_t RasterizerStorageGLES2::texture_get_height(RID p_texture) const {
	return 0;
}

uint32_t RasterizerStorageGLES2::texture_get_depth(RID p_texture) const {
	return 0;
}

void RasterizerStorageGLES2::texture_set_size_override(RID p_texture, int p_width, int p_height, int p_depth) {
}

void RasterizerStorageGLES2::texture_set_path(RID p_texture, const String &p_path) {
}

String RasterizerStorageGLES2::texture_get_path(RID p_texture) const {
	return String();
}

void RasterizerStorageGLES2::texture_debug_usage(List<VS::TextureInfo> *r_info) {
	List<RID> textures;
	texture_owner.get_owned_list(&textures);

	for (List<RID>::Element *E = textures.front(); E; E = E->next()) {

		Texture *t = texture_owner.getornull(E->get());
		if (!t)
			continue;
		VS::TextureInfo tinfo;
		tinfo.path = t->path;
		tinfo.format = t->format;
		tinfo.width = t->alloc_width;
		tinfo.height = t->alloc_height;
		tinfo.depth = 0;
		tinfo.bytes = t->total_data_size;
		r_info->push_back(tinfo);
	}
}

void RasterizerStorageGLES2::texture_set_shrink_all_x2_on_set_data(bool p_enable) {
}

void RasterizerStorageGLES2::textures_keep_original(bool p_enable) {
}

Size2 RasterizerStorageGLES2::texture_size_with_proxy(RID p_texture) const {
	return Size2();
}

void RasterizerStorageGLES2::texture_set_proxy(RID p_texture, RID p_proxy) {
}

void RasterizerStorageGLES2::texture_set_force_redraw_if_visible(RID p_texture, bool p_enable) {
}

void RasterizerStorageGLES2::texture_set_detect_3d_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) {
}

void RasterizerStorageGLES2::texture_set_detect_srgb_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) {
}

void RasterizerStorageGLES2::texture_set_detect_normal_callback(RID p_texture, VisualServer::TextureDetectCallback p_callback, void *p_userdata) {
}

RID RasterizerStorageGLES2::texture_create_radiance_cubemap(RID p_source, int p_resolution) const {
	return RID();
}

RID RasterizerStorageGLES2::sky_create() {
	return RID();
}

void RasterizerStorageGLES2::sky_set_texture(RID p_sky, RID p_panorama, int p_radiance_size) {
}

/* SHADER API */

RID RasterizerStorageGLES2::shader_create() {
	return RID();
}

void RasterizerStorageGLES2::_shader_make_dirty(Shader *p_shader) {
}

void RasterizerStorageGLES2::shader_set_code(RID p_shader, const String &p_code) {
}

String RasterizerStorageGLES2::shader_get_code(RID p_shader) const {
	return String();
}

void RasterizerStorageGLES2::_update_shader(Shader *p_shader) const {
}

void RasterizerStorageGLES2::update_dirty_shaders() {
}

void RasterizerStorageGLES2::shader_get_param_list(RID p_shader, List<PropertyInfo> *p_param_list) const {
}

void RasterizerStorageGLES2::shader_set_default_texture_param(RID p_shader, const StringName &p_name, RID p_texture) {
}

RID RasterizerStorageGLES2::shader_get_default_texture_param(RID p_shader, const StringName &p_name) const {
	return RID();
}

/* COMMON MATERIAL API */

void RasterizerStorageGLES2::_material_make_dirty(Material *p_material) const {
}

RID RasterizerStorageGLES2::material_create() {
	return RID();
}

void RasterizerStorageGLES2::material_set_shader(RID p_material, RID p_shader) {
}

RID RasterizerStorageGLES2::material_get_shader(RID p_material) const {
	return RID();
}

void RasterizerStorageGLES2::material_set_param(RID p_material, const StringName &p_param, const Variant &p_value) {
}

Variant RasterizerStorageGLES2::material_get_param(RID p_material, const StringName &p_param) const {
	return Variant();
}

Variant RasterizerStorageGLES2::material_get_param_default(RID p_material, const StringName &p_param) const {
	return Variant();
}

void RasterizerStorageGLES2::material_set_line_width(RID p_material, float p_width) {
}

void RasterizerStorageGLES2::material_set_next_pass(RID p_material, RID p_next_material) {
}

bool RasterizerStorageGLES2::material_is_animated(RID p_material) {
	return false;
}

bool RasterizerStorageGLES2::material_casts_shadows(RID p_material) {
	return false;
}

void RasterizerStorageGLES2::material_add_instance_owner(RID p_material, RasterizerScene::InstanceBase *p_instance) {
}

void RasterizerStorageGLES2::material_remove_instance_owner(RID p_material, RasterizerScene::InstanceBase *p_instance) {
}

void RasterizerStorageGLES2::material_set_render_priority(RID p_material, int priority) {
}

void RasterizerStorageGLES2::_update_material(Material *p_material) {
}

void RasterizerStorageGLES2::_material_add_geometry(RID p_material, Geometry *p_geometry) {
}

void RasterizerStorageGLES2::_material_remove_geometry(RID p_material, Geometry *p_geometry) {
}

void RasterizerStorageGLES2::update_dirty_materials() {
}

/* MESH API */

RID RasterizerStorageGLES2::mesh_create() {
	return RID();
}

void RasterizerStorageGLES2::mesh_add_surface(RID p_mesh, uint32_t p_format, VS::PrimitiveType p_primitive, const PoolVector<uint8_t> &p_array, int p_vertex_count, const PoolVector<uint8_t> &p_index_array, int p_index_count, const AABB &p_aabb, const Vector<PoolVector<uint8_t> > &p_blend_shapes, const Vector<AABB> &p_bone_aabbs) {
}

void RasterizerStorageGLES2::mesh_set_blend_shape_count(RID p_mesh, int p_amount) {
}

int RasterizerStorageGLES2::mesh_get_blend_shape_count(RID p_mesh) const {
	return 0;
}

void RasterizerStorageGLES2::mesh_set_blend_shape_mode(RID p_mesh, VS::BlendShapeMode p_mode) {
}

VS::BlendShapeMode RasterizerStorageGLES2::mesh_get_blend_shape_mode(RID p_mesh) const {
	return VS::BlendShapeMode::BLEND_SHAPE_MODE_NORMALIZED;
}

void RasterizerStorageGLES2::mesh_surface_update_region(RID p_mesh, int p_surface, int p_offset, const PoolVector<uint8_t> &p_data) {
}

void RasterizerStorageGLES2::mesh_surface_set_material(RID p_mesh, int p_surface, RID p_material) {
}

RID RasterizerStorageGLES2::mesh_surface_get_material(RID p_mesh, int p_surface) const {
	return RID();
}

int RasterizerStorageGLES2::mesh_surface_get_array_len(RID p_mesh, int p_surface) const {
	return 0;
}

int RasterizerStorageGLES2::mesh_surface_get_array_index_len(RID p_mesh, int p_surface) const {
	return 0;
}

PoolVector<uint8_t> RasterizerStorageGLES2::mesh_surface_get_array(RID p_mesh, int p_surface) const {
	return PoolVector<uint8_t>();
}

PoolVector<uint8_t> RasterizerStorageGLES2::mesh_surface_get_index_array(RID p_mesh, int p_surface) const {
	return PoolVector<uint8_t>();
}

uint32_t RasterizerStorageGLES2::mesh_surface_get_format(RID p_mesh, int p_surface) const {
	return 0;
}

VS::PrimitiveType RasterizerStorageGLES2::mesh_surface_get_primitive_type(RID p_mesh, int p_surface) const {
	return VS::PrimitiveType::PRIMITIVE_LINES;
}

AABB RasterizerStorageGLES2::mesh_surface_get_aabb(RID p_mesh, int p_surface) const {
	return AABB();
}

Vector<PoolVector<uint8_t> > RasterizerStorageGLES2::mesh_surface_get_blend_shapes(RID p_mesh, int p_surface) const {
	return Vector<PoolVector<uint8_t> >();
}
Vector<AABB> RasterizerStorageGLES2::mesh_surface_get_skeleton_aabb(RID p_mesh, int p_surface) const {
	return Vector<AABB>();
}

void RasterizerStorageGLES2::mesh_remove_surface(RID p_mesh, int p_surface) {
}

int RasterizerStorageGLES2::mesh_get_surface_count(RID p_mesh) const {
	return 0;
}

void RasterizerStorageGLES2::mesh_set_custom_aabb(RID p_mesh, const AABB &p_aabb) {
}

AABB RasterizerStorageGLES2::mesh_get_custom_aabb(RID p_mesh) const {
	return AABB();
}

AABB RasterizerStorageGLES2::mesh_get_aabb(RID p_mesh, RID p_skeleton) const {
	return AABB();
}
void RasterizerStorageGLES2::mesh_clear(RID p_mesh) {
}

/* MULTIMESH API */

RID RasterizerStorageGLES2::multimesh_create() {
	return RID();
}

void RasterizerStorageGLES2::multimesh_allocate(RID p_multimesh, int p_instances, VS::MultimeshTransformFormat p_transform_format, VS::MultimeshColorFormat p_color_format, VS::MultimeshCustomDataFormat p_data) {
}

int RasterizerStorageGLES2::multimesh_get_instance_count(RID p_multimesh) const {
	return 0;
}

void RasterizerStorageGLES2::multimesh_set_mesh(RID p_multimesh, RID p_mesh) {
}

void RasterizerStorageGLES2::multimesh_instance_set_transform(RID p_multimesh, int p_index, const Transform &p_transform) {
}

void RasterizerStorageGLES2::multimesh_instance_set_transform_2d(RID p_multimesh, int p_index, const Transform2D &p_transform) {
}

void RasterizerStorageGLES2::multimesh_instance_set_color(RID p_multimesh, int p_index, const Color &p_color) {
}

void RasterizerStorageGLES2::multimesh_instance_set_custom_data(RID p_multimesh, int p_index, const Color &p_custom_data) {
}

RID RasterizerStorageGLES2::multimesh_get_mesh(RID p_multimesh) const {
	return RID();
}

Transform RasterizerStorageGLES2::multimesh_instance_get_transform(RID p_multimesh, int p_index) const {
	return Transform();
}

Transform2D RasterizerStorageGLES2::multimesh_instance_get_transform_2d(RID p_multimesh, int p_index) const {
	return Transform2D();
}

Color RasterizerStorageGLES2::multimesh_instance_get_color(RID p_multimesh, int p_index) const {
	return Color();
}

Color RasterizerStorageGLES2::multimesh_instance_get_custom_data(RID p_multimesh, int p_index) const {
	return Color();
}

void RasterizerStorageGLES2::multimesh_set_as_bulk_array(RID p_multimesh, const PoolVector<float> &p_array) {
}

void RasterizerStorageGLES2::multimesh_set_visible_instances(RID p_multimesh, int p_visible) {
}

int RasterizerStorageGLES2::multimesh_get_visible_instances(RID p_multimesh) const {
	return 0;
}

AABB RasterizerStorageGLES2::multimesh_get_aabb(RID p_multimesh) const {
	return AABB();
}

void RasterizerStorageGLES2::update_dirty_multimeshes() {
}

/* IMMEDIATE API */

RID RasterizerStorageGLES2::immediate_create() {
	return RID();
}

void RasterizerStorageGLES2::immediate_begin(RID p_immediate, VS::PrimitiveType p_primitive, RID p_texture) {
}

void RasterizerStorageGLES2::immediate_vertex(RID p_immediate, const Vector3 &p_vertex) {
}

void RasterizerStorageGLES2::immediate_normal(RID p_immediate, const Vector3 &p_normal) {
}

void RasterizerStorageGLES2::immediate_tangent(RID p_immediate, const Plane &p_tangent) {
}

void RasterizerStorageGLES2::immediate_color(RID p_immediate, const Color &p_color) {
}

void RasterizerStorageGLES2::immediate_uv(RID p_immediate, const Vector2 &tex_uv) {
}

void RasterizerStorageGLES2::immediate_uv2(RID p_immediate, const Vector2 &tex_uv) {
}

void RasterizerStorageGLES2::immediate_end(RID p_immediate) {
}

void RasterizerStorageGLES2::immediate_clear(RID p_immediate) {
}

AABB RasterizerStorageGLES2::immediate_get_aabb(RID p_immediate) const {
	return AABB();
}

void RasterizerStorageGLES2::immediate_set_material(RID p_immediate, RID p_material) {
}

RID RasterizerStorageGLES2::immediate_get_material(RID p_immediate) const {
	return RID();
}

/* SKELETON API */

RID RasterizerStorageGLES2::skeleton_create() {
	return RID();
}

void RasterizerStorageGLES2::skeleton_allocate(RID p_skeleton, int p_bones, bool p_2d_skeleton) {
}

int RasterizerStorageGLES2::skeleton_get_bone_count(RID p_skeleton) const {
	return 0;
}

void RasterizerStorageGLES2::skeleton_bone_set_transform(RID p_skeleton, int p_bone, const Transform &p_transform) {
}

Transform RasterizerStorageGLES2::skeleton_bone_get_transform(RID p_skeleton, int p_bone) const {
	return Transform();
}
void RasterizerStorageGLES2::skeleton_bone_set_transform_2d(RID p_skeleton, int p_bone, const Transform2D &p_transform) {
}

Transform2D RasterizerStorageGLES2::skeleton_bone_get_transform_2d(RID p_skeleton, int p_bone) const {
	return Transform2D();
}

void RasterizerStorageGLES2::skeleton_set_base_transform_2d(RID p_skeleton, const Transform2D &p_base_transform) {
}

void RasterizerStorageGLES2::skeleton_set_world_transform(RID p_skeleton, bool p_enable, const Transform &p_world_transform) {
}

void RasterizerStorageGLES2::_update_skeleton_transform_buffer(const PoolVector<float> &p_data, size_t p_size) {
}

void RasterizerStorageGLES2::update_dirty_skeletons() {
}

/* Light API */

RID RasterizerStorageGLES2::light_create(VS::LightType p_type) {
	return RID();
}

void RasterizerStorageGLES2::light_set_color(RID p_light, const Color &p_color) {
}

void RasterizerStorageGLES2::light_set_param(RID p_light, VS::LightParam p_param, float p_value) {
}

void RasterizerStorageGLES2::light_set_shadow(RID p_light, bool p_enabled) {
}

void RasterizerStorageGLES2::light_set_shadow_color(RID p_light, const Color &p_color) {
}

void RasterizerStorageGLES2::light_set_projector(RID p_light, RID p_texture) {
}

void RasterizerStorageGLES2::light_set_negative(RID p_light, bool p_enable) {
}

void RasterizerStorageGLES2::light_set_cull_mask(RID p_light, uint32_t p_mask) {
}

void RasterizerStorageGLES2::light_set_reverse_cull_face_mode(RID p_light, bool p_enabled) {
}

void RasterizerStorageGLES2::light_omni_set_shadow_mode(RID p_light, VS::LightOmniShadowMode p_mode) {
}

VS::LightOmniShadowMode RasterizerStorageGLES2::light_omni_get_shadow_mode(RID p_light) {
	return VS::LightOmniShadowMode::LIGHT_OMNI_SHADOW_CUBE;
}

void RasterizerStorageGLES2::light_omni_set_shadow_detail(RID p_light, VS::LightOmniShadowDetail p_detail) {
}

void RasterizerStorageGLES2::light_directional_set_shadow_mode(RID p_light, VS::LightDirectionalShadowMode p_mode) {
}

void RasterizerStorageGLES2::light_directional_set_blend_splits(RID p_light, bool p_enable) {
}

bool RasterizerStorageGLES2::light_directional_get_blend_splits(RID p_light) const {
	return false;
}

VS::LightDirectionalShadowMode RasterizerStorageGLES2::light_directional_get_shadow_mode(RID p_light) {
	return VS::LightDirectionalShadowMode::LIGHT_DIRECTIONAL_SHADOW_ORTHOGONAL;
}

void RasterizerStorageGLES2::light_directional_set_shadow_depth_range_mode(RID p_light, VS::LightDirectionalShadowDepthRangeMode p_range_mode) {
}

VS::LightDirectionalShadowDepthRangeMode RasterizerStorageGLES2::light_directional_get_shadow_depth_range_mode(RID p_light) const {
	return VS::LightDirectionalShadowDepthRangeMode::LIGHT_DIRECTIONAL_SHADOW_DEPTH_RANGE_OPTIMIZED;
}

VS::LightType RasterizerStorageGLES2::light_get_type(RID p_light) const {
	return VS::LightType::LIGHT_DIRECTIONAL;
}

float RasterizerStorageGLES2::light_get_param(RID p_light, VS::LightParam p_param) {
	return 0.f;
}

Color RasterizerStorageGLES2::light_get_color(RID p_light) {
	return Color();
}

bool RasterizerStorageGLES2::light_has_shadow(RID p_light) const {
	return false;
}

uint64_t RasterizerStorageGLES2::light_get_version(RID p_light) const {
	return 0;
}

AABB RasterizerStorageGLES2::light_get_aabb(RID p_light) const {
	return AABB();
}

/* PROBE API */

RID RasterizerStorageGLES2::reflection_probe_create() {
	return RID();
}

void RasterizerStorageGLES2::reflection_probe_set_update_mode(RID p_probe, VS::ReflectionProbeUpdateMode p_mode) {
}

void RasterizerStorageGLES2::reflection_probe_set_intensity(RID p_probe, float p_intensity) {
}

void RasterizerStorageGLES2::reflection_probe_set_interior_ambient(RID p_probe, const Color &p_ambient) {
}

void RasterizerStorageGLES2::reflection_probe_set_interior_ambient_energy(RID p_probe, float p_energy) {
}

void RasterizerStorageGLES2::reflection_probe_set_interior_ambient_probe_contribution(RID p_probe, float p_contrib) {
}

void RasterizerStorageGLES2::reflection_probe_set_max_distance(RID p_probe, float p_distance) {
}
void RasterizerStorageGLES2::reflection_probe_set_extents(RID p_probe, const Vector3 &p_extents) {
}
void RasterizerStorageGLES2::reflection_probe_set_origin_offset(RID p_probe, const Vector3 &p_offset) {
}

void RasterizerStorageGLES2::reflection_probe_set_as_interior(RID p_probe, bool p_enable) {
}
void RasterizerStorageGLES2::reflection_probe_set_enable_box_projection(RID p_probe, bool p_enable) {
}

void RasterizerStorageGLES2::reflection_probe_set_enable_shadows(RID p_probe, bool p_enable) {
}
void RasterizerStorageGLES2::reflection_probe_set_cull_mask(RID p_probe, uint32_t p_layers) {
}

void RasterizerStorageGLES2::reflection_probe_set_resolution(RID p_probe, int p_resolution) {
}

AABB RasterizerStorageGLES2::reflection_probe_get_aabb(RID p_probe) const {
	return AABB();
}
VS::ReflectionProbeUpdateMode RasterizerStorageGLES2::reflection_probe_get_update_mode(RID p_probe) const {
	return VS::ReflectionProbeUpdateMode::REFLECTION_PROBE_UPDATE_ALWAYS;
}

uint32_t RasterizerStorageGLES2::reflection_probe_get_cull_mask(RID p_probe) const {
	return 0;
}

Vector3 RasterizerStorageGLES2::reflection_probe_get_extents(RID p_probe) const {
	return Vector3();
}
Vector3 RasterizerStorageGLES2::reflection_probe_get_origin_offset(RID p_probe) const {
	return Vector3();
}

bool RasterizerStorageGLES2::reflection_probe_renders_shadows(RID p_probe) const {
	return false;
}

float RasterizerStorageGLES2::reflection_probe_get_origin_max_distance(RID p_probe) const {
	return 0.f;
}

int RasterizerStorageGLES2::reflection_probe_get_resolution(RID p_probe) const {
	return 0;
}

RID RasterizerStorageGLES2::gi_probe_create() {
	return RID();
}

void RasterizerStorageGLES2::gi_probe_set_bounds(RID p_probe, const AABB &p_bounds) {
}

AABB RasterizerStorageGLES2::gi_probe_get_bounds(RID p_probe) const {
	return AABB();
}

void RasterizerStorageGLES2::gi_probe_set_cell_size(RID p_probe, float p_size) {
}

float RasterizerStorageGLES2::gi_probe_get_cell_size(RID p_probe) const {
	return 0.0;
}

void RasterizerStorageGLES2::gi_probe_set_to_cell_xform(RID p_probe, const Transform &p_xform) {
}

Transform RasterizerStorageGLES2::gi_probe_get_to_cell_xform(RID p_probe) const {
	return Transform();
}

void RasterizerStorageGLES2::gi_probe_set_dynamic_data(RID p_probe, const PoolVector<int> &p_data) {
}

PoolVector<int> RasterizerStorageGLES2::gi_probe_get_dynamic_data(RID p_probe) const {
	return PoolVector<int>();
}

void RasterizerStorageGLES2::gi_probe_set_dynamic_range(RID p_probe, int p_range) {
}

int RasterizerStorageGLES2::gi_probe_get_dynamic_range(RID p_probe) const {
	return 0;
}

void RasterizerStorageGLES2::gi_probe_set_energy(RID p_probe, float p_range) {
}

void RasterizerStorageGLES2::gi_probe_set_bias(RID p_probe, float p_range) {
}

void RasterizerStorageGLES2::gi_probe_set_normal_bias(RID p_probe, float p_range) {
}

void RasterizerStorageGLES2::gi_probe_set_propagation(RID p_probe, float p_range) {
}

void RasterizerStorageGLES2::gi_probe_set_interior(RID p_probe, bool p_enable) {
}

bool RasterizerStorageGLES2::gi_probe_is_interior(RID p_probe) const {
	return false;
}

void RasterizerStorageGLES2::gi_probe_set_compress(RID p_probe, bool p_enable) {
}

bool RasterizerStorageGLES2::gi_probe_is_compressed(RID p_probe) const {
	return false;
}
float RasterizerStorageGLES2::gi_probe_get_energy(RID p_probe) const {
	return 0;
}

float RasterizerStorageGLES2::gi_probe_get_bias(RID p_probe) const {
	return 0;
}

float RasterizerStorageGLES2::gi_probe_get_normal_bias(RID p_probe) const {
	return 0;
}

float RasterizerStorageGLES2::gi_probe_get_propagation(RID p_probe) const {
	return 0;
}

uint32_t RasterizerStorageGLES2::gi_probe_get_version(RID p_probe) {
	return 0;
}

RasterizerStorage::GIProbeCompression RasterizerStorageGLES2::gi_probe_get_dynamic_data_get_preferred_compression() const {
	return GI_PROBE_UNCOMPRESSED;
}

RID RasterizerStorageGLES2::gi_probe_dynamic_data_create(int p_width, int p_height, int p_depth, GIProbeCompression p_compression) {
	return RID();
}

void RasterizerStorageGLES2::gi_probe_dynamic_data_update(RID p_gi_probe_data, int p_depth_slice, int p_slice_count, int p_mipmap, const void *p_data) {
}

///////

RID RasterizerStorageGLES2::lightmap_capture_create() {
	return RID();
}

void RasterizerStorageGLES2::lightmap_capture_set_bounds(RID p_capture, const AABB &p_bounds) {
}
AABB RasterizerStorageGLES2::lightmap_capture_get_bounds(RID p_capture) const {
	return AABB();
}
void RasterizerStorageGLES2::lightmap_capture_set_octree(RID p_capture, const PoolVector<uint8_t> &p_octree) {
}
PoolVector<uint8_t> RasterizerStorageGLES2::lightmap_capture_get_octree(RID p_capture) const {
	return PoolVector<uint8_t>();
}

void RasterizerStorageGLES2::lightmap_capture_set_octree_cell_transform(RID p_capture, const Transform &p_xform) {
}

Transform RasterizerStorageGLES2::lightmap_capture_get_octree_cell_transform(RID p_capture) const {
	return Transform();
}

void RasterizerStorageGLES2::lightmap_capture_set_octree_cell_subdiv(RID p_capture, int p_subdiv) {
}

int RasterizerStorageGLES2::lightmap_capture_get_octree_cell_subdiv(RID p_capture) const {
	return 0;
}

void RasterizerStorageGLES2::lightmap_capture_set_energy(RID p_capture, float p_energy) {
}

float RasterizerStorageGLES2::lightmap_capture_get_energy(RID p_capture) const {
	return 0.f;
}

const PoolVector<RasterizerStorage::LightmapCaptureOctree> *RasterizerStorageGLES2::lightmap_capture_get_octree_ptr(RID p_capture) const {
	return NULL;
}

///////

RID RasterizerStorageGLES2::particles_create() {
	return RID();
}

void RasterizerStorageGLES2::particles_set_emitting(RID p_particles, bool p_emitting) {
}

bool RasterizerStorageGLES2::particles_get_emitting(RID p_particles) {
	return false;
}

void RasterizerStorageGLES2::particles_set_amount(RID p_particles, int p_amount) {
}

void RasterizerStorageGLES2::particles_set_lifetime(RID p_particles, float p_lifetime) {
}

void RasterizerStorageGLES2::particles_set_one_shot(RID p_particles, bool p_one_shot) {
}

void RasterizerStorageGLES2::particles_set_pre_process_time(RID p_particles, float p_time) {
}

void RasterizerStorageGLES2::particles_set_explosiveness_ratio(RID p_particles, float p_ratio) {
}

void RasterizerStorageGLES2::particles_set_randomness_ratio(RID p_particles, float p_ratio) {
}

void RasterizerStorageGLES2::particles_set_custom_aabb(RID p_particles, const AABB &p_aabb) {
}

void RasterizerStorageGLES2::particles_set_speed_scale(RID p_particles, float p_scale) {
}

void RasterizerStorageGLES2::particles_set_use_local_coordinates(RID p_particles, bool p_enable) {
}

void RasterizerStorageGLES2::particles_set_fixed_fps(RID p_particles, int p_fps) {
}

void RasterizerStorageGLES2::particles_set_fractional_delta(RID p_particles, bool p_enable) {
}

void RasterizerStorageGLES2::particles_set_process_material(RID p_particles, RID p_material) {
}

void RasterizerStorageGLES2::particles_set_draw_order(RID p_particles, VS::ParticlesDrawOrder p_order) {
}

void RasterizerStorageGLES2::particles_set_draw_passes(RID p_particles, int p_passes) {
}

void RasterizerStorageGLES2::particles_set_draw_pass_mesh(RID p_particles, int p_pass, RID p_mesh) {
}

void RasterizerStorageGLES2::particles_restart(RID p_particles) {
}

void RasterizerStorageGLES2::particles_request_process(RID p_particles) {
}

AABB RasterizerStorageGLES2::particles_get_current_aabb(RID p_particles) {
	return AABB();
}

AABB RasterizerStorageGLES2::particles_get_aabb(RID p_particles) const {
	return AABB();
}

void RasterizerStorageGLES2::particles_set_emission_transform(RID p_particles, const Transform &p_transform) {
}

int RasterizerStorageGLES2::particles_get_draw_passes(RID p_particles) const {
	return 0;
}

RID RasterizerStorageGLES2::particles_get_draw_pass_mesh(RID p_particles, int p_pass) const {
	return RID();
}

void RasterizerStorageGLES2::update_particles() {
}

bool RasterizerStorageGLES2::particles_is_inactive(RID p_particles) const {
	return true;
}

////////

void RasterizerStorageGLES2::instance_add_skeleton(RID p_skeleton, RasterizerScene::InstanceBase *p_instance) {
}

void RasterizerStorageGLES2::instance_remove_skeleton(RID p_skeleton, RasterizerScene::InstanceBase *p_instance) {
}

void RasterizerStorageGLES2::instance_add_dependency(RID p_base, RasterizerScene::InstanceBase *p_instance) {
}

void RasterizerStorageGLES2::instance_remove_dependency(RID p_base, RasterizerScene::InstanceBase *p_instance) {
}

/* RENDER TARGET */

void RasterizerStorageGLES2::_render_target_allocate(RenderTarget *rt) {
}

void RasterizerStorageGLES2::_render_target_clear(RenderTarget *rt) {
}

RID RasterizerStorageGLES2::render_target_create() {
	return RID();
}

void RasterizerStorageGLES2::render_target_set_size(RID p_render_target, int p_width, int p_height) {
}

RID RasterizerStorageGLES2::render_target_get_texture(RID p_render_target) const {
	return RID();
}

void RasterizerStorageGLES2::render_target_set_flag(RID p_render_target, RenderTargetFlags p_flag, bool p_value) {
}

bool RasterizerStorageGLES2::render_target_was_used(RID p_render_target) {
	return true;
}

void RasterizerStorageGLES2::render_target_clear_used(RID p_render_target) {
}

void RasterizerStorageGLES2::render_target_set_msaa(RID p_render_target, VS::ViewportMSAA p_msaa) {
}

/* CANVAS SHADOW */

RID RasterizerStorageGLES2::canvas_light_shadow_buffer_create(int p_width) {
	return RID();
}

/* LIGHT SHADOW MAPPING */

RID RasterizerStorageGLES2::canvas_light_occluder_create() {
	return RID();
}

void RasterizerStorageGLES2::canvas_light_occluder_set_polylines(RID p_occluder, const PoolVector<Vector2> &p_lines) {
}

VS::InstanceType RasterizerStorageGLES2::get_base_type(RID p_rid) const {
	return VS::INSTANCE_NONE;
}

bool RasterizerStorageGLES2::free(RID p_rid) {
	return false;
}

bool RasterizerStorageGLES2::has_os_feature(const String &p_feature) const {
	return false;
}

////////////////////////////////////////////

void RasterizerStorageGLES2::set_debug_generate_wireframes(bool p_generate) {
}

void RasterizerStorageGLES2::render_info_begin_capture() {
}

void RasterizerStorageGLES2::render_info_end_capture() {
}

int RasterizerStorageGLES2::get_captured_render_info(VS::RenderInfo p_info) {
	return 0;
}

void RasterizerStorageGLES2::initialize() {
}

void RasterizerStorageGLES2::finalize() {
}

void RasterizerStorageGLES2::_copy_screen() {
}

void RasterizerStorageGLES2::update_dirty_resources() {
}

RasterizerStorageGLES2::RasterizerStorageGLES2() {
}

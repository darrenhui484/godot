/*************************************************************************/
/*  noise.h                                                              */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2018 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2018 Godot Engine contributors (cf. AUTHORS.md)    */
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

#ifndef NOISE_H
#define NOISE_H

#include <reference.h>
#include "lib/fast_noise/FastNoise.h"
#include "lib/open_simplex/open-simplex-noise.h"

typedef fastnoise::FastNoise _Noise;

class Noise : public Reference {
	GDCLASS(Noise, Reference);

public:

	// Enums Godot-style (same values)

	enum Type {
		TYPE_VALUE = _Noise::Value,
		TYPE_VALUE_FRACTAL = _Noise::ValueFractal,
		TYPE_GRADIENT = _Noise::Gradient,
		TYPE_GRADIENT_FRACTAL = _Noise::GradientFractal,
		TYPE_SIMPLEX = _Noise::Simplex,
		TYPE_SIMPLEX_FRACTAL = _Noise::SimplexFractal,
		TYPE_CELLULAR = _Noise::Cellular,
		TYPE_CELLULAR_HQ = _Noise::CellularHQ,
		TYPE_WHITE_NOISE = _Noise::WhiteNoise
	};

	enum Interpolation {
		INTERP_LINEAR = _Noise::InterpLinear,
		INTERP_QUINTIC = _Noise::InterpQuintic,
		INTERP_HERMITE = _Noise::InterpHermite
	};

	enum FractalType {
		FRACTAL_FBM = _Noise::FBM,
		FRACTAL_BILLOW = _Noise::Billow,
		FRACTAL_RIGID_MULTI = _Noise::RigidMulti
	};

	enum CellularDistanceFunction {
		DISTANCE_EUCLIDEAN = _Noise::Euclidean,
		DISTANCE_MANHATTAN = _Noise::Manhattan,
		DISTANCE_NATURAL = _Noise::Natural
	};

	enum CellularReturnType {
		RETURN_CELL_VALUE = _Noise::CellValue,
		RETURN_NOISE_LOOKUP = _Noise::NoiseLookup,
		RETURN_DISTANCE_2_CENTER = _Noise::Distance2Center,
		RETURN_DISTANCE_2_CENTER_X_VALUE = _Noise::Distance2CenterXValue,
		RETURN_DISTANCE_2_CENTER_SQ = _Noise::Distance2CenterSq,
		RETURN_DISTANCE_2_CENTER_SQ_X_VALUE = _Noise::Distance2CenterSqXValue,
		RETURN_DISTANCE_2_EDGE = _Noise::Distance2Edge,
		RETURN_DISTANCE_2_EDGE_X_VALUE = _Noise::Distance2EdgeXValue,
		RETURN_DISTANCE_2_EDGE_SQ = _Noise::Distance2EdgeSq,
		RETURN_DISTANCE_2_EDGE_SQ_X_VALUE = _Noise::Distance2EdgeSqXValue
	};

	Noise();

	// Methods (Godot-style mappings to Noise)

	int get_seed() { return _noise.GetSeed(); } // TODO should be const
	void set_seed(int seed) { _noise.SetSeed(seed); }

	void set_noise_type(Type noise_type) { _noise.SetNoiseType((_Noise::NoiseType)noise_type); }
	_Noise::NoiseType get_noise_type() { return _noise.GetNoiseType(); }
	void set_interpolation(Interpolation interp) { _noise.SetInterp((_Noise::Interp)interp); }
	void set_frequency(float freq) { _noise.SetFrequency(freq); }
	void set_fractal_gain(float gain) { _noise.SetFractalGain(gain); }
	void set_fractal_type(FractalType type) { _noise.SetFractalType((_Noise::FractalType)type); }
	void set_fractal_octaves(unsigned int octave_count) { _noise.SetFractalOctaves(octave_count); }
	void set_fractal_lacunarity(float lacunarity) { _noise.SetFractalLacunarity(lacunarity); }
	void set_cellular_distance_function(CellularDistanceFunction func) { _noise.SetCellularDistanceFunction((_Noise::CellularDistanceFunction)func); }
	void set_cellular_return_type(CellularReturnType ret) { _noise.SetCellularReturnType((_Noise::CellularReturnType)ret); }

	// TODO Q: how can I do that properly?
	void set_cellular_noise_lookup(Ref<Noise> other_noise);

	// 2D

	float get_noise_2d(float x, float y);

	//float get_gradient_2d(float x, float y) { return _noise.GetGradient(x, y); }
	//float get_simplex_2d(float x, float y) { return _noise.GetSimplex(x, y); }
	//float get_cellular_2d(float x, float y) { return _noise.GetCellular(x, y); }
	//float get_cellular_hq_2d(float x, float y) { return _noise.GetCellularHQ(x, y); }
	//float get_white_noise_2d(float x, float y) { return _noise.GetWhiteNoise(x, y); }
	//float get_value_2d(float x, float y) { return _noise.GetValue(x, y); }

	// 3D

	float get_noise_3d(float x, float y, float z) { return _noise.GetNoise(x, y, z); }

	//float get_gradient_3d(float x, float y, float z) { return _noise.GetGradient(x, y, z); }
	//float get_simplex_3d(float x, float y, float z) { return _noise.GetSimplex(x, y, z); }
	//float get_cellular_3d(float x, float y, float z) { return _noise.GetCellular(x, y, z); }
	//float get_cellular_hq_3d(float x, float y, float z) { return _noise.GetCellularHQ(x, y, z); }
	//float get_white_noise_3d(float x, float y, float z) { return _noise.GetWhiteNoise(x, y, z); }
	//float get_value_2d(float x, float y, float z) { return _noise.GetValue(x, y, z); }

	// 4D

	float get_simplex_4d(float x, float y, float z, float w) { return _noise.GetSimplex(x, y, z, w); }
	float get_white_noise_4d(float x, float y, float z, float w) { return _noise.GetWhiteNoise(x, y, z, w); }

	// Convenience

	float get_noise_2dv(Vector2 pos) { return _noise.GetNoise(pos.x, pos.y); }
	float get_noise_3dv(Vector3 pos) { return _noise.GetNoise(pos.x, pos.y, pos.z); }


protected:
	static void _bind_methods();

private:
	_Noise _noise;
	Ref<Noise> _cellular_lookup_ref;

	Ref<OsnNoise> _osn_noise;
	Ref<OsnFractalNoise> _osn_fractal_noise;
};

// Make Variant happy with custom enums
VARIANT_ENUM_CAST(Noise::Type);
VARIANT_ENUM_CAST(Noise::FractalType);
VARIANT_ENUM_CAST(Noise::Interpolation);
VARIANT_ENUM_CAST(Noise::CellularDistanceFunction);
VARIANT_ENUM_CAST(Noise::CellularReturnType);

// NOTE: The Osn classes are only provided for use in substituting the simple noise 2D methods
//       and thereby side-stepping any patents for the simplex noise algorithm in image generation.

// C++ wrapper for OpenSimplex context.
// Allocates permutation memory for each instance.
class OsnNoise : public Reference {
	GDCLASS(OsnNoise, Reference)

		osn_context * _context;
	int _seed;

public:
	OsnNoise();
	~OsnNoise();

	void set_seed(int seed);
	int get_seed();

	_FORCE_INLINE_ float get_noise_2d(float x, float y) { return open_simplex_noise2(_context, x, y); }
	_FORCE_INLINE_ float get_noise_3d(float x, float y, float z) { return open_simplex_noise3(_context, x, y, z); }
	_FORCE_INLINE_ float get_noise_4d(float x, float y, float z, float w) { return open_simplex_noise4(_context, x, y, z, w); }

	// Convenience

	_FORCE_INLINE_ float get_noise_2dv(Vector2 v) { return open_simplex_noise2(_context, v.x, v.y); }
	_FORCE_INLINE_ float get_noise_3dv(Vector3 v) { return open_simplex_noise3(_context, v.x, v.y, v.z); }

protected:
	static void _bind_methods();

};

// TODO: if the OpenSimplex library didn't allocated memory for each seed, there could be just one, easy to use class...

// Fractal noise generator with a few tweakable parameters. Lightweight.
// This is mostly used in games for generating heightmaps or clouds.
class OsnFractalNoise : public Reference {
	GDCLASS(OsnFractalNoise, Reference)

		Ref<OsnNoise> _noise;

	float _persistance; // Controls details, value in [0,1]. Higher increases grain, lower increases smoothness.
	int _octaves; // Number of noise layers
	float _period; // Distance above which we start to see similarities. The higher, the longer "hills" will be on a terrain.
	float _lacunarity; // Controls period change across octaves. 2 is usually a good value to address all detail levels.

public:
	OsnFractalNoise();

	Ref<OsnNoise> get_source_noise() { return _noise; }
	void set_source_noise(Ref<OsnNoise> noise) { _noise = noise; }

	void set_octaves(int count) { _octaves = count; }
	int get_octaves() const { return _octaves; }

	void set_period(float p) { _period = p; }
	float get_period() const { return _period; }

	void set_persistance(float p) { _persistance = p; }
	float get_persistance() const { return _persistance; }

	void set_lacunarity(float lacunarity) { _lacunarity = lacunarity; }
	float get_lacunarity() const { return _lacunarity; }

	float get_noise_2d(float x, float y);
	float get_noise_3d(float x, float y, float z);
	float get_noise_4d(float x, float y, float z, float w);

	// Convenience

	_FORCE_INLINE_ float get_noise_2dv(Vector2 v) { return get_noise_2d(v.x, v.y); }
	_FORCE_INLINE_ float get_noise_3dv(Vector3 v) { return get_noise_3d(v.x, v.y, v.z); }

protected:
	static void _bind_methods();

};

#endif

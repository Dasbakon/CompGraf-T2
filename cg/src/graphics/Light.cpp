//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2018, 2022 Orthrus Group.                         |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: Light.cpp
// ========
// Source file for light.
//
// Author: Paulo Pagliosa
// Last revision: 22/01/2022

#include "graphics/Light.h"

namespace cg
{ // begin namespace cg


/////////////////////////////////////////////////////////////////////
//
// Light implementation
// =====
static inline unsigned int
nextLightId()
{
  static unsigned int lid;
  return ++lid;
}

Light::Light():
  _type{Type::Directional},
  flags{TurnedOn | Infinite},
  color{Color::white},
  position{vec3f::null()},
  direction{0, 0, 1},
  falloff{Falloff::Constant},
  _range{0},
  _spotAngle{60}
{
  setName("Light %d", nextLightId());
}

void
Light::setRange(float value)
{
  _range = math::max<float>(0, value);
}

void
Light::setSpotAngle(float value)
{
  _spotAngle = math::clamp(value, minSpotAngle, maxSpotAngle);
}

} // end namespace cg

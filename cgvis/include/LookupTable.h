//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2018, 2022 Paulo Pagliosa.                        |
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
// OVERVIEW: LookupTable.h
// ========
// Class definition for lookup table.
//
// Author: Paulo Pagliosa
// Last revision: 17/02/2022

#ifndef __LookupTable_h
#define __LookupTable_h

#include "graphics/Color.h"
#include "Object.h"
#include <vector>

namespace cg
{ // begin namespace cg

namespace vis
{ // begin namespace vis


/////////////////////////////////////////////////////////////////////
//
// LookupTable: lookup table class
// ===========
class LookupTable: public Object
{
public:
  LookupTable(int size = 256);

  void build();

  void setScalarRange(float min, float max);

  auto minScalar() const
  {
    return _scalarRange[0];
  }

  auto maxScalar() const
  {
    return _scalarRange[1];
  }

  void setHueRange(float min, float max)
  {
    _hueRange[0] = min;
    _hueRange[1] = max;
    _buildTime.reset();
  }

  auto minHue() const
  {
    return _hueRange[0];
  }

  auto maxHue() const
  {
    return _hueRange[1];
  }

  void setSaturationRange(float min, float max)
  {
    _saturationRange[0] = min;
    _saturationRange[1] = max;
    _buildTime.reset();
  }

  auto minSaturation() const
  {
    return _saturationRange[0];
  }

  auto maxSaturation() const
  {
    return _saturationRange[1];
  }

  void setValueRange(float min, float max)
  {
    _valueRange[0] = min;
    _valueRange[1] = max;
    _buildTime.reset();
  }

  auto minValue() const
  {
    return _valueRange[0];
  }

  auto maxValue() const
  {
    return _valueRange[1];
  }

  const Color& mapValue(float) const;

  auto size() const
  {
    return int(_colors.size());
  }

  auto& operator [](int i)
  {
    return _colors[i];
  }

  const auto& operator [](int i) const
  {
    return _colors[i];
  }

protected:
  std::vector<Color> _colors;
  float _scalarRange[2];
  float _hueRange[2];
  float _saturationRange[2];
  float _valueRange[2];
  Timestamp _buildTime;

}; // LookupTable

} // end namespace vis

} // end namespace cg

#endif // __LookupTable_h

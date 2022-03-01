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
// OVERVIEW: TriCellMeshMapper.h
// ========
// Class definition for vis tri cell mesh mapper.
//
// Author: Paulo Pagliosa
// Last revision: 01/03/2022

#ifndef __TriCellMeshMapper_h
#define __TriCellMeshMapper_h

#include "Mapper.h"
#include "TriCellMesh.h"
#include "graphics/GLMesh.h"

namespace cg
{ // begin namespace cg

namespace vis
{ // begin namespace vis


/////////////////////////////////////////////////////////////////////
//
// TriCellMeshMapper: tri cell mesh mapper class
// =================
class TriCellMeshMapper final: public Mapper<TriCellMesh>
{
public:
  using Base = Mapper<TriCellMesh>;

  static Reference<TriCellMeshMapper> New()
  {
    return new TriCellMeshMapper;
  }

  const char* name() const override;

private:
  mutable Reference<GLColorBuffer> _colorBuffer;

  void renderColorMap() const;

  bool mapColors(Scalars*) const override;
  bool draw(GLRenderer&) const override;

}; // TriCellMeshMapper

} // end namespace vis

} // end namespace cg

#endif // __TriCellMeshMapper_h

//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2022 Orthrus Group.                               |
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
// OVERVIEW: LightProxy.cpp
// ========
// Source file for light proxy.
//
// Author: Paulo Pagliosa
// Last revision: 20/01/2022

#include "graph/LightProxy.h"
#include "graph/Scene.h"

namespace cg
{ // begin namespace cg

namespace graph
{ // begin namespace graph


/////////////////////////////////////////////////////////////////////
//
// LightProxy implementation
// ==========
void
LightProxy::onAfterAdded()
{
  assert(sceneObject() != nullptr);
  sceneObject()->scene()->addLight(_object);
}

void
LightProxy::onBeforeRemoved()
{
  assert(sceneObject() != nullptr);
  sceneObject()->scene()->removeLight(_object);
}

} // end namepace graph

} // end namespace cg
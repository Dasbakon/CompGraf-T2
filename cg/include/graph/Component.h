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
// OVERVIEW: Component.h
// ========
// Class definition for scene object component.
//
// Author: Paulo Pagliosa
// Last revision: 24/01/2022

#ifndef __SceneObjectComponent_h
#define __SceneObjectComponent_h

#include "core/SharedObject.h"

namespace cg
{ // begin namespace cg

namespace graph
{ // begin namespace graph

class SceneObject;
class Transform;


/////////////////////////////////////////////////////////////////////
//
// Component: scene object component class
// =========
class Component abstract: public SharedObject
{
public:
  /// Returns the type name of this component.
  auto typeName() const
  {
    return _typeName;
  }

  /// Returns the scene object owning this component.
  auto sceneObject() const
  {
    return _sceneObject;
  }

  /// Returns the transform of this component.
  Transform* transform() const; // implemented in SceneObject.h

  /// Returns true if this component is erasable.
  auto erasable() const
  {
    return _erasable;
  }

protected:
  Component(const char* const typeName, bool erasable = true):
    _typeName{typeName},
    _erasable{erasable}
  {
    // do nothing
  }

  virtual bool canBeSiblingOf(Component* component) const;

  virtual void afterAdded();
  virtual void beforeRemoved();
  virtual void update();
  virtual void setVisible(bool value);

private:
  const char* const _typeName;
  SceneObject* _sceneObject{};
  bool _erasable;

  friend class SceneObject;

}; // Component

} // end namepace graph

} // end namespace cg

#endif // __SceneObjectComponent_h

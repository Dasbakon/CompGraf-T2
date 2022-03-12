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
// OVERVIEW: MainWindow.cpp
// ========
// Source file for cg vis demo main window.
//
// Author: Paulo Pagliosa
// Last revision: 11/03/2022

#include "ContourFilter.h"
#include "ElevationFilter.h"
#include "PolyDataMapper.h"
#include "TransformFilter.h"
#include "TriCellMeshMapper.h"
#include "TriCellMeshReader.h"
#include "SphereSource.h"
#include "MainWindow.h"
#include <utility>

namespace cg::vis
{ // begin namespace cg::vis

std::pair<Actor*, Actor*>
pipelineTest(Source<TriCellMesh>* source, LookupTable* colorTable)
{
  auto elevationFilter = ElevationFilter<TriCellMesh>::New();

  elevationFilter->setInput(*source);
  elevationFilter->setDirection(ElevationDirection::Z);

  auto meshMapper = TriCellMeshMapper::New();

  meshMapper->setInput(*elevationFilter);
  meshMapper->setLookupTable(colorTable);

  auto contourFilter = ContourFilter<TriCellMesh>::New();

  contourFilter->setInput(*elevationFilter);
  contourFilter->generateValues(10, 0, 1);

  auto isolineMapper = PolyDataMapper::New();

  isolineMapper->setInput(*contourFilter);
  isolineMapper->setLookupTable(colorTable);
  return {new Actor(*meshMapper), new Actor(*isolineMapper)};
}


/////////////////////////////////////////////////////////////////////
//
// MainWindow implementation
// ==========
void
MainWindow::initializeScene()
{
  try
  {
    auto scene = this->scene();

    {
      auto colorTable = LookupTable::jet();
      auto sphere = SphereSource::New();

      sphere->setResolution(20);

      auto [a1, a2] = pipelineTest(sphere, colorTable);

      scene->addActor(a1, "Sphere");
      scene->addActor(a2, "Sphere Isolines");

      auto transformFilter = TransformFilter<TriCellMesh>::New();

      transformFilter->setInput(*sphere);
      transformFilter->setPosition(vec3f{2, 0, 0});
      transformFilter->setScale(vec3f{0.5f, 1.5f, 2});

      auto [a3, a4] = pipelineTest(transformFilter, colorTable);

      scene->addActor(a3, "Transformed Sphere");
      scene->addActor(a4, "Transformed Sphere Isolines");
    }
    {
      auto colorTable = LookupTable::cooper();
      auto reader = TriCellMeshReader::New();

      reader->setPath("../../../cgdemo/assets/meshes/f-16.obj");

      auto [a1, a2] = pipelineTest(reader, colorTable);

      scene->addActor(a1, "F-16");
      scene->addActor(a2, "F-16 Isolines");
    }

    auto light = new Light;

    light->setType(Light::Type::Directional);
    light->setEulerAngles({50, 30, 0});
    scene->addLight(light, "Main Light");
    scene->ambientLight = Color::gray;
  }
  catch (const std::exception& e)
  {
    std::cout << "Error: " << e.what() << '\n';
  }
}

inline void
MainWindow::showOptions()
{
  ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.6f);
  ImGui::showStyleSelector("Color Theme##Selector");
  ImGui::colorEdit3("Selected Actor Bounds", _selectedWireframeColor);
  ImGui::PopItemWidth();
}

inline void
MainWindow::fileMenu()
{
  if (ImGui::MenuItem("Exit", "Alt+F4"))
  {
    shutdown();
  }
}

inline void
MainWindow::mainMenu()
{
  if (ImGui::BeginMainMenuBar())
  {
    if (ImGui::BeginMenu("File"))
    {
      fileMenu();
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View"))
    {
      ImGui::MenuItem("Scene Window", nullptr, &_showHierarchy);
      ImGui::MenuItem("Inspector Window", nullptr, &_showInspector);
      ImGui::MenuItem("Editor View Settings", nullptr, &_showEditorView);
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Tools"))
    {
      if (ImGui::BeginMenu("Options"))
      {
        showOptions();
        ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}

void
MainWindow::gui()
{
  mainMenu();

  constexpr auto evw = (float)360;
  constexpr auto evh = (float)300;
  constexpr auto lft = (float)0;
  constexpr auto top = (float)20;
  auto w = (float)width();
  auto h = (float)height();
  auto evy = h - evh;

  // Hierarchy Window
  ImGui::SetNextWindowPos({lft, top});
  ImGui::SetNextWindowSize({evw, evy - top});
  hierarchyWindow("Scene");
  // Editor View
  ImGui::SetNextWindowPos({lft, evy});
  ImGui::SetNextWindowSize({evw, evh});
  editorView();

  constexpr auto iww = (float)420;
  auto rgt = w - iww;
  auto awh = h / 3;
  auto awy = h - awh;

  // Inspector Window
  ImGui::SetNextWindowPos({rgt, top});
  ImGui::SetNextWindowSize({iww, h - top});
  inspectorWindow();
}

} // end namespace cg::vis
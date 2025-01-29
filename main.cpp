#include <iostream>
#include <memory>

#include "MaterialManager.h"
#include "TextureManager.h"
#include "RaytracingRenderer.hpp"
#include "Sphere.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Quad.hpp"
#include "Triangle.hpp"
#include "Ring.hpp"
#include "Ellipse.hpp"
#include "PointLight.hpp"
#include "Box.hpp"

const Scene CornellBox() {
  Scene scene;
  
  CreateNewMaterial("red");
  GetMaterial("red")->SetDiffuse(vec3(0.65f, 0.05f, 0.0f));
  
  CreateNewMaterial("white");
  GetMaterial("white")->SetDiffuse(vec3(0.73f, 0.73f, 0.73f));
  
  CreateNewMaterial("green");
  GetMaterial("green")->SetDiffuse(vec3(0.12f, 0.45f, 0.15f));
  
  CreateNewMaterial("light");
  GetMaterial("light")->SetDiffuse(vec3(1.0f));
  GetMaterial("light")->SetEmissionIntensity(15.0f);
  
  scene.AddObject(std::make_shared<Quad>(vec3(555,277.5,277.5), vec3(0,555,0), vec3(0,0,555), "green"));
  scene.AddObject(std::make_shared<Quad>(vec3(0,277.5,277.5), vec3(0,555,0), vec3(0,0,555), "red"));
  scene.AddObject(std::make_shared<Quad>(vec3(278, 554, 274.5), vec3(-130,0,0), vec3(0,0,-105), "light"));
  scene.AddObject(std::make_shared<Quad>(vec3(277.5,0,277.5), vec3(555,0,0), vec3(0,0,555), "white"));
  scene.AddObject(std::make_shared<Quad>(vec3(277.5,555,277.5), vec3(-555,0,0), vec3(0,0,-555), "white"));
  scene.AddObject(std::make_shared<Quad>(vec3(277.5,277.5,555), vec3(555,0,0), vec3(0,555,0), "white"));
  
  auto box1 = std::make_shared<Box>(vec3(397.5f,165.0f,377.5f), vec3(165.0f,330.0f,165.0f), "white");
  box1->SetRotation(vec3(0.0f, 15.0f, 0.0f));
  scene.AddObject(box1);

  auto box2 = std::make_shared<Box>(vec3(212.5f,82.5f,147.5f), vec3(165.0f,165.0f,165.0f), "white");
  box2->SetRotation(vec3(0.0f, -18.0f, 0.0f));
  scene.AddObject(box2);
  
  std::shared_ptr<Camera> camera = std::make_shared<Camera>();
  camera->SetPosition(vec3(278.0f, 278.0f, -800.0f));
  camera->SetSensorWidth(0.036);
  camera->SetFOV(40);
  camera->LookAt(vec3(278.0f, 278.0f, 0.0f));
  camera->SetFocusDistance(10.0);
  camera->SetAperture(100);
  
  scene.AddObject(camera);
  
  return scene;
}

int main(int argc, const char * argv[]) {
  
  Scene scene = CornellBox();
  
  RaytracingRenderer renderer(600, 600);
  renderer.SetSamplesPerPixels(10);
  renderer.SetRayMinDistance(1e-3);
  renderer.SetRayMaxDistance(1e4);
  renderer.SetMaxDepth(50);
  renderer.SetGamma(2.2);
  renderer.SetToneMapping(ToneMapping::NONE);
  
  CreateNewTexture("skybox", vec3(0.0f));
  renderer.SetBackground("skybox");
  
  renderer.Render(scene);
  renderer.SaveToDisk("output");
  
  return 0;
}

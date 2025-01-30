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

#include "vec3.h"

const Scene Spheres() {
  Scene scene;
  
  std::shared_ptr<Camera> camera = std::make_shared<Camera>();
  camera->SetPosition(vec3(13, 2, 3));
  camera->SetSensorWidth(0.036);
  camera->SetFOV(40);
  camera->LookAt(vec3(0, 0, 0.0f));
  camera->SetFocusDistance(10.0);
  camera->SetAperture(100);
  
  scene.AddObject(camera);
  
  CreateNewMaterial("ground");
  GetMaterial("ground")->SetDiffuse(vec3(0.5f, 0.5f, 0.5f));
  scene.AddSphere(vec3(0, -1000, 0), 1000, "ground");
  
  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_float();
      vec3 center(a + 0.9*random_float(), 0.2, b + 0.9*random_float());
      
      if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
        CreateNewMaterial("t" + std::to_string(a) + "p" + std::to_string(b));
        
        if (choose_mat < 0.8) {
          // diffuse
          GetMaterial("t" + std::to_string(a) + "p" + std::to_string(b))->SetDiffuse(random_vec3() * random_vec3());
          scene.AddSphere(center, 0.2, "t" + std::to_string(a) + "p" + std::to_string(b));
        } else if (choose_mat < 0.95) {
          // metal
          GetMaterial("t" + std::to_string(a) + "p" + std::to_string(b))->SetDiffuse(random_vec3(0.5f, 1.0f));
          GetMaterial("t" + std::to_string(a) + "p" + std::to_string(b))->SetMetallic(1.0f);
          GetMaterial("t" + std::to_string(a) + "p" + std::to_string(b))->SetRoughness(random_float(0.0f, 0.05f));
          scene.AddSphere(center, 0.2, "t" + std::to_string(a) + "p" + std::to_string(b));
        } else {
          // glass
          GetMaterial("t" + std::to_string(a) + "p" + std::to_string(b))->SetOpacity(0.0f);
          GetMaterial("t" + std::to_string(a) + "p" + std::to_string(b))->SetIOR(1.5f);
          scene.AddSphere(center, 0.2, "t" + std::to_string(a) + "p" + std::to_string(b));
        }
      }
    }
  }
  
  CreateNewMaterial("glass_sphere");
  GetMaterial("glass_sphere")->SetOpacity(0.0f);
  GetMaterial("glass_sphere")->SetIOR(1.5f);
  scene.AddSphere(vec3(0, 1, 0), 1.0, "glass_sphere");
  
  CreateNewMaterial("diffuse_sphere");
  GetMaterial("diffuse_sphere")->SetDiffuse(vec3(0.4f, 0.2f, 0.1f));
  scene.AddSphere(vec3(-4, 1, 0), 1.0, "diffuse_sphere");
  
  CreateNewMaterial("metal_sphere");
  GetMaterial("metal_sphere")->SetDiffuse(vec3(0.7f, 0.6f, 0.5f));
  GetMaterial("metal_sphere")->SetMetallic(1.0f);
  GetMaterial("metal_sphere")->SetRoughness(0.0f);
  scene.AddSphere(vec3(4, 1, 0), 1.0, "metal_sphere");

  
  return scene;
}

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
//  box1->SetRotation(vec3(0.0f, 15.0f, 0.0f));
  scene.AddObject(box1);
  
  auto box2 = std::make_shared<Box>(vec3(212.5f,82.5f,147.5f), vec3(165.0f,165.0f,165.0f), "white");
//  box2->SetRotation(vec3(0.0f, -18.0f, 0.0f));
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

const Scene ExampleScene() {
  Scene scene;
  
  std::shared_ptr<Camera> camera = std::make_shared<Camera>();
  camera->SetPosition(vec3(478, 278, -800));
  camera->SetSensorWidth(0.036);
  camera->SetFOV(40);
  camera->LookAt(vec3(278.0f, 278.0f, 0.0f));
  camera->SetFocusDistance(10.0);
  camera->SetAperture(100);
  
  scene.AddObject(camera);
  
  CreateNewMaterial("ground");
  GetMaterial("ground")->SetDiffuse(vec3(0.48, 0.83, 0.53));
  
  int boxes_per_side = 20;
  float box_size = 100.0;
  
  for (int i = 0; i < boxes_per_side; i++) {
    for (int j = 0; j < boxes_per_side; j++) {
      auto x0 = -1000.0 + i*box_size;
      auto z0 = -1000.0 + j*box_size;
      
      auto height = random_float(1,101);
      
      vec3 pos = vec3(x0 + box_size, height, z0) / 2.0f;
      vec3 size = vec3(box_size, height, box_size);
      
      scene.AddBox(pos, size, "ground");
    }
  }
  
  CreateNewMaterial("earth");
  CreateNewTexture("earth_texture", std::string("images/earthmap.jpg"));
  GetMaterial("earth")->SetDiffuse(std::string("earth_texture"));
  scene.AddSphere(vec3(400, 200, 400), 100, "earth");
  
  CreateNewMaterial("metal_white");
  GetMaterial("metal_white")->SetDiffuse(vec3(0.8f, 0.8f, 0.9f));
  GetMaterial("metal_white")->SetMetallic(1.0f);
  scene.AddSphere(vec3(0.0f, 150.0f, 145.0f), 50, "metal_white");
  
  CreateNewMaterial("metal_blue");
  GetMaterial("metal_blue")->SetDiffuse(vec3(0.2f, 0.4f, 0.9f));
  GetMaterial("metal_blue")->SetMetallic(1.0f);
  GetMaterial("metal_blue")->SetRoughness(0.05f);
  scene.AddSphere(vec3(360.0f, 150.0f, 145.0f), 70, "metal_blue");
  
  CreateNewMaterial("glass");
  GetMaterial("glass")->SetIOR(1.5f);
  GetMaterial("glass")->SetOpacity(0.0f);
  scene.AddSphere(vec3(260, 150.0f, 45.0f), 50, "glass");
  
  CreateNewMaterial("light");
  GetMaterial("light")->SetEmissionColor(vec3(1.0f));
  GetMaterial("light")->SetEmissionIntensity(7);
  
  scene.AddQuad(vec3(273,554,279.5), vec3(300,0,0), vec3(0,0,265), "light");
  
  return scene;
}

int main(int argc, const char * argv[]) {
  
  Scene scene = CornellBox();
  //  Scene scene = ExampleScene();
  
  
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

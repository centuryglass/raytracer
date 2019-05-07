
add_library (ablib
 Scene.h Scene.cpp
 Basis.h Basis.cpp 
 HitStruct.h HitStruct.cpp 
 XMLContainerClass.h XMLContainerClass.cpp
 Matrix4x4.h Matrix4x4.cpp
 Ray.h 
 Light.h AreaLight.h AreaLight.cpp
LightMap.h LightMap.cpp
 
 Camera.h Camera.cpp 
 cameras/PerspectiveCamera.h cameras/PerspectiveCamera.cpp 
 cameras/OrthographicCamera.h cameras/OrthographicCamera.cpp  
cameras/SphereCamera.h cameras/SphereCamera.cpp 

Shape.h Shape.cpp BoundingBox.h BoundingBox.cpp
 shapes/Sphere.h  shapes/Sphere.cpp
  shapes/Triangle.h  shapes/Triangle.cpp 
  shapes/Box.h  shapes/Box.cpp 
shapes/InstancedObject.h shapes/InstancedObject.cpp 
shapes/Mesh.h shapes/Mesh.cpp
shapes/ShapeContainer.h shapes/ShapeContainer.cpp
 
Shader.h Shader.cpp
 shaders/FlatShader.h
 shaders/NormalMapShader.h shaders/NormalMapShader.cpp 
 shaders/LambertianShader.h shaders/LambertianShader.cpp 
 shaders/PhongShader.h shaders/PhongShader.cpp 
 shaders/BlinnPhongShader.h shaders/BlinnPhongShader.cpp
shaders/DielectricShader.h shaders/DielectricShader.cpp 
shaders/PortalShader.h shaders/PortalShader.cpp
shaders/MultiReflectionShader.h shaders/MultiReflectionShader.cpp
shaders/CombinationShader.h shaders/CombinationShader.cpp
 
TextureMap.h 
 textures/FlatTexture.h 
  textures/ImageTexture.h  textures/ImageTexture.cpp
textures/PerlinNoiseTexture.h textures/PerlinNoiseTexture.cpp
textures/MarbleTexture.h textures/MarbleTexture.cpp
textures/TextureCalculator.h textures/TextureCalculator.cpp


nanoflann.hpp)
target_link_libraries(ablib sive-rtutil)

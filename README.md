# RayTracer Project
This project uses xml scene files to render images using a variety of ray tracing techniques. Originally created for CS5721 Computer Graphics in spring 2013.



This was the first major coding project I ever really got invested in. If it wasn't for this project, it's entirely possible I wouldn't have become a software developer. It's about as rough as you'd expect for an old student project, but I'm still pretty fond of some of the results this project produced.

#### Building the project:
```
cmake .
make
```
### Ray Traced Image Examples
![Spheres 1K](./examples/spheres_1K.png?raw=true "Spheres 1K")
 * A fairly standard ray tracer test, one thousand spheres, some with reflections.

![metallic dragons](./examples/metallicDragons.png?raw=true "Metallic Dragons")
 * Basic 3D model rendering using the [Stanford dragon](https://en.wikipedia.org/wiki/Stanford_dragon).

![amethyst](./examples/amethyst.png?raw=true "amethyst")
 * An example of the multi-reflection shader, originally created due to a bug in reflection handling.

![amethystDielectric](./examples/amethystDielectric.png?raw=true "amethyst dielectric")

![Dielectric Multi-reflection](./examples/dielectricmultireflection.png?raw=true "dielectric multi-reflection")
 * Combining multi-reflection with dielectric shaders.

![dielectric portal](./examples/dielectricportal.png?raw=true "dielectric portal")
 * Combining dielectric shaders with the portal shader, which transports rays between two arbitrary locations.


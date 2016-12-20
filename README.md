Ray_Tracer
=============
A simple ray tracer using Phong's BRDF and no extra libraries.

Characteristics
------------
The binary `ray_trace` is used as a showcase of some hardcoded scenes. It can handle the following 3D shapes:

* Spheres
* Planes
* Rectangles
* Triangles
* Boxes
* Triangle meshes (loaded from a cutdown version of .obj files)
* Menger Sponges (just for fun)

It can render Lambertian, mirror and refractive surfaces.

As of `v 1.0` there is no support for bitmap textures but to give scenes some artistic sense you can use checker board patterns of any colors and use some experimental features that mess around with surface normals.

Compilation
-------------
To use the basic binary included to render some samples just run from the project directory:

```
mkdir build
cd build
cmake ..
make
```

Usage
-------------
Usage for the binary is as follows.
```
$ ray_trace -h
Usage: ray_trace [OPTION]...
If no options are specified, a default Cornell box with 64 indirect rays will be rendered and saved as cornell.ppm.

Some images will not look good by default, in such cases use --gamma, to use a gamma correction of 2.2, or --clamp to limit color values to the maximum.

Available options:
	-h : Print this helpful text.
	--res <WIDTHxHEIGHT> : Select a different resolution for the result image.
	--indirect_steps <NUMBER> : Choose the number of indirect lighting steps to render images faster. 0 to disable indirect lighting.
	--indirect_rays <NUMBER> : Sets the number of indirect rays that will be used to render the image.
	--clamp : Instead of dividing by the greatest color value in the image, all colors will be clamped.
	--gamma : Instead of dividing by the greatest color value in the image, all colors will be gamma corrected and then clamped.
	-s [SCENE_NAME] : Selects the scene to render.

Available scenes:
	chess_texture
	cornell
	diamond_sphere
	direct_vs_indirect
	dragon
	experimental
	glass_sphere
	glass_sphere_2
	indirect
	infinite_mirror
	menger_1
	menger_2
	menger_3
	menger_4
	menger_5
	phong_spheres
	quartz_sphere
	room
	specular_lobe_1
	specular_lobe_2
	specular_lobe_3
	spheres
	teapot
	water_sphere

```

About
-------------
This is the first project of a computer graphics course. As such, it could be used in similar environments which is why this project will be private until and if permission by the faculty is granted.

Authors
-------------
This project is made by Santiago Gil Begué and Miguel Jorge Galindo Ramos.

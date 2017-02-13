render_engine
=============
A simple ray tracer and photon mapper that uses Phong's BRDF together with reflectant and refracting materials render 3D scenes using pure C++ without the need for extra libraries.

Characteristics
------------
The binary `render` is used as a showcase of some hardcoded scenes. It can handle the following 3D shapes:

* Spheres
* Planes
* Rectangles
* Triangles
* Boxes
* Triangle meshes (loaded from a cutdown version of .obj files)
* Menger Sponges (just for fun)

It can render Lambertian, mirror and refractive surfaces.

As of `v 1.0` there is no support for bitmap textures but to give scenes some artistic sense you can use checker board patterns of any colors and use some experimental features that mess around with surface normals.

Added in this version, you can use tiled textures in .ppm format for axis aligned planes.

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
The example binary works as follows:
```
$ render -h
Usage: render [OPTION]...
If no options are specified, a default Cornell box with 100000 emitted photons and 500 nearest neighbours will be rendered and saved as cornell.ppm.

The resulting images are clamped by default. If they don't look quite right try --noclamp to divide all colors by the maximum or --gamma to use a 2.2 gamma correction.

Available options:
	-h : Print this helpful text.
	--res <WIDTHxHEIGHT> : Select a different resolution for the result image.
	--clamp : Instead of dividing by the greatest color value in the image, all colors will be clamped.
	--gamma : Instead of dividing by the greatest color value in the image, all colors will be gamma corrected and then clamped.
	-p <INTEGER> : Emits INTEGER photons. The default value is 100,000.
	-k <INTEGER> : When tracing rays search for the INTEGER nearest photons. The default value is 300.
	-s [SCENE_NAME] : Selects the scene to render.

Available scenes:
	caustic
	chess_texture
	cornell
	cornell_media
	diamond_sphere
	direct_vs_indirect
	dragon
	experimental
	glass_sphere
	glass_sphere_2
	indirect
	infinite_mirror
	media_0
	media_1
	media_caustic
	menger_1
	menger_2
	menger_3
	menger_4
	menger_5
	mirror_caustic
	phong_spheres
	quartz_sphere
	rat_in_glass
	room
	specular_lobe_1
	specular_lobe_2
	specular_lobe_3
	spheres
	teapot
	water_sphere
```

Images!!
-------------
These are some of the results achieved using the example code.

![Cornell Box](https://mjgalindo.github.io/caustic.png)

![Rat in Cube](https://mjgalindo.github.io/rat_in_cube.png)

![Weird Room](https://mjgalindo.github.io/scaled_room.png)

![Menger Sponge 5 iterations](https://mjgalindo.github.io/menger_5_ind.png)

About
-------------
This is the second project of a computer graphics course. As such, it could be used in similar environments. It's unlikely that this project will be mantained or improved in any way but it should remain as a way to satisfy some curious mind out there.

If you're using this repository as a reference for a class project keep in mind not to copy anything directly, teachers know about GitHub :wink:.

Authors
-------------
This project was made by Santiago Gil Begué and Miguel Jorge Galindo Ramos.

###### [Apache 2.0 license](https://github.com/Santi-7/UNIZAR-30226-2016-01/blob/master/LICENSE). If you use this code or parts of it, please name us.

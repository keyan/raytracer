# raytracer

Ray tracer, supports rendering diffuse and reflective spheres.

![Example output](https://user-images.githubusercontent.com/6401746/48807144-7e889380-ecd1-11e8-9e2c-18eec89b3412.jpg)

## Overview

Implemented through following [Peter Shirley's great book](https://www.amazon.com/dp/B01B5AODD8). It is now free online too, but I'm linking to the ebook because it is a great resource and you should support him if you can.

That book is helpful, but to really understand the methods being used additional references were required, namely:
- http://www.scratchapixel.com, specifically their [ray tracing introduction](http://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing)
- Andrew Kensler's famous [business card ray tracer analysis](http://eastfarthing.com/blog/2016-01-12-card/)
- And Fabien Sanglard's [analysis of the same code](http://fabiensanglard.net/rayTracing_back_of_business_card/)
- Occasional cross referencing with [Fundamentals of Computer Graphics](https://www.amazon.com/Fundamentals-Computer-Graphics-Peter-Shirley/dp/1568814690), also by Peter Shirley

There is a tendency in graphics code to use lots of magic numbers, single character variable names, and assume understanding of some geometric calculations, so I tried to add lots of comments to explain those sorts of cases.

## Usage

Requires C++11 compatible compiler, running: `make` will generate the example image in this README.

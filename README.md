# Teaching Myself OpenGL

## Prerequisites

```
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

## 1

```
gcc 1.c -o 1glut -lGLU -lGL
./1
```

The vertex positions are this:


```
     (-1,1)        (0,1)        (1,1)
        +------------+------------+
        |            |            |
        |            | (0,0)      |
        |            |/           |
 (-1,0) +------------+------------+ (1,0)
        |            |            |
        |            |            |
        |            |            |
        +------------+------------+
     (-1,-1)       (0,-1)       (1,-1)
```

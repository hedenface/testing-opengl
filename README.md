# Teaching Myself OpenGL

## Prerequisites

```
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

## 1

```
gcc 1.c -o 1 -lglut -lGLU -lGL
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

## 2

```
gcc 2.c -o 2 -lglut -lGLU -lGL
./2
```

The bitmap is made up of the following array of (24) bytes:

```                                                                                      1
0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xff, 0xc0, 0xff, 0xc0
```

This makes up:

```
11000000 00000000 11000000 00000000 11000000 00000000 11000000 00000000 11000000 00000000 11111111 00000000 11111111 00000000 11000000 00000000 11000000 00000000 11000000 00000000 11111111 11000000 11111111 11000000
```

This looks better like this:

```
xx              xx              xx              xx              xx              xxxxxxxx        xxxxxxxx        xx              xx              xx              xxxxxxxxxx      xxxxxxxxxx      
```

At first glance, you'd think that this would be written from upper left corner. But it isn't. It starts at the origin, which is 0,0, which is the lower left corner. So if we put this together starting there, moving right (2 bytes at a time), and up, we're given the following:

```
1111111111000000     xxxxxxxxxx      
1111111111000000     xxxxxxxxxx      
1100000000000000     xx              
1100000000000000     xx              
1100000000000000     xx              
1111111100000000 --> xxxxxxxx        
1111111100000000     xxxxxxxx        
1100000000000000     xx              
1100000000000000     xx              
1100000000000000     xx              
1100000000000000     xx              
1100000000000000     xx              
```

`glBitmap()` arguments are as follows: 1st pair is the width and height of the bitmap, second is the location of the bitmap origin relative to the lower left corner of the bitmap image, the third specifies x and y offsets to be added to the current raster position after the bitmap has been drawn, and the final argument is a pointer to the bitmap image itself.

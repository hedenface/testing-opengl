# Teaching Myself OpenGL

## Prerequisites

```
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev libpng-dev
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

## 3

Nothing very special here. Just expanding on `2` a bit.

```
gcc 3.c -o 3 -lglut -lGLU -lGL
./3
```

## 4

Now we're getting somewhere. We pass an argument in to the application which is the file path of a bitmap image. This then loads that image, and displays it.

```
gcc 4.c -o 4 -lglut -lGLU -lGL
./4 squares.bmp
```

Some notes: this only works on 24-bit bitmaps. We expect a byte per color, so 3 colors * 1 byte = 24 bits. Duh

## 5

Well, what happens when we want transparency? We could mark bits of a certain color as transparent in a 24-bit bitmap, but that seems like a bunch of work. Now we utilize the libpng we installed as a prerequisite, and load a png in a similar fashion to `./4`

```
gcc 5.c -g -o 5 -lglut -lGLU -lGL -lpng
./5 sprite.png
./5 testing1.png
```

## 6

This is a VERY BASIC program to move a sprite around on top of a bg image. To be honest, I hobbled this together from many different sources, and only guessed mostly at what needed to be done until I came to this exact rendition.

```
gcc 6.c -g -o 6 -lglut -lGLU -lGL -lpng
./6 testing1.png sprite.png
```

Then use the arrow keys to move the sprite around ..until the memory in your PC runs out for some reason and everything gets `kill -9`'d.

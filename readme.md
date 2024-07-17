# Rubix Cube 2000

Rubik's cube simulator written in C. 

To build:

```
make
```

To run:

```
./build/rubix
```

To play:

```
USAGE: 
q        quit
?        help
!        debug mode
c        reset cube
s        scramble cube
turn cube clockwise (counter-clockwise):
u (u')   turn up face
l (l')   turn left face
r (r')   turn right face
f (f')   turn front face
b (b')   turn back face
d (d')   turn down face
```

To run head-less::

```
$ echo "l'd'u'" | ./build/rubix -s "udl"
300400100412412412033022011444333222115445335355255155 0
000000000111111111222222222333333333444444444555555555 1
```

## Screenshot

![Screenshot of Rubix Game](screenshot.png)

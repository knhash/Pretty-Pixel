#!/bin/bash
if [ $# -eq 0 ]
  then
    echo "Running PrettyPixel"
    g++ PrettyPixel.cpp Pictures.h -o PrettyPixel -lGL -lGLU -lglut && ./PrettyPixel
fi
if [ $# -eq 1 ]
  then
    echo "Running Draw"
    g++ Draw.cpp -o Draw -lGL -lGLU -lglut && ./Draw $1
fi

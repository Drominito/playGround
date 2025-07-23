#!/bin/bash
FILE="new.bmp"
i=0
x=100
y=100

gcc -O2 -o main main.c -lm || exit 1

while true; do
  ./main "$i" "$x" "$y"
  ((i=i+1))  # kleinerer Schritt für mehr FPS

  # Kein convert, kein scaling → spart Zeit
  viu "$FILE"

  #sleep 0.033  # etwa 30 FPS
  sleep 0.031847
done


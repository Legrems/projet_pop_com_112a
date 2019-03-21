#!/bin/bash
time_w=0

for i in {1..9}
do
   ./projet Error "errors/E0$i.txt"
   sleep "$time_w"
done

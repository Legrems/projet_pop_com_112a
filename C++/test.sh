#!/bin/bash
time_w=0

for i in {1..15}
do
	echo $i
	if [ $i -gt 9 ]
	then
   		./projet Error "errors/E$i.txt"
   	else
   		./projet Error "errors/E0$i.txt"
   	fi
   	sleep "$time_w"
done

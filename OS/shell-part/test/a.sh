#!/bin/bash


a="robi,bobi,dobi"

(IFS=","
for var in $a;do
	echo $var
done
)

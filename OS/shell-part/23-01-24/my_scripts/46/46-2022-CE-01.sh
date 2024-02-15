#!/bin/bash


if [[ $# -ne 3 ]];then
	echo "Wrong usage!Usage <number> <prefix> <unit>"
	exit 1
fi
if ! [[ "$1" =~ ^[0-9]+\.[0-9]+$ ]];then
	echo "First argument should be a number"
	exit 1
fi
bs="./base.csv"
pfx="./prefix.csv"

number="${1}"
prefix="${2}"
unit="${3}"

name_measure="$(cat "${bs}" | egrep ",${unit}," | cut -d ',' -f 1,3)"
multi="$(cat "${pfx}" | egrep ",${prefix}," | cut -d ',' -f 3)"
name="$(echo "${name_measure}" | cut -d ',' -f 1)"
measure="$(echo "${name_measure}" | cut -d ',' -f 2)"
result="$(echo "scale=2; ${number} * ${multi}" | bc)"


echo "${result} ${3} (${name}, ${measure})"
exit 0

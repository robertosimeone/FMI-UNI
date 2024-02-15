#!/bin/bash

if [[ $# -ne 3  ]];then
	echo "Incorrect number of arguments!"
	exit 1
fi

if ! [[ -f "${1}" ]] ||  [[ -f "${2}" ]] || ! [[ -d "${3}" ]]; then
	echo "Wrong usage!"
	exit 2
fi
directory="${3}"

while read -d $'\0' filename; do
	regex="^{ [[:alnum:]-]+;? };$"
	cat "${filename}" | cut -d '#' -f 1 | grep -Evn "${regex}" | awk -v fname="${filename}" ' BEGIN { print fname } { printf("Line %d: %s", $1, $2) }'


	if [ "$(cat "${filename}" | cut -d '#' -f 1 | grep -Evn "${regex}")" = "" ]; then

		# FILE IS VALID
		cat $filename >> $2

		UNAME=$(echo "${filename}" | sed -E 's/^(.*)\.cfg$/\1/')
		# ... grepim v $1 s $UNAME
	
		echo $UNAME
		PASS=$(pwgen 16 1)
		echo $PASS

		echo "${UNAME}:$(md5sum $PASS)" >> $1
	fi

done < <(find "${directory}" -type f -name "*.cfg" -print0)


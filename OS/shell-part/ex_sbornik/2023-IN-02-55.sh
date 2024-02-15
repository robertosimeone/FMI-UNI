#!/bin/bash
if [[ ${#} -ne 1 ]]; then
	echo "Wrong usage! Usage ${0} <directory>"
	exit  1
fi
if ! [[ -d "${1}" ]]; then
	echo "No such directory exists!"
	exit 2
fi
search_directory="${1}"

while read -d $'\0' filename;do
	
done < <(find "${search_directory}" -type f -print0)

#!/bin/bash

if [[ "${#}" -ne 2 ]];then
	echo "Wrong usage!Usage <directory> <number>"
	exit 1
fi

if ! [[ -d "${1}" ]];then
	echo "The directory either doesnt exist or is not a directory"
	exit 1
fi

if [[ "${2}" -gt 99 ]] || [[ "${2}" -lt 1 ]];then
	echo "Wrong usage!The number should be between 1 and 99"
	exit 1
fi
dir="$1"
allowed_space="${2}"
function current_used_space {
	local used_space="$(df "${1}" | tail -n +2 | tr -s ' ' | cut -d ' ' -f 5 | rev | cut -c 2- | rev)"
	echo "${used_space}"
}
if [[ "$(current_used_space "${dir}")" -le "$allowed_space"]];then
	exit 0
fi
while read dirname;do
	while read -d $'\0' ddfilename;do
		if [[ "$(current_used_space "${dir}")" -le "$allowed_space"]];then
			break
		fi
		unique_files="$(find "$dirname" -type f | sed -E 's/-[0-9]+\.tar\.xz//g' | sort | uniq -c )"
	done < <(find "${dirname}" -type f -print0 | sed 's/\.tar\.xz//g' | sort -zn -t '-' -k 3 )
done < <(find "${dir}" -mindepth 1 -type d -print0 | sort -zn)

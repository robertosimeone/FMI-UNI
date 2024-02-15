#!/bin/bash


if [[ "${#}" -ne 2 ]];then
	echo "Wrong usage!Usage <directory> <directory>"
	exit 1
fi

if ! [[ -d "${1}" ]] || ! [[ -d "${2}" ]];then
	echo "The directories either don't exist or are not directories"
	exit 2
fi

if [[ "$(find "${2}" -mindepth 1 | wc -l)" -ne 0 ]];then
	echo "The second passed positional directory should be empty!"
	exit 3
fi

fromdir="${1}"
todir="${2}"

while read -d $'\0' filename;do
	if [[ -d "{filename}" ]];then
		cp -r "${filename}" "${todir}"
	else
		cp "${filename}" "${todir}"
	fi
done< <(find "${fromdir}" -mindepth 1 -print0)

while read -d $'\0' filename;do
	dir_name="$(dirname "$filename")"
	base_name="$(basename "$filename")"
	real_file_name="$(echo "${base_name}" | cut -d '.' -f 2)"
	if find "${dir_name}" -mindepth 1 -maxdepth 1 | xargs -I {} basename {} | egrep "^${real_file_name}$";then
		rm "${filename}"
	fi
done< <(find "${todir}" -mindepth 1 -name ".*.swp"  -print0)

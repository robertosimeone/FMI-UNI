#!/bin/bash


if [[ "${#}" -eq 1 ]];then
	echo "Wrong usage!Usage <directory>"
	exit 1
fi

if ! [[ -d "${1}" ]];then
	echo "The directory either doesnt exist or is not a directory"
	exit 1
fi

fuga="${1}"
error_file="$(mktemp)"
config_folder="${fuga}/cfg"
scp="${fuga}/validate.sh"

added_users="$(mktemp)"
auth_file="${fuga}/foo.pwd"


while read -d $'\0' filename;do
	#check if file is valid
	"${scp}" "${filename}" >> "${error_file}"
	cat "$error_file" | sed "s/(^Line.*)/${filename}:\1/g"
	if [[ "${?}" -eq 0 ]];then
		username="$(echo "$filename" | sed -E 's/\..*//g')"
		if ! grep "${username}" "${auth_file}";then
			password="$(pwgen 12 1)"
			hashed_pw="$(mkpasswd "${password}")"
			echo "${username}:${hashed_passwd}" >> "${auth_file}"
			echo "${username}:${password}" >> "${added_users}"
		fi
		cat "$filename" >> "${fuga}/foo.conf"	
	fi
done < <(find "${config_folder}" -mindepth 1 -type f -print0)

cat "$error_file" >&2
cat "${added_users}"

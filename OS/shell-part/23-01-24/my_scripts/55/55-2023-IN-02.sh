#/bin/bash

#-------------------------
#Task with lab measurements
#-------------------------


if [[ ${#} -ne 1 ]];then
	echo "Wrong usage!Usage <directory>."
	exit 1
fi
if [[ ! -d "${1}" ]];then
	echo "The given parameter is not a directory or it doesnt exist"
	exit 1
fi
dirname="${1}"
storedir="/tmp/HASHES"
mkdir "${storedir}" 

#MD5SUMSFILE=$(mktemp)

while read -d $'\0' filename;do
	current_md5sum="$(md5sum "${filename}" | cut -d ' ' -f 1)"
	stat -c '%i %n' ${filename} >> "${storedir}"/"${current_md5sum}"
done < <(find "${dirname}" -type f -print0)


while read -d $'\0' filename;do
	lines="$(cat "${filename}" | wc -l)"
	unique_values="$(cat "${filename}" | cut -d ' ' -f 1 | sort -n | unique | wc -l)"
	if [[ "${lines}" -eq 1 ]];then
		continue
	fi
	#Here we have a group of hardlinks
	if [[ "${unique_values}" -eq 1 ]];then
		cat "${filename}" | head -n 1 | cut -d ' ' -f 2
	#Dealing with all unique files
	elif [[ "${unique_values}" -eq "${lines}" ]];then
		cat "${filename}" | head -n -1 | cut -d ' ' -f 2
	#Dealing with a combination of both
	else
		cat "${filename}" | sort -n -t ' ' -k 1,2 | awk 'BEGIN{last_inode=-1;last_filename=""} last_inode == -1{last_inode = $1;last_filename=$2;next} last_inode != $1{last_inode = $1;last_filename=$2;print last_filename} END{print last_filename}'
	fi

done < <(find "${storedir}" -type f -print0)

rm -rf "${storedir}"


exit 0

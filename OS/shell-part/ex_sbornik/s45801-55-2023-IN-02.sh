#!/bin/bash

if [ $# -ne 1 ];then
	echo "ERROR:Wrong num of args"
	exit
fi

FHS=$(find "${1}" -mindepth 1 -maxdepth 1 -type f -exec sha256sum {} \;)
SORTEDHS=$(echo "${FHS}" | cut -d ' ' -f 1 | sort | uniq)

while read HASH;do

	CURFILES=$(echo "${FHS}" | grep "${HASH}" | sed -E "s/^[[:alnum:]]+ *//")
	FLSIND=""

	while read FILE;do
		CUR=$(stat "${FILE}" --printf "%n %i")
		TMP=$(echo -e "${FLSIND}\n${CUR}")
		FLSIND=$TMP
	done < <(echo "${CURFILES}")

	INODES=$(echo "${FLSIND}" | tail -n +2 | cut -d ' ' -f 2 | sort)
	UNIQINODES=$(echo "${INODES}" | uniq)
	INODESCOUNT=$(echo "${INODES}" | wc -l)
	INDLINES=$(echo "${UNIQINODES}" | wc -l)

	if [ ${INODESCOUNT} -gt 1 ];then

		if [ ${INODESCOUNT} -eq ${INDLINES} ];then
			echo "${CURFILES}" | head -n -1
		else
			for INODE in $(echo "${UNIQINODES}");do
				echo "${FLSIND}" | grep "${INODE}" | cut -d ' ' -f 1 | head -n 1
			done
		fi

	fi

done < <(echo "${SORTEDHS}")





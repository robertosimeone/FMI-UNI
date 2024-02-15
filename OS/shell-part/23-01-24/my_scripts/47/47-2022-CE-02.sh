#!/bin/bash

if [[ "${1}" -ne 1 ]];then
	echo "Wrong usage!Usage <device>"
	exit 1
fi

if [[ "$(echo "${1}" | wc -c)" -ge 5 ]];then
	echo "The device name should consist of at most 4 symbols"
	exit 1
fi

info_file="/proc/acpi/wakeup"
device="${1}"
if ! cat "${info_file}" | egrep -q "^${device}[ \t]+.*";then
	echo "No such device here"
	exit 1
else
	if cat "${info_file}" | egrep -q "^${device}[ \t]+.*$" | egrep -q "^.*[\t ]+\*enabled[\t ]+.*$";then
		echo "${device}" > "${info_file}"
	fi
fi

exit 0

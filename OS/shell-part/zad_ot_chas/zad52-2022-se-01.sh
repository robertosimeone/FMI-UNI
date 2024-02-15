#!/bin/bash

if [ $# -ne 1 ]; then
	echo "ERROR must be one arg"
	exit
fi

if ! [ -f "${1}" ]; then
	echo "ERROR not a file"
	exit
fi

while read DEVICE STATE ; do
	if ! grep -q $DEVICE /proc/acpi/wakeup ; then
		echo "WARN: $DEVICE not in wakeup" >&2
		continue
	fi

	CURRSTATE=$(grep $DEVICE /proc/acpi/wakeup | sed -E "s/^.*\*(.*) .*$/\1/")

	if [ "${CURRSTATE}" != "${STATE}" ]; then
		echo "${DEVICE}" > /proc/acpi/wakeup
	fi
done < <(cat $1 | cut -d'#' -f 1 | grep -v "^ *$")



#!/bin/bash

if [[ "${#}" -ge 2 ]];then
	echo "Wrong usage! The script takes 0 or 1 arguments!"
	exit 1
fi

if [[ "$(whoami)" != "root" ]];then
	echo "Only root has rights to execute this script!"
	exit 2
fi

if [[ ${1} == "autoconfig" ]];then
	echo "yes"
	exit 0
fi

if [[ -n "${CTRLSLOTS}" ]];then
	for slotN in "${CTRLSLOTS}";do
		slot_info="$(ssacli ctrl slot=${slotN} pd all show details)"

		
	done
else

fi
# tazi q napravihme v chas princip ama moje ako ostane vreme da q naprawq otnowo

#!/bin/bash
	if [[ $# -ne 1 ]];then
		echo "Wrong usage!"
		exit 1

	fi
	if ! [[ -f "$1" ]]; then
		echo "No such file exists or it's not a normal file"
		exit 2
	fi
settings="${1}"
#twa tuka otdolu maha vsichki tabove speisove i tn
while read DEVICE STATE; do
	if ! grep -q  $DEVICE /proc/acpi/wakeup ; then
		echo "WARN: $DEVICE not in wakeup" >&2 #ne tr da ima interval inache zapiswa wuw file &2
	continue
	fi

	CURRSTATE = $(grep $DEVICE /proc/acpi/wakeup | sed -E "s/^.*\*(.*) .*$/\1/g"
	if [[ "$CURRSTATE" 1= "$STATE"  ]]; then
		echo "$DEVICE" > /proc/acpi/wakeup
	fi
done < <(cat "$1" | cut -d '#' -f 1 | grep -v "^$") # tuk po dobre e mai "^ $"


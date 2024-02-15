#!/bin/bash
folder="${1}"

output="$("${folder}/test.sh" $2)"
echo "exit status is : ${?}"
echo $output

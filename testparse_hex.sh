#!/bin/bash

if [ $# -eq 1 ]
then
	$0 < $1
	exit $?
fi

sed -e 's/.*:  //' -e 's/  .*//' | xxd -r -ps | ./testparse

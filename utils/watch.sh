#!/bin/bash

if [ "$1" == "" ]
then
	TARGET=qemu_compile
else
	TARGET=$1
fi

if pwd | grep 'utils$'
then
	cd ..
fi

LASTMOD=0
CHILDPID=0
while true
do
	THISMOD=$(stat -c %Y BoneOS.iso)

	if [ $LASTMOD -ne $THISMOD ]
	then
		LASTMOD=$THISMOD

		if [ $CHILDPID -ne 0 ]
		then
			kill $CHILDPID
		fi

		nice -n 19 make $TARGET &
		CHILDPID=$!
	else
		make 1>/dev/null
	fi

	sleep 1
done

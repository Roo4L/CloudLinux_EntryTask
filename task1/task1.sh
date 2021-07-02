#!/bin/bash
flags=""

while getopts "iLfn" flag
do
	# all flags were chosen according to "cp" command flags
	case ${flag} in
		i) flags+="-i ";;
		L) flags+="-L ";;
		f) flags+="-f ";;
		n) flags+="-n ";;
	esac
done
		
		
for File in $(find -name '*.c')
do
	cp ${flags} $File "${File}.orig"
done




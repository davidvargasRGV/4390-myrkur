#!/bin/bash

for i in $(seq 1 $1)
do
	./doc/create_user.sh $i
done

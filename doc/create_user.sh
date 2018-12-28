#!/bin/bash

let port=10100+$1

# create microdc2 downloaddir

if [ ! -d "/home/dvargas/.microdc2/downloaddir/$1" ]; then
	mkdir "/home/dvargas/.microdc2/downloaddir/$1"
fi

# create microdc2 sharedir

if [ ! -d "/home/dvargas/.microdc2/sharedir/$1" ]; then
	mkdir "/home/dvargas/.microdc2/sharedir/$1"
fi

# create microdc2 config

MCFG="/home/dvargas/.microdc2/config-$1"

echo "set sharedir /home/dvargas/.microdc2/sharedir/$1" > "$MCFG"

echo "set downloaddir /home/dvargas/.microdc2/downloaddir/$1" >> "$MCFG"

echo "set nick user$1" >> "$MCFG"

echo "set listenport $port" >> "$MCFG"

echo "connect 127.0.0.1:5000" >> "$MCFG"


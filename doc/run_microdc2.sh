#!/bin/bash

for i in $(seq 1 $1)
do
screen -dmS microdc2$i microdc2 --config=/home/dvargas/.microdc2/config-$i &
done

#screen -dmS microdc2a microdc2 --config=/home/dvargas/.microdc2/config-a &
#screen -dmS microdc2b microdc2 --config=/home/dvargas/.microdc2/config-b &
#screen -dmS microdc2c microdc2 --config=/home/dvargas/.microdc2/config-c &
#screen -dmS microdc2d microdc2 --config=/home/dvargas/.microdc2/config-d &
#screen -dmS microdc2e microdc2 --config=/home/dvargas/.microdc2/config-e &
#screen -dmS microdc2f microdc2 --config=/home/dvargas/.microdc2/config-f &
#screen -dmS microdc2g microdc2 --config=/home/dvargas/.microdc2/config-g &

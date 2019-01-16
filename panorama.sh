#!/bin/bash

cropped_image_dir=syc
image_dir=examples

n=0
for picture in "$image_dir"/*.bmp
do
    image[ $n ]="$picture"
    (( n++ ))
done
image[ $n ]=${image[ 0 ]}

i=0
while [ $i -lt $n ]
do
    echo ${image[ $i ]}
    ./program "-e" ${image[ $i ]}
    (( i++ ))
done

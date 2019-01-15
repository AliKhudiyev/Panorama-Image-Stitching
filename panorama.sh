#!/bin/bash

cropped_image_dir=examples

n=0
for picture in "$cropped_image_dir"/*.bmp
do
    image[ $n ]="$picture"
    (( n++ ))
done

i=0
while [ $i -lt $n ]
do
    echo ${image[ $i ]} ${image[ $i+1 ]}
    (( i++ ))
done

# ./crop.sh [folder_name]
# ...
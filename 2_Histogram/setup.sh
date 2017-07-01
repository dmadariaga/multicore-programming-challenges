#!/usr/bin/env bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
TARGET_FOLDER="${DIR}/sdsl-local-install"


TO_COMPILE="${DIR}/LZ/"
echo "Compiling..."
make
mkdir images
echo "Creating test images in /image..."
for IMAGE_SIZE in 1024 2048 4096 8192 # Reference size
do
    ./random_rgb ${IMAGE_SIZE} ${IMAGE_SIZE} images/${IMAGE_SIZE}.ppm
    echo "Created ${IMAGE_SIZE}.ppm with ${IMAGE_SIZE}X${IMAGE_SIZE} pixels"
done
echo "Done"


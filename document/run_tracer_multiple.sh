#!/bin/bash

EXECUTABLE=./ray_tracer
SCENES=(simple_room 
simple_room_bunny
complex_room_bunny
room_teapot
room_material_balls
room_normal_map
room_volume
room_bot
room_cube
room_cornell)

for SCENE in "${SCENES[@]}"; do
    echo "scene: $SCENE"
    "$EXECUTABLE" "$SCENE"
    if [ $? -ne 0 ]; then
        echo "scene: $SCENE failed"
        exit 1
    fi
    echo "scene $SCENE done"
done

echo "all scenes done"
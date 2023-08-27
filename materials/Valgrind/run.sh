#!/bin/bash

cd ../../
docker rmi -f geniezan/valgrind/smart_calc
docker build . -t geniezan/valgrind/smart_calc -f materials/Valgrind/Dockerfile
docker run --rm geniezan/valgrind/smart_calc

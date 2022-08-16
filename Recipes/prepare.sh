#!/bin/bash

echo "Preparing the 'Commons' library for the installation" && \
  git submodule init && git submodule update && \
  echo "The 'Commons' library is prepared for the installation"
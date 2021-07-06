#!/usr/bin/env bash

# 1. Generate graph
circo -Tsvg ./states.gv -o states.svg &&

# 2. Optimize SVG
svgo states.svg

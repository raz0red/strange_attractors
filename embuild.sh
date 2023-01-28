#!/bin/bash
em++ main.cpp -O3 -sLEGACY_GL_EMULATION -sUSE_GLFW=3 -sGL_UNSAFE_OPTS=0 \
    -sMODULARIZE=1 -sEXPORT_NAME="'sattract'" -sEXIT_RUNTIME=0 -s EXPORTED_RUNTIME_METHODS="['cwrap']" \
    -sEXPORTED_FUNCTIONS="['_main', '_main_loop', '_setWindowSize']" \ -sINVOKE_RUN=0 \
    -o sattract.js
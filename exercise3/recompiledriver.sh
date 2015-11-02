#! /bin/bash

ptxdist clean driver-gamepad
ptxdist compile driver-gamepad
ptxdist targetinstall driver-gamepad
ptxdist image root.romfs
ptxdist test flash-rootfs

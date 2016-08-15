#!/usr/local/bin/bash

if [ -n "$BASH_VERSION" ]; then
	if [ -f "$HOME/.bashrc" ]; then
		. "$HOME/.bashrc"
	fi
fi

# start X at login
# [[ -z $DISPLAY && $XDG_VTNR -eq 1 ]] && exec xinit
[[ $(tty) = "/dev/tty1" ]] && exec xinit

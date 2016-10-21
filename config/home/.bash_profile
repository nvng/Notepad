#!/usr/local/bin/bash

if [ -n "$BASH_VERSION" ]; then
	if [ -f "$HOME/.bashrc" ]; then
		. "$HOME/.bashrc"
	fi
fi

if [ -f ~/.git-completion.bash ]; then
        . ~/.git-completion.bash
fi

# start X at login
# [[ -z $DISPLAY && $XDG_VTNR -eq 1 ]] && exec xinit
[[ $(tty) = "/dev/tty1" ]] && exec xinit

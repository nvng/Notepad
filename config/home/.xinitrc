#!/bin/bash
export LC_CTYPE=zh_CN.UTF-8
export XMODIFIERS=@im=SCIM
export XIM=SCIM
export XIM_PROGRAM=scim
export GTK_IM_MODULE=scim
export QT_IM_MODULE=scim

urxvtd &
scim -d &
rdm &
# feh --bg-scale ~/.wallPaper &

exec /usr/local/bin/dwm

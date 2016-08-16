#!/bin/bash

alias ls="ls --color=auto"
alias gdb="gdb -q"      # gdb启动时，不显示多余的提示信息。

export EDITOR=/usr/bin/vim
export TERM=linux               # 出现 unknown terminal type
export LC_CTYPE=zh_CN.UTF-8     # 从 xshell 登录中文乱码       

export LESS="-erX" # 解决 git log 显示信息乱

PS1='\e[0;33m[\u@\h \W]\$ \e[0;0m'

# Try to enable the auto-completion.
[ -r /usr/share/bash-completion/bash_completion   ] && . /usr/share/bash-completion/bash_completion

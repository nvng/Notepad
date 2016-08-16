#!/bin/bash

alias ls="ls --color=auto"
alias gdb="gdb -q"      # gdb����ʱ������ʾ�������ʾ��Ϣ��

export EDITOR=/usr/bin/vim
export TERM=linux               # ���� unknown terminal type
export LC_CTYPE=zh_CN.UTF-8     # �� xshell ��¼��������       

export LESS="-erX" # ��� git log ��ʾ��Ϣ��

PS1='\e[0;33m[\u@\h \W]\$ \e[0;0m'

# Try to enable the auto-completion.
[ -r /usr/share/bash-completion/bash_completion   ] && . /usr/share/bash-completion/bash_completion

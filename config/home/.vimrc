set nocompatible

filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'Rip-Rip/clang_complete'
Plugin 'kien/ctrlp.vim'
" Plugin 'tacahiroy/ctrlp-funky'
Plugin 'dkprice/vim-easygrep'
Plugin 'vim-scripts/mru.vim'
" Plugin 'Andersbakken/rtags'   " 使用 clang 生成 tag 进行精确跳转
" Plugin 'rizsotto/Bear'        " 生成 compile_commands.json
Plugin 'lyuts/vim-rtags'        " rtags 在 vim 中的快捷键
Plugin 'vim-scripts/a.vim'
Plugin 'majutsushi/tagbar'      " 比taglist强大好用
" Plugin 'vim-scripts/taglist.vim'
" Plugin 'vim-scripts/autotags' "
Plugin 'vim-scripts/DoxygenToolkit.vim'
" Plugin 'Shougo/neocomplete.vim'
" Plugin 'jiangmiao/auto-pairs'
Plugin 'mbbill/undotree'
" Plugin 'ardagnir/athame'
" Plugin 'vim-scripts/gdbmgr'
" Plugin 'gilligan/vim-lldb'
" Plugin 'xaizek/vim-inccomplete'
" Plugin 'dschwen/switch-header-source'
" Plugin 'po1/vim-pycmake'
Plugin 'davidhalter/jedi-vim'
Plugin 'vimwiki/vimwiki'
Plugin 'plasticboy/vim-markdown'
Plugin 'gerw/vim-latex-suite'
call vundle#end()

syntax enable
" Enable file type detection.
" Use the default filetype settings, so that mail gets 'tw' set to 72,
" 'cindent' is on in C files, etc.
" Also load indent files, to automatically do language-dependent indenting.
filetype plugin indent on

set nowrap
set foldmethod=marker
set expandtab   " use spaces instand of tab.
set showcmd
set wildmenu			" 命令行补全以增强模式运行。

set vb t_vb=			" 取消在命令错误时的响铃。
set scrolloff=1 		" 光标上下两侧最少保留的屏幕行数。
set history=1024		" 最大历史记录条数。
" set tm=500			" 毫秒计的等待键码或者映射的键序列完成的时间。

set cpt-=i " not scan current and included files.
set cpt-=t " do not use tag completion.

set cindent			" C 缩进方式。
set autoread			" 如果文件在 vim 之外修改过而在 vim 里面没有的话，自动重新读入。

set backspace=start,indent	" 使得 <BS> 键不能在换行符上退格。

" for search
set hlsearch
set incsearch
set backupdir=~/.vbk
" set backupext=.lswbak		" 指定备份文件后缀名。
" set patchmode=.orig		" 保存原始版本。

autocmd FileType [ch],cpp,cc setlocal cinoptions=g0,:0,N-s
set path+=/usr/include/c++/v1

if has('gui')
	colorscheme evening
	" set guifont=Inconsolata\ 15
	set guifont=DejaVu\ Sans\ mono\ 12
	" set guifont=simsun\ 12
	set go=
endif

if has('mouse')
	set mouse=c
endif

" 设置状态栏
" set ruler		" Show the line and column number of the cursor position.
" set laststatus=2	" always show the status line
set statusline=\ %f%y%m%r%w\ \[%{&fileformat}\\%{&fileencoding}\]\ %=%-14.(%l/%L,%c%V%)\ %P\

" 使用 <Space> 来打开和关闭折叠
nnoremap <space> @=((foldclosed(line('.')) < 0) ? 'zc' : 'zo')<cr>

" 清空上一次搜索使用的寄存器。
nmap <leader><Space>d :let @/ = ""<cr>

" 删除每行后面多余的空格。
nmap <leader><Space><Space> :%s/\s\+$//ge<cr>

" 把一连串的空行(b)或空白行(n)压缩到一行。
nmap <leader><Space>b   GoZ<Esc>:g/^$/.,/./-j<CR>Gdd
nmap <leader><Space>n   GoZ<Esc>:g/^[ <Tab>]*$/.,/[^ <Tab>]/-j<CR>Gdd

" 对空格和空行进行综合性处理。
nmap <leader><Space> :call ForSpace()<cr>

function! ForSpace()
        exec "normal mz"
        exec "normal \\\<Space>b"
        exec "normal \\\<Space>n"
        exec "normal \\\<Space>\<Space>"
        exec ":retab!"
        exec "normal \\\<Space>d"
        exec "normal `z"
endfunction

" press Alt-Shift-J(or Alt-Shift-K) to jump to the next (or previous) method
" in a C++ file
nnoremap <M-J> /\v^(\w+\s+)?\w+::\w+\(.*\)
nnoremap <M-K> ?\v^(\w+\s+)?\w+::\w+\(.*\)

" for make
" 在执行 make 命令时，写入已经修改的缓冲区。
autocmd FileType [ch],cpp,vim setlocal autowriteall
if filereadable("Makefile") || filereadable("makefile")
	set makeprg=make
else
	" autocmd FileType [ch],cpp set makeprg=clang\ -g\ -Wall\ -o\ %<.out\ %
	autocmd FileType [ch],cpp set makeprg=g++\ -std=c++11\ -g\ -Wall\ -Werror\ -o\ %<.out\ %
endif

" When editing a file, always jump to the last known cursor position.
" Don't do it when the position is invalid or when inside an event handler
" (happens when dropping a file on gvim).
" Also don't do it when the mark is in the first line, that is the default
" position when opening a file.
autocmd BufReadPost *
                        \ if line("'\"") > 1 && line("'\"") <= line("$") |
                        \   exe "normal! g`\"" |
                        \ endif

" Automatically open, but do not go to (if there are errors) the quickfix /
" location list window, or close it when is has become empty.
"
" Note: Must allow nesting of autocmds to enable any customizations for quickfix buffers.
" Note: Normally, :cwindow jumps to the quickfix window if the command opens it
" (but not if it's already open). However, as part of the autocmd, this doesn't seem to happen.
autocmd QuickFixCmdPost [^l]* nested cwindow
autocmd QuickFixCmdPost    l* nested lwindow
" }}}

" taglist
let Tlist_Exit_OnlyWindow = 1
let Tlist_File_Fold_Auto_Close = 1
let Tlist_Enable_Fold_Column = 0
let Tlist_Show_One_File = 1     " 只显示当前文件的 tag
" let Tlist_Use_Right_Window = 1  " 窗口显示在右则
" let Tlist_GainFocus_On_ToggleOpen = 1

" 补全比较
" rtags 自带补全 必须加 -include PCH 才能补全在 PCH 中包含，但在补全文件中没有包含的头文件内容。且该文件必须被包含在一个 cc 文件中。
" clang_complete 使用 compile_commands.json 作为补全命令文件
"       即使加入 -include 也无法补全相应文件。
" clang_complete 使用 .clang_complete 作为补全命令文件
"       只要文件被创建，就可以补全，头文件要么包含在 PCH 中（此时需要加 -include），要么包含在该文件中。
" clang_complete 补全显示也更加清析

" clang_complete
" 无法区分哪些函数能够直接调用，如析构函数。
" 无法区分哪些成员不能调用，如私有成员变量。
let g:clang_close_preview   = 1 " the preview window will be close automatically after a completion.
let g:clang_complete_copen  = 1 " open quickfix window on error
let g:clang_user_options    = "-std=c++11"
let g:clang_complete_macros = 1 " 宏和常量补全
" let g:clang_auto_user_options = "compile_commands.json"

" enables only <C-X><C-U> clang_complete_auto设置就没有意义
let g:clang_omnicppcomplete_compliance = 1

" undotree
if has("persistent_undo")
        set undodir='~/.undodir/'
        set undofile
endif

" ctrlp.vim
" :CtrlPDir dir         本次搜索指定目录 dir 下的内容 
let g:ctrlp_custom_ignore = {
                        \ 'dir':  '\v[\/]\.(git|hg|svn)$',
                        \ 'file': '\v\.(exe|so|dll|out|o|d|gch)$',
                        \ 'link': 'SOME_BAD_SYMBOLIC_LINKS',
                        \ }
" vim-easygrep
let g:EasyGrepFilesToExclude=".svn,.git,.hg,*.exe,*.so,*.dll,*.out,.*~,*.o,*.d,*.gch,*.pb.*"

" tagbar
let g:tagbar_left = 1   " 放在左边，如 ctrlp 的窗口就可以很好地显示在右边了

" 设置支持的文件编码类项，目前设置为 utf-8 和 gbk 两种类型。
set fileencodings=utf-8,chinese

" 在涉及到 sessions 文件时，使用 unix 格式。
set sessionoptions+=unix,slash

" 设置列高亮
" set cc=78			" 高亮第n列。

" 查看鼠标所在的列的对齐性。
map <leader>ch :call SetColorColumn()<CR>

function! SetColorColumn()
        let col_num = virtcol(".")
        let cc_list = split(&cc, ',')
        if count(cc_list, string(col_num)) <= 0
                execute "set cc+=".col_num
        else
                execute "set cc-=".col_num
        endif
endfunction

" set completeopt=longest,menu " 选择方法时，不显示预览窗口。
" autocmd InsertLeave * if pumvisible() == 0|pclose|endif	" 离开插入模式后自动关闭预览窗口

" some tips for vim
" Ctrl-r                计算器
" \(\<\w\+\>\)\_s*\1    查找重复的连续单词
" :w !sudo tee %        以非root方式打开，以root方式保存
" ggVGg?                实时加密文本
" diffthis diffoff      打开和关闭比较
" di(                   删除括号内的文字，只要光标放在括号内就可以，可以用于[或{ ""等
" dt[标记]              删除指定标记前的内容 dt.
" :%!xxd  :%!xxd -r     十六进制编辑器
" Ctrl-o Ctrl-i         跳来跳去
" %Tohtml               把当前文件转化为肉页
" :g/^/m0               Reverse file (m = move)
" :'a,'bg/^/m'b         Reverse a section a to b
" :g/^/t.               duplicate every line

" Ctrl-s 卡死           ctrl-s 在 LINUX 里是锁定屏幕的快捷键，解锁 ctrl-q

" 生成连续数字
"       ctrl-a          自己录宏，使用该命令递增
"       :let i=0 | g/zcc/s//\=i/ | let i=i+1  插入这样递增数列的地方插入一个全文不会重复出现的字母序列zcc，然后输入该命令

" vim: set enc=utf8

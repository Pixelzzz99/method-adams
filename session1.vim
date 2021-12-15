let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd D:/my_projects/method-adams
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
$argadd .
edit AdamsMoulton.py
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 54 + 39) / 79)
exe 'vert 1resize ' . ((&columns * 135 + 135) / 271)
exe '2resize ' . ((&lines * 22 + 39) / 79)
exe 'vert 2resize ' . ((&columns * 135 + 135) / 271)
exe '3resize ' . ((&lines * 54 + 39) / 79)
exe 'vert 3resize ' . ((&columns * 135 + 135) / 271)
exe '4resize ' . ((&lines * 22 + 39) / 79)
exe 'vert 4resize ' . ((&columns * 135 + 135) / 271)
argglobal
balt Figure_1.png
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 83 - ((41 * winheight(0) + 27) / 54)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 83
normal! 021|
wincmd w
argglobal
if bufexists("term://D:/my_projects/method-adams//1776:C:/Windows/system32/cmd.exe") | buffer term://D:/my_projects/method-adams//1776:C:/Windows/system32/cmd.exe | else | edit term://D:/my_projects/method-adams//1776:C:/Windows/system32/cmd.exe | endif
if &buftype ==# 'terminal'
  silent file term://D:/my_projects/method-adams//1776:C:/Windows/system32/cmd.exe
endif
balt AdamsMoulton.py
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 1003 - ((6 * winheight(0) + 11) / 22)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1003
normal! 017|
wincmd w
argglobal
if bufexists("method_adams.c") | buffer method_adams.c | else | edit method_adams.c | endif
if &buftype ==# 'terminal'
  silent file method_adams.c
endif
balt AdamsMoulton.py
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 110 - ((30 * winheight(0) + 27) / 54)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 110
normal! 010|
wincmd w
argglobal
if bufexists("term://D:/my_projects/method-adams//11328:C:/Windows/system32/cmd.exe") | buffer term://D:/my_projects/method-adams//11328:C:/Windows/system32/cmd.exe | else | edit term://D:/my_projects/method-adams//11328:C:/Windows/system32/cmd.exe | endif
if &buftype ==# 'terminal'
  silent file term://D:/my_projects/method-adams//11328:C:/Windows/system32/cmd.exe
endif
balt method_adams.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 1076 - ((21 * winheight(0) + 11) / 22)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1076
normal! 028|
wincmd w
3wincmd w
exe '1resize ' . ((&lines * 54 + 39) / 79)
exe 'vert 1resize ' . ((&columns * 135 + 135) / 271)
exe '2resize ' . ((&lines * 22 + 39) / 79)
exe 'vert 2resize ' . ((&columns * 135 + 135) / 271)
exe '3resize ' . ((&lines * 54 + 39) / 79)
exe 'vert 3resize ' . ((&columns * 135 + 135) / 271)
exe '4resize ' . ((&lines * 22 + 39) / 79)
exe 'vert 4resize ' . ((&columns * 135 + 135) / 271)
tabnext 1
badd +1 Figure_1.png
badd +83 AdamsMoulton.py
badd +111 method_adams.c
badd +0 term://D:/my_projects/method-adams//11328:C:/Windows/system32/cmd.exe
badd +0 term://D:/my_projects/method-adams//1776:C:/Windows/system32/cmd.exe
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOFA
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :

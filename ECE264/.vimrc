"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
"
" .vimrc file of Alex Quinn
" License:  public domain (use as you please, no credit needed)
"
" vim: set tabstop=4 shiftwidth=4 fileencoding=utf8 expandtab:

set nocompatible " Use VIM settings rather than Vi settings; this *must* be
                 " first in .vimrc

"_________________________________________________________________________
" GENERAL SETTINGS
"

set autoindent           " copy indent from the current line when starting a new line
set backspace=2          " allow backspacing over everything in insert mode
set history=50           " keep 50 lines of command line history
set ignorecase           " search commands are case-insensitive
set incsearch            " while typing a search command, show matches incrementally
                         " instead of waiting for you to press enter
set mouse=a              " enable mouse interaction
set number               " line numbers at the side
set ruler                " show the cursor position all the time
set shiftwidth=4         " pressing >> or << in normal mode indents by 4 characters
set tabstop=4            " a tab character indents to the 4th (or 8th, 12th, etc.) column
set viminfo='20,\"50     " read/write a .viminfo file, don't store more than 50 lines of registers
set encoding=utf8        " non-ascii characters are encoded with UTF-8 by default
set noexpandtab          " pressing the tab key creates a tab character, not spaces
set formatoptions=croq   " c=autowrap comments, r=continue comment on <enter>,
                         " o=continue comment on o or O, q=allow format comment with gqgq
set textwidth=0          " no forced wrapping in any file type (unless overridden)
set showcmd              " show length of visual selection (docs recommended
                         " keeping this off when working over slow connections)
set complete=.,w,b,u     " make autocomplete faster - http://www.mail-archive.com/vim@vim.org/msg03963.html
set splitright           " create vertical splits to the right
set splitbelow           " create horizontal splits below

set switchbuf=usetab     " when switching buffers, include tabs
set tabpagemax=30        " show up to 30 tabs
set hlsearch

set cryptmethod=blowfish " use blowfish encryption for encrytped files
let g:netrw_mouse_maps=0 " Ignore mouse clicks when browsing directories

"_________________________________________________________________________
" Create command to disable mouse and arrow keys if you wish (mainly for HW01)
"
function! DisableMouseAndArrowKeys()
	map <up>   <nop>
	map <down> <nop>
	map <left> <nop>
	map <up>   <nop>
	set mouse=
endfunction
command DisableMouseAndArrowKeys :call DisableMouseAndArrowKeys()


"_________________________________________________________________________
" MAPPINGS for normal mode
"

" F1 - help on some command
map <F1> :h 

" F2 - open file in new tab
map <F2> :tabe 

" F3 - save current file
map <F3> :w<CR>

" F4 - exit
map <F4> :q<CR>

" Shift-F4 - exit without saving
map <S-F4> :q!<CR>

" F6 - switch to next split
map <F6> <C-W><C-W>

" Shift-F6 - switch to next split, in reverse order
map <S-F6> <C-W>W

" F7 - Start search command, delimited by comma
nmap <F7> :%s,

" F8 - stop highlighting search results
map <F8> :noh<CR>

" F9 - change a setting
map <F9> :set 

" Shift-F9 - change a setting, only in current tab/buffer
map <S-F9> :setlocal 

" F12 - toggle display of whitespace
nmap <F12> :set invlist<CR>

" ; (semicolon) - same as : (colon)
nmap ; :

" ' ' (space) - same as : (colon)
nmap <SPACE> :

" [ (left bracket) - change tabs to the left
nnoremap <s-tab> gT

" [ (right bracket) - change tabs to the right
nnoremap <tab> gt


"_________________________________________________________________________
" MAPPINGS for insert mode
"

" F2 - add another item to a comma-separated list of strings
imap <F2> <RIGHT>, ""<LEFT>

" F3 - autocomplete, backward
inoremap <F3> <C-P>

" F4 - autocomplete, forward
inoremap <F4> <C-N>

" F5 - underscore (to save pinky finger)
map! <F5> _

" F6 - pair of curly braces, continue typing inside them
map! <F6> {}<LEFT>

" F7 - pair of parentheses, continue typing after them
map! <F7> ()

" F8 - pair of parentheses, continue typing inside them
map! <F8> ()<LEFT>

" F9 - pair of parentheses with extra spaces inside, continue typing inside them
map! <F9> (  )<LEFT><LEFT>

" F10 - pair of double quotation marks, continue typing inside them
map! <F10> ""<LEFT>

" Shift-F10 - pair of single quotation marks, continue typing inside them
map! <S-F10> ''<LEFT>

" F11 - pair of square brackets, continue typing inside them
map! <F11> []<LEFT>

" F12 - pair of angle brackets, continue typing inside them
map! <F12> <><LEFT>


"_________________________________________________________________________
" PLUGINS
"
" We are making some plugins and color schemes available to all students.
" For a list, enter the following from bash:
"   $ ls /home/shay/a/ece264s0/16au/vimfiles/{bundle,colors}
"
" As of 8/1/2016, it included these plugins:  airline, commentary, easy-align,
" LargeFile, multiple-cursors, Rename, SimpylFold, snipmate, surround.
"
" We use the Pathogen plugin manager.  (https://github.com/tpope/vim-pathogen)
if filereadable('/home/shay/a/ece264s0/16au/vimfiles/autoload/pathogen.vim')
	let &runtimepath='/home/shay/a/ece264s0/16au/vimfiles,' . &runtimepath
	execute pathogen#infect('/home/shay/a/ece264s0/16au/vimfiles/bundle/{}')
endif

" hotkeys for easy-align plugin, if installed
if exists(":EasyAlign")
	nmap g<tab> <Plug>(EasyAlign) 
	xmap g<tab> <Plug>(EasyAlign)
endif

"_________________________________________________________________________
" COLORS
"
if &t_Co > 2 || has("gui_running")
	try
		colorscheme summerfruit256 " might not be on every system
	catch /^Vim\%((\a\+)\)\=:E185/
		colorscheme slate          " backup, in case summerfruit was not available
	endtry

    syntax on
endif


"_________________________________________________________________________
" GUI OPTIONS - only affects gvim
"
if has("gui_running")
    au GUIEnter * simalt ~x     " Start maximized
    set guioptions-=T           " No toolbar
    set guioptions-=m           " No menus
    set guioptions-=L           " No left scrollbar
    set guioptions-=r           " No right scrollbar
endif


"_________________________________________________________________________
" AUTOMATIC BACKUP FILES
"
" Enable backup files - Every time you save a file, it will create a copy of the file
" called <filename>~ (e.g., file.txt~) in the directory ~/.vim_backup_files/.
" This is *NOT* a comphrehensive backup solution, but it can help sometimes.
"
let &backupdir=($HOME . '/.vim_backup_files')
if ! isdirectory(&backupdir)
	call mkdir(&backupdir, "", 0700)
endif
set backup

syntax enable
colorscheme monokai

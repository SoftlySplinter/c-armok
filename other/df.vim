" Vim syntax file
" Language: Armok
" Maintainer: Alexander Brown
" Latest Revision: 19 November 2013

if exists("b:current_syntax")
  finish
endif

" Keywords
syn match dfType "+"
syn match dfType "-"

syn match dfFunction ">"
syn match dfFunction "<"

syn match dfFunction "w"

syn match dfStatement "m"
syn match dfStatement "d"

syn region dfComment start="!!" end="!!"

syn region dfValidDwarf start="[+-]" end="[+-]" contains=ALL,dfStatementdfFunction

syn match dfError "." contains=ALLBUT,dfValidDwarfdfComment

hi link dfType Type
hi link dfValidDwarf Function
"hi link dfStatement Statement
"hi link dfFunction Function
hi link dfString String
hi link dfComment Comment
hi link dfError Error

let b:current_syntax = "df"

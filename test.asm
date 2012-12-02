.386
.MODEL FLAT



ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

INCLUDE io.h 
INCLUDE list.h

cr EQU 0dh 
Lf EQU 0ah 

.STACK 4096 



.DATA

string	BYTE	20	DUP(?),0
endl	BYTE	cr,Lf,0

prompt_constructor	BYTE	"list with 20 byte capacity has been made by list macro",cr,Lf,0
prompt_constructor2	BYTE	"another list has been built by list.h macro",cr,Lf,0
prompt_append1		BYTE	"values 7,9,132,2,5 has been added to list",cr,Lf,0
prompt_append2		BYTE	"values  87,21,1,9,38 has been added to list",cr,Lf,0
prompt_append3		BYTE	"values  7,9 has been added to this list",cr,Lf,0
prompt_show			BYTE	"list's values:",cr,Lf,0
prompt_show2		BYTE	"second list's values:",cr,Lf,0
prompt_quicksort	BYTE	"list has been sort by quick sort",cr,Lf,0
prompt_bubblesort	BYTE	"list has been sort by bubble sort",cr,Lf,0
prompt_get			BYTE	"list[1]:",cr,Lf,0
prompt_pop_back		BYTE	"list has been pop_back",cr,Lf,0
prompt_top			BYTE	"list's top value:",cr,Lf,0
prompt_delete		BYTE 	"list[1] has been deleted",cr,Lf,0
prompt_min			BYTE	"list's min value:",cr,Lf,0
prompt_max			BYTE	"list's max value:",cr,Lf,0
prompt_len			BYTE	"list's length:",cr,Lf,0
prompt_find			BYTE	"index of find element 9:",cr,Lf,0
.CODE
_start:	
	
	list metallica2,20
	output	prompt_constructor
	output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	append	metallica2,7
	append	metallica2,9
	output	prompt_append3
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_show2
	show	metallica2
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	list metallica,50
	output	prompt_constructor2
	output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	append	metallica,7
	append	metallica,9
	append	metallica,132
	append	metallica,2
	append	metallica,5
	output	prompt_append1
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_show
	show	metallica
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_get
	get		metallica,1
	dtoa	string,ebx
	output	string
		output	endl
		output	endl	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_len
	len		metallica
	dtoa	string,eax
	output	string
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_pop_back
	pop_back 	metallica
	output	prompt_show
	show	metallica
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_top
	top		metallica
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_delete
	delete	metallica,1
	output	prompt_show
	show	metallica
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_min
	min		metallica
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_max
	max		metallica
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	output		prompt_bubblesort
	BubbleSort	metallica	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_show
	show	metallica
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
		
	append	metallica,87
	append	metallica,21
	append	metallica,1
	append	metallica,9	
	append	metallica,38
	output	prompt_append2
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_show
	show	metallica
		output	endl
		output	endl	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output		prompt_find
	find		metallica,9
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output		prompt_quicksort
	QuickSort	metallica	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	output	prompt_show
	show	metallica
		output	endl
		output	endl
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	
	
		
	INVOKE ExitProcess, 0 	;exit with return code 0


PUBLIC _start 			;make entry point public

END 				;end of source code




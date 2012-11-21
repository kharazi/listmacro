.386
.MODEL FLAT



ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

INCLUDE io.h 
INCLUDE list.h

cr EQU 0dh 
Lf EQU 0ah 

.STACK 4096 



.DATA

string	BYTE	20	DUP(?)

.CODE
_start:	

	list 20
	append	eax,7
	append	eax,4
	show	eax
	
	
		
	INVOKE ExitProcess, 0 	;exit with return code 0


PUBLIC _start 			;make entry point public

END 				;end of source code



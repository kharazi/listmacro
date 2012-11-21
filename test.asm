.386
.MODEL FLAT



ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

INCLuDE io.h 
INCLuDE list.h

cr EQU 0dh 
Lf EQU 0ah 

.STACK 4096 



.DATA

string	BYTE	20	DUP(?)

.CODE
_start:	

	;mov eax,34
	;push eax
	;call malloc
	
	list 20
	
	mov DWORD ptr [eax],2
	dtoa	string,[eax]
	output string
	
	mov DWORD ptr [eax+8],1
	dtoa	string,[eax+8]
	output string
	
		
	INVOKE ExitProcess, 0 	;exit with return code 0


PUBLIC _start 			;make entry point public

END 				;end of source code



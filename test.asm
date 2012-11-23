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
.CODE
_start:	
	mov		metallica,0
	list metallica,20
	append	metallica,1
	append	metallica,2
	append	metallica,3
	append	metallica,4
	show	metallica
		output	endl
		
	get		metallica,1
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
		
	pop_back 	metallica
	show	metallica
		output	endl
		output	endl
		
	top		metallica
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
		
	append	metallica,4
	delete	metallica,1
	show	metallica
		output	endl
		output	endl
		
	delete	metallica,0
	append	metallica,2
	append	metallica,1
	append	metallica,3
	show	metallica
		output	endl
		output	endl
		
	min		metallica
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
	show metallica
		output	endl
		output	endl
		
	len		metallica
	dtoa	string,eax
	output	string
		output	endl
		output	endl
		
	find		metallica,4
	dtoa	string,eax
	output	string
		output	endl
		output	endl
		
	INVOKE ExitProcess, 0 	;exit with return code 0


PUBLIC _start 			;make entry point public

END 				;end of source code



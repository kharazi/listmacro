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

	list 20
	append	eax,1
	append	eax,2
	append	eax,3
	append	eax,4
	show	eax
		output	endl
		
	get		eax,1
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
		
	pop_back 	eax
	show	eax
		output	endl
		output	endl
		
	top		eax
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
		
	append	eax,4
	delete	eax,1
	show	eax
		output	endl
		output	endl
		
	delete	eax,0
	append	eax,2
	append	eax,1
	append	eax,3
	show	eax
		output	endl
		output	endl
		
	min		eax
	dtoa	string,ebx
	output	string
		output	endl
		output	endl
		
	INVOKE ExitProcess, 0 	;exit with return code 0


PUBLIC _start 			;make entry point public

END 				;end of source code



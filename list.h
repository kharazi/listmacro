.NOLIST     ; turn off listing
.386
.STACK 4096 


ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

INCLUDE io.h 
extern C malloc:proc
includelib	 msvcrt.dll

cr EQU 0dh 
Lf EQU 0ah 

.DATA
append_error	BYTE	"ERROR!",cr,Lf,"len=size",0
reshte			BYTE	11 DUP(?)

.CODE


arr STRUCT
	address		DWORD PTR		?
	s	 		DWORD 		?
	len 		DWORD 		?
arr ENDS

list	macro	siz

		
		mov 	eax,siz					
		push 	eax
		call 	malloc							;allocate memorry
		
		ASSUME 	ebx:PTR arr						;ebx is an object
												;assign objects attributes
		mov  	[ebx].address,eax		
		
		
		mov 	[ebx].s,siz
		mov 	[ebx].len,0					
		
		mov		eax,ebx							;returns address of object in eax
		
		
ENDM		

append	macro	adres,value

		
		pushad									;save	registers
		
		mov		eax,adres						;address of object
			
		mov		ecx,(arr PTR[eax]).address		;address of list
		mov		ebx,(arr PTR[eax]).len
		mov		edx,(arr PTR[eax]).s
	

		;cmp 	ebx,edx
		;jl		continue						;jump if len<s 
												;else if len>s or len=s	
		;output 	append_error
		;INVOKE ExitProcess, 0 					;exit with return code 0
		
;continue:
		mov		DWORD PTR[ecx+ebx*4],value		;at first len=0
		add 	(arr PTR[eax]).len,1			;len++
		popad									;reload registers

ENDM
		
tes		macro	adres

		pushad									;save	registers
		mov		eax,adres						;address of object
		mov		ebx,(arr PTR[eax]).len
		
		mov 	edx,[(arr PTR[eax]).address]
		popad									;reload registers
ENDM

show	macro	adres							;just for test

		
		pushad									;save	registers
		mov		eax,adres						;address of object
		mov		ecx,(arr PTR[eax]).address		;address of list							;age jaye ecx o 
																							;ba ebx avaz konim error
		dtoa 	reshte,[ecx]																;mide!!!!!!!!!!			
		output	reshte
		dtoa 	reshte,[ecx+4]																
		output	reshte
		dtoa 	reshte,[ecx+8]																
		output	reshte
		popad									;reload registers
ENDM

;min		macro	  address,siz		
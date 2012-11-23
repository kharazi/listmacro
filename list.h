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
reshte			BYTE	11 DUP(?),0
reshte2			BYTE	'*',0
.CODE


arr STRUCT
	address		DWORD PTR		?
	s	 		DWORD 		?
	len 		DWORD 		?
arr ENDS

list	macro	nam,siz					;mov address to eax
		
		.DATA
		nam		DWORD		?
		
		.CODE
		
		mov 	eax,siz					
		push 	eax
		call 	malloc							;allocate memorry
		
		ASSUME 	ebx:PTR arr						;ebx is an object
												;assign objects attributes
		mov  	[ebx].address,eax		
		
		
		mov 	[ebx].s,siz
		mov 	[ebx].len,0					
		
		mov		eax,ebx							;returns address of object in eax
		mov		nam,eax							;save address of object in memory
		
		
ENDM		

append	macro	nam,value			
local	continue
		
		pushad									;save	registers
		mov		eax,nam						;address of object
		mov		ecx,(arr PTR[eax]).address		;address of list
		mov		ebx,(arr PTR[eax]).len
		mov		edx,(arr PTR[eax]).s
	

		cmp 	ebx,edx							;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		jl		continue						;jump if len<s 
												;else if len>s or len=s	
		output 	append_error
		INVOKE ExitProcess, 0 					;exit with return code 0
		
continue:
		mov		DWORD PTR[ecx+ebx*4],value		;at first len=0
		add 	(arr PTR[eax]).len,1			;len++
		popad									;reload registers

ENDM

len 	macro 	nam				; Move len of list to eax register
		push 	ecx 					; Save ecx register
		mov		ecx,nam						;address of object
		mov 	eax , (arr PTR[ecx]).len	; Move len of list to eax register  
		pop 	ecx						; Reload ecx register
ENDM



find	macro 	nam,value 				; Move first occourd value in list to eax register , Move -1 if not find
local 	find_for,not_find,end_find,finded	
		
		push 	ecx
		push 	edx
		mov		eax,nam						;address of object
		mov 	ecx , (arr PTR[eax]).address
		mov 	edx , (arr PTR[eax]).len 
		jz		not_find		; if len ==0 
		dec 	edx
		mov 	ebx, 0 
find_for:
		mov		edi,[ecx+ebx*4]
		cmp 	edi,value
		je		finded
		cmp 	ebx,edx
		jle		find_for 
		
		
not_find:
		mov 	eax,-1
		jmp		end_find
finded:
		mov 	eax, ebx 
end_find:
		pop 	edx
		pop 	ecx
ENDM
		
get		macro	nam,index			;move 	index	to ebx				;;;;;;;;;;;;;;;must check index

		mov		eax,nam						;address of object
		mov 	ecx,[(arr PTR[eax]).address]
		mov		ebx,[ecx+4*index]

ENDM

show	macro	nam				;output	all indexes
local forloop,end_m
		pushad									;save	registers
		mov		eax,nam							;address of object
		mov		ecx,(arr PTR[eax]).address		;address of list 	;age jaye ecx o ba ebx avaz konim error mide!
		mov		edx,(arr PTR[eax]).len
		cmp		edx,0
		jz		end_m							;if len=0
		dec  	edx								;cause	index start from 0
		mov 	ebx,0
forloop:
		dtoa 	reshte,[ecx+ebx*4]
		output	reshte
		inc 	ebx
		cmp		ebx,edx
		jle		forloop
		
end_m:
		popad									;reload registers
ENDM

pop_back macro	nam				;pop the last index

		 pushad									;save	registers
		 mov		eax,nam						;address of object
		 dec		(arr PTR[eax]).len
		 popad									;reload registers
ENDM

top		 macro	nam				;return's the last index in ebx

		 mov		eax,nam						;address of object
		 mov		ecx,(arr PTR[eax]).address
		 mov		edx,(arr PTR[eax]).len
		 dec		edx
		 mov		ebx,[ecx+4*edx]
ENDM

delete 	 macro	nam,index			 ;delete the  index
local forloop2,end_m2
		pushad									;save	registers
		mov		eax,nam						;address of object
		mov		ecx,(arr PTR[eax]).address		;address of list 	;age jaye ecx o ba ebx avaz konim error mide!
		mov		edx,(arr PTR[eax]).len
		dec 	edx
		jz		end_m2							;if len=0
		mov		ebx,index						;cause	index start from index
		cmp		ebx,edx
		jge		end_m2
		
		dec		(arr PTR[eax]).len				;len--
forloop2:
		mov		edi,ebx
		inc		edi
		mov		edi,[ecx+4*edi]
		mov		DWORD PTR[ecx+4*ebx],edi
		inc		ebx
		cmp		ebx,edx
		jle		forloop2
		
end_m2:
		popad									;reload registers
ENDM


min		macro	  nam
local forloop3,ebxbigger,endloop3
		push 	eax
		mov		eax,nam						;address of object
		mov		ecx,(arr PTR[eax]).address		;address of list 	;age jaye ecx o ba ebx avaz konim error mide!
		mov		edx,(arr PTR[eax]).len
		
		mov	eax,[ecx]								;eax=min
		mov	edi,0									;edi=counter
		cmp edx,0
		jz 	endloop3
		
forloop3:
		cmp 	edi,edx
		jz		endloop3
		mov 	ebx,[ecx+edi*4]						;ebx=list[i]
		cmp 	ebx,eax								;list[i]<min
		jg		ebxbigger
		mov		eax,ebx
					
ebxbigger:	
		inc 	edi
		jmp 	forloop3
					
endloop3:
		mov		ebx,eax								;returns min in ebx
		pop		eax									;reload	addres in eax
ENDM


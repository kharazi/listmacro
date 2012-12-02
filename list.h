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
outofindex		BYTE	"ERROR!",cr,Lf,"index>len",0
reshte			BYTE	11 DUP(?),0
reshte2			BYTE	'*',0
privot			DWORD	?
i				DWORD 	?
j				DWORD	?
tmp				DWORD	?
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
		
		pushad
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
		
		popad
ENDM		

append	macro	nam,value			
local	continue
		
		pushad									;save	registers
		mov		eax,nam							;address of object
		mov		ecx,(arr PTR[eax]).address		;address of list
		mov		ebx,(arr PTR[eax]).len
		mov		edx,(arr PTR[eax]).s
	

		cmp 	ebx,edx			
		jl		continue						;jump if len<s 
												;else if len>s or len=s	
		output 	append_error
		INVOKE ExitProcess, 0 					;exit with return code 0
		
continue:
		mov		DWORD PTR[ecx+ebx*4],value		;at first len=0
		add 	(arr PTR[eax]).len,1			;len++
		popad									;reload registers

ENDM

len 	macro 	nam								; Move len of list to eax register
		push 	ecx 							; Save ecx register
		mov		ecx,nam							;address of object
		mov 	eax , (arr PTR[ecx]).len		; Move len of list to eax register  
		pop 	ecx								; Reload ecx register
ENDM



find	macro 	nam,value 			; Move first occourd value in list to ebx register , Move -1 if not find
local 	find_for,not_find,end_find
		
		push 	ecx
		push 	edx
		mov		eax,nam							;address of object
		mov 	ecx , (arr PTR[eax]).address
		mov 	edx , (arr PTR[eax]).len 
		cmp		edx,0
		jz		not_find						; if len ==0 
		dec 	edx
		mov 	ebx, 0 
find_for:
		mov		edi,[ecx+ebx*4]
		cmp 	edi,value
		je		end_find
		inc		ebx
		cmp 	ebx,edx
		jle		find_for 
		
		
not_find:
		mov 	ebx,-1
end_find:
		pop 	edx
		pop 	ecx
ENDM
		
get		macro	nam,index		;move 	index	to ebx				
local	notbreak
		mov		eax,nam						;address of object
		mov 	ecx,[(arr PTR[eax]).address]
		mov		edx,index
		cmp		edx,(arr PTR[eax]).len		;check if index>len or not
		jl		notbreak
		output	outofindex
		notbreak:
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

delete 	 macro	nam,index		;delete the  index
local forloop2,end_m2
		pushad									;save	registers
		mov		eax,nam							;address of object
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



max		macro	  nam
local forloop3,ebxbigger,endloop3
		push 	eax
		mov		eax,nam								;address of object
		mov		ecx,(arr PTR[eax]).address			;address of list 	
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
		jl		ebxbigger
		mov		eax,ebx
					
ebxbigger:	
		inc 	edi
		jmp 	forloop3
					
endloop3:
		mov		ebx,eax								;returns min in ebx
		pop		eax									;reload	addres in eax
ENDM







quickaux proc
	push ebp
	mov ebp,esp
	pushad

	mov ebx,[ebp+8]		; start of partition
						;;  find pivot index:	
ploop:
	cmp ebx,[ebp+12]	;  last cell of partition?
	jge qretrn			;  no pivot, so exit
	mov eax, [ebx+4]	;  A[i+1]
	cmp eax, [ebx]		;  A[i]
	jl pfound			;  A[i]>A[i+1], pivot found
	add ebx,4			;  next cell
	jmp ploop
pfound:
	;;  use two counters:	 ebx and esi.  ebx always points to the
	;;  first cell of second partition (what's >= pivot)
	mov ecx,[ebx]		;  save pivot in ecx
	mov esi,ebx
	add esi,4			;  next cell
tloop:
	cmp ecx,[esi]		;  compare pivot and element
	jle noswap			;  no swap if element >=pivot
	;;  swap [ebx] and [esi], advance both
	mov eax,[ebx]
	push eax		;  use stack as temp
	mov eax,[esi]
	mov [ebx],eax
	pop eax
	mov [esi],eax		
	add ebx,4			;  next cell must still be >= pivot
noswap:				
	add esi,4			;  goto next cell, preserve ebx
	cmp esi,[ebp+12]	;  end of partition?
	jle tloop			

	;;  ebx holds start addr of second partition
	
	sub ebx,4
	push ebx			;  end of first paritition
	mov eax,[ebp+8]		 
	push eax			;  start of first partition
	call quickaux
	add esp,8			
	;;  second partition
	mov eax,[ebp+12]
	push eax			;  end of second partition
	add ebx,4
	push ebx			;  start of second partition
	call quickaux
	add esp,8
	
qretrn:
	popad
	mov esp,ebp
	pop ebp
	ret
quickaux endp




QuickSort macro  nam

	pushad
	mov		eax,nam						;address of object
	mov ebx,(arr PTR[eax]).address		;  start addr of array
	mov eax,(arr PTR[eax]).len			;  end index of partition
	dec eax
	shl eax,2							;  multiply by 4: sizeof(int)==4
	add eax,ebx							;  eax holds end addr of partition
	mov ecx,0							;  start index of partition
	shl ecx,2
	add ecx,ebx							;  start addr of partition
	push eax							;  quickaux expects start and end 
	push ecx							;    addresses of partition as arguments.
	call quickaux		
	add esp,8
	popad
ENDM




BubbleSort macro  nam

	pushad
	mov		eax,nam						;address of object
	mov ebx,(arr PTR[eax]).address		;  start addr of array
	mov eax,(arr PTR[eax]).len			;  end index of partition
	
	
	push eax							;  quickaux expects start and end 
	push ecx							;    addresses of partition as arguments.
	call bs
	add esp,8
	popad
ENDM



bs proc
		push ebp
		mov ebp,esp
		pushad
        mov ecx,[ebp+12]
	
        mov edx,[ebp+8]
		
		mov	eax,0
bs_i:
		dec	ecx
		mov eax,0
bs_j:
		
        mov edi,DWORD PTR [edx+eax*4]
		
        cmp DWORD PTR [edx+eax*4+4],edi
        jl l
        mov edi,DWORD PTR [edx+eax*4]
		mov	esi,DWORD PTR [edx+eax*4+4]
        mov DWORD PTR [edx+eax*4+4],edi
		mov DWORD PTR [edx+eax*4],esi
l:
        inc eax
        cmp eax,ecx
        jl bs_j
		
		
        cmp ecx,0
        jg bs_i
		
		popad
		mov esp,ebp
		pop ebp
		ret
bs endp
 
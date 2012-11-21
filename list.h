.NOLIST     ; turn off listing
.386

extern C malloc:proc
includelib	 msvcrt.dll

arr STRUCT
	address		DWORD		?
	s	 		DWORD 		?
	len 		DWORD 		?
arr ENDS

list	macro	siz

		
		mov eax,siz		
		push eax
		call malloc
		
		ASSUME ebx:PTR arr
		mov [ebx].address,eax
		mov [ebx].s,siz
		mov [ebx].len,0
		
ENDM		

;min		macro	  address,siz		
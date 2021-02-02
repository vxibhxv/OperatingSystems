bits 16
org 0x7c00

boot:
	mov ax,0x2401
	int 0x15
	mov ax,0x3
	int 0x10
	cli
	lgdt [gdt_desc]
	mov eax, cr0
	or eax,0x1
	mov cr0,eax
	jmp CODE_SEG: start
gdt_null:
	dq 0x0
gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_end:
gdt_desc: 
	dw gdt_end - gdt_null
	dd gdt_null

CODE_SEG equ gdt_code - gdt_null
DATA_SEG equ gdt_data - gdt_null

bits 32
start:
	mov ax,DATA_SEG
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov ss,ax
	mov esi,hello
	mov edx, cr0
	mov ecx, 32
	mov ebx, 0xb8000

.loop:
	lodsb
	or al,al
	jz .loop1
	or eax, 0x100
	mov word [ebx], ax
	add ebx,2
	jmp .loop

.loop1:
	mov eax, 0x130
	shl edx, 1
	adc eax, 0
	mov [ebx],ax
	add ebx,2
	dec ecx
	jnz .loop1

done:
	cli
	hlt

hello db "Hello World!",0

times 510-($-$$) db 0	
dw 0xaa55


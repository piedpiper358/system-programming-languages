section .text
	
string_length:
		xor rax, rax
	.loop:
		cmp byte[rdi + rax], 0
		je .finish
		inc rax
		jmp .loop
	.finish:
		ret
		
print_string:	
	push rdi
	call string_length
	mov rdx, rax
	mov rax, 1 
	mov rdi, 1 
	pop rsi
	syscall
	xor rax, rax
    ret
	
print_char:
	push rdi
	mov rax, 1 
	mov rdi, 1 
	mov rsi, rsp
	mov rdx, 1 
	syscall
	pop rax	;dec rsp
	xor rax, rax
	ret
	
print_newline:	
	mov rdi, 0xA
	call print_char
	xor rax, rax
	ret

print_uint:	
		mov r8, rsp
		mov rax, rdi
		push 0x0
	.loop:
		xor rdx, rdx
		mov rsi, 10
		div rsi  	
		add rdx, 0x30
		dec rsp
		mov byte [rsp], dl ;push dl  
		test rax, rax 
		jnz .loop
	
		mov rdi, rsp
		call print_string
		mov rsp, r8
		xor rax, rax
		ret

print_int:
		test rdi, rdi
		jns .print
		not rdi
		inc rdi
		push rdi    
		mov rdi, 0x2D
		call print_char
		pop rdi
	.print:
		call print_uint
		ret
		
read_char:
	push 0
	mov rax, 0
	mov rdi, 0
	lea rsi, [rsp]
	mov rdx, 1 
	syscall
	pop rax
	ret
	
section .data
	word_buffer: times 256 db 0
section .text	

read_word:
		push rbx
		xor rbx, rbx
	.loop1:
		call read_char
		cmp rax, 0x20
		je .loop1
		cmp rax, 0x09
		je .loop1
		cmp rax, 0x0A
		je .loop1
		cmp rax, 0x00
		je .quit
	
	.loop2:
		mov byte [word_buffer+rbx], al 
		inc rbx
		call read_char
		cmp rax, 0x20
		je .quit
		cmp rax, 0x9
		je .quit
		cmp rax, 0xA
		je .quit
		cmp rax, 0x0
		je .quit
		
		jmp .loop2
	.quit:
		mov byte [word_buffer+rbx], 0x0
		mov rdx, rbx
		mov rax, word_buffer  
		pop rbx
		ret

parse_uint: ; прихерачить rdx
		xor rax, rax
		xor rsi, rsi
		xor rcx, rcx
	.loop:
		mov cl, [rdi+rsi]
		sub rcx, 0x30
		js .quit
		cmp rcx, 0xA
		jns .quit
		mov rdx, 10
		mul rdx  
		
		sal rdx, 32 ; прихерачить rdx
		add rax, rdx
		

		add rax, rcx
		inc rsi
		jmp .loop
	.quit:
		mov rdx, rsi
		ret
		
parse_int:
		xor rcx, rcx
		mov cl, [rdi]
		cmp rcx, 0x2D
		je .neg
		cmp rcx, 0x30
		js .nan
		cmp rcx, 0x3A
		jns .nan
		call parse_uint
		ret
	.neg:
		lea rdi, [rdi+1]
		call parse_uint
		inc rdx
		not rax
		inc rax
		ret
	.nan:
		xor rax, rax
		xor rdx, rdx
		ret
	
string_copy:
	.loop:
		xor rcx, rcx
		mov cl, [rdi]
		mov [rsi], rcx
		inc rdi
		inc rsi
		cmp rcx, [newline_char]
		jne .loop
		xor rax, rax
        ret

string_equals:
	.loop:
		xor rcx, rcx
		xor rdx, rdx
		mov cl, [rdi]
		mov dl, [rsi]
		cmp rcx, rdx 
		je .equal
		xor rax, rax
		ret
	.equal:
		inc rdi
		inc rsi
		cmp rcx, 0x0;
		jne .loop
		mov rax, 1
		ret
		
		
		
		
section .data
	codes: db '0123456789abcdef', 0xA
	
section .text
print_hex:
	mov rax, rdi
	mov rdi, 1
	mov rdx, 1
	mov rcx, 64 
	iterate:
	push rax 
	sub rcx, 4
	sar rax, cl 
	and rax, 0xf 
	lea rsi, [codes + rax]
	mov rax, 1
	push rcx 
	syscall
	pop rcx
	pop rax 
	test rcx, rcx 
	jnz iterate
	ret


	
	
section .data
	newline_char: db 0xA
	string_to_parse: db '10fdsf'
section .text

	
		global _start
	_start:
	
	
	mov rdi, 48
	call print_int
	
	call print_newline

	
	mov rax, 60
	xor rdi, rdi
	syscall

	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	push rax
	push rcx
	push rdx
	push rsi
	push rdi
	
	mov rdi, rcx
	;call print_hex
	;call print_newline
	
	pop rdi
	pop rsi
	pop rdx
	pop	rcx
	pop rax
	
	
	;pusha
	;popa
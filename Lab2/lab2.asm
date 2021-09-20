%include "../lab1/lib.inc"
%define pc r12;rax ;указыаает на ячейку памяти, в кторой лежит следующий XT 
%define w r13 ;rax ;
%define rstack rax; rsp стека адресов возврата


docol: ;call
	sub rstack, 8
	mov [rstack], pc
	add w, 8 
	mov pc, w
	jmp next

exit: ;ret
	mov pc, [rstack]
	add rstack, 8
	jmp next

next:
	mov w, pc
	add pc, 8 
	mov w, [w]
	jmp [w]




%define link 0
%macro native 3
	section .data
		w_%2:
			%%link: dq link
			ww_%2: db %1, 0
			db %3
		xt_%2:
			dq %2_impl
	
	section .text
	 %2_impl:
	%define link %%link
%endmacro

%macro native 2
native %1, %2, 0
%endmacro

%macro colon 3
	section .data
		w_%2:
			%%link: dq link
			db %1, 0
			db %3
			dq docol
	%define link %%link
%endmacro





; colon ’>’, greater
	; dq xt_swap
	; dq xt_less
	; dq exit

	
native '+' , plus
	pop rax
	add [rsp], rax
	jmp next
	
	
native '-' , minus, 0
	pop rax
	add [rsp], rax
	jmp next
	

	
	
	
	
section .text
find_word:
		mov rcx, link
	.loop:
		; в rdi адрес 1 строки
		lea rsi, [rcx+8]
		push rcx
		call string_equals
		pop rcx
		test rax, rax
		jz .next
		mov rax, rcx 
		ret
	.next:
		mov rcx, [rcx]
		test rcx, rcx
		jnz .loop
		xor rax, rax
		ret

cfa:;или через string_length
		lea rax, [rdi+8]
	.loop:
		cmp byte[rax], 0
		je .quit
		inc rax
		jmp .loop
	.quit:
		;inc rax
		add rax, 2
		ret

	
	
section .data
	program_stub: dq 0
	xt_interpreter: dq .interpreter
	.interpreter: dq interpreter_loop
	
	
	rword: db 0
section .text	

interpreter_loop:
	call read_word ;можно переделать read_word, чтоб он писал в переданный как аргумент укзатель
	mov [rword], rax
	mov rdi, rax
	call string_length
	test rax, rax
	jz .quit
	

	mov rdi, [rword]
	call find_word
	mov rdi, rax
	
	test rdi, rdi
	jz .number
	call cfa
	
	mov rdi, rax 
	call print_hex
	call print_newline
	ret
	
	mov [xt_interpreter], rax
	mov qword[program_stub], xt_interpreter
	mov pc, program_stub
	jmp next
	
	
.number:	
	mov rdi, [rword]
	call parse_uint
	test rdx, rdx
	jz .quit
	
	push rax
	
	
	;mov pc, xt_interpreter
	;jmp next
	.quit:
	ret 

section .data
last_word: dq link	
section .data
	word_to_parse: db '+', 0	
global _start
_start:

mov rdi, word_to_parse
call find_word
mov rdi, rax
call print_hex
call print_newline



; mov rdi, w_minus
; call print_hex
; call print_newline

mov rdi, w_plus
call print_hex
call print_newline



mov rdi, w_plus 
call cfa
mov rdi, rax
call print_hex
call print_newline


mov rdi, xt_plus 
call print_hex
call print_newline


call interpreter_loop


mov rdi, xt_minus 
call print_hex
call print_newline

mov rax, 60
xor rdi, rdi
syscall

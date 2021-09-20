
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

%macro colon 2
native %1, %2, 0z
%endmacro



;colon '>', greater
        dq xt_swap
        dq xt_less
        dq exit

native '.S' , stack

        jmp next

native '+' , plus
        pop rax
        add [rsp], rax
        jmp next

native '-' , minus
        pop rax
        sub [rsp], rax
        jmp next

native '*' , asterisk
        pop rax
        pop rdx
        mul rdx
        ;- rdx -----
        ;sal rdx, 32
        ;add rax, rdx
        ;push rdx
        push rax
        jmp next

native '/' , slash
        pop rcx
        pop rax
        xor rdx, rdx
        div rcx
        push rax
        jmp next

native '=' , es; equal; equals sign
        pop rax
        pop rdx
        cmp rax, rdx
        je .equal
        push 0
        jmp next
        .equal:
        push 1
        jmp next


native '<' , less

        jmp next

native 'and' , and

        jmp next

native 'not' , not

        jmp next

native 'rot' , rot
        pop rax ;c
        pop rdx ;b
        pop rcx ;a

        push rdx
        push rax
        push rcx
        jmp next

native 'swap' , swap
        pop rax
        pop rdx
        push rax
        push rdx
        jmp next

native 'dup' , dup
        ; pop rax
        ; push rax
        ; push rax
        push qword [rsp]
        jmp next

native 'drop' , drop
        ; pop rax
        ; push rax
        ; push rax
        push qword [rsp]
        jmp next

native '.' , dot
        pop rdi
        call print_int
        call print_newline
        jmp next

native 'key' , key
        call read_char
        push rax
        jmp next

native 'emit' , emit
        pop rdi
        call print_char
        call print_newline
        jmp next

native 'number' , number ;???
        ;call read_int
        push rax
        jmp next

native 'mem' , mem
        push user_mem
        jmp next

native '!' , em;exclamation_mark ;???
        pop rax
        pop rdi
        mov [rax], rdi
        jmp next

native '@' , at
        pop rax
        push qword [rax]
        jmp next



native ';' , semicolon
        mov rax, 60
        xor rdi, rdi
        syscall

native ':' , colon
        ;here
        ;mov [state], [state]
        jmp next

native 'q' , quit
        mov rax, 60
        xor rdi, rdi
        syscall
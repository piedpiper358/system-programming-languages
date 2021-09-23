extern  _GLOBAL_OFFSET_TABLE_   

section .data
	align 16
	byte2float:
	%assign i 0 
	%rep	256 
		dd %[i].
	%assign i i+1 
	%endrep
	align 16
	 cn1:
		dd 0.0, 0.393, 0.349, 0.272
	cn2:
		dd 0.0, 0.769, 0.686, 0.543
	cn3:
		dd 0.0, 0.189, 0.168, 0.131
		
	%macro firstfill 3
		lea rax, [rdi + %2 + 3*%3]
		xor rcx, rcx
		mov byte cl, [rax]
		lea rax, [rel byte2float]
		lea rax, [rax + rcx*4]
		;lea rax, [rcx*4 + rel byte2float wrt ..gotoff]
		movss %1, [rax]
		shufps %1, %1, 00h
		
		lea rax, [rdi + %2 + 3]
		xor rcx, rcx
		mov byte cl, [rax]
		lea rax, [rel byte2float]
		lea rax, [rax + rcx*4]
		;lea rax, [rcx*4 + rel byte2float wrt ..gotoff]
		movss xmm7, [rax]
		movss %1, xmm7
	%endmacro
	
	%macro fill_cn 3
		lea rax, [rel cn%2]
		movaps %1, [rax]
		lea rax, [rax + %3*4]
		;lea rax, [%3*4 + rel cn%2 wrt ..gotpc]
		movss xmm7, [rax]
		movss %1, xmm7
	%endmacro

	%macro p1_2byte 0
		cvttss2si rax, xmm3			;r1
		cmp rax, 255
		jle %%skip
		mov rax, 255
	%%skip:
		dec rsp
		mov byte [rsp], al
	%endmacro

	%macro float2byte 2
		shufps %1, %1, 39h
		cvttss2si rax, %1
		cmp rax, 255
		jle %%skip
		mov rax, 255
	%%skip:
		lea rdx, [rdi + %2]
		mov byte [rdx], al
	%endmacro
		
section .text
	global sepia_filter_asm:function
	sepia_filter_asm:
		push rbp
		mov rbp, rsp
		push rbx

		; Computing the number of pixels
		mov dword eax, [rdi]				;width -> rax
		lea rdx, [rdi+4]					;height -> rdx
		mov dword edx, [rdx]
		mul edx						;rax *= rdx -> width *= height
		
		; Load pixel pointer into rdi and compute the end
		lea rdi, [rdi + 8]
		mov rdi, [rdi]
		lea rsi, [3*rax]
		add rsi, rdi	
		
	.loop:
		cmp rdi, rsi
		jge .end

		firstfill xmm0, 0, 0 		;r0r0r0r1
		firstfill xmm1, 1, 0 		;g0g0g0g1
		firstfill xmm2, 2, 0 		;b0b0b0b1
		
		fill_cn xmm3, 1, 1 		;c30 c20 c10 c10 
		fill_cn xmm4, 2, 1 		;c31 c21 c11 c11
		fill_cn xmm5, 3, 1 		;c32 c22 c12 c12	
		
		mulps xmm3, xmm0			;r0*c30 r0*c20 r0*c10 r1*c10
		mulps xmm4, xmm1			;g0*c31 g0*c21 g0*c11 g1*c11
		mulps xmm5, xmm2			;b0*c32 b0*c22 b0*c12 b1*c12
		addps xmm3, xmm4		
		addps xmm3, xmm5			;b0 g0 r0 r1

		p1_2byte
		float2byte xmm3, 0
		float2byte xmm3, 1
		float2byte xmm3, 2

		firstfill xmm0, 0, 2 		;r2r2r2r1
		firstfill xmm1, 1, 2 		;g2g2g2g1
		firstfill xmm2, 2, 2 		;b2b2b2b1

		fill_cn xmm3, 1, 2 		;c30 c20 c10 c20
		fill_cn xmm4, 2, 2 		;c31 c21 c11 c21
		fill_cn xmm5, 3, 2 		;c32 c22 c12 c22

		mulps xmm3, xmm0 			;r2*c30 r2*c20 r2*c10 r1*c20
		mulps xmm4, xmm1 			;g2*c31 g2*c21 g2*c11 g1*c21
		mulps xmm5, xmm2 			;b2*c32 b2*c22 b2*c12 b1*c22
		addps xmm3, xmm4
		addps xmm3, xmm5			;b2 g2 r2 g1
	
		p1_2byte
		float2byte xmm3, 6
		float2byte xmm3, 7
		float2byte xmm3, 8

		firstfill xmm0, 0, 3 		;r3r3r3r1
		firstfill xmm1, 1, 3 		;g3g3g3g1
		firstfill xmm2, 2, 3 		;b3b3b3b1

		fill_cn xmm3, 1, 3 		;c30 c20 c10 c30
		fill_cn xmm4, 2, 3 		;c31 c21 c11 c31
		fill_cn xmm5, 3, 3 		;c32 c22 c12 c32

		mulps xmm3, xmm0 			;r3*c30 r3*c20 r3*c10 r1*c30
		mulps xmm4, xmm1 			;r3*c31 r3*c21 r3*c11 g1*c31
		mulps xmm5, xmm2 			;r3*c31 r3*c22 r3*c12 b1*c32
		addps xmm3, xmm4
		addps xmm3, xmm5			;b3 g3 r3 b1

		p1_2byte
		float2byte xmm3, 9
		float2byte xmm3, 10
		float2byte xmm3, 11

		;Unwinding stack to get pixel 1 values r1 g1 b1
		lea rdx, [rdi + 5]
		mov byte al, [rsp]
		mov byte [rdx], al
		inc rsp
		dec rdx
		mov byte al, [rsp]
		mov byte [rdx], al
		inc rsp
		dec rdx
		mov byte al, [rsp]
		mov byte [rdx], al
		inc rsp

		add rdi, 12
		jmp .loop
	.end:
		pop rbx
		leave
		ret
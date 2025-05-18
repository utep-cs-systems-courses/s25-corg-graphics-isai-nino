	.arch msp430g2553
	.p2align 1,0

	.text
	.global set_boundaries_s
	.extern platCol		     	; Var in platform.c
	.extern width		    	; Var in platform.c
	.extern set_plat_color	    	; Function in platform.c
	.equ screenWidth, 128   	; \
	.equ COLOR_RED, 0x001f  	;   constants
	.equ COLOR_HOT_PINK, 0xb35f     ; /
	
set_boundaries_s:
	mov.b &platCol, r13	; r13 = platCol
	cmp.b #2, r13		; platCol - 2
	jc check_right		; Jump if platCol >= 2
	mov.b #2, &platCol	; platCol = 2
	mov #COLOR_RED, r12	; r12 = COLOR_RED
	call #set_plat_color	; set_plat_color(COLOR_RED)
	jmp Out

check_right:
	mov.b &width, r14	; r14 = width
	mov #screenWidth, r13 	; r13 = screenWidth
	sub r14, r13		; r13 = screenWidth - width
	mov.b &platCol, r12	; r12 = platCol
	cmp.b r12, r13		; If platCol <= (screenWidth - width)
	jc Else			; 
	mov.b r13, &platCol	; platCol = screenWidth - width
	mov #COLOR_RED, r12	; r12 = COLOR_RED
	call #set_plat_color	; set_plat_color(COLOR_RED)
	jmp Out
Else:
	mov #COLOR_HOT_PINK, r12 ; Default platform color
	call #set_plat_color
Out:
	ret

	

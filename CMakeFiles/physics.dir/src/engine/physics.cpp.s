	.file	"physics.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN14Physics_engine16update_positionsER6Engine
	.type	_ZN14Physics_engine16update_positionsER6Engine, @function
_ZN14Physics_engine16update_positionsER6Engine:
.LFB11945:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	call	_ZN6Engine12get_entitiesEv@PLT
	movq	(%rax), %rbx
	movq	8(%rax), %r12
	cmpq	%rbx, %r12
	je	.L1
	.p2align 4,,10
	.p2align 3
.L3:
	movq	(%rbx), %rdi
	addq	$16, %rbx
	movq	%rbp, %rsi
	movq	(%rdi), %rax
	call	*24(%rax)
	cmpq	%rbx, %r12
	jne	.L3
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11945:
	.size	_ZN14Physics_engine16update_positionsER6Engine, .-_ZN14Physics_engine16update_positionsER6Engine
	.align 2
	.p2align 4
	.globl	_ZN14Physics_engine11pre_physicsER6Engine
	.type	_ZN14Physics_engine11pre_physicsER6Engine, @function
_ZN14Physics_engine11pre_physicsER6Engine:
.LFB11964:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	call	_ZN6Engine12get_entitiesEv@PLT
	movq	(%rax), %rbx
	movq	8(%rax), %r12
	cmpq	%rbx, %r12
	je	.L7
	.p2align 4,,10
	.p2align 3
.L9:
	movq	(%rbx), %rdi
	addq	$16, %rbx
	movq	%rbp, %rsi
	movq	(%rdi), %rax
	call	*16(%rax)
	cmpq	%rbx, %r12
	jne	.L9
.L7:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11964:
	.size	_ZN14Physics_engine11pre_physicsER6Engine, .-_ZN14Physics_engine11pre_physicsER6Engine
	.align 2
	.p2align 4
	.globl	_ZN14Physics_engine12post_physicsER6Engine
	.type	_ZN14Physics_engine12post_physicsER6Engine, @function
_ZN14Physics_engine12post_physicsER6Engine:
.LFB11965:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	call	_ZN6Engine12get_entitiesEv@PLT
	movq	(%rax), %rbx
	movq	8(%rax), %r12
	cmpq	%rbx, %r12
	je	.L12
	.p2align 4,,10
	.p2align 3
.L14:
	movq	(%rbx), %rdi
	addq	$16, %rbx
	movq	%rbp, %rsi
	movq	(%rdi), %rax
	call	*40(%rax)
	cmpq	%rbx, %r12
	jne	.L14
.L12:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11965:
	.size	_ZN14Physics_engine12post_physicsER6Engine, .-_ZN14Physics_engine12post_physicsER6Engine
	.section	.text._ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv,"axG",@progbits,_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
	.type	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv, @function
_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv:
.LFB12599:
	.cfi_startproc
	endbr64
	cmpb	$0, __libc_single_threaded(%rip)
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	je	.L18
	movl	8(%rdi), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rdi)
.L19:
	cmpl	$1, %eax
	je	.L26
.L17:
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L26:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L22
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L23:
	cmpl	$1, %eax
	jne	.L17
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	movq	24(%rax), %rax
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L18:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rdi)
	jmp	.L19
	.p2align 4,,10
	.p2align 3
.L22:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L23
	.cfi_endproc
.LFE12599:
	.size	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv, .-_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB0:
	.text
.LHOTB0:
	.align 2
	.p2align 4
	.globl	_ZN14Physics_engine18compute_collisionsER6Engine
	.type	_ZN14Physics_engine18compute_collisionsER6Engine, @function
_ZN14Physics_engine18compute_collisionsER6Engine:
.LFB11950:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA11950
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rsi, %rdi
	movq	%rsi, %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
.LEHB0:
	call	_ZN6Engine12get_entitiesEv@PLT
.LEHE0:
	movq	$0, 8(%rsp)
	movq	8(%rax), %rcx
	movq	%rax, %rbp
	movq	(%rax), %rax
	cmpq	%rcx, %rax
	je	.L27
	leaq	32(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L28:
	addq	$1, 8(%rsp)
	subq	%rax, %rcx
	movq	8(%rsp), %rbx
	sarq	$4, %rcx
	cmpq	%rcx, %rbx
	jnb	.L27
	movq	%rbx, %r13
	salq	$4, %r13
	subq	$16, %r13
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L39:
	movq	8(%rbp), %rcx
	addq	$1, %rbx
	movq	%rcx, %rdx
	subq	%rax, %rdx
	sarq	$4, %rdx
	cmpq	%rdx, %rbx
	jnb	.L100
.L58:
	movq	%rbx, %r12
	movq	(%rax,%r13), %rdi
	salq	$4, %r12
	addq	%r12, %rax
	movq	(%rax), %rdx
	movq	8(%rax), %rax
	movq	%rdx, 32(%rsp)
	movq	%rax, 40(%rsp)
	testq	%rax, %rax
	je	.L30
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L31
	addl	$1, 8(%rax)
.L30:
	movq	%r14, %rsi
.LEHB1:
	call	_ZNK6Entity8collidesESt10shared_ptrIS_E@PLT
.LEHE1:
	movq	40(%rsp), %rdi
	movl	%eax, %edx
	testq	%rdi, %rdi
	je	.L33
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L34
	movl	8(%rdi), %eax
	leal	-1(%rax), %ecx
	movl	%ecx, 8(%rdi)
.L35:
	cmpl	$1, %eax
	je	.L101
.L33:
	movq	0(%rbp), %rax
	testb	%dl, %dl
	je	.L39
	movq	(%rax,%r13), %rdi
	addq	%r12, %rax
	movq	(%rdi), %rdx
	movq	32(%rdx), %rcx
	movq	(%rax), %rdx
	movq	8(%rax), %rax
	movq	%rdx, 32(%rsp)
	movq	%rax, 40(%rsp)
	testq	%rax, %rax
	je	.L40
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L41
	addl	$1, 8(%rax)
.L40:
	movq	%r14, %rdx
	movq	%r15, %rsi
.LEHB2:
	call	*%rcx
.LEHE2:
	movq	40(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L43
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L44
	movl	8(%rdi), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rdi)
.L45:
	cmpl	$1, %eax
	je	.L102
.L43:
	movq	0(%rbp), %rax
	movq	(%rax,%r12), %rdi
	addq	%r13, %rax
	movq	(%rdi), %rdx
	movq	32(%rdx), %rcx
	movq	(%rax), %rdx
	movq	8(%rax), %rax
	movq	%rdx, 32(%rsp)
	movq	%rax, 40(%rsp)
	testq	%rax, %rax
	je	.L49
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L50
	addl	$1, 8(%rax)
.L49:
	movq	%r14, %rdx
	movq	%r15, %rsi
.LEHB3:
	call	*%rcx
.LEHE3:
	movq	40(%rsp), %r12
	testq	%r12, %r12
	je	.L99
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L53
	movl	8(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%r12)
.L54:
	cmpl	$1, %eax
	je	.L96
.L99:
	movq	0(%rbp), %rax
	jmp	.L39
	.p2align 4,,10
	.p2align 3
.L31:
	lock addl	$1, 8(%rax)
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L101:
	movq	(%rdi), %rax
	movb	%dl, 31(%rsp)
	movq	%rdi, 16(%rsp)
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	movq	16(%rsp), %rdi
	movzbl	31(%rsp), %edx
	je	.L37
	movl	12(%rdi), %eax
	leal	-1(%rax), %ecx
	movl	%ecx, 12(%rdi)
.L38:
	cmpl	$1, %eax
	jne	.L33
	movq	(%rdi), %rax
	movb	%dl, 16(%rsp)
	call	*24(%rax)
	movzbl	16(%rsp), %edx
	jmp	.L33
	.p2align 4,,10
	.p2align 3
.L34:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rdi)
	jmp	.L35
	.p2align 4,,10
	.p2align 3
.L100:
	cmpq	%rdx, 8(%rsp)
	jb	.L28
	.p2align 4,,10
	.p2align 3
.L27:
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L103
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L41:
	.cfi_restore_state
	lock addl	$1, 8(%rax)
	jmp	.L40
	.p2align 4,,10
	.p2align 3
.L50:
	lock addl	$1, 8(%rax)
	jmp	.L49
	.p2align 4,,10
	.p2align 3
.L102:
	movq	(%rdi), %rax
	movq	%rdi, 16(%rsp)
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	movq	16(%rsp), %rdi
	je	.L47
	movl	12(%rdi), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rdi)
.L48:
	cmpl	$1, %eax
	jne	.L43
	movq	(%rdi), %rax
	call	*24(%rax)
	jmp	.L43
	.p2align 4,,10
	.p2align 3
.L37:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rdi)
	jmp	.L38
	.p2align 4,,10
	.p2align 3
.L96:
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L56
	movl	12(%r12), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%r12)
.L57:
	cmpl	$1, %eax
	jne	.L99
	movq	(%r12), %rax
	movq	%r12, %rdi
	call	*24(%rax)
	jmp	.L99
	.p2align 4,,10
	.p2align 3
.L53:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%r12)
	jmp	.L54
	.p2align 4,,10
	.p2align 3
.L44:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rdi)
	jmp	.L45
	.p2align 4,,10
	.p2align 3
.L47:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rdi)
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L56:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%r12)
	jmp	.L57
.L103:
	call	__stack_chk_fail@PLT
.L69:
	endbr64
	movq	%rax, %rbp
	jmp	.L63
.L68:
	endbr64
	movq	%rax, %rbp
	jmp	.L61
.L67:
	endbr64
	movq	%rax, %rbp
	jmp	.L59
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA11950:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE11950-.LLSDACSB11950
.LLSDACSB11950:
	.uleb128 .LEHB0-.LFB11950
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB11950
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L67-.LFB11950
	.uleb128 0
	.uleb128 .LEHB2-.LFB11950
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L68-.LFB11950
	.uleb128 0
	.uleb128 .LEHB3-.LFB11950
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L69-.LFB11950
	.uleb128 0
.LLSDACSE11950:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC11950
	.type	_ZN14Physics_engine18compute_collisionsER6Engine.cold, @function
_ZN14Physics_engine18compute_collisionsER6Engine.cold:
.LFSB11950:
.L63:
	.cfi_def_cfa_offset 128
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	40(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L64
	call	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
.L64:
	movq	%rbp, %rdi
.LEHB4:
	call	_Unwind_Resume@PLT
.L61:
	movq	40(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L62
	call	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
.L62:
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.L59:
	movq	40(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L60
	call	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
.L60:
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE4:
	.cfi_endproc
.LFE11950:
	.section	.gcc_except_table
.LLSDAC11950:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC11950-.LLSDACSBC11950
.LLSDACSBC11950:
	.uleb128 .LEHB4-.LCOLDB0
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSEC11950:
	.section	.text.unlikely
	.text
	.size	_ZN14Physics_engine18compute_collisionsER6Engine, .-_ZN14Physics_engine18compute_collisionsER6Engine
	.section	.text.unlikely
	.size	_ZN14Physics_engine18compute_collisionsER6Engine.cold, .-_ZN14Physics_engine18compute_collisionsER6Engine.cold
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZN14Physics_engine16update_positionsER6Engine, @function
_GLOBAL__sub_I__ZN14Physics_engine16update_positionsER6Engine:
.LFB12973:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	_ZStL8__ioinit(%rip), %rbp
	movq	%rbp, %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	movq	%rbp, %rsi
	popq	%rbp
	.cfi_def_cfa_offset 8
	leaq	__dso_handle(%rip), %rdx
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE12973:
	.size	_GLOBAL__sub_I__ZN14Physics_engine16update_positionsER6Engine, .-_GLOBAL__sub_I__ZN14Physics_engine16update_positionsER6Engine
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN14Physics_engine16update_positionsER6Engine
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:

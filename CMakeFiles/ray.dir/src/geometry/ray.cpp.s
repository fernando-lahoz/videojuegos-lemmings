	.file	"ray.cpp"
	.text
	.section	.rodata._ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%f"
	.section	.text._ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0,"axG",@progbits,_ZlsIfERSoS0_RK7Vector3IT_E,comdat
	.p2align 4
	.type	_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0, @function
_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0:
.LFB4580:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbx
	subq	$208, %rsp
	.cfi_offset 3, -48
	movq	%r8, -176(%rbp)
	movq	%r9, -168(%rbp)
	testb	%al, %al
	je	.L2
	movaps	%xmm0, -160(%rbp)
	movaps	%xmm1, -144(%rbp)
	movaps	%xmm2, -128(%rbp)
	movaps	%xmm3, -112(%rbp)
	movaps	%xmm4, -96(%rbp)
	movaps	%xmm5, -80(%rbp)
	movaps	%xmm6, -64(%rbp)
	movaps	%xmm7, -48(%rbp)
.L2:
	movq	%fs:40, %rax
	movq	%rax, -216(%rbp)
	movq	%rsp, %rax
	cmpq	%rax, %rsp
	je	.L4
.L20:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%rax, %rsp
	jne	.L20
.L4:
	subq	$80, %rsp
	orq	$0, 72(%rsp)
	movl	$58, %ecx
	movl	$1, %edx
	movl	$58, %esi
	leaq	.LC0(%rip), %r8
	leaq	15(%rsp), %r13
	leaq	16(%rbp), %rax
	movl	$32, -240(%rbp)
	andq	$-16, %r13
	movq	%rax, -232(%rbp)
	leaq	-240(%rbp), %r9
	leaq	-208(%rbp), %rax
	movq	%r13, %rdi
	movq	%rax, -224(%rbp)
	movl	$48, -236(%rbp)
	call	__vsnprintf_chk@PLT
	movslq	%eax, %r14
	leaq	16(%r12), %rax
	movq	%rax, (%r12)
	movq	%r14, %rbx
	cmpl	$15, %r14d
	jle	.L6
	leaq	1(%r14), %rdi
	call	_Znwm@PLT
	movq	%r14, 16(%r12)
	movq	%rax, (%r12)
.L6:
	cmpl	$8, %ebx
	jnb	.L7
	testb	$4, %bl
	jne	.L21
	testl	%ebx, %ebx
	je	.L8
	movzbl	0(%r13), %edx
	movb	%dl, (%rax)
	testb	$2, %bl
	jne	.L22
.L8:
	movq	(%r12), %rax
	movq	%r14, 8(%r12)
	movb	$0, (%rax,%r14)
	movq	-216(%rbp), %rax
	subq	%fs:40, %rax
	jne	.L23
	leaq	-32(%rbp), %rsp
	movq	%r12, %rax
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L7:
	.cfi_restore_state
	movq	0(%r13), %rdx
	leaq	8(%rax), %rdi
	movq	%r13, %rsi
	andq	$-8, %rdi
	movq	%rdx, (%rax)
	movl	%ebx, %edx
	movq	-8(%r13,%rdx), %rcx
	movq	%rcx, -8(%rax,%rdx)
	subq	%rdi, %rax
	leal	(%rbx,%rax), %ecx
	subq	%rax, %rsi
	shrl	$3, %ecx
	rep movsq
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L22:
	movl	%ebx, %ebx
	movzwl	-2(%r13,%rbx), %edx
	movw	%dx, -2(%rax,%rbx)
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L21:
	movl	0(%r13), %edx
	movl	%ebx, %ebx
	movl	%edx, (%rax)
	movl	-4(%r13,%rbx), %edx
	movl	%edx, -4(%rax,%rbx)
	jmp	.L8
.L23:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE4580:
	.size	_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0, .-_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Ray[origin=%f, %f, %f, direction=%f, %f, %f, maximum_offset=%f]\n"
	.text
	.align 2
	.p2align 4
	.globl	_ZNK3Ray5printEv
	.type	_ZNK3Ray5printEv, @function
_ZNK3Ray5printEv:
.LFB3811:
	.cfi_startproc
	endbr64
	pxor	%xmm0, %xmm0
	pxor	%xmm6, %xmm6
	pxor	%xmm5, %xmm5
	movl	$7, %eax
	pxor	%xmm4, %xmm4
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	cvtss2sd	(%rdi), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	36(%rdi), %xmm6
	cvtss2sd	20(%rdi), %xmm5
	cvtss2sd	16(%rdi), %xmm4
	cvtss2sd	12(%rdi), %xmm3
	cvtss2sd	8(%rdi), %xmm2
	cvtss2sd	4(%rdi), %xmm1
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	jmp	__printf_chk@PLT
	.cfi_endproc
.LFE3811:
	.size	_ZNK3Ray5printEv, .-_ZNK3Ray5printEv
	.section	.rodata._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm.str1.1,"aMS",@progbits,1
.LC2:
	.string	"basic_string::_M_create"
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm:
.LFB4452:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%r8, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rsi, %r12
	addq	%rdx, %rsi
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%r8, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	subq	%rdx, %rbp
	leaq	16(%rbx), %r13
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	8(%rdi), %rax
	movq	%rsi, 24(%rsp)
	movq	%rax, %rdi
	addq	%rax, %rbp
	subq	%rsi, %rdi
	movq	%rdi, 8(%rsp)
	cmpq	(%rbx), %r13
	je	.L38
	movq	16(%rbx), %rax
.L26:
	testq	%rbp, %rbp
	js	.L52
	cmpq	%rax, %rbp
	jbe	.L28
	addq	%rax, %rax
	cmpq	%rax, %rbp
	jnb	.L28
	testq	%rax, %rax
	js	.L29
	movq	%rax, %rbp
	.p2align 4,,10
	.p2align 3
.L28:
	movq	%rbp, %rdi
	addq	$1, %rdi
	js	.L29
	movq	%rcx, 16(%rsp)
	call	_Znwm@PLT
	testq	%r12, %r12
	movq	16(%rsp), %rcx
	movq	%rax, %r15
	je	.L31
	movq	(%rbx), %rsi
	cmpq	$1, %r12
	je	.L53
	movq	%r12, %rdx
	movq	%rax, %rdi
	movq	%rcx, 16(%rsp)
	call	memcpy@PLT
	movq	16(%rsp), %rcx
.L31:
	testq	%rcx, %rcx
	je	.L33
	testq	%r14, %r14
	je	.L33
	leaq	(%r15,%r12), %rdi
	cmpq	$1, %r14
	je	.L54
	movq	%r14, %rdx
	movq	%rcx, %rsi
	call	memcpy@PLT
.L33:
	movq	8(%rsp), %rax
	movq	(%rbx), %r9
	testq	%rax, %rax
	je	.L35
.L56:
	movq	24(%rsp), %rsi
	leaq	(%r12,%r14), %r8
	leaq	(%r15,%r8), %rdi
	addq	%r9, %rsi
	cmpq	$1, %rax
	je	.L55
	movq	%rax, %rdx
	movq	%r9, 16(%rsp)
	call	memcpy@PLT
	movq	16(%rsp), %r9
.L35:
	cmpq	%r9, %r13
	je	.L37
.L57:
	movq	16(%rbx), %rax
	movq	%r9, %rdi
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L37:
	movq	%r15, (%rbx)
	movq	%rbp, 16(%rbx)
	addq	$40, %rsp
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
.L29:
	.cfi_restore_state
	call	_ZSt17__throw_bad_allocv@PLT
	.p2align 4,,10
	.p2align 3
.L38:
	movl	$15, %eax
	jmp	.L26
	.p2align 4,,10
	.p2align 3
.L53:
	movzbl	(%rsi), %eax
	movb	%al, (%r15)
	jmp	.L31
	.p2align 4,,10
	.p2align 3
.L54:
	movzbl	(%rcx), %eax
	movq	(%rbx), %r9
	movb	%al, (%rdi)
	movq	8(%rsp), %rax
	testq	%rax, %rax
	je	.L35
	jmp	.L56
	.p2align 4,,10
	.p2align 3
.L55:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	cmpq	%r9, %r13
	jne	.L57
	jmp	.L37
.L52:
	leaq	.LC2(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE4452:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.section	.rodata._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm.str1.1,"aMS",@progbits,1
.LC3:
	.string	"basic_string::_M_replace"
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm:
.LFB4453:
	.cfi_startproc
	endbr64
	movabsq	$9223372036854775807, %rax
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rdx, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	addq	%r13, %rax
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %rdx
	subq	%rdx, %rax
	cmpq	%rax, %r8
	ja	.L102
	movq	%r8, %rbp
	movq	(%rdi), %rax
	movq	%rcx, %r15
	leaq	16(%rdi), %rcx
	subq	%r13, %rbp
	movq	%rdi, %r12
	movq	%r8, %r14
	leaq	(%rdx,%rbp), %rbx
	cmpq	%rcx, %rax
	je	.L81
	movq	16(%rdi), %rcx
.L60:
	cmpq	%rbx, %rcx
	jb	.L61
	leaq	(%rax,%rsi), %r8
	movq	%rdx, %r9
	addq	%r13, %rsi
	subq	%rsi, %r9
	cmpq	%r15, %rax
	jbe	.L103
.L62:
	testq	%r9, %r9
	je	.L65
	cmpq	%r14, %r13
	je	.L65
	leaq	(%r8,%r13), %rsi
	leaq	(%r8,%r14), %rdi
	cmpq	$1, %r9
	je	.L104
	movq	%r9, %rdx
	movq	%r8, 8(%rsp)
	call	memmove@PLT
	movq	8(%rsp), %r8
.L65:
	testq	%r14, %r14
	je	.L68
	cmpq	$1, %r14
	je	.L101
	movq	%r14, %rdx
	movq	%r15, %rsi
	movq	%r8, %rdi
	call	memcpy@PLT
.L68:
	movq	(%r12), %rax
	movq	%rbx, 8(%r12)
	movb	$0, (%rax,%rbx)
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rax
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
.L103:
	.cfi_restore_state
	addq	%rdx, %rax
	cmpq	%rax, %r15
	ja	.L62
	leaq	-1(%r14), %rax
	cmpq	%rax, %r13
	jbe	.L64
	cmpq	$1, %r14
	je	.L105
	movq	%r8, %rdi
	movq	%r14, %rdx
	movq	%r15, %rsi
	movq	%r9, 8(%rsp)
	call	memmove@PLT
	movq	8(%rsp), %r9
	movq	%rax, %r8
.L64:
	testq	%r9, %r9
	je	.L71
	cmpq	%r14, %r13
	je	.L71
	leaq	(%r8,%r13), %rsi
	leaq	(%r8,%r14), %rdi
	cmpq	$1, %r9
	je	.L106
	movq	%r9, %rdx
	movq	%r8, 8(%rsp)
	call	memmove@PLT
	movq	8(%rsp), %r8
.L71:
	cmpq	%r14, %r13
	jnb	.L68
	addq	%r8, %r13
	leaq	(%r15,%r14), %rax
	cmpq	%rax, %r13
	jnb	.L107
	cmpq	%r15, %r13
	ja	.L76
	leaq	(%r15,%rbp), %rsi
	cmpq	$1, %r14
	je	.L108
	movq	%r14, %rdx
	movq	%r8, %rdi
	call	memcpy@PLT
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L61:
	movq	%r14, %r8
	movq	%r15, %rcx
	movq	%r13, %rdx
	movq	%r12, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L101:
	movzbl	(%r15), %eax
	movb	%al, (%r8)
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L104:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L65
	.p2align 4,,10
	.p2align 3
.L81:
	movl	$15, %ecx
	jmp	.L60
	.p2align 4,,10
	.p2align 3
.L107:
	cmpq	$1, %r14
	je	.L101
	movq	%r14, %rdx
	movq	%r15, %rsi
	movq	%r8, %rdi
	call	memmove@PLT
	jmp	.L68
	.p2align 4,,10
	.p2align 3
.L106:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L71
	.p2align 4,,10
	.p2align 3
.L105:
	movzbl	(%r15), %eax
	movb	%al, (%r8)
	jmp	.L64
	.p2align 4,,10
	.p2align 3
.L76:
	subq	%r15, %r13
	cmpq	$1, %r13
	je	.L109
	testq	%r13, %r13
	je	.L79
	movq	%r8, %rdi
	movq	%r13, %rdx
	movq	%r15, %rsi
	call	memmove@PLT
	movq	%rax, %r8
.L79:
	movq	%r14, %rdx
	leaq	(%r8,%r14), %rsi
	leaq	(%r8,%r13), %rdi
	subq	%r13, %rdx
	cmpq	$1, %rdx
	je	.L110
	testq	%rdx, %rdx
	je	.L68
	call	memcpy@PLT
	jmp	.L68
.L109:
	movzbl	(%r15), %eax
	movb	%al, (%r8)
	jmp	.L79
.L110:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L68
.L108:
	movzbl	(%rsi), %eax
	movb	%al, (%r8)
	jmp	.L68
.L102:
	leaq	.LC3(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE4453:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
	.section	.rodata._ZlsIfERSoS0_RK7Vector3IT_E.str1.1,"aMS",@progbits,1
.LC8:
	.string	"vector["
.LC9:
	.string	"basic_string::append"
.LC10:
	.string	", "
.LC11:
	.string	"]"
	.section	.text._ZlsIfERSoS0_RK7Vector3IT_E,"axG",@progbits,_ZlsIfERSoS0_RK7Vector3IT_E,comdat
	.p2align 4
	.weak	_ZlsIfERSoS0_RK7Vector3IT_E
	.type	_ZlsIfERSoS0_RK7Vector3IT_E, @function
_ZlsIfERSoS0_RK7Vector3IT_E:
.LFB4174:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA4174
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %r15
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
	subq	$376, %rsp
	.cfi_def_cfa_offset 432
	movss	(%rsi), %xmm4
	movss	8(%rsi), %xmm3
	movq	%fs:40, %rax
	movq	%rax, 360(%rsp)
	xorl	%eax, %eax
	leaq	48(%rsp), %rax
	movb	$0, 48(%rsp)
	movl	4(%rsi), %ebx
	movss	.LC7(%rip), %xmm1
	movss	.LC6(%rip), %xmm0
	movss	%xmm4, 8(%rsp)
	andps	%xmm0, %xmm4
	movq	%rax, (%rsp)
	comiss	%xmm4, %xmm1
	movq	%rax, 32(%rsp)
	movq	$0, 40(%rsp)
	jbe	.L112
	pxor	%xmm7, %xmm7
	movss	%xmm7, 8(%rsp)
.L112:
	movd	%ebx, %xmm2
	andps	%xmm0, %xmm2
	comiss	%xmm2, %xmm1
	jbe	.L114
	movl	.LC4(%rip), %ebx
.L114:
	andps	%xmm3, %xmm0
	pxor	%xmm2, %xmm2
	comiss	%xmm0, %xmm1
	ja	.L116
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm3, %xmm2
.L116:
	movq	vsnprintf@GOTPCREL(%rip), %rbp
	leaq	.LC0(%rip), %r13
	movapd	%xmm2, %xmm0
	leaq	256(%rsp), %rdi
	movq	%r13, %rcx
	movl	$58, %edx
	movl	$1, %eax
	movq	%rdi, 24(%rsp)
	movq	%rbp, %rsi
.LEHB0:
	call	_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0
.LEHE0:
	movd	%ebx, %xmm5
	pxor	%xmm0, %xmm0
	movq	%r13, %rcx
	movl	$58, %edx
	leaq	160(%rsp), %r12
	movq	%rbp, %rsi
	movl	$1, %eax
	cvtss2sd	%xmm5, %xmm0
	movq	%r12, %rdi
.LEHB1:
	call	_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0
.LEHE1:
	leaq	64(%rsp), %r14
	pxor	%xmm0, %xmm0
	movq	%r13, %rcx
	movq	%rbp, %rsi
	movl	$58, %edx
	movq	%r14, %rdi
	movl	$1, %eax
	cvtss2sd	8(%rsp), %xmm0
.LEHB2:
	call	_ZN9__gnu_cxx12__to_xstringINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEcEET_PFiPT0_mPKS8_P13__va_list_tagEmSB_z.constprop.0
.LEHE2:
	movl	$7, %r8d
	xorl	%edx, %edx
	xorl	%esi, %esi
	movq	%r14, %rdi
	leaq	.LC8(%rip), %rcx
.LEHB3:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
.LEHE3:
	leaq	112(%rsp), %rbx
	leaq	16(%rax), %rdx
	movq	%rbx, 96(%rsp)
	movq	(%rax), %rcx
	cmpq	%rdx, %rcx
	je	.L231
	movq	%rcx, 96(%rsp)
	movq	16(%rax), %rcx
	movq	%rcx, 112(%rsp)
.L118:
	movq	8(%rax), %rcx
	movb	$0, 16(%rax)
	movq	%rcx, 104(%rsp)
	movq	$0, 8(%rax)
	movq	104(%rsp), %rbp
	movq	%rdx, (%rax)
	movabsq	$9223372036854775807, %rax
	subq	%rbp, %rax
	cmpq	$1, %rax
	jbe	.L232
	movq	96(%rsp), %rdx
	movl	$15, %eax
	leaq	2(%rbp), %r13
	cmpq	%rbx, %rdx
	cmovne	112(%rsp), %rax
	cmpq	%rax, %r13
	ja	.L121
	movl	$8236, %ecx
	movw	%cx, (%rdx,%rbp)
.L122:
	movq	96(%rsp), %rax
	movq	%r13, 104(%rsp)
	leaq	144(%rsp), %r13
	movb	$0, 2(%rax,%rbp)
	movq	96(%rsp), %rcx
	movq	%r13, 128(%rsp)
	cmpq	%rbx, %rcx
	je	.L233
	movq	104(%rsp), %rsi
	movq	112(%rsp), %rax
	cmpq	%r13, %rcx
	movl	$15, %edx
	movq	168(%rsp), %r8
	movq	%rbx, 96(%rsp)
	movq	%rcx, 128(%rsp)
	movq	%rsi, 136(%rsp)
	leaq	(%rsi,%r8), %rbp
	movq	$0, 104(%rsp)
	movb	$0, 112(%rsp)
	movq	%rax, 144(%rsp)
	cmove	%rdx, %rax
.L124:
	movq	160(%rsp), %r9
	cmpq	%rbp, %rax
	jnb	.L125
	leaq	176(%rsp), %rax
	cmpq	%rax, %r9
	movq	%rax, 16(%rsp)
	movl	$15, %eax
	cmovne	176(%rsp), %rax
	cmpq	%rbp, %rax
	jnb	.L234
	leaq	128(%rsp), %rdi
	movq	%r9, %rcx
	xorl	%edx, %edx
.LEHB4:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.LEHE4:
	movq	128(%rsp), %rcx
.L131:
	movq	%rbp, 136(%rsp)
	movb	$0, (%rcx,%rbp)
	movq	128(%rsp), %rax
	leaq	208(%rsp), %rbp
	movq	%rbp, 192(%rsp)
	cmpq	%r13, %rax
	je	.L235
	movq	%rax, 192(%rsp)
	movq	144(%rsp), %rax
	movq	%rax, 208(%rsp)
.L136:
	movq	136(%rsp), %rsi
	movq	%r13, 128(%rsp)
	movq	$0, 136(%rsp)
	movq	%rsi, 200(%rsp)
	movb	$0, 144(%rsp)
.L135:
	movabsq	$9223372036854775807, %rax
	subq	%rsi, %rax
	cmpq	$1, %rax
	jbe	.L236
	movq	192(%rsp), %rdx
	movl	$15, %eax
	leaq	2(%rsi), %r12
	cmpq	%rbp, %rdx
	cmovne	208(%rsp), %rax
	cmpq	%rax, %r12
	ja	.L139
	movl	$8236, %eax
	movw	%ax, (%rdx,%rsi)
.L140:
	movq	192(%rsp), %rax
	movq	%r12, 200(%rsp)
	leaq	240(%rsp), %r14
	movb	$0, (%rax,%r12)
	movq	192(%rsp), %rcx
	movq	%r14, 224(%rsp)
	cmpq	%rbp, %rcx
	je	.L237
	movq	200(%rsp), %rsi
	movq	208(%rsp), %rax
	cmpq	%r14, %rcx
	movl	$15, %edx
	movq	264(%rsp), %r8
	movq	%rcx, 224(%rsp)
	movq	%rsi, 232(%rsp)
	movq	%rbp, 192(%rsp)
	leaq	(%rsi,%r8), %r12
	movq	$0, 200(%rsp)
	movb	$0, 208(%rsp)
	movq	%rax, 240(%rsp)
	cmove	%rdx, %rax
.L142:
	movq	256(%rsp), %r9
	cmpq	%r12, %rax
	jnb	.L143
	leaq	272(%rsp), %rax
	cmpq	%rax, %r9
	movq	%rax, 8(%rsp)
	movl	$15, %eax
	cmovne	272(%rsp), %rax
	cmpq	%r12, %rax
	jnb	.L238
	leaq	224(%rsp), %rdi
	movq	%r9, %rcx
	xorl	%edx, %edx
.LEHB5:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.LEHE5:
	movq	224(%rsp), %rcx
.L149:
	movq	%r12, 232(%rsp)
	movb	$0, (%rcx,%r12)
	movq	224(%rsp), %rax
	leaq	304(%rsp), %r12
	movq	%r12, 288(%rsp)
	cmpq	%r14, %rax
	je	.L239
	movq	%rax, 288(%rsp)
	movq	240(%rsp), %rax
	movq	%rax, 304(%rsp)
.L154:
	movq	232(%rsp), %rsi
	movq	%r14, 224(%rsp)
	movq	$0, 232(%rsp)
	movq	%rsi, 296(%rsp)
	movb	$0, 240(%rsp)
.L153:
	movabsq	$9223372036854775807, %rax
	cmpq	%rax, %rsi
	je	.L240
	movq	288(%rsp), %rdx
	movl	$15, %eax
	leaq	1(%rsi), %rcx
	movq	%rcx, 24(%rsp)
	cmpq	%r12, %rdx
	cmovne	304(%rsp), %rax
	cmpq	%rax, %rcx
	ja	.L157
	movb	$93, (%rdx,%rsi)
.L158:
	movq	24(%rsp), %rdx
	movq	288(%rsp), %rax
	leaq	336(%rsp), %rcx
	movq	%rdx, 296(%rsp)
	movb	$0, (%rax,%rdx)
	movq	288(%rsp), %rax
	movq	%rcx, 320(%rsp)
	cmpq	%r12, %rax
	je	.L241
	movq	304(%rsp), %rsi
	movq	296(%rsp), %rdx
	movq	%rax, 320(%rsp)
	movq	%r12, 288(%rsp)
	movq	32(%rsp), %rdi
	movq	%rsi, 336(%rsp)
	movq	%rdx, 328(%rsp)
	movq	$0, 296(%rsp)
	movb	$0, 304(%rsp)
	cmpq	%rcx, %rax
	je	.L160
	movq	%rdx, %xmm0
	movq	%rsi, %xmm6
	punpcklqdq	%xmm6, %xmm0
	cmpq	(%rsp), %rdi
	je	.L242
	movq	48(%rsp), %r8
	movq	%rax, 32(%rsp)
	movq	%rdx, 40(%rsp)
	movq	%rsi, 48(%rsp)
	testq	%rdi, %rdi
	je	.L166
	movq	%rdi, 320(%rsp)
	movq	%r8, 336(%rsp)
.L164:
	movq	$0, 328(%rsp)
	movb	$0, (%rdi)
	movq	320(%rsp), %rdi
	cmpq	%rcx, %rdi
	je	.L167
	movq	336(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L167:
	movq	288(%rsp), %rdi
	cmpq	%r12, %rdi
	je	.L168
	movq	304(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L168:
	movq	224(%rsp), %rdi
	cmpq	%r14, %rdi
	je	.L169
	movq	240(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L169:
	movq	192(%rsp), %rdi
	cmpq	%rbp, %rdi
	je	.L170
	movq	208(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L170:
	movq	128(%rsp), %rdi
	cmpq	%r13, %rdi
	je	.L171
	movq	144(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L171:
	movq	96(%rsp), %rdi
	cmpq	%rbx, %rdi
	je	.L172
	movq	112(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L172:
	movq	64(%rsp), %rdi
	leaq	80(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L173
	movq	80(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L173:
	movq	160(%rsp), %rdi
	cmpq	16(%rsp), %rdi
	je	.L174
	movq	176(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L174:
	movq	256(%rsp), %rdi
	cmpq	8(%rsp), %rdi
	je	.L175
	movq	272(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L175:
	movq	40(%rsp), %rdx
	movq	32(%rsp), %rsi
	movq	%r15, %rdi
.LEHB6:
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
.LEHE6:
	movq	32(%rsp), %rdi
	cmpq	(%rsp), %rdi
	je	.L176
	movq	48(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L176:
	movq	360(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L243
	addq	$376, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r15, %rax
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
.L125:
	.cfi_restore_state
	testq	%r8, %r8
	je	.L229
	leaq	(%rcx,%rsi), %rdi
	cmpq	$1, %r8
	je	.L244
	movq	%r8, %rdx
	movq	%r9, %rsi
	call	memcpy@PLT
	movq	128(%rsp), %rcx
.L229:
	leaq	176(%rsp), %rax
	movq	%rax, 16(%rsp)
	jmp	.L131
	.p2align 4,,10
	.p2align 3
.L234:
	movq	%rsi, %r8
	xorl	%edx, %edx
	xorl	%esi, %esi
	movq	%r12, %rdi
.LEHB7:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
.LEHE7:
	leaq	208(%rsp), %rbp
	leaq	16(%rax), %rdx
	movq	%rbp, 192(%rsp)
	movq	(%rax), %rcx
	cmpq	%rdx, %rcx
	je	.L245
	movq	%rcx, 192(%rsp)
	movq	16(%rax), %rcx
	movq	%rcx, 208(%rsp)
.L134:
	movq	8(%rax), %rcx
	movb	$0, 16(%rax)
	movq	%rcx, 200(%rsp)
	movq	$0, 8(%rax)
	movq	200(%rsp), %rsi
	movq	%rdx, (%rax)
	jmp	.L135
	.p2align 4,,10
	.p2align 3
.L143:
	testq	%r8, %r8
	je	.L230
	leaq	(%rcx,%rsi), %rdi
	cmpq	$1, %r8
	je	.L246
	movq	%r8, %rdx
	movq	%r9, %rsi
	call	memcpy@PLT
	movq	224(%rsp), %rcx
.L230:
	leaq	272(%rsp), %rax
	movq	%rax, 8(%rsp)
	jmp	.L149
	.p2align 4,,10
	.p2align 3
.L121:
	leaq	96(%rsp), %rdi
	movl	$2, %r8d
	xorl	%edx, %edx
	movq	%rbp, %rsi
	leaq	.LC10(%rip), %rcx
.LEHB8:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.LEHE8:
	jmp	.L122
	.p2align 4,,10
	.p2align 3
.L139:
	leaq	192(%rsp), %rdi
	movl	$2, %r8d
	leaq	.LC10(%rip), %rcx
	xorl	%edx, %edx
.LEHB9:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.LEHE9:
	jmp	.L140
	.p2align 4,,10
	.p2align 3
.L157:
	leaq	288(%rsp), %rdi
	movl	$1, %r8d
	leaq	.LC11(%rip), %rcx
	xorl	%edx, %edx
.LEHB10:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
.LEHE10:
	jmp	.L158
	.p2align 4,,10
	.p2align 3
.L231:
	movdqu	16(%rax), %xmm7
	movaps	%xmm7, 112(%rsp)
	jmp	.L118
	.p2align 4,,10
	.p2align 3
.L233:
	movq	104(%rsp), %rsi
	movdqa	112(%rsp), %xmm6
	movq	%r13, %rcx
	movb	$0, 112(%rsp)
	movq	168(%rsp), %r8
	movl	$15, %eax
	movq	$0, 104(%rsp)
	movq	%rsi, 136(%rsp)
	movaps	%xmm6, 144(%rsp)
	leaq	(%r8,%rsi), %rbp
	jmp	.L124
	.p2align 4,,10
	.p2align 3
.L237:
	movq	200(%rsp), %rsi
	movq	264(%rsp), %r8
	movq	%r14, %rcx
	movl	$15, %eax
	movdqa	208(%rsp), %xmm7
	movq	$0, 200(%rsp)
	movq	%rsi, 232(%rsp)
	leaq	(%r8,%rsi), %r12
	movb	$0, 208(%rsp)
	movaps	%xmm7, 240(%rsp)
	jmp	.L142
	.p2align 4,,10
	.p2align 3
.L241:
	movq	296(%rsp), %rdx
	movq	32(%rsp), %rdi
	movq	$0, 296(%rsp)
	movdqa	304(%rsp), %xmm6
	movb	$0, 304(%rsp)
	movq	%rdx, 328(%rsp)
	movaps	%xmm6, 336(%rsp)
.L160:
	testq	%rdx, %rdx
	je	.L162
	cmpq	$1, %rdx
	je	.L247
	movq	%rcx, %rsi
	movq	%rcx, 24(%rsp)
	call	memcpy@PLT
	movq	32(%rsp), %rdi
	movq	24(%rsp), %rcx
	movq	328(%rsp), %rdx
.L162:
	movq	%rdx, 40(%rsp)
	movb	$0, (%rdi,%rdx)
	movq	320(%rsp), %rdi
	jmp	.L164
	.p2align 4,,10
	.p2align 3
.L235:
	movdqa	144(%rsp), %xmm5
	movaps	%xmm5, 208(%rsp)
	jmp	.L136
	.p2align 4,,10
	.p2align 3
.L239:
	movdqa	240(%rsp), %xmm7
	movaps	%xmm7, 304(%rsp)
	jmp	.L154
	.p2align 4,,10
	.p2align 3
.L238:
	movq	24(%rsp), %rdi
	movq	%rsi, %r8
	xorl	%edx, %edx
	xorl	%esi, %esi
.LEHB11:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm
.LEHE11:
	leaq	304(%rsp), %r12
	leaq	16(%rax), %rdx
	movq	%r12, 288(%rsp)
	movq	(%rax), %rcx
	cmpq	%rdx, %rcx
	je	.L248
	movq	%rcx, 288(%rsp)
	movq	16(%rax), %rcx
	movq	%rcx, 304(%rsp)
.L152:
	movq	8(%rax), %rcx
	movb	$0, 16(%rax)
	movq	%rcx, 296(%rsp)
	movq	$0, 8(%rax)
	movq	296(%rsp), %rsi
	movq	%rdx, (%rax)
	jmp	.L153
	.p2align 4,,10
	.p2align 3
.L242:
	movq	%rax, 32(%rsp)
	movups	%xmm0, 40(%rsp)
.L166:
	movq	%rcx, 320(%rsp)
	leaq	336(%rsp), %rcx
	movq	%rcx, %rdi
	jmp	.L164
	.p2align 4,,10
	.p2align 3
.L244:
	movzbl	(%r9), %eax
	movb	%al, (%rdi)
	leaq	176(%rsp), %rax
	movq	128(%rsp), %rcx
	movq	%rax, 16(%rsp)
	jmp	.L131
	.p2align 4,,10
	.p2align 3
.L246:
	movzbl	(%r9), %eax
	movb	%al, (%rdi)
	leaq	272(%rsp), %rax
	movq	224(%rsp), %rcx
	movq	%rax, 8(%rsp)
	jmp	.L149
	.p2align 4,,10
	.p2align 3
.L245:
	movdqu	16(%rax), %xmm5
	movaps	%xmm5, 208(%rsp)
	jmp	.L134
	.p2align 4,,10
	.p2align 3
.L248:
	movdqu	16(%rax), %xmm3
	movaps	%xmm3, 304(%rsp)
	jmp	.L152
	.p2align 4,,10
	.p2align 3
.L247:
	movzbl	336(%rsp), %eax
	movb	%al, (%rdi)
	movq	328(%rsp), %rdx
	movq	32(%rsp), %rdi
	jmp	.L162
.L236:
	leaq	.LC9(%rip), %rdi
.LEHB12:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE12:
.L240:
	leaq	.LC9(%rip), %rdi
.LEHB13:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE13:
.L243:
	call	__stack_chk_fail@PLT
.L232:
	leaq	.LC9(%rip), %rdi
.LEHB14:
	call	_ZSt20__throw_length_errorPKc@PLT
.LEHE14:
.L208:
	endbr64
	movq	%rax, %rbp
	leaq	176(%rsp), %rax
	movq	%rax, 16(%rsp)
	leaq	272(%rsp), %rax
	movq	%rax, 8(%rsp)
	jmp	.L189
.L207:
	endbr64
	movq	%rax, %rbp
	leaq	272(%rsp), %rax
	movq	%rax, 8(%rsp)
	jmp	.L191
.L212:
	endbr64
	movq	%rax, %r12
	leaq	272(%rsp), %rax
	movq	%rax, 8(%rsp)
	jmp	.L181
.L211:
	endbr64
	movq	%rax, %rbp
	leaq	272(%rsp), %rax
	movq	%rax, 8(%rsp)
	jmp	.L183
.L214:
	endbr64
	movq	%rax, %r15
	jmp	.L177
.L206:
	endbr64
	movq	%rax, %rbp
	jmp	.L193
.L209:
	endbr64
	movq	%rax, %rbp
	leaq	176(%rsp), %rax
	movq	%rax, 16(%rsp)
	leaq	272(%rsp), %rax
	movq	%rax, 8(%rsp)
	jmp	.L187
.L210:
	endbr64
	movq	%rax, %rbp
	leaq	176(%rsp), %rax
	movq	%rax, 16(%rsp)
	leaq	272(%rsp), %rax
	movq	%rax, 8(%rsp)
	jmp	.L185
.L213:
	endbr64
	movq	%rax, %r12
	jmp	.L179
.L177:
	movq	288(%rsp), %rdi
	cmpq	%r12, %rdi
	jne	.L249
.L178:
	movq	%r15, %r12
.L179:
	movq	224(%rsp), %rdi
	cmpq	%r14, %rdi
	je	.L181
	movq	240(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L181:
	movq	192(%rsp), %rdi
	cmpq	%rbp, %rdi
	jne	.L250
.L182:
	movq	%r12, %rbp
.L183:
	movq	128(%rsp), %rdi
	cmpq	%r13, %rdi
	je	.L185
	movq	144(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L185:
	movq	96(%rsp), %rdi
	cmpq	%rbx, %rdi
	je	.L187
	movq	112(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L187:
	movq	64(%rsp), %rdi
	leaq	80(%rsp), %rax
	cmpq	%rax, %rdi
	je	.L189
	movq	80(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L189:
	movq	160(%rsp), %rdi
	cmpq	16(%rsp), %rdi
	je	.L191
	movq	176(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L191:
	movq	256(%rsp), %rdi
	cmpq	8(%rsp), %rdi
	je	.L193
	movq	272(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L193:
	movq	32(%rsp), %rdi
	cmpq	(%rsp), %rdi
	je	.L194
	movq	48(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L194:
	movq	%rbp, %rdi
.LEHB15:
	call	_Unwind_Resume@PLT
.LEHE15:
.L250:
	movq	208(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
	jmp	.L182
.L249:
	movq	304(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
	jmp	.L178
	.cfi_endproc
.LFE4174:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZlsIfERSoS0_RK7Vector3IT_E,"aG",@progbits,_ZlsIfERSoS0_RK7Vector3IT_E,comdat
.LLSDA4174:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE4174-.LLSDACSB4174
.LLSDACSB4174:
	.uleb128 .LEHB0-.LFB4174
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L206-.LFB4174
	.uleb128 0
	.uleb128 .LEHB1-.LFB4174
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L207-.LFB4174
	.uleb128 0
	.uleb128 .LEHB2-.LFB4174
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L208-.LFB4174
	.uleb128 0
	.uleb128 .LEHB3-.LFB4174
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L209-.LFB4174
	.uleb128 0
	.uleb128 .LEHB4-.LFB4174
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L211-.LFB4174
	.uleb128 0
	.uleb128 .LEHB5-.LFB4174
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L213-.LFB4174
	.uleb128 0
	.uleb128 .LEHB6-.LFB4174
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L206-.LFB4174
	.uleb128 0
	.uleb128 .LEHB7-.LFB4174
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L211-.LFB4174
	.uleb128 0
	.uleb128 .LEHB8-.LFB4174
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L210-.LFB4174
	.uleb128 0
	.uleb128 .LEHB9-.LFB4174
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L212-.LFB4174
	.uleb128 0
	.uleb128 .LEHB10-.LFB4174
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L214-.LFB4174
	.uleb128 0
	.uleb128 .LEHB11-.LFB4174
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L213-.LFB4174
	.uleb128 0
	.uleb128 .LEHB12-.LFB4174
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L212-.LFB4174
	.uleb128 0
	.uleb128 .LEHB13-.LFB4174
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L214-.LFB4174
	.uleb128 0
	.uleb128 .LEHB14-.LFB4174
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L210-.LFB4174
	.uleb128 0
	.uleb128 .LEHB15-.LFB4174
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
.LLSDACSE4174:
	.section	.text._ZlsIfERSoS0_RK7Vector3IT_E,"axG",@progbits,_ZlsIfERSoS0_RK7Vector3IT_E,comdat
	.size	_ZlsIfERSoS0_RK7Vector3IT_E, .-_ZlsIfERSoS0_RK7Vector3IT_E
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC12:
	.string	"ray[origin="
.LC13:
	.string	"point["
.LC14:
	.string	", direction="
.LC15:
	.string	", maximum_offset="
	.text
	.p2align 4
	.globl	_ZlsRSoRK3Ray
	.type	_ZlsRSoRK3Ray, @function
_ZlsRSoRK3Ray:
.LFB3810:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$11, %edx
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rsi, %rbx
	leaq	.LC12(%rip), %rsi
	subq	$40, %rsp
	.cfi_def_cfa_offset 80
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movss	(%rbx), %xmm3
	movss	4(%rbx), %xmm2
	movss	.LC6(%rip), %xmm0
	movss	.LC7(%rip), %xmm1
	movss	8(%rbx), %xmm5
	pxor	%xmm4, %xmm4
	movaps	%xmm3, %xmm6
	andps	%xmm0, %xmm6
	comiss	%xmm6, %xmm1
	ja	.L252
	pxor	%xmm4, %xmm4
	cvtss2sd	%xmm3, %xmm4
.L252:
	movaps	%xmm2, %xmm6
	pxor	%xmm3, %xmm3
	andps	%xmm0, %xmm6
	comiss	%xmm6, %xmm1
	ja	.L253
	pxor	%xmm3, %xmm3
	cvtss2sd	%xmm2, %xmm3
.L253:
	andps	%xmm5, %xmm0
	pxor	%xmm2, %xmm2
	comiss	%xmm0, %xmm1
	ja	.L254
	pxor	%xmm2, %xmm2
	cvtss2sd	%xmm5, %xmm2
.L254:
	movl	$6, %edx
	leaq	.LC13(%rip), %rsi
	movq	%r12, %rdi
	movsd	%xmm2, 24(%rsp)
	movsd	%xmm3, 16(%rsp)
	leaq	.LC10(%rip), %r13
	movsd	%xmm4, 8(%rsp)
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movsd	8(%rsp), %xmm4
	movq	%r12, %rdi
	movapd	%xmm4, %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movq	%r13, %rsi
	movl	$2, %edx
	movq	%rax, %rdi
	movq	%rax, %rbp
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movsd	16(%rsp), %xmm3
	movq	%rbp, %rdi
	movapd	%xmm3, %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movq	%r13, %rsi
	movl	$2, %edx
	leaq	.LC11(%rip), %r13
	movq	%rax, %rdi
	movq	%rax, %rbp
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movsd	24(%rsp), %xmm2
	movq	%rbp, %rdi
	movapd	%xmm2, %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movq	%r13, %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	$12, %edx
	movq	%r12, %rdi
	leaq	.LC14(%rip), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	leaq	12(%rbx), %rsi
	movq	%r12, %rdi
	call	_ZlsIfERSoS0_RK7Vector3IT_E
	movl	$17, %edx
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rbp
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbp, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	36(%rbx), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movq	%r13, %rsi
	movl	$1, %edx
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	addq	$40, %rsp
	.cfi_def_cfa_offset 40
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3810:
	.size	_ZlsRSoRK3Ray, .-_ZlsRSoRK3Ray
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZlsRSoRK3Ray, @function
_GLOBAL__sub_I__ZlsRSoRK3Ray:
.LFB4578:
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
.LFE4578:
	.size	_GLOBAL__sub_I__ZlsRSoRK3Ray, .-_GLOBAL__sub_I__ZlsRSoRK3Ray
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZlsRSoRK3Ray
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.set	.LC4,.LC6+4
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC6:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC7:
	.long	869711765
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

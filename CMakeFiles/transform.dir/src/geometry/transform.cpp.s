	.file	"transform.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN9TransformC2Ev
	.type	_ZN9TransformC2Ev, @function
_ZN9TransformC2Ev:
.LFB3917:
	.cfi_startproc
	endbr64
	movss	.LC0(%rip), %xmm0
	movups	%xmm0, (%rdi)
	movaps	.LC1(%rip), %xmm0
	movups	%xmm0, 16(%rdi)
	movaps	.LC2(%rip), %xmm0
	movups	%xmm0, 32(%rdi)
	movaps	.LC3(%rip), %xmm0
	movups	%xmm0, 48(%rdi)
	ret
	.cfi_endproc
.LFE3917:
	.size	_ZN9TransformC2Ev, .-_ZN9TransformC2Ev
	.globl	_ZN9TransformC1Ev
	.set	_ZN9TransformC1Ev,_ZN9TransformC2Ev
	.align 2
	.p2align 4
	.globl	_ZN9TransformC2ERK9Matrix4x4IfE
	.type	_ZN9TransformC2ERK9Matrix4x4IfE, @function
_ZN9TransformC2ERK9Matrix4x4IfE:
.LFB3920:
	.cfi_startproc
	endbr64
	movups	16(%rsi), %xmm2
	movups	32(%rsi), %xmm1
	movups	48(%rsi), %xmm0
	movups	(%rsi), %xmm3
	movups	%xmm2, 16(%rdi)
	movups	%xmm3, (%rdi)
	movups	%xmm1, 32(%rdi)
	movups	%xmm0, 48(%rdi)
	ret
	.cfi_endproc
.LFE3920:
	.size	_ZN9TransformC2ERK9Matrix4x4IfE, .-_ZN9TransformC2ERK9Matrix4x4IfE
	.globl	_ZN9TransformC1ERK9Matrix4x4IfE
	.set	_ZN9TransformC1ERK9Matrix4x4IfE,_ZN9TransformC2ERK9Matrix4x4IfE
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC6:
	.string	"[ "
.LC7:
	.string	" "
.LC8:
	.string	" ]\n"
.LC9:
	.string	" ]"
	.text
	.p2align 4
	.globl	_ZlsRSoRK9Transform
	.type	_ZlsRSoRK9Transform, @function
_ZlsRSoRK9Transform:
.LFB3922:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rsi, %rax
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	subq	$80, %rsp
	.cfi_def_cfa_offset 128
	movups	(%rax), %xmm0
	movups	48(%rax), %xmm1
	movups	16(%rax), %xmm3
	movups	32(%rax), %xmm2
	movl	4(%rax), %edi
	movss	28(%rax), %xmm12
	movaps	%xmm1, %xmm7
	movss	24(%rax), %xmm13
	movss	20(%rax), %xmm14
	movaps	%xmm3, %xmm15
	movaps	%xmm2, %xmm11
	movss	44(%rax), %xmm8
	movss	40(%rax), %xmm9
	movss	36(%rax), %xmm10
	movss	60(%rax), %xmm4
	movq	%fs:40, %rdx
	movq	%rdx, 72(%rsp)
	xorl	%edx, %edx
	movss	56(%rax), %xmm5
	movaps	%xmm1, 48(%rsp)
	movl	12(%rsi), %ecx
	movss	52(%rax), %xmm6
	cvttss2sil	%xmm0, %eax
	pxor	%xmm1, %xmm1
	movl	8(%rsi), %esi
	movaps	%xmm0, (%rsp)
	movss	.LC4(%rip), %xmm0
	movaps	%xmm3, 16(%rsp)
	movaps	%xmm2, 32(%rsp)
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L5
	movl	$0x00000000, (%rsp)
.L5:
	movd	%edi, %xmm2
	pxor	%xmm1, %xmm1
	cvttss2sil	%xmm2, %eax
	movl	%eax, %edx
	negl	%edx
	cmovns	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L7
	movl	$0x00000000, 4(%rsp)
.L7:
	movd	%esi, %xmm3
	pxor	%xmm1, %xmm1
	cvttss2sil	%xmm3, %edx
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L9
	movl	$0x00000000, 8(%rsp)
.L9:
	movd	%ecx, %xmm2
	pxor	%xmm1, %xmm1
	cvttss2sil	%xmm2, %edx
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L11
	movl	$0x00000000, 12(%rsp)
.L11:
	cvttss2sil	%xmm15, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L13
	movl	$0x00000000, 16(%rsp)
.L13:
	cvttss2sil	%xmm14, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L15
	movl	$0x00000000, 20(%rsp)
.L15:
	cvttss2sil	%xmm13, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L17
	movl	$0x00000000, 24(%rsp)
.L17:
	cvttss2sil	%xmm12, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L19
	movl	$0x00000000, 28(%rsp)
.L19:
	cvttss2sil	%xmm11, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L21
	movl	$0x00000000, 32(%rsp)
.L21:
	cvttss2sil	%xmm10, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L23
	movl	$0x00000000, 36(%rsp)
.L23:
	cvttss2sil	%xmm9, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L25
	movl	$0x00000000, 40(%rsp)
.L25:
	cvttss2sil	%xmm8, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L27
	movl	$0x00000000, 44(%rsp)
.L27:
	cvttss2sil	%xmm7, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L29
	movl	$0x00000000, 48(%rsp)
.L29:
	cvttss2sil	%xmm6, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L31
	movl	$0x00000000, 52(%rsp)
.L31:
	cvttss2sil	%xmm5, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L33
	movl	$0x00000000, 56(%rsp)
.L33:
	cvttss2sil	%xmm4, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L35
	movl	$0x00000000, 60(%rsp)
.L35:
	leaq	.LC6(%rip), %r14
	movl	$2, %edx
	movq	%r12, %rdi
	movq	%r14, %rsi
	leaq	.LC7(%rip), %rbp
	leaq	.LC8(%rip), %r15
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r12, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	4(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	8(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	12(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$3, %edx
	movq	%r15, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	$2, %edx
	movq	%r14, %rsi
	movq	%r13, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	16(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	20(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	24(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	28(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$3, %edx
	movq	%r15, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	$2, %edx
	movq	%r14, %rsi
	movq	%r13, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	32(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	36(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	40(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	44(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$3, %edx
	movq	%r15, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	$2, %edx
	movq	%r14, %rsi
	movq	%r13, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	48(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	52(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	56(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	movq	%rbp, %rsi
	movq	%rax, %r13
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	60(%rsp), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$2, %edx
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	72(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L55
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	movq	%r12, %rax
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
.L55:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3922:
	.size	_ZlsRSoRK9Transform, .-_ZlsRSoRK9Transform
	.section	.rodata.str1.1
.LC10:
	.string	"[ %f %f %f %f ]\n"
	.text
	.align 2
	.p2align 4
	.globl	_ZNK9Transform5printEv
	.type	_ZNK9Transform5printEv, @function
_ZNK9Transform5printEv:
.LFB3924:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	subq	$80, %rsp
	.cfi_def_cfa_offset 96
	movups	(%rdi), %xmm0
	movups	48(%rdi), %xmm1
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movups	16(%rdi), %xmm3
	movups	32(%rdi), %xmm2
	cvttss2sil	%xmm0, %eax
	movaps	%xmm1, %xmm7
	movaps	%xmm1, 48(%rsp)
	pxor	%xmm1, %xmm1
	movaps	%xmm0, (%rsp)
	movl	12(%rdi), %ecx
	movl	8(%rdi), %esi
	movaps	%xmm3, %xmm15
	movss	.LC4(%rip), %xmm0
	movl	4(%rdi), %r8d
	movaps	%xmm2, %xmm11
	movaps	%xmm3, 16(%rsp)
	movss	28(%rdi), %xmm12
	movss	24(%rdi), %xmm13
	movaps	%xmm2, 32(%rsp)
	movl	%eax, %edx
	movss	20(%rdi), %xmm14
	movss	44(%rdi), %xmm8
	negl	%edx
	movss	40(%rdi), %xmm9
	movss	36(%rdi), %xmm10
	cmovns	%edx, %eax
	movss	60(%rdi), %xmm4
	movss	56(%rdi), %xmm5
	movss	52(%rdi), %xmm6
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L57
	movl	$0x00000000, (%rsp)
.L57:
	movd	%r8d, %xmm2
	pxor	%xmm1, %xmm1
	cvttss2sil	%xmm2, %edx
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L59
	movl	$0x00000000, 4(%rsp)
.L59:
	movd	%esi, %xmm3
	pxor	%xmm1, %xmm1
	cvttss2sil	%xmm3, %edx
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L61
	movl	$0x00000000, 8(%rsp)
.L61:
	movd	%ecx, %xmm2
	pxor	%xmm1, %xmm1
	cvttss2sil	%xmm2, %edx
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L63
	movl	$0x00000000, 12(%rsp)
.L63:
	cvttss2sil	%xmm15, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L65
	movl	$0x00000000, 16(%rsp)
.L65:
	cvttss2sil	%xmm14, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L67
	movl	$0x00000000, 20(%rsp)
.L67:
	cvttss2sil	%xmm13, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L69
	movl	$0x00000000, 24(%rsp)
.L69:
	cvttss2sil	%xmm12, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L71
	movl	$0x00000000, 28(%rsp)
.L71:
	cvttss2sil	%xmm11, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L73
	movl	$0x00000000, 32(%rsp)
.L73:
	cvttss2sil	%xmm10, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L75
	movl	$0x00000000, 36(%rsp)
.L75:
	cvttss2sil	%xmm9, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L77
	movl	$0x00000000, 40(%rsp)
.L77:
	cvttss2sil	%xmm8, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L79
	movl	$0x00000000, 44(%rsp)
.L79:
	cvttss2sil	%xmm7, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L81
	movl	$0x00000000, 48(%rsp)
.L81:
	cvttss2sil	%xmm6, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L83
	movl	$0x00000000, 52(%rsp)
.L83:
	cvttss2sil	%xmm5, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L85
	movl	$0x00000000, 56(%rsp)
.L85:
	cvttss2sil	%xmm4, %edx
	pxor	%xmm1, %xmm1
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm1
	comiss	%xmm1, %xmm0
	jbe	.L87
	movl	$0x00000000, 60(%rsp)
.L87:
	leaq	.LC10(%rip), %rbp
	movl	$1, %edi
	pxor	%xmm0, %xmm0
	movl	$4, %eax
	movq	%rbp, %rsi
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	cvtss2sd	(%rsp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	12(%rsp), %xmm3
	cvtss2sd	8(%rsp), %xmm2
	cvtss2sd	4(%rsp), %xmm1
	call	__printf_chk@PLT
	movq	%rbp, %rsi
	movl	$1, %edi
	pxor	%xmm0, %xmm0
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	movl	$4, %eax
	pxor	%xmm1, %xmm1
	cvtss2sd	16(%rsp), %xmm0
	cvtss2sd	28(%rsp), %xmm3
	cvtss2sd	24(%rsp), %xmm2
	cvtss2sd	20(%rsp), %xmm1
	call	__printf_chk@PLT
	pxor	%xmm0, %xmm0
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	pxor	%xmm1, %xmm1
	movq	%rbp, %rsi
	movl	$1, %edi
	movl	$4, %eax
	cvtss2sd	32(%rsp), %xmm0
	cvtss2sd	44(%rsp), %xmm3
	cvtss2sd	40(%rsp), %xmm2
	cvtss2sd	36(%rsp), %xmm1
	call	__printf_chk@PLT
	movq	72(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L108
	pxor	%xmm0, %xmm0
	pxor	%xmm3, %xmm3
	pxor	%xmm2, %xmm2
	movq	%rbp, %rsi
	pxor	%xmm1, %xmm1
	movl	$1, %edi
	movl	$4, %eax
	cvtss2sd	48(%rsp), %xmm0
	cvtss2sd	60(%rsp), %xmm3
	cvtss2sd	56(%rsp), %xmm2
	cvtss2sd	52(%rsp), %xmm1
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	__printf_chk@PLT
.L108:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3924:
	.size	_ZNK9Transform5printEv, .-_ZNK9Transform5printEv
	.align 2
	.p2align 4
	.globl	_ZNK9TransformeqERKS_
	.type	_ZNK9TransformeqERKS_, @function
_ZNK9TransformeqERKS_:
.LFB3925:
	.cfi_startproc
	endbr64
	movss	(%rsi), %xmm0
	comiss	(%rdi), %xmm0
	jne	.L118
	movss	4(%rdi), %xmm0
	comiss	4(%rsi), %xmm0
	jne	.L118
	movss	8(%rdi), %xmm0
	comiss	8(%rsi), %xmm0
	jne	.L118
	movss	12(%rdi), %xmm0
	comiss	12(%rsi), %xmm0
	sete	%al
.L110:
	movss	16(%rdi), %xmm0
	comiss	16(%rsi), %xmm0
	jne	.L122
	movss	20(%rsi), %xmm0
	comiss	20(%rdi), %xmm0
	jne	.L122
	movss	24(%rsi), %xmm0
	comiss	24(%rdi), %xmm0
	jne	.L122
	xorl	%edx, %edx
	movss	28(%rsi), %xmm0
	comiss	28(%rdi), %xmm0
	cmovne	%edx, %eax
.L111:
	movss	32(%rsi), %xmm0
	comiss	32(%rdi), %xmm0
	jne	.L126
	movss	36(%rsi), %xmm0
	comiss	36(%rdi), %xmm0
	jne	.L126
	movss	40(%rsi), %xmm0
	comiss	40(%rdi), %xmm0
	jne	.L126
	xorl	%edx, %edx
	movss	44(%rsi), %xmm0
	comiss	44(%rdi), %xmm0
	cmovne	%edx, %eax
.L112:
	movss	48(%rsi), %xmm0
	comiss	48(%rdi), %xmm0
	jne	.L129
	movss	52(%rsi), %xmm0
	comiss	52(%rdi), %xmm0
	jne	.L129
	movss	56(%rsi), %xmm0
	comiss	56(%rdi), %xmm0
	jne	.L129
	xorl	%edx, %edx
	movss	60(%rsi), %xmm0
	comiss	60(%rdi), %xmm0
	cmovne	%edx, %eax
	ret
.L118:
	xorl	%eax, %eax
	jmp	.L110
.L122:
	xorl	%eax, %eax
	jmp	.L111
.L126:
	xorl	%eax, %eax
	jmp	.L112
.L129:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE3925:
	.size	_ZNK9TransformeqERKS_, .-_ZNK9TransformeqERKS_
	.align 2
	.p2align 4
	.globl	_ZNK9TransformneERKS_
	.type	_ZNK9TransformneERKS_, @function
_ZNK9TransformneERKS_:
.LFB3926:
	.cfi_startproc
	endbr64
	movss	(%rsi), %xmm0
	comiss	(%rdi), %xmm0
	jne	.L142
	movss	4(%rdi), %xmm0
	comiss	4(%rsi), %xmm0
	jne	.L142
	movss	8(%rdi), %xmm0
	comiss	8(%rsi), %xmm0
	jne	.L142
	movss	12(%rdi), %xmm0
	comiss	12(%rsi), %xmm0
	sete	%al
.L134:
	movss	16(%rdi), %xmm0
	comiss	16(%rsi), %xmm0
	jne	.L146
	movss	20(%rsi), %xmm0
	comiss	20(%rdi), %xmm0
	jne	.L146
	movss	24(%rsi), %xmm0
	comiss	24(%rdi), %xmm0
	jne	.L146
	xorl	%edx, %edx
	movss	28(%rsi), %xmm0
	comiss	28(%rdi), %xmm0
	cmovne	%edx, %eax
.L135:
	movss	32(%rsi), %xmm0
	comiss	32(%rdi), %xmm0
	jne	.L150
	movss	36(%rsi), %xmm0
	comiss	36(%rdi), %xmm0
	jne	.L150
	movss	40(%rsi), %xmm0
	comiss	40(%rdi), %xmm0
	jne	.L150
	xorl	%edx, %edx
	movss	44(%rsi), %xmm0
	comiss	44(%rdi), %xmm0
	cmovne	%edx, %eax
.L136:
	movss	48(%rsi), %xmm0
	comiss	48(%rdi), %xmm0
	jne	.L153
	movss	52(%rsi), %xmm0
	comiss	52(%rdi), %xmm0
	jne	.L153
	movss	56(%rsi), %xmm0
	comiss	56(%rdi), %xmm0
	jne	.L153
	xorl	%edx, %edx
	movss	60(%rsi), %xmm0
	comiss	60(%rdi), %xmm0
	cmovne	%edx, %eax
	xorl	$1, %eax
	ret
.L142:
	xorl	%eax, %eax
	jmp	.L134
.L146:
	xorl	%eax, %eax
	jmp	.L135
.L150:
	xorl	%eax, %eax
	jmp	.L136
.L153:
	xorl	%eax, %eax
	xorl	$1, %eax
	ret
	.cfi_endproc
.LFE3926:
	.size	_ZNK9TransformneERKS_, .-_ZNK9TransformneERKS_
	.align 2
	.p2align 4
	.globl	_ZNK9TransformltERKS_
	.type	_ZNK9TransformltERKS_, @function
_ZNK9TransformltERKS_:
.LFB3927:
	.cfi_startproc
	endbr64
	movss	(%rdi), %xmm1
	movss	(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	4(%rdi), %xmm1
	movss	4(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	8(%rdi), %xmm1
	movss	8(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	12(%rdi), %xmm1
	movss	12(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	16(%rdi), %xmm1
	movss	16(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	20(%rdi), %xmm1
	movss	20(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	24(%rdi), %xmm1
	movss	24(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	28(%rdi), %xmm1
	movss	28(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	32(%rdi), %xmm1
	movss	32(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	36(%rdi), %xmm1
	movss	36(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	40(%rdi), %xmm1
	movss	40(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	44(%rdi), %xmm1
	movss	44(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	48(%rdi), %xmm1
	movss	48(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	52(%rdi), %xmm1
	movss	52(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	56(%rdi), %xmm1
	movss	56(%rsi), %xmm0
	comiss	%xmm1, %xmm0
	ja	.L188
	comiss	%xmm0, %xmm1
	ja	.L189
	movss	60(%rsi), %xmm0
	comiss	60(%rdi), %xmm0
	seta	%al
	ret
	.p2align 4,,10
	.p2align 3
.L189:
	xorl	%eax, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L188:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE3927:
	.size	_ZNK9TransformltERKS_, .-_ZNK9TransformltERKS_
	.align 2
	.p2align 4
	.globl	_ZNK9Transform11is_identityEv
	.type	_ZNK9Transform11is_identityEv, @function
_ZNK9Transform11is_identityEv:
.LFB3928:
	.cfi_startproc
	endbr64
	movss	.LC11(%rip), %xmm0
	comiss	(%rdi), %xmm0
	jne	.L251
	pxor	%xmm1, %xmm1
	comiss	4(%rdi), %xmm1
	jne	.L251
	comiss	8(%rdi), %xmm1
	jne	.L251
	comiss	12(%rdi), %xmm1
	jne	.L251
	comiss	16(%rdi), %xmm1
	jne	.L251
	comiss	20(%rdi), %xmm0
	jne	.L251
	comiss	24(%rdi), %xmm1
	jne	.L251
	comiss	28(%rdi), %xmm1
	jne	.L251
	comiss	32(%rdi), %xmm1
	jne	.L251
	comiss	36(%rdi), %xmm1
	jne	.L251
	comiss	40(%rdi), %xmm0
	jne	.L251
	comiss	44(%rdi), %xmm1
	jne	.L251
	comiss	48(%rdi), %xmm1
	jne	.L251
	comiss	52(%rdi), %xmm1
	jne	.L251
	comiss	56(%rdi), %xmm1
	jne	.L251
	comiss	60(%rdi), %xmm0
	sete	%al
	ret
	.p2align 4,,10
	.p2align 3
.L251:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE3928:
	.size	_ZNK9Transform11is_identityEv, .-_ZNK9Transform11is_identityEv
	.align 2
	.p2align 4
	.globl	_ZNK9Transform10get_matrixEv
	.type	_ZNK9Transform10get_matrixEv, @function
_ZNK9Transform10get_matrixEv:
.LFB3929:
	.cfi_startproc
	endbr64
	movq	%rdi, %rax
	ret
	.cfi_endproc
.LFE3929:
	.size	_ZNK9Transform10get_matrixEv, .-_ZNK9Transform10get_matrixEv
	.align 2
	.p2align 4
	.globl	_ZNK9Transform9has_scaleEv
	.type	_ZNK9Transform9has_scaleEv, @function
_ZNK9Transform9has_scaleEv:
.LFB3930:
	.cfi_startproc
	endbr64
	movss	(%rdi), %xmm0
	movss	16(%rdi), %xmm6
	movl	$1, %eax
	movss	32(%rdi), %xmm1
	movss	4(%rdi), %xmm2
	mulss	%xmm6, %xmm6
	movss	8(%rdi), %xmm5
	movss	24(%rdi), %xmm3
	mulss	%xmm0, %xmm0
	movss	20(%rdi), %xmm8
	movss	36(%rdi), %xmm7
	mulss	%xmm1, %xmm1
	movss	40(%rdi), %xmm4
	addss	%xmm6, %xmm0
	movss	.LC11(%rip), %xmm6
	subss	%xmm6, %xmm1
	addss	%xmm1, %xmm0
	movss	.LC12(%rip), %xmm1
	andps	%xmm1, %xmm0
	comiss	.LC4(%rip), %xmm0
	ja	.L253
	mulss	%xmm2, %xmm2
	mulss	%xmm8, %xmm8
	mulss	%xmm7, %xmm7
	addss	%xmm8, %xmm2
	subss	%xmm6, %xmm7
	addss	%xmm7, %xmm2
	andps	%xmm1, %xmm2
	comiss	.LC4(%rip), %xmm2
	jbe	.L257
.L253:
	ret
	.p2align 4,,10
	.p2align 3
.L257:
	mulss	%xmm5, %xmm5
	mulss	%xmm3, %xmm3
	mulss	%xmm4, %xmm4
	addss	%xmm5, %xmm3
	subss	%xmm6, %xmm4
	addss	%xmm4, %xmm3
	andps	%xmm1, %xmm3
	comiss	.LC4(%rip), %xmm3
	seta	%al
	ret
	.cfi_endproc
.LFE3930:
	.size	_ZNK9Transform9has_scaleEv, .-_ZNK9Transform9has_scaleEv
	.align 2
	.p2align 4
	.globl	_ZNK9TransformclERK6Point3IfE
	.type	_ZNK9TransformclERK6Point3IfE, @function
_ZNK9TransformclERK6Point3IfE:
.LFB3931:
	.cfi_startproc
	endbr64
	movq	(%rdx), %xmm3
	movss	48(%rsi), %xmm1
	movq	%rdi, %rax
	movss	52(%rsi), %xmm2
	movss	8(%rdx), %xmm4
	mulss	%xmm3, %xmm1
	movaps	%xmm3, %xmm7
	movaps	%xmm3, %xmm0
	movss	20(%rsi), %xmm6
	shufps	$0xe5, %xmm7, %xmm7
	mulss	%xmm7, %xmm2
	movaps	%xmm7, %xmm5
	mulss	32(%rsi), %xmm0
	mulss	36(%rsi), %xmm5
	addss	%xmm2, %xmm1
	movss	56(%rsi), %xmm2
	mulss	%xmm4, %xmm2
	addss	%xmm5, %xmm0
	movss	16(%rsi), %xmm5
	addss	60(%rsi), %xmm2
	addss	%xmm2, %xmm1
	movss	.LC11(%rip), %xmm2
	divss	%xmm1, %xmm2
	movss	40(%rsi), %xmm1
	mulss	%xmm4, %xmm1
	shufps	$0xe0, %xmm4, %xmm4
	addss	44(%rsi), %xmm1
	addss	%xmm1, %xmm0
	movss	(%rsi), %xmm1
	unpcklps	%xmm5, %xmm1
	movaps	%xmm3, %xmm5
	shufps	$0xe5, %xmm3, %xmm3
	shufps	$0xe0, %xmm5, %xmm5
	mulps	%xmm5, %xmm1
	movss	4(%rsi), %xmm5
	unpcklps	%xmm6, %xmm5
	mulps	%xmm5, %xmm3
	movss	24(%rsi), %xmm5
	addps	%xmm3, %xmm1
	movss	8(%rsi), %xmm3
	mulss	%xmm2, %xmm0
	shufps	$0xe0, %xmm2, %xmm2
	unpcklps	%xmm5, %xmm3
	movss	28(%rsi), %xmm5
	mulps	%xmm4, %xmm3
	movss	12(%rsi), %xmm4
	unpcklps	%xmm5, %xmm4
	movss	%xmm0, 8(%rdi)
	addps	%xmm4, %xmm3
	addps	%xmm3, %xmm1
	mulps	%xmm2, %xmm1
	movlps	%xmm1, (%rdi)
	ret
	.cfi_endproc
.LFE3931:
	.size	_ZNK9TransformclERK6Point3IfE, .-_ZNK9TransformclERK6Point3IfE
	.align 2
	.p2align 4
	.globl	_ZNK9TransformclERK7Vector3IfE
	.type	_ZNK9TransformclERK7Vector3IfE, @function
_ZNK9TransformclERK7Vector3IfE:
.LFB3932:
	.cfi_startproc
	endbr64
	movq	(%rdx), %xmm2
	movss	8(%rdx), %xmm3
	movq	%rdi, %rax
	movss	32(%rsi), %xmm0
	movss	40(%rsi), %xmm1
	movaps	%xmm2, %xmm6
	movss	16(%rsi), %xmm4
	movss	24(%rsi), %xmm5
	mulss	%xmm3, %xmm1
	shufps	$0xe5, %xmm6, %xmm6
	shufps	$0xe0, %xmm3, %xmm3
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	movss	36(%rsi), %xmm1
	mulss	%xmm6, %xmm1
	addss	%xmm1, %xmm0
	movss	(%rsi), %xmm1
	unpcklps	%xmm4, %xmm1
	movaps	%xmm2, %xmm4
	shufps	$0xe5, %xmm2, %xmm2
	shufps	$0xe0, %xmm4, %xmm4
	mulps	%xmm4, %xmm1
	movss	8(%rsi), %xmm4
	unpcklps	%xmm5, %xmm4
	mulps	%xmm4, %xmm3
	movss	20(%rsi), %xmm4
	addps	%xmm3, %xmm1
	movss	4(%rsi), %xmm3
	movss	%xmm0, 8(%rdi)
	unpcklps	%xmm4, %xmm3
	mulps	%xmm3, %xmm2
	addps	%xmm2, %xmm1
	movlps	%xmm1, (%rdi)
	ret
	.cfi_endproc
.LFE3932:
	.size	_ZNK9TransformclERK7Vector3IfE, .-_ZNK9TransformclERK7Vector3IfE
	.align 2
	.p2align 4
	.globl	_ZN9TransformclERK6Point3IfER7Vector3IfE
	.type	_ZN9TransformclERK6Point3IfER7Vector3IfE, @function
_ZN9TransformclERK6Point3IfER7Vector3IfE:
.LFB3933:
	.cfi_startproc
	endbr64
	movq	(%rdx), %xmm2
	movss	16(%rsi), %xmm3
	movq	%rdi, %rax
	movss	.LC12(%rip), %xmm8
	movss	(%rsi), %xmm11
	movss	4(%rsi), %xmm9
	movss	8(%rdx), %xmm0
	movss	8(%rsi), %xmm6
	movaps	%xmm2, %xmm1
	movaps	%xmm2, %xmm4
	unpcklps	%xmm3, %xmm11
	movaps	%xmm2, %xmm3
	shufps	$0xe5, %xmm2, %xmm2
	movss	12(%rsi), %xmm12
	shufps	$0xe0, %xmm3, %xmm3
	mulps	%xmm3, %xmm11
	movss	20(%rsi), %xmm3
	shufps	$0xe5, %xmm4, %xmm4
	movaps	%xmm4, %xmm7
	movss	44(%rsi), %xmm5
	movq	.LC13(%rip), %xmm10
	mulss	52(%rsi), %xmm7
	unpcklps	%xmm3, %xmm9
	movss	32(%rsi), %xmm3
	mulps	%xmm2, %xmm9
	movss	24(%rsi), %xmm2
	mulss	%xmm1, %xmm3
	mulss	48(%rsi), %xmm1
	unpcklps	%xmm2, %xmm6
	movaps	%xmm0, %xmm2
	shufps	$0xe0, %xmm2, %xmm2
	mulps	%xmm2, %xmm6
	movss	28(%rsi), %xmm2
	mulss	36(%rsi), %xmm4
	unpcklps	%xmm2, %xmm12
	movss	40(%rsi), %xmm2
	movaps	%xmm12, %xmm13
	mulss	%xmm0, %xmm2
	addss	%xmm7, %xmm1
	andps	%xmm10, %xmm13
	mulss	56(%rsi), %xmm0
	addss	60(%rsi), %xmm0
	addss	%xmm0, %xmm1
	movaps	%xmm6, %xmm0
	addps	%xmm12, %xmm6
	andps	%xmm10, %xmm0
	addps	%xmm13, %xmm0
	movaps	%xmm9, %xmm13
	addps	%xmm11, %xmm9
	andps	%xmm10, %xmm13
	andps	%xmm11, %xmm10
	movaps	%xmm1, %xmm7
	addps	%xmm13, %xmm10
	andps	%xmm8, %xmm7
	addps	%xmm9, %xmm6
	addps	%xmm10, %xmm0
	movq	.LC14(%rip), %xmm10
	mulps	%xmm10, %xmm0
	movaps	%xmm7, %xmm10
	shufps	$0xe0, %xmm10, %xmm10
	mulps	%xmm10, %xmm0
	movq	(%rcx), %xmm10
	addps	%xmm10, %xmm0
	movaps	%xmm5, %xmm10
	andps	%xmm8, %xmm10
	movlps	%xmm0, (%rcx)
	movaps	%xmm2, %xmm0
	addss	%xmm5, %xmm2
	andps	%xmm8, %xmm0
	addss	%xmm10, %xmm0
	movaps	%xmm3, %xmm10
	addss	%xmm4, %xmm3
	andps	%xmm8, %xmm10
	andps	%xmm4, %xmm8
	addss	%xmm10, %xmm8
	addss	%xmm3, %xmm2
	addss	%xmm8, %xmm0
	mulss	%xmm7, %xmm0
	mulss	.LC15(%rip), %xmm0
	addss	8(%rcx), %xmm0
	movss	%xmm0, 8(%rcx)
	movss	.LC11(%rip), %xmm0
	divss	%xmm1, %xmm0
	mulss	%xmm0, %xmm2
	movaps	%xmm0, %xmm1
	shufps	$0xe0, %xmm1, %xmm1
	mulps	%xmm1, %xmm6
	movss	%xmm2, 8(%rdi)
	movlps	%xmm6, (%rdi)
	ret
	.cfi_endproc
.LFE3933:
	.size	_ZN9TransformclERK6Point3IfER7Vector3IfE, .-_ZN9TransformclERK6Point3IfER7Vector3IfE
	.align 2
	.p2align 4
	.globl	_ZNK9TransformclERK12BoundingBox3IfE
	.type	_ZNK9TransformclERK12BoundingBox3IfE, @function
_ZNK9TransformclERK12BoundingBox3IfE:
.LFB3935:
	.cfi_startproc
	endbr64
	subq	$56, %rsp
	.cfi_def_cfa_offset 64
	movss	8(%rdx), %xmm0
	movq	%rdi, %r8
	movq	%rdx, %rcx
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	(%rdx), %rax
	leaq	24(%rsp), %rdi
	leaq	8(%rsp), %rdx
	movss	%xmm0, 16(%rsp)
	movq	%rax, 8(%rsp)
	call	_ZNK9TransformclERK6Point3IfE
	movss	32(%rsp), %xmm1
	movss	28(%rsp), %xmm2
	movss	24(%rsp), %xmm0
	movaps	%xmm1, %xmm3
	movss	%xmm1, 20(%r8)
	unpcklps	%xmm0, %xmm3
	unpcklps	%xmm2, %xmm0
	movss	%xmm2, 16(%r8)
	movlhps	%xmm3, %xmm0
	movups	%xmm0, (%r8)
	movss	4(%rcx), %xmm2
	movss	12(%rcx), %xmm1
	movss	8(%rcx), %xmm0
	unpcklps	%xmm2, %xmm1
	movlps	%xmm1, 8(%rsp)
	movss	%xmm0, 16(%rsp)
	call	_ZNK9TransformclERK6Point3IfE
	movq	16(%r8), %xmm1
	movq	28(%rsp), %xmm0
	movss	24(%rsp), %xmm2
	movss	32(%rsp), %xmm4
	movaps	%xmm1, %xmm3
	movss	(%r8), %xmm1
	minss	8(%r8), %xmm4
	maxps	%xmm0, %xmm3
	minss	4(%r8), %xmm0
	minss	%xmm2, %xmm1
	maxss	12(%r8), %xmm2
	movlps	%xmm3, 16(%r8)
	unpcklps	%xmm0, %xmm1
	unpcklps	%xmm2, %xmm4
	movaps	%xmm1, %xmm0
	movlhps	%xmm4, %xmm0
	movups	%xmm0, (%r8)
	movss	16(%rcx), %xmm2
	movss	(%rcx), %xmm1
	movss	8(%rcx), %xmm0
	unpcklps	%xmm2, %xmm1
	movlps	%xmm1, 8(%rsp)
	movss	%xmm0, 16(%rsp)
	call	_ZNK9TransformclERK6Point3IfE
	movq	16(%r8), %xmm1
	movq	28(%rsp), %xmm0
	movss	24(%rsp), %xmm2
	movss	32(%rsp), %xmm4
	movaps	%xmm1, %xmm3
	movss	(%r8), %xmm1
	minss	8(%r8), %xmm4
	maxps	%xmm0, %xmm3
	minss	4(%r8), %xmm0
	minss	%xmm2, %xmm1
	maxss	12(%r8), %xmm2
	movlps	%xmm3, 16(%r8)
	unpcklps	%xmm0, %xmm1
	unpcklps	%xmm2, %xmm4
	movaps	%xmm1, %xmm0
	movlhps	%xmm4, %xmm0
	movups	%xmm0, (%r8)
	movq	(%rcx), %rax
	movss	20(%rcx), %xmm0
	movq	%rax, 8(%rsp)
	movss	%xmm0, 16(%rsp)
	call	_ZNK9TransformclERK6Point3IfE
	movq	16(%r8), %xmm1
	movq	28(%rsp), %xmm0
	movss	24(%rsp), %xmm2
	movss	32(%rsp), %xmm4
	movaps	%xmm1, %xmm3
	movss	(%r8), %xmm1
	minss	8(%r8), %xmm4
	maxps	%xmm0, %xmm3
	minss	4(%r8), %xmm0
	minss	%xmm2, %xmm1
	maxss	12(%r8), %xmm2
	movlps	%xmm3, 16(%r8)
	unpcklps	%xmm0, %xmm1
	unpcklps	%xmm2, %xmm4
	movaps	%xmm1, %xmm0
	movlhps	%xmm4, %xmm0
	movups	%xmm0, (%r8)
	movss	16(%rcx), %xmm2
	movss	(%rcx), %xmm1
	movss	20(%rcx), %xmm0
	unpcklps	%xmm2, %xmm1
	movlps	%xmm1, 8(%rsp)
	movss	%xmm0, 16(%rsp)
	call	_ZNK9TransformclERK6Point3IfE
	movq	16(%r8), %xmm1
	movq	28(%rsp), %xmm0
	movss	24(%rsp), %xmm2
	movss	32(%rsp), %xmm4
	movaps	%xmm1, %xmm3
	movss	(%r8), %xmm1
	minss	8(%r8), %xmm4
	maxps	%xmm0, %xmm3
	minss	4(%r8), %xmm0
	minss	%xmm2, %xmm1
	maxss	12(%r8), %xmm2
	movlps	%xmm3, 16(%r8)
	unpcklps	%xmm0, %xmm1
	unpcklps	%xmm2, %xmm4
	movaps	%xmm1, %xmm0
	movlhps	%xmm4, %xmm0
	movups	%xmm0, (%r8)
	movq	12(%rcx), %rax
	movss	8(%rcx), %xmm0
	movq	%rax, 8(%rsp)
	movss	%xmm0, 16(%rsp)
	call	_ZNK9TransformclERK6Point3IfE
	movq	16(%r8), %xmm1
	movq	28(%rsp), %xmm0
	movss	24(%rsp), %xmm2
	movss	32(%rsp), %xmm4
	movaps	%xmm1, %xmm3
	movss	(%r8), %xmm1
	minss	8(%r8), %xmm4
	maxps	%xmm0, %xmm3
	minss	4(%r8), %xmm0
	minss	%xmm2, %xmm1
	maxss	12(%r8), %xmm2
	movlps	%xmm3, 16(%r8)
	unpcklps	%xmm0, %xmm1
	unpcklps	%xmm2, %xmm4
	movaps	%xmm1, %xmm0
	movlhps	%xmm4, %xmm0
	movups	%xmm0, (%r8)
	movss	4(%rcx), %xmm2
	movss	12(%rcx), %xmm1
	movss	20(%rcx), %xmm0
	unpcklps	%xmm2, %xmm1
	movlps	%xmm1, 8(%rsp)
	movss	%xmm0, 16(%rsp)
	call	_ZNK9TransformclERK6Point3IfE
	movq	16(%r8), %xmm1
	movq	28(%rsp), %xmm0
	movss	24(%rsp), %xmm2
	movss	32(%rsp), %xmm4
	movaps	%xmm1, %xmm3
	movss	(%r8), %xmm1
	minss	8(%r8), %xmm4
	maxps	%xmm0, %xmm3
	minss	4(%r8), %xmm0
	minss	%xmm2, %xmm1
	maxss	12(%r8), %xmm2
	movlps	%xmm3, 16(%r8)
	unpcklps	%xmm0, %xmm1
	unpcklps	%xmm2, %xmm4
	movaps	%xmm1, %xmm0
	movlhps	%xmm4, %xmm0
	movups	%xmm0, (%r8)
	movss	20(%rcx), %xmm0
	movq	12(%rcx), %rax
	movss	%xmm0, 16(%rsp)
	movq	%rax, 8(%rsp)
	call	_ZNK9TransformclERK6Point3IfE
	movq	16(%r8), %xmm1
	movq	28(%rsp), %xmm0
	movss	24(%rsp), %xmm2
	movss	32(%rsp), %xmm4
	movaps	%xmm1, %xmm3
	movss	(%r8), %xmm1
	minss	8(%r8), %xmm4
	maxps	%xmm0, %xmm3
	minss	4(%r8), %xmm0
	minss	%xmm2, %xmm1
	maxss	12(%r8), %xmm2
	movlps	%xmm3, 16(%r8)
	unpcklps	%xmm0, %xmm1
	unpcklps	%xmm2, %xmm4
	movaps	%xmm1, %xmm0
	movlhps	%xmm4, %xmm0
	movups	%xmm0, (%r8)
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L264
	movq	%r8, %rax
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L264:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3935:
	.size	_ZNK9TransformclERK12BoundingBox3IfE, .-_ZNK9TransformclERK12BoundingBox3IfE
	.align 2
	.p2align 4
	.globl	_ZNK9TransformmlERKS_
	.type	_ZNK9TransformmlERKS_, @function
_ZNK9TransformmlERKS_:
.LFB3946:
	.cfi_startproc
	endbr64
	movups	(%rsi), %xmm3
	movups	32(%rdx), %xmm6
	movq	%rdi, %rax
	movups	48(%rdx), %xmm7
	movups	(%rdx), %xmm4
	movaps	%xmm3, %xmm8
	movaps	%xmm3, %xmm9
	movups	16(%rdx), %xmm5
	movups	16(%rsi), %xmm2
	shufps	$170, %xmm3, %xmm8
	mulps	%xmm6, %xmm8
	movups	32(%rsi), %xmm1
	movups	48(%rsi), %xmm0
	shufps	$255, %xmm3, %xmm9
	mulps	%xmm7, %xmm9
	addps	%xmm9, %xmm8
	movaps	%xmm3, %xmm9
	shufps	$0, %xmm3, %xmm9
	shufps	$85, %xmm3, %xmm3
	mulps	%xmm4, %xmm9
	mulps	%xmm5, %xmm3
	addps	%xmm9, %xmm3
	addps	%xmm8, %xmm3
	movaps	%xmm2, %xmm8
	shufps	$170, %xmm2, %xmm8
	mulps	%xmm6, %xmm8
	movups	%xmm3, (%rdi)
	movaps	%xmm2, %xmm3
	shufps	$255, %xmm2, %xmm3
	mulps	%xmm7, %xmm3
	addps	%xmm8, %xmm3
	movaps	%xmm2, %xmm8
	shufps	$85, %xmm2, %xmm8
	shufps	$0, %xmm2, %xmm2
	mulps	%xmm5, %xmm8
	mulps	%xmm4, %xmm2
	addps	%xmm8, %xmm2
	addps	%xmm3, %xmm2
	movaps	%xmm1, %xmm3
	shufps	$170, %xmm1, %xmm3
	mulps	%xmm6, %xmm3
	movups	%xmm2, 16(%rdi)
	movaps	%xmm1, %xmm2
	shufps	$255, %xmm1, %xmm2
	mulps	%xmm7, %xmm2
	addps	%xmm3, %xmm2
	movaps	%xmm1, %xmm3
	shufps	$85, %xmm1, %xmm3
	shufps	$0, %xmm1, %xmm1
	mulps	%xmm5, %xmm3
	mulps	%xmm4, %xmm1
	addps	%xmm3, %xmm1
	addps	%xmm2, %xmm1
	movaps	%xmm0, %xmm2
	shufps	$170, %xmm0, %xmm2
	mulps	%xmm6, %xmm2
	movups	%xmm1, 32(%rdi)
	movaps	%xmm0, %xmm1
	shufps	$255, %xmm0, %xmm1
	mulps	%xmm7, %xmm1
	addps	%xmm2, %xmm1
	movaps	%xmm0, %xmm2
	shufps	$85, %xmm0, %xmm2
	shufps	$0, %xmm0, %xmm0
	mulps	%xmm5, %xmm2
	mulps	%xmm4, %xmm0
	addps	%xmm2, %xmm0
	addps	%xmm1, %xmm0
	movups	%xmm0, 48(%rdi)
	ret
	.cfi_endproc
.LFE3946:
	.size	_ZNK9TransformmlERKS_, .-_ZNK9TransformmlERKS_
	.align 2
	.p2align 4
	.globl	_ZNK9TransformclERKS_
	.type	_ZNK9TransformclERKS_, @function
_ZNK9TransformclERKS_:
.LFB3947:
	.cfi_startproc
	endbr64
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	_ZNK9TransformmlERKS_
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L269
	movq	%rdi, %rax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L269:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3947:
	.size	_ZNK9TransformclERKS_, .-_ZNK9TransformclERKS_
	.align 2
	.p2align 4
	.globl	_ZNK9Transform16swaps_handednessEv
	.type	_ZNK9Transform16swaps_handednessEv, @function
_ZNK9Transform16swaps_handednessEv:
.LFB3948:
	.cfi_startproc
	endbr64
	movss	20(%rdi), %xmm3
	movss	24(%rdi), %xmm2
	movss	40(%rdi), %xmm4
	movss	36(%rdi), %xmm1
	movss	32(%rdi), %xmm5
	movss	16(%rdi), %xmm6
	movaps	%xmm3, %xmm0
	movaps	%xmm2, %xmm7
	mulss	%xmm1, %xmm7
	mulss	%xmm4, %xmm0
	mulss	%xmm5, %xmm2
	mulss	%xmm6, %xmm4
	mulss	%xmm6, %xmm1
	mulss	%xmm5, %xmm3
	subss	%xmm7, %xmm0
	mulss	(%rdi), %xmm0
	subss	%xmm4, %xmm2
	mulss	4(%rdi), %xmm2
	subss	%xmm3, %xmm1
	mulss	8(%rdi), %xmm1
	addss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	comiss	%xmm0, %xmm1
	seta	%al
	ret
	.cfi_endproc
.LFE3948:
	.size	_ZNK9Transform16swaps_handednessEv, .-_ZNK9Transform16swaps_handednessEv
	.align 2
	.p2align 4
	.globl	_ZNK9TransformclERK6Point3IfER7Vector3IfE
	.type	_ZNK9TransformclERK6Point3IfER7Vector3IfE, @function
_ZNK9TransformclERK6Point3IfER7Vector3IfE:
.LFB3949:
	.cfi_startproc
	endbr64
	movq	(%rdx), %xmm2
	movss	32(%rsi), %xmm1
	movss	.LC12(%rip), %xmm4
	movq	%rdi, %rax
	movss	36(%rsi), %xmm3
	movss	8(%rdx), %xmm8
	movaps	%xmm2, %xmm0
	movaps	%xmm2, %xmm7
	movaps	%xmm2, %xmm6
	shufps	$0xe5, %xmm2, %xmm2
	mulss	%xmm0, %xmm1
	movss	44(%rsi), %xmm9
	movss	16(%rsi), %xmm10
	shufps	$0xe0, %xmm7, %xmm7
	mulss	%xmm2, %xmm3
	shufps	$0xe5, %xmm6, %xmm6
	movaps	%xmm8, %xmm5
	movss	28(%rsi), %xmm11
	shufps	$0xe0, %xmm5, %xmm5
	andps	%xmm4, %xmm1
	andps	%xmm4, %xmm3
	addss	%xmm3, %xmm1
	movss	40(%rsi), %xmm3
	mulss	%xmm8, %xmm3
	andps	%xmm4, %xmm3
	andps	%xmm9, %xmm4
	movq	.LC13(%rip), %xmm9
	addss	%xmm4, %xmm3
	movss	20(%rsi), %xmm4
	addss	%xmm1, %xmm3
	movss	4(%rsi), %xmm1
	mulss	.LC16(%rip), %xmm3
	unpcklps	%xmm4, %xmm1
	movss	(%rsi), %xmm4
	mulps	%xmm6, %xmm1
	unpcklps	%xmm10, %xmm4
	movss	24(%rsi), %xmm10
	mulps	%xmm7, %xmm4
	andps	%xmm9, %xmm1
	andps	%xmm9, %xmm4
	addps	%xmm4, %xmm1
	movss	8(%rsi), %xmm4
	unpcklps	%xmm10, %xmm4
	movss	12(%rsi), %xmm10
	movss	%xmm3, 8(%rcx)
	mulps	%xmm5, %xmm4
	unpcklps	%xmm11, %xmm10
	andps	%xmm9, %xmm4
	andps	%xmm10, %xmm9
	addps	%xmm9, %xmm4
	addps	%xmm4, %xmm1
	movq	.LC17(%rip), %xmm4
	mulps	%xmm4, %xmm1
	movlps	%xmm1, (%rcx)
	movss	48(%rsi), %xmm1
	movss	52(%rsi), %xmm3
	movss	20(%rsi), %xmm4
	mulss	%xmm2, %xmm3
	mulss	%xmm0, %xmm1
	mulss	36(%rsi), %xmm2
	mulss	32(%rsi), %xmm0
	addss	%xmm3, %xmm1
	movss	56(%rsi), %xmm3
	mulss	%xmm8, %xmm3
	addss	%xmm2, %xmm0
	movss	16(%rsi), %xmm2
	addss	60(%rsi), %xmm3
	addss	%xmm3, %xmm1
	movss	.LC11(%rip), %xmm3
	divss	%xmm1, %xmm3
	movss	40(%rsi), %xmm1
	mulss	%xmm8, %xmm1
	addss	44(%rsi), %xmm1
	addss	%xmm1, %xmm0
	movss	(%rsi), %xmm1
	unpcklps	%xmm2, %xmm1
	movss	4(%rsi), %xmm2
	mulps	%xmm7, %xmm1
	unpcklps	%xmm4, %xmm2
	movss	24(%rsi), %xmm4
	mulps	%xmm6, %xmm2
	addps	%xmm2, %xmm1
	movss	8(%rsi), %xmm2
	mulss	%xmm3, %xmm0
	unpcklps	%xmm4, %xmm2
	movss	12(%rsi), %xmm4
	shufps	$0xe0, %xmm3, %xmm3
	mulps	%xmm5, %xmm2
	movss	28(%rsi), %xmm5
	unpcklps	%xmm5, %xmm4
	movss	%xmm0, 8(%rdi)
	addps	%xmm4, %xmm2
	addps	%xmm2, %xmm1
	mulps	%xmm3, %xmm1
	movlps	%xmm1, (%rdi)
	ret
	.cfi_endproc
.LFE3949:
	.size	_ZNK9TransformclERK6Point3IfER7Vector3IfE, .-_ZNK9TransformclERK6Point3IfER7Vector3IfE
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC18:
	.string	"Transform doesn't support pError transformation"
	.section	.text.unlikely,"ax",@progbits
	.align 2
	.globl	_ZNK9TransformclERK6Point3IfERK7Vector3IfERS5_
	.type	_ZNK9TransformclERK6Point3IfERK7Vector3IfERS5_, @function
_ZNK9TransformclERK6Point3IfERK7Vector3IfERS5_:
.LFB3950:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3950
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	$16, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rax
	.cfi_def_cfa_offset 32
	call	__cxa_allocate_exception@PLT
	leaq	.LC18(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %rbp
.LEHB0:
	call	_ZNSt13runtime_errorC1EPKc@PLT
.LEHE0:
	movq	_ZNSt13runtime_errorD1Ev@GOTPCREL(%rip), %rdx
	leaq	_ZTISt13runtime_error(%rip), %rsi
	movq	%rbp, %rdi
.LEHB1:
	call	__cxa_throw@PLT
.L274:
	endbr64
	movq	%rax, %r12
.L273:
	movq	%rbp, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rdi
	call	_Unwind_Resume@PLT
.LEHE1:
	.cfi_endproc
.LFE3950:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA3950:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3950-.LLSDACSB3950
.LLSDACSB3950:
	.uleb128 .LEHB0-.LFB3950
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L274-.LFB3950
	.uleb128 0
	.uleb128 .LEHB1-.LFB3950
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE3950:
	.section	.text.unlikely
	.size	_ZNK9TransformclERK6Point3IfERK7Vector3IfERS5_, .-_ZNK9TransformclERK6Point3IfERK7Vector3IfERS5_
	.text
	.align 2
	.p2align 4
	.globl	_ZNK9TransformclERK7Vector3IfERS1_
	.type	_ZNK9TransformclERK7Vector3IfERS1_, @function
_ZNK9TransformclERK7Vector3IfERS1_:
.LFB3951:
	.cfi_startproc
	endbr64
	movq	%rsi, %rax
	movss	(%rdx), %xmm3
	movss	4(%rdx), %xmm1
	movq	%rdi, %r8
	movss	32(%rax), %xmm0
	movss	8(%rdx), %xmm2
	movq	%rdx, %rsi
	pxor	%xmm4, %xmm4
	mulss	%xmm3, %xmm0
	cvttss2sil	%xmm0, %edi
	movss	36(%rax), %xmm0
	mulss	%xmm1, %xmm0
	movl	%edi, %edx
	negl	%edx
	cmovs	%edi, %edx
	cvttss2sil	%xmm0, %r9d
	movss	40(%rax), %xmm0
	mulss	%xmm2, %xmm0
	movl	%r9d, %edi
	negl	%edi
	cmovs	%r9d, %edi
	cvttss2sil	%xmm0, %r9d
	movss	4(%rax), %xmm0
	addl	%edi, %edx
	mulss	%xmm1, %xmm0
	mulss	20(%rax), %xmm1
	movl	%r9d, %edi
	negl	%edi
	cmovs	%r9d, %edi
	addl	%edi, %edx
	cvttss2sil	%xmm0, %edi
	cvtsi2ssl	%edx, %xmm4
	mulss	.LC16(%rip), %xmm4
	movl	%edi, %edx
	negl	%edx
	cmovns	%edx, %edi
	movd	%edi, %xmm0
	cvttss2sil	%xmm1, %edi
	movss	(%rax), %xmm1
	mulss	%xmm3, %xmm1
	mulss	16(%rax), %xmm3
	movl	%edi, %edx
	negl	%edx
	cmovs	%edi, %edx
	cvttss2sil	%xmm1, %edi
	movd	%edx, %xmm7
	punpckldq	%xmm7, %xmm0
	movl	%edi, %edx
	negl	%edx
	cmovns	%edx, %edi
	movd	%edi, %xmm1
	cvttss2sil	%xmm3, %edi
	movl	%edi, %edx
	negl	%edx
	cmovs	%edi, %edx
	movd	%edx, %xmm5
	punpckldq	%xmm5, %xmm1
	paddd	%xmm1, %xmm0
	movss	8(%rax), %xmm1
	mulss	%xmm2, %xmm1
	mulss	24(%rax), %xmm2
	movss	%xmm4, 8(%rcx)
	cvttss2sil	%xmm1, %edi
	movl	%edi, %edx
	negl	%edx
	cmovns	%edx, %edi
	movd	%edi, %xmm1
	cvttss2sil	%xmm2, %edi
	movl	%edi, %edx
	negl	%edx
	cmovs	%edi, %edx
	movd	%edx, %xmm7
	punpckldq	%xmm7, %xmm1
	paddd	%xmm1, %xmm0
	movq	.LC17(%rip), %xmm1
	cvtdq2ps	%xmm0, %xmm0
	mulps	%xmm1, %xmm0
	movlps	%xmm0, (%rcx)
	movq	(%rsi), %xmm2
	movss	8(%rsi), %xmm3
	movss	32(%rax), %xmm0
	movss	40(%rax), %xmm1
	movaps	%xmm2, %xmm6
	movss	16(%rax), %xmm4
	movss	20(%rax), %xmm5
	mulss	%xmm3, %xmm1
	shufps	$0xe5, %xmm6, %xmm6
	shufps	$0xe0, %xmm3, %xmm3
	mulss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	movss	36(%rax), %xmm1
	mulss	%xmm6, %xmm1
	addss	%xmm1, %xmm0
	movss	(%rax), %xmm1
	unpcklps	%xmm4, %xmm1
	movaps	%xmm2, %xmm4
	shufps	$0xe5, %xmm2, %xmm2
	shufps	$0xe0, %xmm4, %xmm4
	mulps	%xmm4, %xmm1
	movss	4(%rax), %xmm4
	unpcklps	%xmm5, %xmm4
	mulps	%xmm4, %xmm2
	movss	24(%rax), %xmm4
	addps	%xmm2, %xmm1
	movss	8(%rax), %xmm2
	movss	%xmm0, 8(%r8)
	movq	%r8, %rax
	unpcklps	%xmm4, %xmm2
	mulps	%xmm3, %xmm2
	addps	%xmm2, %xmm1
	movlps	%xmm1, (%r8)
	ret
	.cfi_endproc
.LFE3951:
	.size	_ZNK9TransformclERK7Vector3IfERS1_, .-_ZNK9TransformclERK7Vector3IfERS1_
	.section	.rodata.str1.8
	.align 8
.LC19:
	.string	"Transform doesn't support vError transformation"
	.section	.text.unlikely
	.align 2
	.globl	_ZNK9TransformclERK7Vector3IfES3_RS1_
	.type	_ZNK9TransformclERK7Vector3IfES3_RS1_, @function
_ZNK9TransformclERK7Vector3IfES3_RS1_:
.LFB3952:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3952
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movl	$16, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rax
	.cfi_def_cfa_offset 32
	call	__cxa_allocate_exception@PLT
	leaq	.LC19(%rip), %rsi
	movq	%rax, %rdi
	movq	%rax, %rbp
.LEHB2:
	call	_ZNSt13runtime_errorC1EPKc@PLT
.LEHE2:
	movq	_ZNSt13runtime_errorD1Ev@GOTPCREL(%rip), %rdx
	leaq	_ZTISt13runtime_error(%rip), %rsi
	movq	%rbp, %rdi
.LEHB3:
	call	__cxa_throw@PLT
.L279:
	endbr64
	movq	%rax, %r12
.L278:
	movq	%rbp, %rdi
	call	__cxa_free_exception@PLT
	movq	%r12, %rdi
	call	_Unwind_Resume@PLT
.LEHE3:
	.cfi_endproc
.LFE3952:
	.section	.gcc_except_table
.LLSDA3952:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3952-.LLSDACSB3952
.LLSDACSB3952:
	.uleb128 .LEHB2-.LFB3952
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L279-.LFB3952
	.uleb128 0
	.uleb128 .LEHB3-.LFB3952
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE3952:
	.section	.text.unlikely
	.size	_ZNK9TransformclERK7Vector3IfES3_RS1_, .-_ZNK9TransformclERK7Vector3IfES3_RS1_
	.text
	.align 2
	.p2align 4
	.globl	_ZNK9TransformclERK3RayR7Vector3IfES5_
	.type	_ZNK9TransformclERK3RayR7Vector3IfES5_, @function
_ZNK9TransformclERK3RayR7Vector3IfES5_:
.LFB3953:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %r10
	movq	%rdx, %r11
	movq	%rcx, %rbx
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	_ZNK9TransformclERK6Point3IfER7Vector3IfE
	addq	$12, %rdx
	leaq	12(%rsp), %rdi
	movq	%r8, %rcx
	call	_ZNK9TransformclERK7Vector3IfERS1_
	movss	12(%rsp), %xmm4
	movss	16(%rsp), %xmm0
	movss	20(%rsp), %xmm3
	movss	36(%r11), %xmm6
	movaps	%xmm4, %xmm2
	movaps	%xmm0, %xmm1
	mulss	%xmm0, %xmm1
	mulss	%xmm4, %xmm2
	addss	%xmm1, %xmm2
	movaps	%xmm3, %xmm1
	mulss	%xmm3, %xmm1
	addss	%xmm1, %xmm2
	comiss	.LC5(%rip), %xmm2
	jbe	.L286
	movss	.LC12(%rip), %xmm5
	movaps	%xmm4, %xmm1
	movaps	%xmm0, %xmm7
	andps	%xmm5, %xmm1
	andps	%xmm5, %xmm7
	andps	%xmm3, %xmm5
	mulss	4(%rbx), %xmm7
	mulss	(%rbx), %xmm1
	mulss	8(%rbx), %xmm5
	addss	%xmm7, %xmm1
	movaps	%xmm0, %xmm7
	addss	%xmm5, %xmm1
	divss	%xmm2, %xmm1
	movaps	%xmm1, %xmm2
	movaps	%xmm1, %xmm5
	subss	%xmm1, %xmm6
	mulss	%xmm4, %xmm2
	mulss	%xmm1, %xmm7
	addss	(%rsp), %xmm2
	mulss	%xmm3, %xmm5
	addss	4(%rsp), %xmm7
	addss	8(%rsp), %xmm5
.L283:
	movaps	%xmm2, %xmm1
	unpcklps	%xmm4, %xmm5
	movzbl	40(%r11), %eax
	unpcklps	%xmm7, %xmm1
	movlhps	%xmm5, %xmm1
	movb	%al, 40(%r10)
	movups	%xmm1, (%r10)
	movss	.LC11(%rip), %xmm1
	movaps	%xmm1, %xmm2
	divss	%xmm4, %xmm2
	movaps	%xmm1, %xmm4
	divss	%xmm0, %xmm4
	unpcklps	%xmm3, %xmm0
	divss	%xmm3, %xmm1
	unpcklps	%xmm4, %xmm2
	movlhps	%xmm2, %xmm0
	movups	%xmm0, 16(%r10)
	unpcklps	%xmm6, %xmm1
	movlps	%xmm1, 32(%r10)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L287
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	movq	%r10, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L286:
	.cfi_restore_state
	movss	(%rsp), %xmm2
	movss	4(%rsp), %xmm7
	movss	8(%rsp), %xmm5
	jmp	.L283
.L287:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3953:
	.size	_ZNK9TransformclERK3RayR7Vector3IfES5_, .-_ZNK9TransformclERK3RayR7Vector3IfES5_
	.align 2
	.p2align 4
	.globl	_ZNK9TransformclEPKS_
	.type	_ZNK9TransformclEPKS_, @function
_ZNK9TransformclEPKS_:
.LFB3958:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rsi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, %rbp
	movl	$64, %edi
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	call	_Znwm@PLT
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rax, %rdi
	movq	%rax, %r8
	call	_ZNK9TransformmlERKS_
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L291
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	movq	%r8, %rax
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L291:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3958:
	.size	_ZNK9TransformclEPKS_, .-_ZNK9TransformclEPKS_
	.p2align 4
	.globl	_Z9transposeRK9Transform
	.type	_Z9transposeRK9Transform, @function
_Z9transposeRK9Transform:
.LFB3961:
	.cfi_startproc
	endbr64
	movups	(%rsi), %xmm0
	movups	32(%rsi), %xmm3
	movq	%rdi, %rax
	movups	16(%rsi), %xmm1
	movups	48(%rsi), %xmm4
	movaps	%xmm0, %xmm2
	unpckhps	%xmm3, %xmm0
	unpcklps	%xmm3, %xmm2
	movaps	%xmm1, %xmm3
	unpckhps	%xmm4, %xmm1
	unpcklps	%xmm4, %xmm3
	movaps	%xmm2, %xmm4
	unpckhps	%xmm3, %xmm2
	unpcklps	%xmm3, %xmm4
	movups	%xmm2, 16(%rdi)
	movaps	%xmm0, %xmm2
	unpckhps	%xmm1, %xmm0
	unpcklps	%xmm1, %xmm2
	movups	%xmm4, (%rdi)
	movups	%xmm2, 32(%rdi)
	movups	%xmm0, 48(%rdi)
	ret
	.cfi_endproc
.LFE3961:
	.size	_Z9transposeRK9Transform, .-_Z9transposeRK9Transform
	.p2align 4
	.globl	_Z9transposePK9Transform
	.type	_Z9transposePK9Transform, @function
_Z9transposePK9Transform:
.LFB3962:
	.cfi_startproc
	endbr64
	subq	$72, %rsp
	.cfi_def_cfa_offset 80
	movups	(%rdi), %xmm0
	movups	32(%rdi), %xmm3
	movups	16(%rdi), %xmm1
	movups	48(%rdi), %xmm4
	movl	$64, %edi
	movaps	%xmm0, %xmm2
	unpckhps	%xmm3, %xmm0
	unpcklps	%xmm3, %xmm2
	movaps	%xmm1, %xmm3
	unpckhps	%xmm4, %xmm1
	unpcklps	%xmm4, %xmm3
	movaps	%xmm2, %xmm4
	unpcklps	%xmm3, %xmm4
	unpckhps	%xmm3, %xmm2
	movaps	%xmm0, %xmm3
	unpcklps	%xmm1, %xmm3
	unpckhps	%xmm1, %xmm0
	movaps	%xmm4, 48(%rsp)
	movaps	%xmm2, 32(%rsp)
	movaps	%xmm3, 16(%rsp)
	movaps	%xmm0, (%rsp)
	call	_Znwm@PLT
	movaps	48(%rsp), %xmm4
	movaps	32(%rsp), %xmm2
	movaps	16(%rsp), %xmm3
	movaps	(%rsp), %xmm0
	movups	%xmm4, (%rax)
	movups	%xmm2, 16(%rax)
	movups	%xmm3, 32(%rax)
	movups	%xmm0, 48(%rax)
	addq	$72, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3962:
	.size	_Z9transposePK9Transform, .-_Z9transposePK9Transform
	.p2align 4
	.globl	_Z9translateRK7Vector3IfE
	.type	_Z9translateRK7Vector3IfE, @function
_Z9translateRK7Vector3IfE:
.LFB3963:
	.cfi_startproc
	endbr64
	movq	.LC20(%rip), %rdx
	movss	8(%rsi), %xmm0
	movq	%rdi, %rax
	movss	4(%rsi), %xmm1
	movss	(%rsi), %xmm2
	movl	$0x00000000, 8(%rdi)
	movq	%rdx, (%rdi)
	movabsq	$4575657221408423936, %rdx
	movq	%rdx, 16(%rdi)
	movl	$0x00000000, 24(%rdi)
	movq	$0, 32(%rdi)
	movl	$0x3f800000, 40(%rdi)
	movq	$0, 48(%rdi)
	movq	%rdx, 56(%rdi)
	movss	%xmm2, 12(%rdi)
	movss	%xmm1, 28(%rdi)
	movss	%xmm0, 44(%rdi)
	ret
	.cfi_endproc
.LFE3963:
	.size	_Z9translateRK7Vector3IfE, .-_Z9translateRK7Vector3IfE
	.p2align 4
	.globl	_Z5scalefff
	.type	_Z5scalefff, @function
_Z5scalefff:
.LFB3967:
	.cfi_startproc
	endbr64
	movq	$0, 4(%rdi)
	movq	%rdi, %rax
	movq	$0, 12(%rdi)
	movq	$0, 24(%rdi)
	movq	$0, 32(%rdi)
	movq	$0, 44(%rdi)
	movq	$0, 52(%rdi)
	movl	$0x3f800000, 60(%rdi)
	movss	%xmm0, (%rdi)
	movss	%xmm1, 20(%rdi)
	movss	%xmm2, 40(%rdi)
	ret
	.cfi_endproc
.LFE3967:
	.size	_Z5scalefff, .-_Z5scalefff
	.p2align 4
	.globl	_Z7rotateXf
	.type	_Z7rotateXf, @function
_Z7rotateXf:
.LFB3968:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	mulss	.LC21(%rip), %xmm0
	leaq	12(%rsp), %rdi
	leaq	8(%rsp), %rsi
	cvtss2sd	%xmm0, %xmm0
	mulsd	.LC22(%rip), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	call	sincosf@PLT
	movss	12(%rsp), %xmm0
	movq	%r12, %rax
	movss	8(%rsp), %xmm1
	movss	.LC0(%rip), %xmm2
	movl	$0x00000000, 16(%r12)
	movaps	%xmm0, %xmm3
	xorps	.LC23(%rip), %xmm3
	movups	%xmm2, (%r12)
	movq	$0, 28(%r12)
	unpcklps	%xmm1, %xmm0
	movaps	%xmm1, %xmm2
	movlps	%xmm0, 36(%r12)
	unpcklps	%xmm3, %xmm2
	pxor	%xmm0, %xmm0
	movl	$0x3f800000, 60(%r12)
	movlps	%xmm2, 20(%r12)
	movups	%xmm0, 44(%r12)
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3968:
	.size	_Z7rotateXf, .-_Z7rotateXf
	.p2align 4
	.globl	_Z7rotateYf
	.type	_Z7rotateYf, @function
_Z7rotateYf:
.LFB3969:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	mulss	.LC21(%rip), %xmm0
	leaq	12(%rsp), %rdi
	leaq	8(%rsp), %rsi
	cvtss2sd	%xmm0, %xmm0
	mulsd	.LC22(%rip), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	call	sincosf@PLT
	movss	12(%rsp), %xmm0
	movq	%r12, %rax
	movl	$0x00000000, 4(%r12)
	movss	8(%rsp), %xmm1
	movss	%xmm0, 8(%r12)
	xorps	.LC23(%rip), %xmm0
	movq	$0, 12(%r12)
	movq	$1065353216, 20(%r12)
	movl	$0x00000000, 28(%r12)
	movl	$0x00000000, 36(%r12)
	movq	$0, 44(%r12)
	movq	$0, 52(%r12)
	movl	$0x3f800000, 60(%r12)
	movss	%xmm1, (%r12)
	movss	%xmm0, 32(%r12)
	movss	%xmm1, 40(%r12)
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3969:
	.size	_Z7rotateYf, .-_Z7rotateYf
	.p2align 4
	.globl	_Z7rotateZf
	.type	_Z7rotateZf, @function
_Z7rotateZf:
.LFB3970:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	mulss	.LC21(%rip), %xmm0
	leaq	12(%rsp), %rdi
	leaq	8(%rsp), %rsi
	cvtss2sd	%xmm0, %xmm0
	mulsd	.LC22(%rip), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	call	sincosf@PLT
	movss	8(%rsp), %xmm1
	movss	12(%rsp), %xmm0
	movq	$0, 8(%r12)
	movq	.LC24(%rip), %rax
	movaps	%xmm0, %xmm3
	unpcklps	%xmm1, %xmm0
	xorps	.LC23(%rip), %xmm3
	movlps	%xmm0, 16(%r12)
	movaps	%xmm1, %xmm2
	pxor	%xmm0, %xmm0
	movups	%xmm0, 24(%r12)
	unpcklps	%xmm3, %xmm2
	movss	.LC0(%rip), %xmm0
	movq	%rax, 56(%r12)
	movq	%r12, %rax
	movlps	%xmm2, (%r12)
	movups	%xmm0, 40(%r12)
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3970:
	.size	_Z7rotateZf, .-_Z7rotateZf
	.p2align 4
	.globl	_Z11base_changeRK6Point3IfERK7Vector3IfES6_S6_
	.type	_Z11base_changeRK6Point3IfERK7Vector3IfES6_S6_, @function
_Z11base_changeRK6Point3IfERK7Vector3IfES6_S6_:
.LFB3971:
	.cfi_startproc
	endbr64
	movss	8(%rsi), %xmm0
	movss	8(%r8), %xmm1
	movq	%rdi, %rax
	movss	8(%rcx), %xmm2
	movss	4(%rcx), %xmm3
	unpcklps	%xmm0, %xmm1
	movss	8(%rdx), %xmm0
	movss	(%rcx), %xmm4
	unpcklps	%xmm2, %xmm0
	movss	4(%r8), %xmm2
	movlhps	%xmm1, %xmm0
	movss	4(%rsi), %xmm1
	unpcklps	%xmm1, %xmm2
	movss	4(%rdx), %xmm1
	unpcklps	%xmm3, %xmm1
	movss	(%r8), %xmm3
	movlhps	%xmm2, %xmm1
	movss	(%rsi), %xmm2
	unpcklps	%xmm2, %xmm3
	movss	(%rdx), %xmm2
	movups	%xmm0, 32(%rdi)
	movaps	.LC3(%rip), %xmm0
	movups	%xmm1, 16(%rdi)
	unpcklps	%xmm4, %xmm2
	movups	%xmm0, 48(%rdi)
	movlhps	%xmm3, %xmm2
	movups	%xmm2, (%rdi)
	ret
	.cfi_endproc
.LFE3971:
	.size	_Z11base_changeRK6Point3IfERK7Vector3IfES6_S6_, .-_Z11base_changeRK6Point3IfERK7Vector3IfES6_S6_
	.p2align 4
	.globl	_Z15new_base_changeRK6Point3IfERK7Vector3IfES6_S6_
	.type	_Z15new_base_changeRK6Point3IfERK7Vector3IfES6_S6_, @function
_Z15new_base_changeRK6Point3IfERK7Vector3IfES6_S6_:
.LFB3972:
	.cfi_startproc
	endbr64
	subq	$56, %rsp
	.cfi_def_cfa_offset 64
	movss	8(%rdi), %xmm0
	movss	8(%rcx), %xmm1
	movss	8(%rdx), %xmm2
	movss	4(%rdx), %xmm3
	unpcklps	%xmm0, %xmm1
	movss	8(%rsi), %xmm0
	movss	(%rdx), %xmm4
	unpcklps	%xmm2, %xmm0
	movss	4(%rcx), %xmm2
	movlhps	%xmm1, %xmm0
	movss	4(%rdi), %xmm1
	movaps	%xmm0, 32(%rsp)
	unpcklps	%xmm1, %xmm2
	movss	4(%rsi), %xmm1
	unpcklps	%xmm3, %xmm1
	movss	(%rcx), %xmm3
	movlhps	%xmm2, %xmm1
	movss	(%rdi), %xmm2
	movl	$64, %edi
	movaps	%xmm1, 16(%rsp)
	unpcklps	%xmm2, %xmm3
	movss	(%rsi), %xmm2
	unpcklps	%xmm4, %xmm2
	movlhps	%xmm3, %xmm2
	movaps	%xmm2, (%rsp)
	call	_Znwm@PLT
	movaps	32(%rsp), %xmm0
	movaps	(%rsp), %xmm2
	movaps	16(%rsp), %xmm1
	movups	%xmm0, 32(%rax)
	movaps	.LC3(%rip), %xmm0
	movups	%xmm2, (%rax)
	movups	%xmm1, 16(%rax)
	movups	%xmm0, 48(%rax)
	addq	$56, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3972:
	.size	_Z15new_base_changeRK6Point3IfERK7Vector3IfES6_S6_, .-_Z15new_base_changeRK6Point3IfERK7Vector3IfES6_S6_
	.p2align 4
	.globl	_Z6rotatefRK7Vector3IfE
	.type	_Z6rotatefRK7Vector3IfE, @function
_Z6rotatefRK7Vector3IfE:
.LFB3973:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movss	(%rsi), %xmm5
	movss	4(%rsi), %xmm1
	movss	8(%rsi), %xmm3
	leaq	28(%rsp), %rdi
	leaq	24(%rsp), %rsi
	mulss	.LC21(%rip), %xmm0
	movaps	%xmm5, %xmm2
	movaps	%xmm1, %xmm6
	movaps	%xmm5, %xmm4
	mulss	%xmm1, %xmm6
	unpcklps	%xmm3, %xmm4
	mulss	%xmm5, %xmm2
	mulss	%xmm3, %xmm3
	cvtss2sd	%xmm0, %xmm0
	mulsd	.LC22(%rip), %xmm0
	addss	%xmm6, %xmm2
	cvtsd2ss	%xmm0, %xmm0
	addss	%xmm3, %xmm2
	movaps	%xmm2, %xmm3
	rsqrtss	%xmm3, %xmm3
	mulss	%xmm3, %xmm2
	mulss	%xmm3, %xmm2
	mulss	.LC26(%rip), %xmm3
	addss	.LC25(%rip), %xmm2
	mulss	%xmm3, %xmm2
	mulss	%xmm2, %xmm1
	movaps	%xmm2, %xmm8
	shufps	$0xe0, %xmm8, %xmm8
	mulps	%xmm4, %xmm8
	mulss	%xmm5, %xmm2
	movss	%xmm1, 4(%rsp)
	movaps	%xmm8, %xmm7
	movlps	%xmm8, 8(%rsp)
	movss	%xmm8, 16(%rsp)
	shufps	$0xe5, %xmm7, %xmm7
	movss	%xmm2, (%rsp)
	movss	%xmm7, 20(%rsp)
	call	sincosf@PLT
	movss	(%rsp), %xmm2
	movq	%r12, %rax
	movss	28(%rsp), %xmm7
	movq	8(%rsp), %xmm8
	movss	24(%rsp), %xmm6
	movl	$0x00000000, 12(%r12)
	movaps	%xmm2, %xmm5
	movss	16(%rsp), %xmm4
	movss	20(%rsp), %xmm3
	movl	$0x00000000, 28(%r12)
	mulss	%xmm2, %xmm2
	unpcklps	%xmm7, %xmm5
	movaps	%xmm6, %xmm0
	movq	$0, 44(%r12)
	movq	$0, 52(%r12)
	mulps	%xmm8, %xmm5
	movq	.LC27(%rip), %xmm8
	unpcklps	%xmm6, %xmm2
	subps	%xmm2, %xmm8
	movaps	%xmm4, %xmm2
	movaps	%xmm8, %xmm1
	shufps	$0xe5, %xmm1, %xmm1
	movaps	%xmm1, %xmm10
	movss	4(%rsp), %xmm1
	mulss	%xmm1, %xmm2
	movaps	%xmm1, %xmm9
	mulss	%xmm1, %xmm9
	unpcklps	%xmm2, %xmm0
	movaps	%xmm4, %xmm2
	mulps	%xmm8, %xmm0
	movaps	%xmm7, %xmm8
	mulss	%xmm1, %xmm8
	mulss	%xmm3, %xmm2
	mulss	%xmm3, %xmm1
	mulss	%xmm4, %xmm7
	mulss	%xmm3, %xmm3
	movaps	%xmm0, %xmm4
	subps	%xmm5, %xmm4
	mulss	%xmm10, %xmm2
	mulss	%xmm10, %xmm1
	movaps	%xmm0, %xmm10
	shufps	$0xe5, %xmm0, %xmm0
	addps	%xmm5, %xmm10
	shufps	$0xe5, %xmm5, %xmm5
	addss	%xmm5, %xmm0
	movss	%xmm10, %xmm4
	movss	%xmm0, 16(%r12)
	movlps	%xmm4, (%r12)
	movaps	%xmm2, %xmm4
	subss	%xmm8, %xmm2
	addss	%xmm8, %xmm4
	movss	%xmm2, 32(%r12)
	movss	%xmm4, 8(%r12)
	movss	.LC11(%rip), %xmm4
	movaps	%xmm4, %xmm0
	movss	%xmm4, 60(%r12)
	subss	%xmm9, %xmm0
	mulss	%xmm6, %xmm0
	addss	%xmm9, %xmm0
	movss	%xmm0, 20(%r12)
	movaps	%xmm1, %xmm0
	addss	%xmm7, %xmm1
	subss	%xmm7, %xmm0
	movss	%xmm1, 36(%r12)
	movss	%xmm0, 24(%r12)
	movaps	%xmm4, %xmm0
	subss	%xmm3, %xmm0
	mulss	%xmm6, %xmm0
	addss	%xmm3, %xmm0
	movss	%xmm0, 40(%r12)
	addq	$32, %rsp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3973:
	.size	_Z6rotatefRK7Vector3IfE, .-_Z6rotatefRK7Vector3IfE
	.p2align 4
	.globl	_Z7look_atRK6Point3IfES2_RK7Vector3IfE
	.type	_Z7look_atRK6Point3IfES2_RK7Vector3IfE, @function
_Z7look_atRK6Point3IfES2_RK7Vector3IfE:
.LFB3979:
	.cfi_startproc
	endbr64
	subq	$136, %rsp
	.cfi_def_cfa_offset 144
	movq	4(%rsi), %xmm0
	movss	(%rsi), %xmm5
	movq	%rdi, %r8
	movq	%fs:40, %rax
	movq	%rax, 120(%rsp)
	xorl	%eax, %eax
	movq	4(%rdx), %xmm9
	movq	(%rsi), %xmm1
	movq	(%rdx), %xmm2
	movaps	%xmm0, %xmm4
	movss	8(%rsi), %xmm12
	movss	%xmm0, 8(%rsp)
	subps	%xmm0, %xmm9
	shufps	$0xe5, %xmm4, %xmm4
	movaps	%xmm1, %xmm7
	movss	%xmm4, 36(%rsp)
	subps	%xmm1, %xmm2
	movss	8(%rdx), %xmm0
	movss	(%rdx), %xmm6
	movaps	%xmm12, %xmm10
	movss	.LC25(%rip), %xmm15
	movss	4(%rdx), %xmm8
	unpcklps	%xmm5, %xmm10
	movss	%xmm12, 24(%rsp)
	movaps	%xmm9, %xmm4
	movaps	%xmm0, %xmm13
	subss	4(%rsi), %xmm8
	movaps	%xmm2, %xmm1
	shufps	$0xe5, %xmm4, %xmm4
	movaps	%xmm4, %xmm3
	movaps	%xmm9, %xmm4
	mulss	%xmm9, %xmm4
	subss	%xmm12, %xmm13
	unpcklps	%xmm6, %xmm0
	mulss	%xmm2, %xmm1
	subss	%xmm5, %xmm6
	movq	(%rcx), %xmm5
	subps	%xmm10, %xmm0
	mulss	%xmm3, %xmm3
	movaps	%xmm5, %xmm11
	mulss	%xmm5, %xmm11
	addss	%xmm4, %xmm1
	addss	%xmm3, %xmm1
	movaps	%xmm1, %xmm4
	rsqrtss	%xmm4, %xmm4
	mulss	%xmm4, %xmm1
	movaps	%xmm4, %xmm3
	mulss	.LC26(%rip), %xmm3
	mulss	%xmm4, %xmm1
	addss	%xmm15, %xmm1
	mulss	%xmm3, %xmm1
	mulss	%xmm1, %xmm6
	movaps	%xmm1, %xmm4
	shufps	$0xe0, %xmm4, %xmm4
	mulps	%xmm4, %xmm2
	mulss	%xmm1, %xmm13
	mulss	%xmm1, %xmm8
	mulps	%xmm4, %xmm0
	mulps	%xmm4, %xmm9
	movaps	%xmm2, %xmm12
	movaps	%xmm5, %xmm2
	shufps	$0xe5, %xmm2, %xmm2
	movaps	%xmm2, %xmm1
	movss	8(%rcx), %xmm2
	movlps	%xmm12, 40(%rsp)
	mulss	%xmm1, %xmm1
	movaps	%xmm2, %xmm3
	movaps	%xmm2, %xmm10
	movaps	%xmm0, %xmm14
	mulss	%xmm2, %xmm3
	unpcklps	%xmm5, %xmm10
	movss	%xmm9, 4(%rsp)
	movaps	%xmm9, %xmm4
	shufps	$0xe5, %xmm4, %xmm4
	addss	%xmm11, %xmm1
	addss	%xmm1, %xmm3
	movaps	%xmm3, %xmm11
	rsqrtss	%xmm11, %xmm11
	mulss	%xmm11, %xmm3
	mulss	%xmm11, %xmm3
	mulss	.LC26(%rip), %xmm11
	addss	%xmm15, %xmm3
	mulss	%xmm11, %xmm3
	mulss	%xmm3, %xmm2
	movaps	%xmm3, %xmm0
	shufps	$0xe0, %xmm0, %xmm0
	mulps	%xmm0, %xmm10
	mulps	%xmm0, %xmm5
	movss	4(%rcx), %xmm0
	mulss	%xmm3, %xmm0
	mulps	%xmm12, %xmm10
	mulps	%xmm14, %xmm5
	movaps	%xmm0, %xmm1
	movss	(%rcx), %xmm0
	movaps	%xmm1, %xmm11
	mulss	%xmm3, %xmm0
	mulss	%xmm6, %xmm11
	subps	%xmm5, %xmm10
	mulss	%xmm13, %xmm1
	movaps	%xmm10, %xmm5
	movaps	%xmm10, %xmm12
	mulss	%xmm10, %xmm12
	movaps	%xmm0, %xmm3
	shufps	$0xe5, %xmm5, %xmm5
	mulss	%xmm8, %xmm3
	mulss	%xmm5, %xmm5
	mulss	%xmm13, %xmm0
	subss	%xmm11, %xmm3
	movaps	%xmm2, %xmm11
	mulss	%xmm8, %xmm2
	addss	%xmm12, %xmm5
	movss	4(%rsp), %xmm12
	mulss	%xmm6, %xmm11
	subss	%xmm2, %xmm1
	subss	%xmm0, %xmm11
	movaps	%xmm14, %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm1, %xmm2
	addss	%xmm2, %xmm5
	movaps	%xmm5, %xmm2
	rsqrtss	%xmm2, %xmm2
	mulss	%xmm2, %xmm5
	mulss	%xmm2, %xmm5
	mulss	.LC26(%rip), %xmm2
	addss	%xmm15, %xmm5
	mulss	%xmm2, %xmm5
	mulss	%xmm5, %xmm1
	movaps	%xmm5, %xmm2
	shufps	$0xe0, %xmm2, %xmm2
	mulps	%xmm10, %xmm2
	mulss	%xmm5, %xmm11
	mulss	%xmm5, %xmm3
	mulps	%xmm2, %xmm0
	movaps	%xmm0, %xmm15
	shufps	$0xe5, %xmm15, %xmm15
	movss	%xmm15, 20(%rsp)
	movaps	%xmm2, %xmm15
	shufps	$0xe5, %xmm15, %xmm15
	movaps	%xmm15, %xmm14
	movaps	%xmm15, %xmm10
	unpcklps	%xmm1, %xmm14
	mulps	%xmm9, %xmm14
	subps	%xmm0, %xmm14
	movaps	%xmm1, %xmm0
	mulss	%xmm13, %xmm0
	movaps	%xmm14, %xmm5
	movaps	%xmm14, %xmm9
	shufps	$0xe5, %xmm5, %xmm5
	movss	%xmm5, 12(%rsp)
	movaps	%xmm11, %xmm5
	mulss	%xmm6, %xmm5
	mulss	%xmm13, %xmm11
	movd	%xmm5, %eax
	movaps	%xmm1, %xmm5
	mulss	%xmm8, %xmm5
	movd	%eax, %xmm15
	subss	%xmm5, %xmm15
	movss	%xmm5, 28(%rsp)
	movaps	%xmm15, %xmm5
	movaps	%xmm3, %xmm15
	mulss	%xmm6, %xmm15
	mulss	%xmm5, %xmm12
	mulss	%xmm8, %xmm3
	subss	%xmm15, %xmm0
	subss	%xmm11, %xmm3
	movaps	%xmm7, %xmm11
	mulss	%xmm2, %xmm11
	movaps	%xmm0, %xmm15
	mulss	%xmm13, %xmm15
	movaps	%xmm4, %xmm13
	mulss	%xmm8, %xmm3
	mulss	%xmm14, %xmm13
	mulss	%xmm6, %xmm0
	subss	%xmm12, %xmm15
	movss	12(%rsp), %xmm12
	mulss	%xmm10, %xmm12
	movss	%xmm15, 16(%rsp)
	movaps	%xmm5, %xmm15
	mulss	%xmm2, %xmm15
	mulss	%xmm14, %xmm2
	subss	%xmm12, %xmm15
	movss	%xmm15, 32(%rsp)
	movaps	%xmm5, %xmm15
	movss	12(%rsp), %xmm12
	movss	8(%rsp), %xmm8
	mulss	%xmm6, %xmm15
	movlps	%xmm14, 64(%rsp)
	movaps	%xmm1, %xmm6
	mulss	%xmm1, %xmm8
	movss	%xmm5, 72(%rsp)
	mulss	%xmm12, %xmm6
	movl	$0x00000000, 104(%rsp)
	movq	$0, 96(%rsp)
	movd	%xmm15, %edx
	movaps	%xmm7, %xmm15
	mulss	%xmm10, %xmm15
	mulss	%xmm14, %xmm10
	movd	%edx, %xmm14
	subss	%xmm13, %xmm14
	movaps	%xmm3, %xmm13
	subss	%xmm0, %xmm13
	subss	%xmm3, %xmm0
	mulss	24(%rsp), %xmm0
	movd	%edx, %xmm3
	movd	%xmm14, %ecx
	movaps	%xmm13, %xmm14
	movaps	%xmm7, %xmm13
	mulss	%xmm4, %xmm13
	mulss	4(%rsp), %xmm7
	mulss	%xmm12, %xmm13
	movss	36(%rsp), %xmm12
	mulss	%xmm5, %xmm7
	subss	%xmm13, %xmm0
	movss	8(%rsp), %xmm13
	mulss	%xmm13, %xmm3
	subss	%xmm3, %xmm7
	movaps	%xmm13, %xmm3
	addss	%xmm7, %xmm0
	movaps	%xmm13, %xmm7
	movss	16(%rsp), %xmm13
	mulss	%xmm4, %xmm7
	mulss	%xmm9, %xmm7
	mulss	%xmm9, %xmm9
	addss	%xmm7, %xmm0
	movd	%ecx, %xmm7
	unpcklps	%xmm7, %xmm13
	movaps	%xmm4, %xmm7
	mulss	%xmm11, %xmm7
	unpcklps	%xmm0, %xmm14
	movlhps	%xmm14, %xmm13
	movaps	%xmm5, %xmm14
	mulss	%xmm1, %xmm14
	movaps	%xmm7, %xmm0
	movss	20(%rsp), %xmm7
	mulss	%xmm3, %xmm7
	movss	28(%rsp), %xmm3
	mulss	%xmm12, %xmm3
	addss	%xmm7, %xmm0
	movaps	%xmm4, %xmm7
	mulss	%xmm8, %xmm7
	subss	%xmm11, %xmm8
	movaps	%xmm2, %xmm11
	subss	%xmm6, %xmm11
	mulss	%xmm5, %xmm8
	mulss	%xmm5, %xmm5
	subss	%xmm7, %xmm3
	movd	%eax, %xmm7
	mulss	%xmm12, %xmm7
	addss	%xmm3, %xmm0
	movaps	%xmm7, %xmm3
	movss	4(%rsp), %xmm7
	mulss	%xmm15, %xmm7
	addss	%xmm7, %xmm3
	movaps	%xmm10, %xmm7
	subss	%xmm14, %xmm7
	movaps	%xmm6, %xmm14
	subss	%xmm2, %xmm14
	mulss	%xmm4, %xmm6
	subss	%xmm3, %xmm0
	mulss	%xmm2, %xmm4
	unpcklps	%xmm14, %xmm7
	movss	32(%rsp), %xmm14
	unpcklps	%xmm14, %xmm0
	movlhps	%xmm7, %xmm0
	movss	12(%rsp), %xmm7
	movups	%xmm0, 76(%rsp)
	movss	8(%rsp), %xmm0
	mulss	%xmm7, %xmm15
	mulss	%xmm10, %xmm0
	mulss	20(%rsp), %xmm7
	subss	%xmm0, %xmm15
	movaps	%xmm11, %xmm0
	mulss	%xmm12, %xmm0
	addss	%xmm7, %xmm4
	addss	%xmm15, %xmm8
	addss	%xmm0, %xmm8
	movss	4(%rsp), %xmm0
	mulss	%xmm10, %xmm0
	movss	%xmm8, 92(%rsp)
	addss	%xmm0, %xmm6
	movss	16(%rsp), %xmm0
	mulss	%xmm1, %xmm0
	addss	%xmm5, %xmm6
	subss	%xmm4, %xmm6
	addss	%xmm0, %xmm9
	movss	40(%rsp), %xmm0
	mulss	%xmm14, %xmm0
	movss	%xmm6, 108(%rsp)
	addss	%xmm0, %xmm9
	comiss	.LC5(%rip), %xmm9
	je	.L311
	movss	.LC11(%rip), %xmm0
	movaps	64(%rsp), %xmm2
	movaps	80(%rsp), %xmm1
	divss	%xmm9, %xmm0
	shufps	$0, %xmm0, %xmm0
	mulps	%xmm0, %xmm13
	mulps	%xmm0, %xmm2
	mulps	%xmm0, %xmm1
	mulps	96(%rsp), %xmm0
.L309:
	movups	%xmm13, (%r8)
	movups	%xmm2, 16(%r8)
	movups	%xmm1, 32(%r8)
	movups	%xmm0, 48(%r8)
	movq	120(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L313
	movq	%r8, %rax
	addq	$136, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L311:
	.cfi_restore_state
	movaps	.LC3(%rip), %xmm0
	movaps	.LC2(%rip), %xmm1
	movss	.LC0(%rip), %xmm13
	movaps	.LC1(%rip), %xmm2
	jmp	.L309
.L313:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3979:
	.size	_Z7look_atRK6Point3IfES2_RK7Vector3IfE, .-_Z7look_atRK6Point3IfES2_RK7Vector3IfE
	.section	.text._Z7inverseIfE9Matrix4x4IT_ERKS2_,"axG",@progbits,_Z7inverseIfE9Matrix4x4IT_ERKS2_,comdat
	.p2align 4
	.weak	_Z7inverseIfE9Matrix4x4IT_ERKS2_
	.type	_Z7inverseIfE9Matrix4x4IT_ERKS2_, @function
_Z7inverseIfE9Matrix4x4IT_ERKS2_:
.LFB4352:
	.cfi_startproc
	endbr64
	movss	36(%rsi), %xmm4
	movss	20(%rsi), %xmm10
	movq	%rdi, %rax
	movss	8(%rsi), %xmm5
	movss	28(%rsi), %xmm12
	movss	%xmm4, -116(%rsp)
	movss	40(%rsi), %xmm4
	movaps	%xmm10, %xmm9
	movss	56(%rsi), %xmm0
	movss	%xmm5, -72(%rsp)
	movss	60(%rsi), %xmm2
	movss	44(%rsi), %xmm1
	movaps	%xmm12, %xmm15
	mulss	%xmm4, %xmm9
	movss	24(%rsi), %xmm14
	movss	52(%rsi), %xmm3
	movss	%xmm10, -100(%rsp)
	mulss	%xmm1, %xmm10
	movss	16(%rsi), %xmm6
	movss	48(%rsi), %xmm7
	movss	%xmm3, -108(%rsp)
	movss	4(%rsi), %xmm8
	movss	12(%rsi), %xmm13
	movss	(%rsi), %xmm11
	movss	%xmm8, -104(%rsp)
	movss	32(%rsi), %xmm8
	movaps	%xmm9, %xmm5
	movss	-116(%rsp), %xmm9
	movss	%xmm13, -92(%rsp)
	mulss	%xmm2, %xmm5
	movss	%xmm11, -96(%rsp)
	mulss	%xmm12, %xmm9
	mulss	%xmm0, %xmm10
	mulss	%xmm0, %xmm9
	addss	%xmm9, %xmm5
	movss	-116(%rsp), %xmm9
	mulss	%xmm14, %xmm9
	mulss	%xmm2, %xmm9
	addss	%xmm10, %xmm9
	movaps	%xmm12, %xmm10
	mulss	%xmm4, %xmm10
	subss	%xmm9, %xmm5
	movaps	%xmm14, %xmm9
	mulss	%xmm1, %xmm9
	subss	%xmm10, %xmm9
	movaps	%xmm14, %xmm10
	movss	%xmm10, -112(%rsp)
	mulss	%xmm8, %xmm14
	mulss	%xmm3, %xmm9
	movaps	%xmm5, %xmm3
	movd	%xmm14, %edx
	movaps	%xmm12, %xmm14
	mulss	%xmm8, %xmm14
	addss	%xmm9, %xmm3
	movaps	%xmm6, %xmm9
	mulss	%xmm1, %xmm9
	movss	%xmm3, -68(%rsp)
	movaps	%xmm6, %xmm3
	mulss	%xmm4, %xmm3
	movaps	%xmm9, %xmm13
	movaps	%xmm10, %xmm9
	movaps	%xmm12, %xmm10
	mulss	%xmm7, %xmm10
	movaps	%xmm13, %xmm5
	mulss	%xmm7, %xmm9
	mulss	%xmm0, %xmm5
	movaps	%xmm10, %xmm12
	movaps	%xmm9, %xmm11
	movaps	%xmm10, %xmm9
	mulss	%xmm4, %xmm9
	movaps	%xmm11, %xmm10
	mulss	%xmm1, %xmm10
	addss	%xmm9, %xmm5
	movaps	%xmm14, %xmm9
	mulss	%xmm0, %xmm9
	mulss	-108(%rsp), %xmm14
	addss	%xmm9, %xmm10
	movd	%edx, %xmm9
	subss	%xmm3, %xmm9
	subss	%xmm10, %xmm5
	movaps	%xmm9, %xmm10
	movss	-116(%rsp), %xmm9
	mulss	%xmm2, %xmm10
	mulss	%xmm6, %xmm9
	addss	%xmm10, %xmm5
	movaps	%xmm9, %xmm10
	movss	-100(%rsp), %xmm9
	movss	%xmm10, -88(%rsp)
	mulss	%xmm2, %xmm10
	movss	%xmm5, -64(%rsp)
	movaps	%xmm9, %xmm5
	mulss	%xmm8, %xmm5
	mulss	-108(%rsp), %xmm13
	mulss	%xmm7, %xmm9
	addss	%xmm14, %xmm10
	mulss	-116(%rsp), %xmm12
	mulss	-116(%rsp), %xmm11
	movaps	%xmm5, %xmm14
	subss	-88(%rsp), %xmm5
	mulss	%xmm2, %xmm14
	mulss	%xmm0, %xmm5
	addss	%xmm14, %xmm13
	movaps	%xmm9, %xmm14
	mulss	%xmm1, %xmm14
	mulss	%xmm4, %xmm9
	subss	%xmm13, %xmm10
	movaps	%xmm14, %xmm13
	movaps	%xmm10, %xmm14
	subss	%xmm12, %xmm13
	addss	%xmm13, %xmm14
	movss	-108(%rsp), %xmm13
	mulss	%xmm13, %xmm3
	movss	%xmm14, -60(%rsp)
	movd	%edx, %xmm14
	mulss	%xmm13, %xmm14
	addss	%xmm3, %xmm5
	movaps	%xmm13, %xmm3
	movss	-92(%rsp), %xmm13
	addss	%xmm14, %xmm9
	subss	%xmm9, %xmm5
	movaps	%xmm5, %xmm14
	movss	-72(%rsp), %xmm5
	addss	%xmm11, %xmm14
	movss	-116(%rsp), %xmm11
	movaps	%xmm5, %xmm10
	mulss	%xmm5, %xmm11
	mulss	%xmm3, %xmm10
	movss	%xmm14, -16(%rsp)
	movss	-116(%rsp), %xmm14
	mulss	%xmm13, %xmm14
	movd	%xmm11, %esi
	movaps	%xmm13, %xmm11
	mulss	%xmm3, %xmm11
	movss	-96(%rsp), %xmm3
	movaps	%xmm3, %xmm9
	movaps	%xmm3, %xmm12
	mulss	%xmm4, %xmm9
	mulss	%xmm1, %xmm12
	movss	%xmm11, -88(%rsp)
	movaps	%xmm5, %xmm11
	mulss	%xmm8, %xmm5
	movss	%xmm9, -56(%rsp)
	movaps	%xmm11, %xmm9
	mulss	%xmm7, %xmm9
	movss	%xmm12, -52(%rsp)
	movss	.LC23(%rip), %xmm12
	movss	%xmm5, -84(%rsp)
	movaps	%xmm13, %xmm5
	mulss	%xmm8, %xmm5
	movss	%xmm9, -80(%rsp)
	movaps	%xmm13, %xmm9
	mulss	%xmm7, %xmm9
	movss	%xmm5, -28(%rsp)
	movaps	%xmm3, %xmm5
	movss	-116(%rsp), %xmm3
	xorps	%xmm12, %xmm5
	mulss	%xmm5, %xmm3
	movss	%xmm9, -76(%rsp)
	movaps	%xmm5, %xmm9
	movaps	%xmm8, %xmm5
	movss	-104(%rsp), %xmm8
	mulss	-112(%rsp), %xmm9
	mulss	%xmm8, %xmm5
	mulss	%xmm8, %xmm7
	movss	%xmm3, -48(%rsp)
	movss	-100(%rsp), %xmm3
	movd	%xmm9, %edx
	movss	%xmm5, -44(%rsp)
	movss	-112(%rsp), %xmm5
	movss	%xmm7, -24(%rsp)
	movaps	%xmm11, %xmm7
	mulss	%xmm8, %xmm5
	mulss	%xmm15, %xmm8
	mulss	%xmm3, %xmm7
	movss	%xmm5, -40(%rsp)
	movaps	%xmm8, %xmm5
	movaps	%xmm13, %xmm8
	movaps	%xmm11, %xmm13
	movss	-92(%rsp), %xmm11
	mulss	%xmm3, %xmm8
	movss	-96(%rsp), %xmm3
	mulss	%xmm6, %xmm11
	mulss	%xmm6, %xmm13
	movaps	%xmm3, %xmm9
	mulss	%xmm15, %xmm9
	movss	%xmm11, -20(%rsp)
	movss	-100(%rsp), %xmm11
	mulss	%xmm3, %xmm11
	movss	-104(%rsp), %xmm3
	mulss	%xmm6, %xmm3
	movaps	%xmm12, %xmm6
	movd	%edx, %xmm12
	xorps	%xmm12, %xmm6
	movss	-88(%rsp), %xmm12
	movss	%xmm11, -36(%rsp)
	mulss	%xmm4, %xmm12
	movss	%xmm3, -32(%rsp)
	subss	%xmm11, %xmm3
	movss	-104(%rsp), %xmm11
	movss	%xmm3, -12(%rsp)
	movaps	%xmm6, %xmm3
	movaps	%xmm11, %xmm6
	mulss	%xmm1, %xmm6
	mulss	%xmm0, %xmm6
	addss	%xmm12, %xmm6
	movaps	%xmm14, %xmm12
	mulss	%xmm0, %xmm12
	mulss	-112(%rsp), %xmm14
	movss	%xmm12, -104(%rsp)
	movaps	%xmm10, %xmm12
	mulss	%xmm1, %xmm12
	addss	-104(%rsp), %xmm12
	movss	%xmm11, -104(%rsp)
	mulss	%xmm15, %xmm10
	subss	%xmm12, %xmm6
	movaps	%xmm11, %xmm12
	movd	%esi, %xmm11
	mulss	%xmm4, %xmm12
	subss	%xmm12, %xmm11
	movaps	%xmm11, %xmm12
	mulss	%xmm2, %xmm12
	addss	%xmm12, %xmm6
	movaps	%xmm8, %xmm12
	mulss	%xmm0, %xmm12
	mulss	%xmm4, %xmm8
	movd	%xmm6, %ecx
	movss	-40(%rsp), %xmm6
	mulss	%xmm2, %xmm6
	addss	%xmm12, %xmm6
	movaps	%xmm5, %xmm12
	mulss	%xmm0, %xmm12
	mulss	%xmm4, %xmm5
	movaps	%xmm12, %xmm11
	movaps	%xmm7, %xmm12
	subss	-40(%rsp), %xmm7
	movss	%xmm3, -40(%rsp)
	mulss	%xmm2, %xmm12
	addss	%xmm14, %xmm5
	movss	-28(%rsp), %xmm14
	addss	%xmm11, %xmm12
	subss	%xmm12, %xmm6
	movaps	%xmm15, %xmm12
	movss	-88(%rsp), %xmm15
	mulss	-112(%rsp), %xmm15
	movss	%xmm12, -88(%rsp)
	subss	%xmm15, %xmm10
	movss	-84(%rsp), %xmm15
	addss	%xmm10, %xmm6
	movaps	%xmm8, %xmm10
	movd	%esi, %xmm8
	mulss	%xmm12, %xmm8
	movss	-20(%rsp), %xmm12
	addss	%xmm10, %xmm8
	movss	-76(%rsp), %xmm10
	subss	%xmm8, %xmm5
	movaps	%xmm7, %xmm8
	movd	%ecx, %xmm7
	mulss	%xmm1, %xmm8
	addss	%xmm8, %xmm5
	movss	-68(%rsp), %xmm8
	unpcklps	%xmm7, %xmm8
	movss	-56(%rsp), %xmm7
	unpcklps	%xmm5, %xmm6
	movaps	%xmm8, %xmm11
	movss	-52(%rsp), %xmm8
	mulss	%xmm2, %xmm7
	movlhps	%xmm6, %xmm11
	movaps	%xmm14, %xmm6
	mulss	%xmm0, %xmm6
	mulss	%xmm0, %xmm8
	movaps	%xmm7, %xmm5
	movss	-80(%rsp), %xmm7
	addss	%xmm6, %xmm5
	movaps	%xmm15, %xmm6
	mulss	%xmm2, %xmm6
	mulss	%xmm1, %xmm7
	addss	%xmm8, %xmm6
	movaps	%xmm9, %xmm8
	mulss	%xmm0, %xmm8
	subss	%xmm6, %xmm5
	movaps	%xmm7, %xmm6
	movaps	%xmm10, %xmm7
	mulss	%xmm4, %xmm7
	subss	%xmm7, %xmm6
	movaps	%xmm12, %xmm7
	mulss	%xmm0, %xmm7
	addss	%xmm6, %xmm5
	movaps	%xmm8, %xmm6
	movss	-112(%rsp), %xmm8
	mulss	%xmm10, %xmm8
	movaps	%xmm7, %xmm10
	movss	-80(%rsp), %xmm7
	mulss	-88(%rsp), %xmm7
	addss	%xmm8, %xmm6
	movaps	%xmm7, %xmm8
	movd	%edx, %xmm7
	addss	%xmm13, %xmm7
	addss	%xmm10, %xmm8
	mulss	%xmm2, %xmm7
	subss	%xmm8, %xmm6
	movss	-88(%rsp), %xmm8
	mulss	%xmm15, %xmm8
	addss	%xmm7, %xmm6
	movaps	%xmm12, %xmm7
	mulss	%xmm4, %xmm7
	movaps	%xmm6, %xmm10
	addss	%xmm8, %xmm7
	movaps	%xmm9, %xmm8
	mulss	%xmm4, %xmm8
	movaps	%xmm7, %xmm6
	movaps	%xmm13, %xmm7
	mulss	%xmm1, %xmm7
	addss	%xmm8, %xmm7
	movss	-112(%rsp), %xmm8
	mulss	%xmm14, %xmm8
	subss	%xmm7, %xmm6
	movaps	%xmm3, %xmm7
	mulss	%xmm1, %xmm7
	subss	%xmm8, %xmm7
	movss	-64(%rsp), %xmm8
	unpcklps	%xmm5, %xmm8
	movss	-52(%rsp), %xmm5
	movss	-108(%rsp), %xmm3
	addss	%xmm7, %xmm6
	movss	-24(%rsp), %xmm15
	movaps	%xmm14, %xmm7
	mulss	%xmm3, %xmm5
	mulss	%xmm3, %xmm7
	unpcklps	%xmm6, %xmm10
	movss	-116(%rsp), %xmm6
	movlhps	%xmm10, %xmm8
	movss	-76(%rsp), %xmm10
	mulss	%xmm10, %xmm6
	addss	%xmm6, %xmm5
	movaps	%xmm15, %xmm6
	mulss	%xmm1, %xmm6
	addss	%xmm7, %xmm6
	movaps	%xmm12, %xmm7
	mulss	%xmm3, %xmm7
	mulss	-116(%rsp), %xmm12
	subss	%xmm6, %xmm5
	movss	-48(%rsp), %xmm6
	addss	-44(%rsp), %xmm6
	mulss	%xmm2, %xmm6
	addss	%xmm6, %xmm5
	movss	-36(%rsp), %xmm6
	mulss	%xmm2, %xmm6
	mulss	-32(%rsp), %xmm2
	addss	%xmm7, %xmm6
	movaps	%xmm9, %xmm7
	mulss	%xmm3, %xmm7
	movss	-12(%rsp), %xmm3
	mulss	-116(%rsp), %xmm9
	mulss	%xmm3, %xmm1
	addss	%xmm7, %xmm2
	movss	-88(%rsp), %xmm7
	mulss	%xmm15, %xmm7
	subss	%xmm12, %xmm1
	movss	-44(%rsp), %xmm12
	subss	%xmm2, %xmm6
	movaps	%xmm10, %xmm2
	movss	-100(%rsp), %xmm10
	mulss	%xmm10, %xmm2
	mulss	%xmm10, %xmm14
	subss	%xmm2, %xmm7
	movss	-56(%rsp), %xmm2
	addss	%xmm7, %xmm6
	movaps	%xmm14, %xmm7
	movss	-108(%rsp), %xmm14
	addss	%xmm9, %xmm7
	mulss	%xmm14, %xmm2
	movaps	%xmm14, %xmm9
	addss	%xmm1, %xmm7
	movss	-88(%rsp), %xmm1
	mulss	%xmm12, %xmm1
	subss	%xmm1, %xmm7
	movss	-60(%rsp), %xmm1
	unpcklps	%xmm5, %xmm1
	movaps	%xmm15, %xmm5
	mulss	%xmm4, %xmm5
	unpcklps	%xmm7, %xmm6
	movaps	%xmm1, %xmm7
	movlhps	%xmm6, %xmm7
	movss	-84(%rsp), %xmm6
	movaps	%xmm6, %xmm1
	mulss	%xmm14, %xmm1
	movss	-80(%rsp), %xmm14
	addss	%xmm5, %xmm1
	movaps	%xmm12, %xmm5
	mulss	%xmm0, %xmm5
	addss	%xmm5, %xmm2
	movss	-116(%rsp), %xmm5
	mulss	%xmm14, %xmm5
	subss	%xmm2, %xmm1
	movss	-48(%rsp), %xmm2
	mulss	%xmm0, %xmm2
	mulss	%xmm3, %xmm0
	movaps	%xmm9, %xmm3
	addss	%xmm2, %xmm5
	movaps	%xmm14, %xmm2
	movss	-112(%rsp), %xmm14
	mulss	%xmm10, %xmm2
	subss	%xmm5, %xmm1
	movaps	%xmm15, %xmm5
	mulss	%xmm14, %xmm5
	subss	%xmm5, %xmm2
	movaps	%xmm13, %xmm5
	mulss	%xmm9, %xmm5
	movss	-116(%rsp), %xmm9
	mulss	%xmm13, %xmm9
	subss	%xmm5, %xmm0
	movss	-40(%rsp), %xmm5
	mulss	%xmm5, %xmm3
	addss	%xmm2, %xmm0
	movss	-36(%rsp), %xmm2
	mulss	%xmm4, %xmm2
	addss	%xmm3, %xmm0
	movss	-32(%rsp), %xmm3
	mulss	%xmm4, %xmm3
	movaps	%xmm6, %xmm4
	mulss	%xmm10, %xmm4
	addss	%xmm9, %xmm2
	addss	%xmm4, %xmm3
	movss	-116(%rsp), %xmm4
	mulss	%xmm5, %xmm4
	subss	%xmm3, %xmm2
	movaps	%xmm12, %xmm3
	mulss	%xmm14, %xmm3
	subss	%xmm4, %xmm3
	movss	-16(%rsp), %xmm4
	addss	%xmm3, %xmm2
	unpcklps	%xmm2, %xmm0
	movaps	%xmm4, %xmm2
	mulss	-92(%rsp), %xmm4
	unpcklps	%xmm1, %xmm2
	movlhps	%xmm0, %xmm2
	movss	-64(%rsp), %xmm0
	mulss	-104(%rsp), %xmm0
	movss	-68(%rsp), %xmm1
	movss	-60(%rsp), %xmm3
	mulss	-96(%rsp), %xmm1
	mulss	-72(%rsp), %xmm3
	addss	%xmm4, %xmm0
	addss	%xmm3, %xmm1
	addss	%xmm1, %xmm0
	comiss	.LC5(%rip), %xmm0
	jne	.L319
	movss	.LC0(%rip), %xmm0
	movups	%xmm0, (%rdi)
	movaps	.LC1(%rip), %xmm0
	movups	%xmm0, 16(%rdi)
	movaps	.LC2(%rip), %xmm0
	movups	%xmm0, 32(%rdi)
	movaps	.LC3(%rip), %xmm0
	movups	%xmm0, 48(%rdi)
	ret
	.p2align 4,,10
	.p2align 3
.L319:
	movss	.LC11(%rip), %xmm1
	divss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	shufps	$0, %xmm0, %xmm0
	mulps	%xmm0, %xmm11
	mulps	%xmm0, %xmm8
	mulps	%xmm0, %xmm7
	mulps	%xmm0, %xmm2
	movups	%xmm11, (%rdi)
	movups	%xmm8, 16(%rdi)
	movups	%xmm7, 32(%rdi)
	movups	%xmm2, 48(%rdi)
	ret
	.cfi_endproc
.LFE4352:
	.size	_Z7inverseIfE9Matrix4x4IT_ERKS2_, .-_Z7inverseIfE9Matrix4x4IT_ERKS2_
	.text
	.p2align 4
	.globl	_Z7inverseRK9Transform
	.type	_Z7inverseRK9Transform, @function
_Z7inverseRK9Transform:
.LFB3959:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	subq	$80, %rsp
	.cfi_def_cfa_offset 96
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	_Z7inverseIfE9Matrix4x4IT_ERKS2_
	movaps	(%rsp), %xmm0
	movaps	16(%rsp), %xmm1
	movaps	32(%rsp), %xmm2
	movaps	48(%rsp), %xmm3
	movups	%xmm0, (%r12)
	movups	%xmm1, 16(%r12)
	movups	%xmm2, 32(%r12)
	movups	%xmm3, 48(%r12)
	movq	72(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L323
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	movq	%r12, %rax
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L323:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3959:
	.size	_Z7inverseRK9Transform, .-_Z7inverseRK9Transform
	.p2align 4
	.globl	_Z7inversePK9Transform
	.type	_Z7inversePK9Transform, @function
_Z7inversePK9Transform:
.LFB3960:
	.cfi_startproc
	endbr64
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movq	%rdi, %rsi
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rdi
	call	_Z7inverseIfE9Matrix4x4IT_ERKS2_
	movl	$64, %edi
	call	_Znwm@PLT
	movaps	(%rsp), %xmm0
	movaps	16(%rsp), %xmm1
	movaps	32(%rsp), %xmm2
	movaps	48(%rsp), %xmm3
	movups	%xmm0, (%rax)
	movups	%xmm1, 16(%rax)
	movups	%xmm2, 32(%rax)
	movups	%xmm3, 48(%rax)
	movq	72(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L327
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L327:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3960:
	.size	_Z7inversePK9Transform, .-_Z7inversePK9Transform
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZN9TransformC2Ev, @function
_GLOBAL__sub_I__ZN9TransformC2Ev:
.LFB4740:
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
.LFE4740:
	.size	_GLOBAL__sub_I__ZN9TransformC2Ev, .-_GLOBAL__sub_I__ZN9TransformC2Ev
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN9TransformC2Ev
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1065353216
	.long	0
	.long	0
	.long	0
	.align 16
.LC1:
	.long	0
	.long	1065353216
	.long	0
	.long	0
	.align 16
.LC2:
	.long	0
	.long	0
	.long	1065353216
	.long	0
	.align 16
.LC3:
	.long	0
	.long	0
	.long	0
	.long	1065353216
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC4:
	.long	869711765
	.set	.LC5,.LC0+4
	.set	.LC11,.LC0
	.section	.rodata.cst16
	.align 16
.LC12:
	.long	2147483647
	.long	0
	.long	0
	.long	0
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC13:
	.long	2147483647
	.long	2147483647
	.align 8
.LC14:
	.long	889192452
	.long	889192452
	.set	.LC15,.LC14
	.set	.LC16,.LC17
	.align 8
.LC17:
	.long	884998149
	.long	884998149
	.set	.LC20,.LC0
	.section	.rodata.cst4
	.align 4
.LC21:
	.long	1078530011
	.section	.rodata.cst8
	.align 8
.LC22:
	.long	381774871
	.long	1064747372
	.section	.rodata.cst16
	.align 16
.LC23:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.set	.LC24,.LC1
	.section	.rodata.cst4
	.align 4
.LC25:
	.long	-1069547520
	.align 4
.LC26:
	.long	-1090519040
	.section	.rodata.cst8
	.align 8
.LC27:
	.long	1065353216
	.long	1065353216
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

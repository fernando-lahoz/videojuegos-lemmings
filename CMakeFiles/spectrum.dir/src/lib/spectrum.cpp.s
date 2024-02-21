	.file	"spectrum.cpp"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"("
.LC1:
	.string	", "
.LC2:
	.string	")"
	.text
	.p2align 4
	.globl	_ZlsRSoRK11SpectrumHDR
	.type	_ZlsRSoRK11SpectrumHDR, @function
_ZlsRSoRK11SpectrumHDR:
.LFB3767:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %edx
	leaq	.LC1(%rip), %r13
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
	leaq	.LC0(%rip), %rsi
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r12, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	(%rbx), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movq	%r13, %rsi
	movl	$2, %edx
	movq	%rax, %rbp
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbp, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	4(%rbx), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movq	%r13, %rsi
	movl	$2, %edx
	movq	%rax, %rbp
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbp, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	8(%rbx), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movq	%r13, %rsi
	movl	$2, %edx
	movq	%rax, %rbp
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rbp, %rdi
	pxor	%xmm0, %xmm0
	cvtss2sd	12(%rbx), %xmm0
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	movl	$1, %edx
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	addq	$8, %rsp
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
.LFE3767:
	.size	_ZlsRSoRK11SpectrumHDR, .-_ZlsRSoRK11SpectrumHDR
	.align 2
	.p2align 4
	.globl	_ZNK11SpectrumHDR7to_rgbaEv
	.type	_ZNK11SpectrumHDR7to_rgbaEv, @function
_ZNK11SpectrumHDR7to_rgbaEv:
.LFB3768:
	.cfi_startproc
	endbr64
	movss	.LC3(%rip), %xmm0
	movss	(%rdi), %xmm1
	pxor	%xmm2, %xmm2
	xorl	%edx, %edx
	mulss	%xmm0, %xmm1
	minss	%xmm0, %xmm1
	maxss	%xmm2, %xmm1
	cvttss2sil	%xmm1, %eax
	movss	4(%rdi), %xmm1
	mulss	%xmm0, %xmm1
	movb	%al, %dl
	minss	%xmm0, %xmm1
	maxss	%xmm2, %xmm1
	cvttss2sil	%xmm1, %eax
	movss	8(%rdi), %xmm1
	mulss	%xmm0, %xmm1
	movb	%al, %dh
	movzwl	%dx, %eax
	minss	%xmm0, %xmm1
	maxss	%xmm2, %xmm1
	cvttss2sil	%xmm1, %ecx
	movss	12(%rdi), %xmm1
	mulss	%xmm0, %xmm1
	movzbl	%cl, %ecx
	sall	$16, %ecx
	orl	%ecx, %eax
	minss	%xmm0, %xmm1
	maxss	%xmm2, %xmm1
	cvttss2sil	%xmm1, %edx
	sall	$24, %edx
	orl	%edx, %eax
	ret
	.cfi_endproc
.LFE3768:
	.size	_ZNK11SpectrumHDR7to_rgbaEv, .-_ZNK11SpectrumHDR7to_rgbaEv
	.align 2
	.p2align 4
	.globl	_ZNK11SpectrumHDR12squared_normEv
	.type	_ZNK11SpectrumHDR12squared_normEv, @function
_ZNK11SpectrumHDR12squared_normEv:
.LFB3769:
	.cfi_startproc
	endbr64
	movss	(%rdi), %xmm0
	movss	4(%rdi), %xmm2
	movss	8(%rdi), %xmm1
	mulss	%xmm2, %xmm2
	mulss	%xmm0, %xmm0
	mulss	%xmm1, %xmm1
	addss	%xmm2, %xmm0
	addss	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE3769:
	.size	_ZNK11SpectrumHDR12squared_normEv, .-_ZNK11SpectrumHDR12squared_normEv
	.align 2
	.p2align 4
	.globl	_ZNK11SpectrumHDR4normEv
	.type	_ZNK11SpectrumHDR4normEv, @function
_ZNK11SpectrumHDR4normEv:
.LFB3770:
	.cfi_startproc
	endbr64
	movss	(%rdi), %xmm1
	movss	4(%rdi), %xmm2
	movss	8(%rdi), %xmm0
	mulss	%xmm2, %xmm2
	mulss	%xmm1, %xmm1
	mulss	%xmm0, %xmm0
	addss	%xmm2, %xmm1
	addss	%xmm1, %xmm0
	sqrtss	%xmm0, %xmm0
	ret
	.cfi_endproc
.LFE3770:
	.size	_ZNK11SpectrumHDR4normEv, .-_ZNK11SpectrumHDR4normEv
	.p2align 4
	.globl	_ZlsRSoRK11SpectrumRGB
	.type	_ZlsRSoRK11SpectrumRGB, @function
_ZlsRSoRK11SpectrumRGB:
.LFB3771:
	.cfi_startproc
	endbr64
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$1, %edx
	leaq	.LC1(%rip), %r13
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
	leaq	.LC0(%rip), %rsi
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movzbl	(%rbx), %esi
	movq	%r12, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$2, %edx
	movq	%r13, %rsi
	movq	%rax, %rdi
	movq	%rax, %rbp
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movzbl	1(%rbx), %esi
	movq	%rbp, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$2, %edx
	movq	%r13, %rsi
	movq	%rax, %rdi
	movq	%rax, %rbp
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movzbl	2(%rbx), %esi
	movq	%rbp, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$2, %edx
	movq	%r13, %rsi
	movq	%rax, %rdi
	movq	%rax, %rbp
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movzbl	3(%rbx), %esi
	movq	%rbp, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$1, %edx
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	addq	$8, %rsp
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
.LFE3771:
	.size	_ZlsRSoRK11SpectrumRGB, .-_ZlsRSoRK11SpectrumRGB
	.align 2
	.p2align 4
	.globl	_ZNK11SpectrumRGB12squared_normEv
	.type	_ZNK11SpectrumRGB12squared_normEv, @function
_ZNK11SpectrumRGB12squared_normEv:
.LFB3772:
	.cfi_startproc
	endbr64
	movzbl	(%rdi), %eax
	movzbl	1(%rdi), %ecx
	pxor	%xmm0, %xmm0
	movzbl	2(%rdi), %edx
	imull	%eax, %eax
	imull	%ecx, %ecx
	imull	%edx, %edx
	addl	%ecx, %eax
	addl	%edx, %eax
	cvtsi2ssl	%eax, %xmm0
	ret
	.cfi_endproc
.LFE3772:
	.size	_ZNK11SpectrumRGB12squared_normEv, .-_ZNK11SpectrumRGB12squared_normEv
	.align 2
	.p2align 4
	.globl	_ZNK11SpectrumRGB4normEv
	.type	_ZNK11SpectrumRGB4normEv, @function
_ZNK11SpectrumRGB4normEv:
.LFB3773:
	.cfi_startproc
	endbr64
	movzbl	(%rdi), %eax
	movzbl	1(%rdi), %ecx
	pxor	%xmm0, %xmm0
	movzbl	2(%rdi), %edx
	imull	%eax, %eax
	imull	%ecx, %ecx
	imull	%edx, %edx
	addl	%ecx, %eax
	addl	%edx, %eax
	cvtsi2ssl	%eax, %xmm0
	sqrtss	%xmm0, %xmm0
	ret
	.cfi_endproc
.LFE3773:
	.size	_ZNK11SpectrumRGB4normEv, .-_ZNK11SpectrumRGB4normEv
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZlsRSoRK11SpectrumHDR, @function
_GLOBAL__sub_I__ZlsRSoRK11SpectrumHDR:
.LFB4518:
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
.LFE4518:
	.size	_GLOBAL__sub_I__ZlsRSoRK11SpectrumHDR, .-_GLOBAL__sub_I__ZlsRSoRK11SpectrumHDR
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZlsRSoRK11SpectrumHDR
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC3:
	.long	1132396544
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

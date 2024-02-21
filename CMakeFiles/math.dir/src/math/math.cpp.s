	.file	"math.cpp"
	.text
	.p2align 4
	.globl	_ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_
	.type	_ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_, @function
_ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_:
.LFB3667:
	.cfi_startproc
	endbr64
	movdqa	%xmm0, %xmm4
	movq	%xmm0, %rax
	movaps	%xmm1, %xmm11
	xorl	%r8d, %r8d
	movq	%xmm2, %rdx
	movss	.LC0(%rip), %xmm0
	pxor	%xmm7, %xmm7
	movdqa	%xmm1, %xmm2
	mulss	%xmm1, %xmm11
	movd	%edx, %xmm10
	movq	%xmm1, %rcx
	mulss	%xmm4, %xmm0
	movd	%edx, %xmm9
	movaps	%xmm11, %xmm6
	mulss	%xmm0, %xmm10
	subss	%xmm10, %xmm6
	comiss	%xmm6, %xmm7
	ja	.L1
	shrq	$32, %rdx
	shrq	$32, %rax
	sqrtss	%xmm6, %xmm6
	pxor	%xmm1, %xmm1
	movd	%edx, %xmm3
	cvttss2sil	%xmm9, %edx
	movd	%eax, %xmm5
	shrq	$32, %rcx
	movd	%ecx, %xmm8
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvttss2sil	%xmm0, %edx
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm1
	movl	%edx, %eax
	negl	%eax
	mulss	%xmm5, %xmm1
	cmovs	%edx, %eax
	cvttss2sil	%xmm2, %edx
	cvtsi2ssl	%eax, %xmm0
	movl	%edx, %eax
	mulss	%xmm0, %xmm1
	negl	%eax
	pxor	%xmm0, %xmm0
	cmovs	%edx, %eax
	cvttss2sil	%xmm10, %edx
	pxor	%xmm10, %xmm10
	cvtss2sd	%xmm6, %xmm10
	cvtsi2ssl	%eax, %xmm0
	cvttss2sil	%xmm11, %eax
	pxor	%xmm11, %xmm11
	cvtsi2ssl	%eax, %xmm11
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	comiss	%xmm2, %xmm7
	addss	%xmm11, %xmm0
	mulss	%xmm8, %xmm0
	addss	%xmm0, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	mulss	%xmm3, %xmm0
	addss	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	mulsd	.LC2(%rip), %xmm0
	divsd	%xmm10, %xmm0
	cvtsd2ss	%xmm0, %xmm0
	addss	%xmm8, %xmm0
	ja	.L15
	addss	%xmm6, %xmm2
.L13:
	mulss	.LC3(%rip), %xmm2
	pxor	%xmm6, %xmm6
	pxor	%xmm1, %xmm1
	movl	$1, %r8d
	movaps	%xmm2, %xmm7
	cvttss2sil	%xmm2, %edx
	divss	%xmm4, %xmm7
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm6
	mulss	%xmm6, %xmm0
	mulss	%xmm6, %xmm3
	cvttss2sil	%xmm7, %edx
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvttss2sil	%xmm4, %edx
	cvtsi2ssl	%eax, %xmm1
	mulss	%xmm4, %xmm4
	movl	%edx, %eax
	negl	%eax
	mulss	%xmm5, %xmm1
	cmovs	%edx, %eax
	pxor	%xmm5, %xmm5
	cvtsi2ssl	%eax, %xmm5
	mulss	%xmm0, %xmm5
	addss	%xmm5, %xmm1
	divss	%xmm4, %xmm1
	pxor	%xmm4, %xmm4
	unpcklps	%xmm1, %xmm7
	movaps	%xmm9, %xmm1
	divss	%xmm2, %xmm1
	movlps	%xmm7, (%rdi)
	mulss	%xmm2, %xmm2
	cvttss2sil	%xmm1, %edx
	movl	%edx, %eax
	negl	%eax
	cmovs	%edx, %eax
	cvtsi2ssl	%eax, %xmm4
	mulss	%xmm4, %xmm0
	addss	%xmm3, %xmm0
	divss	%xmm2, %xmm0
	movaps	%xmm1, %xmm2
	unpcklps	%xmm0, %xmm2
	movlps	%xmm2, (%rsi)
	movss	(%rdi), %xmm0
	comiss	%xmm1, %xmm0
	jbe	.L1
	movss	4(%rdi), %xmm1
	movq	(%rsi), %rax
	movl	$1, %r8d
	unpcklps	%xmm1, %xmm0
	movq	%rax, (%rdi)
	movlps	%xmm0, (%rsi)
.L1:
	movl	%r8d, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L15:
	subss	%xmm6, %xmm2
	jmp	.L13
	.cfi_endproc
.LFE3667:
	.size	_ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_, .-_ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_, @function
_GLOBAL__sub_I__ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_:
.LFB4406:
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
.LFE4406:
	.size	_GLOBAL__sub_I__ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_, .-_GLOBAL__sub_I__ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN4math9quadraticE10ErrorFloatS0_S0_RS0_S1_
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1082130432
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC2:
	.long	0
	.long	1071644672
	.section	.rodata.cst4
	.align 4
.LC3:
	.long	-1090519040
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

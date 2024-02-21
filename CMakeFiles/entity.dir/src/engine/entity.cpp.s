	.file	"entity.cpp"
	.text
	.align 2
	.p2align 4
	.globl	_ZN6Entity13on_event_downER6EngineN8EngineIO10InputEventE
	.type	_ZN6Entity13on_event_downER6EngineN8EngineIO10InputEventE, @function
_ZN6Entity13on_event_downER6EngineN8EngineIO10InputEventE:
.LFB12028:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE12028:
	.size	_ZN6Entity13on_event_downER6EngineN8EngineIO10InputEventE, .-_ZN6Entity13on_event_downER6EngineN8EngineIO10InputEventE
	.globl	_ZN6Entity11on_event_upER6EngineN8EngineIO10InputEventE
	.set	_ZN6Entity11on_event_upER6EngineN8EngineIO10InputEventE,_ZN6Entity13on_event_downER6EngineN8EngineIO10InputEventE
	.align 2
	.p2align 4
	.globl	_ZN6Entity11pre_physicsER6Engine
	.type	_ZN6Entity11pre_physicsER6Engine, @function
_ZN6Entity11pre_physicsER6Engine:
.LFB12030:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE12030:
	.size	_ZN6Entity11pre_physicsER6Engine, .-_ZN6Entity11pre_physicsER6Engine
	.globl	_ZN6Entity12post_physicsER6Engine
	.set	_ZN6Entity12post_physicsER6Engine,_ZN6Entity11pre_physicsER6Engine
	.globl	_ZN6Entity15update_positionER6Engine
	.set	_ZN6Entity15update_positionER6Engine,_ZN6Entity11pre_physicsER6Engine
	.align 2
	.p2align 4
	.globl	_ZN6Entity12on_collisionER6EngineSt10shared_ptrIS_E
	.type	_ZN6Entity12on_collisionER6EngineSt10shared_ptrIS_E, @function
_ZN6Entity12on_collisionER6EngineSt10shared_ptrIS_E:
.LFB12032:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE12032:
	.size	_ZN6Entity12on_collisionER6EngineSt10shared_ptrIS_E, .-_ZN6Entity12on_collisionER6EngineSt10shared_ptrIS_E
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev:
.LFB13024:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE13024:
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED1Ev
	.set	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED1Ev,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv:
.LFB13027:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA13027
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	%rdi, %r8
	xorl	%edi, %edi
	call	*16(%r8)
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13027:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,"aG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,comdat
.LLSDA13027:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE13027-.LLSDACSB13027
.LLSDACSB13027:
.LLSDACSE13027:
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,comdat
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev:
.LFB13031:
	.cfi_startproc
	endbr64
	ret
	.cfi_endproc
.LFE13031:
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED1Ev
	.set	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED1Ev,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED2Ev
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv:
.LFB13034:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA13034
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	%rdi, %r8
	xorl	%edi, %edi
	call	*16(%r8)
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13034:
	.section	.gcc_except_table._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,"aG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,comdat
.LLSDA13034:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE13034-.LLSDACSB13034
.LLSDACSB13034:
.LLSDACSE13034:
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv,comdat
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info:
.LFB13036:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	8(%rsi), %rdi
	leaq	_ZTSPFvP11SDL_TextureE(%rip), %rsi
	cmpq	%rsi, %rdi
	je	.L12
	xorl	%r12d, %r12d
	cmpb	$42, (%rdi)
	je	.L11
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L11
.L12:
	leaq	16(%rbx), %r12
.L11:
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13036:
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev:
.LFB13033:
	.cfi_startproc
	endbr64
	movl	$32, %esi
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE13033:
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev:
.LFB13026:
	.cfi_startproc
	endbr64
	movl	$32, %esi
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE13026:
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv:
.LFB13028:
	.cfi_startproc
	endbr64
	movl	$32, %esi
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE13028:
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv:
.LFB13035:
	.cfi_startproc
	endbr64
	movl	$32, %esi
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE13035:
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.section	.text._ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info,"axG",@progbits,_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.type	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info, @function
_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info:
.LFB13029:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	8(%rsi), %rdi
	leaq	_ZTSPFvP11SDL_SurfaceE(%rip), %rsi
	cmpq	%rsi, %rdi
	je	.L22
	xorl	%r12d, %r12d
	cmpb	$42, (%rdi)
	je	.L21
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L21
.L22:
	leaq	16(%rbx), %r12
.L21:
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13029:
	.size	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info, .-_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.section	.text._ZN7TextureD2Ev,"axG",@progbits,_ZN7TextureD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN7TextureD2Ev
	.type	_ZN7TextureD2Ev, @function
_ZN7TextureD2Ev:
.LFB11962:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	24(%rdi), %rbp
	testq	%rbp, %rbp
	je	.L29
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L30
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L31:
	cmpl	$1, %eax
	je	.L43
.L29:
	movq	8(%rbx), %rbp
	testq	%rbp, %rbp
	je	.L27
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L37
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L38:
	cmpl	$1, %eax
	je	.L44
.L27:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L43:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L33
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L34:
	cmpl	$1, %eax
	jne	.L29
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L29
	.p2align 4,,10
	.p2align 3
.L44:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L40
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L41:
	cmpl	$1, %eax
	jne	.L27
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	movq	24(%rax), %rax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L37:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L38
	.p2align 4,,10
	.p2align 3
.L30:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L31
	.p2align 4,,10
	.p2align 3
.L33:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L40:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L41
	.cfi_endproc
.LFE11962:
	.size	_ZN7TextureD2Ev, .-_ZN7TextureD2Ev
	.weak	_ZN7TextureD1Ev
	.set	_ZN7TextureD1Ev,_ZN7TextureD2Ev
	.text
	.align 2
	.p2align 4
	.globl	_ZNK6Entity14world_to_localE6Point2IfE
	.type	_ZNK6Entity14world_to_localE6Point2IfE, @function
_ZNK6Entity14world_to_localE6Point2IfE:
.LFB11969:
	.cfi_startproc
	endbr64
	movss	(%rdx), %xmm0
	movss	4(%rdx), %xmm1
	movq	%rdi, %rax
	subss	60(%rsi), %xmm0
	subss	64(%rsi), %xmm1
	divss	72(%rsi), %xmm0
	divss	76(%rsi), %xmm1
	unpcklps	%xmm1, %xmm0
	movlps	%xmm0, (%rdx)
	movlps	%xmm0, (%rdi)
	ret
	.cfi_endproc
.LFE11969:
	.size	_ZNK6Entity14world_to_localE6Point2IfE, .-_ZNK6Entity14world_to_localE6Point2IfE
	.align 2
	.p2align 4
	.globl	_ZNK6Entity14world_to_localE7Vector2IfE
	.type	_ZNK6Entity14world_to_localE7Vector2IfE, @function
_ZNK6Entity14world_to_localE7Vector2IfE:
.LFB11971:
	.cfi_startproc
	endbr64
	movss	(%rdx), %xmm0
	movss	4(%rdx), %xmm1
	divss	72(%rsi), %xmm0
	divss	76(%rsi), %xmm1
	unpcklps	%xmm1, %xmm0
	movq	%rdi, %rax
	movlps	%xmm0, (%rdx)
	movlps	%xmm0, (%rdi)
	ret
	.cfi_endproc
.LFE11971:
	.size	_ZNK6Entity14world_to_localE7Vector2IfE, .-_ZNK6Entity14world_to_localE7Vector2IfE
	.align 2
	.p2align 4
	.globl	_ZNK6Entity14local_to_worldE6Point2IfE
	.type	_ZNK6Entity14local_to_worldE6Point2IfE, @function
_ZNK6Entity14local_to_worldE6Point2IfE:
.LFB11972:
	.cfi_startproc
	endbr64
	movq	72(%rsi), %xmm1
	movq	(%rdx), %xmm0
	movq	%rdi, %rax
	mulps	%xmm1, %xmm0
	movq	60(%rsi), %xmm1
	addps	%xmm1, %xmm0
	movlps	%xmm0, (%rdx)
	movlps	%xmm0, (%rdi)
	ret
	.cfi_endproc
.LFE11972:
	.size	_ZNK6Entity14local_to_worldE6Point2IfE, .-_ZNK6Entity14local_to_worldE6Point2IfE
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"basic_string::_M_construct null not valid"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"basic_string::_M_create"
	.text
	.align 2
	.p2align 4
	.globl	_ZNK6Entity15get_entity_nameB5cxx11Ev
	.type	_ZNK6Entity15get_entity_nameB5cxx11Ev, @function
_ZNK6Entity15get_entity_nameB5cxx11Ev:
.LFB11974:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	addq	$16, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, (%r12)
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	112(%rsi), %rbp
	movq	120(%rsi), %rbx
	movq	%rbp, %rax
	addq	%rbx, %rax
	je	.L49
	testq	%rbp, %rbp
	je	.L66
.L49:
	cmpq	$15, %rbx
	ja	.L67
	cmpq	$1, %rbx
	je	.L68
	testq	%rbx, %rbx
	jne	.L53
.L55:
	movq	%rbx, 8(%r12)
	movq	%r12, %rax
	movb	$0, (%rdi,%rbx)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L68:
	.cfi_restore_state
	movzbl	0(%rbp), %eax
	movb	%al, 16(%r12)
	jmp	.L55
	.p2align 4,,10
	.p2align 3
.L67:
	testq	%rbx, %rbx
	js	.L69
	movq	%rbx, %rdi
	addq	$1, %rdi
	js	.L70
	call	_Znwm@PLT
	movq	%rbx, 16(%r12)
	movq	%rax, (%r12)
	movq	%rax, %rdi
.L53:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	memcpy@PLT
	movq	(%r12), %rdi
	jmp	.L55
.L66:
	leaq	.LC0(%rip), %rdi
	call	_ZSt19__throw_logic_errorPKc@PLT
	.p2align 4,,10
	.p2align 3
.L70:
	call	_ZSt17__throw_bad_allocv@PLT
.L69:
	leaq	.LC1(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE11974:
	.size	_ZNK6Entity15get_entity_nameB5cxx11Ev, .-_ZNK6Entity15get_entity_nameB5cxx11Ev
	.align 2
	.p2align 4
	.globl	_ZNK6Entity9get_classB5cxx11Ev
	.type	_ZNK6Entity9get_classB5cxx11Ev, @function
_ZNK6Entity9get_classB5cxx11Ev:
.LFB11975:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdi, %r12
	addq	$16, %rdi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rdi, (%r12)
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	80(%rsi), %rbp
	movq	88(%rsi), %rbx
	movq	%rbp, %rax
	addq	%rbx, %rax
	je	.L72
	testq	%rbp, %rbp
	je	.L89
.L72:
	cmpq	$15, %rbx
	ja	.L90
	cmpq	$1, %rbx
	je	.L91
	testq	%rbx, %rbx
	jne	.L76
.L78:
	movq	%rbx, 8(%r12)
	movq	%r12, %rax
	movb	$0, (%rdi,%rbx)
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L91:
	.cfi_restore_state
	movzbl	0(%rbp), %eax
	movb	%al, 16(%r12)
	jmp	.L78
	.p2align 4,,10
	.p2align 3
.L90:
	testq	%rbx, %rbx
	js	.L92
	movq	%rbx, %rdi
	addq	$1, %rdi
	js	.L93
	call	_Znwm@PLT
	movq	%rbx, 16(%r12)
	movq	%rax, (%r12)
	movq	%rax, %rdi
.L76:
	movq	%rbx, %rdx
	movq	%rbp, %rsi
	call	memcpy@PLT
	movq	(%r12), %rdi
	jmp	.L78
.L89:
	leaq	.LC0(%rip), %rdi
	call	_ZSt19__throw_logic_errorPKc@PLT
	.p2align 4,,10
	.p2align 3
.L93:
	call	_ZSt17__throw_bad_allocv@PLT
.L92:
	leaq	.LC1(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE11975:
	.size	_ZNK6Entity9get_classB5cxx11Ev, .-_ZNK6Entity9get_classB5cxx11Ev
	.align 2
	.p2align 4
	.globl	_ZNK6Entity14get_position2DEv
	.type	_ZNK6Entity14get_position2DEv, @function
_ZNK6Entity14get_position2DEv:
.LFB11976:
	.cfi_startproc
	endbr64
	movq	60(%rsi), %rdx
	movq	%rdi, %rax
	movq	%rdx, (%rdi)
	ret
	.cfi_endproc
.LFE11976:
	.size	_ZNK6Entity14get_position2DEv, .-_ZNK6Entity14get_position2DEv
	.align 2
	.p2align 4
	.globl	_ZNK6Entity14get_position3DEv
	.type	_ZNK6Entity14get_position3DEv, @function
_ZNK6Entity14get_position3DEv:
.LFB11977:
	.cfi_startproc
	endbr64
	movq	60(%rsi), %rdx
	movss	68(%rsi), %xmm0
	movq	%rdi, %rax
	movq	%rdx, (%rdi)
	movss	%xmm0, 8(%rdi)
	ret
	.cfi_endproc
.LFE11977:
	.size	_ZNK6Entity14get_position3DEv, .-_ZNK6Entity14get_position3DEv
	.align 2
	.p2align 4
	.globl	_ZNK6Entity12get_diagonalEv
	.type	_ZNK6Entity12get_diagonalEv, @function
_ZNK6Entity12get_diagonalEv:
.LFB11978:
	.cfi_startproc
	endbr64
	movq	72(%rsi), %rdx
	movq	%rdi, %rax
	movq	%rdx, (%rdi)
	ret
	.cfi_endproc
.LFE11978:
	.size	_ZNK6Entity12get_diagonalEv, .-_ZNK6Entity12get_diagonalEv
	.align 2
	.p2align 4
	.globl	_ZN6Entity14set_position2DE6Point2IfE
	.type	_ZN6Entity14set_position2DE6Point2IfE, @function
_ZN6Entity14set_position2DE6Point2IfE:
.LFB11979:
	.cfi_startproc
	endbr64
	movq	(%rsi), %rax
	movq	%rax, 60(%rdi)
	ret
	.cfi_endproc
.LFE11979:
	.size	_ZN6Entity14set_position2DE6Point2IfE, .-_ZN6Entity14set_position2DE6Point2IfE
	.align 2
	.p2align 4
	.globl	_ZN6Entity14set_position3DE6Point3IfE
	.type	_ZN6Entity14set_position3DE6Point3IfE, @function
_ZN6Entity14set_position3DE6Point3IfE:
.LFB11980:
	.cfi_startproc
	endbr64
	movq	(%rsi), %rax
	movq	%rax, 60(%rdi)
	movss	8(%rsi), %xmm0
	movss	%xmm0, 68(%rdi)
	ret
	.cfi_endproc
.LFE11980:
	.size	_ZN6Entity14set_position3DE6Point3IfE, .-_ZN6Entity14set_position3DE6Point3IfE
	.align 2
	.p2align 4
	.globl	_ZNK6Entity13get_entity_idEv
	.type	_ZNK6Entity13get_entity_idEv, @function
_ZNK6Entity13get_entity_idEv:
.LFB11981:
	.cfi_startproc
	endbr64
	movl	52(%rdi), %eax
	ret
	.cfi_endproc
.LFE11981:
	.size	_ZNK6Entity13get_entity_idEv, .-_ZNK6Entity13get_entity_idEv
	.align 2
	.p2align 4
	.globl	_ZN6Entity13set_entity_idEi
	.type	_ZN6Entity13set_entity_idEi, @function
_ZN6Entity13set_entity_idEi:
.LFB11982:
	.cfi_startproc
	endbr64
	movl	%esi, 52(%rdi)
	ret
	.cfi_endproc
.LFE11982:
	.size	_ZN6Entity13set_entity_idEi, .-_ZN6Entity13set_entity_idEi
	.align 2
	.p2align 4
	.globl	_ZNK6Entity12max_corner2DEv
	.type	_ZNK6Entity12max_corner2DEv, @function
_ZNK6Entity12max_corner2DEv:
.LFB11983:
	.cfi_startproc
	endbr64
	movq	60(%rsi), %xmm0
	movq	72(%rsi), %xmm1
	movq	%rdi, %rax
	addps	%xmm1, %xmm0
	movlps	%xmm0, (%rdi)
	ret
	.cfi_endproc
.LFE11983:
	.size	_ZNK6Entity12max_corner2DEv, .-_ZNK6Entity12max_corner2DEv
	.align 2
	.p2align 4
	.globl	_ZNK6Entity12max_corner3DEv
	.type	_ZNK6Entity12max_corner3DEv, @function
_ZNK6Entity12max_corner3DEv:
.LFB11984:
	.cfi_startproc
	endbr64
	movq	60(%rsi), %xmm0
	movq	72(%rsi), %xmm2
	movq	%rdi, %rax
	movss	68(%rsi), %xmm1
	addps	%xmm2, %xmm0
	movss	%xmm1, 8(%rdi)
	movlps	%xmm0, (%rdi)
	ret
	.cfi_endproc
.LFE11984:
	.size	_ZNK6Entity12max_corner3DEv, .-_ZNK6Entity12max_corner3DEv
	.align 2
	.p2align 4
	.globl	_ZNK6Entity7bound2fEv
	.type	_ZNK6Entity7bound2fEv, @function
_ZNK6Entity7bound2fEv:
.LFB11985:
	.cfi_startproc
	endbr64
	movss	64(%rsi), %xmm2
	movss	60(%rsi), %xmm0
	movq	%rdi, %rax
	movss	76(%rsi), %xmm3
	movss	72(%rsi), %xmm4
	movaps	%xmm0, %xmm1
	movaps	%xmm2, %xmm5
	addss	%xmm2, %xmm3
	addss	%xmm0, %xmm4
	minss	%xmm3, %xmm5
	minss	%xmm4, %xmm1
	maxss	%xmm4, %xmm0
	maxss	%xmm3, %xmm2
	unpcklps	%xmm5, %xmm1
	unpcklps	%xmm2, %xmm0
	movlhps	%xmm0, %xmm1
	movups	%xmm1, (%rdi)
	ret
	.cfi_endproc
.LFE11985:
	.size	_ZNK6Entity7bound2fEv, .-_ZNK6Entity7bound2fEv
	.align 2
	.p2align 4
	.globl	_ZNK6Entity18get_active_textureEv
	.type	_ZNK6Entity18get_active_textureEv, @function
_ZNK6Entity18get_active_textureEv:
.LFB11986:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	addq	$8, %rsi
	movq	%rdi, %r12
	call	_ZN7TextureC1ERKS_@PLT
	movq	%r12, %rax
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11986:
	.size	_ZNK6Entity18get_active_textureEv, .-_ZNK6Entity18get_active_textureEv
	.align 2
	.p2align 4
	.globl	_ZN6Entity18set_active_textureE7Texture
	.type	_ZN6Entity18set_active_textureE7Texture, @function
_ZN6Entity18set_active_textureE7Texture:
.LFB11987:
	.cfi_startproc
	endbr64
	addq	$8, %rdi
	jmp	_ZN7TextureaSERKS_@PLT
	.cfi_endproc
.LFE11987:
	.size	_ZN6Entity18set_active_textureE7Texture, .-_ZN6Entity18set_active_textureE7Texture
	.align 2
	.p2align 4
	.globl	_ZNK6Entity10is_deletedEv
	.type	_ZNK6Entity10is_deletedEv, @function
_ZNK6Entity10is_deletedEv:
.LFB11988:
	.cfi_startproc
	endbr64
	movzbl	48(%rdi), %eax
	ret
	.cfi_endproc
.LFE11988:
	.size	_ZNK6Entity10is_deletedEv, .-_ZNK6Entity10is_deletedEv
	.align 2
	.p2align 4
	.globl	_ZN6Entity7destroyEv
	.type	_ZN6Entity7destroyEv, @function
_ZN6Entity7destroyEv:
.LFB11989:
	.cfi_startproc
	endbr64
	movb	$1, 48(%rdi)
	ret
	.cfi_endproc
.LFE11989:
	.size	_ZN6Entity7destroyEv, .-_ZN6Entity7destroyEv
	.align 2
	.p2align 4
	.globl	_ZNK6Entity18mouse_was_hoveringEv
	.type	_ZNK6Entity18mouse_was_hoveringEv, @function
_ZNK6Entity18mouse_was_hoveringEv:
.LFB11990:
	.cfi_startproc
	endbr64
	movzbl	56(%rdi), %eax
	ret
	.cfi_endproc
.LFE11990:
	.size	_ZNK6Entity18mouse_was_hoveringEv, .-_ZNK6Entity18mouse_was_hoveringEv
	.align 2
	.p2align 4
	.globl	_ZN6Entity18enable_mouse_hoverEv
	.type	_ZN6Entity18enable_mouse_hoverEv, @function
_ZN6Entity18enable_mouse_hoverEv:
.LFB11991:
	.cfi_startproc
	endbr64
	movb	$1, 56(%rdi)
	ret
	.cfi_endproc
.LFE11991:
	.size	_ZN6Entity18enable_mouse_hoverEv, .-_ZN6Entity18enable_mouse_hoverEv
	.align 2
	.p2align 4
	.globl	_ZN6Entity19disable_mouse_hoverEv
	.type	_ZN6Entity19disable_mouse_hoverEv, @function
_ZN6Entity19disable_mouse_hoverEv:
.LFB11992:
	.cfi_startproc
	endbr64
	movb	$0, 56(%rdi)
	ret
	.cfi_endproc
.LFE11992:
	.size	_ZN6Entity19disable_mouse_hoverEv, .-_ZN6Entity19disable_mouse_hoverEv
	.section	.text.unlikely,"ax",@progbits
	.align 2
.LCOLDB4:
	.text
.LHOTB4:
	.align 2
	.p2align 4
	.globl	_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE
	.type	_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE, @function
_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE:
.LFB11993:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA11993
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
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
	subq	$200, %rsp
	.cfi_def_cfa_offset 256
	movss	64(%rdi), %xmm0
	movss	76(%rdi), %xmm1
	movss	60(%rdi), %xmm2
	movss	72(%rdi), %xmm3
	movq	%rdx, 40(%rsp)
	addss	%xmm0, %xmm1
	movaps	%xmm0, %xmm7
	addss	%xmm2, %xmm3
	movaps	%xmm2, %xmm6
	movq	%fs:40, %rax
	movq	%rax, 184(%rsp)
	xorl	%eax, %eax
	movq	(%rsi), %rax
	minss	%xmm1, %xmm7
	maxss	%xmm0, %xmm1
	movss	72(%rax), %xmm4
	movss	60(%rax), %xmm0
	minss	%xmm3, %xmm6
	maxss	%xmm3, %xmm2
	movss	76(%rax), %xmm5
	movss	64(%rax), %xmm3
	addss	%xmm0, %xmm4
	movaps	%xmm0, %xmm8
	addss	%xmm3, %xmm5
	movaps	%xmm3, %xmm9
	maxss	%xmm4, %xmm0
	minss	%xmm4, %xmm8
	maxss	%xmm5, %xmm3
	minss	%xmm5, %xmm9
	comiss	%xmm6, %xmm0
	seta	%r12b
	comiss	%xmm8, %xmm2
	seta	%al
	andl	%eax, %r12d
	comiss	%xmm7, %xmm3
	seta	%al
	andl	%eax, %r12d
	comiss	%xmm9, %xmm1
	seta	%al
	andb	%al, %r12b
	jne	.L189
.L112:
	movq	184(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L190
	addq	$200, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movl	%r12d, %eax
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
.L189:
	.cfi_restore_state
	minss	%xmm3, %xmm1
	maxss	%xmm8, %xmm6
	movq	%rsi, %r13
	movq	%rdi, %rbx
	minss	%xmm2, %xmm0
	maxss	%xmm9, %xmm7
	leaq	96(%rsp), %r14
	leaq	8(%rdi), %rsi
	movaps	%xmm1, %xmm5
	movaps	%xmm6, %xmm2
	movq	%r14, %rdi
	minss	%xmm7, %xmm5
	minss	%xmm0, %xmm2
	maxss	%xmm7, %xmm1
	maxss	%xmm0, %xmm6
	movss	%xmm5, 36(%rsp)
	movss	%xmm2, 72(%rsp)
	movd	%xmm1, %ebp
	movd	%xmm6, %r15d
.LEHB0:
	call	_ZN7TextureC1ERKS_@PLT
.LEHE0:
	movq	0(%r13), %rax
	leaq	8(%rax), %rsi
	leaq	144(%rsp), %rax
	movq	%rax, %rdi
	movq	%rax, 48(%rsp)
.LEHB1:
	call	_ZN7TextureC1ERKS_@PLT
.LEHE1:
	movd	%ebp, %xmm0
	subss	36(%rsp), %xmm0
	movss	.LC3(%rip), %xmm1
	leaq	80(%rsp), %rax
	movl	$0, 68(%rsp)
	movq	%rax, 56(%rsp)
	mulss	%xmm1, %xmm0
	movss	%xmm0, 64(%rsp)
	movd	%r15d, %xmm0
	leaq	88(%rsp), %r15
	subss	72(%rsp), %xmm0
	mulss	%xmm1, %xmm0
	movss	%xmm0, 76(%rsp)
	pxor	%xmm0, %xmm0
.L116:
	mulss	76(%rsp), %xmm0
	xorl	%ebp, %ebp
	addss	72(%rsp), %xmm0
	movss	%xmm0, 12(%rsp)
	pxor	%xmm0, %xmm0
	jmp	.L118
	.p2align 4,,10
	.p2align 3
.L120:
	addl	$1, %ebp
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%ebp, %xmm0
	cmpl	$10, %ebp
	je	.L191
.L118:
	mulss	64(%rsp), %xmm0
	movq	0(%r13), %rax
	movq	%r15, %rsi
	movq	%r14, %rdi
	movss	36(%rsp), %xmm6
	movss	12(%rsp), %xmm1
	movss	64(%rax), %xmm5
	movss	60(%rax), %xmm2
	movss	72(%rax), %xmm7
	movss	76(%rax), %xmm4
	subss	60(%rbx), %xmm1
	movss	%xmm5, 20(%rsp)
	divss	72(%rbx), %xmm1
	addss	%xmm0, %xmm6
	movss	%xmm2, 24(%rsp)
	movss	%xmm7, 28(%rsp)
	movss	%xmm4, 32(%rsp)
	movss	%xmm6, 16(%rsp)
	subss	64(%rbx), %xmm6
	movss	%xmm1, 88(%rsp)
	movaps	%xmm6, %xmm0
	divss	76(%rbx), %xmm0
	movss	%xmm0, 92(%rsp)
.LEHB2:
	call	_ZNK7Texture14is_alpha_pixelE6Point2IfE@PLT
	testb	%al, %al
	jne	.L120
	movq	56(%rsp), %rsi
	movq	48(%rsp), %rdi
	movss	12(%rsp), %xmm0
	movss	16(%rsp), %xmm1
	subss	24(%rsp), %xmm0
	subss	20(%rsp), %xmm1
	divss	28(%rsp), %xmm0
	divss	32(%rsp), %xmm1
	unpcklps	%xmm1, %xmm0
	movlps	%xmm0, 80(%rsp)
	call	_ZNK7Texture14is_alpha_pixelE6Point2IfE@PLT
.LEHE2:
	testb	%al, %al
	jne	.L120
	movss	12(%rsp), %xmm0
	movss	16(%rsp), %xmm3
	movq	40(%rsp), %rax
	movq	168(%rsp), %rbp
	unpcklps	%xmm3, %xmm0
	movlps	%xmm0, (%rax)
	testq	%rbp, %rbp
	je	.L122
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L123
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L124:
	cmpl	$1, %eax
	je	.L192
.L122:
	movq	152(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L129
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L130
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L131:
	cmpl	$1, %eax
	je	.L193
.L129:
	movq	120(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L136
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L137
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L138:
	cmpl	$1, %eax
	je	.L194
.L136:
	movq	104(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L112
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L144
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L145:
	cmpl	$1, %eax
	jne	.L112
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L147
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L148:
	cmpl	$1, %eax
	jne	.L112
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L112
	.p2align 4,,10
	.p2align 3
.L191:
	addl	$1, 68(%rsp)
	movl	68(%rsp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2ssl	%eax, %xmm0
	cmpl	$10, %eax
	jne	.L116
	movq	168(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L151
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L152
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L153:
	cmpl	$1, %eax
	je	.L195
.L151:
	movq	152(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L158
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L159
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L160:
	cmpl	$1, %eax
	je	.L196
.L158:
	movq	120(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L165
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L166
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L167:
	cmpl	$1, %eax
	je	.L197
.L165:
	movq	104(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L172
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L173
	movl	8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rbp)
.L174:
	cmpl	$1, %eax
	je	.L198
.L172:
	xorl	%r12d, %r12d
	jmp	.L112
.L192:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L126
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L127:
	cmpl	$1, %eax
	jne	.L122
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L122
.L193:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L133
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L134:
	cmpl	$1, %eax
	jne	.L129
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L129
.L194:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L140
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L141:
	cmpl	$1, %eax
	jne	.L136
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L136
.L144:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L145
.L137:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L138
.L123:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L124
.L130:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L131
.L198:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L176
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L177:
	cmpl	$1, %eax
	jne	.L172
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L172
.L195:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L155
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L156:
	cmpl	$1, %eax
	jne	.L151
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L151
.L196:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L162
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L163:
	cmpl	$1, %eax
	jne	.L158
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L158
.L197:
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L169
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L170:
	cmpl	$1, %eax
	jne	.L165
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*24(%rax)
	jmp	.L165
.L173:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L174
.L159:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L160
.L166:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L167
.L152:
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rbp)
	jmp	.L153
.L126:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L127
.L147:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L148
.L140:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L141
.L133:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L134
.L155:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L156
.L162:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L163
.L176:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L177
.L169:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L170
.L190:
	call	__stack_chk_fail@PLT
.L182:
	endbr64
	movq	%rax, %rbp
	jmp	.L178
.L181:
	endbr64
	movq	%rax, %rbp
	jmp	.L179
	.section	.gcc_except_table,"a",@progbits
.LLSDA11993:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE11993-.LLSDACSB11993
.LLSDACSB11993:
	.uleb128 .LEHB0-.LFB11993
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB11993
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L181-.LFB11993
	.uleb128 0
	.uleb128 .LEHB2-.LFB11993
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L182-.LFB11993
	.uleb128 0
.LLSDACSE11993:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC11993
	.type	_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE.cold, @function
_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE.cold:
.LFSB11993:
.L178:
	.cfi_def_cfa_offset 256
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	48(%rsp), %rdi
	call	_ZN7TextureD1Ev
.L179:
	movq	%r14, %rdi
	call	_ZN7TextureD1Ev
	movq	%rbp, %rdi
.LEHB3:
	call	_Unwind_Resume@PLT
.LEHE3:
	.cfi_endproc
.LFE11993:
	.section	.gcc_except_table
.LLSDAC11993:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC11993-.LLSDACSBC11993
.LLSDACSBC11993:
	.uleb128 .LEHB3-.LCOLDB4
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSEC11993:
	.section	.text.unlikely
	.text
	.size	_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE, .-_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE
	.section	.text.unlikely
	.size	_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE.cold, .-_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE.cold
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
	.align 2
.LCOLDB5:
	.text
.LHOTB5:
	.align 2
	.p2align 4
	.globl	_ZNK6Entity8containsE6Point2IfE
	.type	_ZNK6Entity8containsE6Point2IfE, @function
_ZNK6Entity8containsE6Point2IfE:
.LFB12025:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA12025
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$80, %rsp
	.cfi_def_cfa_offset 112
	movss	60(%rdi), %xmm0
	movss	72(%rdi), %xmm2
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movss	(%rsi), %xmm1
	movss	64(%rdi), %xmm4
	addss	%xmm0, %xmm2
	movaps	%xmm0, %xmm3
	movss	76(%rdi), %xmm5
	maxss	%xmm2, %xmm3
	comiss	%xmm1, %xmm3
	jb	.L200
	minss	%xmm2, %xmm0
	comiss	%xmm0, %xmm1
	jnb	.L233
.L200:
	xorl	%eax, %eax
.L199:
	movq	72(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L234
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L233:
	.cfi_restore_state
	addss	%xmm4, %xmm5
	movaps	%xmm4, %xmm1
	movss	4(%rsi), %xmm0
	movq	%rsi, %rbp
	minss	%xmm5, %xmm1
	comiss	%xmm1, %xmm0
	jb	.L200
	maxss	%xmm5, %xmm4
	comiss	%xmm0, %xmm4
	jb	.L200
	leaq	32(%rsp), %r12
	movq	%rdi, %rbx
	leaq	8(%rdi), %rsi
	movq	%r12, %rdi
.LEHB4:
	call	_ZN7TextureC1ERKS_@PLT
.LEHE4:
	movss	0(%rbp), %xmm0
	movss	4(%rbp), %xmm1
	movq	%r12, %rdi
	subss	60(%rbx), %xmm0
	subss	64(%rbx), %xmm1
	divss	72(%rbx), %xmm0
	divss	76(%rbx), %xmm1
	leaq	24(%rsp), %rsi
	unpcklps	%xmm1, %xmm0
	movlps	%xmm0, 24(%rsp)
.LEHB5:
	call	_ZNK7Texture14is_alpha_pixelE6Point2IfE@PLT
.LEHE5:
	movq	56(%rsp), %rbp
	xorl	$1, %eax
	testq	%rbp, %rbp
	je	.L204
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L205
	movl	8(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 8(%rbp)
.L206:
	cmpl	$1, %edx
	jne	.L204
	movq	0(%rbp), %rdx
	movb	%al, 15(%rsp)
	movq	%rbp, %rdi
	call	*16(%rdx)
	cmpb	$0, __libc_single_threaded(%rip)
	movzbl	15(%rsp), %eax
	je	.L208
	movl	12(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 12(%rbp)
.L209:
	cmpl	$1, %edx
	jne	.L204
	movq	0(%rbp), %rdx
	movb	%al, 15(%rsp)
	movq	%rbp, %rdi
	call	*24(%rdx)
	movzbl	15(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L204:
	movq	40(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L199
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L212
	movl	8(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 8(%rbp)
.L213:
	cmpl	$1, %edx
	jne	.L199
	movq	0(%rbp), %rdx
	movb	%al, 15(%rsp)
	movq	%rbp, %rdi
	call	*16(%rdx)
	cmpb	$0, __libc_single_threaded(%rip)
	movzbl	15(%rsp), %eax
	je	.L215
	movl	12(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 12(%rbp)
.L216:
	cmpl	$1, %edx
	jne	.L199
	movq	0(%rbp), %rdx
	movb	%al, 15(%rsp)
	movq	%rbp, %rdi
	call	*24(%rdx)
	movzbl	15(%rsp), %eax
	jmp	.L199
	.p2align 4,,10
	.p2align 3
.L212:
	movl	$-1, %edx
	lock xaddl	%edx, 8(%rbp)
	jmp	.L213
	.p2align 4,,10
	.p2align 3
.L205:
	movl	$-1, %edx
	lock xaddl	%edx, 8(%rbp)
	jmp	.L206
.L215:
	movl	$-1, %edx
	lock xaddl	%edx, 12(%rbp)
	jmp	.L216
.L208:
	movl	$-1, %edx
	lock xaddl	%edx, 12(%rbp)
	jmp	.L209
.L234:
	call	__stack_chk_fail@PLT
.L219:
	endbr64
	movq	%rax, %rbp
	jmp	.L217
	.section	.gcc_except_table
.LLSDA12025:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE12025-.LLSDACSB12025
.LLSDACSB12025:
	.uleb128 .LEHB4-.LFB12025
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB5-.LFB12025
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L219-.LFB12025
	.uleb128 0
.LLSDACSE12025:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC12025
	.type	_ZNK6Entity8containsE6Point2IfE.cold, @function
_ZNK6Entity8containsE6Point2IfE.cold:
.LFSB12025:
.L217:
	.cfi_def_cfa_offset 112
	.cfi_offset 3, -32
	.cfi_offset 6, -24
	.cfi_offset 12, -16
	movq	%r12, %rdi
	call	_ZN7TextureD1Ev
	movq	%rbp, %rdi
.LEHB6:
	call	_Unwind_Resume@PLT
.LEHE6:
	.cfi_endproc
.LFE12025:
	.section	.gcc_except_table
.LLSDAC12025:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC12025-.LLSDACSBC12025
.LLSDACSBC12025:
	.uleb128 .LEHB6-.LCOLDB5
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSEC12025:
	.section	.text.unlikely
	.text
	.size	_ZNK6Entity8containsE6Point2IfE, .-_ZNK6Entity8containsE6Point2IfE
	.section	.text.unlikely
	.size	_ZNK6Entity8containsE6Point2IfE.cold, .-_ZNK6Entity8containsE6Point2IfE.cold
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
	.align 2
.LCOLDB6:
	.text
.LHOTB6:
	.align 2
	.p2align 4
	.globl	_ZNK6Entity18contains_the_mouseER6Engine
	.type	_ZNK6Entity18contains_the_mouseER6Engine, @function
_ZNK6Entity18contains_the_mouseER6Engine:
.LFB12026:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA12026
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	subq	$80, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	leaq	24(%rsp), %rdi
.LEHB7:
	call	_ZN6Engine18get_mouse_positionEv@PLT
	movss	60(%rbx), %xmm1
	movss	72(%rbx), %xmm3
	movss	24(%rsp), %xmm2
	movss	64(%rbx), %xmm5
	movaps	%xmm1, %xmm0
	movaps	%xmm1, %xmm4
	movss	76(%rbx), %xmm6
	addss	%xmm3, %xmm0
	maxss	%xmm0, %xmm4
	comiss	%xmm2, %xmm4
	jb	.L236
	minss	%xmm1, %xmm0
	comiss	%xmm0, %xmm2
	jnb	.L269
.L236:
	xorl	%eax, %eax
.L235:
	movq	72(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L270
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L269:
	.cfi_restore_state
	movaps	%xmm5, %xmm0
	movaps	%xmm5, %xmm7
	movss	28(%rsp), %xmm4
	addss	%xmm6, %xmm0
	minss	%xmm0, %xmm7
	comiss	%xmm7, %xmm4
	jb	.L236
	maxss	%xmm5, %xmm0
	comiss	%xmm4, %xmm0
	jb	.L236
	subss	%xmm1, %xmm2
	subss	%xmm5, %xmm4
	leaq	32(%rsp), %rbp
	leaq	8(%rbx), %rsi
	movq	%rbp, %rdi
	divss	%xmm3, %xmm2
	divss	%xmm6, %xmm4
	unpcklps	%xmm4, %xmm2
	movlps	%xmm2, 8(%rsp)
	call	_ZN7TextureC1ERKS_@PLT
.LEHE7:
	movq	8(%rsp), %xmm2
	leaq	16(%rsp), %rsi
	movq	%rbp, %rdi
	movlps	%xmm2, 16(%rsp)
.LEHB8:
	call	_ZNK7Texture14is_alpha_pixelE6Point2IfE@PLT
.LEHE8:
	movq	56(%rsp), %rbp
	xorl	$1, %eax
	testq	%rbp, %rbp
	je	.L240
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L241
	movl	8(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 8(%rbp)
.L242:
	cmpl	$1, %edx
	jne	.L240
	movq	0(%rbp), %rdx
	movb	%al, 8(%rsp)
	movq	%rbp, %rdi
	call	*16(%rdx)
	cmpb	$0, __libc_single_threaded(%rip)
	movzbl	8(%rsp), %eax
	je	.L244
	movl	12(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 12(%rbp)
.L245:
	cmpl	$1, %edx
	jne	.L240
	movq	0(%rbp), %rdx
	movb	%al, 8(%rsp)
	movq	%rbp, %rdi
	call	*24(%rdx)
	movzbl	8(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L240:
	movq	40(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L235
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L248
	movl	8(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 8(%rbp)
.L249:
	cmpl	$1, %edx
	jne	.L235
	movq	0(%rbp), %rdx
	movb	%al, 8(%rsp)
	movq	%rbp, %rdi
	call	*16(%rdx)
	cmpb	$0, __libc_single_threaded(%rip)
	movzbl	8(%rsp), %eax
	je	.L251
	movl	12(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 12(%rbp)
.L252:
	cmpl	$1, %edx
	jne	.L235
	movq	0(%rbp), %rdx
	movb	%al, 8(%rsp)
	movq	%rbp, %rdi
	call	*24(%rdx)
	movzbl	8(%rsp), %eax
	jmp	.L235
	.p2align 4,,10
	.p2align 3
.L248:
	movl	$-1, %edx
	lock xaddl	%edx, 8(%rbp)
	jmp	.L249
	.p2align 4,,10
	.p2align 3
.L241:
	movl	$-1, %edx
	lock xaddl	%edx, 8(%rbp)
	jmp	.L242
.L251:
	movl	$-1, %edx
	lock xaddl	%edx, 12(%rbp)
	jmp	.L252
.L244:
	movl	$-1, %edx
	lock xaddl	%edx, 12(%rbp)
	jmp	.L245
.L270:
	call	__stack_chk_fail@PLT
.L255:
	endbr64
	movq	%rax, %r12
	jmp	.L253
	.section	.gcc_except_table
.LLSDA12026:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE12026-.LLSDACSB12026
.LLSDACSB12026:
	.uleb128 .LEHB7-.LFB12026
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB8-.LFB12026
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L255-.LFB12026
	.uleb128 0
.LLSDACSE12026:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC12026
	.type	_ZNK6Entity18contains_the_mouseER6Engine.cold, @function
_ZNK6Entity18contains_the_mouseER6Engine.cold:
.LFSB12026:
.L253:
	.cfi_def_cfa_offset 112
	.cfi_offset 3, -32
	.cfi_offset 6, -24
	.cfi_offset 12, -16
	movq	%rbp, %rdi
	call	_ZN7TextureD1Ev
	movq	%r12, %rdi
.LEHB9:
	call	_Unwind_Resume@PLT
.LEHE9:
	.cfi_endproc
.LFE12026:
	.section	.gcc_except_table
.LLSDAC12026:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC12026-.LLSDACSBC12026
.LLSDACSBC12026:
	.uleb128 .LEHB9-.LCOLDB6
	.uleb128 .LEHE9-.LEHB9
	.uleb128 0
	.uleb128 0
.LLSDACSEC12026:
	.section	.text.unlikely
	.text
	.size	_ZNK6Entity18contains_the_mouseER6Engine, .-_ZNK6Entity18contains_the_mouseER6Engine
	.section	.text.unlikely
	.size	_ZNK6Entity18contains_the_mouseER6Engine.cold, .-_ZNK6Entity18contains_the_mouseER6Engine.cold
.LCOLDE6:
	.text
.LHOTE6:
	.section	.text.unlikely
	.align 2
.LCOLDB7:
	.text
.LHOTB7:
	.align 2
	.p2align 4
	.globl	_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE
	.type	_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE, @function
_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE:
.LFB12027:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA12027
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	subq	$88, %rsp
	.cfi_def_cfa_offset 112
	movss	60(%rdi), %xmm1
	movss	72(%rdi), %xmm3
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movss	(%rdx), %xmm2
	movss	64(%rdi), %xmm5
	movaps	%xmm1, %xmm0
	movaps	%xmm1, %xmm4
	movss	76(%rdi), %xmm6
	addss	%xmm3, %xmm0
	maxss	%xmm0, %xmm4
	comiss	%xmm2, %xmm4
	jb	.L272
	minss	%xmm1, %xmm0
	comiss	%xmm0, %xmm2
	jnb	.L305
.L272:
	xorl	%eax, %eax
.L271:
	movq	72(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L306
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L305:
	.cfi_restore_state
	movaps	%xmm5, %xmm0
	movaps	%xmm5, %xmm7
	movss	4(%rdx), %xmm4
	addss	%xmm6, %xmm0
	minss	%xmm0, %xmm7
	comiss	%xmm7, %xmm4
	jb	.L272
	maxss	%xmm5, %xmm0
	comiss	%xmm4, %xmm0
	jb	.L272
	subss	%xmm1, %xmm2
	subss	%xmm5, %xmm4
	leaq	32(%rsp), %rbp
	leaq	8(%rdi), %rsi
	movq	%rbp, %rdi
	divss	%xmm3, %xmm2
	divss	%xmm6, %xmm4
	unpcklps	%xmm4, %xmm2
	movlps	%xmm2, 8(%rsp)
.LEHB10:
	call	_ZN7TextureC1ERKS_@PLT
.LEHE10:
	movq	8(%rsp), %xmm2
	leaq	24(%rsp), %rsi
	movq	%rbp, %rdi
	movlps	%xmm2, 24(%rsp)
.LEHB11:
	call	_ZNK7Texture14is_alpha_pixelE6Point2IfE@PLT
.LEHE11:
	movq	56(%rsp), %rbp
	xorl	$1, %eax
	testq	%rbp, %rbp
	je	.L276
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L277
	movl	8(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 8(%rbp)
.L278:
	cmpl	$1, %edx
	jne	.L276
	movq	0(%rbp), %rdx
	movb	%al, 8(%rsp)
	movq	%rbp, %rdi
	call	*16(%rdx)
	cmpb	$0, __libc_single_threaded(%rip)
	movzbl	8(%rsp), %eax
	je	.L280
	movl	12(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 12(%rbp)
.L281:
	cmpl	$1, %edx
	jne	.L276
	movq	0(%rbp), %rdx
	movb	%al, 8(%rsp)
	movq	%rbp, %rdi
	call	*24(%rdx)
	movzbl	8(%rsp), %eax
	.p2align 4,,10
	.p2align 3
.L276:
	movq	40(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L271
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L284
	movl	8(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 8(%rbp)
.L285:
	cmpl	$1, %edx
	jne	.L271
	movq	0(%rbp), %rdx
	movb	%al, 8(%rsp)
	movq	%rbp, %rdi
	call	*16(%rdx)
	cmpb	$0, __libc_single_threaded(%rip)
	movzbl	8(%rsp), %eax
	je	.L287
	movl	12(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 12(%rbp)
.L288:
	cmpl	$1, %edx
	jne	.L271
	movq	0(%rbp), %rdx
	movb	%al, 8(%rsp)
	movq	%rbp, %rdi
	call	*24(%rdx)
	movzbl	8(%rsp), %eax
	jmp	.L271
	.p2align 4,,10
	.p2align 3
.L284:
	movl	$-1, %edx
	lock xaddl	%edx, 8(%rbp)
	jmp	.L285
	.p2align 4,,10
	.p2align 3
.L277:
	movl	$-1, %edx
	lock xaddl	%edx, 8(%rbp)
	jmp	.L278
.L287:
	movl	$-1, %edx
	lock xaddl	%edx, 12(%rbp)
	jmp	.L288
.L280:
	movl	$-1, %edx
	lock xaddl	%edx, 12(%rbp)
	jmp	.L281
.L306:
	call	__stack_chk_fail@PLT
.L291:
	endbr64
	movq	%rax, %r12
	jmp	.L289
	.section	.gcc_except_table
.LLSDA12027:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE12027-.LLSDACSB12027
.LLSDACSB12027:
	.uleb128 .LEHB10-.LFB12027
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB11-.LFB12027
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L291-.LFB12027
	.uleb128 0
.LLSDACSE12027:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC12027
	.type	_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE.cold, @function
_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE.cold:
.LFSB12027:
.L289:
	.cfi_def_cfa_offset 112
	.cfi_offset 6, -24
	.cfi_offset 12, -16
	movq	%rbp, %rdi
	call	_ZN7TextureD1Ev
	movq	%r12, %rdi
.LEHB12:
	call	_Unwind_Resume@PLT
.LEHE12:
	.cfi_endproc
.LFE12027:
	.section	.gcc_except_table
.LLSDAC12027:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC12027-.LLSDACSBC12027
.LLSDACSBC12027:
	.uleb128 .LEHB12-.LCOLDB7
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
.LLSDACSEC12027:
	.section	.text.unlikely
	.text
	.size	_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE, .-_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE
	.section	.text.unlikely
	.size	_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE.cold, .-_ZNK6Entity18contains_the_mouseER6Engine6Point2IfE.cold
.LCOLDE7:
	.text
.LHOTE7:
	.section	.text._ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv,"axG",@progbits,_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
	.type	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv, @function
_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv:
.LFB12667:
	.cfi_startproc
	endbr64
	cmpb	$0, __libc_single_threaded(%rip)
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	je	.L308
	movl	8(%rdi), %eax
	leal	-1(%rax), %edx
	movl	%edx, 8(%rdi)
.L309:
	cmpl	$1, %eax
	je	.L316
.L307:
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L316:
	.cfi_restore_state
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	call	*16(%rax)
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L312
	movl	12(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, 12(%rbp)
.L313:
	cmpl	$1, %eax
	jne	.L307
	movq	0(%rbp), %rax
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	movq	24(%rax), %rax
	jmp	*%rax
	.p2align 4,,10
	.p2align 3
.L308:
	.cfi_restore_state
	movl	$-1, %eax
	lock xaddl	%eax, 8(%rdi)
	jmp	.L309
	.p2align 4,,10
	.p2align 3
.L312:
	movl	$-1, %eax
	lock xaddl	%eax, 12(%rbp)
	jmp	.L313
	.cfi_endproc
.LFE12667:
	.size	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv, .-_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
	.section	.text.unlikely
	.align 2
.LCOLDB8:
	.text
.LHOTB8:
	.align 2
	.p2align 4
	.globl	_ZNK6Entity8collidesESt10shared_ptrIS_E
	.type	_ZNK6Entity8collidesESt10shared_ptrIS_E, @function
_ZNK6Entity8collidesESt10shared_ptrIS_E:
.LFB12011:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA12011
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	subq	$64, %rsp
	.cfi_def_cfa_offset 80
	movdqu	(%rsi), %xmm0
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	movaps	%xmm0, 32(%rsp)
	movq	40(%rsp), %rax
	testq	%rax, %rax
	je	.L318
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L319
	addl	$1, 8(%rax)
.L318:
	leaq	24(%rsp), %rdx
	leaq	32(%rsp), %rsi
.LEHB13:
	call	_ZNK6Entity8collidesESt10shared_ptrIS_ER6Point2IfE
.LEHE13:
	movq	40(%rsp), %rbp
	testq	%rbp, %rbp
	je	.L317
	cmpb	$0, __libc_single_threaded(%rip)
	je	.L322
	movl	8(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 8(%rbp)
.L323:
	cmpl	$1, %edx
	je	.L338
.L317:
	movq	56(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L339
	addq	$64, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L319:
	.cfi_restore_state
	lock addl	$1, 8(%rax)
	jmp	.L318
	.p2align 4,,10
	.p2align 3
.L338:
	movq	0(%rbp), %rdx
	movb	%al, 15(%rsp)
	movq	%rbp, %rdi
	call	*16(%rdx)
	cmpb	$0, __libc_single_threaded(%rip)
	movzbl	15(%rsp), %eax
	je	.L325
	movl	12(%rbp), %edx
	leal	-1(%rdx), %ecx
	movl	%ecx, 12(%rbp)
.L326:
	cmpl	$1, %edx
	jne	.L317
	movq	0(%rbp), %rdx
	movb	%al, 15(%rsp)
	movq	%rbp, %rdi
	call	*24(%rdx)
	movzbl	15(%rsp), %eax
	jmp	.L317
	.p2align 4,,10
	.p2align 3
.L322:
	movl	$-1, %edx
	lock xaddl	%edx, 8(%rbp)
	jmp	.L323
	.p2align 4,,10
	.p2align 3
.L325:
	movl	$-1, %edx
	lock xaddl	%edx, 12(%rbp)
	jmp	.L326
.L339:
	call	__stack_chk_fail@PLT
.L330:
	endbr64
	movq	%rax, %rbp
	jmp	.L327
	.section	.gcc_except_table
.LLSDA12011:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE12011-.LLSDACSB12011
.LLSDACSB12011:
	.uleb128 .LEHB13-.LFB12011
	.uleb128 .LEHE13-.LEHB13
	.uleb128 .L330-.LFB12011
	.uleb128 0
.LLSDACSE12011:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC12011
	.type	_ZNK6Entity8collidesESt10shared_ptrIS_E.cold, @function
_ZNK6Entity8collidesESt10shared_ptrIS_E.cold:
.LFSB12011:
.L327:
	.cfi_def_cfa_offset 80
	.cfi_offset 6, -16
	movq	40(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L328
	call	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
.L328:
	movq	%rbp, %rdi
.LEHB14:
	call	_Unwind_Resume@PLT
.LEHE14:
	.cfi_endproc
.LFE12011:
	.section	.gcc_except_table
.LLSDAC12011:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC12011-.LLSDACSBC12011
.LLSDACSBC12011:
	.uleb128 .LEHB14-.LCOLDB8
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
.LLSDACSEC12011:
	.section	.text.unlikely
	.text
	.size	_ZNK6Entity8collidesESt10shared_ptrIS_E, .-_ZNK6Entity8collidesESt10shared_ptrIS_E
	.section	.text.unlikely
	.size	_ZNK6Entity8collidesESt10shared_ptrIS_E.cold, .-_ZNK6Entity8collidesESt10shared_ptrIS_E.cold
.LCOLDE8:
	.text
.LHOTE8:
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm:
.LFB12788:
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
	je	.L353
	movq	16(%rbx), %rax
.L341:
	testq	%rbp, %rbp
	js	.L367
	cmpq	%rax, %rbp
	jbe	.L343
	addq	%rax, %rax
	cmpq	%rax, %rbp
	jnb	.L343
	testq	%rax, %rax
	js	.L344
	movq	%rax, %rbp
	.p2align 4,,10
	.p2align 3
.L343:
	movq	%rbp, %rdi
	addq	$1, %rdi
	js	.L344
	movq	%rcx, 16(%rsp)
	call	_Znwm@PLT
	testq	%r12, %r12
	movq	16(%rsp), %rcx
	movq	%rax, %r15
	je	.L346
	movq	(%rbx), %rsi
	cmpq	$1, %r12
	je	.L368
	movq	%r12, %rdx
	movq	%rax, %rdi
	movq	%rcx, 16(%rsp)
	call	memcpy@PLT
	movq	16(%rsp), %rcx
.L346:
	testq	%rcx, %rcx
	je	.L348
	testq	%r14, %r14
	je	.L348
	leaq	(%r15,%r12), %rdi
	cmpq	$1, %r14
	je	.L369
	movq	%r14, %rdx
	movq	%rcx, %rsi
	call	memcpy@PLT
.L348:
	movq	8(%rsp), %rax
	movq	(%rbx), %r9
	testq	%rax, %rax
	je	.L350
.L371:
	movq	24(%rsp), %rsi
	leaq	(%r12,%r14), %r8
	leaq	(%r15,%r8), %rdi
	addq	%r9, %rsi
	cmpq	$1, %rax
	je	.L370
	movq	%rax, %rdx
	movq	%r9, 16(%rsp)
	call	memcpy@PLT
	movq	16(%rsp), %r9
.L350:
	cmpq	%r9, %r13
	je	.L352
.L372:
	movq	16(%rbx), %rax
	movq	%r9, %rdi
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L352:
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
.L344:
	.cfi_restore_state
	call	_ZSt17__throw_bad_allocv@PLT
	.p2align 4,,10
	.p2align 3
.L353:
	movl	$15, %eax
	jmp	.L341
	.p2align 4,,10
	.p2align 3
.L368:
	movzbl	(%rsi), %eax
	movb	%al, (%r15)
	jmp	.L346
	.p2align 4,,10
	.p2align 3
.L369:
	movzbl	(%rcx), %eax
	movq	(%rbx), %r9
	movb	%al, (%rdi)
	movq	8(%rsp), %rax
	testq	%rax, %rax
	je	.L350
	jmp	.L371
	.p2align 4,,10
	.p2align 3
.L370:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	cmpq	%r9, %r13
	jne	.L372
	jmp	.L352
.L367:
	leaq	.LC1(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE12788:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	.section	.rodata.str1.1
.LC9:
	.string	"basic_string::_M_replace"
	.text
	.align 2
	.p2align 4
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm.isra.0, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm.isra.0:
.LFB13057:
	.cfi_startproc
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
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	addq	%r12, %rax
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %rdx
	subq	%rdx, %rax
	cmpq	%r8, %rax
	jb	.L417
	movq	%r8, %r15
	movq	(%rdi), %rax
	movq	%rcx, %r14
	leaq	16(%rdi), %rcx
	subq	%r12, %r15
	movq	%rdi, %rbx
	movq	%r8, %r13
	leaq	(%rdx,%r15), %rbp
	cmpq	%rcx, %rax
	je	.L396
	movq	16(%rdi), %rcx
.L375:
	cmpq	%rcx, %rbp
	ja	.L376
	leaq	(%rax,%rsi), %r8
	movq	%rdx, %r9
	addq	%r12, %rsi
	subq	%rsi, %r9
	cmpq	%r14, %rax
	jbe	.L418
.L377:
	testq	%r9, %r9
	je	.L380
	cmpq	%r13, %r12
	je	.L380
	leaq	(%r8,%r12), %rsi
	leaq	(%r8,%r13), %rdi
	cmpq	$1, %r9
	je	.L419
	movq	%r9, %rdx
	movq	%r8, 8(%rsp)
	call	memmove@PLT
	movq	8(%rsp), %r8
.L380:
	testq	%r13, %r13
	je	.L383
	cmpq	$1, %r13
	je	.L416
	movq	%r13, %rdx
	movq	%r14, %rsi
	movq	%r8, %rdi
	call	memcpy@PLT
.L383:
	movq	(%rbx), %rax
	movq	%rbp, 8(%rbx)
	movb	$0, (%rax,%rbp)
	addq	$24, %rsp
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
.L418:
	.cfi_restore_state
	addq	%rdx, %rax
	cmpq	%rax, %r14
	ja	.L377
	leaq	-1(%r13), %rax
	cmpq	%rax, %r12
	jbe	.L379
	cmpq	$1, %r13
	je	.L420
	movq	%r8, %rdi
	movq	%r13, %rdx
	movq	%r14, %rsi
	movq	%r9, 8(%rsp)
	call	memmove@PLT
	movq	8(%rsp), %r9
	movq	%rax, %r8
.L379:
	testq	%r9, %r9
	je	.L386
	cmpq	%r13, %r12
	je	.L386
	leaq	(%r8,%r12), %rsi
	leaq	(%r8,%r13), %rdi
	cmpq	$1, %r9
	je	.L421
	movq	%r9, %rdx
	movq	%r8, 8(%rsp)
	call	memmove@PLT
	movq	8(%rsp), %r8
.L386:
	cmpq	%r13, %r12
	jnb	.L383
	addq	%r8, %r12
	leaq	(%r14,%r13), %rax
	cmpq	%rax, %r12
	jnb	.L422
	cmpq	%r12, %r14
	jb	.L391
	leaq	(%r14,%r15), %rsi
	cmpq	$1, %r13
	je	.L423
	movq	%r13, %rdx
	movq	%r8, %rdi
	call	memcpy@PLT
	jmp	.L383
	.p2align 4,,10
	.p2align 3
.L376:
	movq	%r13, %r8
	movq	%r14, %rcx
	movq	%r12, %rdx
	movq	%rbx, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm
	jmp	.L383
	.p2align 4,,10
	.p2align 3
.L416:
	movzbl	(%r14), %eax
	movb	%al, (%r8)
	jmp	.L383
	.p2align 4,,10
	.p2align 3
.L419:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L380
	.p2align 4,,10
	.p2align 3
.L396:
	movl	$15, %ecx
	jmp	.L375
	.p2align 4,,10
	.p2align 3
.L422:
	cmpq	$1, %r13
	je	.L416
	movq	%r13, %rdx
	movq	%r14, %rsi
	movq	%r8, %rdi
	call	memmove@PLT
	jmp	.L383
	.p2align 4,,10
	.p2align 3
.L421:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L386
	.p2align 4,,10
	.p2align 3
.L420:
	movzbl	(%r14), %eax
	movb	%al, (%r8)
	jmp	.L379
	.p2align 4,,10
	.p2align 3
.L391:
	subq	%r14, %r12
	cmpq	$1, %r12
	je	.L424
	testq	%r12, %r12
	je	.L394
	movq	%r8, %rdi
	movq	%r12, %rdx
	movq	%r14, %rsi
	call	memmove@PLT
	movq	%rax, %r8
.L394:
	movq	%r13, %rdx
	leaq	(%r8,%r13), %rsi
	leaq	(%r8,%r12), %rdi
	subq	%r12, %rdx
	cmpq	$1, %rdx
	je	.L425
	testq	%rdx, %rdx
	je	.L383
	call	memcpy@PLT
	jmp	.L383
.L424:
	movzbl	(%r14), %eax
	movb	%al, (%r8)
	jmp	.L394
.L425:
	movzbl	(%rsi), %eax
	movb	%al, (%rdi)
	jmp	.L383
.L423:
	movzbl	(%rsi), %eax
	movb	%al, (%r8)
	jmp	.L383
.L417:
	leaq	.LC9(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE13057:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm.isra.0, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm.isra.0
	.section	.text.unlikely
	.align 2
.LCOLDB11:
	.text
.LHOTB11:
	.align 2
	.p2align 4
	.globl	_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_
	.type	_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_, @function
_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_:
.LFB11967:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA11967
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rcx, %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	subq	$72, %rsp
	.cfi_def_cfa_offset 128
	movq	$0, 8(%rdi)
	movq	128(%rsp), %rax
	movq	$0, 16(%rdi)
	movq	%r8, 8(%rsp)
	movq	%rax, 24(%rsp)
	movq	136(%rsp), %rax
	movq	%r9, 16(%rsp)
	movq	%rax, 32(%rsp)
	leaq	16+_ZTV6Entity(%rip), %rax
	movq	%rax, (%rdi)
	movl	$32, %edi
.LEHB15:
	call	_Znwm@PLT
.LEHE15:
	movq	.LC10(%rip), %r14
	movq	SDL_DestroyTexture@GOTPCREL(%rip), %rdx
	movq	%rax, 16(%rbx)
	leaq	16+_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE(%rip), %rcx
	movq	%rcx, (%rax)
	movl	$32, %edi
	movq	%r14, 8(%rax)
	movq	%rdx, 16(%rax)
	movq	$0, 24(%rax)
	movq	$0, 24(%rbx)
	movq	$0, 32(%rbx)
.LEHB16:
	call	_Znwm@PLT
.LEHE16:
	movss	(%r12), %xmm0
	movss	8(%rbp), %xmm1
	movq	%r14, 8(%rax)
	leaq	16+_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE(%rip), %rsi
	movss	4(%rbp), %xmm2
	movq	%rsi, (%rax)
	leaq	8(%rbx), %r13
	movq	%r15, %rsi
	unpcklps	%xmm0, %xmm1
	movss	0(%rbp), %xmm0
	movq	%rax, 32(%rbx)
	movq	%r13, %rdi
	movq	SDL_FreeSurface@GOTPCREL(%rip), %rdx
	movq	$0, 24(%rax)
	leaq	112(%rbx), %r14
	unpcklps	%xmm2, %xmm0
	movq	$0, 40(%rbx)
	movq	%rdx, 16(%rax)
	leaq	80(%rbx), %rax
	movlhps	%xmm1, %xmm0
	movq	%rax, 40(%rsp)
	leaq	96(%rbx), %rax
	movq	%rax, 56(%rsp)
	movq	%rax, 80(%rbx)
	leaq	128(%rbx), %rax
	movups	%xmm0, 60(%rbx)
	movss	4(%r12), %xmm0
	movb	$0, 48(%rbx)
	movb	$0, 56(%rbx)
	movq	$0, 88(%rbx)
	movb	$0, 96(%rbx)
	movq	%rax, 112(%rbx)
	movq	$0, 120(%rbx)
	movb	$0, 128(%rbx)
	movss	%xmm0, 76(%rbx)
	movq	%rax, 48(%rsp)
.LEHB17:
	call	_ZN7TextureaSERKS_@PLT
	movq	120(%rbx), %rdx
	movq	8(%rsp), %r8
	xorl	%esi, %esi
	movq	%r14, %rdi
	movq	16(%rsp), %rcx
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm.isra.0
	movq	88(%rbx), %rdx
	movq	24(%rsp), %r8
	xorl	%esi, %esi
	movq	32(%rsp), %rcx
	movq	40(%rsp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm.isra.0
.LEHE17:
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
.L441:
	.cfi_restore_state
	endbr64
	movq	%rax, %rdi
	jmp	.L428
.L437:
	endbr64
	movq	%rax, %rbp
	jmp	.L434
.L439:
	endbr64
	movq	%rax, %rdi
	jmp	.L431
	.section	.gcc_except_table
	.align 4
.LLSDA11967:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATT11967-.LLSDATTD11967
.LLSDATTD11967:
	.byte	0x1
	.uleb128 .LLSDACSE11967-.LLSDACSB11967
.LLSDACSB11967:
	.uleb128 .LEHB15-.LFB11967
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L441-.LFB11967
	.uleb128 0x1
	.uleb128 .LEHB16-.LFB11967
	.uleb128 .LEHE16-.LEHB16
	.uleb128 .L439-.LFB11967
	.uleb128 0x1
	.uleb128 .LEHB17-.LFB11967
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L437-.LFB11967
	.uleb128 0
.LLSDACSE11967:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATT11967:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC11967
	.type	_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_.cold, @function
_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_.cold:
.LFSB11967:
.L428:
	.cfi_def_cfa_offset 128
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	call	__cxa_begin_catch@PLT
	xorl	%edi, %edi
.LEHB18:
	call	SDL_DestroyTexture@PLT
	call	__cxa_rethrow@PLT
.LEHE18:
.L434:
	movq	112(%rbx), %rdi
	cmpq	%rdi, 48(%rsp)
	je	.L435
	movq	128(%rbx), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L435:
	movq	80(%rbx), %rdi
	cmpq	%rdi, 56(%rsp)
	je	.L436
	movq	96(%rbx), %rsi
	addq	$1, %rsi
	call	_ZdlPvm@PLT
.L436:
	movq	%r13, %rdi
	call	_ZN7TextureD1Ev
	movq	%rbp, %rdi
.LEHB19:
	call	_Unwind_Resume@PLT
.LEHE19:
.L431:
	call	__cxa_begin_catch@PLT
	xorl	%edi, %edi
.LEHB20:
	call	SDL_FreeSurface@PLT
	call	__cxa_rethrow@PLT
.LEHE20:
.L440:
	endbr64
	movq	%rax, %rbp
	call	__cxa_end_catch@PLT
	movq	%rbp, %rdi
.LEHB21:
	call	_Unwind_Resume@PLT
.LEHE21:
.L438:
	endbr64
	movq	%rax, %rbp
	call	__cxa_end_catch@PLT
	movq	16(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L433
	call	_ZNSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE10_M_releaseEv
.L433:
	movq	%rbp, %rdi
.LEHB22:
	call	_Unwind_Resume@PLT
.LEHE22:
	.cfi_endproc
.LFE11967:
	.section	.gcc_except_table
	.align 4
.LLSDAC11967:
	.byte	0xff
	.byte	0x9b
	.uleb128 .LLSDATTC11967-.LLSDATTDC11967
.LLSDATTDC11967:
	.byte	0x1
	.uleb128 .LLSDACSEC11967-.LLSDACSBC11967
.LLSDACSBC11967:
	.uleb128 .LEHB18-.LCOLDB11
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L440-.LCOLDB11
	.uleb128 0
	.uleb128 .LEHB19-.LCOLDB11
	.uleb128 .LEHE19-.LEHB19
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB20-.LCOLDB11
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L438-.LCOLDB11
	.uleb128 0
	.uleb128 .LEHB21-.LCOLDB11
	.uleb128 .LEHE21-.LEHB21
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB22-.LCOLDB11
	.uleb128 .LEHE22-.LEHB22
	.uleb128 0
	.uleb128 0
.LLSDACSEC11967:
	.byte	0x1
	.byte	0
	.align 4
	.long	0

.LLSDATTC11967:
	.section	.text.unlikely
	.text
	.size	_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_, .-_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_
	.section	.text.unlikely
	.size	_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_.cold, .-_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_.cold
.LCOLDE11:
	.text
.LHOTE11:
	.globl	_ZN6EntityC1E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_
	.set	_ZN6EntityC1E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_,_ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.type	_GLOBAL__sub_I__ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_, @function
_GLOBAL__sub_I__ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_:
.LFB13046:
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
.LFE13046:
	.size	_GLOBAL__sub_I__ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_, .-_GLOBAL__sub_I__ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZN6EntityC2E6Point3IfE7Vector2IfE7TextureSt17basic_string_viewIcSt11char_traitsIcEES8_
	.weak	_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 32
	.type	_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE, 47
_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE:
	.string	"St11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE"
	.weak	_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.section	.data.rel.ro._ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,"awG",@progbits,_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 8
	.type	_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE, 16
_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.weak	_ZTSPFvP11SDL_SurfaceE
	.section	.rodata._ZTSPFvP11SDL_SurfaceE,"aG",@progbits,_ZTSPFvP11SDL_SurfaceE,comdat
	.align 16
	.type	_ZTSPFvP11SDL_SurfaceE, @object
	.size	_ZTSPFvP11SDL_SurfaceE, 19
_ZTSPFvP11SDL_SurfaceE:
	.string	"PFvP11SDL_SurfaceE"
	.weak	_ZTSPFvP11SDL_TextureE
	.section	.rodata._ZTSPFvP11SDL_TextureE,"aG",@progbits,_ZTSPFvP11SDL_TextureE,comdat
	.align 16
	.type	_ZTSPFvP11SDL_TextureE, @object
	.size	_ZTSPFvP11SDL_TextureE, 19
_ZTSPFvP11SDL_TextureE:
	.string	"PFvP11SDL_TextureE"
	.weak	_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 32
	.type	_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE, 52
_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE:
	.string	"St16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE"
	.weak	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.section	.data.rel.ro._ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,"awG",@progbits,_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 8
	.type	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE, 24
_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSSt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.quad	_ZTISt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE
	.weak	_ZTS6Entity
	.section	.rodata._ZTS6Entity,"aG",@progbits,_ZTS6Entity,comdat
	.align 8
	.type	_ZTS6Entity, @object
	.size	_ZTS6Entity, 8
_ZTS6Entity:
	.string	"6Entity"
	.weak	_ZTI6Entity
	.section	.data.rel.ro._ZTI6Entity,"awG",@progbits,_ZTI6Entity,comdat
	.align 8
	.type	_ZTI6Entity, @object
	.size	_ZTI6Entity, 16
_ZTI6Entity:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTS6Entity
	.weak	_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 32
	.type	_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE, 80
_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE:
	.string	"St19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE"
	.weak	_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.section	.data.rel.ro._ZTISt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE,"awG",@progbits,_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 8
	.type	_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE, 24
_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.quad	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.weak	_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.section	.rodata._ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE,"aG",@progbits,_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 32
	.type	_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE, 80
_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE:
	.string	"St19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE"
	.weak	_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.section	.data.rel.ro._ZTISt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE,"awG",@progbits,_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 8
	.type	_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE, 24
_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.quad	_ZTISt16_Sp_counted_baseILN9__gnu_cxx12_Lock_policyE2EE
	.weak	_ZTV6Entity
	.section	.data.rel.ro.local._ZTV6Entity,"awG",@progbits,_ZTV6Entity,comdat
	.align 8
	.type	_ZTV6Entity, @object
	.size	_ZTV6Entity, 64
_ZTV6Entity:
	.quad	0
	.quad	_ZTI6Entity
	.quad	_ZN6Entity13on_event_downER6EngineN8EngineIO10InputEventE
	.quad	_ZN6Entity11on_event_upER6EngineN8EngineIO10InputEventE
	.quad	_ZN6Entity11pre_physicsER6Engine
	.quad	_ZN6Entity15update_positionER6Engine
	.quad	_ZN6Entity12on_collisionER6EngineSt10shared_ptrIS_E
	.quad	_ZN6Entity12post_physicsER6Engine
	.weak	_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.section	.data.rel.ro.local._ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE,"awG",@progbits,_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 8
	.type	_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE, 56
_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE:
	.quad	0
	.quad	_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED1Ev
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_TextureESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.weak	_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.section	.data.rel.ro.local._ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE,"awG",@progbits,_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE,comdat
	.align 8
	.type	_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE, @object
	.size	_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE, 56
_ZTVSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE:
	.quad	0
	.quad	_ZTISt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED1Ev
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_disposeEv
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE10_M_destroyEv
	.quad	_ZNSt19_Sp_counted_deleterIDnPFvP11SDL_SurfaceESaIvELN9__gnu_cxx12_Lock_policyE2EE14_M_get_deleterERKSt9type_info
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC3:
	.long	1036831949
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC10:
	.long	1
	.long	1
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

	.file	"lab11.c"
	.text
	.globl	proc
	.type	proc, @function
proc:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movq	%rcx, -48(%rbp)
	movl	%r8d, %edx
	movq	%r9, -56(%rbp)
	movl	16(%rbp), %eax
	movw	%dx, -40(%rbp)
	movb	%al, -60(%rbp)
	movq	24(%rbp), %rax
	movq	%rax, -72(%rbp)
	movq	40(%rbp), %rax
	movq	%rax, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-48(%rbp), %rax
	movl	(%rax), %edx
	movl	-36(%rbp), %eax
	addl	%eax, %edx
	movq	-48(%rbp), %rax
	movl	%edx, (%rax)
	movq	-56(%rbp), %rax
	movzwl	(%rax), %eax
	movl	%eax, %edx
	movzwl	-40(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movq	-56(%rbp), %rax
	movw	%dx, (%rax)
	movq	-72(%rbp), %rax
	movzbl	(%rax), %eax
	movl	%eax, %edx
	movzbl	-60(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movq	-72(%rbp), %rax
	movb	%dl, (%rax)
	cmpq	$1, 32(%rbp)
	jg	.L2
	movq	-80(%rbp), %rax
	movq	$1, (%rax)
	jmp	.L3
.L2:
	movq	32(%rbp), %rax
	leaq	-1(%rax), %r11
	movsbl	-60(%rbp), %edi
	movswl	-40(%rbp), %r10d
	movq	-56(%rbp), %r9
	movq	-48(%rbp), %rcx
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rsi
	movq	-24(%rbp), %rax
	leaq	-16(%rbp), %r8
	pushq	%r8
	pushq	%r11
	pushq	-72(%rbp)
	pushq	%rdi
	movl	%r10d, %r8d
	movq	%rax, %rdi
	call	proc
	addq	$32, %rsp
	movl	-36(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movswl	-40(%rbp), %edx
	movsbl	-60(%rbp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	cltq
	imulq	%rax, %rcx
	movq	%rcx, %rdx
	movq	-80(%rbp), %rax
	movq	%rdx, (%rax)
.L3:
	movq	-80(%rbp), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L5
	call	__stack_chk_fail
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	proc, .-proc
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$1, -32(%rbp)
	movl	$2, -36(%rbp)
	movw	$3, -38(%rbp)
	movb	$4, -39(%rbp)
	movq	$5, -16(%rbp)
	movzbl	-39(%rbp), %eax
	movsbl	%al, %edi
	movzwl	-38(%rbp), %eax
	movswl	%ax, %r10d
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rax
	leaq	-38(%rbp), %r9
	leaq	-36(%rbp), %rcx
	leaq	-32(%rbp), %rsi
	leaq	-24(%rbp), %r8
	pushq	%r8
	pushq	-16(%rbp)
	leaq	-39(%rbp), %r8
	pushq	%r8
	pushq	%rdi
	movl	%r10d, %r8d
	movq	%rax, %rdi
	call	proc
	addq	$32, %rsp
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L8
	call	__stack_chk_fail
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu12) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

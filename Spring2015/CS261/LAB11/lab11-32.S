	.file	"lab11.c"
	.text
	.globl	proc
	.type	proc, @function
proc:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$52, %esp
	.cfi_offset 3, -12
	movl	24(%ebp), %edx
	movl	32(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	%ecx, -28(%ebp)
	movl	20(%ebp), %ecx
	movl	%ecx, -32(%ebp)
	movw	%dx, -36(%ebp)
	movl	28(%ebp), %edx
	movl	%edx, -40(%ebp)
	movb	%al, -44(%ebp)
	movl	36(%ebp), %eax
	movl	%eax, -48(%ebp)
	movl	44(%ebp), %eax
	movl	%eax, -52(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	movl	-28(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-28(%ebp), %eax
	movl	%edx, (%eax)
	movl	-32(%ebp), %eax
	movl	(%eax), %edx
	movl	16(%ebp), %eax
	addl	%eax, %edx
	movl	-32(%ebp), %eax
	movl	%edx, (%eax)
	movl	-40(%ebp), %eax
	movzwl	(%eax), %eax
	movl	%eax, %edx
	movzwl	-36(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	-40(%ebp), %eax
	movw	%dx, (%eax)
	movl	-48(%ebp), %eax
	movzbl	(%eax), %eax
	movl	%eax, %edx
	movzbl	-44(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, %edx
	movl	-48(%ebp), %eax
	movb	%dl, (%eax)
	cmpl	$1, 40(%ebp)
	jg	.L2
	movl	-52(%ebp), %eax
	movl	$1, (%eax)
	jmp	.L3
.L2:
	movl	40(%ebp), %eax
	leal	-1(%eax), %ebx
	movsbl	-44(%ebp), %edx
	movswl	-36(%ebp), %eax
	subl	$8, %esp
	leal	-16(%ebp), %ecx
	pushl	%ecx
	pushl	%ebx
	pushl	-48(%ebp)
	pushl	%edx
	pushl	-40(%ebp)
	pushl	%eax
	pushl	-32(%ebp)
	pushl	16(%ebp)
	pushl	-28(%ebp)
	pushl	8(%ebp)
	call	proc
	addl	$48, %esp
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movswl	-36(%ebp), %edx
	movsbl	-44(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	imull	%eax, %ecx
	movl	%ecx, %edx
	movl	-52(%ebp), %eax
	movl	%edx, (%eax)
.L3:
	movl	-52(%ebp), %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %ebx
	xorl	%gs:20, %ebx
	je	.L5
	call	__stack_chk_fail
.L5:
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	proc, .-proc
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x74,0x6
	.cfi_escape 0x10,0x6,0x2,0x75,0x7c
	.cfi_escape 0x10,0x3,0x2,0x75,0x78
	subl	$44, %esp
	movl	%gs:20, %eax
	movl	%eax, -28(%ebp)
	xorl	%eax, %eax
	movl	$1, -44(%ebp)
	movl	$2, -40(%ebp)
	movw	$3, -46(%ebp)
	movb	$4, -47(%ebp)
	movl	$5, -32(%ebp)
	movzbl	-47(%ebp), %eax
	movsbl	%al, %ebx
	movzwl	-46(%ebp), %eax
	movswl	%ax, %ecx
	movl	-40(%ebp), %edx
	movl	-44(%ebp), %eax
	subl	$8, %esp
	leal	-36(%ebp), %esi
	pushl	%esi
	pushl	-32(%ebp)
	leal	-47(%ebp), %esi
	pushl	%esi
	pushl	%ebx
	leal	-46(%ebp), %ebx
	pushl	%ebx
	pushl	%ecx
	leal	-40(%ebp), %ecx
	pushl	%ecx
	pushl	%edx
	leal	-44(%ebp), %edx
	pushl	%edx
	pushl	%eax
	call	proc
	addl	$48, %esp
	movl	-36(%ebp), %eax
	movl	-28(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L8
	call	__stack_chk_fail
.L8:
	leal	-12(%ebp), %esp
	popl	%ecx
	.cfi_restore 1
	.cfi_def_cfa 1, 0
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%ebp
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu12) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

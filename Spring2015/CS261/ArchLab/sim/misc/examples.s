	.file	"examples.c"
	.text
	.size	sum_list, .-sum_list
	.globl	rsum_list
	.type	rsum_list, @function
rsum_list:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$0, 8(%ebp)
	jne	.L6
	movl	$0, %eax
	jmp	.L7
.L6:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	rsum_list
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	movl	-16(%ebp), %edx
	movl	-12(%ebp), %eax
	addl	%edx, %eax
.L7:
	leave
	ret
	.size	rsum_list, .-rsum_list
	.globl	copy_block
	.type	copy_block, @function
copy_block:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -8(%ebp)
	jmp	.L9
.L10:
	movl	8(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, 8(%ebp)
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, 12(%ebp)
	movl	-4(%ebp), %edx
	movl	%edx, (%eax)
	movl	-4(%ebp), %eax
	xorl	%eax, -8(%ebp)
	subl	$1, 16(%ebp)
.L9:
	cmpl	$0, 16(%ebp)
	jg	.L10
	movl	-8(%ebp), %eax
	leave
	ret
	.size	copy_block, .-copy_block
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu7) 4.9.2"
	.section	.note.GNU-stack,"",@progbits

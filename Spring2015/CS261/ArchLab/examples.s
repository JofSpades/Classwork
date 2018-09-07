		.file	"examples.c"
		.text
.globl sum_list
		.type	sum_list, @function
sum_list:
		pushl	%ebp
		movl	%esp,%ebp
		movl    8(%ebp), %edx
        movl    $0, %eax
        testl   %edx, %edx
        je	.L4
        movl    $0, %eax
.L5:
    	addl    (%edx), %eax
        movl    4(%edx), %edx
        testl   %edx, %edx
        jne     .L5
.L4:
    	popl    %ebp
        ret
		.size   sum_list, .-sum_list
.globl rsum_list
        .type   rsum_list, @function
rsum_list:
		pushl   %ebp
        movl    %esp, %ebp
        pushl   %ebx
        subl    $4, %esp
        movl    8(%ebp), %edx
        movl    $0, %eax
        testl   %edx, %edx
        je	.L11
        movl    (%edx), %ebx
        movl    4(%edx), %eax
        movl	%ezx, (%esp)
        call    rsum_list
        addl    %ebx, %eax
.L11:
     	addl    $4, %esp
        popl    %ebx
        popl    %ebp
        ret
		.size   rsum_list, .-rsum_list
.globl copy_block
        .type   copy_block, @function
copy_block:
		pushl   %ebp
        movl    %esp, %ebp
        pushl   %esi
        pushl   %ebx
        movl    8(%ebp), %ebx
        movl    12(%ebp), %ecx
        movl    16(%ebp), %edx
        movl    $0, %esi
        testl   %edx, %edx
        jle     .L16
        movl    $0, %esi
.L17:
     	movl    (%ebx), %eax
        addl    $4, %ebx
        movl    %eax, (%ecx)
        addl    $4, %ecx
        xorl    %eax, %esi
        subl    $1, %edx
        jne     .L17
.L16:
     	movl    %esi, %eax
        popl    %ebx
        popl    %esi
        popl    %ebp
        ret
	.size   copy_block, .-copy_block
        .ident  "GCC: (GNU) 4.1.2 20080704 (Red Hat 4.1.2-55)"
        .section        .note.GNU-stack,"",@progbits

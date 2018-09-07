_bubble_a:                              ## @bubble_a
## BB#0:
        pushl   %ebp
        rrmovl    %esp, %ebp
        subl    $20, %esp
        irmovl    12(%ebp), %eax
        mrmovl    8(%ebp), %ecx
        rmmovl    %ecx, -4(%ebp)
        rmmovl    %eax, -8(%ebp)
        mrmovl    -8(%ebp), %eax
        subl    $1, %eax
        rmmovl    %eax, -16(%ebp)
LBB0_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_3 Depth 2
        cmpl    $0, -16(%ebp)
        jle     LBB0_10
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
        irmovl    $0, -12(%ebp)
LBB0_3:                                 ##   Parent Loop BB0_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
        mrmovl    -12(%ebp), %eax
        cmpl    -16(%ebp), %eax
        jge     LBB0_8
## BB#4:                                ##   in Loop: Header=BB0_3 Depth=2
        movl    -12(%ebp), %eax
        movl    -4(%ebp), %ecx
        movl    4(%ecx,%eax,4), %eax
        movl    -12(%ebp), %ecx
        movl    -4(%ebp), %edx
        cmpl    (%edx,%ecx,4), %eax
        jle     LBB0_6
## BB#5:                                ##   in Loop: Header=BB0_3 Depth=2
        movl    -12(%ebp), %eax
        movl    -4(%ebp), %ecx
        movl    4(%ecx,%eax,4), %eax
        movl    %eax, -20(%ebp)
        movl    -12(%ebp), %eax
        movl    -4(%ebp), %ecx
        movl    (%ecx,%eax,4), %eax
        movl    -12(%ebp), %ecx
        movl    -4(%ebp), %edx
        movl    %eax, 4(%edx,%ecx,4)
        movl    -20(%ebp), %eax
        movl    -12(%ebp), %ecx
        movl    -4(%ebp), %edx
        movl    %eax, (%edx,%ecx,4)
LBB0_6:                                 ##   in Loop: Header=BB0_3 Depth=2
        jmp     LBB0_7
LBB0_7:                                 ##   in Loop: Header=BB0_3 Depth=2
        mrmovl    -12(%ebp), %eax
        addl    $1, %eax
        rmmovl    %eax, -12(%ebp)
        jmp     LBB0_3
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
        jmp     LBB0_9
LBB0_9:                                 ##   in Loop: Header=BB0_1 Depth=1
        mrmovl    -16(%ebp), %eax
        addl    $4294967295, %eax       ## imm = 0xFFFFFFFF
        rmmovl    %eax, -16(%ebp)
        jmp     LBB0_1
LBB0_10:
        addl    $20, %esp
        popl    %ebp
        retl
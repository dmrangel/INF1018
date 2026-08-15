.text
.globl funcao0
funcao0:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $32, %rsp
    movl    %edi, -24(%rbp)
    
    movl    -24(%rbp), %eax
    movl    -24(%rbp), %ecx
    imull   %ecx, %eax
    movl    %eax, -20(%rbp)
    
    movl    -20(%rbp), %eax
    leave
    ret

.globl funcao1
funcao1:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $32, %rsp
    movl    %edi, -24(%rbp)
    
    movl    -24(%rbp), %eax
    cmpl    $0, %eax
    jne     .L1
    movl    $0, %eax
    leave
    ret
    
.L1:
    movl    -24(%rbp), %eax
    movl    $1, %ecx
    subl    %ecx, %eax
    movl    %eax, -20(%rbp)
    
    movl    -24(%rbp), %eax
    movl    %eax, %edi
    call    funcao0
    movl    %eax, -16(%rbp)
    
    movl    -20(%rbp), %eax
    movl    %eax, %edi
    call    funcao1
    movl    %eax, -12(%rbp)
    
    movl    -16(%rbp), %eax
    movl    -12(%rbp), %ecx
    addl    %ecx, %eax
    movl    %eax, -8(%rbp)
    
    movl    -8(%rbp), %eax
    leave
    ret
    
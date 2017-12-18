	.text
	.globl	_between
_between:
LFB0:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax # move int x into %eax
	cmpl	12(%ebp), %eax # compare int a and the value of %eax (int x)
	jle	L2 # return 0 if x is less than a
	cmpl	16(%ebp), %eax # compare int b and the value of %eax (int b)
	jge	L2 # return 0 if x is greater than b
	movl	$1, %eax #move 1 into % eax
	jmp	L3
L2:
	movl	$0, %eax # move 0 into %eax
L3:
	popl	%ebp
	ret

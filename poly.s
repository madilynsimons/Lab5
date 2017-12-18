	.text
	.globl	_poly
_poly:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax # move int x into %eax
	imull	8(%ebp), %eax # multiply the value in %eax by int x
	imull	12(%ebp), %eax #multiply the value in %eax by int a
	movl	%eax, %edx # move the value in %eax into % edx
	movl	8(%ebp), %eax #move int x into %eax
	imull	16(%ebp), %eax #multiply the value of %eax by int b
	addl	%eax, %edx # add the value of %eax to the value of % edx (a*x*x + b*x)
	movl	20(%ebp), %eax # move int x to % eax
	addl	%edx, %eax # add the value of %edx to the value of %eax
	popl	%ebp
	ret

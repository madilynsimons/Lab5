  .text
  .globl	_dblit
_dblit:
LFB0:
  pushl	%ebp
  movl	%esp, %ebp
  subl	$16, %esp
  movl	$0, -4(%ebp) # move 0 into -4(%ebp), which is the current index of the array
  jmp	L2
L3:
  movl	-4(%ebp), %eax # move the index of the array into % eax
  leal	0(,%eax,4), %edx # move address of 0(,%eax,4) into %edx
  movl	8(%ebp), %eax # move address of element into %eax
  addl	%edx, %eax # add memory address of 0(,%eax,4) to address of element
  movl	-4(%ebp), %edx # move the index of the array into % edx
  leal	0(,%edx,4), %ecx # move address of 0(,%edx,4) into %ecx
  movl	8(%ebp), %edx # move element of array into %edx
  addl	%ecx, %edx # add memory address to %edx
  movl	(%edx), %edx # move the value at the address stored in %edx to %edx
  addl	%edx, %edx # add the value of %edx to itself (aka multiply it by two)
  movl	%edx, (%eax) # move value of edx to address of eax
  addl	$1, -4(%ebp) # traverse to the next element in the array
L2:
  movl	-4(%ebp), %eax # move the index of the array into %eax
  cmpl	12(%ebp), %eax # compare length to index
  jl	L3 # if there are more elements left in the array, return to the loop
  leave
  ret

TITLE Programming Assignment 3    (assignment3.asm)

; Author: Aryan Aziz
; CS271 / Programming Assignment 3                Date: 10/13/14
; Description: Assignment 3

INCLUDE Irvine32.inc

; (insert constant definitions here)


.data


.code
main PROC
   push 3
   push 8
   call rcrsn
   exit
main ENDP

rcrsn PROC
   push ebp
   mov ebp,esp
   mov eax,[ebp + 12]
   mov ebx,[ebp+8]
   cmp eax,ebx
   jl recurse
   jmp quit
recurse:
   inc eax
   push eax
   push ebx
   call rcrsn
   mov eax,[ebp + 12]
   call WriteDec
   ;Space 2
quit:
   pop ebp
   ret 8
rcrsn ENDP

; (insert additional procedures here)

END main

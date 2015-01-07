TITLE Programming Assignment 2    (assignment2.asm)

; Author: Aryan Aziz
; CS271 / Programming Assignment 2                Date: 10/13/14
; Description: Assignment 2

INCLUDE Irvine32.inc

; (insert constant definitions here)
upperLimit = 46

.data
;Inputs
userName            BYTE      33 DUP(0)
numTerms            DWORD     ?

;Data Holders
currentFib          DWORD      ?

;Strings
programIntro        BYTE      "Hello, welcome to [CS271] Programming Assignment 2 (Fibonacci Numbers) - Author: Aryan Aziz",0
userInstruction     BYTE      "Please enter your name: ",0
greeting            BYTE      "Hello, ",0
prompt1             BYTE      "Please the number of Fibonacci terms to be displayed [1-46]: ",0
prompt2             BYTE      "That was not in the range. Please enter a number between 1 and 46: ",0
programExit         BYTE      "Alright, that is it. #late",0
space               BYTE      "   ",0

.code
main PROC
;Introduction
     mov       edx, OFFSET programIntro 
     call      WriteString
     call      CrLf
;userInstructions
     mov       edx, OFFSET userInstruction
     call      WriteString
     mov       edx, OFFSET userName                    ;offset EDX the length of the username
     mov       ecx, 32                                 ;set the max length of the username
     call      ReadString                              ;take it in
;getUserData
     mov       edx, OFFSET greeting
     call      WriteString
     mov       edx, OFFSET userName
     call      WriteString
     call      CrLf
     mov       edx, OFFSET prompt1
     call      WriteString
     call      ReadInt
     mov       numTerms, eax
     whileStart:                                       ;start the while loop
     cmp       eax,upperLimit                          ;compare the number entered to the upperLimit
     jle       exitLoop                                ;if it's less than or equal to, move on
     mov       edx, OFFSET prompt2                     ;else, prompt again and read the int
     call      WriteString
     call      ReadInt
     mov       numTerms, eax
     jmp       whileStart                              ;if it got into the else, jump back to the start of the loop and check if the new number is cool. 
     exitLoop:
;displayFibs
     mov       eax, 1
     mov       ebx, 0
     mov       ecx, numTerms
     .IF       numTerms < 2
     call      WriteDec
     mov       edx, OFFSET space
     call      WriteString
     .ELSE
     call      WriteDec
     mov       edx, OFFSET space
     call      WriteString
     mov       eax, numTerms
     mov       ebx, 1
     sub       eax, ebx
     mov       ecx, eax
     mov       eax, 1
     mov       ebx, 0
     fibLoop:
     mov       currentFib, eax
     mov       eax, ebx
     mov       ebx, currentFib
     add       eax, ebx
     call      WriteDec
     mov       edx, OFFSET space
     call      WriteString
     loop      fibLoop
     .ENDIF
     call      CrLf
;farewell
     mov       edx, OFFSET programExit
     call      WriteString
     call      CrLf
	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main

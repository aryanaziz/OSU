TITLE Programming Assignment 3    (assignment3.asm)

; Author: Aryan Aziz
; CS271 / Programming Assignment 3                Date: 10/13/14
; Description: Assignment 3

INCLUDE Irvine32.inc

; (insert constant definitions here)
upperLimit = 100
lowerLimit = 0

.data
;Inputs
userName            BYTE      33 DUP(0)
sum                 DWORD     0
numEntries          DWORD     0
average             DWORD     ?
remainder           DWORD     ?

;Data Holders

;Strings
programIntro        BYTE      "Hello, welcome to [CS271] Programming Assignment 3 (Number Fun!) - Author: Aryan Aziz",0
userInstruction     BYTE      "Please enter your name: ",0
greeting            BYTE      "Hello, ",0
prompt1             BYTE      "Please enter a number less than or equal to 100: ",0
prompt2             BYTE      "That was not in the range. Please enter a number less than or equal to 100: ",0
numEntriesText      BYTE      "You entered ",0
numbers             BYTE      " numbers.",0
sumText             BYTE      "The sum of your numbers is ",0
AverageText         BYTE      "The rounded average is ",0
programExit         BYTE      "Alright, that is it. Thanks for playing ",0
noNumbersText       BYTE      "Uh oh, you didn't enter any positive integers!",0
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
;greeting
     mov       edx, OFFSET greeting
     call      WriteString
     mov       edx, OFFSET userName
     call      WriteString
     call      CrLf
;UserInputLoop
     TheLoopStart:
     mov       edx, OFFSET prompt1
     call      WriteString
     call      ReadInt
     whileStart:                                       ;make sure the number is less than upper limit
     cmp       eax,upperLimit                          ;compare the number entered to the upperLimit
     jle       whileEnd                                ;if it's less than or equal to, move on
     mov       edx, OFFSET prompt2                     ;else, prompt again and read the int
     call      WriteString
     call      ReadInt
     jmp       whileStart                              ;if it got into the else, jump back to the start of the loop and check if the new number is cool. 
     whileEnd:
     .IF SDWORD PTR eax > 0                            ;if the input is greater than 0
     add       sum,eax
     add       numEntries,1
     .ENDIF
     cmp      eax, 0
     jge      TheLoopStart                             ;If the input is > 0, go back to the start of the whole loop       
     TheLoopEnd:
;Calculate And Display Results
     .IF numEntries < 1                                ;if there is only 1 input
     mov       edx, OFFSET noNumbersText
     call      WriteString
     .ELSE
     mov       edx, 0
     mov       eax, sum
     mov       ebx, numEntries
     idiv      ebx
     shr       ebx,1                                   ;bitshift 1
     .IF       edx >= ebx                              ;compare the divisor to remainder, if it's greater than or equal to half of it
     inc       eax                                     ;round up (automatically would round down)
     .ENDIF
     mov       average, eax
     mov       remainder, edx
     mov       edx, OFFSET numEntriesText
     call      WriteString
     mov       eax, numEntries
     call      WriteDec
     mov       edx, OFFSET numbers
     call      WriteString
     call      CrLf
     mov       edx, OFFSET sumText
     call      WriteString
     mov       eax, sum
     call      Writedec
     call      CrLf
     shr       numEntries,1
     mov       edx, OFFSET averageText
     call      WriteString
     mov       eax, average
     call      Writedec
     .ENDIF
     call      CrLf
;farewell
     mov       edx, OFFSET programExit
     call      WriteString
     mov       edx, OFFSET userName
     call      WriteString
     call      CrLf
	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main

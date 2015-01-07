TITLE Programming Assignment 1    (assignment1.asm)

; Author: Aryan Aziz
; CS271 / Programming Assignment 1                Date: 10/10/14
; Description: Assignment 1

INCLUDE Irvine32.inc

; (insert constant definitions here)

.data

;Inputs
firstNumber         DWORD     ?    ;first integer from user
secondNumber        DWORD     ?    ;second integer from user
remainder           DWORD     ?    ;holding the remainder
result              DWORD     ?    ;holding the result

;Strings
programIntro        BYTE      "Hello, welcome to [CS271] Programming Assignment 1 - Author: Aryan Aziz",0
userInstructions    BYTE      "Enter 2 numbers and I will do some math for you!",0
prompt1             BYTE      "Please enter an integer ",0
prompt2             BYTE      "Please enter another integer ",0
prompt3             BYTE      "That was not less than the first number. Please enter an integer less than the first. ",0
remainderText       BYTE      "remainder ",0
programExit         BYTE      "Alright, that is it. #late",0
space               BYTE      " ",0

.code
main PROC

; Introduce Program
     mov       edx, OFFSET userInstructions       ;place string into edx
     call      WriteString                        ;write it to console
     call      CrLf                               ;new line
; Ask User for First Input
     mov       edx, OFFSET prompt1                ;move the first prompt into place
     call      WriteString                        ;write it to console
     call      ReadInt                            ;grab the input
     mov       firstNumber, eax                   ;set the firstNumber variable
; Ask User for Second Input
     mov       edx, OFFSET prompt2                ;move the second prompt into place
     call      WriteString                        ;write it to console
     call      ReadInt                            ;grab the input
     mov       secondNumber, eax                  ;set the secondNumber variable
     whileStart:                                  ;while loop lable
     cmp       eax,firstNumber                    ;compare the input to the first number
     jl        exitLoop                           ;if it is less than the first, move on to exit loop label
     mov       edx, OFFSET prompt3                ;move the third prompt into place
     call      WriteString                        ;write it to console
     call      ReadInt                            ;grab the input
     mov       secondNumber, eax                  ;set the secondNumber variable
     jmp       whileStart                         ;jump back up to the whileStart label
     exitLoop:                                    ;end of loop
; Calculate Sum
     mov       eax, firstNumber                   ;move the first number into place
     mov       ebx, secondNumber                  ;move the second number into place
     add       eax, ebx                           ;add em up
     mov       result, eax                        ;set the result
     mov       eax, firstNumber                   ;set eax to firstNumber so we can write it to console
     call      WriteDec                           ;write it to console all pretty like
     mov       edx, OFFSET space                  ;add a space
     call      WriteString                        ;write the space to console
     mov       al, 43                             ;set the + symbol
     call      WriteChar                          ;write it to console
     call      WriteString                        ;write the space to console
     mov       eax, secondNumber                  ;set eax to the secondNumber so we can write it to console
     call      WriteDec                           ;write it to console all pretty like
     call      WriteString                        ;write the space to the console
     mov       al, 61                             ;set the = symbol
     call      WriteChar                          ;write it to console
     call      WriteString                        ;write the space to the console
     mov       eax, result                        ;move the result into eax so we can write it to console
     call      WriteDec                           ;write it to the console all pretty like
     call      CrLf                               ;new line
; Calculate Difference
     mov       eax, firstNumber                   ;move the first number into place
     mov       ebx, secondNumber                  ;move the second number into place
     sub       eax, ebx                           ;subtract them
     mov       result, eax                        ;set the result
     mov       eax, firstNumber                   ;set eax to firstNumber so we can write it to console
     call      WriteDec                           ;write it all pretty like
     mov       edx, OFFSET space                  ;put the space into place for writing
     call      WriteString                        ;write the space to the console
     mov       al, 45                             ;set the - symbol
     call      WriteChar                          ;write it to console
     call      WriteString                        ;write the space to the console
     mov       eax, secondNumber                  ;set eax to the secondNumber so we can write it to console
     call      WriteDec                           ;write it to console all pretty like
     call      WriteString                        ;write the space to the console
     mov       al, 61                             ;set the = symbol
     call      WriteChar                          ;write it to console
     call      WriteString                        ;write the space to the console
     mov       eax, result                        ;move the result into place
     call      WriteDec                           ;write it all pretty like
     call      CrLf                               ;new line
; Calculate Product
     mov       eax, firstNumber                   ;move the firstNumber into place
     mov       ebx, secondNumber                  ;move the secondNumber into place
     mul       ebx                                ;multiply them
     mov       result, eax                        ;set the result
     mov       eax, firstNumber                   ;move the firstNumber into place
     call      WriteDec                           ;write it to console
     mov       edx, OFFSET space                  ;move the space string into place
     call      WriteString                        ;write it to console
     mov       al, 120                            ;set the x symbol
     call      WriteChar                          ;write it to console
     call      WriteString                        ;write the space to console
     mov       eax, secondNumber                  ;move the secondNumber into place
     call      WriteDec                           ;write it to console
     call      WriteString                        ;write the space to console
     mov       al, 61                             ;set the = symbol  
     call      WriteChar                          ;write it to console
     call      WriteString                        ;write the space to console
     mov       eax, result                        ;move the result into place
     call      WriteDec                           ;write it to console
     call      CrLf                               ;new line
; Calculate Quotient and Remainder
     mov       edx, 0                             ;make edx = 0
     mov       eax, firstNumber                   ;move firstNumber into place
     mov       ebx, secondNumber                  ;move secondNumber into place
     idiv      ebx                                ;divide them
     mov       remainder, edx                     ;set the remainder
     mov       result, eax                        ;set the result
     mov       eax, firstNumber                   ;move the firstNumber into place
     call      WriteDec                           ;write it to console
     mov       edx, OFFSET space                  ;move the space string into place
     call      WriteString                        ;write it to console
     mov       al, 246                            ;set the divide symbol
     call      WriteChar                          ;write it to console
     call      WriteString                        ;write the space to console
     mov       eax, secondNumber                  ;move the secondNumber into place
     call      WriteDec                           ;write it to console
     call      WriteString                        ;write the space to console.
     mov       al, 61                             ;set the = symbol
     call      WriteChar                          ;write it to console
     call      WriteString                        ;write the space to console
     mov       eax, result                        ;move the result into place
     call      WriteDec                           ;write it to console
     call      WriteString                        ;write the space to console
     mov       edx, OFFSET remainderText          ;move the remainder text into place
     call      WriteString                        ;write it to console
     mov       eax, remainder                     ;move the remainder into place
     call      WriteDec                           ;write it to console
     call      CrLf                               ;new line
; End Program
     mov       edx, OFFSET programExit            ;move the exit text into place
     call      WriteString                        ;write it to console
     call      CrLf                               ;new line for shits and giggles
	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main

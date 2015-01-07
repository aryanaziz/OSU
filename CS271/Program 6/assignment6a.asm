TITLE Programming Assignment 6    (assignment6a.asm)

; Author: Aryan Aziz
; CS271 / Programming Assignment 6a                Date: 12/05/14
; Description: Assignment 6a - Random Numbers and Sorting. 
; Program will ask the user for 10 unsigned integers, then calculate the sum and the average of those. 
;EXTRA CREDIT INCLUDED:
;1. Numbered request lines for the user

INCLUDE Irvine32.inc


; (insert constant definitions here)
arraySize           =    10                                                ;Array Size

;Macros
displayString  MACRO     string                                            ;Based on Lecture 26
     push      edx                                                         ;Save edx register
     mov       edx, OFFSET string
     call      WriteString
     pop       edx                                                         ;Restore edx
ENDM

getString      MACRO     var, string         ;Based on Lecture 26
     push      ecx
     push      edx
     displayString string                    ;Ask the user to enter a string
     mov       edx,OFFSET var                ;place to store it
     mov       ecx,(SIZEOF var) - 1                                        
     call      ReadString
     pop       edx
     pop       ecx
ENDM

.data
;Inputs
array               DWORD     arraySize DUP(?)
input               BYTE      20 DUP(?)
inputLength         DWORD     0
number              DWORD     ?
count               DWORD     0
sum                 DWORD     0

;Strings
programIntro        BYTE      "Hello, welcome to [CS271] Programming Assignment 6a (Macros!) - Author: Aryan Aziz",0
programIntroTwo     BYTE      "You're going to be asked to enter 10 numbers. The number on the left will show you which one you're on.",0
programExitString   BYTE      "Alright, that is it. Thanks for playing ",0
userInstruction     BYTE      ". Enter a number (0-4,294,967,286): ",0
notANum             BYTE      "That's either not a number or not within range. Please try again: ",0
sumString           BYTE      "The sum of your numbers is: ",0
avgString           BYTE      "The average of your numbers is: ",0
comma               BYTE      ", ",0
yourNumbers         BYTE      "You entered the following numbers: ",0

.code
main PROC
     call      Introduction                  ;Introduce program

     mov       ecx, arraySize                ;Counter to get 10 numbers
     GetVars:
     push      OFFSET array                  ;Push the array onto the stack
     push      count                         ;Push the current count onto the stack
     call      ReadVal                       ;Call the ReadVal procedure
     inc       count               
     loop      GetVars
         
     call      CrLf 
     
     displayString yourNumbers          
     push      OFFSET array                  ;push the array onto the stack
     push      arraySize                     ;push the size of the array onto the stack
     call      WriteVal
     
     call CrLf     

     push OFFSET array                       ;Push the array into the stack
     push arraySize                          ;Push the size of the array into the stack
     push sum
     call      calculateSum                  ;Calculate the sum

     push      sum                           ;Push the sum into the stack
     push      arraySize                     ;Push the size of the array into the stack
     call      calculateAverage              ;Calculate the average

     call      CrLf
     call      programExit
     exit
main ENDP

;---------------------------------------------------------
;introduction PROC
 
; Introduces the program to the user
; Receives: Nothing
; Returns: Nothing
;---------------------------------------------------------
introduction PROC
     displayString programIntro
     call      CrLf
     displayString programIntroTwo
     call      CrLf
     ret
introduction ENDP

;---------------------------------------------------------
;ReadVal PROC

; Grabs the number from the user, validates it, converts the string to integers
; Receives:
;    array pushed onto stack
;    count pushed onto stack
; Returns: Nothing
;---------------------------------------------------------
ReadVal PROC
     pushad
     mov       ebp, esp
     top:
     mov       eax, [ebp+36]                 ;set eax to the current counter
     add       eax, 1                        ;add 1 to it, since we start at 0 and end at 9
     call      WriteDec
     getString input, userInstruction
     jmp       validate                      ;go to validate the numbers

     redo:                                   ;if somewhere in validation broke, jump here
     getString input, notANum

     validate:
     mov       inputLength, eax
     mov       ecx, eax
     mov       esi, OFFSET input
     mov       edi, OFFSET number

     counter:                                ;setup a loop to go digit by digit
     lodsb
     cmp       al,48                         ;0 is character 48
     jl        notNum                        ;so if it's less than 48, it's not a number

     cmp       al,57                         ;9 = 57
     jg        notNum                        ;or if it's greater than 57, it's not a number
     loop      counter
     jmp       isNum                         ;if it got out of the loop, it's a number

     notNum:                                 
     jmp       redo                          ;Grab another number

     isNum:
     mov       edx, OFFSET input
     mov       ecx, inputLength
     call      ParseDecimal32                    
     .IF CARRY?                              ;ParseDecimal32 will set the carry flag if it's bigger than allowable size
     jmp       redo                          ;and if it is, go grab another number
     .ENDIF
     mov       edx, [ebp+40]                 ;move into edx the array
     mov       ebx, [ebp+36]                 ;move into ebx the current count
     imul      ebx, 4                        ;multiply the count by size of dword to see where to place it
     mov       [edx+ebx], eax                ;put the value into the array

     endIt:
     popad
     ret       8
ReadVal ENDP

;---------------------------------------------------------
;WriteVal PROC
 
; Displays the array of numbers to the user
; Receives:
;    array pushed onto the stack
;    arraySize pushed onto the stack (to iterate through the array)
; Returns: Nothing
;---------------------------------------------------------
WriteVal PROC
     push      ebp
     mov       ebp, esp
     mov       edi, [ebp+12]
     mov       ecx, [ebp+8]

     theLoop:
     mov       eax, [edi]
     call      WriteDec
     cmp       ecx, 1                        ;if ecx is = to 1, then no comma needed after the number
     je        noComma                       
     displayString comma
     add       edi, 4
     noComma:
     loop      theLoop

     pop       ebp
     ret       8
WriteVal ENDP


;---------------------------------------------------------
;calculateSum PROC
 
; Calculates and displays the sum
; Receives:
;    array pushed onto the stack
;    sum pushed onto the stack (to be modified)
;    arraySize pushed onto the stack (to iterate through the array)
; Returns: Nothing
;---------------------------------------------------------
calculateSum PROC
     push      ebp
     mov       ebp, esp
     mov       edi, [ebp+16]
     mov       ecx, [ebp+12]
     mov       ebx, [ebp+8]

     theLoop:
     mov       eax, [edi]          ;move the number into eax
     add       ebx, eax            ;add eax to the sum
     add       edi, 4              ;move on to the next one
     loop      theLoop
     
     displayString sumString
     mov       eax, ebx
     call      WriteDec
     call      CrLf
     mov       sum, ebx
     pop       ebp
     ret       12
calculateSum ENDP


;---------------------------------------------------------
;calculateAverage PROC
 
; Grabs the sum that was calculated by calculateSum and calculates/displays the average
; Receives:
;    sum pushed onto the stack
;    arraySize pushed onto the stack
; Returns: Nothing
;---------------------------------------------------------
calculateAverage PROC
     push      ebp
     mov       ebp, esp
     mov       eax, [ebp+12]
     mov       ebx, [ebp+8]
     mov       edx, 0              ;setting up division

     idiv      ebx                 ;doing the division

     displayString avgString

     call      WriteDec

     pop ebp
     ret 8
calculateAverage ENDP

;---------------------------------------------------------
;programExit PROC
 
; Says goodbye to the user
; Receives: Nothing
; Returns: Nothing
;---------------------------------------------------------
programExit PROC
     displayString programExitString
     call      CrLf
     ret
programExit ENDP

END main
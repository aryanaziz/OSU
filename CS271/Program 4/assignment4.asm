TITLE Programming Assignment 4    (assignment3.asm)

; Author: Aryan Aziz
; CS271 / Programming Assignment 4                Date: 11/03/14
; Description: Assignment 4

INCLUDE Irvine32.inc

; (insert constant definitions here)
upperLimit = 200
lowerLimit = 1

.data
;Inputs
numPrimesInput      DWORD     ?
primeBool           BYTE      0
currentNumber       DWORD     ?
remainder           DWORD     ?
ecxHolder           DWORD     ?
eaxHolder           DWORD     ?

;Strings
programIntro        BYTE      "Hello, welcome to [CS271] Programming Assignment 3 (Number Fun!) - Author: Aryan Aziz",0
programExit         BYTE      "Alright, that is it. Thanks for playing ",0
userInstruction     BYTE      "Enter the number of primes to display (1-200): ",0
outOfRange          BYTE      "That's not within the range. Please try again",0
tripleSpace         BYTE      "   ",0

.code
main PROC
     call      introduction
     call      getUserData
     call      showPrimes
     call      farewell
	exit	; exit to operating system
main ENDP

introduction PROC
     mov       edx, OFFSET programIntro 
     call      WriteString
     call      CrLf
     ret
introduction ENDP

getUserData PROC
     mov       edx, OFFSET userInstruction
     call      WriteString
     call      ReadInt
     call      validate
     ret
getUserData ENDP

validate PROC
     .IF eax > upperLimit
     mov       edx, OFFSET outOfRange
     call      WriteString
     call      CrLf
     call      getUserData
     .ENDIF
     .IF eax < lowerLimit
     mov       edx, OFFSET outOfRange
     call      WriteString
     call      CrLf
     call      getUserData
     .ENDIF
     ret
validate ENDP

showPrimes PROC
     mov       numPrimesInput, eax           ;Now that we are done validating, store the number we wanna get. 
     mov       ecx, numPrimesInput           ;Set the beginning of the loop
     TheLoop:
     .IF numPrimesInput == ecx
     mov       eax, 2                        ;Write the first prime number
     call      WriteDec
     mov       edx, OFFSET tripleSpace
     call      WriteString
     dec       ecx                           ;remove 1 since we wrote the first prime number
     mov       eax, 1                        ;this is where we will start from
     .ENDIF
     CalculatePrimeLoop:
     add       eax, 2
     mov       currentNumber, eax
     mov       ecxHolder, ecx
     call      isPrime
     cmp       primeBool, 1
     jne       CalculatePrimeLoop
     call      WriteDec
     mov       edx, OFFSET tripleSpace
     call      Writestring
     loop TheLoop
     call      CrLf
     ret
showPrimes ENDP

isPrime PROC
     mov       eaxHolder, eax
     mov       ecxHolder, ecx

     mov       ebx, eax
     cmp       ebx, 2
     je        PrimeNum
     cmp       ebx, 3
     je        PrimeNum

     mov       ecx, 2
     mov       edx, 0
     div       ecx
     mov       ecx, eax

     IsPrimeLoop:
     mov       eax, ebx
     cmp       ecx, 1
     je        PrimeNum
     mov       edx, 0
     div       ecx
     cmp       edx, 0
     je        NotPrimeNum
     loop IsPrimeLoop
     jmp       PrimeNum

     PrimeNum:
     mov       primeBool, 1
     mov       eax, eaxHolder
     mov       ecx, ecxHolder
     ret

     NotPrimeNum:
     mov       primeBool, 0
     mov       eax, eaxHolder
     mov       ecx, ecxHolder
     ret
isPrime ENDP

farewell PROC
     mov       edx, OFFSET programExit 
     call      WriteString
     call      CrLf
     ret
farewell ENDP

END main

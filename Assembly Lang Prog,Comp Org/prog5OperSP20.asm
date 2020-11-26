
;  Comment block below must be filled out completely for each assignment
;  ************************************************************* 
;  Student Name: Raphael Bret-Mounet
;  COMSC-260 Spring 2020
;  Date: 3/30/2020
;  Assignment # 5
;  Version of Visual Studio used (2015)(2017)(2019): 2019 
;  Did program compile? Yes
;  Did program produce correct results? Yes
;  Is code formatted correctly including indentation, spacing and vertical alignment? Yes
;  Is every line of code commented? Yes
;
;  Estimate of time in hours to complete assignment: 6 hours
;
;  In a few words describe the main challenge in writing this program: Indexing through the dword array.
;  
;  Short description of what program does: The program takes in 2 arrrays of signed/unsigned numbers stored in dwords and performs a series of oppertions;multiplication,addition,subtraction,and division. The program
;  also detecs overflow for negative,positive,and multiplication. Each operation is then displayed with the answer
;  
;
;
;  *************************************************************
;  Reminder: each assignment should be the result of your
;  individual effort with no collaboration with other students.
;
;  Reminder: every line of code must be commented and formatted  
;  per the ProgramExpectations.pdf file on the class web site


.386      ;identifies minimum CPU for this program

.MODEL flat,stdcall    ;flat - protected mode program
                       ;stdcall - enables calling of MS_windows programs

;allocate memory for stack
;(default stack size for 32 bit implementation is 1MB without .STACK directive 
;  - default works for most situations)

.STACK 4096            ;allocate 4096 bytes (1000h) for stack


;*******************MACROS********************************

;mPrtStr
;usage: mPrtStr nameOfString
;ie to display a 0 terminated string named message say:
;mPrtStr message

;Macro definition of mPrtStr. Wherever mPrtStr appears in the code
;it will  be replaced with 

mPrtStr  MACRO  arg1    ;arg1 is replaced by the name of string to be displayed
         push edx
         mov edx, offset arg1    ;address of str to display should be in dx
         call WriteString        ;display 0 terminated string
         pop edx
ENDM

mPrtChar  MACRO  arg1    ;arg1 is replaced by the name of character to be displayed
         push eax        ;save eax
         mov al, arg1    ;character to display should be in al
         call WriteChar  ;display character in al
         pop eax         ;restore eax
ENDM

;*************************PROTOTYPES*****************************

ExitProcess PROTO,
    dwExitCode:DWORD    ;from Win32 api not Irvine to exit to dos with exit code


WriteDec PROTO          ;Irvine code to write number stored in eax
                        ;to console in decimal
ReadDec  PROTO

ReadChar PROTO          ;Irvine code for getting a single char from keyboard
				        ;Character is stored in the al register.
			            ;Can be used to pause program execution until key is hit.

WriteChar PROTO         ;write the character in al to the console

WriteString PROTO		;Irvine code to write null-terminated string to output
                        ;EDX points to string

                     
;************************  Constants  ***************************

    LF         equ     0Ah               ; ASCII Line Feed
    $parm1     EQU DWORD PTR [ebp + 8]   ;parameter 1
    $parm2     EQU DWORD PTR [ebp + 12]  ;parameter 2
    
;************************DATA SEGMENT***************************

.data

operand1 dword   -2147483600,-2147483648,-2147482612,-5, -2147483648,1062741823,2147483647,2147483547, 0, -94567 ,4352687,-2147483648,-249346713,-678, -2147483643,32125, -2147483648, -2147483648,2147483647
operators byte    '-','-', '+','*','*', '*', '+', '%', '/',  '/', '+', '-','/', '%','-','*','/', '+','-'
operand2 dword    -200,545,12, 2, -8, 2, 10, -5635, 543,   383, 19786, 150,43981, 115,5,31185,365587,-10,-10
ARRAY_SIZE EQU   ($ - operand2)

;The ARRAY_SIZE constant should be defined immediately after the operand2 array otherwise the value contained in it will not be correct.

;Use the following messages if overflow is detected.
;Do not change the messages between the quotes.

equal    byte    " = ",0                                      ;used to display equal
titlemsg byte    "Program 5 by Raphael Bret-Mounet",LF,LF,0   ;used to display title of program
posOF    byte    "+Error: Positive Overflow+",LF,0            ;used to indicated whne their is positive overflow
negOF    byte    "-Error: Negative Overflow-",LF,0            ;used to indicated whne their is negative overflow
multOF   byte    "*Multiplication Overflow*",LF,0             ;used to indicated whne their is multipication overflow

;************************CODE SEGMENT****************************

.code

main PROC
    mPrtStr titlemsg                ;prints title message

    mov     esi  ,0                 ;sets esi counter to 0 for operators
    mov     ecx  ,0                 ;sets ecx counter to 0 for operands
    
loopTop:
    cmp     ecx, ARRAY_SIZE         ;compare ecx to the total bytes of the array
    jae     done                    ;if we have processed all bytes then done

    push    [ecx + operand2]        ;pushes 1 element from operand2 array to stack
    push    [ecx + operand1]        ;pushes 1 element from operand1 array to stack

    mov     eax, [ecx + operand1]   ;moves  1 element from operand1 array to eax
    call    DspDword                ;displays Dword in eax

    mPrtChar   ' '
    mPrtChar  operators[esi] 
    mPrtChar   ' '
   
    mov     eax, [ecx + operand2]   ;moves  1 element from operand1 array to eax
    call    DspDword                ;displays Dword in eax            

    movzx   eax,operators[esi]      ;stores 1 element from operators array to eax

    cmp     eax,'-'                 ;checks to see if it is a subtraction operation
    je      subtract                ;if true then go to subtract

    cmp     eax,'+'                 ;checks to see if it is a addition operation
    je      addition                ;if true then go to subtract

    cmp     eax,'*'                 ;checks to see if it is a multiplication operation
    je      multi                   ;if true then go to subtract

    call doDiv                      ;if none are true then do division

    mPrtChar equal                  ;prints out =
    call DspDword                   ;displays Dword in eax 
    mPrtChar LF                     ;prints new line

    inc     esi                     ;esi   contains the offset from the beginning of the array. 
                                    ;add 1 to esi   so that testArray + esi   points to the 
                                    ;next element of the byte array 

    add     ecx,4                   ;increments ecx to next element.

    jmp     loopTop                 ;repeat
        
  subtract:
    call doSub                      ;do subtraction

    cmp eax,-1                      ;checks to see if returned -1
    je  continue                    ;if true then jump to continue

    mPrtStr equal                   ;prints out =
    call DspDword                   ;displays Dword in eax 
    mPrtChar LF                     ;prints new line

    inc     esi                     ;esi   contains the offset from the beginning of the array. 
                                    ;add 1 to esi   so that testArray + esi   points to the 
                                    ;next element of the byte array

    add     ecx,4                   ;increments ecx to next element.

    jmp     loopTop                 ;repeat

  addition:
    call doAdd                      ;calls addition function

    cmp eax,-1                      ;checks to see if function returns -1
    je  continue                    ;if true jump to continue

    mPrtStr equal                   ;prints out =
    call DspDword                   ;displays Dword in eax 
    mPrtChar LF                     ;prints new line

    inc     esi                     ;esi   contains the offset from the beginning of the array. 
                                    ;add 1 to esi   so that testArray + esi   points to the 
                                    ;next element of the byte array 

    add     ecx,4                   ;increments ecx to next element.

    jmp     loopTop                 ;repeat
 

  multi:
    call doMult                     ;calls the multiplication function

    cmp eax,-1                      ;checks to see if function returns -1 
    je  continue                    ;if true jump to continue

    mPrtStr equal                   ;prints out =
    call DspDword                   ;displays Dword in eax 
    mPrtChar LF                     ;prints new line

    inc     esi                     ;esi   contains the offset from the beginning of the array. 
                                    ;add 1 to esi   so that testArray + esi   points to the 
                                    ;next element of the byte array 

    add     ecx,4                   ;increments ecx to next element.

    jmp     loopTop                 ;repeat

  continue:
    inc     esi                     ;esi   contains the offset from the beginning of the array. 
                                    ;add 1 to esi   so that testArray + esi   points to the 
                                    ;next element of the byte array 

    add     ecx,4                   ;increments ecx to next element.

    jmp     loopTop                 ;repeat

done:
    call    ReadChar                ;pauses the program until user hits any key
    INVOKE  ExitProcess,0           ;exit to dos: like C++ exit(0)
main ENDP

doSub PROC
;************** doSub - dword subtraction
;
; ENTRY - operand 1 and operand 2 are pushed on the stack
;
; EXIT -EAX = result (operand 1 - operand 2)
; REGS - List registers changed in this function
;
; note: Before calling doSub push operand 2 onto the stack and then push operand 1.
;
; to call doSub in main function:
; push 2 ;32 bit operand2
; push 10 ;32 bit operand1
; call doSub ;10 – 2 = 8 (answer in eax)
;
; Remove parameters by using ret 8 rather than just ret at the end of this function
;--------------

   push	   ebp	                ;Save original value of EBP on stack
   mov	   ebp,esp	            ;EBP= address of original EBP on stack (00f8)
			                    ; Aim at a fixed location on the stack so
			                    ;   we can access other stack locations
                                ;   relative to this location!   
   mov     eax, $parm1          ;takes parameter 1 from stack and stores in eax
   sub     eax, $parm2          ;subtracts parameter 2 from eax
  
   jo   overflow                ;checks for overflow
   pop  ebp                     ;if no overflow the return ebp to original offset
   ret 8                        ;returns to main
overflow:
   or   eax,eax                 ;checks to see if eax is negative

   js   PositiveOF              ;if negative then jump to positive overflow
    
   mPrtStr equal                ;pints out =
   mPrtStr negOF                ;prints of negative overflow error
   mov eax,-1                   ;returns -1 to skip over DspDWORD
   pop ebp                      ;returns ebp to original offset
   ret 8                        ;returns to main

PositiveOF: 
   mPrtStr equal                ;prints out =  
   mPrtStr posOF                ;prints out positive overflow message
   mov eax,-1                   ;returns -1 to skip over DspDWORD
   pop ebp                      ;returns ebp to original offset 
   ret 8                        ;returns to main

doSub ENDP

doAdd PROC
;************** doAdd - dword addition
;
; ENTRY – operand 1 and operand 2 are on the stack
;
; EXIT - EAX = result (operand 1 + operand 2) (any carry is ignored so the answer must fit in 32 bits)
; REGS - List registers changed in this function
;
; note: Before calling doAdd push operand 2 onto the stack and then push operand 1.
;
;
; to call doAdd in main function:
; push 9 ;32 bit operand2
; push 1 ;32 bit operand1
; call doAdd ;1 + 9 = 10 (answer in eax)
;
; Remove parameters by using ret 8 rather than just ret at the end of this function
;   
;--------------
   push    ebp	                ;Save original value of EBP on stack
   mov	   ebp,esp	            ;EBP= address of original EBP on stack (00f8)
			                    ; Aim at a fixed location on the stack so
			                    ;   we can access other stack locations
                                ;   relative to this location!   
   mov     eax, $parm1          ;takes parameter 1 from stack and stores in eax
   add     eax, $parm2          ;adds parameter 2 from stack to eax.

   jo      overflow             ;checks to see if eax is negative
   pop     ebp                  ;if no overflow the return ebp to original offset 
   ret 8                        ;returns to main
overflow:
   or      eax,eax              ;checks to see if eax is negative

   js  PositiveOF               ;if negative jump to positive overflow
    
   mPrtStr equal                ;prints out =
   mPrtStr negOF                ;prints out negative overflow message
   mov eax,-1                   ;changes eax to -1 so it skips over DspDword
   pop ebp                      ;returns ebp to original offset
   ret 8                        ;returns to main

PositiveOF:
    mPrtStr equal               ;prints out =
    mPrtStr posOF               ;prints out positive overflow
    mov eax,-1                  ;changes eax to -1 so it skips over DspDword
    pop ebp                     ;returns ebp to original offset
    ret 8                       ;returns to main

doAdd ENDP

doMult PROC
;************** doMult - signed dword multiplication
;
; ENTRY - operand 1 and operand 2 are on the stack
;
; EXIT - EDX:EAX = result (operand 1 * operand 2)
; (for this assignment the product is assumed to fit in EAX and EDX is ignored)
;
; REGS - List registers changed in this function
;
; note: Before calling doMult push operand 2 onto the stack and then push operand 1.
;
; to call doMult in main function:
; push 2 ;32 bit operand2
; push 6 ;32 bit operand1
; call doMult ; 6 * 2 = 12 (answer in eax)
;
; Remove parameters by using ret 8 rather than just ret at the end of this function
;--------------
   push	ebp	                    ;Save original value of EBP on stack
   mov	ebp,esp	                ;EBP= address of original EBP on stack (00f8)
			                    ; Aim at a fixed location on the stack so
			                    ;   we can access other stack locations
                                ;   relative to this location!   
   mov     eax, $parm1          ;stores parameter 1 from stack into eax

   imul $parm2                  ;eax=parm1 * parm2 
   
  
   jo  overflow                 ;if overflow then jump to overflow

   pop ebp                      ;returns ebp back to offset before function call
   ret 8                        ;returns to main
overflow:
   mPrtStr equal                ;prints out =
   mPrtStr multOF               ;prints out multiplication overflow message

   mov eax,-1                   ;eax = -1 

   pop ebp                      ;returns ebp back to offset before function call

   ret 8                        ;returns to main
doMult ENDP

doDiv PROC
;************** doDiv - signed dword / dword division
;
; ENTRY - operand 1(dividend) and operand 2(divisor) are on the stack
;
; EXIT - EAX = quotient
; EDX = remainder
; REGS - List registers changed in this function
;
; note: Before calling doDiv push operand 2(divisor) onto the stack and then push operand 1(dividend).
;
; to call doDiv in main function:
; push 4 ;32 bit operand2 (Divisor)
; push 19 ;32 bit operand1 (Dividend)
; call doDiv ;19/ 4 = 4 R3(4 = quotient in eax, 3 = remainder in edx )
;
; Remove parameters by using ret 8 rather than just ret at the end of this function
;--------------

    push	ebp	                ;Save original value of EBP on stack
	mov	    ebp,esp	            ;EBP= address of original EBP on stack (00f8)
			                    ; Aim at a fixed location on the stack so
			                    ;   we can access other stack locations
                                ;   relative to this location!   
    mov     eax, $parm1         ;eax = param1
    cdq                         ;converts eax to qword
    idiv    $parm2              ;eax = param1/param2

    pop     ebp                 ;returns ebp back to offset before function call
    ret 8                       ;returns to mains

doDiv ENDP

DspDword proc
    push     ebp                 ;save ebp to stack
    mov      ebp,esp             ;save stack pointer
    sub      esp,12              ;allocate 12 bytes for byte array
                                 ;note: must be an increment of 4
                                 ;otherwise WriteChar will  not work
    push     edi                 ;save edi to stack
    push     ecx                 ;save ecx to stack
    push     edx                 ;save edx to stack
    push     eax                 ;save eax to stack

    mov      edi,-1              ;edi = offset of beginning of byte array from ebp 
    mov 	 ecx,10              ;ecx = divisor for peeling off decimal digits

    or       eax,eax             ;checks to see if eax is a negative
    js       negative            ;if negative then jump to negative
    jns      next_digit          ;if positive thne jump to next_digit
negative:                   
    mPrtChar '-'                 ;prints out minus for the negative number
    neg      eax                 ;does two's complement on eax

next_digit:
    mov      edx,0               ; before edx:eax / 10, set edx to 0 
    div      ecx                 ; eax = quotient = dividend shifted right
                                 ; edx = remainder = digit to print.
                                 ; next time through loop quotient becomes
                                 ; new dividend.
    add      dl,'0'              ; convert digit to ascii character: i.e. 1 becomes '1'
    mov      [ebp+edi],dl        ; Save converted digit to buffer on stack
    dec      edi                 ; Move down in stack to next digit position
    cmp      edi, -10            ; only process 10 digits
    jge      next_digit          ; repeat until 10 digits on stack
                                 ; since working with a signed number, use jge not jae

    inc      edi                 ; when above loop ends we have gone 1 byte too far
                                 ; so back up one byte

;loop to display all digits stored in byte array on stack
DISPLAY_NEXT_DIGIT:      
    cmp      edi,-1              ; are we done processing digits?
    jg       DONE10              ; repeat loop as long as edi <= -1
    mPrtChar byte ptr[ebp+edi]   ; print digit
    inc      edi                 ; edi = edi + 1: if edi = -10 then edi + 1 = -9
    jmp      DISPLAY_NEXT_DIGIT  ; repeat
DONE10:
    
    pop      eax                 ; eax restored to original value
    pop      edx                 ; edx restored to original value
    pop      ecx                 ; ecx restored to original value
    pop      edi                 ; edi restored to original value

    mov      esp,ebp             ;restore stack pointer which removes local byte array
    pop      ebp                 ;restore ebp to original value
    ret
DspDword endp
END main
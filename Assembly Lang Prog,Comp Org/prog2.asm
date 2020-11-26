;  Comment block below must be filled out completely for each assignment
;  ************************************************************* 
;  Student Name: Raphael Bret-Mounet
;  COMSC-260 Fall 2019
;  Date: 2/19/2020
;  Assignment # 2
;  Version of Visual Studio used (2015)(2017)(2019): 2019 
;  Did program compile? Yes
;  Did program produce correct results? Yes
;  Is code formatted correctly including indentation, spacing and vertical alignment? Yes
;  Is every line of code commented? Yes
;
;  Estimate of time in hours to complete assignment: 2 hours
;
;  In a few words describe the main challenge in writing this program: Using only the required amount of lines/making it efficient.
;  
;  Short description of what program does: This program takes the following equation num1+num2/num3*(num4-num5)%num6 – num7 and prints out the hex values
;  of each variable in the same order and then completes the equation using the assigned hex values and gives a result in hex.
;
;
;  *************************************************************
;  Reminder: each assignment should be the result of your
;  individual effort with no collaboration with other students.
;
;  Reminder: every line of code must be commented and formatted  
;  per the ProgramExpectations.pdf file on the class web site
; *************************************************************



.386      ;identifies minimum CPU for this program

.MODEL flat,stdcall    ;flat - protected mode program
                       ;stdcall - enables calling of MS_windows programs

;allocate memory for stack
;(default stack size for 32 bit implementation is 1MB without .STACK directive 
;  - default works for most situations)

.STACK 4096            ;allocate 4096 bytes (1000h) for stack

;*************************PROTOTYPES*****************************

ExitProcess PROTO,dwExitCode:DWORD ;from Win32 api not Irvine

ReadChar PROTO                     ;Irvine code for getting a single char from keyboard
				                   ;Character is stored in the al register.
			                       ;Can be used to pause program execution until key is hit.
WriteChar PROTO

WriteHex PROTO                     ;Irvine function to write a hex number in EAX to the console

WriteString PROTO                  ;Write null-terminated string to console in EDX
;************************  Constants  ***************************

    LF       equ     0Ah           ; ASCII Line Feed

;************************DATA SEGMENT***************************

.data

   openingMsg byte    "Program 2 by Raphael Bret-Mounet",LF,LF,0 ;openingMsg = "Program 2 by Raphael Bret-Mounet" + newline
   endMsg     byte    "Hit any key to exit!",0                   ;endMsg = "Hit any key to exit!" + newline
   plus       byte    "h+",0
   multi      byte    "h*(",0
   division   byte    "h/",0
   minus      byte    "h-",0
   cParenth   byte    "h)%",0
   equal      byte    "h=",0
   endSpacing byte    "h",LF,LF,0

   num1       DWORD   0CB7FB84h                                  ;num1 = 0CB7FB84h
   num2       DWORD   0F56A2C5h                                  ;num2 = 0F56A2C5h 
   num3       DWORD   0ADC154h                                   ;num3 = 0ADC154h   
   num4       DWORD   0C7A25A9h                                  ;num4 = 0C7A25A9h
   num5       DWORD   0B461ACBh                                  ;num5 = 0B461ACBh
   num6       DWORD   0D3494h                                    ;num6 = 0D3494h
   num7       DWORD   1514ABCh                                   ;num7 = 1514ABCh

;************************CODE SEGMENT****************************

.code

main PROC

    ;Prints "Progam 2 by Raphael Bret-Mounet":
    mov		edx, offset openingMsg      ;edx = address of zero termined string
    call	WriteString                 ;Displays contents of edx to console.
  
    ;Prints out num1h+
    mov     eax,num1                    ;Copies hex value of num1 into eax
    call    WriteHex                    ;Print number in eax to the console in hex
    mov		edx, offset plus		    ;Copies plus into edx
	call	WriteString			        ;Prints edx to console

    ;Prints out num2h/
    mov     eax, num2                   ;Copies hex value of num2 into eax
    call    WriteHex                    ;Print number in eax to the console in hex
    mov		edx, offset division		;Copies division into edx
	call	WriteString			        ;Prints edx to console

    ;Prints out num3h*(
    mov     eax, num3                   ;Copies hex value of num3 into eax
    call    WriteHex                    ;Prints eax to console
    mov		edx, offset multi		    ;Copies multi into edx
	call	WriteString			        ;Prints edx to console

    ;Prints out num4h-
    mov     eax, num4                   ;Copies hex value of num4 into eax
    call    WriteHex                    ;Prints eax to console
    mov		edx, offset minus		    ;Copies minus into edx
	call	WriteString			        ;Prints edx to console

    ;Prints out num5h)%
    mov     eax, num5                   ;Copies hex value of num5 into eax
    call    WriteHex                    ;Prints eax to console
    mov	    edx, offset cParenth	    ;Copies cParenth into edx
	call	WriteString			        ;Prints edx to console

    ;Prints out num6h-
    mov     eax, num6                   ;Copies hex value of num6 into eax
    call    WriteHex                    ;Prints eax to console
    mov	    edx, offset minus		    ;Copies minsut into edx
	call	WriteString			        ;Prints edx to console

    ;Prints out num7
    mov     eax, num7                    ;Copies hex value of num7 into eax
    call    WriteHex                     ;Prints eax to console

    ;num1+num2/num3*(num4-num5)%num6 – num7 (Total Process):

    ;num4-num5:

    mov     ebx, num4                   ;coppies num4 into ebx
    sub     ebx, num5                   ;num4-num5

    ;num2/num3:
    
    mov     eax, num2                   ;Copies num2 into eax
    mov     edx, 0                      ;Sets edx to 0
    div     num3                        ;eax/num3

    ;num2/num3*(num4-num5):

    mul     ebx                         ;eax*ebx

    ;num2/num3*(num4-num5)%num6:
    mov     ebx, num6                   ;copies num6 into ebx
    div     ebx                         ;eax/ebx

    ;num1+num2/num3*(num4-num5)%num6:

    mov     eax,num1                    ;copies num1 to eax
    add     eax,edx                     ;eax+edx

    ;num1+num2/num3*(num4-num5)%num6 – num7: 

    sub     eax,num7                    ;edx-num7
    
    ;Prints out result of the equation:
    mov	    edx, offset equal		    ;copies equal to edx
	call	WriteString			        ;Prints edx to console
    call    WriteHex                    ;Prints answer to console

    ;Prints out h plus two newlines
    mov	    edx, offset endSpacing
    call    WriteString


    ;Prints "Hit any key to exit!":
    mov		edx, offset endMsg          ;edx = address of zero termined string
    call	WriteString                 ;Displays contents of edx to console.

    
    call    ReadChar                    ;Pause program execution while user inputs a non-displayed char
	INVOKE	ExitProcess,0               ;exit to dos: like C++ exit(0)

main ENDP
END main
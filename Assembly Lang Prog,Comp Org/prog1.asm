;  Comment block below must be filled out completely for each assignment
;  ************************************************************* 
;  Student Name: Raphael Bret-Mounet
;  COMSC-260 Fall 2019
;  Date: 1/29/2020
;  Assignment # 1
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
;  Short description of what program does: eax = edx + cx - num2 + num1 - bl + bh. The program adds the hex value stored in edx to the hex value of
;  cx. Then subtracts the hex stored in num2 from the new total of edx and stores it in edx. Then adds the hex value stored in num1 to the total of
;  edx, subtracts the decimial value storerd in bl from edx. Then adds the binary value stored in bh to edx and finally moves the total of edx into 
;  eax.
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


WriteHex PROTO                     ;Irvine function to write a hex number in EAX to the console


;************************DATA SEGMENT***************************

.data

   Num1    WORD   0FDEBh      ;Num1 = 0FDEBh
   Num2    WORD   321h        ;Num2 = 321h

;************************CODE SEGMENT****************************

.code

main PROC

    ; Assign registries

    mov     ebx, 0BBBBBBBBh   ;ebx = 0BBBBBBBBh
    mov     eax, 0AAAAAAAAh   ;eax = 0AAAAAAAAh
    mov     ecx, 0CCCCCCCCh   ;ecx = 0CCCCCCCCh
    mov     edx, 0F4D8DEE2h   ;edx = 0F4D8DEE2
    mov     bh , 11110101b    ;bh = 11110101b
    mov     bl , 249d         ;bl = 249d
    mov     cx , 0FFA2h       ;cx = 0FFA2h

    ;eax = edx + cx - num2 + num1 - bl + bh (Total Process)

    ;edx = edx + cx

    movzx   ecx, cx           ;copies cx to ecx (16bit to 32bit)
    add     edx, ecx          ;adds ecx to edx (32bit + 32bit)

    ;edx = edx + cx - num2

    movzx   eax, Num2        ;copies Num2 to register (16bit to 32bit)
    sub     edx, eax         ;edx = edx - eax (32bit - 32bit)

    ;edx = edx + cx - num2 + num1

    movzx   eax, Num1        ;copies Num1 to register (16bit to 32bit)
    add     edx, eax         ;adds eax to edx (32bit + 32bit)

    ;edx = edx + cx - num2 + num1 - bl

    movzx   ecx, bl           ;copies bl to ecx (16bit to 32bit)
    sub     edx, ecx          ;edx = edx - ecx (32bit - 32bit)

    ;edx = edx + cx - num2 + num1 - bl + bh

    movzx   ebx, bh           ;copies bh to ebx (16bit to 32bit)
    add     edx, ebx          ;adds ebx  to edx (32bit + 32bit)

    ;eax = edx

    mov     eax, edx          ;moves edx to eax (32bit to 32bit)


    call    WriteHex          ;Print number in eax to the console in hex
    call    ReadChar          ;Pause program execution while user inputs a non-displayed char
	INVOKE	ExitProcess,0     ;exit to dos: like C++ exit(0)

main ENDP
END main
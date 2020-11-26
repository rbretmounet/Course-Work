;  Comment block below must be filled out completely for each assignment
;  ************************************************************* 
;  Student Name: Raphael Bret-Mounet
;  COMSC-260 Fall 2019
;  Date: 2/25/2020
;  Assignment # 3
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
;  Short description of what program does: This program randomly generates a hex value and asks the user to guess that value. If the user guess a value higher
;  than the generated value the user is told that it is too high and must guess again. If the guess is too low then the user is told so and must guess again until
;  the user guesses correctly. When the user guesses the correct value a message box appears and asks the user if they would like to play again. If yes then a new 
;  hex value is generated and the user goes through the same proccess until they guess correctly. If the user selects no then the program is terminated.
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

;************************  Constants  ***************************

LF       equ     0Ah                   ; ASCII Line Feed

;*******************MACROS********************************

;mPrtStr
;usage: mPrtStr nameOfString
;ie to display a 0 terminated string named message say:
;mPrtStr message

;Macro definition of mPrtStr. Wherever mPrtStr appears in the code
;it will  be replaced with 

mPrtStr  MACRO  arg1    ;arg1 is replaced by the name of string to be displayed
		 push edx				;save edx
         mov  edx, offset arg1  ;address of str to display should be in edx
         call WriteString       ;display 0 terminated string
         pop  edx				;restore edx
ENDM

;Wherever "mPrtStr message" appears in the code it will  be replaced with 
;push edx
;mov edx, offset arg1   
;call WriteString       
;pop edx

;arg1 is replaced with message if that is the name of the string passed in.


;*************************PROTOTYPES*****************************

ExitProcess PROTO,
    dwExitCode:DWORD    ;from Win32 api not Irvine

RandomRange PROTO       ; Returns an unsigned pseudo-random 32-bit integer
                        ; in EAX, between 0 and n-1. Input parameter:
                        ; EAX = n.

Randomize   PROTO       ; Re-seeds the random number generator with the current time
                        ; in seconds.

WriteString PROTO	    ; Irvine code to write null-terminated string to output
                        ; EDX points to string
                                          
ReadHex     PROTO       ; Takes user's hex input and stores in eax


;MessageBoxA is a win32 api function (not an Irvine function)
;that displays a dialogue box with a caption, message and buttons

MessageBoxA PROTO,      ;MessageBoxA takes 4 parameters:
  handleOwn:DWORD,      ;1. window owner handle
     msgAdd:DWORD,      ;2. message address (zero terminated string)
 captionAdd:DWORD,      ;3. title address(zero terminated string)
    boxType:DWORD       ;4. which button(s) to display

;************************DATA SEGMENT***************************

.data
   header      byte "Program 3 by Raphael Bret-Mounet", LF, 0                     ;header = "Program 3 by Raphael Bret-Mounet", LF, 0 
   instruction byte LF,"Guess a hex number in the range Ah - Fh.",LF,"Guess: ",0  ;intruction = LF,"Guess a hex number in the range Ah - Fh.",LF,"Guess: ",0
   tooHigh     byte "High! (Guess Lower)",LF,"Guess: ",0                          ;tooHigh = "High! (Guess Lower)",LF,"Guess: ",0  
   tooLow      byte "Low! (Guess Higher)",LF,"Guess: ",0                          ;tooLow = "Low! (Guess Higher)",LF,"Guess: ",0   
   correct     byte "Correct! Play again?", 0                                     ;correct = "Correct! Play again?", 0   

;************************CODE SEGMENT****************************

.code

main PROC

    mPrtStr header             ;prints out the title of project
    call    Randomize          ;seed the random number generator

    ;used to genrate random hex and print out instructions on how to play.
    loop1:
        mPrtStr instruction

        mov  eax,6h            ;range to generate random numbers 0-5
        call RandomRange       ;generate random number in range and stores in eax
                               
        add eax, 10            ;adds 10 to random number to max a hex
        mov edx, eax           ;moves random hex to edx.
        jmp loop2              ;jumps to loop2

    ;used to gather user's guess and comapre with random hex
    loop2: 
        call ReadHex		    ;stores user's guess in eax
        cmp  eax,edx            ;compares user's guess to random hex
        JE   correct2           ;checks to see if eax == edx and if true jumps to correct2
        JA   high2              ;checks to see if eax > edx and if true jumps to high2

        ;if all other conditions dont arent true then display too low 
        mPrtStr tooLow          ;prints out too low message
        jmp  loop2              ;jumps back to loop2

    ;runs when guess is higher than random hex
    high2:
        mPrtStr tooHigh        ;prints out too high message
        jmp loop2              ;jumps to loop2 for new guess

    ;runs when guess is equal to random hex
    correct2:
       invoke  MessageBoxA ,   ;call MessageBoxA Win32 API function
                          0,   ;0 indicates no window owner
               addr correct,   ;address of message to be displayed in middle of msg box
                addr header,   ;caption to be displayed in title bar of msg box
                          4    ;display yes, no buttons in msg box
                               ;(6 returned in eax if user hits yes)
                               ;(7 returned in eax if user hits no)

       cmp     eax,6           ;checks to see if user selected yes
       JE      loop1           ;if so restart the game
       invoke  ExitProcess,0   ;else end the program

   
main ENDP
END main
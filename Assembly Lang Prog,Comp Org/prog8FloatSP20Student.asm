;  Comment block below must be filled out completely for each assignment
;  ************************************************************* 
;  Student Name: Raphael Bret-Mounet
;  COMSC-260 Fall 2019
;  Date: 5/11/2020
;  Assignment # 4
;  Version of Visual Studio used (2015)(2017)(2019): 2019 
;  Did program compile? Yes
;  Did program produce correct results? Yes
;  Is code formatted correctly including indentation, spacing and vertical alignment? Yes
;  Is every line of code commented? Yes
;
;  Estimate of time in hours to complete assignment: 2.5 hours
;
;  In a few words describe the main challenge in writing this program: Not having to jump back for the Y,M,D logic
;  
;  Short description of what program does: The program evaluates a formula for calculating the compound interest on an investment for a certain number of years.
;  Using the formula A = P (1 + r/n)^nt where A = ending balance, P = initial principal, r = annual interest rate as a float 5% = 0.05, 
;  n = number of compounding periods. Compounded yearly = 1, monthly = 12, daily = 365, and t = number of years to compound interest
;
;  *************************************************************
;  Reminder: each assignment should be the result of your
;  individual effort with no collaboration with other students.
;
;  Reminder: every line of code must be commented and formatted  
;  per the ProgramExpectations.pdf file on the class web site

;Due Date: Monday May 11, 11:59pm
;30 points

;You should include kennedyDspFloat.lib and Irvine32.lib in your project
;For examples of using DspFloat see DspFloatExample.asm

;This file should compile and run as is before you start coding.

;**************************************************
; This program will evaluate a formula for calculating the compound interest on an investment for a certain number of years.

      ;formula
      ;A = P (1 + r/n)^nt
      ;where
      ;A = ending balance
      ;P = initial principal
      ;r = annual interest rate as a float 5% = 0.05
      ;n = number of compounding periods. Compounded yearly = 1, monthly = 12, daily = 365
      ;t = number of years to compound interest

      ;order of operations
      ;1. r/n (float/ int: fidiv)
      ;2. step 1 + 1.0 (float addition: fadd)
      ;3. n * t (integer multiplication: mul)
      ;4. step 2 to the step 3 power (call Power function)
      ;5. P * step 4 



.586      ;identifies minimum CPU for this program

.MODEL flat,stdcall             ;flat - protected mode program
                                ;stdcall - enables calling of MS_windows programs

;allocate memory for stack
;(default stack size for 32 bit implementation is 1MB without .STACK directive 
;  - default works for most situations)

.STACK 4096                     ;allocate 4096 bytes (1000h) for stack

;*******************MACROS********************************

;NOTE: Use the macros below to print strings, single chars and decimal numbers
;Do not define any other macros.

;mPrtStr will print a zero terminated string to the console
mPrtStr  MACRO  arg1            ;arg1 is replaced by the name of string to be displayed
         push edx               ;save edx
         mov edx, offset arg1   ;address of str to display should be in dx
         call WriteString       ;display 0 terminated string
         pop edx                ;restore edx
ENDM

;mPrtChar will print a single char to the console
mPrtChar MACRO  arg1            ;arg1 is replaced by char to be displayed
         push eax               ;save eax
         mov  al, arg1          ;al = char to display
         call WriteChar         ;display char to console
         pop  eax               ;restore eax
ENDM

;mPrtDec will print a dec number to the console
mPrtDec  MACRO  arg1            ;arg1 is replaced by the name of string to be displayed
         push eax               ;save eax
         mov  eax, arg1         ;eax = dec num to print
         call WriteDec          ;display dec num to console
         pop  eax               ;restore eax
ENDM



;*************************PROTOTYPES*****************************

ExitProcess PROTO,
    dwExitCode:DWORD    ;from Win32 api not Irvine to exit to dos with exit code

ReadChar PROTO          ;Irvine code for getting a single char from keyboard
				        ;Character is stored in the al register.
			            ;Can be used to pause program execution until key is hit.

WriteDec PROTO          ;Irvine code to write number stored in eax
                        ;to console in decimal

WriteString PROTO		;Irvine code to write null-terminated string to output
                        ;EDX points to string

WriteChar PROTO         ;write the character in al to the console

;To call SetFloatPlaces, SetFieldWidth or DspFloat in your program you must first include
;kennedyDspFloat.lib in your project

SetFloatPlaces PROTO    ;sets the number of places a float should round to while printing 
                        ;The default place is 1.
                        ;populate ecx with the number of places to round a floating point num to
                        ;then call SetFloatPlaces.
                        ;If the places to round to  is 2 then 7.466
                        ;would display as 7.47 after calling DspFloat
                        ;The places to round to does not change unless
                        ;you call SetFloatPlaces again.


DspFloatP PROTO         ;prints a float in st(0) to the console formatted to a field width and rounding places.
                        ;DspFloat pops the floating point stack.


SetFieldWidth PROTO     ;Set the space a float should occupy when printed.
                        ;Populate ecx with the total space you want want a displayed float to occupy.
                        ;Use this to help right justify a displayed float to line up a column of numbers vertically
                        ;The default field width is 0.
                        ;To change the field width from the default call SetFieldWidth before calling DspFloat.

Power PROTO             ;calculate operand^exponent. Populate st(0) with the operand and ecx with the exponent. Exponent must be an integer.
                        ;result is returned in st(0)

TSeparatorOn proto      ;Print a comma to separate thousands when calling DspFloat or DspFloatP. 10,000.00 will print instead of 10000.00.
                        ;To turn on the thousands separator call TSeparatorOn before calling DspFloat.
                        ;The thousands separator will remain on until TSeparatorOff is called.
                        ;The default is no thousands separator.


PrefixOn  proto         ; If prefix is on, a character will be printed in front of the floating point number. 
                        ;The default prefix character is a '$'.  This is useful in conjunction with SetFieldWidth. 
                        ;If the user manually prints a prefix character and the field width is other than zero then 
                        ;spaces will appear between the prefix character and the floating point number. 
                        ;With PrefixOn the prefix character will print in front of the floating point number with 
                        ;no spaces even if the field width is greater than zero.
                        ;
                        ;The default is no prefix.

PrefixOff proto         ;Turn off printing a prefix character.

;************************  Constants  ***************************

    LF       equ     0Ah                   ; ASCII Line Feed


;************************  Structs  ***************************


.data

    ;NOTE: do not change the strings below except to add LFs for line spacing
    ;and to change my name to your name.

    heading         byte   "Program 8 by Raphael Bret-Mounet",LF,LF,0
    heading2        byte   "   PRINCIPAL        RATE    CMP   YEARS   BALANCE",LF,0
    yearly          byte   "     Y      ",0
    monthly         byte   "     M      ",0
    daily           byte   "     D      ",0
    spacing         byte   "        ",0
    hundred         real8  100.00
    increment       real8   1.0
    
    ;the parallel arrays below contain the data for several CDs including 
    ;beginning principal balance, interest rate, compounding periods and number of years the money is invested

    ;For example the data at offset 0 in each array is the data for one CD:
    ;beginning balance 2000.00
    ;interest rate:0.035
    ;compounding periods: 1 (means yearly)
    ;investment period: 3 years

  
    ;;beginning principal balance
    principal real8 2000.00,2000.00,2000.00,5000.00,5000.00,5000.00,7500.00,7500.00,7500.00,10000.00,10000.00,10000.00

    ;interest rate
    rate real8 0.035,0.035,0.035,0.025,0.025,0.025,0.0175,0.0175,0.0175,0.03,0.03,0.03

    ;1 means compounded yearly, 12 means monthly, 365 means daily
    compoundedYlyMlyDly dword 1,12,365,1,12,365,1,12,365,1,12,365

    ;total period of investment in years
    period dword 3,3,3,5,5,5,7,7,7,9,9,9

    TOTAL_SIZE        equ sizeof period                            ;total bytes in period array

;************************CODE SEGMENT****************************

.code

Main PROC

    ;Write a main function that will produce output in the form
    ;given in the sample output at the end of this file.
    ;
    ;NOTE: this program has no user defined functions.
    ;
    ;NOTE: use DspFloatP to print floats
    ;NOTE: use mPrtChar to print single characters like 'M' or 'D'
    ;NOTE: use mPrtStr to print strings
    ;NOTE: use mPrtDec to print decimal numbers
    ;
    ;Program the following:
    ;
    ;Before the loop you need to set the thousands separator on, the place rounding to 2 and the field width to 12.
    ;You only need to do this once since it won't change.
    ;
    ;You should code a while loop similar to the one in program 5 that will keep going until you have 
    ;processed all the data in the principal, rate, compounded and period arrays.
    ;
    ;Note: since you have arrays of different sizes(real8 and dword) you may have to use 2 different counters.
    ;
    ;You should use TOTAL_SIZE as the termination condition for the loop in main.
    ;Note: TOTAL_SIZE is the total bytes in the dword array
    ;
    ;In the loop you should call PrefixOn and PrefixOff as necessary to print the '$'
    ;which should print before the beginning and ending balance but not before the interest rate.
    ;
    ;Each time through the loop you are to evaluate and print the row for one CD in the format
    ;given the the sample output at the end of this file.  
    ;
    ;For example the first row after the column heading should look as follows:
    ;    $2,000.00        3.50%     Y      3    $2,217.44
    ;
    ;In the above $2,000.00 is the beginning principal balance, 3.50% is the interest rate, 'Y' means the interest is compounded yearly,
    ;3 is the number of years for the interest to accumulate and $2,217.44 is the ending balance
    ;
    ;The interest rate is stored as a dec fraction in the rate array. You will have to multiple the rate by 100.00 to get a percent:
    ;for example .05 * 100.00 = 5.00. 
    ;Use the hundred real8 variable for 100.00.
    ;
    ;For the CMP column print 'Y' for yearly if the compounding period is 1, else if the compounding period is 12 print'M' for monthly otherwise print 'D' for daily (compounding period is 365).
    ;To print the 'Y', 'M' or 'D' you should use the yearly, monthly or daily strings.
    ;
    ;You should use the following formula to calculate the ending balance:
    ;
    ;A = P (1 + r/n)^nt
    ;
    ;where
    ;A = ending balance
    ;P = initial principal
    ;r = annual interest rate as a float 5% = 0.05
    ;n = number of compounding periods. Compounded yearly = 1, monthly = 12, daily = 365
    ;t = number of years to compound interest
    ;
    ;You should use the following order of operations
    ;1. r/n (float/ int: fidiv)
    ;2. step 1 + 1.0 (float addition: fadd)(use increment var for 1.0)
    ;3. calculate exponent with n * t (integer multiplication: mul)
    ;4. step 2 to the step 3 exponent (call Power function)(st(0) should already be populated with step 2)(ecx gets exponent from step 3)
    ;5. calculate ending balance P * step 4 
    ;
    ;Floating point instructions Like fadd, fmul, and fidiv can take on many forms
    ;as to where the operands have to be.
    ;
    ;In this program we will be using the ONE OPERAND version of fadd, fmul and fidiv.
    ;which means you should push operand1 onto the floating point stack then execute the floating point math instruction.
    ;(see fadd.asm for an example of pushing data onto the floating point stack)
    ;
    ;for example:
    ;
    ;fld operand1
    ;fadd operand2 ;result in st(0)
    ;
    ;
    ;NOTE: none of the floating point math instructions below pop the stack
    ;
    ;fadd operand2 : st(0) = st(0) + operand2
    ;fmul operand2: st(0) = st(0) * operand2 (float * float)
    ;fidiv operand2: st(0) = st(0) / oprand2 (float/ integer)
    ;
    ;NOTE: use mul (not fmul) for n * t since both are integers
    ;NOTE: use fidiv for r/n since r is a float and n is an integer
    ;(fidiv converts operand2 to a float then does the division)
    ;
    ;After you call any of the above math functions the result should be 
    ;in st(0)
    ;
    ;NOTE: you will be graded partly on efficiency which means do not
    ;repeat code unnecessarily and only jump back up in the code to repeat a loop
    

    call TSeparatorOn                   ;turns on thousand separator

    mov ecx,2                           ;ecx = 2
    call SetFloatPlaces                 ;sets float places to two

    mov ecx,12                          ;ecx = 12 
    call SetFieldWidth                  ;sets field width to 12

    mov ebx, 0                          ;initializes counter
    mov esi, 0                          ;initializes counter
    mPrtStr heading                     ;prints out heading  
    mPrtStr heading2                    ;prints out heading2
loopTop:
    cmp esi, TOTAL_SIZE                 ;checks to see if counter has gotten to the end of array.
    je  done                            ;If true jump to done
    
    fld  [ebx + principal]              ;pushes principal on to float point stack
    call PrefixOn                       ;sets $ 
    call DspFloatP                      ;Prints str(0) and pops off the stack

 
    fld  [ebx + rate]                   ;pushes rate on to float point stack
    fmul hundred                        ;turns it into a percent
    call PrefixOff                      ;removes $
    call DspFloatP                      ;Prints str(0) and pops off the stack
    mPrtChar '%'                        ;prints % at end

    cmp [esi + compoundedYlyMlyDly], 1  ;checks to see if compoundedYlyMlyDly = 1
    je  year                            ;if true jump to year
    cmp [esi + compoundedYlyMlyDly], 12 ;checks to see if compoundedYlyMlyDly = 12
    je  month                           ;if true jump to month

    mPrtStr daily                       ;else print daily string
    jmp calculations                    ;jumps to calculations
year:
    mPrtStr yearly                      ;prints out yearly
    jmp calculations                    ;jumps to calculations
month:
    mPrtStr  monthly                    ;prints out monthly

calculations:
    mPrtDec [esi + period]              ;print out period 

    fld     [ebx + rate]                ;push rate to floating point stack
    fidiv   [esi + compoundedYlyMlyDly] ;str(0) = str(0)/compoundedYlyMlyDly
    
    fadd increment                      ;str(0) = str(0) + increment

    mov eax, [esi + compoundedYlyMlyDly];moves compoundedYlyMlyDly into eax
    mul [esi + period]                  ;eax = eax*period

    mov ecx,eax                         ;moves eax to ecx

    call Power                          ;str(0) = str(0)^ecx

    fmul [ebx + principal]              ;str(0) = str(0)*principal

    call PrefixOn                       ;set $
    call DspFloatP                      ;print out str(0) and pop it off the stack

    add ebx,8                           ;increments ebx by 8
    add esi,4                           ;increments esi by 4

    mPrtChar LF                         ;prints new line
    jmp loopTop                         ;jump back to top of loop

done:
    call    ReadChar                    ;pause execution
	INVOKE  ExitProcess,0               ;exit to dos: like C++ exit(0)

Main ENDP

END Main


;Sample output (Substitute your name for my name)
;Your output should match the 
;output below with a blank line after the title and no more blank lines.
;
;Program 8 by Fred Kennedy
;
   ;PRINCIPAL        RATE    CMP   YEARS   BALANCE
   ;$2,000.00        3.50%     Y      3   $2,217.44
   ;$2,000.00        3.50%     M      3   $2,221.08
   ;$2,000.00        3.50%     D      3   $2,221.41
   ;$5,000.00        2.50%     Y      5   $5,657.04
   ;$5,000.00        2.50%     M      5   $5,665.01
   ;$5,000.00        2.50%     D      5   $5,665.72
   ;$7,500.00        1.75%     Y      7   $8,468.42
   ;$7,500.00        1.75%     M      7   $8,476.64
   ;$7,500.00        1.75%     D      7   $8,477.37
  ;$10,000.00        3.00%     Y      9  $13,047.73
  ;$10,000.00        3.00%     M      9  $13,095.23
  ;$10,000.00        3.00%     D      9  $13,099.50;
  ;
;;NOTE: to print floats you should use the DspFloatP function.
;NOTE: to print decimal numbers you should use the mPrtDec macro.
;NOTE: to print strings you should use the mPrtStr macro
;NOTE: to print single chars you should use the mPrtChar macro
;NOTE the '$' before the beginning and ending balance (PrefixOn)
;NOTE: no '$' before the interest rate (PrefixOff)
;NOTE THE '%' after the interest rate (mPrtChar '%')
;
;Submission
;  Email the instructor the following item as an email attachment:  
;
;  prog8FloatSP20Student.asm (use exact file name)

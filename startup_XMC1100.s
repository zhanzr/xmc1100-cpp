;*********************************************************************************************************************
;* @file     startup_XMC1100.s
;* @brief    CMSIS Core Device Startup File for Infineon XMC1100 Device Series
;* @version  V1.4
;* @date     03 Sep 2015
;*
;* @cond
;*********************************************************************************************************************
;* Copyright (c) 2013-2016, Infineon Technologies AG
;* All rights reserved.                        
;*                                             
;* Redistribution and use in source and binary forms, with or without modification,are permitted provided that the 
;* following conditions are met:   
;*                                                                              
;* Redistributions of source code must retain the above copyright notice, this list of conditions and the following 
;* disclaimer.                        
;* 
;* Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following 
;* disclaimer in the documentation and/or other materials provided with the distribution.                       
;* 
;* Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote 
;* products derived from this software without specific prior written permission.                                           
;*                                                                              
;* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
;* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE  
;* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR  
;* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
;* WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                                  
;*                                                                              
;* To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes with 
;* Infineon Technologies AG dave@infineon.com).                                                          
;*********************************************************************************************************************
;*
;**************************** Change history ********************************
;* V1.0, Jan, 21, 2013 TYS:Startup file for XMC1
;* V1.1, Jul, 17, 2013 TYS:remove redundant vector table
;* V1.2, Nov, 25, 2014 JFT:Removed DAVE3 dependency. 
;*                         Default handler used for all IRQs
;* V1.3, Dec, 11, 2014 JFT:Default clocking changed, MCLK=32MHz and PCLK=64MHz
;* V1.4, Sep, 03, 2015 JFT:SSW default clocking changed, MCLK=8MHz and PCLK=16MHz avoid problems with BMI tool timeout
;*
;* @endcond 
;*

; ------------------ <<< Use Configuration Wizard in Context Menu >>> ------------------
           
           
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000A00

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

; <h> Clock system handling by SSW
;   <h> CLK_VAL1 Configuration
;    <o0.0..7>    FDIV Fractional Divider Selection
;    <i> Deafult: 0. Fractional part of clock divider, MCLK = DCO1 / (2 x (IDIV + (FDIV / 256)))
;    <o0.8..15>   IDIV Divider Selection (limited to 1-16)
;                    <0=> Divider is bypassed
;                    <1=> MCLK = 32 MHz
;                    <2=> MCLK = 16 MHz
;                    <3=> MCLK = 10.67 MHz
;                    <4=> MCLK = 8 MHz
;                    <254=> MCLK = 126 kHz
;                    <255=> MCLK = 125.5 kHz
;    <i> Deafult: 4. Interger part of clock divider, MCLK = DCO1 / (2 x (IDIV + (FDIV / 256))) = 8MHz
;    <o0.16>      PCLKSEL PCLK Clock Select
;                    <0=> PCLK = MCLK
;                    <1=> PCLK = 2 x MCLK
;    <i> Deafult: 2 x MCLK
;    <o0.17..19>  RTCCLKSEL RTC Clock Select
;                    <0=> 32.768kHz standby clock
;                    <1=> 32.768kHz external clock from ERU0.IOUT0
;                    <2=> 32.768kHz external clock from ACMP0.OUT
;                    <3=> 32.768kHz external clock from ACMP1.OUT
;                    <4=> 32.768kHz external clock from ACMP2.OUT
;                    <5=> Reserved
;                    <6=> Reserved
;                    <7=> Reserved
;    <i> Deafult: 32.768kHz standby clock 
;    <o0.31>      do not move CLK_VAL1 to SCU_CLKCR[0..19]
;   </h>
CLK_VAL1_Val    EQU     0x00000000      

;   <h> CLK_VAL2 Configuration
;    <o0.0>    disable VADC and SHS Gating
;    <o0.1>    disable CCU80 Gating
;    <o0.2>    disable CCU40 Gating
;    <o0.3>    disable USIC0 Gating
;    <o0.4>    disable BCCU0 Gating
;    <o0.5>    disable LEDTS0 Gating
;    <o0.6>    disable LEDTS1 Gating
;    <o0.7>    disable POSIF0 Gating
;    <o0.8>    disable MATH Gating
;    <o0.9>    disable WDT Gating
;    <o0.10>   disable RTC Gating
;    <o0.31>   do not move CLK_VAL2 to SCU_CGATCLR0[0..10]
;  </h>
; *****************************************************************************/
CLK_VAL2_Val    EQU     0x80000000      
; </h>

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     CLK_VAL1_Val              ; CLK_VAL1
                DCD     CLK_VAL2_Val              ; CLK_VAL2
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                
; Following code initializes the Veneers at address 0x20000000 with a "branch to itself"
; The real veneers will be copied later from the scatter loader before reaching main.
; This init code should handle an exception before the real veneers are copied.
SRAM_BASE            EQU     0x20000000
VENEER_INIT_CODE     EQU     0xE7FEBF00             ; NOP, B .

                LDR     R1, =SRAM_BASE
                LDR     R2, =VENEER_INIT_CODE                
                MOVS    R0, #48                     ; Veneer 0..47
Init_Veneers
                STR     R2, [R1]
                ADDS    R1, #4
                SUBS    R0, R0, #1
                BNE     Init_Veneers
                
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

Default_Handler PROC

                EXPORT  HardFault_Handler       [WEAK]
                EXPORT  SVC_Handler             [WEAK]
                EXPORT  PendSV_Handler          [WEAK]
                EXPORT  SysTick_Handler         [WEAK]
                EXPORT  SCU_0_IRQHandler        [WEAK]
                EXPORT  SCU_1_IRQHandler        [WEAK]
                EXPORT  SCU_2_IRQHandler        [WEAK]
                EXPORT  ERU0_0_IRQHandler       [WEAK]
                EXPORT  ERU0_1_IRQHandler       [WEAK]
                EXPORT  ERU0_2_IRQHandler       [WEAK]
                EXPORT  ERU0_3_IRQHandler       [WEAK]
                EXPORT  USIC0_0_IRQHandler      [WEAK]
                EXPORT  USIC0_1_IRQHandler      [WEAK]
                EXPORT  USIC0_2_IRQHandler      [WEAK]
                EXPORT  USIC0_3_IRQHandler      [WEAK]
                EXPORT  USIC0_4_IRQHandler      [WEAK]
                EXPORT  USIC0_5_IRQHandler      [WEAK]
                EXPORT  VADC0_C0_0_IRQHandler   [WEAK]
                EXPORT  VADC0_C0_1_IRQHandler   [WEAK]
                EXPORT  CCU40_0_IRQHandler      [WEAK]
                EXPORT  CCU40_1_IRQHandler      [WEAK]
                EXPORT  CCU40_2_IRQHandler      [WEAK]
                EXPORT  CCU40_3_IRQHandler      [WEAK]

HardFault_Handler       
SVC_Handler             
PendSV_Handler          
SysTick_Handler         
SCU_0_IRQHandler        
SCU_1_IRQHandler        
SCU_2_IRQHandler        
ERU0_0_IRQHandler       
ERU0_1_IRQHandler       
ERU0_2_IRQHandler       
ERU0_3_IRQHandler       
USIC0_0_IRQHandler      
USIC0_1_IRQHandler      
USIC0_2_IRQHandler      
USIC0_3_IRQHandler      
USIC0_4_IRQHandler      
USIC0_5_IRQHandler      
VADC0_C0_0_IRQHandler   
VADC0_C0_1_IRQHandler   
CCU40_0_IRQHandler      
CCU40_1_IRQHandler      
CCU40_2_IRQHandler      
CCU40_3_IRQHandler      
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


;* ================== START OF INTERRUPT HANDLER VENEERS ==================== */
; Veneers are located to fix SRAM Address 0x2000'0000
                AREA    |.ARM.__at_0x20000000|, CODE, READWRITE

; Each Veneer has exactly a lengs of 4 Byte

                MACRO
                STAYHERE $IrqNumber
                LDR  R0, =$IrqNumber
                B    .
                MEND

                MACRO
                JUMPTO $Handler
                LDR  R0, =$Handler
                BX   R0
                MEND

                STAYHERE 0x0                          ;* Reserved
                STAYHERE 0x1                          ;* Reserved 
                STAYHERE 0x2                          ;* Reserved 
                JUMPTO   HardFault_Handler            ;* HardFault Veneer  
                STAYHERE 0x4                          ;* Reserved 
                STAYHERE 0x5                          ;* Reserved 
                STAYHERE 0x6                          ;* Reserved 
                STAYHERE 0x7                          ;* Reserved 
                STAYHERE 0x8                          ;* Reserved 
                STAYHERE 0x9                          ;* Reserved 
                STAYHERE 0xA                          ;* Reserved
                JUMPTO   SVC_Handler                  ;* SVC Veneer        
                STAYHERE 0xC                          ;* Reserved
                STAYHERE 0xD                          ;* Reserved
                JUMPTO   PendSV_Handler               ;* PendSV Veneer     
                JUMPTO   SysTick_Handler              ;* SysTick Veneer    
                JUMPTO   SCU_0_IRQHandler             ;* SCU_0 Veneer      
                JUMPTO   SCU_1_IRQHandler             ;* SCU_1 Veneer      
                JUMPTO   SCU_2_IRQHandler             ;* SCU_2 Veneer      
                JUMPTO   ERU0_0_IRQHandler            ;* SCU_3 Veneer      
                JUMPTO   ERU0_1_IRQHandler            ;* SCU_4 Veneer      
                JUMPTO   ERU0_2_IRQHandler            ;* SCU_5 Veneer      
                JUMPTO   ERU0_3_IRQHandler            ;* SCU_6 Veneer      
                STAYHERE 0x17                         ;* Reserved  
                STAYHERE 0x18                         ;* Reserved
                JUMPTO   USIC0_0_IRQHandler           ;* USIC0_0 Veneer    
                JUMPTO   USIC0_1_IRQHandler           ;* USIC0_1 Veneer    
                JUMPTO   USIC0_2_IRQHandler           ;* USIC0_2 Veneer    
                JUMPTO   USIC0_3_IRQHandler           ;* USIC0_3 Veneer    
                JUMPTO   USIC0_4_IRQHandler           ;* USIC0_4 Veneer    
                JUMPTO   USIC0_5_IRQHandler           ;* USIC0_5 Veneer    
                JUMPTO   VADC0_C0_0_IRQHandler        ;* VADC0_C0_0 Veneer 
                JUMPTO   VADC0_C0_1_IRQHandler        ;* VADC0_C0_1 Veneer 
                STAYHERE 0x21                         ;* Reserved
                STAYHERE 0x22                         ;* Reserved
                STAYHERE 0x23                         ;* Reserved
                STAYHERE 0x24                         ;* Reserved
                JUMPTO   CCU40_0_IRQHandler           ;* CCU40_0 Veneer    
                JUMPTO   CCU40_1_IRQHandler           ;* CCU40_1 Veneer    
                JUMPTO   CCU40_2_IRQHandler           ;* CCU40_2 Veneer    
                JUMPTO   CCU40_3_IRQHandler           ;* CCU40_3 Veneer    
                STAYHERE 0x29                         ;* Reserved 
                STAYHERE 0x2A                         ;* Reserved  
                STAYHERE 0x2B                         ;* Reserved 
                STAYHERE 0x2C                         ;* Reserved
                STAYHERE 0x2D                         ;* Reserved
                STAYHERE 0x2E                         ;* Reserved
                STAYHERE 0x2F                         ;* Reserved

                ALIGN

;* ================== END OF INTERRUPT HANDLER VENEERS ====================== */

                END

.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:

    /* Set stack pointer */
    LDR   r0, =_estack
    MOV   sp, r0

    /* Check if boot space corresponds to test memory */
    LDR   R0,=0x00000004
    LDR   R1, [R0]
    LSRS  R1, R1, #24
    LDR   R2,=0x1F
    CMP   R1, R2
    BNE   ApplicationStart

    /* SYSCFG clock enable */
    LDR   R0,=0x40021018
    LDR   R1,=0x00000001
    STR   R1, [R0]

    /* Set CFGR1 register with flash memory remap at address 0 */
    LDR   R0,=0x40010000
    LDR   R1,=0x00000000
    STR   R1, [R0]

    ApplicationStart:
        /* Copy the data segment initializers from flash to SRAM */
        LDR   r0, =_sdata
        LDR   r1, =_edata
        LDR   r2, =_sidata
        MOVS  r3, #0
        B     LoopCopyDataInit

    CopyDataInit:
        LDR   r4, [r2, r3]
        STR   r4, [r0, r3]
        ADDS  r3, r3, #4

    LoopCopyDataInit:
        ADDS  r4, r0, r3
        CMP   r4, r1
        BCC   CopyDataInit

        /* Zero fill the bss segment. */
        LDR   r2, =_sbss
        LDR   r4, =_ebss
        MOVS  r3, #0
        B     LoopFillZerobss

    FillZerobss:
        STR   r3, [r2]
        ADDS  r2, r2, #4

    LoopFillZerobss:
        CMP   r2, r4
        BCC   FillZerobss

        /* Call the clock system intitialization function. */
        BL    SystemInit
        /* Call static constructors */
        /* Call the application's entry point. */
        BL    main

    LoopForever:
        B     LoopForever

.size Reset_Handler, .-Reset_Handler

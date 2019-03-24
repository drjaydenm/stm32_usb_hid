.syntax unified
.cpu cortex-m0
.fpu softvfp
.thumb

.global vtable
.global Default_Handler

/*
 * The vector table.
 */
.type vtable, %object
.section .isr_vector,"a",%progbits
vtable:
    .word  _estack
    .word  Reset_Handler
    .word  NMI_Handler
    .word  HardFault_Handler
    .word  0
    .word  0
    .word  0
    .word  0
    .word  0
    .word  0
    .word  0
    .word  SVC_Handler
    .word  0
    .word  0
    .word  PendSV_Handler
    .word  SysTick_Handler
    .word  WWDG_IRQHandler                   /* Window WatchDog              */
    .word  PVD_VDDIO2_IRQHandler             /* PVD and VDDIO2 through EXTI Line detect */
    .word  RTC_IRQHandler                    /* RTC through the EXTI line    */
    .word  FLASH_IRQHandler                  /* FLASH                        */
    .word  RCC_CRS_IRQHandler                /* RCC and CRS                  */
    .word  EXTI0_1_IRQHandler                /* EXTI Line 0 and 1            */
    .word  EXTI2_3_IRQHandler                /* EXTI Line 2 and 3            */
    .word  EXTI4_15_IRQHandler               /* EXTI Line 4 to 15            */
    .word  TSC_IRQHandler                    /* TSC                          */
    .word  DMA1_Channel1_IRQHandler          /* DMA1 Channel 1               */
    .word  DMA1_Channel2_3_IRQHandler        /* DMA1 Channel 2 and Channel 3 */
    .word  DMA1_Channel4_5_IRQHandler        /* DMA1 Channel 4 and Channel 5 */
    .word  ADC1_IRQHandler                   /* ADC1                         */
    .word  TIM1_BRK_UP_TRG_COM_IRQHandler    /* TIM1 Break, Update, Trigger and Commutation */
    .word  TIM1_CC_IRQHandler                /* TIM1 Capture Compare         */
    .word  TIM2_IRQHandler                   /* TIM2                         */
    .word  TIM3_IRQHandler                   /* TIM3                         */
    .word  0                                 /* Reserved                     */
    .word  0                                 /* Reserved                     */
    .word  TIM14_IRQHandler                  /* TIM14                        */
    .word  0                                 /* Reserved                     */
    .word  TIM16_IRQHandler                  /* TIM16                        */
    .word  TIM17_IRQHandler                  /* TIM17                        */
    .word  I2C1_IRQHandler                   /* I2C1                         */
    .word  0                                 /* Reserved                     */
    .word  SPI1_IRQHandler                   /* SPI1                         */
    .word  SPI2_IRQHandler                   /* SPI2                         */
    .word  USART1_IRQHandler                 /* USART1                       */
    .word  USART2_IRQHandler                 /* USART2                       */
    .word  0                                 /* Reserved                     */
    .word  CEC_CAN_IRQHandler                /* CEC and CAN                  */
    .word  USB_IRQHandler                    /* USB                          */

    /*
     * Setup weak aliases for each exception handler to the
     * default one. These can be updated later, or just
     * overridden since they're weak refs.
     * The Reset_Handler is set up separately.
     */
    .weak      NMI_Handler
    .thumb_set NMI_Handler,Default_Handler

    .weak      HardFault_Handler
    .thumb_set HardFault_Handler,Default_Handler

    .weak      SVC_Handler
    .thumb_set SVC_Handler,Default_Handler

    .weak      PendSV_Handler
    .thumb_set PendSV_Handler,Default_Handler

    .weak      SysTick_Handler
    .thumb_set SysTick_Handler,Default_Handler

    .weak      WWDG_IRQHandler
    .thumb_set WWDG_IRQHandler,Default_Handler

    .weak      PVD_VDDIO2_IRQHandler
    .thumb_set PVD_VDDIO2_IRQHandler,Default_Handler

    .weak      RTC_IRQHandler
    .thumb_set RTC_IRQHandler,Default_Handler

    .weak      FLASH_IRQHandler
    .thumb_set FLASH_IRQHandler,Default_Handler

    .weak      RCC_CRS_IRQHandler
    .thumb_set RCC_CRS_IRQHandler,Default_Handler

    .weak      EXTI0_1_IRQHandler
    .thumb_set EXTI0_1_IRQHandler,Default_Handler

    .weak      EXTI2_3_IRQHandler
    .thumb_set EXTI2_3_IRQHandler,Default_Handler

    .weak      EXTI4_15_IRQHandler
    .thumb_set EXTI4_15_IRQHandler,Default_Handler

    .weak      TSC_IRQHandler
    .thumb_set TSC_IRQHandler,Default_Handler

    .weak      DMA1_Channel1_IRQHandler
    .thumb_set DMA1_Channel1_IRQHandler,Default_Handler

    .weak      DMA1_Channel2_3_IRQHandler
    .thumb_set DMA1_Channel2_3_IRQHandler,Default_Handler

    .weak      DMA1_Channel4_5_IRQHandler
    .thumb_set DMA1_Channel4_5_IRQHandler,Default_Handler

    .weak      ADC1_IRQHandler
    .thumb_set ADC1_IRQHandler,Default_Handler

    .weak      TIM1_BRK_UP_TRG_COM_IRQHandler
    .thumb_set TIM1_BRK_UP_TRG_COM_IRQHandler,Default_Handler

    .weak      TIM1_CC_IRQHandler
    .thumb_set TIM1_CC_IRQHandler,Default_Handler

    .weak      TIM2_IRQHandler
    .thumb_set TIM2_IRQHandler,Default_Handler

    .weak      TIM3_IRQHandler
    .thumb_set TIM3_IRQHandler,Default_Handler

    .weak      TIM14_IRQHandler
    .thumb_set TIM14_IRQHandler,Default_Handler

    .weak      TIM16_IRQHandler
    .thumb_set TIM16_IRQHandler,Default_Handler

    .weak      TIM17_IRQHandler
    .thumb_set TIM17_IRQHandler,Default_Handler

    .weak      I2C1_IRQHandler
    .thumb_set I2C1_IRQHandler,Default_Handler

    .weak      SPI1_IRQHandler
    .thumb_set SPI1_IRQHandler,Default_Handler

    .weak      SPI2_IRQHandler
    .thumb_set SPI2_IRQHandler,Default_Handler

    .weak      USART1_IRQHandler
    .thumb_set USART1_IRQHandler,Default_Handler

    .weak      USART2_IRQHandler
    .thumb_set USART2_IRQHandler,Default_Handler

    .weak      CEC_CAN_IRQHandler
    .thumb_set CEC_CAN_IRQHandler,Default_Handler

    .weak      USB_IRQHandler
    .thumb_set USB_IRQHandler,Default_Handler
.size vtable, .-vtable

/*
 * A 'Default' interrupt handler. This is where interrupts
 * which are not otherwise configured will go.
 * It is an infinite loop, because...well, we weren't
 * expecting the interrupt, so what can we do?
 */
.section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    B Infinite_Loop
    .size Default_Handler, .-Default_Handler

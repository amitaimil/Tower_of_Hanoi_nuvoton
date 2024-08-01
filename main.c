
//
// Smpl_Timer_LCD
// 
// Timer0 set at one-shot   @ 1 sec or 1 Hz
// Timer1 set at periodic   @ 1 sec or 1 Hz
// Timer2 set at contiuous  @ 1 sec or 1 Hz

#include <stdio.h> 
#include <string.h>
#include "NUC1xx.h"
#include "LCD_Driver.h"
#include "scankey.h"
#include "NUC1xx-LB_002\LCD_Driver.h"
#include "Driver\DrvSYS.h"
#define  ONESHOT  0   // counting and interrupt when reach TCMPR number, then stop
#define  PERIODIC 1   // counting and interrupt when reach TCMPR number, then counting from 0 again
#define  TOGGLE   2   // keep counting and interrupt when reach TCMPR number, tout toggled (between 0 and 1)
#define  CONTINUOUS 3 // keep counting and interrupt when reach TCMPR number
static char TEXT2[16] = "                ";
static char TEXT1[16] = "                ";
static char step[16] = "                ";
static uint16_t stepnum =0;
void hanoi(int n, char A, char B, char C) {
    uint16_t i;
    if (n == 0) {
        return;
			stepnum++;
    }
    hanoi(n - 1, A, C, B);
    clr_all_panel();
		stepnum++;
    sprintf(TEXT1, "Move disc %d", n);
    sprintf(TEXT2, "from %c to %c", A, B);
		sprintf(step, "step: %d",stepnum);
    print_lcd(1, TEXT1);
    print_lcd(2, TEXT2);
		    print_lcd(3, step);
    for (i = 0; i < 15; i++) {
        DrvSYS_Delay(10000000);
    }

    hanoi(n - 1, C, B, A);


}

int scanNum() {
    uint16_t num = 0;
    char TEXT3[16] = "How many";
    char TEXT4[16] = "disks are there?";
    char TEXT5[2] = "";
    print_lcd(0, TEXT3);
    print_lcd(1, TEXT4);
    while (num == 0) {
        num = Scankey();
        sprintf(TEXT5, "%d", num);
        print_lcd(2, TEXT5);
    }
    DrvSYS_Delay(10000000);
    DrvSYS_Delay(10000000);
    clr_all_panel();
    return num;
}

int32_t main(void) {
    char A = 'A';
    char B = 'B';
    char C = 'C';
    uint16_t num;
    OpenKeyPad();

    UNLOCKREG();
    SYSCLK->PWRCON.XTL12M_EN = 1; //Enable 12MHz Crystal
    SYSCLK->CLKSEL0.HCLK_S = 0;
    LOCKREG();

    Initial_panel();
    clr_all_panel();
    num = scanNum();
    hanoi(num, 'A', 'B', 'C');

    while (1) {
        __NOP(); // No Operation
    }
}



#include "config.h"
#include "bits.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "adc.h"
#include "limpar.h"
#include "ssd.h "
#include "timer.h"
#define ON 0x0F

void main(void) {
    int x = 3000, t, passos = 1, y, z, a, cp = 0, cm = 0, mesa = 0, ap = 0, b = 1, c = 0, i,k=0,j=0;
    unsigned int tecla = 16;
    adcInit();


    lcdInit();
    ssdInit();
    kpInit();
    lcdString("Bem Vindo");
    atraso(1000);
    lcdPosition(0, 0);
    lcdString("Quanto deseja");
    lcdPosition(1, 0);
    lcdString("apostar?");
    atraso(1000);
    clear(0, 0);
    for (;;) {

        switch (passos) {
            case 1:
                clear(0, 0);
                for (;;) {
                    a++;
                    if (a == 15)
                        a = 1;




                    y = adcRead(0);
                    if (y > 1000)
                        y = 1000;
                    lcdCommand(0x80);
                    lcdString("Valor: R$");
                    lcdChar((y / 1000) % 10 + 48);
                    lcdChar((y / 100) % 10 + 48);
                    lcdChar((y / 10) % 10 + 48);
                    lcdChar(y % 10 + 48);
                    lcdPosition(1, 0);
                    lcdString("Saldo: R$");
                    lcdNumber(x);


                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (b == 0) {
                        if (bitTst(tecla, 1)) {
                            b = 1;
                            passos++;
                            break;
                        }

                    }
                    if (b == 1) {
                        if (bitTst(tecla, 0)) {
                            b = 0;
                            passos++;
                            break;
                        }

                    }
                    kpDebounce();

                }
                break;

            case 2:
                clear(0, 0);
                lcdString("Confirmar aposta");
                lcdPosition(1, 0);
                lcdString("de: R$");
                lcdNumber(y);
                for (;;) {
                    z++;
                    if (z == 15)
                        z = 1;
                    kpDebounce();
                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (b == 0) {
                        if (bitTst(tecla, 1)) {
                            b = 1;
                            x -= y;
                            passos++;
                            if (x < 0) {
                                clear(0, 0);
                                lcdString("Aposta invalida");
                                atraso(1000);

                                x += y;
                                passos -= 2;

                            }
                            break;
                        }
                        if (bitTst(tecla, 3)) {
                            passos--;
                            b = 1;
                            break;
                        }
                    }
                    if (b == 1) {
                        if (bitTst(tecla, 0)) {
                            b = 0;

                            x -= y;
                            passos++;
                            if (x < 0) {
                                clear(0, 0);
                                lcdString("Aposta invalida");
                                atraso(1000);

                                x += y;
                                passos -= 2;

                            }
                            break;
                        }
                        if (bitTst(tecla, 2)) {
                            passos--;
                            b = 0;
                            break;
                        }
                    }


                }
                break;
            case 3:
                clear(0, 0);
                lcdString("Sua Carta he: ");
                switch (a) {
                    case 1:
                        lcdString("1");
                        break;
                    case 2:
                        lcdString("2");
                        break;
                    case 3:
                        lcdString("3");
                        break;
                    case 4:
                        lcdString("4");
                        break;
                    case 5:
                        lcdString("5");
                        break;
                    case 6:
                        lcdString("6");
                        break;
                    case 7:
                        lcdString("7");
                        break;
                    case 8:
                        lcdString("8");
                        break;
                    case 9:
                        lcdString("9");
                        break;
                    case 10:
                        lcdString("10");
                        break;
                    case 11:
                        lcdString("J");
                        a = 10;
                        break;
                    case 12:
                        lcdString("Q");
                        a = 10;
                        break;
                    case 13:
                        lcdString("K");
                        a = 10;
                        break;
                    case 14:
                        lcdString("A");
                        a = 11;
                        cp++;
                        break;

                }

                atraso(200);
                lcdPosition(1, 0);
                lcdString("A da mesa he: ");
                switch (z) {
                    case 1:
                        lcdString("1");
                        break;
                    case 2:
                        lcdString("2");
                        break;
                    case 3:
                        lcdString("3");
                        break;
                    case 4:
                        lcdString("4");
                        break;
                    case 5:
                        lcdString("5");
                        break;
                    case 6:
                        lcdString("6");
                        break;
                    case 7:
                        lcdString("7");
                        break;
                    case 8:
                        lcdString("8");
                        break;
                    case 9:
                        lcdString("9");
                        break;
                    case 10:
                        lcdString("10");
                        break;
                    case 11:
                        lcdString("J");
                        z = 10;
                        break;
                    case 12:
                        lcdString("Q");
                        z = 10;
                        break;
                    case 13:
                        lcdString("K");
                        z = 10;
                        break;
                    case 14:
                        lcdString("A");
                        z = 11;
                        cm++;
                        break;

                }
                mesa += z;
                ap += a;
                atraso(200);
                for (;;) {
                    a++;
                    if (a == 15)
                        a = 1;
                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (b == 1) {

                        if (bitTst(tecla, 0)) {
                            passos++;
                            b = 0;
                            break;
                        }
                    }
                    if (b == 0) {

                        if (bitTst(tecla, 1)) {
                            passos++;
                            b = 1;
                            break;
                        }
                    }



                    ssdDigit((mesa) % 10, 3);
                    ssdDigit((mesa / 10) % 10, 2);
                    ssdDigit((ap) % 10, 1);
                    ssdDigit((ap / 10) % 10, 0);
                    ssdUpdate();
                    for (t = 0; t < 1000; t++);
                    kpDebounce();
                }
                break;
            case 4:
                clear(0, 0);
                lcdString("Sua nova carta");
                lcdPosition(1, 0);
                lcdString("eh: ");
                switch (a) {
                    case 1:
                        lcdString("1");
                        break;
                    case 2:
                        lcdString("2");
                        break;
                    case 3:
                        lcdString("3");
                        break;
                    case 4:
                        lcdString("4");
                        break;
                    case 5:
                        lcdString("5");
                        break;
                    case 6:
                        lcdString("6");
                        break;
                    case 7:
                        lcdString("7");
                        break;
                    case 8:
                        lcdString("8");
                        break;
                    case 9:
                        lcdString("9");
                        break;
                    case 10:
                        lcdString("10");
                        break;
                    case 11:
                        lcdString("J");
                        a = 10;
                        break;
                    case 12:
                        lcdString("Q");
                        a = 10;
                        break;
                    case 13:
                        lcdString("K");
                        a = 10;
                        break;
                    case 14:
                        lcdString("A");
                        a = 11;
                        cp++;
                        break;

                }
                ap += a;

                for (;;) {
                    a++;
                    if (a == 15)
                        a = 1;

                    if (ap > 21 && cp >= 1) {
                        ap -= 10;
                        cp--;
                    }
                    

                    if (ap > 21) {
                        passos = 9;
                        break;
                    }



                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (b == 0) {
                        if (bitTst(tecla, 1)) {
                            b = 1;
                            c = 1;
                            break;
                        }
                        if (bitTst(tecla, 3)) {
                            passos ++;
                            b = 1;
                            break;
                        }
                    }
                    if (b == 1) {
                        if (bitTst(tecla, 0)) {
                            b = 0;
                            break;
                        }
                        if (bitTst(tecla, 2)) {
                            passos ++;
                            b = 0;
                            break;
                        }
                    }

                    ssdDigit((mesa) % 10, 3);
                    ssdDigit((mesa / 10) % 10, 2);
                    ssdDigit((ap) % 10, 1);
                    ssdDigit((ap / 10) % 10, 0);
                    ssdUpdate();
                    for (t = 0; t < 1000; t++);
                    kpDebounce();
                }
                break;
            case 5:
                if (ap == 21 && c==0) {
                    if(mesa < 10 || k==1){
                    atraso(1000);
                    clear(0, 0);
                    lcdString("   BlackJack!   ");
                    x-=y;
                    y=2*y;                    
                    passos = 8;
                    
                    }
                    else{
                        j=1;
                        passos++;
                    }}
                else
                    passos++;
                

                break;
            case 6:
                clear(0, 0);
                lcdString("A nova carta da");
                lcdPosition(1, 0);
                lcdString("mesa eh: ");
                switch (a) {
                    case 1:
                        lcdString("1");
                        break;
                    case 2:
                        lcdString("2");
                        break;
                    case 3:
                        lcdString("3");
                        break;
                    case 4:
                        lcdString("4");
                        break;
                    case 5:
                        lcdString("5");
                        break;
                    case 6:
                        lcdString("6");
                        break;
                    case 7:
                        lcdString("7");
                        break;
                    case 8:
                        lcdString("8");
                        break;
                    case 9:
                        lcdString("9");
                        break;
                    case 10:
                        lcdString("10");
                        break;
                    case 11:
                        lcdString("J");
                        a = 10;
                        break;
                    case 12:
                        lcdString("Q");
                        a = 10;
                        break;
                    case 13:
                        lcdString("K");
                        a = 10;
                        break;
                    case 14:
                        lcdString("A");
                        a = 11;
                        cm++;
                        break;

                }
                
                mesa += a;
                if(j==1 && mesa!=21){
                    k=1;
                    passos=5;
                    break;
                }
                    

                for (;;) {
                    a++;
                    if (a == 15)
                        a = 1;

                    if (mesa > 21 && cm == 1) {
                        mesa -= 10;
                        cm = 0;
                    }





                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (b == 0) {
                        if (bitTst(tecla, 1)) {
                            b = 1;
                            c = 1;
                            break;
                        }

                    }
                    if (b == 1) {
                        if (bitTst(tecla, 0)) {
                            b = 0;
                            break;
                        }

                    }

                    ssdDigit((mesa) % 10, 3);
                    ssdDigit((mesa / 10) % 10, 2);
                    ssdDigit((ap) % 10, 1);
                    ssdDigit((ap / 10) % 10, 0);
                    ssdUpdate();
                    for (t = 0; t < 1000; t++);
                    kpDebounce();

                    if (mesa >= 17 && mesa <= 21) {
                        passos++;
                        break;
                    }
                    if (mesa > 21) {
                        passos += 2;
                        break;
                    }



                }
                break;
            case 7:
                if (ap > mesa)
                    passos++;
                if (ap < mesa)
                    passos += 2;
                if (ap == mesa)
                    passos += 3;
                break;
            case 8:
                atraso(1000);
                clear(0, 0);

                lcdString("  Voce ganhou!  ");
                lcdPosition(1, 0);
                lcdString("    R$");
                lcdNumber(y);
                for (i = 0; i < 1000; i++) {
                    ssdDigit((mesa) % 10, 3);
                    ssdDigit((mesa / 10) % 10, 2);
                    ssdDigit((ap) % 10, 1);
                    ssdDigit((ap / 10) % 10, 0);
                    ssdUpdate();

                }
                x += 2 * y;

                passos = 11;
                break;
            case 9:
                atraso(1000);
                clear(0, 0);

                lcdString("  Voce perdeu!  ");
                lcdPosition(1, 0);
                lcdString("    R$");
                lcdNumber(y);
                for (i = 0; i < 1000; i++) {
                    ssdDigit((mesa) % 10, 3);
                    ssdDigit((mesa / 10) % 10, 2);
                    ssdDigit((ap) % 10, 1);
                    ssdDigit((ap / 10) % 10, 0);
                    ssdUpdate();

                }


                passos = 11;
                break;
            case 10:
                atraso(1000);
                clear(0, 0);

                lcdString("    Empatou!  ");

                for (i = 0; i < 1000; i++) {
                    ssdDigit((mesa) % 10, 3);
                    ssdDigit((mesa / 10) % 10, 2);
                    ssdDigit((ap) % 10, 1);
                    ssdDigit((ap / 10) % 10, 0);
                    ssdUpdate();

                }
                x += y;
                lcdString("R$");
                passos = 11;
                break;
            case 11:
                clear(0, 0);
                lcdString("   Seu saldo:");
                lcdPosition(1, 0);
                lcdString("    R$");
                lcdNumber(x);
                for (;;) {
                    kpDebounce();
                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (b == 0) {
                        if (bitTst(tecla, 1)) {
                            b = 1;
                            mesa = 0;
                            ap = 0;
                            cm = 0;
                            cp = 0;
                            c = 0;
                            k=0;
                            j=0;
                            passos = 1;

                            break;
                        }
                        if (bitTst(tecla, 3)) {
                            passos = 12;
                            b = 1;
                            break;
                        }
                    }
                    if (b == 1) {
                        if (bitTst(tecla, 0)) {
                            passos = 1;
                            mesa = 0;
                            ap = 0;
                            cm = 0;
                            cp = 0;
                            c = 0;
                            b = 0;
                            k=0;
                            j=0;

                            break;
                        }
                        if (bitTst(tecla, 2)) {
                            passos = 12;
                            b = 0;
                            break;
                        }
                    }
                }
                break;
            case 12:
                clear(0,0);
                lcdString("      Fim!");
                for(;;){}
        }
    }












}


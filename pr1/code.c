#include <stdio.h>
/* 
Архитектура Фон Неймана
Единая память хранит в себе всё
Выполнение идет последовательно по шагам
Программное управление зависит от того, какую инструкцию подали
*/
int main() {
    int i=0;
    int memory[256]= {0},cpu_state[8]={0};
    
    while(i<256 && scanf("%d", &memory[i]) == 1) {
        i++;
    }
    cpu_state[3] = memory[0];
    cpu_state[0] = 2;
    
    while(cpu_state[4]==0){
        if(cpu_state[0] < 0 || cpu_state[0] >= 256) {
            printf("Ошибка выход за границы памяти (pc = %d).\n", cpu_state[0]);
            cpu_state[0] = cpu_state[3]; 
            continue;
        }
        int current_pc = cpu_state[0];
        cpu_state[2] = memory[current_pc]; /* cpu_state[0] хрнаит номер ячейки памяти и потом мы смотрим в памяти 
                                            и там написано какую команду выполнить*/
        if (cpu_state[2] >= 2 && cpu_state[2] <= 5){
            if (cpu_state[0] + 1 >= 256 || memory[cpu_state[0] + 1] < 0 || memory[cpu_state[0] + 1] >= 256) { /* memory[cpu_state[0] + 1] < 0 делается для проверки, чтобы не было memory[-1], а такого быть не может*/
                        if (cpu_state[5] != 0) { cpu_state[4] = 1; break; }
                        cpu_state[5] = 1;
                        cpu_state[0] = cpu_state[3];
                    continue;
            }
        }                          
        switch (cpu_state[2]){
            case 0:
            cpu_state[4]=1;
            cpu_state[0]+=1;
            break;
            case 1:
            printf("%d\n",cpu_state[1]);
            cpu_state[0]+=1; /*т.к нету действия дальнейшего*/
            break;
            case 2:
            
            cpu_state[1]=memory[memory[cpu_state[0]+1]]; /* Берем два раза memory из-за того сначала узнаем
                                                             где хранятся данные, а потом идем за данными*/
            cpu_state[0]+=2; /*т.к в если сделать +1 там будет лежать адрес, а программа воспримет его за новую команду*/
            break;
            case 3:
            
            cpu_state[1]*=memory[memory[cpu_state[0]+1]];
            cpu_state[0]+=2;
            break;
            case 4:
            
            cpu_state[0]=memory[cpu_state[0]+1]; /*один раз мемори т.к мы прыгаем именно по адерсу, раньше мы брали оттуда число*/
            break;
            case 5:
            
            if(cpu_state[1]==0){
                cpu_state[0]=memory[cpu_state[0]+1];
                break;
            }else{
                cpu_state[0]+=2; /*т.к занимаем команда и адрес ячейки 2 памяти*/
                break;
            }
            default:
            if (cpu_state[5] != 0) {
                    cpu_state[4] = 1;
                    break;
                }
                cpu_state[5] = 2;
                cpu_state[0] = cpu_state[3];
                continue;
        }
        int operand = 0;
        if (cpu_state[2] >= 2 && cpu_state[2] <= 5 && current_pc + 1 < 256) /*проверили что там требуется адрес*/ {
            operand = memory[current_pc + 1];
        }
        printf("pc=%d команда %d операнд %d аккумулятор %d\n", current_pc, cpu_state[2], operand, cpu_state[1]);
        
    }
    return 0;
}

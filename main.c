#include <stdio.h>
#include <stdlib.h>
#define C 10
#define R 8
void set_water_zero(int, int, int [][C], int[][C]);
void output_matrice(int, int, int[][C]);
void output_matrice_ships(int, int, int[][C]);
void shoot_input_position(int *, int *);
void edit_shoot_matrice_values(int, int, int, int [][C],  int[][C], int *, int*);
void input_ships(int, int, int *, int *, int[][C], int);
void edit_input_matrice_values(int, int *, int *, int[][C], int);
void output_legend();
int ships_matrice_check(int, int, int[][C]);
int main(void){
    int ship_size, keep_shooting, r_input_position, c_input_position, ship3_counter, ship2_counter, moves_counter, ships_input_matrice[R][C], shoot_input_matrice[R][C];
    char keep_playing;
    do{ //questo ciclo serve per far decidere se si vuole giocare un'altra partita o chiudere il gioco
        system("cls");
        ship_size=1;
        ship3_counter=0;
        ship2_counter=0;
        moves_counter=0;
        set_water_zero(R, C, ships_input_matrice, shoot_input_matrice);
        output_legend();
        output_matrice_ships(R, C, ships_input_matrice);
        for(int i=1; i<4; i++){ // questo ciclo serve a far piazzare le ships al giocatore 1
            input_ships(R, C, &r_input_position, &c_input_position, ships_input_matrice, ship_size);
            system("cls");
            output_legend();
            output_matrice_ships(R, C, ships_input_matrice);
            ship_size++;
        }
        do{ //questo ciclo serve a far sparare il giocatore 2
            system("cls");
            output_legend();
            output_matrice(R, C, shoot_input_matrice);
            do
                shoot_input_position(&r_input_position, &c_input_position);
            while(r_input_position<0 || r_input_position>R-1 || c_input_position<0 || c_input_position>C-1);
            moves_counter++;
            edit_shoot_matrice_values(C, r_input_position, c_input_position, ships_input_matrice, shoot_input_matrice, &ship2_counter, &ship3_counter);
            keep_shooting=ships_matrice_check(R, C, ships_input_matrice);
        }while(keep_shooting==1); //cicla se ci sono ancora ships in campo
        system("cls");
        output_legend();
        output_matrice(R, C, shoot_input_matrice);
        printf("\n\nHai vinto in %d mosse", moves_counter);
        printf("\nDigitare s per iniziare un'altra partita, qualsiasi altro tasto per chiudere il gioco");
        scanf(" %c", &keep_playing);
    }while(keep_playing=='s');
}
// imposta tutte le caselle a 0 (acqua)
void set_water_zero(int r, int c, int ships_input_matrice[][c], int shoot_input_matrice[][c]){
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++){
            ships_input_matrice[i][j]=0;
            shoot_input_matrice[i][j]=0;
    }
}
// mostra a schermo il campo per il giocatore che deve sparare
void output_matrice(int r, int c, int shoot_input_matrice[][c]){
    printf("    |");
    for(int k=0; k<c; k++)
        printf("%d|",k);
    printf("\n");
    for(int i=0; i<r; i++){
        printf("\n%d|  ",i);
        for(int j=0; j<c; j++)
            printf("|%d", shoot_input_matrice[i][j]);
        printf("|");
    }
}
// mostra a schermo la posizione delle ships in fase di input
void output_matrice_ships(int r, int c, int ships_input_matrice[][c]){
    printf("    |");
    for(int k=0; k<c; k++)
        printf("%d|",k);
    printf("\n");
    for(int i=0; i<r; i++){
        printf("\n%d|  ",i);
        for(int j=0; j<c; j++)
            printf("|%d", ships_input_matrice[i][j]);
        printf("|");
    }
}
// input della posizione degli spari
void shoot_input_position(int *r_input_position, int *c_input_position){
    printf("\n\n   Inserire numero riga: ");
    scanf("%d", r_input_position);
    printf("\n   Inserire numero colonna: ");
    scanf("%d", c_input_position);
}
// modifica matrice dopo hit ricevuta
void edit_shoot_matrice_values(int c, int r_input_position, int c_input_position, int ships_input_matrice[][c], int shoot_input_matrice[][c], int *ship2_counter, int *ship3_counter){
    int i=0, j=0;
    while(i<r_input_position)
        i++;
    while(j<c_input_position)
        j++;
    if(ships_input_matrice[i][j]==0)
        shoot_input_matrice[i][j]=7;
    else if(ships_input_matrice[i][j]==1){
        shoot_input_matrice[i][j]=6;
        ships_input_matrice[i][j]=6;
    }else if(ships_input_matrice[i][j]==2 && *ship2_counter<1){
        shoot_input_matrice[i][j]=5;
        ships_input_matrice[i][j]=5;
        (*ship2_counter)++;
    }else if(ships_input_matrice[i][j]==2 && *ship2_counter==1){
        shoot_input_matrice[i][j]=6;
        ships_input_matrice[i][j]=6;
    }else if((ships_input_matrice[i][j]==3 && *ship3_counter<1) || (ships_input_matrice[i][j]==3 && *ship3_counter==1)){
        shoot_input_matrice[i][j]=5;
        ships_input_matrice[i][j]=5;
        (*ship3_counter)++;
    }else if(ships_input_matrice[i][j]==3 && *ship3_counter>1){
        shoot_input_matrice[i][j]=6;
        ships_input_matrice[i][j]=6;
     }
}
// input della posizione delle ships e rimando alla funzione che le posiziona nella matrice
void input_ships(int r, int c, int *r_input_position, int *c_input_position, int ships_input_matrice[][c], int ship_size){
    switch(ship_size){
        case 1:
            printf("\n\n ship da 1 casella:");
            do{
                printf("\n   Inserire posizione casella ");
                printf("\n   Posizione riga: ");
                scanf("%d", r_input_position);
                printf("\n   Posizione colonna: ");
                scanf("%d", c_input_position);
            }while(*r_input_position<0 || *r_input_position>r-1 || *c_input_position<0 || *c_input_position>c-1);
                edit_input_matrice_values(c, r_input_position, c_input_position, ships_input_matrice, ship_size);
            break;
        case 2:
            printf("\n\n ship da 2 caselle:");
            do{
                printf("\n   Inserire posizione della prima casella ");
                printf("\n   Posizione riga: ");
                scanf("%d", r_input_position);
                printf("\n   Posizione colonna: ");
                scanf("%d", c_input_position);
            }while(*r_input_position<0 || *r_input_position>r-1 || *c_input_position<0 || *c_input_position>c-1);
                edit_input_matrice_values(c, r_input_position, c_input_position, ships_input_matrice, ship_size);
            do{
                printf("\n   Inserire posizione della seconda casella ");
                printf("\n   Posizione riga: ");
                scanf("%d", r_input_position);
                printf("\n   Posizione colonna: ");
                scanf("%d", c_input_position);
            }while(*r_input_position<0 || *r_input_position>r-1 || *c_input_position<0 || *c_input_position>c-1);
                edit_input_matrice_values(c, r_input_position, c_input_position, ships_input_matrice, ship_size);
            break;
        case 3:
             printf("\n\n ship da 3 caselle:");
             do{
                printf("\n   Inserire posizione della prima casella ");
                printf("\n   Posizione riga: ");
                scanf("%d", r_input_position);
                printf("\n   Posizione colonna: ");
                scanf("%d", c_input_position);
            }while(*r_input_position<0 || *r_input_position>r-1 || *c_input_position<0 || *c_input_position>c-1);
                edit_input_matrice_values(c, r_input_position, c_input_position, ships_input_matrice, ship_size);
            do{
                printf("\n   Inserire posizione della seconda casella ");
                printf("\n   Posizione riga: ");
                scanf("%d", r_input_position);
                printf("\n   Posizione colonna: ");
                scanf("%d", c_input_position);
            }while(*r_input_position<0 || *r_input_position>r-1 || *c_input_position<0 || *c_input_position>c-1);
                edit_input_matrice_values(c, r_input_position, c_input_position, ships_input_matrice, ship_size);
            do{
                printf("\n   Inserire posizione della terza casella ");
                printf("\n   Posizione riga: ");
                scanf("%d", r_input_position);
                printf("\n   Posizione colonna: ");
                scanf("%d", c_input_position);
            }while(*r_input_position<0 || *r_input_position>r-1 || *c_input_position<0 || *c_input_position>c-1);
                edit_input_matrice_values(c, r_input_position, c_input_position, ships_input_matrice, ship_size);
            break;
    }
}
//posizionamento ships date in input
void edit_input_matrice_values(int c, int *r_input_position, int *c_input_position, int ships_input_matrice[][c], int ship_size){
    int i=0, j=0;
    while(i<*r_input_position)
        i++;
    while(j<*c_input_position)
        j++;
    ships_input_matrice[i][j]=ship_size;
}
//output a schermo legenda
void output_legend(){
    printf("                        BATTAGLIA NAVALE");
    printf("\n   0 indica l'acqua");
    printf("\n   1 indica la posizione della ship da 1 casella");
    printf("\n   2 indica la posizione di un pezzo della ship da 2 caselle");
    printf("\n   3 indica la posizione di un pezzo della ship da 3 caselle");
    printf("\n   7 indica il colpo andato a vuoto");
    printf("\n   5 indica colpito");
    printf("\n   6 indica colpito e affondato\n\n");
}
//controllo se ci sono ancora ships nel campo
int ships_matrice_check(int r, int c, int ships_input_matrice[][c]){
    int keep_shooting;
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            if(ships_input_matrice[i][j]>0 && ships_input_matrice[i][j]<4)
                keep_shooting=1;
    return keep_shooting;
}

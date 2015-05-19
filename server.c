#include "server.h"
#include <string.h>

kartyaType * pakliKartya(){
    kartyaType * pakli = malloc(sizeof(kartyaType)*KARTYASZ);
    int tombIndex = 0;
    for(int szin = pikk; szin <= kor; szin++ ){
        for(int rang = ketto; rang <= a; rang++, tombIndex++){
            pakli[tombIndex].rang = rang;
            pakli[tombIndex].szin = szin;
            pakli[tombIndex].jatekos = -1;
        }
    }

    return pakli;
}

kartyaType * pakli; // globális pakli
int i = 0;          // egy "ciklus" változo

void jatekosKezd(int jatekos, int random){
    if( i < 13 ){
        if ( pakli[random].jatekos == -1){ // ha az adott kártya nincs még kiosztva
            pakli[random].jatekos = jatekos;
            i++;
            jatekosKezd(jatekos, rand() % 52);
        }else{  // ha kivanosztva akkor
            jatekosKezd(jatekos, rand() % 52);
        }
    } else {  i = 0; }// ha már kiosztott 13 kártyát egy játékosnak
}

void kartyaKiosztas() {
    for( int i = 0; i < 4; i++ ){
        jatekosKezd(i, rand() % 52); // jatekosokhoz hozza rendelem a kartyakat
    }
}

void pakliKiiratasa(){ // elenőrzés véget
    for ( int i = 0; i < KARTYASZ; i++){
        printf("%i.\t%i\t%i\t%i\n", i,pakli[i].szin,pakli[i].rang,pakli[i].jatekos);
    }
}

char buff[13][7]; // jatekosok kártyái külön-külön
char * jatekosPakli(int jatekos){
     int a = 0;
    for( int i = 0; i < KARTYASZ; i++ ){
        if( pakli[i].jatekos == jatekos ){
            sprintf(buff[a], ";%2d;%2d;", pakli[i].rang, pakli[i].szin);
            a++;
        }
    }
    
    return * buff;

}

int kezdoJatekos(){ // Treff 2-es
    for ( int i = 0; i < KARTYASZ; i++){
        if(pakli[i].szin = treff && pakli[i].rang == ketto) {
            return pakli[i].jatekos;
        }
    }
}

int main()
{
    srand(time(NULL));

    int listenfd = 0;
    int clients[4] = {0};
    struct sockaddr_in serv_addr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    int korok = 0;

    char sendBuff[1025] = {' '};

    for( int i = 0; i < 4 ; i++ ){
        printf("%i jatekosra varas.\n", i);
        clients[i] = accept(listenfd, (struct sockaddr*)NULL, NULL);

        printf("Jatekos szam kiosztsa!\n");
        //sprintf( sendBuff, "%d" , i);
        snprintf(sendBuff, sizeof(sendBuff), "%d\n", i);
        send(clients[i], sendBuff, strlen(sendBuff) , 0);
    }


    while(1)
    {
        pakli = pakliKartya(); // pakli legenerálása
        kartyaKiosztas();
        //pakliKiiratasa();
        char sendBuff[1025] = {' '};
        char recvBuff[1025] = {' '};
        int kezdo = kezdoJatekos();


        for( int i = 0; i < 4 ; i++ ){
            snprintf(sendBuff, sizeof(sendBuff), "%s\n", jatekosPakli(i));
            //printf("%s ezek a kartyak kikuldese.\n", sendBuff);
            send(clients[i], sendBuff, strlen(sendBuff), 0);

            snprintf(sendBuff, sizeof(sendBuff), "%d\n", kezdo);
            printf("%s kezd.\n", sendBuff);
            send(clients[i], sendBuff, strlen(sendBuff), 0);
        }

        int pontok[4] = {0};
        int legkisebb, kisIndex;
        int legnagyobb, nagyIndex;

    do {
        char korLapja[4][1025] = {' '};
        snprintf(sendBuff, sizeof(sendBuff), "%d %s\n", korok,"kor");
        printf("%i kor megkezdese.\n", korok);
        for(int i = 0; i < 4; i++ )
            send(clients[i], sendBuff, strlen(sendBuff), 0);

        for(int i = 0; i < 4; i++) {
                int n = recv(clients[i], korLapja[i], 1025, 0);
                if ( n < 0)
                    printf("Valami baj van.");
                printf("%i jatekos ezt kuldte: %s",i, korLapja[i]);
        }



        int akiMindentVisz = 5;
        int pikkDama = 0;

        if(korok == 0){
            for(int i = 0; i < 4; i++ ){
                if(korLapja[0][4] == '0' && korLapja[0][5] == '0'
                    && korLapja[0][1] == '1' && korLapja[0][2] == '0' ||
                        korLapja[i][4] == '0' && korLapja[i][5] == '0'
                            && korLapja[i][1] == '1' && korLapja[i][2] == '0') // ekkor pikk dáma kijátszva
                    {
                        pikkDama = 1;
                    }
                if( korLapja[i][5] != '2' ){
                    akiMindentVisz = i;
                    break;
                }
            }
        }

        if(korok != 0) {
        for( int i = 1; i < 4; i++ ){ // azonos szín e mind és van e pikk dáma(q) ( 10 0 )
            if(korLapja[0][4] == '0' && korLapja[0][5] == '0'
                && korLapja[0][1] == '1' && korLapja[0][2] == '0' ||
                    korLapja[i][4] == '0' && korLapja[i][5] == '0'
                        && korLapja[i][1] == '1' && korLapja[i][2] == '0') // ekkor pikk dáma kijátszva
                {
                    pikkDama = 1;
                }
                if( korLapja[0][5] != korLapja[i][5] ){ // elsohoz kepest nem azonos a szin
                    akiMindentVisz = i;
                    break;
                }
        }
        }

        if( akiMindentVisz == 5 ){ // mindenki ugyan olyan színt rakott le
            char rang[2] = {korLapja[0][1],korLapja[0][2]};
            for( int i = 1; i < 4; i++ ){
                if( rang[0] < korLapja[i][1]            // pl 02 - 12
                    && rang[1] <= korLapja[i][2] ){
                        rang[0] = korLapja[i][1];
                        rang[1] = korLapja[i][2];
                        akiMindentVisz = i;
                } else if ( rang[0] > korLapja[i][1] ){ // ha a tizesem nagyobb akkor a szám is nagyobb
                    rang[0] = korLapja[i][1];
                    rang[1] = korLapja[i][2];
                    akiMindentVisz = i;
                } else if( rang[0] == korLapja[i][1]            // pl 10 - 12
                    && rang[1] < korLapja[i][2] ){
                        rang[0] = korLapja[i][1];
                        rang[1] = korLapja[i][2];
                        akiMindentVisz = i;
                }
            }
        }

        if(pikkDama){ pontok[akiMindentVisz] += 13; }
        else { pontok[akiMindentVisz]++; }

        for(int i = 0; i < 4; i++){
            printf("%i. jatekos %i pontja van.\n", i, pontok[i]);
        }

        for( int i = 0; i < 4; i++)
            for(int ii = 0; ii < 4; ii++){
                send(clients[i],korLapja[ii], 1025, 0 );
            }

        legkisebb = pontok[0]; kisIndex = 0;
        legnagyobb = pontok[1]; nagyIndex = 1;
        for( int i = 0; i < 4; i++){
            if (legkisebb > pontok[i])
                legkisebb = pontok[i];
            if (legnagyobb < pontok[i])
                legnagyobb = pontok[i];
        }

        if ( legnagyobb >= 100 ){
            printf("Jatek vége!");
            break; // kilépek a körböl
        }

        if(korLapja[0][0] == 'f' || korLapja[1][0] == 'f' ||
            korLapja[2][0] == 'f' || korLapja[3][0] == 'f' ){
            printf("Kor megszakitasa, egyik jatekos feladta.\n");
            break;
        }

        korok++;

    }while(1);

        printf("jatek vege!");

        for( int i = 0; i < 4; i++){
            if( legnagyobb == pontok[i] && nagyIndex != i ){
                printf("Döntetlen!");
                break;
            }
            if( i == 3 ){
                printf("Nyertes %d jatekos %d ponttal.\n", kisIndex, pontok[kisIndex]);
            }
        }

        /*snprintf(sendBuff, sizeof(sendBuff), "%s\n", "vege");
        for( int i = 0; i < 4 ; i++ ){
            send(clients[i], sendBuff, strlen(sendBuff), 0);
        }*/

        //snprintf(recvBuff, sizeof(recvBuff), " ");
        char b[1025] = {'0'};
        for(int i = 0; i < 4; i++) {
                int n = recv(clients[i], b, 1025, 0);
                if ( n < 0)
                    printf("Valami baj van.");

                printf("%i jatekos ezt kuldte arra hogy vege: %s\n",i, b);

                if( b[0] != 'i' )
                    break;
        }

        break;

        sleep(1);
    } // while end

     for( int i = 0; i < 4 ; i++ ){
         printf("%i jatekos kapcsolat bontas.\n",i);
         close(clients[i]);
     }
}

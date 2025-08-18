#include "equipArray.h"


struct equipArray_s{
    int qtUso;
    int vettEq[EQUIP_SLOT]; //versione come ADT
    //inv_t *vettEqp[MAX]; //versione con puntatori
};

equipArray_t equipArray_init(){
    equipArray_t head; //head è puntatore
    int i;
    head=malloc(1 * sizeof(struct equipArray_s));
    head->qtUso=0;
    for(i=0; i<EQUIP_SLOT; i++){
        head->vettEq[i]=-1;
    }
    return head;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    return equipArray->qtUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i, ele,indice=equipArray_inUse(equipArray);
    for(i=0; i<indice; i++){
        ele= equipArray_getEquipByIndex(equipArray, i);
        invArray_printByIndex(fp, invArray, ele);
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    char check, nome[50];// *fitname;//ricordati del free per il nome
    int  flag=0, i, invnum, found=0, search, j;
    printf("Equipaggiamento disponibile:\n");
    invArray_print(stdout, invArray);
    /*while(!flag){
        printf("Quanti oggetti vuoi inserire o rimuovere nell'inventario? (MAX 8 oggetti)\n");
        scanf(" %d", &how_many);
        if(how_many<9 && how_many>-1)//in negativo o superare gli slot disponibili
            flag=1;
        else
            printf(" Numero non valido, riprovare\n");
    }
    flag=0;*/
    //for(i=0; i<how_many; i++){
        while(!flag){
            printf("\nScrivi il nome dell'oggetto\n");
            scanf(" %s", nome);
            //fitname=strdup(nome);
            if((invnum=invArray_searchByName(invArray, nome)) ==-1)
                printf("Errore: Oggetto non trovato\n");
            else
                flag=1;
        }
        printf("Inserimento (I) o rimozione (R) di un oggetto dall'equipaggiamento?\n");
        scanf(" %c", &check);
        switch (check){
            case 'I':
                if(equipArray_inUse(equipArray)<9){
                    equipArray->vettEq[ equipArray->qtUso ]=invnum;
                    equipArray->qtUso++;//indice di prima casella vuota (anche inesistente)
                }
                else
                    printf("Equipaggiamento pieno, prima rimuovere oggetti\n");
                break;

            case 'R':
                if(equipArray_inUse(equipArray)>0){
                    //elimina elemento e sposta tutto indietro
                    for(i=0; i<equipArray_inUse(equipArray) && !found; i++){
                        if(invArray_searchByName(invArray, nome)>-1){
                            found=1;
                            //elemento che contiene l'equip è all'indice i
                            for(j=i; j<equipArray_inUse(equipArray); j++){
                                //fino al penultimo elemento
                                equipArray->vettEq[j]=equipArray->vettEq[j+1];
                            }
                            equipArray->qtUso--;
                        }
                    }
                }
                else
                    printf("Equipaggiamento vuoto oppure equipaggiamento da rimuovere non trovato\n");
                break;
            default: printf("Comando non valido\n");
        }
    //}
    printf("Equipaggiamento corrente:");
    equipArray_print(stdout, equipArray, invArray);
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    return equipArray->vettEq[index];
}


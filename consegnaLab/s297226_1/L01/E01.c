#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 50

char *cercaRegexp(char *src, char *regexp);
int funzione(char *scelte,char confronto);
int main() {
    char src[MAX+1],regexp[MAX+1];
    char *pos=NULL; //dichiarazione di puntatore
    printf("scrivi src (dove cercare) e poi regexp (cosa cercare)\n");
    scanf("%s%s",src,regexp);
    pos=cercaRegexp(src,regexp);
    printf("Lettera inziale: %c\n",*pos);
    return 0;
}

char *cercaRegexp(char *src, char *regexp){
    int i=0, n=strlen(regexp), let=0, punt=0;
    char dentro[27]; //lettere dell'alfabeto
    int check, concorde,k, match=1;
    int save; //Local variable is only assigned but never accessed
    while(src[i]!='\0' || let+punt==n){
        if (i == 0 || !match)
            save = i; //The value is never used
        match=1;
        if (let+punt == n) {
            return &src[save];
            //correlazione tra i due warning sopra e il fatto che save viene usato?
            //rivedi puntatori
        }else if ((src[i] == regexp[let+punt]) || regexp[let+punt]=='.') {
            let++;
        }else{
            if(ispunct(regexp[let+punt])){
                if(regexp[let+punt]=='\\'){
                    if((regexp[let+punt+1]=='a' && islower(src[i])) || (regexp[let+punt+1]=='A' && isupper(src[i]))){
                        let++; punt++;
                    }else{
                        i=i-(let+punt); let=punt=0;
                    }
                }
                if(regexp[let+punt]=='['){
                    k=let+punt; check=0;
                    while(regexp[k]!=']'){
                        dentro[k-(let+punt)]=regexp[k];
                        k++;
                    }
                    if(regexp[let+punt+1]=='^'){
                        check=3;
                        concorde=funzione(&dentro[0],src[i]);
                    }else if (isalpha(regexp[let+punt+1])){
                        check=2;
                        concorde=funzione(&dentro[0],src[i]);
                    }
                    if(check!=concorde){
                        i=i-(let+punt); let=punt=0; match=0;
                    } else if (check==2 || check==3){
                        punt=punt+check;
                        let=k-punt+1;
                    }
                }
            }else{
                i=i-(let+punt); let=punt=0; match=0; //ricomincio
            }
        }
        i++;
    }
    return NULL;
}

int funzione( char *scelte,char confronto) {
    if (strchr(scelte, confronto)) {
        return 2;
    }
    return 3;
}

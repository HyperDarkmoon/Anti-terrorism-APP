#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct personnel {
    char login[50];
    char pw[50];
    int admin;
}personnel;

typedef struct alert {
    char name[50];
    char id[20];
    int critical;
}alert;

void fillArray(personnel T[],int n);
int connexion(personnel T[],int n);
void showArray(personnel T[], int n);
int addAlert(alert A[],int n);
int searchAlert(alert A[],int n);
void showAllAlerts(alert A[], int n);
int alertsPercentage(alert A[], int n);
void showSingleAlert(alert A[], int n);
int deleteAlert(alert A[], int n);
void modifyAlert(alert A[], int n);

int main() {
    personnel T[50];
    alert A[50];
    int n,x,choix,choice,na,pos,count,y;
    na=0;
    float percentage;
    printf("Donner le nombre de personnel a remplir\n");
    do {
        scanf("%d",&n);
    } while ((n<0));
    fillArray(T,n);
    do {
    system("cls");
    printf("Identifiez-vous (case sensitive):\n");
    x=connexion(T,n);
    printf("%d\n",x);
    switch (x) {
        case -1:
            printf("Utilisateur inexistant\n");
            break;
        case 1:
        do {
            do {
                system("cls");
                printf("1: Afficher Liste des alertes\n");
                printf("2: Pourcentage des alertes par rapport au total\n");
                scanf("%d",&choix);
                switch (choix) {
                    case 1:
                        showAllAlerts(A,na);
                        break;
                    case 2:
                        count=alertsPercentage(A,na);
                        percentage=((float)count/(float)na)*100;
                        printf("La pourcentage = %fPercent\n",percentage);
                        break;
                break;
                }
                printf("Voulez vous continuer?(1:Oui|2:Non)\n");
                scanf("%d",&y);
            } while (y!=0);
                printf("Voulez vous deconnecter?(1:Oui|2:Non)\n");
                scanf("%d",&y);
        } while (y!=1);
        case 2:
            do {
            do {
                system("cls");
                printf("1: Ajouter une nouvelle alerte\n");
                printf("2: Chercher une alerte et retourner sa position\n");
                printf("3: Afficher ou modifier ou supprimer une alerte\n");
                printf("4: Afficher la liste des alertes\n");
                scanf("%d",&choix);
                switch (choix) {
                    case 1:
                        na=addAlert(A,na);
                        break;
                    case 2:
                        pos=searchAlert(A,na);
                        if (pos!=-1) {
                            printf("La position de cet alert est %d\n",pos);
                        } else {
                            printf("Cet alert nexiste pas\n");
                        }
                        break;
                    case 3:
                        printf("Que voulez vous faire?\n");
                        printf("1:Afficher\n2:Modifier\n3:Supprimer\n");
                        scanf("%d",&choice);
                        switch (choice) {
                            case 1:
                                showSingleAlert(A,na);
                                break;
                            case 2:
                                modifyAlert(A,na);
                                break;
                            case 3:
                                na=deleteAlert(A,na);
                                break;
                        }
                            break;
                        break;
                    case 4:
                        showAllAlerts(A,na);
                        break;
                    break;
                }
            printf("Voulez vous continuer?(1:Oui|2:Non)\n");
            scanf("%d",&y);
        } while (y!=0);
            printf("Voulez vous deconnecter?(1:Oui|2:Non)\n");
                scanf("%d",&y);
        } while (y!=1);
    }
        printf("Voulez vous connectez de nouveau?(1:Oui|2:Non)\n");
        scanf("%d",&y);
    } while (y!=0);
}

void fillArray(personnel T[], int n) {
    int i;
    for (i=0;i<n;i++) {
        printf("Donner le login, Mdp et type d'utilisateur (1 si admin 2 si agent)\n");
        scanf("%s",&T[i].login);
        scanf("%s",&T[i].pw);
        do {
            scanf("%d",&T[i].admin);
        } while ((T[i].admin > 2) || (T[i].admin < 1));
    }
}

void showArray(personnel T[], int n) {
    int i;
    for (i=0;i<n;i++) {
        printf("Login:%s\nPassword:%s\nType:%d\n",T[i].login,T[i].pw,T[i].admin);
    }
}

int connexion(personnel T[],int n) {
    char log[50];
    char pass[50];
    int i;
    int test=0;
    int cnx=-1;
    scanf("%s",&log);
    for (i=0;i<n;i++) {
        if (strcmp(T[i].login,log)==0) {
            test=1;
            break;
        }
    }
    int tpw=0;
    int tries=0;
    if (test==1) {
        printf("Donnez votre mdp:\n");
        do {
            scanf("%s",&pass);
            i=0;
            do {
                if (strcmp(T[i].pw,pass)==0) {
                    tpw=1;
                }
                i++;
            } while ((tpw==0) && (i!=n));
            tries++;
        } while ((tpw==0) && (tries!=3));
    }
    if (tpw==1) {
        cnx=T[i-1].admin;
    }
    return(cnx);
}

int works(char id[]) {
    int i;
    int ok,ok2;
    ok=0;
    if ( (toupper(id[0])>='A') && (toupper(id[0])<='Z') && (toupper(id[1])>='A') && (toupper(id[1])<='Z') ) {
        ok=1;
    }
    ok2=1;
    for (i=2;i<strlen(id);i++) {
        if ( (id[i]>'9') || id[i]<'0') {
            ok2=0;
        }
    }
    return(ok&&ok2);
}

int addAlert(alert A[], int n) {
    char name[50];
    char id[50];
    int crit;
    printf("Donner le nom, l'Id du zone et si cest critique ou non (1: oui 0: non)\n");
    scanf("%s",&name);
    do {
        printf("Format de ID: 2 Lettres et 4 Chiffres\n");
        scanf("%s",&id);
    } while ((works(id)==0) || (strlen(id)!=6));
    do {
        scanf("%d",&crit);
    } while ((crit > 1) || (crit < 0));
    strcpy(A[n].name,name);
    strcpy(A[n].id,id);
    A[n].critical=crit;
    n++;
    return(n);
}

int searchAlert(alert A[],int n) {
    char idAlert[50];
    do {
        printf("Donner l'ID du zone que vous voulez trouver\n");
        scanf("%s",&idAlert);
    } while ((works(idAlert)==0) || (strlen(idAlert)>6));
    int save=-1,i;
    for (i=0;i<n;i++) {
        if (strcmp(idAlert,A[i].id)==0) {
            save=i;
        }
    }
    return(save+1);
}

void showAllAlerts(alert A[],int n) {
    int i;
    for (i=0;i<n;i++) {
        printf("Nom du zone:%s\nID du zone:%s\nType(1 critique, 0 non):%d\n",A[i].name,A[i].id,A[i].critical);
    }
}

void uppercase(char s[]) {
    for (int i=0;i<strlen(s);i++) {
        s[i]=toupper(s[i]);
    }
}

int alertsPercentage(alert A[], int n) {
    char name[50];
    int i,count;
    printf("Donner le nom du zone\n");
    scanf("%s",&name);
    count=0;
    uppercase(name);
    for (i=0;i<n;i++) {
        uppercase(A[i].name);
        if (strcmp(name,A[i].name)==0) {
            count++;
        }
        printf("%d\n",count);
    }
    return(count);
}

void showSingleAlert(alert A[], int n) {
    char id[50];
    int trouve=0,save,i;
    printf("Donner L'ID du alert a afficher\n");
    do {
        scanf("%s",&id);
    } while ((works(id)==0) || (strlen(id)!=6));
    for (i=0;i<n;i++) {
        if (strcmp(id,A[i].id)==0) {
            trouve=1;
            save=i;
        }
    }
    if (trouve==1) {
        printf("Nom du zone:%s\nID du zone:%s\nType(1 critique, 0 non):%d\n",A[save].name,A[save].id,A[save].critical);
    } else {
        printf("Non existant\n");
    }
}

int deleteAlert(alert A[], int n) {
    char id[50];
    int trouve=0,save,i;
    printf("Donner L'ID du alert a chercher\n");
    do {
        scanf("%s",&id);
    } while ((works(id)==0) || (strlen(id)!=6));
    int j;
    for (i=0;i<n;i++) {
        if (strcmp(id,A[i].id)==0) {
            j=i;
        }
    }
    for (i=j;i<n-1;i++) {
        A[i]=A[i+1];
    }
    n--;
    return(n);
}

void modifyAlert(alert A[], int n) {
    char id[50];
    int choix,i,level,savepos;
    alert save;
    char name[50];
    printf("Donner L'ID du alert a chercher\n");
    do {
        scanf("%s",&id);
    } while ((works(id)==0) || (strlen(id)!=6));
    do {
        printf("Que voulez vous modifier?\n1:Nom\n2:ID\n3:Niveau du critique\n");
        scanf("%d",&choix);
    } while ((choix > 3) || (choix < 1));
    for (i=0;i<n;i++) {
        if (strcmp(id,A[i].id)==0) {
            save=A[i];
            savepos=i;
        }
    }
    switch (choix) {
        case 1:
            printf("Donner le nouveau nom\n");
            scanf("%s",&name);
            strcpy(save.name,name);
            break;
        case 2:
            printf("Donner le nouveau id (Format standard)\n");
            do {
            scanf("%s",&id);
            } while ((works(id)==0) || (strlen(id)!=6));
            strcpy(save.id,id);
            break;
        case 3:
            printf("Donner le nouveau niveau de critique (1 ou 0)\n");
            do {
                scanf("%d",level);
            }   while ((level > 1) || (level < 0));
            save.critical=level;
            break;
    }
    A[savepos]=save;
}

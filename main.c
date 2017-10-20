#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "GMV5.h"


//Fonction qui permet la lecture d'un message.

void read_msg(char **ppMsg)
{
    printf("Message : ");

    char sUserInput[255];

    fflush(stdin);
    fgets(sUserInput, 255, stdin);

    *ppMsg = malloc((strlen(sUserInput) + 1) * sizeof(char));

    strcpy(*ppMsg, sUserInput);
}

/*  Vérifie si l'action est un NOMBRE compris entre 1 et le nombre de possibilités
    permises (dNPos) */

void action(int *dAction, int dNPos)
{
    char sAction[20];

    do
    {
        fflush(stdin);
        fgets(sAction, 20, stdin);

        if (strlen(sAction) > 2)
        {
            printf("Too many characters , try again!\n");
            continue;
        }

        *dAction = atoi(sAction);

        if(*dAction < 1 || *dAction > dNPos)
        {
            printf("Wrong Number!\nTry again\n");
        }

    } while(*dAction < 1 || *dAction > dNPos);
}

void ask_msgh_and_check_if_exist(int dMsgHCount, int *n)
{
    do
    {
        printf("Message handler number?\n");

        // Test si l'entrée est bien un integer.

        if(scanf("%d", n) != 1)
        {
            printf("Wrong input.Try again.\n");
            fflush(stdin); // Evite une boucle infinie si l'entrée est différente d'un integer.
            continue;
        }

        // Test si le nombre entré correspond a un gestionnaire de message existant déjà.

        if(*n >= dMsgHCount)
        {
            printf("msgH(%d) doesn't exist yet!\nTry again\n", *n);
        }
    }
    while(*n >= dMsgHCount);
}

int main()
{
    char *pMsg = NULL;
    int dAction, n; //n sera le numéro du gestionnaire de messages.
    int i = 0;
    int dMsgHCount = 0;
    bool stop = false;
    MsgHandler **msgH = NULL;


    program_init(1);

    //Boucle infinie pour pouvoir tester mon module GMv4.

    while(!stop)
    {
        if(i == 0)
        {
            printf("What to do?\n\
               1.Initialize a message handler.\n");
            action(&dAction, 1);
        }
        else
        {
            printf("What to do?\n\
               1.Initialize a message handler.\n\
               2.Reinitialize a message handler.\n\
               3.Add messages to a message handler.\n\
               4.Display messages for a specific message handler.\n\
               5.Stop program.\n");
            action(&dAction, 5);
        }

        switch(dAction)
        {
            case 1 :
                if(dMsgHCount == 0)
                {
                    msgH = malloc(sizeof(MsgHandler*));
                }
                else
                {
                    MsgHandler **ptemp = realloc(msgH, (dMsgHCount + 1) * sizeof(MsgHandler*));
                    if(!ptemp)
                    {
                        printf("Erreur realloc msgH(%d)\n", dMsgHCount);
                    }
                    else
                    {
                        msgH = ptemp;
                    }
                }
                msgH[dMsgHCount] = NULL;
                msgH[dMsgHCount] = msgh_init(msgH[dMsgHCount]);
                if(msgH[dMsgHCount] != NULL)
                {
                    printf("msgH(%d) initialized!\n", dMsgHCount);
                }
                else
                {
                    printf("Error occured when trying to initialize msgH(%d)\n", dMsgHCount);
                }
                dMsgHCount++;
                break;
            case 2 :
                ask_msgh_and_check_if_exist(dMsgHCount, &n);
                msgH[n] = msgh_init(msgH[n]);
                if(msgH[n] != NULL)
                {
                    printf("msgH(%d) reinitialized!\n", n);
                }
                else
                {
                    printf("Error occured when trying to reinitialize msgH(%d)", n);
                }
                break;
            case 3 :
                ask_msgh_and_check_if_exist(dMsgHCount, &n);
                printf("Enter 1 to stop input\n");
                while(1)
                {
                    read_msg(&pMsg);
                    if(pMsg[0] == '1')
                    {
                        break;
                    }
                    if(msg_add(msgH[n], pMsg) == MH_ERROR)
                    {
                        printf("Error occured when trying to add a message to msgH(%d)", n);
                    }
                }
                break;
            case 4 :
                ask_msgh_and_check_if_exist(dMsgHCount, &n);
                printf("1.Display all messages\n\
                        2.Unread messages only\n\
                        3.Already read messages only.\n");
                action(&dAction, 3);
                switch(dAction)
                {
                    case 1 :
                        if(msg_display(msgH[n], MSG_ALL) == MH_ERROR)
                        {
                            printf("Error occured when trying do display all messages in msgH(%d)", n);
                        }
                        break;
                    case 2 :
                        if(msg_display(msgH[n], MSG_NOT_READ) == MH_ERROR)
                        {
                            printf("Error occured when trying do display unread messages in msgH(%d)", n);
                        }
                        break;
                    case 3 :
                        if(msg_display(msgH[n], MSG_READ) == MH_ERROR)
                        {
                            printf("Error occured when trying do display already read messages in msgH(%d)", n);
                        }
                        break;
                    default :
                        printf("Wrong number!\nTry again");
                }
                break;
            case 5 :
                stop = true;
                break;
            default :
                printf("Wrong number!\n");

        }
        i++;
    }

    for(i = 0 ; i < dMsgHCount ; i++)
    {
        free_msgh(msgH[i]);
    }
    free(msgH);

    program_display_trace();
}

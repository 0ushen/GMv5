#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "GMv5.h"
#include "GMv5_trace_codes.h"
#include "date_and_time.h"
#include "LDCv2.h"


struct MsgHandler_t
{
    DLL *dLL;
    bool isInit; // true -> le gestionnaire de message a été initialisé.
};

int dTraceLevel; // Niveau de tracage 1=complet 0=inexistant

void program_init(int dUserTraceLevel)
{
    dTraceLevel = dUserTraceLevel;

    if(dTraceLevel >= 1)
    {
        char *logFile = current_date(); /* current_date() renvoi l'adresse d'une chaine de caractères
                                           contenant la date actuelle au format AAAA MM JJ. */
        char *currentTime = current_time(); /* current_time() renvoi l'adresse d'une chaine de caractères
                                               contenant l'heure actuelle au format hh:mm:ss. */

        FILE* eventlogs = fopen(logFile, "a+");
        free(logFile);
        if(eventlogs != NULL)
        {
            fputs("\n\nNEW SESSION : ", eventlogs);
            fputs(currentTime, eventlogs);
            free(currentTime);
            fputs("\n", eventlogs);
            printf("Logs created.\n");
            fclose(eventlogs);
        }
        else
        {
            printf("Error : can't open logfile in program_init(), no logs created...\n");
        }
    }
}

// Fonction qui ajoute chaque message d'erreur généré par le module dans les logs selon le niveau de tracage.

static void program_trace(char *pMsg, int dLevelMsg)
{
    if(dTraceLevel >= dLevelMsg)
    {
        char *logFile = current_date();
        char *currentTime = current_time();

        FILE* eventlogs = fopen(logFile, "a+");
        free(logFile);
        if(eventlogs != NULL)
        {
            fputs(currentTime, eventlogs);
            free(currentTime);
            fputs(" ", eventlogs);
            fputs(pMsg, eventlogs);
            fputs("\n", eventlogs);
            fclose(eventlogs);
        }
        else
        {
            printf("Error : can't open log file in program_trace()");
        }
    }
}

/* Fonction qui affiche ligne par ligne le texte contenu dans le fichier logFile
   jusqu'à la fin du texte (donc quand fgets() rencontre EOF et renvoi alors un pointeur NULL) . */

void program_display_trace()
{
    char *logFile = current_date();
    char string[150] = "";

    FILE* eventlogs = fopen(logFile, "r");
    free(logFile);
    if(eventlogs != NULL)
    {
        while(fgets(string, 150, eventlogs) != NULL)
        {
            printf("%s", string);
        }
        fclose(eventlogs);
    }
    else
    {
        printf("Error : can't open logfile in program_display_trace().\n");
    }
}

void free_msgh(MsgHandler *msgH)
{
    free_dll(msgH->dLL);
    free(msgH);
}

MsgHandler* msgh_init(MsgHandler *msgH)
{
    program_trace(MH000I, 1);

    /* Si le pointeur passé en paramètre est NULL, on crée de l'espace pour
       un gestionnaire de messages via malloc().
       Si il contient une adresse c'est que la fonction a été appellée pour
       une réinitialisation, donc on efface les données contenues dans ce gestionnaire
       de messages et on en crée un nouveau. */

    if(msgH == NULL)
    {
        msgH = malloc(sizeof(MsgHandler));
        if (msgH == NULL)
        {
            program_trace(MH000E, 1);
        }
    }
    else
    {
        free_msgh(msgH);
        msgH = malloc(sizeof(MsgHandler));
        if (msgH == NULL)
        {
            program_trace(MH001E, 1);
        }
    }

    //Initialisation des valeurs du gestionnaire de messages.

    msgH->isInit = true;

    // Création d'une liste doublement chainées pour pouvoir y stocker les messages.

    msgH->dLL = NULL;
    msgH->dLL = dll_init(msgH->dLL);
    if(msgH->dLL == NULL)
    {
        program_trace(MH002E, 1);
        return MH_ERROR;
    }

    program_trace(MH001I, 1);

    return msgH;
}

//Fonction qui ajoute un message à la position courante dans le gestionnaire de messages.

int msg_add(MsgHandler *msgH, char *pMsg)
{
    program_trace(MH020I, 1);

    // Je vérifie si ce gestionnaire de messages a été préalablement initialisé.

    if(msgH->isInit != true)
    {
        program_trace(MH020E, 1);
        return MH_ERROR;
    }


    // Ajout du message dans la liste doublement chaînées.

    if(dll_add(msgH->dLL, pMsg) == DLL_OK)
    {
        program_trace(MH024I, 1);
    }
    else
    {
        program_trace(MH023E, 1);
        return MH_ERROR;
    }

    return MH_OK;

}

//Fonction qui affiche les messages enregistrés dans le gestionnaire de messages.

int msg_display(MsgHandler *msgH, int msgStatus)
{
    program_trace(MH030I, 1);

    // Je vérifie si ce gestionnaire de messages a été préalablement initialisé.

    if(msgH->isInit != true)
    {
        program_trace(MH030E, 1);
        return MH_ERROR;
    }

    // Fcontion d'affichage d'un message à passer en argument à la fonction dll_display().

    void display_message(void* pData)
    {
        char *pMsg = pData;

        printf("%s\n", pMsg);
    }

    //  Affichage des messages contenu dans la liste doublement chaînée.

    if(dll_display(msgH->dLL, msgStatus, ASC, display_message) == DLL_OK)
    {
        program_trace(MH031I, 1);
    }
    else
    {
        program_trace(MH031E, 1);
    }

    return MH_OK;
}

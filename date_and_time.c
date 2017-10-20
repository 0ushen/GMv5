#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* current_date()
{
    // time_t est le type de variable appropri� pour stocker le temps �coul�.

    time_t rawtime;

    /* info est un pointeur vers une structure de type tm, c'est un structure
       utilis�e pour stocker le temps sous format calendrier. */

    struct tm *info;

    /* time() calcule le temps �coul� (en secondes) depuis le 1er janvier 1970 puis
       le stocke dans la variable rawtime */

    time(&rawtime);

    /* localtime() rempli une structure tm via un temps donn� en secondes et en prenant
       compte du fuseau horaire local */

    info = localtime(&rawtime);

    // currentDate sera la cha�ne de caract�re contenant la date actuelle.

    char* currentDate = malloc(20 * sizeof(char));

    /* strftime stocke dans une chaine de caract�res (param1) au maximum 20 caract�res (param2)
       le temps contenu dans la structure de type tm (param4) sous un format qui doit �tre sp�cifi�
       (param3).
       Pour plus d'informations : https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm */

    strftime(currentDate,20,"%Y %m %d", info);

    return currentDate;
}

char* current_time()
{
    time_t rawtime;
    struct tm *info;

    time(&rawtime);
    info = localtime(&rawtime);

    char* currentTime = malloc(20 * sizeof(char));

    strftime(currentTime,20,"%H:%M:%S", info);

    return currentTime;
}

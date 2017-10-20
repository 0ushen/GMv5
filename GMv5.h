/**
 * GMv4.h
 *
 * auteur : Samir Benlafya
 */


/**
 * MH_OK
 *
 * return code si la fonction s'est effectu�e correctement.
 */
#define MH_OK 1

/**
 * MH_ERROR
 *
 * return code si il y a eu une erreur dans la fonction.
 */
#define MH_ERROR 0

/**
 * MSG_ALL
 *
 * d�finit un param�tre "tous les messages"
 */
#define MSG_ALL 2

/**
 * MSG_READ
 *
 * d�finit un param�tre "message lus uniquement"
 */
#define MSG_READ 1

/**
 * MSG_NOT_READ
 *
 * d�finit un param�tre "messages non lus uniquement"
 */
#define MSG_NOT_READ 0

typedef struct MsgHandler_t MsgHandler;

/**
 * program_init : proc�de � l'ensemble des initialisations sp�cifiques du module.
 *                A FAIRE EN PREMIER LIEU AVANT TOUTE MANIPULATION DU MODULE.
 *
 * @param dUserTraceLevel : niveau de tracage 1=complet 0=inexistant
 */
void program_init(int dUserTraceLevel);

/**
 * program_display_trace : affiche les logs.
 */
void program_display_trace();

/**
 * free_msgh : efface un gestionnaire de messages en lib�rant la m�moire.
 *             !!!A UTILISER POUR CHAQUE GESTIONNAIRE DE MESSAGES CREE UNE FOIS
 *             QU'ON EN A PLUS BESOIN SOUS PEINE DE FUITES MEMOIRES!!!
 */
void free_msgh(MsgHandler *msgH);

/**
 * msgh_init : (Re)Initialise un gestionnaire de messages.
 *
 *
 * @param *msgH : gestionnaire de message sur lequel la manipulation sera effectu�e.
 *
 * @return : adresse du gestionnaire de messages.
 */
MsgHandler* msgh_init(MsgHandler *msgH);

/**
 * msg_add : Ajoute un message dans le gestionnaire de messages sp�cifi�.
 *
 * @param pMsg : le message � stocker.
 * @param *msgH : gestionnaire de message sur lequel la manipulation sera effectu�e.
 *
 * @return : GM_OK ou GM_ERROR
 */
int msg_add(MsgHandler *msgH, char *pMsg);

/**
 * msg_display : Affiche les messages d'un gestionnaire de messages sp�cifi�.
 *
 * @param msgStatus : sp�cifie le type de messages � afficher (lu ou non ou les deux).
 * @param *msgH : gestionnaire de message sur lequel la manipulation sera effectu�e.
 *
 * @return : GM_OK ou GM_ERROR
 */
int msg_display(MsgHandler *msgH, int msgStatus);

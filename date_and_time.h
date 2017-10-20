/**
 *date_and_time.h
 *
 * auteur : Samir Benlafya
 */

/**
 * current_date() : calcule la date actuelle puis la stocke sous forme de chaîne de
 *                  caractères au format ANNEE MOIS JOUR.
 *
 * @return adresse à laquelle la date actuelle est stockée sous forme de chaîne de
 *         caractères.
 *
 * ATTENTION : Libérer l'adresse via un free() une fois qu'on a plus besoin de la chaîne.
 */
 char* current_date();

 /**
 * current_time() : calcule l'heure locale puis la stocke sous forme de chaîne de
 *                  caractères au format HEURE:MINUTE:SECONDE.
 *
 * @return adresse à laquelle l'heure actuelle est stockée sous forme de chaîne de
 *         caractères.
 *
 * ATTENTION : Libérer l'adresse via un free() une fois qu'on a plus besoin de la chaîne.
 */
 char* current_time();

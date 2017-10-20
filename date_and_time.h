/**
 *date_and_time.h
 *
 * auteur : Samir Benlafya
 */

/**
 * current_date() : calcule la date actuelle puis la stocke sous forme de cha�ne de
 *                  caract�res au format ANNEE MOIS JOUR.
 *
 * @return adresse � laquelle la date actuelle est stock�e sous forme de cha�ne de
 *         caract�res.
 *
 * ATTENTION : Lib�rer l'adresse via un free() une fois qu'on a plus besoin de la cha�ne.
 */
 char* current_date();

 /**
 * current_time() : calcule l'heure locale puis la stocke sous forme de cha�ne de
 *                  caract�res au format HEURE:MINUTE:SECONDE.
 *
 * @return adresse � laquelle l'heure actuelle est stock�e sous forme de cha�ne de
 *         caract�res.
 *
 * ATTENTION : Lib�rer l'adresse via un free() une fois qu'on a plus besoin de la cha�ne.
 */
 char* current_time();

/*-----------------------------------------------------------------------------------
Nom du fichier       : Labo_02_Taxi_j.cpp
Auteur(s) 		      : Kevin Auberson & Nicolas Carbonara
Modification         : Delétraz Alexandre - Drompt Laurie
Date creation 	      : 07.10.2022
Date de modification : 12.10.2022
Description 	      : Calcule le prix d’une course d'un taxi
Remarque(s) 	      : Le programme ne gère pas les erreurs de saisie (caractères
                       spéciaux et lettres).
                       Le programme traite les valeurs incorrectes (hors champ).
                       Dans un tel cas, le programme s'interrompt et affiche un
                       message d'erreur.
Compilateur 	      : Mingw-w64 g++ 12.1.0
-----------------------------------------------------------------------------------*/

#include <iomanip>	// setw(...) et setprecision(...)
#include <cstdlib>	// EXIT_SUCCESS
#include <iostream> // cout et cin
#include <limits>	// numeric_limits<streamsize>

#define CLEAR_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

using namespace std;

int main()
{
   //-------------------------------------------------------------
   // Initializing constants
   //-------------------------------------------------------------
   // Prices
   const double PRICE_TAX_BASE     = 5.00;
   const double PRICE_TAX_BAG      = 2.60;
   const double PRICE_MINUTE_DAY   = 1.00;
   const double PRICE_MINUTE_NIGHT = 1.60;
   const int 	 HOURS_BEGIN_DAY    = 8;
   const int 	 HOURS_FINISH_DAY   = 20;

   // Others
   const int 	 WIDTH              = 8;
   const int	 WIDTHTOTALPRICE    = 26;

   //-------------------------------------------------------------
   // Initializing variables
   //-------------------------------------------------------------

   // Others
   bool   checkMistake = true;

   // Setting the precision of the output and aligns it to the left
   cout << fixed << setprecision(2) << left;

   //-------------------------------------------------------------
   //                          Welcome
   //-------------------------------------------------------------
   cout << "Bonjour, ce programme permet de calculer le prix d'une"      << endl
        << " course de taxi."                                            << endl
        << "Lorsque'il vous sera demander l'heure de depart, veuilliez"  << endl
        << "saisir l'heure en format hh:mm."                             << endl
        << "Voici les conditions      "                                  << endl
        << "=========================="                                  << endl
        << " - prise en charge  : " << setw(WIDTH) << PRICE_TAX_BASE 	    << endl
        << " - supp par bagage  : " << setw(WIDTH)	<< PRICE_TAX_BAG 		<< endl
        << " - tarif/min (jour) : " << setw(WIDTH)	<< PRICE_MINUTE_DAY 	<< endl
        << " - tarif/min (nuit) : " << setw(WIDTH)	<< PRICE_MINUTE_NIGHT   << endl
        << " - heures de jour   : " << "["         << HOURS_BEGIN_DAY    << " - "
        << HOURS_FINISH_DAY         << "]"         << endl               << endl;

   //-------------------------------------------------------------
   // Ask the user to enter their order
   //-------------------------------------------------------------

   const int HOUR_TO_MINUTE = 60;
   const int MINUTES_IN_DAY = 24 * HOUR_TO_MINUTE;

   // Users inputs
   int    numberBag;
   int    distanceTrip;
   int    averageSpeed;
   int    hourBegin;
   int    minuteBegin;
   int    depTimeInMinutes;
   // Prices
   double BagTotal;
   double tripTotal;
   double finalTotal;

   // Users min/max inputs
   const int 	 MIN_BAG   = 0;
   const int 	 MAX_BAG   = 4;
   const int 	 MIN_KM    = 0;
   const int 	 MAX_KM	  = 500;
   const int 	 MIN_SPEED = 50;
   const int 	 MAX_SPEED = 120;


   cout << "Votre commande"         << endl
        << "=============="         << endl
        << "- nbre de bagage     [" << MIN_BAG << " - " << MAX_BAG << "] : ";
   cin  >> numberBag;
   CLEAR_BUFFER;

   // Check if the number of bag is between MIN_BAG and MAX_BAG
   if (numberBag >= MIN_BAG and numberBag <= MAX_BAG)
   {
      BagTotal = PRICE_TAX_BAG * numberBag;

      cout << "- distance [km]    [" << MIN_KM << " - " << MAX_KM << "] : ";
      cin  >> distanceTrip;
      CLEAR_BUFFER;

      // check if the distance is between MIN_KM and MAX_KM
      if (distanceTrip >= MIN_KM and distanceTrip <= MAX_KM)
      {
         cout << "- vitesse         [" << MIN_SPEED << " - " << MAX_SPEED << "] : ";
         cin  >> averageSpeed;
         CLEAR_BUFFER;

         // check if the speed is between MIN_SPEED and MAX_SPEED
         if (averageSpeed >= MIN_SPEED and averageSpeed <= MAX_SPEED)
         {
            cout << "- depart            [hh:mm] : ";
            cin  >> hourBegin >> minuteBegin;
            depTimeInMinutes = hourBegin * HOUR_TO_MINUTE + minuteBegin;
            // Insert a blank line for a better reading on the output
            cout << endl;
            CLEAR_BUFFER;

            double travelTimeInMinutes = double(distanceTrip) / averageSpeed *
                                         HOUR_TO_MINUTE;
            // IF start hour is between the hour of the day then take day prices
            if (depTimeInMinutes >= HOURS_BEGIN_DAY  * HOUR_TO_MINUTE and
                depTimeInMinutes <  HOURS_FINISH_DAY * HOUR_TO_MINUTE)
            {
               if (depTimeInMinutes + travelTimeInMinutes > HOURS_FINISH_DAY
                  * HOUR_TO_MINUTE)
               {
                  tripTotal = (depTimeInMinutes  + travelTimeInMinutes -
                              HOURS_FINISH_DAY   * HOUR_TO_MINUTE)     *
                              PRICE_MINUTE_NIGHT +

                              (HOURS_FINISH_DAY  * HOUR_TO_MINUTE      -
                              depTimeInMinutes)  * PRICE_MINUTE_DAY;
               }
               else
               {
                  // Casting to double to avoid integer division
                  tripTotal = travelTimeInMinutes * PRICE_MINUTE_DAY;
               }
            }
            // else take night prices
            else if (depTimeInMinutes >= HOURS_FINISH_DAY * HOUR_TO_MINUTE or
                     depTimeInMinutes <  HOURS_BEGIN_DAY  * HOUR_TO_MINUTE)
            {
               if (depTimeInMinutes + travelTimeInMinutes >= HOURS_BEGIN_DAY * HOUR_TO_MINUTE) {
                   tripTotal = (depTimeInMinutes  + travelTimeInMinutes -
                                HOURS_BEGIN_DAY   * HOUR_TO_MINUTE)     *
                               PRICE_MINUTE_NIGHT +

                               (HOURS_BEGIN_DAY  * HOUR_TO_MINUTE      -
                                depTimeInMinutes)  * PRICE_MINUTE_DAY;

               }

               else if (depTimeInMinutes > MINUTES_IN_DAY)
               {
                  tripTotal = (MINUTES_IN_DAY - depTimeInMinutes + travelTimeInMinutes
                               - HOURS_BEGIN_DAY) * PRICE_MINUTE_DAY +

                              (HOURS_BEGIN_DAY + depTimeInMinutes - MINUTES_IN_DAY) *
                              PRICE_MINUTE_NIGHT;
               }

               else if (depTimeInMinutes == MINUTES_IN_DAY)
               {
                  tripTotal = (travelTimeInMinutes - HOURS_BEGIN_DAY) *
                              PRICE_MINUTE_DAY +
                              (HOURS_BEGIN_DAY) * PRICE_MINUTE_NIGHT;
               }

               else
               {
                  // Casting to double to avoid integer division
                  tripTotal = travelTimeInMinutes * PRICE_MINUTE_NIGHT;
               }
            }
            else
            {	cout << "Erreur : l'heure de depart doit etre comprise entre "
                        "0 et 23" << endl;
               checkMistake = false;
            }
         }
         else
         {
            cout << "Erreur : la vitesse doit etre comprise entre "
                 << MIN_SPEED << " et " << MAX_SPEED << endl;
            checkMistake = false;
         }
      }
      else
      {
         cout << "Erreur : la distance doit etre comprise entre "
              << MIN_KM << " et " << MAX_KM << endl;
         checkMistake = false;
      }
   }
   else
   {
      cout << "Erreur : le nombre de bagage doit etre compris entre "
           << MIN_BAG << " et " << MAX_BAG << endl;
      checkMistake = false;
   }

   //-------------------------------------------------------------
   // If all values are correct, calculate the total
   //-------------------------------------------------------------
   if (checkMistake)
   {
      finalTotal = PRICE_TAX_BASE + BagTotal + tripTotal;

      cout << "votre Ticket"        << endl
           << "============"        << endl
           << " - prise en charge  	: "           << setw(WIDTH) << right
           << PRICE_TAX_BASE        << endl
           << " - supp bagages    	: "           << setw(WIDTH) << right
           << BagTotal              << endl
           << " - prix de la course 	: "        << setw(WIDTH) << right
           << tripTotal 	         << endl
           << setw(WIDTHTOTALPRICE) << "TOTAL : " << setw(WIDTH) << right
           << finalTotal 			   << endl;
   }

   //-------------------------------------------------------------
   // End of program
   //-------------------------------------------------------------
   cout << "Presser ENTRER pour quitter";
   CLEAR_BUFFER;

   /* Chose considérée comme des erreurs :
    * - utilisé des tabulations au lieu d'espace (corrigé)
    * - Faire un bitwise au lieu d'un et logique (corrigé)
    * - imbriqué autant de if pour les tests
    * */

   /*
    * Travail à faire :
    * Gérer le changement de tarif durant le trajet
    *
    * Gérer la saisie de l'heure au format hh.mm. (Normalement bon).
    *
    */


   return EXIT_SUCCESS;
}
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

#include <iomanip>  // setw(...) et setprecision(...)
#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // cout et cin
#include <limits>	  // numeric_limits<streamsize>
#include <string>   // to work with strings

#define CLEAR_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

using namespace std;

int main()
{
   //-------------------------------------------------------------
   //                  Initializing constants
   //-------------------------------------------------------------
   // Prices
   const double PRICE_TAX_BASE     = 5.00;
   const double PRICE_TAX_BAG      = 2.60;
   const double PRICE_MINUTE_DAY   = 1.00;
   const double PRICE_MINUTE_NIGHT = 1.60;
   const int 	 HOURS_BEGIN_DAY    = 8;
   const int 	 HOURS_FINISH_DAY   = 20;

   //Text messages.

   const string WELCOME_MSG      = "\nBonjour, ce programme permet de calculer\n"
                                     "le prix d'une course de taxi.\n"
                                     "Lorsqu'il vous sera demander l'heure\n"
                                     "de depart, veuillez saisir l'heure en format"
                                     " hh:mm.\n"
                                     "Voici les conditions      "s;
   const string TAX_BASE_MSG     = " - prise en charge  : "s;
   const string TAX_BAG_MSG      = " - supp par bagage  : "s;
   const string PRICE_DAY_MSG    = " - tarif/min (jour) : "s;
   const string PRICE_NIGHT_MSG  = " - tarif/min (nuit) : "s;
   const string DAY_SCHEDULE_MSG = " - heures de jour   : "s;
   const string BAG_ERROR_MSG    = "Erreur : le nombre de bagage doit etre compris"
                                   " entre "s;
   const string DIST_ERROR_MSG   = "Erreur : la distance doit etre comprise entre "s;
   const string SPEED_ERROR_MSG  = "Erreur : la vitesse doit etre comprise entre "s;
   const string TIME_ERROR_MSG   = "Erreur : l'heure de depart doit etre comprise "
                                   "entre "s;
   const string ORDER_MSG        = "Votre commande"s;
   const string BAG_ORDER_MSG    = "- nbre de bagage     "s;
   const string DIST_ORDER_MSG   = "- distance [km]    "s;
   const string FRENCH_AND       = " et "s;
   const string SPEED_ORDER_MSG  = "- vitesse         "s;
   const string DEP_ORDER_MSG    = "- depart            "s;
   const string TIME_FORMAT_MSG  = "[hh:mm]"s;
   const string TICKET_MSG       = "Votre ticket"s;
   const string EXIT_MSG         = "Presser ENTRER pour quitter"s;
   const string TICKET_BASE_MSG  = " - prise en charge  	: "s;
   const string TICKET_BAG_MSG   = " - supp bagages    	: "s;
   const string TICKET_PRICE_MSG = " - prix de la course 	: "s;
   const string TICKET_TOTAL_MSG = "TOTAL : "s;
   const string LAST_HOUR        = "23:59"s;

   //Symboles
   const string OPEN_INTER_SYMB          = "["s;
   const string CLOSE_INTER_SYMB         = "]"s;
   const string WELCOME_SEPARATION_SYM   = "=========================="s;
   const string MID_VALUE_SEPARATION_SYM = " - "s;
   const string ORDER_SEPARATION_SYM     = "=============="s;
   const string DOUBLE_DOT               = " : "s;
   const string TICKET_SEPARATION_SYM    = "============"s;


   // Others
   const int 	 WIDTH              = 8;
   const int	 WIDTHTOTALPRICE    = 26;

   // Setting the precision of the output and aligns it to the left.
   cout << fixed << setprecision(2) << left;

   //-------------------------------------------------------------
   //                          Welcome
   //-------------------------------------------------------------
   cout << WELCOME_MSG            << endl
        << WELCOME_SEPARATION_SYM << endl
        << TAX_BASE_MSG           << setw(WIDTH)      << PRICE_TAX_BASE     << endl
        << TAX_BAG_MSG            << setw(WIDTH)      << PRICE_TAX_BAG      << endl
        << PRICE_DAY_MSG          << setw(WIDTH)      << PRICE_MINUTE_DAY   << endl
        << PRICE_NIGHT_MSG        << setw(WIDTH)      << PRICE_MINUTE_NIGHT << endl
        << DAY_SCHEDULE_MSG       << OPEN_INTER_SYMB  << HOURS_BEGIN_DAY    << MID_VALUE_SEPARATION_SYM
        << HOURS_FINISH_DAY       << CLOSE_INTER_SYMB << endl               << endl;

   //-------------------------------------------------------------
   //                       Order section
   //-------------------------------------------------------------

   const int HOUR_TO_MINUTE = 60;
   const int MINUTES_IN_DAY = 24 * HOUR_TO_MINUTE;

   // Users inputs.
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

   // Users min/max inputs.
   const int MIN_BAG     = 0;
   const int MAX_BAG     = 4;
   const int MIN_KM      = 0;
   const int MAX_KM	    = 500;
   const int MIN_SPEED   = 50;
   const int MAX_SPEED   = 120;
   const int FIRST_HOUR  = 0;

   cout << ORDER_MSG            << endl
        << ORDER_SEPARATION_SYM << endl
        << BAG_ORDER_MSG        << OPEN_INTER_SYMB
        << MIN_BAG              << MID_VALUE_SEPARATION_SYM << MAX_BAG
        << CLOSE_INTER_SYMB     << DOUBLE_DOT;
   cin  >> numberBag;
   CLEAR_BUFFER;

   // Check if the number of bag is between MIN_BAG and MAX_BAG.
   if (numberBag >= MIN_BAG and numberBag <= MAX_BAG)
   {
       BagTotal = PRICE_TAX_BAG * numberBag;
   }
   else
   {
       cout << BAG_ERROR_MSG << MIN_BAG << FRENCH_AND << MAX_BAG << endl;
       return EXIT_FAILURE;
   }

   cout << DIST_ORDER_MSG   << OPEN_INTER_SYMB
        << MIN_KM           << MID_VALUE_SEPARATION_SYM << MAX_KM
        << CLOSE_INTER_SYMB << DOUBLE_DOT;
   cin  >> distanceTrip;
   CLEAR_BUFFER;
   // check if the distance is between MIN_KM and MAX_KM.
   if (!(distanceTrip >= MIN_KM and distanceTrip <= MAX_KM))
   {
      cout << DIST_ERROR_MSG << MIN_KM << FRENCH_AND << MAX_KM << endl;
      return EXIT_FAILURE;
   }

   cout << SPEED_ORDER_MSG  << OPEN_INTER_SYMB
        << MIN_SPEED        << MID_VALUE_SEPARATION_SYM << MAX_SPEED
        << CLOSE_INTER_SYMB << DOUBLE_DOT;
   cin  >> averageSpeed;
   CLEAR_BUFFER;

   // check if the speed is between MIN_SPEED and MAX_SPEED.
   if (!(averageSpeed >= MIN_SPEED and averageSpeed <= MAX_SPEED))
   {
      cout << SPEED_ERROR_MSG << MIN_SPEED << FRENCH_AND << MAX_SPEED << endl;
      return EXIT_FAILURE;
   }

   cout << DEP_ORDER_MSG << TIME_FORMAT_MSG << DOUBLE_DOT;
   cin  >> hourBegin     >> minuteBegin;
   depTimeInMinutes = hourBegin * HOUR_TO_MINUTE + minuteBegin;
   // Insert a blank line for a better reading on the output.
   cout << endl;
   CLEAR_BUFFER;

   if (depTimeInMinutes < FIRST_HOUR or depTimeInMinutes >= MINUTES_IN_DAY)
   {
      cout << TIME_ERROR_MSG << OPEN_INTER_SYMB
           << FIRST_HOUR     << MID_VALUE_SEPARATION_SYM << LAST_HOUR
           << CLOSE_INTER_SYMB;

      return EXIT_FAILURE;
   }

   double travelTimeInMinutes = double(distanceTrip) / averageSpeed * HOUR_TO_MINUTE;
   // IF start hour is between the hour of the day then take day prices
   if (depTimeInMinutes >= HOURS_BEGIN_DAY  * HOUR_TO_MINUTE and
       depTimeInMinutes <  HOURS_FINISH_DAY * HOUR_TO_MINUTE)
   {
      if (depTimeInMinutes + travelTimeInMinutes > HOURS_FINISH_DAY
          * HOUR_TO_MINUTE)
      {
         tripTotal =  //calculates the time that exceeds the night.
                      (depTimeInMinutes   + travelTimeInMinutes -
                      HOURS_FINISH_DAY   * HOUR_TO_MINUTE)     *
                      PRICE_MINUTE_NIGHT +
                      //calculate the time which is in days.
                      (HOURS_FINISH_DAY * HOUR_TO_MINUTE -
                      depTimeInMinutes) * PRICE_MINUTE_DAY;
      }
      else
      {
         //normal calculus
         tripTotal = travelTimeInMinutes * PRICE_MINUTE_DAY;
      }

   }
   // else take night prices
   else if (depTimeInMinutes <  HOURS_BEGIN_DAY  * HOUR_TO_MINUTE or
            depTimeInMinutes >= HOURS_FINISH_DAY * HOUR_TO_MINUTE)
   {
      // If the trip exceeds midnight
      if (depTimeInMinutes + travelTimeInMinutes >= MINUTES_IN_DAY)
      {
         tripTotal = //from 20 h to midnight.
                     (MINUTES_IN_DAY - depTimeInMinutes +
                     //after midnight.
                     travelTimeInMinutes - (MINUTES_IN_DAY - depTimeInMinutes)) *
                     PRICE_MINUTE_NIGHT;
         //if the trip start before midnight and finish in the morning.
         if ((depTimeInMinutes + travelTimeInMinutes) - MINUTES_IN_DAY >
              HOURS_BEGIN_DAY * HOUR_TO_MINUTE)
         {

            tripTotal = //calculates the time that exceeds the day.
                        (depTimeInMinutes + travelTimeInMinutes -
                        MINUTES_IN_DAY - HOURS_BEGIN_DAY * HOUR_TO_MINUTE) *
                        PRICE_MINUTE_DAY +
                        //calculate what remain in night.
                        (MINUTES_IN_DAY + HOURS_BEGIN_DAY * HOUR_TO_MINUTE -
                         depTimeInMinutes) * PRICE_MINUTE_NIGHT;
         }
      }
      else if (0 <= depTimeInMinutes and depTimeInMinutes < HOURS_BEGIN_DAY *
                HOUR_TO_MINUTE)
      {
         if (depTimeInMinutes + travelTimeInMinutes > HOURS_BEGIN_DAY *
              HOUR_TO_MINUTE)
         {
            tripTotal = depTimeInMinutes + travelTimeInMinutes -
               HOURS_BEGIN_DAY * HOUR_TO_MINUTE *
               PRICE_MINUTE_DAY +

               (HOURS_BEGIN_DAY * HOUR_TO_MINUTE -
               depTimeInMinutes) * PRICE_MINUTE_NIGHT;
         }
         else
         {
            tripTotal = travelTimeInMinutes * PRICE_MINUTE_NIGHT;
         }
      }
      else
      {
         tripTotal = travelTimeInMinutes * PRICE_MINUTE_NIGHT;
      }
   }


   //-------------------------------------------------------------
   //     If all values are correct, calculate the total
   //-------------------------------------------------------------

   finalTotal = PRICE_TAX_BASE + BagTotal + tripTotal;

   cout << TICKET_MSG             << endl
        << TICKET_SEPARATION_SYM  << endl
        << TICKET_BASE_MSG        << setw(WIDTH)                     << right
        << PRICE_TAX_BASE         << endl
        << TICKET_BAG_MSG         << setw(WIDTH)                     << right
        << BagTotal               << endl
        << TICKET_PRICE_MSG       << setw(WIDTH)                     << right
        << tripTotal 	          << endl
        << setw(WIDTHTOTALPRICE)  << TICKET_TOTAL_MSG << setw(WIDTH) << right
        << finalTotal 			    << endl;

   //-------------------------------------------------------------
   //                        End of program
   //-------------------------------------------------------------
   cout << EXIT_MSG;
   CLEAR_BUFFER;

   return EXIT_SUCCESS;
}
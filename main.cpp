/*-----------------------------------------------------------------------------------
Nom du fichier : Labo_02_Taxi_j.cpp
Auteur(s) 		: Kevin Auberson & Nicolas Carbonara
Date creation 	: 07.10.2022
Description 	: Calcule le prix d’une course en € d'un taxi
Remarque(s) 	: -
Compilateur 	: Mingw-w64 g++ 12.1.0
-----------------------------------------------------------------------------------*/

#include <iomanip>	// setw(...) et setprecision(...)
#include <cstdlib>	// EXIT_SUCCESS
#include <iostream> // cout et cin
#include <limits>	// numeric_limits<streamsize>

#define BUFFER_CLEAR cin.ignore(numeric_limits<streamsize>::max(), '\n')

using namespace std;

int main()
{
   //-------------------------------------------------------------
   // Initializing constants
   //-------------------------------------------------------------
   // Prices
   const double PRICE_TAX_BASE 		   = 5.00;
   const double PRICE_TAX_BAG 			= 2.60;
   const double PRICE_MINUTE_DAY 		= 1.00;
   const double PRICE_MINUTE_NIGHT 	   = 1.60;
   const double CHANGE_HOUR_TO_MINUTE 	= 60;
   const int 	 HOURS_BEGIN_DAY 		   = 8;
   const int 	 HOURS_FINISH_DAY 		= 20;
   // Users min/max inputs
   const int 	 MINBAG 				   = 0;
   const int 	 MAXBAG 				   = 4;
   const int 	 MINKM 					= 0;
   const int 	 MAXKM	 				= 500;
   const int 	 MINSPEED 				= 50;
   const int 	 MAXSPEED	 			= 120;
   // Others
   const int 	 WIDTH 					= 8;
   const int	 WIDTHTOTALPRICE		= 26;

   //-------------------------------------------------------------
   // Initializing variables
   //-------------------------------------------------------------
   // Users inputs
   int 	 numberBag;
   int 	 distanceTrip;
   int 	 averageSpeed;
   int 	 hourBegin;
   // Prices
   double 	 BagTotal;
   double 	 tripTotal;
   double 	 finalTotal;
   // Others
   bool     checkMistake = true;

   // Setting the precision of the output and alliging it to the left
   cout << fixed << setprecision(2) << left;

   //-------------------------------------------------------------
   // Welcome
   //-------------------------------------------------------------/
   cout << "Bonjour, ce programme ..." 			<< endl;
   cout << "Voici les conditions     " 			<< endl;
   cout << "==========================" 			<< endl;
   cout << " - prise en charge  : " << setw(WIDTH) << PRICE_TAX_BASE 		<< endl;
   cout << " - supp par bagage  : " << setw(WIDTH)	<< PRICE_TAX_BAG 		<< endl;
   cout << " - tarif/min (jour) : " << setw(WIDTH)	<< PRICE_MINUTE_DAY 	<< endl;
   cout << " - tarif/min (nuit) : " << setw(WIDTH)	<< PRICE_MINUTE_NIGHT 	<< endl;
   cout << " - heures de jour   : " << "[" << HOURS_BEGIN_DAY << " - " << HOURS_FINISH_DAY << "]" << endl << endl;

   //-------------------------------------------------------------
   // Ask the user to enter their order
   //-------------------------------------------------------------
   cout << "Votre commande" << endl;
   cout << "==============" << endl;
   cout << "- nbre de bagage     [" << MINBAG << " - " << MAXBAG << "] : ";
   cin  >> numberBag;
   BUFFER_CLEAR;

   // Check if the number of bag is between MINBAG and MAXBAG
   if (numberBag >= MINBAG & numberBag <= MAXBAG)
   {
      BagTotal = PRICE_TAX_BAG * numberBag;

      cout << "- distance [km]    [" << MINKM << " - " << MAXKM << "] : ";
      cin  >> distanceTrip;
      BUFFER_CLEAR;

      // check if the distance is between MINKM and MAXKM
      if (distanceTrip >= MINKM & distanceTrip <= MAXKM)
      {
         cout << "- vitesse         [" << MINSPEED << " - " << MAXSPEED << "] : ";
         cin  >> averageSpeed;
         BUFFER_CLEAR;

         // check if the speed is between MINSPEED and MAXSPEED
         if (averageSpeed >= MINSPEED & averageSpeed <= MAXSPEED)
         {
            cout << "- depart            [0 - 23] : ";
            cin  >> hourBegin;
            // Insert a blank line for a better reading on the output
            cout << endl;
            BUFFER_CLEAR;

            // IF start hour is inbetween the hour of the day then take day prices
            if (hourBegin >= HOURS_BEGIN_DAY & hourBegin < HOURS_FINISH_DAY)
            {
               // Casting to double to avoid integer division
               tripTotal = double(distanceTrip) / averageSpeed * CHANGE_HOUR_TO_MINUTE * PRICE_MINUTE_DAY;
            }
               // else take night prices
            else if (0 <= hourBegin & hourBegin <= 23)
            {
               // Casting to double to avoid integer division
               tripTotal = double(distanceTrip) / averageSpeed * CHANGE_HOUR_TO_MINUTE * PRICE_MINUTE_NIGHT;
            }
            else
            {	cout << "Erreur : l'heure de depart doit etre comprise entre 0 et 23" << endl;
               checkMistake = false;
            }
         }
         else
         {
            cout << "Erreur : la vitesse doit etre comprise entre " << MINSPEED << " et " << MAXSPEED << endl;
            checkMistake = false;
         }
      }
      else
      {
         cout << "Erreur : la distance doit etre comprise entre " << MINKM << " et " << MAXKM << endl;
         checkMistake = false;
      }
   }
   else
   {
      cout << "Erreur : le nombre de bagage doit etre compris entre " << MINBAG << " et " << MAXBAG << endl;
      checkMistake = false;
   }

   //-------------------------------------------------------------
   // If all values are correct, calculate the total
   //-------------------------------------------------------------
   if (checkMistake)
   {
      finalTotal = PRICE_TAX_BASE + BagTotal + tripTotal;

      cout << "votre Ticket" << endl;
      cout << "============" << endl;
      cout << " - prise en charge  	: " 		<< setw(WIDTH) << right << PRICE_TAX_BASE 		<< endl;
      cout << " - supp bagages    	: " 		<< setw(WIDTH) << right << BagTotal 			<< endl;
      cout << " - prix de la course 	: " 		<< setw(WIDTH) << right << tripTotal 			<< endl;
      cout << setw(WIDTHTOTALPRICE) << "TOTAL : " << setw(WIDTH) << right << finalTotal 			<< endl;
   }

   //-------------------------------------------------------------
   // End of program
   //-------------------------------------------------------------
   cout << "Presser ENTRER pour quitter";
   BUFFER_CLEAR;

   return EXIT_SUCCESS;
}
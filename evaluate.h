#ifndef EVALUATE
#define EVALUATE

#include "player_ai1.h"

//forward declarations
class Game_State;
class Global_Settings;
class Initial_Settings;
class Army;
class Country;
class Continent;
class Card;

#include <vector>
#include <iostream>
#include <math.h>

class Evaluate
{
public :

    // scote our situation
    // linear combination of our evaluate_game_state_given_player and those of the other players
    double evaluate_game_state(Global_Settings* global_settings,Initial_Settings* initial_settings,Game_State* game_state,
                               double coeff_other_player, double coeff_security_threat_of_player, double coeff_compacity,
                               double coeff_number_of_strategic_countries,double coeff_expectedNumberOfArmies);

    double evaluate_game_state_given_player(Player* player,Global_Settings* global_settings,Initial_Settings* initial_settings,
                                            Game_State* game_state, double coeff_security_threat_of_player, double coeff_compacity,
                                            double coeff_number_of_strategic_countries,double coeff_expectedNumberOfArmies); //score the situation of the given player
    //this score is a linear combinaison of several coefficients regarding the situation of a given player(our compacity, our security etc)

    double compacite_game_state(Game_State* game_state);

    int number_triangles(Game_State* game_state);

    /**
     * @brief The Security Threat of a given country
     * @param given country, gamestate and global settings
     * @return ratio between the amount of units bordering the country
     * on the amount of the given country's units
     */

    double security_threat_of_country(Country* country, Game_State* game_state, Global_Settings* global_settings);

    /**
     * @brief Sum of Security Threat of the  player's
     * countries
     * @param Player, gamestate and global settings
     * @return float
     */
    double security_threat_of_player(Player* player, Game_State* game_state, Global_Settings* global_settings);


    /**
     * @brief The Number of strategic countries of a given player
     * @param player
     * @param gamestate
     * @return float
     */

    double number_of_strategic_countries(Player* player, Game_State* game_state);

    int evaluate_compacite(Player* player,Game_State* game_state);

    int expectedNumberOfArmies(Player* player, Global_Settings* global_settings, Game_State* game_state);

private:
    // Vector of the the strategic countries'ids
    int strategicCoutries[16] = {0,2,4,10,12,14,17,18,19,22,26,31,32,34,36,39};

};

#endif // EVALUATE



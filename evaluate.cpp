#include "evaluate.h"
#include "./../shared_structures/game_state.h"
#include "./../shared_structures/global_settings.h"
#include "./../shared_structures/initial_settings.h"
#include "./../shared_structures/army.h"
#include "./../shared_structures/continent.h"
#include "./../shared_structures/card.h"
#include "./../shared_structures/country.h"
#include "nbtriangles.cpp"

double Evaluate::evaluate_game_state_given_player(Player* player,Global_Settings* global_settings,Initial_Settings* initial_settings,
                                                  Game_State* game_state, double coeff_security_threat_of_player, double coeff_compacity,
                                                  double coeff_number_of_strategic_countries,double coeff_expectedNumberOfArmies)
{
    return -coeff_security_threat_of_player*security_threat_of_player(player,game_state,global_settings)
            +coeff_compacity*evaluate_compacite(player, game_state)+
            coeff_number_of_strategic_countries*number_of_strategic_countries(player,game_state)+
            coeff_expectedNumberOfArmies*expectedNumberOfArmies(player,global_settings,game_state);
}

double Evaluate::evaluate_game_state(Global_Settings* global_settings,Initial_Settings* initial_settings,Game_State* game_state,
                                     double coeff_other_player, double coeff_security_threat_of_player, double coeff_compacity,
                                     double coeff_number_of_strategic_countries,double coeff_expectedNumberOfArmies)
{

    double resultat = 0;

    //=== A loop over all the players in order to compute the evaluate_game_state_given_player function ================
    for(vector<Player*>::iterator it = initial_settings->all_players.begin(); it != initial_settings->all_players.end(); ++it)
    {
        Player* playerLoop = *it;
        //===== we distinguish cases where the player we analyze is ourself or not : the coeff is different ====
        if(playerLoop == game_state->get_current_player())
        {
            resultat += evaluate_game_state_given_player(playerLoop,global_settings,initial_settings,game_state,
                                                         coeff_security_threat_of_player,coeff_compacity,coeff_number_of_strategic_countries,coeff_expectedNumberOfArmies);
        }

        else
        {
            resultat += coeff_other_player*evaluate_game_state_given_player(playerLoop,global_settings,initial_settings,game_state,
                                                                            coeff_security_threat_of_player,coeff_compacity,coeff_number_of_strategic_countries,coeff_expectedNumberOfArmies);
                           }
        }
        //=========================================================

    //========================================================================================

    return resultat;

}

double Evaluate::security_threat_of_country(Country* country, Game_State* game_state, Global_Settings* global_settings){
    //armies=*(gamestate.current_armies[country]);
    Army * army = game_state->get_army(country);
    int enemies=0;
    //set<Country*> neighbours = globalsettings.graph[country] ;
    set<Country*> neighbors = global_settings->get_neighbors(country);
    for (set<Country*>::iterator it=neighbors.begin(); it!=neighbors.end();++it){
        if (game_state->owner(*it)!=game_state->owner(country)){
            //enemies+=*(gamestate.current_armies[country]);
            enemies += (game_state->get_army(*it))->get_number_of_armies();
        }
    }
    return (double) enemies/(army->get_number_of_armies());
}


int Evaluate::expectedNumberOfArmies(Player* player, Global_Settings* global_settings, Game_State* game_state)
{

    int armiesTerritories =  (int)(floor(game_state->countries_owned_by(player).size() /3));
    //territories just considering the map

    int continentTerritories = 0;

    //list<Country> contPlyer = gameState->countries_owned_by(player);

    set <Continent*> contnt = global_settings->get_continents();
    set <Continent*>::iterator it;
    for (it = contnt.begin();it != contnt.end();it++)
    {
        if((*it)->is_owned_by(player, game_state))
        {
            continentTerritories += (*it)->get_troop_bonus();
        }
    }

    int totArmiesTerr = armiesTerritories + continentTerritories;

    int tradingArmies = 0;

    set<Card*> cards =  game_state->get_hand(player);

    if (cards.size() >= 3)
    {
        int totalJoker = 0;
        int totalInf = 0;
        int totalCav = 0;
        int totalArt = 0;

        for (set<Card*>::iterator it2 = cards.begin();it2 != cards.end();it2++)
        {
            if ((*it2)->get_symbol() == Card::Infantry){ totalInf++;}
            else if ((*it2)->get_symbol() == Card::Cavalry){ totalCav++;}
            else if ((*it2)->get_symbol() == Card::Artillery){totalArt++;}
            else {totalJoker++;}
        }

        if((totalInf >= 1 && totalCav >= 1 && totalArt >= 1)
                ||(totalJoker >= 1 && totalInf >= 1 && totalCav >= 1)
                ||(totalJoker >= 1 && totalInf >= 1 && totalArt >= 1)
                ||(totalJoker >= 1 && totalArt >= 1 && totalCav >= 1))
        {
            tradingArmies += 10;
            int round = game_state->get_reward_index();
            int bonusRound = 0;
            if(round==1) bonusRound = 4;
            else if(round==2) bonusRound = 6;
            else if(round==3) bonusRound = 8;
            else bonusRound = 10 + 5*(round-4);
            tradingArmies += bonusRound;
        }

        else if(totalArt + totalJoker >= 3)
        {
            tradingArmies += 8;
            int round = game_state->get_reward_index();;
            int bonusRound = 0;
            if(round==1) bonusRound = 4;
            else if(round==2) bonusRound = 6;
            else if(round==3) bonusRound = 8;
            else bonusRound = 10 + 5*(round-4);
            tradingArmies += bonusRound;
        }

        else if(totalCav + totalJoker >= 3)
        {
            tradingArmies += 6;
            int round = game_state->get_reward_index();
            int bonusRound = 0;
            if(round==1) bonusRound = 4;
            else if(round==2) bonusRound = 6;
            else if(round==3) bonusRound = 8;
            else bonusRound = 10 + 5*(round-4);
            tradingArmies += bonusRound;
        }

        else if(totalInf + totalJoker >= 3)
        {
            tradingArmies += 4;
            int round = game_state->get_reward_index();
            int bonusRound = 0;
            if(round==1) bonusRound = 4;
            else if(round==2) bonusRound = 6;
            else if(round==3) bonusRound = 8;
            else bonusRound = 10 + 5*(round-4);
            tradingArmies += bonusRound;
        }

    }

    return totArmiesTerr + tradingArmies;
}

double Evaluate::security_threat_of_player (Player* player,Game_State* game_state, Global_Settings* global_settings){
    double sum=0.0;
    list<Country*> territories = game_state->countries_owned_by(player);
    for (list<Country*>::iterator it=territories.begin(); it!=territories.end();++it){
        sum+=security_threat_of_country(*it,game_state,global_settings);
    }

    return sum;
}


double Evaluate::number_of_strategic_countries(Player* player, Game_State* game_state){
    double number=0.0;
    list<Country*> territories = game_state->countries_owned_by(player);
    for (list<Country*>::iterator it=territories.begin(); it!=territories.end();++it){
        int id =(*it)->get_id();
        for (int i=0;i<sizeof(strategicCoutries);i++){
            if (id==strategicCoutries[i]){
                number+=1.0;
            }
        }
    }
    return number;
}

int Evaluate::evaluate_compacite(Player* player,Game_State* game_state){

    int N=42;
    list<Country*> liste;
    liste=game_state->countries_owned_by (player);
         evaluatecompacite(liste);
    return  0;

}





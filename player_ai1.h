#pragma once
#include "./../interfaces/player.h"


class Move;             // Forward declaration
class Game_State;       // Forward declaration
class Global_Settings;  // Forward declaration
class Initial_Settings; // Forward declaration
class Dispatch_Move;    // Forward declaration

using namespace std;

class AIAPlayer : public Player {
public:
    AIAPlayer();
    ~AIAPlayer();

    // External functions
    void receive_global_settings(Global_Settings gs);
    Move first_move(Initial_Settings is);
    Move next_move(Game_State gs);

    // Our functions
    Dispatch_Move decideReinforcements(Game_State* gs);
    Attack_Move decideNextAttack(Game_State* gs);
    Displacement_Move decideTransfer(Game_State* gs);
    Displacement_Move decideFortification(Game_State* gs);

private:
//    GlobalSettings* settings;
    Game_State* gameState;
    map<Country*,set<Country*> > world_map;

};

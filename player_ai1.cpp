#include "player_ai1.h"
#include <map>
#include <stdlib.h>
#include <time.h>

#include "./../shared_structures/moves.h"
#include "./../shared_structures/game_state.h"
#include "./../shared_structures/global_settings.h"
#include "./../shared_structures/initial_settings.h"



AIAPlayer::AIAPlayer()
{

}

AIAPlayer::~AIAPlayer()
{

}


void AIAPlayer::receive_global_settings(Global_Settings gs) {
    world_map = gs.get_graph();
}

//Move AIAPlayer::first_move(Initial_Settings is) {
//    return RandomReinforcement::decideReinforcement(is);
//}

//Move AIAPlayer::next_move(Game_State gs) {
//    set<Card*> my_hand;
//    my_hand = gs. get_hand (this);
//    set<Card*> t[3];
//    for (const auto& elem : my_hand)
//        t[elem.symbol->id].insert(elem);

//    switch (gs.current_step->id) {
//    case 1:
//        Change_Cards_Move answer1;
//        answer1.id = 2;
//        answer1.change = NULL;
//        return answer1;
//    case 2:
//        Change_Cards_Move answer2;
//        answer2.id = 2;
//        for (int i = 0; i < 3; i++) {
//            if (t[i].size() >= 3) {
//                int j = 0;
//                for (const auto& elem : t[i])
//                    if (j < 3) {
//                        answer2.change.insert(elem);
//                        j++;
//                    }
//            }
//        }
//        if (answer2.change.size() != 3) {
//            for (int i = 0; i < 3; i++) {
//                int j = 0;
//                for (const auto& elem : t[i])
//                    if (j == 0) {
//                        answer2.change.insert(elem);
//                        j++;
//                    }
//            }
//        }
//        return answer2;
//    case 3:
//        Dispatch_Move answer3;
//        answer3.id = 3;
//        int nt = 0;
//        for (const auto& elem : gs.current_armies) {
//            if (elem.second->owner == this)
//                nt++;
//        }
//        Country* my_territories[nt];
//        int i = 0;
//        for (const auto& elem : gs.current_armies) {
//            if (elem.second->owner == this) {
//                my_territories[i] = elem.first;
//            }
//        }
//        map<Country*, int> distribution;
//        for (int i = 0; i < nt; i++) {
//            distribution[my_territories[i]] = 0;
//        }
//        int random_number;
//        Dispatch_Step* DS = gs.current_step;
//        for (int i = 0; i < DS->number_of_troops; i++) {
//            random_number = rand() % nt;
//            distribution[my_territories[random_number]] += 1;
//        }
//        answer3.distribution = distribution;
//        return answer3;
//    case 4:
//        Attack_Move answer4;
//        answer4.id = 4;
//        set<Country*> pc;
//        for (const auto& elem : gs.current_armies)
//            if (elem.second->owner == this
//                    && elem.second->number_of_armies >= 2) {
//                pc.insert(elem.first);
//            }

//        if (pc.size() != 0) {
//            int i = 0;
//            int rn = rand() % pc.size();
//            for (const auto& elem : pc) {
//                if (i == rn)
//                    answer4.origin = elem;
//                else
//                    i++;
//            }
//            if (gs.current_armies[answer4.origin] > 3) {
//                answer4.number_of_armies = 3;
//            } else {
//                answer4.number_of_armies = gs.current_armies[answer4.origin]
//                        - 1;
//            }
//            int nn = world_map[answer4.origin].size();
//            int rn = rand() % nn;
//            int i = 0;
//            for (const auto& elem : world_map[answer4.origin]) {
//                if (i == rn)
//                    answer4.destination = elem;
//                else
//                    i++;
//            }
//        } else {
//            answer4.number_of_armies = 0;
//            answer4.origin = NULL;
//            answer4.destination = NULL;
//        }
//        return answer4;
//    case 5:
//        Displacement_Move answer5;
//        answer5.id = 5;
//        set<Country*> pc;
//        for (const auto& elem : gs.current_armies)
//            if (elem.second->owner == this
//                    && elem.second->number_of_armies >= 2) {
//                pc.insert(elem.first);
//            }
//        if (pc.size() != 0) {
//            int i = 0;
//            int rn = rand() % pc.size();
//            for (const auto& elem : pc) {
//                if (i == rn)
//                    answer5.origin = elem;
//                else
//                    i++;
//            }
//            for (const auto& elem : world_map[answer5.origin]) {
//                if ((*gs.current_armies[elem]).owner==this)
//                    answer5.destination = elem;
//            }
//            answer5.number_of_armies = gs.current_armies[answer5.origin]
//                    - 1;
//        }
//        return answer5;
//    case 6:
//        return NULL;
//    }
//}

//
//  baseDataStruct.h
//  Q-Learning
//
//  Created by 黄正跃 on 5/3/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef baseDataStruct_h
#define baseDataStruct_h
/////////////////////////////////////////////////////////////
//namespace gamesettings{
//    
//    struct GameSeting{
//        double noise=0.2;
//        double discount=0.9;
//        double living_reward=0;
//        double epsion=0.5;
//        double alpha=0.2;
//        GameSeting(){
//            
//        }
//        GameSeting(double _noise,double _discount,double _living_reward,double _epison,double _alpha):noise(_noise),discount(_discount),living_reward(_living_reward),epsion(_epison),alpha(_alpha){
//            
//        }
//    };
//    
//    GameSeting gameValues;
//}



struct Vect2{
    int x;
    int y;
    Vect2(int _x,int _y):x(_x),y(_y){}
};
/////////////////////////////////////////////////////////////
struct EvironmentFeedBack{
    Vect2 position;
    double reward;
    double livingReward;
    bool isTerminal;
    
    EvironmentFeedBack(Vect2 pos,double living_reward,bool is_terminal,double _reward):position(pos),reward(_reward),livingReward(living_reward),isTerminal(is_terminal){}
};

/////////////////////////////////////////////////////////////
class ValueNode{
private:
    double value;
    double Qvalue[4]={0};
    bool value_updated;
    int count=0;
public:
    //constructor
    ValueNode():value(0),value_updated(true){}
    //these are get-methods
    
    double getValue(){
        if(!value_updated){
            updateValue();
        }
        return value;
    }
    
    double getQValue(int position){
        return Qvalue[position];
    }
    
    //return the action of this state
    int getPolicy(){
        double max_value=Qvalue[0];
        int max_index=0;
        for(int i=1;i<4;i++){
            if(Qvalue[i]>max_value){
                max_value=Qvalue[i];
                max_index=i;
            }
        }
        return max_index;
    }
    
    int getCount(){
        return count;
    }
    
    void updateValue(){
        double max_v=Qvalue[0];
        for(int i=1;i<4;i++){
            if(Qvalue[i]>max_v){
                max_v=Qvalue[i];
            }
        }
        this->value=max_v;
        this->value_updated=true;
    }
    
    //the flowing are set-value-Fuctions
    void setValue(double _value){
        this->value=_value;
    }
    
    void setQValue(int direction,double qvalue){
        this->value_updated=false;
        this->Qvalue[direction]=qvalue;
    }
    
    void countPlusOne(){
        count++;
    }
    
    
    
};

/////////////////////////////////////////////////////////////
class MapBlock{
public:
    //constructor
    MapBlock():reward(0),is_wall(false),is_terminal(false){}
    
    double getReward(){
        return reward;
    }
    bool isWall(){
        return is_wall;
    }
    bool isTerminal(){
        return is_terminal;
    }
    void setReward(double value){
        reward=value;
    }
    void setWall(){
        this->is_wall=true;
    }
    void setTerminal(){
        this->is_terminal=true;
    }
  
private:
    double reward;
    bool is_wall;
    bool is_terminal;
    
};

#endif /* baseDataStruct_h */

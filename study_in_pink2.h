/*
 * Ho Chi Minh City University of Technology
 * Faculty of Computer Science and Engineering
 * Initial code for Assignment 1
 * Programming Fundamentals Spring 2023
 * Author: Vu Van Tien
 * Date: 02.02.2023
 */

// The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"
////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;

class MagicBook;
class ExcemptionCard;
class EnergyDrink;
class PassingCard;
class FirstAid;
class Character;
class Watson;
class Sherlock;

class TestStudyInPink;

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C = 0,
    S,
    W,
    SW
};

enum MovingObjectType
{
    SHERLOCK,
    WATSON,
    CRIMINAL,
    ROBOT
};

class MapElement
{
    friend class TestStudyPink;

protected:
    ElementType type;

public:
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement
{
    friend class TestStudyPink;

public:
    Path();
};

class Wall : public MapElement
{
    friend class TestStudyPink;

public:
    Wall();
};

class FakeWall : public MapElement
{
    friend class TestStudyPink;

private:
    int req_exp;

public:
    FakeWall(int in_req_exp);
    int getReqExp() const;
};

class Map
{
    friend class TestStudyPink;

private:
    int num_rows, num_cols;
    
    MapElement ***map;

public:
    Map(int num_rows, int num_cols, int num_walls,
        Position *array_walls, int num_fake_walls, Position *array_fake_walls);
    ~Map();

    int getNumRows() const;
    int getNumCols() const;
    ElementType getElementType(int i, int j) const;
    bool isValid(const Position pos, MovingObject *mv_obj) const;
};

class Position
{
    friend class TestStudyPink;

private:
    int r, c;

public:
    bool operator ==(const Position & P) const{
        return (r == P.getRow() && c == P.getCol());
    }
    static const Position npos;
    Position(int r = 0, int c = 0);
    Position(const string &str_pos);
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    string str() const;
    bool isEqual(int in_r, int in_c) const;
    bool isEqual(Position pos) const;
};

class MovingObject
{
    friend class TestStudyPink;

protected:
    int index;
    Position pos;
    Map *map;
    string name;

public:
    MovingObject(int index, const Position pos, Map *map, const string &name = "");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    
    virtual MovingObjectType getObjectType() const = 0;
};

class Character : public MovingObject
{
    friend class TestStudyPink;

public:
    Character(int index, const Position pos, Map *map, const string &name = "");
    
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual MovingObjectType getObjectType() const = 0;
};

class Sherlock : public Character
{
    friend class TestStudyPink;

private:
    // TODO
    int hp, exp;
    
    string moving_rule;
    int index_moving_rule;
    BaseBag *bag;
public:
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);

    Position getNextPosition();
    void move();
    string str() const;
    
    MovingObjectType getObjectType() const;
    BaseBag *getBag() const;
    int getHP() const;
    int getEXP() const;
    void setHP(int hp);
    void setEXP(int exp);
    void setPos(Position pos);
    bool meet(RobotS *robotS);
    bool meet(RobotW *robotW);
    bool meet(RobotSW *robotSW);
    bool meet(RobotC *robotC);
    bool meet(Watson *watson);
    ~Sherlock();
};

class Watson : public Character
{
    friend class TestStudyPink;

private:
    // TODO
    int hp, exp;
    
    string moving_rule;
    int index_moving_rule;
    BaseBag *bag;
public:
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp);
    Position getNextPosition();
    void move();
    string str() const;
    
    MovingObjectType getObjectType() const;
    BaseBag *getBag() const;
    int getHP() const;
    int getEXP() const;
    void setHP(int hp);
    void setEXP(int exp);
    bool meet(RobotS *robotS);
    bool meet(RobotW *robotW);
    bool meet(RobotSW *robotSW);
    bool meet(RobotC *robotC);
    bool meet(Sherlock *sherlock);
    ~Watson();
};

class Criminal : public Character
{
    friend class TestStudyPink;

private:
    // TODO
    Sherlock *sherlock;
    Watson *watson;
    
    int count;
    Position prev_pos;

public:
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson);
    Position getNextPosition();
    void move();
    string str() const;
    
    int manhattanDistance(const Position &pos1, const Position &pos2) const{
        return abs(pos1.getCol() - pos2.getCol()) + abs(pos1.getRow() - pos2.getRow());
    }
    MovingObjectType getObjectType() const;
    int getCount() const;
    bool isCreatedRobotNext() const;

    Position getPrevPosition() const;
    Sherlock* getSherlock(){return sherlock;}
    Watson* getWatson(){return watson;}
};

class ArrayMovingObject
{
    friend class TestStudyPink;

private:
    // TODO
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject *mv_obj);
    string str() const;
    
    bool checkMeet(int index);
    MovingObject *get(int index) const;
    int size() const;
};

class Configuration
{
    friend class TestStudyPink;
    friend class StudyPinkProgram;

private:
    // TODO
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *arr_walls;
    int num_fake_walls;
    Position *arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;

public:
    Configuration(const string &filepath);
    ~Configuration();
    string str() const;
};

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject
{
    friend class TestStudyPink;

protected:
    RobotType robot_type;
    BaseItem* item;
    Criminal *criminal;
    Position poshead;

public:
    Robot(int index,
          const Position &pos,
          Map *map,
          Criminal *criminal,
          const string &name = "");
    MovingObjectType getObjectType() const;
    virtual Position getNextPosition() = 0;
    virtual void move() = 0;
    virtual string str() const = 0;
    virtual RobotType getType();
    
    static Robot *create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
    virtual int getDistance() const = 0;
    BaseItem* getItem() { return item; }
    Position getPoshead(){return poshead;}
    ~Robot(){}
};

class RobotC : public Robot
{
    friend class TestStudyPink;

private:
public:
    RobotC(int index,
           const Position &init_pos,
           Map *map,
           Criminal *criminal);
    Position getNextPosition();
    void move();
    int getDistance(Sherlock *sherlock);
    int getDistance(Watson *watson);

    string str() const;
    
    int getDistance() const override;
    RobotType getType() const;
    ~RobotC(){}
};

class RobotS : public Robot
{
    friend class TestStudyPink;

private:
    Sherlock *sherlock;

public:
    RobotS(int index,
           const Position &init_pos,
           Map *map,
           Criminal *criminal,
           Sherlock *sherlock);
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;
    
    RobotType getType() const;
    ~RobotS(){}
};

class RobotW : public Robot
{
    friend class TestStudyPink;

private:
    Watson *watson;

public:
    RobotW(int index,
           const Position &init_pos,
           Map *map,
           Criminal *criminal,
           Watson *watson);
    Position getNextPosition();
    void move();
    int getDistance() const;
    string str() const;
    
    RobotType getType() const ;
    ~RobotW(){}
};

class RobotSW : public Robot
{
    friend class TestStudyPink;

private:
    Sherlock *sherlock;
    Watson *watson;

public:
    RobotSW(int index,
            const Position &init_pos,
            Map *map,
            Criminal *criminal,
            Sherlock *sherlock,
            Watson *watson);

    Position getNextPosition();
    string str() const;
    int getDistance() const;
    void move();
    
    RobotType getType() const;
    ~RobotSW(){}
};

class BaseItem
{
    friend class TestStudyPink;

public:
    virtual bool canUse(Character *obj, Robot *robot) = 0;
    virtual void use(Character *obj, Robot *robot) = 0;
    
   BaseItem(){

   }
    virtual ItemType getType() const = 0;
    virtual string str() const = 0;
    ~BaseItem(){

    }
};

class MagicBook : public BaseItem
{
    friend class TestStudyPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    
    ItemType getType() const;
    string str() const;
};

class EnergyDrink : public BaseItem
{
    friend class TestStudyPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    
    ItemType getType() const;
    string str() const;
};

class FirstAid : public BaseItem
{
    friend class TestStudyPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    
    ItemType getType() const;
    string str() const;
};

class ExcemptionCard : public BaseItem
{
    friend class TestStudyPink;

public:
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    
    ItemType getType() const;
    string str() const;
};

class PassingCard : public BaseItem
{
    friend class TestStudyPink;

private:
    string challenge;

public:
    PassingCard(int i, int j);
    bool canUse(Character *obj, Robot *robot);
    void use(Character *obj, Robot *robot);
    
    ItemType getType() const;
    string str() const;
    string getChallenge(){return challenge;}
};

class BaseBag
{
    friend class TestStudyPink;

protected:
    
    class Node
    {
    public:
        BaseItem *item;
        Node *next;

    public:
        Node(BaseItem *item, Node *next = nullptr) : item(item), next(next) {}
    };

protected:
    Character *obj;
    
    int size;
    int capacity;
    Node *head;

public:
    virtual bool insert(BaseItem *item);
    virtual BaseItem *get() = 0;
    virtual BaseItem *get(ItemType itemType);
    virtual string str() const;

    
    BaseBag(int capacity);
    virtual ~BaseBag();
    bool checkItem(ItemType itemType);
    BaseItem* find(ItemType itemType);

    bool isFull() const;
};

class SherlockBag : public BaseBag
{
    friend class TestStudyPink;

private:
    Sherlock *sherlock;

public:
    SherlockBag(Sherlock *character);
    BaseItem *get();
};

class WatsonBag : public BaseBag
{
    friend class TestStudyPink;

private:
    Watson *watson;

public:
    WatsonBag(Watson *character);
    BaseItem *get();
};

class StudyPinkProgram
{
    friend class TestStudyPink;

private:
    // Sample attributes
    Configuration *config;
    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;
    Map *map;
    ArrayMovingObject *arr_mv_objs;
    
    string outputFile;

public:
    StudyPinkProgram(const string &config_file_path);
    bool isStop() const;
    void printResult() const
    {
         if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
         {
             cout << "Sherlock caught the criminal" << endl;
         }
         else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
         {
             cout << "Watson caught the criminal" << endl;
         }
         else
         {
             cout << "The criminal escaped" << endl;
         }
    }

    void printStep(int si) const
    {
         cout << "Step: " << setw(4) << setfill('0') << si
              << "--"
              << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }
    void run(bool verbose);
    ~StudyPinkProgram();
    
    void run(ofstream &OUTPUT);
    void run(bool verbose, ofstream &OUTPUT);
    void printInfo(int si, int i, ofstream &OUTPUT)
    {
        OUTPUT << endl
               << "*************AFTER MOVE*************" << endl;
        OUTPUT
            << "ROUND : " << si << " - TURN : " << i << endl;
        stringstream ss(arr_mv_objs->str());
        string lineArr = "";
        getline(ss, lineArr, 'C');
        OUTPUT << lineArr << "]" << endl;
        getline(ss, lineArr, ']');
        OUTPUT << "\tC" << lineArr << "]" << endl;
        while (getline(ss, lineArr, ']'))
        {
            if (lineArr.length() > 0)
                OUTPUT << "\t" << lineArr.substr(1) << "]" << endl;
        }
        OUTPUT << "Sherlock HP_" << sherlock->getHP() << " EXP_" << sherlock->getEXP() << endl
               << "Watson HP_" << watson->getHP() << " EXP_" << watson->getEXP() << endl
               << "SherlockBag : " << sherlock->getBag()->str() << endl
               << "WatsonBag : " << watson->getBag()->str() << endl;
    }
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */

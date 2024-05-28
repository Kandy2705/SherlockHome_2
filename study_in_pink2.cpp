#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

const Position Position::npos = Position(-1, -1);
/*
 * CLASS: MapElement
 */

MapElement::MapElement(ElementType in_type): type(in_type)
{

}

MapElement::~MapElement() {}

ElementType MapElement::getType() const
{
    return type;
}
/*
 * CLASS: Path
 */
Path::Path()
        : MapElement(PATH) {}
/*
 * CLASS: Wall
 */
Wall::Wall()
        : MapElement(WALL) {}
/*
 * CLASS: FakeWall
 */
FakeWall::FakeWall(int in_req_exp)
        : MapElement(ElementType::FAKE_WALL), req_exp(in_req_exp)
{
}
int FakeWall::getReqExp() const
{
    return req_exp;
}
/*
 * CLASS: Position
 */

Position::Position(int r, int c ) :r(r),c(c)
{
}
Position::Position(const string &str_pos)
{
    r = stoi(str_pos.substr(str_pos.find("(") + 1, str_pos.find(",")));
    c = stoi(str_pos.substr(str_pos.find(",") + 1, str_pos.find(")")));
}
int Position::getRow() const
{
    return r;
}
int Position::getCol() const
{
    return c;
}
void Position::setRow(int r)
{
    this -> r = r;
}
void Position::setCol(int c)
{
    this -> c = c;
}
string Position::str() const
{
    string tra = "(" + to_string(r)+ "," + to_string(c) + ")";
    return tra;
}
bool Position::isEqual(Position position) const
{
    if (position.r == r && position.c == c){
        return true;
    }
    return false;
}

bool Position ::isEqual(int in_r, int in_c) const {
    if (r == in_r && c == in_c){
        return true;
    }
    return false;
}

/*
 * CLASS: MovingObject
 */
MovingObject::MovingObject(int index, const Position pos, Map *map, const string &name ):index(index),pos(pos),map(map),name(name)
{
}

MovingObject::~MovingObject(){
}

Position MovingObject::getCurrentPosition() const
{
    return Position(pos.getRow(),pos.getCol());

}
/*
 * CLASS: Character kế thừa class MovingObject
 */
Character::Character(int index, const Position pos, Map *map, const string &name)
        : MovingObject(index,pos,map,name

)
{

}
/*
 * CLASS: Robot kế thừa class MovingObject
 */
Robot::Robot(int index, const Position &pos, Map *map, Criminal *criminal, const string &name)
        : MovingObject(index, pos, map, "Robot"), criminal(criminal) //! khác
{
    this->criminal = criminal;
    int p = pos.getRow()*pos.getCol();
    int s = 0;
    string pp=to_string(p);
    do{
        s = 0;
        for (int i = 0; i < pp.length(); i++) {
            string temp = to_string(pp[i] - '0');
            s += stoi(temp);
        }
        pp = to_string(s);
    }while(to_string(s).length() != 1);
    if (s >= 0 && s <= 1) {
        item = new MagicBook();
    }else if (s >= 2 && s <= 3){
        item = new EnergyDrink();
    }else if(s >= 4 && s <= 5){
        item = new FirstAid();
    }else if(s >= 6 && s <= 7){
        item = new ExcemptionCard();
    }else if (s >= 8 && s <= 9){
        item = new PassingCard(pos.getRow(), pos.getCol());
        poshead.setRow(pos.getRow());
        poshead.setCol(pos.getCol());
    }
}
//Robot::~Robot(){
////    delete item;
//}

RobotType Robot::getType() {
    return this->robot_type;
}

/*
 * CLASS: Sherlock kế thừa class Character
 */
Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), index_moving_rule(0)
{
    index_moving_rule = 0;
    if (init_hp < 0){
        hp = 1;
    }
    else if (init_hp > 500){
        hp = 500;
    }
    else{
        hp = init_hp;
    }
    if (init_exp < 0){
        exp = 0;
    }
    else if (init_exp > 900){
        exp = 900;
    }
    else{
        exp = init_exp;
    }
    this->bag = new SherlockBag(this);
}

Sherlock::~Sherlock(){
    delete bag;
}

void Sherlock::setPos(Position pos) {
    this->pos.setCol(pos.getCol());
    this->pos.setRow(pos.getRow());
}

Position Sherlock::getNextPosition()
{
    if(moving_rule.empty()){
        return Position::npos;
    }
    char vitritieptheo = moving_rule[index_moving_rule];
    index_moving_rule = (index_moving_rule + 1) % moving_rule.size();
    int vitrir = pos.getRow();
    int vitric = pos.getCol();
    if (vitritieptheo == 'L'){
        vitric-=1;
    }
    else if (vitritieptheo == 'R'){
        vitric+=1;
    }
    else if (vitritieptheo == 'U'){
        vitrir-=1;
    }
    else if (vitritieptheo == 'D'){
        vitrir+=1;
    }
    else{
        return Position::npos;
    }

    if (!map ->isValid(Position(vitrir,vitric),this)){//nếu không tìm thấy trên map
        return Position::npos;
    }
    return Position(vitrir,vitric);
}
void Sherlock::move()
{
    if (getEXP() != 0){
        Position vitritiep = getNextPosition();
        if (vitritiep == Position::npos){
            return;
        }
        pos.setRow(vitritiep.getRow());
        pos.setCol(vitritiep.getCol());
    }
}
string Sherlock::str() const
{
    string ketqua = "Sherlock[index="+ to_string(index) +";pos="+pos.str()+";moving_rule=" + moving_rule+"]";
    return ketqua;
}

MovingObjectType Sherlock::getObjectType() const
{
    return SHERLOCK;
}

int Sherlock::getHP() const
{
    return hp;
}
int Sherlock::getEXP() const
{
    return exp;
}
void Sherlock::setHP(int hp)
{
    this -> hp = hp;
}

void Sherlock::setEXP(int exp)
{
    this -> exp = exp;
}
/*
 * CLASS: Watson kế thừa class Character
 */
Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), index_moving_rule(0)
{
    index_moving_rule = 0;
    if (init_hp < 0){
        hp = 1;
    }
    else if (init_hp > 500){
        hp = 500;
    }
    else{
        hp = init_hp;
    }
    if (init_exp < 0){
        exp = 0;
    }
    else if (init_exp > 900){
        exp = 900;
    }
    else{
        exp = init_exp;
    }

    this->bag = new WatsonBag(this);
}

Watson::~Watson(){
    delete bag;
}

Position Watson::getNextPosition()
{
    if(moving_rule.empty()){
        return Position::npos;
    }
    char vitritieptheo = moving_rule[index_moving_rule];
    index_moving_rule = (index_moving_rule + 1) % moving_rule.size();
    int vitrir = pos.getRow();
    int vitric = pos.getCol();
    if (vitritieptheo == 'L'){
        vitric--;
    }
    else if (vitritieptheo == 'R'){
        vitric++;
    }
    else if (vitritieptheo == 'U'){
        vitrir--;
    }
    else if (vitritieptheo == 'D'){
        vitrir++;
    }
    else{
        return Position::npos;
    }
    if (!map ->isValid(Position(vitrir,vitric),this)){//nếu không tìm thấy trên map
        return Position::npos;
    }
    return Position(vitrir,vitric);


}

void Watson::move()
{
    if (getEXP() != 0){
        Position vitritiep = getNextPosition();
        if (vitritiep == Position::npos){
            return;
        }
        pos.setRow(vitritiep.getRow());
        pos.setCol(vitritiep.getCol());
    }
}
string Watson::str() const
{
    string ketqua = "Watson[index="+ to_string(index) +";pos="+pos.str()+";moving_rule=" + moving_rule+"]";
    return ketqua;
}

MovingObjectType Watson::getObjectType() const
{
    return WATSON;
}

int Watson::getHP() const
{
    return hp;
}

int Watson::getEXP() const
{
    return exp;
}

void Watson::setHP(int hp)
{
    this -> hp = hp;
}

void Watson::setEXP(int exp)
{
    this -> exp = exp;
}
/*
 * CLASS: Map
 */
Map::Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls)
        : num_rows(num_rows), num_cols(num_cols)
{
    if(num_cols == 0 || num_rows == 0) return;
    this->num_rows = num_rows;
    this->num_cols = num_cols;

    map = new MapElement**[num_rows];
    for(int i = 0; i < num_rows; i++){
        map[i] = new MapElement*[num_cols];
        for (int j = 0; j < num_cols; j++){
            map[i][j] = nullptr;
        }
    }

    for(int i = 0; i < num_walls; i++){
        int r = array_walls[i].getRow();
        int c = array_walls[i].getCol();
        if (r < num_rows && r >= 0 && c >= 0 && c < num_cols){
            if (map[r][c] == nullptr)
                map[r][c] = new Wall();
        }
    }

    for(int i = 0; i < num_fake_walls; i++){
        int r = array_fake_walls[i].getRow();
        int c = array_fake_walls[i].getCol();
        if (r < num_rows && r >= 0 && c >= 0 && c < num_cols){
            if ((!(map[r][c] != nullptr && map[r][c]->getType() == WALL))){
                if (map[r][c] != nullptr) {
                    delete map[r][c];
                }
                map[r][c] = new FakeWall((r * 257 + c * 139 + 89) % 900 + 1);
            }
        }
    }

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            if (map[i][j] == nullptr) {
                map[i][j] = new Path();
            }
        }
    }
}
Map::~Map()
{
    if (num_rows == 0 || num_cols == 0) return;
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            delete map[i][j];
            map[i][j] = nullptr;
        }
    }

    for (int i = 0; i < num_rows; i++){
        delete [] map[i];
        map[i] = nullptr;
    }
    delete [] map;
    map = nullptr;
}

int Map::getNumRows() const
{
    return num_rows;
}
int Map::getNumCols() const
{
    return num_cols;
}
ElementType Map::getElementType(int i, int j) const
{
    return map[i][j] -> getType();
}
bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
{
    int i = pos.getRow() , j = pos.getCol();
    if (i>= num_rows || i < 0 || j >= num_cols || j < 0) return false;
    if (mv_obj->getObjectType() == SHERLOCK && (map[i][j] -> getType() == PATH || map[i][j] -> getType() == FAKE_WALL)){
        return true;
    }
    if (mv_obj->getObjectType() == WATSON){
        Watson* tempObject = dynamic_cast<Watson*>(mv_obj);
        FakeWall* tempWall = dynamic_cast<FakeWall*>(map[i][j]);
        if (map[i][j]->getType() == PATH)
            return true;
        if (map[i][j]->getType() == FAKE_WALL){
            if (tempObject->getEXP() > tempWall->getReqExp())
                return true;
        }
    }
    if (mv_obj->getObjectType() == CRIMINAL && (map[i][j] -> getType() == PATH || map[i][j] -> getType() == FAKE_WALL)){
        return true;
    }
    if (mv_obj->getObjectType() == ROBOT && (map[i][j] -> getType() == PATH || map[i][j] -> getType() == FAKE_WALL)){
        return true;
    }
    return false;
}
/*
 * CLASS: Criminal kế thừa class Character
 */

Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
        : Character(index,init_pos,map,"Criminal"), sherlock(sherlock), watson(watson)
{
    prev_pos.setCol(-1);
    prev_pos.setRow(-1);
    count = 0;
}

//Criminal::~Criminal(){
////    delete sherlock;
////    delete watson;
//}

int Sum(int x, int y, Sherlock*s, Watson*w){
    return abs(x-s->getCurrentPosition().getCol()) + abs(y - s->getCurrentPosition().getRow()) +
           abs(x-w->getCurrentPosition().getCol()) + abs(y - w->getCurrentPosition().getRow());
}
Position Criminal::getNextPosition()
{

    int vitric = -1;
    int vitrir = -1;
    int sum = -1;
    prev_pos = Position(pos.getRow(),pos.getCol());
    if (map->isValid(Position(pos.getRow() - 1, pos.getCol()), this) && Sum(pos.getCol() , pos.getRow() - 1, sherlock, watson) > sum){
        vitrir = pos.getRow() - 1;
        if(vitrir < 0) vitrir+=1;
        else{
            vitric = pos.getCol();
            sum = Sum(pos.getCol(), pos.getRow() - 1, sherlock, watson);
        }
    }//len
    if (map->isValid(Position(pos.getRow(), pos.getCol() - 1), this) && Sum(pos.getCol() -1 , pos.getRow(), sherlock, watson) > sum){
        vitric = pos.getCol() - 1;
        if(vitric < 0) {
            vitric +=1;
            vitrir = pos.getRow();
        }
        else{
            vitrir = pos.getRow();
            sum = Sum(pos.getCol() - 1, pos.getRow(), sherlock, watson);
        }
    }//trai

    if (map->isValid(Position(pos.getRow() + 1, pos.getCol()), this) && Sum(pos.getCol() , pos.getRow() + 1, sherlock, watson) > sum){
        vitrir = pos.getRow() + 1;
        if(vitrir >= map->getNumRows()) vitrir -=1;
        else{
            vitric = pos.getCol();
            sum = Sum(pos.getCol(), pos.getRow() + 1, sherlock, watson);
        }
    }//xuong

    if (map->isValid(Position(pos.getRow(), pos.getCol() + 1), this) && Sum(pos.getCol()+ 1 , pos.getRow(), sherlock, watson) > sum){

        vitric = pos.getCol()+ 1;
        if(vitric >= map->getNumCols()) vitric -=1;
        else{
            vitrir = pos.getRow() ;
            sum = Sum(pos.getCol() + 1, pos.getRow(), sherlock, watson);
        }
    }//phai


    return Position(vitrir, vitric);
}
Position Criminal::getPrevPosition() const{

    return prev_pos;
}
void Criminal::move()
{
    Position vitritiep = getNextPosition();
    if (vitritiep == Position::npos){
        return;
    }
    pos.setRow(vitritiep.getRow());
    pos.setCol(vitritiep.getCol());
    count += 1;
}

string Criminal::str() const
{
    string ketqua = "Criminal[index="+ to_string(index) +";pos="+pos.str()+"]";
    return ketqua;
}

MovingObjectType Criminal::getObjectType() const
{
    return CRIMINAL;
}
int Criminal::getCount() const
{
    return count;
}

bool Criminal::isCreatedRobotNext() const {
    return count == 3;
}

int kcS(int x, int y, Sherlock*s){
    return abs(x-s->getCurrentPosition().getCol()) + abs(y - s->getCurrentPosition().getRow());
}
int kcW(int x, int y, Watson*w){
    return abs(x-w->getCurrentPosition().getCol()) + abs(y - w->getCurrentPosition().getRow());
}
Robot *Robot::create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
{
    Position cr = criminal->getPrevPosition();
    Position she = sherlock->getCurrentPosition();
    Position wa = watson->getCurrentPosition();
    int kcshe = kcS(cr.getCol(),cr.getRow(),sherlock);
    int kcwa = kcW(cr.getCol(),cr.getRow(),watson);
    Position temp = criminal -> getPrevPosition();
    if (criminal->isCreatedRobotNext()){
        return new RobotC(index,cr,map,criminal);
    }
    else{
        if(kcshe < kcwa){
            return new RobotS(index,cr,map,criminal,sherlock);
        }
        else if(kcwa < kcshe){
            return new RobotW(index,cr,map,criminal,watson);
        }
        else{
            return new RobotSW(index,cr,map,criminal,sherlock,watson);
        }
    }
}
MovingObjectType Robot::getObjectType() const
{
    return ROBOT;
}
/*
 *CLASS: RobotC kế thừa class Robot
 */
RobotC::RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal)
        : Robot(index,init_pos, map, criminal,"RobotC")
{
    this->robot_type = C;
}

int RobotC::getDistance(Sherlock *sherlock)
{
    int distance_sherlock = criminal->manhattanDistance(pos, sherlock->getCurrentPosition());
    return distance_sherlock;
}
int RobotC::getDistance(Watson *watson)
{
    int distance_watson = criminal->manhattanDistance(pos, watson->getCurrentPosition());
    return distance_watson;
}
Position RobotC::getNextPosition()
{
    int vitric = -1;
    int vitrir = -1;
    Position nextP = criminal->getPrevPosition();//getNextPosition();//getCurrentPosition();
    vitrir=nextP.getRow();
    vitric=nextP.getCol();
    return Position(vitrir,vitric);
}
void RobotC::move()
{
    Position vitritiep = getNextPosition();
    if (vitritiep == Position::npos){
        return;
    }
    pos.setRow(vitritiep.getRow());
    pos.setCol(vitritiep.getCol());
}
string RobotC::str() const
{
    string ketqua ="Robot[pos=" + pos.str() + ";type=C;dist=]"/* + to_string(getDistance()) */;
    return ketqua;
}
int RobotC::getDistance() const
{
    //Sherlock*sherlock;
    //Watson*watson;
    int distance_sherlock = criminal->manhattanDistance(pos, criminal->getSherlock()->getCurrentPosition());
    int distance_watson = criminal->manhattanDistance(pos, criminal->getWatson()->getCurrentPosition());
    return distance_sherlock + distance_watson;
}
RobotType RobotC::getType() const
{
    return C;
}
/*
 * CLASS: RobotW kế thừa class Robot
 */

RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson)
        : Robot(index,init_pos, map, criminal,"RobotW")
{
    this->robot_type = W;
    this->watson = watson;
}

Position RobotW::getNextPosition()
{
    int vitrir = pos.getRow();
    int vitric = pos.getCol();


//    Sherlock*sherlock;
//    Watson*watson;

    int ketquacuoicungr = -1;
    int ketquacuoicungc = -1;

    int kc=999999; //khoi tao

    if(map->isValid(Position(vitrir - 1, vitric), this) && kcW(vitric, vitrir - 1,watson) < kc){ //len
        ketquacuoicungr = vitrir - 1;
        ketquacuoicungc = vitric;
        kc = kcW(vitric, vitrir - 1,watson);
    }
    if(map->isValid(Position(vitrir, vitric+1), this) && kcW(vitric + 1, vitrir,watson) < kc){ //phai
        ketquacuoicungr = vitrir;
        ketquacuoicungc = vitric + 1;
        kc = kcW(vitric + 1, vitrir,watson);
    }
    if(map->isValid(Position(vitrir + 1, vitric ), this) && kcW(vitric , vitrir + 1,watson) < kc){  //xuong
        ketquacuoicungr = vitrir + 1;
        ketquacuoicungc = vitric;
        kc = kcW(vitric , vitrir + 1,watson);
    }
    if(map->isValid(Position(vitrir, vitric - 1), this) && kcW(vitric - 1 , vitrir ,watson) < kc){ //trai
        ketquacuoicungr = vitrir;
        ketquacuoicungc = vitric - 1;
        kc = kcW(vitric - 1, vitrir,watson);
    }

    return Position(ketquacuoicungr,ketquacuoicungc);
}

void RobotW::move()
{
    Position vitritiep = getNextPosition();
    if (vitritiep == Position::npos){
        return;
    }
    pos.setRow(vitritiep.getRow());
    pos.setCol(vitritiep.getCol());
}

string RobotW::str() const
{
    string ketqua ="Robot[pos=" + pos.str() + ";type=W;dist=" + to_string(getDistance()) +"]" ;
    return ketqua;
}

RobotType RobotW::getType() const
{
    return W;
}

int RobotW::getDistance() const
{
    //Watson*watson;
    int distance_watson = criminal->manhattanDistance(pos, criminal->getWatson()->getCurrentPosition());
    return distance_watson;
}
/*
 * CLASS: RobotS kế thừa class Robot
 */
RobotS::RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock)
        : Robot(index,init_pos, map, criminal,"RobotS")
{
    this->robot_type = S;
    this->sherlock = sherlock;
}

Position RobotS::getNextPosition()
{
    int vitrir = pos.getRow();
    int vitric = pos.getCol();

    int ketquacuoicungr = -1;
    int ketquacuoicungc = -1;

    int kc=999999; //khoi tao

    //SỬA
    if(map->isValid(Position(vitrir - 1, vitric), this) && kcS(vitric, vitrir - 1,sherlock) < kc){ //len
        ketquacuoicungr = vitrir - 1;
        ketquacuoicungc = vitric;
        kc = kcS(vitric, vitrir - 1,sherlock);
    }
    if(map->isValid(Position(vitrir, vitric+1), this) && kcS(vitric + 1, vitrir,sherlock) < kc){ //phai
        ketquacuoicungr = vitrir;
        ketquacuoicungc = vitric + 1;
        kc = kcS(vitric + 1, vitrir,sherlock);
    }
    if(map->isValid(Position(vitrir + 1, vitric ), this) && kcS(vitric , vitrir + 1,sherlock) < kc){  //xuong
        ketquacuoicungr = vitrir + 1;
        ketquacuoicungc = vitric;
        kc = kcS(vitric , vitrir + 1,sherlock);
    }
    if(map->isValid(Position(vitrir, vitric - 1), this) && kcS(vitric - 1 , vitrir ,sherlock) < kc){ //trai
        ketquacuoicungr = vitrir;
        ketquacuoicungc = vitric - 1;
        kc = kcS(vitric - 1, vitrir,sherlock);
    }

    return Position(ketquacuoicungr,ketquacuoicungc);
}
void RobotS::move()
{
    Position vitritiep = getNextPosition();
    if (vitritiep == Position::npos){
        return;
    }
    pos.setRow(vitritiep.getRow());
    pos.setCol(vitritiep.getCol());
}

string RobotS::str() const
{
    string ketqua ="Robot[pos=" + pos.str() + ";type=S;dist=" + to_string(getDistance()) +"]" ;
    return ketqua;
}

RobotType RobotS::getType() const
{
    return S;
}

int RobotS::getDistance() const
{
    Sherlock*sherlock;
    int distance_sherlock = criminal->manhattanDistance(pos, criminal->getSherlock()->getCurrentPosition());
    return distance_sherlock;
}
/*
 * CLASS: RobotSW kế thừa class Robot
 */
RobotSW::RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson)
        : Robot(index,init_pos, map, criminal,"RobotSW")
{
    this->robot_type = SW;
    this->sherlock = sherlock;
    this->watson = watson;
}

Position RobotSW::getNextPosition()
{
    int vitric = pos.getCol();
    int vitrir = pos.getRow();

    int ketquacuoicungr = -1;
    int ketquacuoicungc = -1;
    int kc = 999999;

    //Len
    if (map->isValid(Position(vitrir - 2, vitric), this) && Sum(vitric, vitrir - 2, sherlock, watson) < kc){
        ketquacuoicungr = vitrir - 2;
        ketquacuoicungc = vitric;
        kc = Sum(vitric, vitrir - 2, sherlock, watson);
    }
    //giamr tangc
    if (map->isValid(Position(vitrir - 1, vitric + 1), this) && Sum(vitric + 1, vitrir - 1, sherlock, watson) < kc){
        ketquacuoicungr = vitrir - 1;
        ketquacuoicungc = vitric + 1;
        kc = Sum(vitric + 1, vitrir - 1, sherlock, watson);
    }

    //Phai
    if (map->isValid(Position(vitrir, vitric + 2), this) && Sum(vitric + 2, vitrir, sherlock, watson) < kc){
        ketquacuoicungr = vitrir;
        ketquacuoicungc = vitric + 2;
        kc = Sum(vitric + 2, vitrir, sherlock, watson);
    }
    //tang
    if (map->isValid(Position(vitrir + 1, vitric + 1), this) && Sum(vitric + 1, vitrir + 1, sherlock, watson) < kc){
        ketquacuoicungr = vitrir + 1;
        ketquacuoicungc = vitric + 1;
        kc = Sum(vitric + 1, vitrir + 1, sherlock, watson);
    }

    //Xuong
    if (map->isValid(Position(vitrir + 2, vitric), this) && Sum(vitric, vitrir + 2, sherlock, watson) < kc){
        ketquacuoicungr = vitrir + 2;
        ketquacuoicungc = vitric;
        kc = Sum(vitric, vitrir + 2, sherlock, watson);
    }
    //tangr giamc
    if (map->isValid(Position(vitrir + 1, vitric - 1), this) && Sum(vitric - 1, vitrir + 1, sherlock, watson) < kc){
        ketquacuoicungr = vitrir + 1;
        ketquacuoicungc = vitric - 1;
        kc = Sum(vitric - 1, vitrir + 1, sherlock, watson);
    }

    //Trai
    if (map->isValid(Position(vitrir, vitric - 2), this) && Sum(vitric - 2, vitrir, sherlock, watson) < kc){
        ketquacuoicungr = vitrir;
        ketquacuoicungc = vitric - 2;
        kc = Sum(vitric - 2, vitrir, sherlock, watson);
    }
    //giam
    if (map->isValid(Position(vitrir - 1, vitric - 1), this) && Sum(vitric - 1, vitrir - 1, sherlock, watson) < kc){
        ketquacuoicungr = vitrir - 1;
        ketquacuoicungc = vitric - 1;
        kc = Sum(vitric - 1, vitrir - 1, sherlock, watson);
    }


    return Position(ketquacuoicungr, ketquacuoicungc);
}
string RobotSW::str() const
{
    string ketqua ="Robot[pos=" + pos.str() + ";type=SW;dist=" + to_string(getDistance()) + "]" ;
    return ketqua;
}
RobotType RobotSW::getType() const
{
    return SW;
}
int RobotSW::getDistance() const
{
//    Sherlock*sherlock;
//    Watson*watson;
    int distance_sherlock = criminal->manhattanDistance(pos, criminal->getSherlock()->getCurrentPosition());
    int distance_watson = criminal->manhattanDistance(pos, criminal->getWatson()->getCurrentPosition());
    return distance_sherlock + distance_watson;
}
void RobotSW::move()
{
    Position vitritiep = getNextPosition();
    if (vitritiep == Position::npos){
        return;
    }
    pos.setRow(vitritiep.getRow());
    pos.setCol(vitritiep.getCol());
}
/*
 * CLASS: ArrayMovingObject
 */

ArrayMovingObject::ArrayMovingObject(int capacity) : capacity(capacity), count(0)
{
    arr_mv_objs = new MovingObject * [capacity];
    for(int i = 0; i < capacity; i++){
        arr_mv_objs[i] = NULL;
    }
}
ArrayMovingObject::~ArrayMovingObject()
{
    for (int i = 3; i < count; i++){
        if (arr_mv_objs[i]->getObjectType() == SHERLOCK) continue;
        if (arr_mv_objs[i]->getObjectType() == WATSON) continue;
        if (arr_mv_objs[i]->getObjectType() == CRIMINAL) continue;
        delete arr_mv_objs[i];
    }

    delete [] arr_mv_objs;
}
bool ArrayMovingObject::isFull() const
{
    if (count == capacity) return true;
    return false;
}
bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    if (isFull()){
        return false;
    }
    else{
        for(int i = 0; i < count; i++){
            if (arr_mv_objs[i] == mv_obj){
                return true;
            }
        }
        arr_mv_objs[count] = mv_obj;
        count++;
    }
    return true;
}
MovingObject *ArrayMovingObject::get(int index) const
{
    if (index < 0 || index >= count){
        return NULL;
    }
    return arr_mv_objs[index];
}

int ArrayMovingObject::size() const
{
    return count;
}

string ArrayMovingObject::str() const
{
    //ArrayMovingObject[count=<count>;capacity=<capacity>;<MovingObject1>;...]
    if (count == 0) return "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity);
    string ketqua = "ArrayMovingObject[count=" + to_string(count) + ";capacity=" + to_string(capacity) + ";";
    for(int i = 0; i < count; i++){
        ketqua += arr_mv_objs[i] ->str();
        if (i != count - 1){
            ketqua += ";";
        }
    }
    ketqua += "]";
    return ketqua;
}
/*
 * CLASS: Configuration
 */
Configuration::Configuration(const string &filepath)
{
    num_fake_walls = 0;
    num_walls = 0;
    num_steps = 0;
    sherlock_init_exp = 0;
    sherlock_moving_rule = "";
    watson_init_exp = 0;
    watson_moving_rule = "";
    sherlock_init_hp = 1;
    watson_init_hp= 1;
    sherlock_init_pos = Position::npos;
    watson_init_pos = Position::npos;
    criminal_init_pos = Position::npos;
    arr_fake_walls = nullptr;
    arr_walls = nullptr;
    map_num_cols = 0;
    map_num_rows = 0;
    max_num_moving_objects = 0;


    ifstream docfile(filepath);
    string dong;
    if (!docfile.is_open()) {
        return;
    }
    while(getline(docfile, dong)) {
        istringstream vitri(dong);
        string giatrican;
        vitri >> giatrican;
        string timchu = giatrican.substr(0, giatrican.find("=", 1));
        string dulieu = giatrican.substr(giatrican.find("=", 1) + 1, giatrican.size());
        if (timchu == "MAP_NUM_ROWS") {
            int nr = stoi(dulieu);
            map_num_rows = nr;
        } else if (timchu == "MAP_NUM_COLS") {
            int nc = stoi(dulieu);
            map_num_cols = nc;
        } else if (timchu == "MAX_NUM_MOVING_OBJECTS") {
            int mnmo = stoi(dulieu);
            max_num_moving_objects = mnmo;
        } else if (timchu == "ARRAY_WALLS") {
            string aw = dulieu;
            //SỬA
            if (aw[0] == '[' && aw[1] == ']'){
                arr_walls = nullptr;
                num_walls = 0;
                continue;
            }
            //SỬA
            int dodai = aw.size();
            int x, y;
            Position* tuong; // Sử dụng con trỏ thay
            string awcon = aw.substr(1, dodai - 2);
            tuong = new Position[awcon.size()]; // Cấp phát mảng động
            int index = 0;
            size_t pos = 0;
            while ((pos = awcon.find(";")) != string::npos) {
                string token = awcon.substr(0, pos);
                x = stoi(token.substr(token.find("(") + 1, token.find(",")));
                y = stoi(token.substr(token.find(",") + 1, token.find(")")));
                tuong[index++] = {x, y};
                awcon.erase(0, pos + 1);
            }
            //SỬA
            if (aw.size() != 0){
                x = stoi(awcon.substr(awcon.find("(") + 1, awcon.find(",")));
                y = stoi(awcon.substr(awcon.find(",") + 1, awcon.find(")")));
                tuong[index++] = {x, y};
            }
            //SỬA
            num_walls = index;
            arr_walls = new Position[num_walls];
            for (int i = 0; i < num_walls; i++) {
                arr_walls[i] = tuong[i];
            }

            delete tuong;
        } else if (timchu == "ARRAY_FAKE_WALLS") {
            string afw = dulieu;
            if (afw[0] == '[' && afw[1] == ']'){
                arr_fake_walls = nullptr;
                num_fake_walls = 0;
                continue;
            }
            int dodai = afw.size();
            int x, y;
            Position* tuong; // Sử dụng con trỏ thay vì vector
            string awcon = afw.substr(1, dodai - 2);
            tuong = new Position[awcon.size()]; // Cấp phát mảng động
            int index = 0;
            size_t pos = 0;
            while ((pos = awcon.find(";")) != string::npos) {
                string token = awcon.substr(0, pos);
                x = stoi(token.substr(token.find("(") + 1, token.find(",")));
                y = stoi(token.substr(token.find(",") + 1, token.find(")")));
                tuong[index++] = {x, y};
                awcon.erase(0, pos + 1);
            }
            //SỬA
            if (afw.size() != 0){
                x = stoi(awcon.substr(awcon.find("(") + 1, awcon.find(",")));
                y = stoi(awcon.substr(awcon.find(",") + 1, awcon.find(")")));
                tuong[index++] = {x, y};
            }
            //SỬA
            num_fake_walls = index;
            arr_fake_walls = new Position[num_fake_walls];
            for (int i = 0; i < num_fake_walls; i++) {
                arr_fake_walls[i] = tuong[i];
            }

            delete tuong;
        } else if (timchu == "SHERLOCK_MOVING_RULE") {
            string smr = dulieu;
            sherlock_moving_rule = smr;
        } else if (timchu == "SHERLOCK_INIT_POS") {
            int x, y;
            string xet = dulieu;
            x = stoi(xet.substr(xet.find("(") + 1, xet.find(",")));
            y = stoi(xet.substr(xet.find(",") + 1, xet.find(")")));
            sherlock_init_pos.setRow(x);
            sherlock_init_pos.setCol(y);
        } else if (timchu == "SHERLOCK_INIT_HP") {
            int sih = stoi(dulieu);
            sherlock_init_hp = sih;
        } else if (timchu == "SHERLOCK_INIT_EXP") {
            int sie = stoi(dulieu);
            sherlock_init_exp = sie;
        } else if (timchu == "WATSON_MOVING_RULE") {
            string wmr = dulieu;
            watson_moving_rule = wmr;
        } else if (timchu == "WATSON_INIT_POS") {
            int x, y;
            string xet = dulieu;
            x = stoi(xet.substr(xet.find("(") + 1, xet.find(",")));
            y = stoi(xet.substr(xet.find(",") + 1, xet.find(")")));
            watson_init_pos.setRow(x);
            watson_init_pos.setCol(y);
        } else if (timchu == "WATSON_INIT_HP") {
            int wih = stoi(dulieu);
            watson_init_hp = wih;
        } else if (timchu == "WATSON_INIT_EXP") {
            int wie = stoi(dulieu);
            watson_init_exp = wie;
        } else if (timchu == "CRIMINAL_INIT_POS") {
            int x, y;
            string xet = dulieu;
            x = stoi(xet.substr(xet.find("(") + 1, xet.find(",")));
            y = stoi(xet.substr(xet.find(",") + 1, xet.find(")")));
            criminal_init_pos.setRow(x);
            criminal_init_pos.setCol(y);
        } else if (timchu == "NUM_STEPS") {
            int ns = stoi(dulieu);
            num_steps = ns;
        }
    }
}

Configuration::~Configuration()
{
    delete[] arr_walls;
    delete[] arr_fake_walls;
}
string Configuration::str() const
{
    stringstream ss;
    ss << "Configuration[" << endl;
    ss << "MAP_NUM_ROWS=" << map_num_rows << endl;
    ss << "MAP_NUM_COLS=" << map_num_cols << endl;
    ss << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << endl;
    ss << "NUM_WALLS=" << num_walls << endl;
    ss << "ARRAY_WALLS=[";
    for (int i = 0; i < num_walls; ++i) {
        ss << "(" << arr_walls[i].getRow() << "," << arr_walls[i].getCol() << ")";
        if (i < num_walls - 1) ss << ";";
    }
    ss << "]" << endl;
    ss << "NUM_FAKE_WALLS=" << num_fake_walls << endl;
    ss << "ARRAY_FAKE_WALLS=[";
    for (int i = 0; i < num_fake_walls; ++i) {
        ss << "(" << arr_fake_walls[i].getRow() << "," << arr_fake_walls[i].getCol() << ")";
        if (i < num_fake_walls - 1) ss << ";";
    }
    ss << "]" << endl;
    ss << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << endl;
    ss << "SHERLOCK_INIT_POS=(" << sherlock_init_pos.getRow() << "," << sherlock_init_pos.getCol() << ")" << endl;
    ss << "SHERLOCK_INIT_HP=" << sherlock_init_hp << endl;
    ss << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << endl;
    ss << "WATSON_MOVING_RULE=" << watson_moving_rule << endl;
    ss << "WATSON_INIT_POS=(" << watson_init_pos.getRow() << "," << watson_init_pos.getCol() << ")" << endl;
    ss << "WATSON_INIT_HP=" << watson_init_hp << endl;
    ss << "WATSON_INIT_EXP=" << watson_init_exp << endl;
    ss << "CRIMINAL_INIT_POS=(" << criminal_init_pos.getRow() << "," << criminal_init_pos.getCol() << ")" << endl;
    ss << "NUM_STEPS=" << num_steps << endl;
    ss << "]";
    return ss.str();

}
/*
 * CLASS: StudyPinkProgram
 */
StudyPinkProgram::StudyPinkProgram(const string &config_file_path)
{
    config = new Configuration(config_file_path);
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);

    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
}
StudyPinkProgram::~StudyPinkProgram()
{
    delete sherlock;
    delete watson;
    delete criminal;
    delete map;
    delete arr_mv_objs;
    delete config;
}
bool StudyPinkProgram::isStop() const {
    return arr_mv_objs->checkMeet(0) || sherlock->getHP() == 1 || watson->getHP() == 1;
}
void StudyPinkProgram::run(bool verbose, ofstream &OUTPUT)
{
    //if (verbose == false) return;
    if (!OUTPUT.is_open())
    {
        return;
    }
    bool isStop; //= arr_mv_objs->checkMeet(0) || sherlock->getHP() == 0 || watson->getHP() == 0;
    if (sherlock->getCurrentPosition() == watson ->getCurrentPosition() || sherlock->getCurrentPosition() == criminal->getCurrentPosition()
        || watson ->getCurrentPosition() == criminal->getCurrentPosition()) return;
    for (int istep = 0; istep < config->num_steps && !isStop; ++istep)
    {
        isStop = arr_mv_objs->checkMeet(0) || sherlock->getHP() == 1 || watson->getHP() == 1;
        if (isStop)
            break;
        for (int i = 0; i < arr_mv_objs->size() && !isStop; ++i)
        {
            if (istep == 16 && i == 2){
                int x = 1;
            }
            if (isStop)
                break;
            OUTPUT << endl
                   << "*************AFTER MOVE*************" << endl;
            OUTPUT
                    << "ROUND : " << istep << " - TURN : " << i << endl;


            if (istep == 9 && i == 3){
                string tempp;
            }
            arr_mv_objs->get(i)->move();

            isStop = arr_mv_objs->checkMeet(0);
            MovingObject *robot = nullptr;
            if (!isStop){
                if (arr_mv_objs->get(i)->getObjectType() == MovingObjectType::CRIMINAL)
                {
                    robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
                }
            }

            if (robot != nullptr)
            {
                if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
                {
                    if (!arr_mv_objs->add(robot)) {
                        delete robot;
                        robot = nullptr;
                    }

                }
                else
                {
                    delete robot;
                    robot = nullptr;
                }
            }
            isStop = arr_mv_objs->checkMeet(i);
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
    }
}

// *CLASS: MagicBook
ItemType MagicBook::getType() const
{
    return MAGIC_BOOK;
}
string MagicBook::str() const
{
    return "MagicBook";
}
bool MagicBook::canUse(Character *obj, Robot *robot)
{
    if ((obj->getObjectType() == SHERLOCK || obj->getObjectType() == WATSON) && robot == nullptr){
        if (obj->getObjectType() == SHERLOCK){
            if (dynamic_cast<Sherlock*>(obj)->getEXP() <= 350){
                return true;
            }
        }
        else{
            if (dynamic_cast<Watson*>(obj)->getEXP() <= 350){
                return true;
            }
        }
    }

    return false;
}
void MagicBook::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot)){
        if (obj->getObjectType() == SHERLOCK || obj->getObjectType() == WATSON){
            if (obj->getObjectType() == SHERLOCK){
                dynamic_cast<Sherlock*>(obj)->setEXP(ceil(dynamic_cast<Sherlock*>(obj)->getEXP() * 1.25));
                if (dynamic_cast<Sherlock*>(obj)->getEXP() > 900){
                    dynamic_cast<Sherlock*>(obj)->setEXP(900);
                }
            }
            else{
                dynamic_cast<Watson*>(obj)->setEXP(ceil(dynamic_cast<Watson*>(obj)->getEXP() * 1.25));
                if (dynamic_cast<Watson*>(obj)->getEXP() > 900){
                    dynamic_cast<Watson*>(obj)->setEXP(900);
                }
            }
        }
    }
}
// *CLASS: EnergyDrink
ItemType EnergyDrink::getType() const
{
    return ENERGY_DRINK;
}
string EnergyDrink::str() const
{
    return "EnergyDrink";
}
bool EnergyDrink::canUse(Character *obj, Robot *robot)
{
    if ((obj->getObjectType() == SHERLOCK || obj->getObjectType() == WATSON) && robot == nullptr){
        if (obj->getObjectType() == SHERLOCK){
            if (dynamic_cast<Sherlock*>(obj)->getHP() <= 100){
                return true;
            }
        }
        else{
            if (dynamic_cast<Watson*>(obj)->getHP() <= 100){
                return true;
            }
        }
    }

    return false;
}
void EnergyDrink::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot)){
        if (obj->getObjectType() == SHERLOCK || obj->getObjectType() == WATSON){
            if (obj->getObjectType() == SHERLOCK){
                dynamic_cast<Sherlock*>(obj)->setHP(ceil(dynamic_cast<Sherlock*>(obj)->getHP() * 1.2));
                if (dynamic_cast<Sherlock*>(obj)->getHP() > 500){
                    dynamic_cast<Sherlock*>(obj)->setHP(500);
                }
            }
            else{
                dynamic_cast<Watson*>(obj)->setHP(ceil(dynamic_cast<Watson*>(obj)->getHP() * 1.2));
                if (dynamic_cast<Watson*>(obj)->getHP() > 500){
                    dynamic_cast<Watson*>(obj)->setHP(500);
                }
            }
        }
    }

}
// *CLASS: FirstAid
ItemType FirstAid::getType() const
{
    return FIRST_AID;
}
string FirstAid::str() const
{
    return "FirstAid";
}
bool FirstAid::canUse(Character *obj, Robot *robot)
{
    if ((obj->getObjectType() == SHERLOCK || obj->getObjectType() == WATSON) && robot == nullptr){
        if (obj->getObjectType() == SHERLOCK){
            if (dynamic_cast<Sherlock*>(obj)->getHP() <= 100 || dynamic_cast<Sherlock*>(obj)->getEXP() <= 350){
                return true;
            }
        }
        else{
            if (dynamic_cast<Watson*>(obj)->getHP() <= 100 || dynamic_cast<Watson*>(obj)->getEXP() <= 350){
                return true;
            }
        }
    }

    return false;
}
void FirstAid::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot)){
        if (obj->getObjectType() == SHERLOCK || obj->getObjectType() == WATSON){
            if (obj->getObjectType() == SHERLOCK){
                dynamic_cast<Sherlock*>(obj)->setHP(ceil(dynamic_cast<Sherlock*>(obj)->getHP() * 1.5));
                if (dynamic_cast<Sherlock*>(obj)->getHP() > 500){
                    dynamic_cast<Sherlock*>(obj)->setHP(500);
                }
            }
            else{
                dynamic_cast<Watson*>(obj)->setHP(ceil(dynamic_cast<Watson*>(obj)->getHP() * 1.5));
                if (dynamic_cast<Watson*>(obj)->getHP() > 500){
                    dynamic_cast<Watson*>(obj)->setHP(500);
                }
            }
        }
    }

}
// *CLASS: ExcemptionCard
ItemType ExcemptionCard::getType() const
{
    return  EXCEMPTION_CARD;
}
string ExcemptionCard::str() const
{
    return "ExcemptionCard";
}
bool ExcemptionCard::canUse(Character *obj, Robot *robot)
{
    if (obj->getObjectType() == SHERLOCK && robot != nullptr){
        if (dynamic_cast<Sherlock*>(obj)->getHP() % 2 != 0){
            return true;
        }
    }
    return false;
}
void ExcemptionCard::use(Character *obj, Robot *robot)
{
    if (canUse(obj, robot)){

    }
}
// *CLASS: PassingCard
PassingCard::PassingCard(int i, int j)
{
    int t = (i * 11 + j) % 4;
    if (t == 0){
        challenge = "RobotS";
    }
    else if (t == 1){
        challenge = "RobotC";
    }
    else if (t == 2){
        challenge = "RobotSW";
    }
    else if (t == 3){
        challenge = "all";
    }
}

PassingCard::PassingCard(string s)
{
    if (s == "RobotS") {
        challenge = "RobotS";
    }
    else if (s == "RobotC"){
        challenge = "RobotC";
    }
    else if (s == "RobotSW"){
        challenge = "RobotSW";
    }
    else if (s == "all"){
        challenge = "all";
    }
}
ItemType PassingCard::getType() const
{
    return PASSING_CARD;
}
string PassingCard::str() const
{
    return "PassingCard";
}
bool PassingCard::canUse(Character *obj, Robot *robot)
{
    if (obj->getObjectType() == WATSON && robot != nullptr){
        if (dynamic_cast<Watson*>(obj)->getHP() % 2 == 0){
            return true;
        }
    }
    return false;
}
void PassingCard::use(Character *obj, Robot *robot)
{
    if (challenge == "all"){

    }
    else if(robot->getType() == C && challenge == "RobotC"){

    }
    else if (robot->getType() == S && challenge == "RobotS"){

    }
    else if (robot->getType() == W && challenge == "RobotW"){

    }
    else if (robot->getType() == SW && challenge == "RobotSW"){

    }
    else{
        Watson* watsonObj = dynamic_cast<Watson*>(obj);
        int expHienTai = watsonObj->getEXP();
        watsonObj->setEXP(expHienTai - 50);
        if(watsonObj->getEXP() < 0){
            watsonObj->setEXP(0);
        }
    }
}
// *CLASS: BaseBag
BaseBag::BaseBag(int capacity)
{
    this->size = 0;
    this->capacity = capacity;
    this->head = nullptr;
}
BaseBag::~BaseBag()
{

    for (int i = 0; i < size; i++){
        Node* temp = head;
        head = head -> next;
        //delete temp->item;
        delete temp;
    }
}
bool BaseBag::insert(BaseItem *item)
{
    Node* vatPhamMoi = new Node(item);
    if (this->head == nullptr && size == 0){
        head = vatPhamMoi;
        size += 1;
        return true;
    }

    if (size < capacity){
        vatPhamMoi->next = head;
        head = vatPhamMoi;
        size += 1;
        return true;
    }

    vatPhamMoi->item = nullptr;
    delete vatPhamMoi;
    return false;

}

BaseItem* BaseBag::find(ItemType itemType) {
    Node* temp = this->head;

    for (int i = 0; i < size; i++){
        if (temp->item->getType() == itemType){
            return temp->item;
        }
        temp=temp->next;
    }

    return nullptr;
}
BaseItem* BaseBag::get(ItemType itemType)
{

    Node* temp = head;

    for (int i = 0; i < size; i++){
        if (temp->item->getType() == itemType){
            break;
        }
        temp = temp->next;
    }

    BaseItem* returnItem = nullptr;

    if (temp != nullptr){
        swap(temp->item, head->item);
        temp = head;
        head = head -> next;
        size -= 1;
        returnItem = temp->item;
        temp->item = nullptr;
        delete temp;
        return returnItem;
    }

    //delete temp;

    return nullptr;
}
string BaseBag::str() const
{
    string s;
    Node* temp = head;
    for (int i = 0; i < size; i++){
        if (i != size - 1){
            s = s + temp->item->str() + ",";
        }
        else s = s + temp->item->str();
        temp = temp->next;
    }
    return "Bag[count=" + to_string(size) + ";" + s +"]";
}
// *CLASS: SherlockBag
SherlockBag::SherlockBag(Sherlock *character)
        : BaseBag(
        13
)
{
    sherlock = character;
}
BaseItem *SherlockBag::get()
{
    Node* temp = head;
    for (int i = 0; i < size; i++){
        if (temp->item->canUse(this->sherlock, nullptr)){
            break;
        }
        temp = temp->next;
    }

    BaseItem* returnItem = nullptr;

    if (temp != nullptr){
        swap(temp->item, head->item);
        temp = head;
        head = head -> next;
        size -= 1;
        returnItem = temp->item;
        temp->item = nullptr;
        delete temp;
        return returnItem;
    }

    //delete temp;
    return nullptr;

}
// *CLASS: WatsonBag
WatsonBag::WatsonBag(Watson *character)
        : BaseBag(
        15
)
{
    watson = character;
}
BaseItem *WatsonBag::get()
{
    Node* temp = head;
    for (int i = 0; i < size; i++){
        if (temp->item->canUse(this->watson, nullptr)){
            break;
        }
        temp = temp->next;
    }

    BaseItem * returnItem = nullptr;

    if (temp != nullptr){
        swap(temp->item, head->item);

        temp = head;
        head = head -> next;
        size -= 1;
        returnItem = temp->item;
        temp->item = nullptr;
        delete temp;
        return returnItem;
    }

    return nullptr;

}

// *CLASS: ArrayMovingObject
bool ArrayMovingObject::checkMeet(int index)
{

    MovingObjectType theloai = arr_mv_objs[index]->getObjectType();

    for (int i = 0; i < this->count; i++){
        if (arr_mv_objs[i]->getCurrentPosition() == arr_mv_objs[index]->getCurrentPosition()){
            if (theloai == SHERLOCK){
                Sherlock * sherlock = dynamic_cast<Sherlock*>(arr_mv_objs[index]);
                Criminal * criminal = dynamic_cast<Criminal*>(arr_mv_objs[0]);
                if (arr_mv_objs[i]->getObjectType() == ROBOT){
                    Robot* robottamthoi = dynamic_cast<Robot*>(arr_mv_objs[i]);
                    if (robottamthoi->getType() == C){
                        if (sherlock->meet(dynamic_cast<RobotC*>(robottamthoi)) == true) {
                            sherlock->setPos(criminal->getCurrentPosition());
                            return true;
                        }
                    }
                    else{
                        if (robottamthoi->getType() == S){
                            sherlock->meet(dynamic_cast<RobotS*>(robottamthoi));
                        }
                        else if (robottamthoi->getType() == W){
                            sherlock->meet(dynamic_cast<RobotW*>(robottamthoi));
                        }
                        else if (robottamthoi->getType() == SW){
                            sherlock->meet(dynamic_cast<RobotSW*>(robottamthoi));
                        }
                    }
                }
                else if (arr_mv_objs[i]->getObjectType() == WATSON){
                    sherlock->meet(dynamic_cast<Watson*>(arr_mv_objs[i]));
                }
                else if (arr_mv_objs[i]->getObjectType() == CRIMINAL){
                    return true;
                }

            }
            else if (theloai == WATSON){

                Watson* watson = dynamic_cast<Watson*>(arr_mv_objs[index]);

                if (arr_mv_objs[i]->getObjectType() == ROBOT){
                    Robot* robottamthoi = dynamic_cast<Robot*>(arr_mv_objs[i]);
                    if (robottamthoi->getType() == C){
                        watson->meet(dynamic_cast<RobotC*>(robottamthoi));
                    }
                    else if (robottamthoi->getType() == S){
                        watson->meet(dynamic_cast<RobotS*>(robottamthoi));
                    }
                    else if (robottamthoi->getType() == W){
                        watson->meet(dynamic_cast<RobotW*>(robottamthoi));
                    }
                    else if (robottamthoi->getType() == SW){
                        watson->meet(dynamic_cast<RobotSW*>(robottamthoi));
                    }
                }
                else if (arr_mv_objs[i]->getObjectType() == SHERLOCK){
                    watson->meet(dynamic_cast<Sherlock*>(arr_mv_objs[i]));
                }
                else if (arr_mv_objs[i]->getObjectType() == CRIMINAL){
                    return true;
                }

            }
            else if (theloai == CRIMINAL){

                if (arr_mv_objs[i]->getObjectType() == ROBOT){

                }
                else if (arr_mv_objs[i]->getObjectType() == SHERLOCK || arr_mv_objs[i]->getObjectType() == WATSON){
                    return true;
                }

            }
            else if (theloai == ROBOT){

                if (arr_mv_objs[i]->getObjectType() == ROBOT){

                }
                else if (arr_mv_objs[i]->getObjectType() == SHERLOCK){
                    Sherlock* sherlock = dynamic_cast<Sherlock*>(arr_mv_objs[i]);
                    Robot* robot = dynamic_cast<Robot*>(arr_mv_objs[index]);
                    Criminal * criminal = dynamic_cast<Criminal*>(arr_mv_objs[0]);
                    if (robot->getType() == C){
                        if (sherlock->meet(dynamic_cast<RobotC*>(arr_mv_objs[index]))) {
                            sherlock->setPos(criminal->getCurrentPosition());
                            return true;
                        }
                    }
                    else{
                        if (robot->getType() == W){
                            sherlock->meet(dynamic_cast<RobotW*>(robot));
                        }
                        else if (robot->getType() == S){
                            sherlock->meet(dynamic_cast<RobotS*>(robot));
                        }
                        else if (robot->getType() == SW){
                            sherlock->meet(dynamic_cast<RobotSW*>(robot));
                        }
                    }
                }
                else if (arr_mv_objs[i]->getObjectType() == WATSON){
                    Watson* watson = dynamic_cast<Watson*>(arr_mv_objs[i]);
                    Robot* robot = dynamic_cast<Robot*>(arr_mv_objs[index]);
                    if (robot->getType() == C){
                        watson->meet(dynamic_cast<RobotC*>(arr_mv_objs[index]));
                    }
                    else if (robot->getType() == W){
                        watson->meet(dynamic_cast<RobotW*>(robot));
                    }
                    else if (robot->getType() == S){
                        watson->meet(dynamic_cast<RobotS*>(robot));
                    }
                    else if (robot->getType() == SW){
                        watson->meet(dynamic_cast<RobotSW*>(robot));
                    }
                }
                else if (arr_mv_objs[i]->getObjectType() == CRIMINAL){

                }
            }
        }
    }
    return false;
}
// *CLASS: Sherlock
bool Sherlock::meet(RobotS *robotS)
{
    // TODO: Xử lý khi gặp robot S

    if (this->exp > 400){
        // bool check = this->bag->findTest(EXCEMPTION_CARD);
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotS)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotS);
                // delete vatphamsudung;
            }
            else {
                vatphamsudung = nullptr;
                // // delete vatphamsudung;
            }
        }
        // BaseItem * newItem;
        // if (robotS->getItem()->getType() == MAGIC_BOOK){
        //     newItem = new MagicBook();
        // }
        // else if (robotS->getItem()->getType() == ENERGY_DRINK){
        //     newItem = new EnergyDrink();
        // }
        // else if (robotS->getItem()->getType() == FIRST_AID){
        //     newItem = new FirstAid();
        // }
        // else if (robotS->getItem()->getType() == EXCEMPTION_CARD){
        //     newItem = new ExcemptionCard();
        // }
        // else{
        //     newItem = new PassingCard(robotS->getPoshead().getRow(), robotS->getPoshead().getCol());
        // }
        //
        // if(!this->bag->insert(newItem)) {
        //     delete newItem;
        // }

        this->bag->insert(robotS->getItem());

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            // delete vatphamsudung;
        }
        return true;
    }
    else{
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        bool dungchua = false;
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotS)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotS);
                dungchua = true;
                // delete vatphamsudung;
            }
            else dungchua = false;
        }

        if (dungchua == false) exp = ceil(exp * 0.9);
        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr){
            if (vatphamsudung != nullptr) {
                vatphamsudung->use(this, NULL);
                // delete vatphamsudung;
            }
            return false;
        }
    }
    return true;
}
bool Sherlock::meet(RobotW *robotW)
{
    BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
    if (vatphamsudung != nullptr){
        if(vatphamsudung->canUse(this, robotW)){
            vatphamsudung = this->bag->get(EXCEMPTION_CARD);
            vatphamsudung->use(this, robotW);
            // delete vatphamsudung;
        }
        else {
            vatphamsudung = nullptr;
            //// delete vatphamsudung;
        }
    }

    // BaseItem * newItem;
    // if (robotW->getItem()->getType() == MAGIC_BOOK){
    //     newItem = new MagicBook();
    // }
    // else if (robotW->getItem()->getType() == ENERGY_DRINK){
    //     newItem = new EnergyDrink();
    // }
    // else if (robotW->getItem()->getType() == FIRST_AID){
    //     newItem = new FirstAid();
    // }
    // else if (robotW->getItem()->getType() == EXCEMPTION_CARD){
    //     newItem = new ExcemptionCard();
    // }
    // else{
    //     newItem = new PassingCard(robotW->getPoshead().getRow(), robotW->getPoshead().getCol());
    // }
    //
    // if(!this->bag->insert(newItem)) {
    //     delete newItem;
    // }

    this->bag->insert(robotW->getItem());

    vatphamsudung = this->bag->get();
    if (vatphamsudung != nullptr) {
        vatphamsudung->use(this, NULL);
        // delete vatphamsudung;
    }
    return true;

}
bool Sherlock::meet(RobotSW *robotSW)
{

    if (this->exp > 300 && this->hp > 335){
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotSW)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotSW);
                // delete vatphamsudung;
            }
            else vatphamsudung = nullptr;
        }

        // BaseItem * newItem;
        // if (robotSW->getItem()->getType() == MAGIC_BOOK){
        //     newItem = new MagicBook();
        // }
        // else if (robotSW->getItem()->getType() == ENERGY_DRINK){
        //     newItem = new EnergyDrink();
        // }
        // else if (robotSW->getItem()->getType() == FIRST_AID){
        //     newItem = new FirstAid();
        // }
        // else if (robotSW->getItem()->getType() == EXCEMPTION_CARD){
        //     newItem = new ExcemptionCard();
        // }
        // else{
        //     newItem = new PassingCard(robotSW->getPoshead().getRow(), robotSW->getPoshead().getCol());
        // }
        //
        // if(!this->bag->insert(newItem)) {
        //     delete newItem;
        // }

        this->bag->insert(robotSW->getItem());

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            // delete vatphamsudung;
        }
        return true;
    }
    else{
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        bool dungchua = false;
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotSW)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotSW);
                // delete vatphamsudung;
                dungchua = true;
            }
            else dungchua = false;
        }

        if (dungchua == false){
            exp = ceil(exp * 0.85);
            hp = ceil(hp * 0.85);
        }
        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr){
            if (vatphamsudung != nullptr) {
                vatphamsudung->use(this, NULL);
                // delete vatphamsudung;
            }
            return false;
        }
    }
    return true;
}
bool Sherlock::meet(RobotC *robotC)
{

    if (this->exp > 500){
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotC)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotC);
                // delete vatphamsudung;
            }
            else vatphamsudung = nullptr;
        }

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            // delete vatphamsudung;
        }

        return true;
    }
    else{
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotC)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotC);
                // delete vatphamsudung;
            }
            else vatphamsudung = nullptr;
        }

        // BaseItem * newItem;
        // if (robotC->getItem()->getType() == MAGIC_BOOK){
        //     newItem = new MagicBook();
        // }
        // else if (robotC->getItem()->getType() == ENERGY_DRINK){
        //     newItem = new EnergyDrink();
        // }
        // else if (robotC->getItem()->getType() == FIRST_AID){
        //     newItem = new FirstAid();
        // }
        // else if (robotC->getItem()->getType() == EXCEMPTION_CARD){
        //     newItem = new ExcemptionCard();
        // }
        // else{
        //     newItem = new PassingCard(robotC->getPoshead().getRow(), robotC->getPoshead().getCol());
        // }
        //
        // if(!this->bag->insert(newItem)) {
        //     delete newItem;
        // }

        this->bag->insert(robotC->getItem());

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            // delete vatphamsudung;
        }

        return false;
    }
    return true;
}
bool Sherlock::meet(Watson *watson)
{

    if (!(this->bag->checkItem(PASSING_CARD) && watson->getBag()->checkItem(EXCEMPTION_CARD))) return false;

    BaseItem* vatphamchowatson = this->bag->get(PASSING_CARD);
    BaseItem* vatphamchosherlock = watson->getBag()->get(EXCEMPTION_CARD);


    //Sherlock

    watson->getBag()->insert(vatphamchowatson);
    vatphamchowatson = this->bag->get(PASSING_CARD);
    while(vatphamchowatson != nullptr){
        watson->getBag()->insert(vatphamchowatson);
        vatphamchowatson = this->bag->get(PASSING_CARD);
    }

    //Watson

    this->bag->insert(vatphamchosherlock);
    vatphamchosherlock = watson->getBag()->get(EXCEMPTION_CARD);
    while(vatphamchosherlock != nullptr){
        this->getBag()->insert(vatphamchosherlock);
        vatphamchosherlock = watson->getBag()->get(EXCEMPTION_CARD);
    }

    return true;
}
// *CLASS: Watson

bool Watson::meet(RobotS *robotS)
{
    BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
    if (vatphamsudung != nullptr) {
        if (vatphamsudung->canUse(this, robotS)) {
            vatphamsudung = this->bag->get(PASSING_CARD);
            vatphamsudung->use(this, robotS);
            // delete vatphamsudung;
        } else {
            vatphamsudung = nullptr;
        }
    }

    vatphamsudung = this->bag->get();
    if (vatphamsudung != nullptr) {
        vatphamsudung->use(this, NULL);
        // delete vatphamsudung;
    }

    return true;
}
bool Watson::meet(RobotW *robotW)
{
    if (this->hp > 350){
        bool dungchua = false;
        BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
        if (vatphamsudung != nullptr){
            if (vatphamsudung->canUse(this, robotW)){
                vatphamsudung = this->bag->get(PASSING_CARD);
                vatphamsudung->use(this, robotW);
                dungchua = true;
                // delete vatphamsudung;
            } else dungchua = false;
        }
        // BaseItem * newItem;
        // if (robotW->getItem()->getType() == MAGIC_BOOK){
        //     newItem = new MagicBook();
        // }
        // else if (robotW->getItem()->getType() == ENERGY_DRINK){
        //     newItem = new EnergyDrink();
        // }
        // else if (robotW->getItem()->getType() == FIRST_AID){
        //     newItem = new FirstAid();
        // }
        // else if (robotW->getItem()->getType() == EXCEMPTION_CARD){
        //     newItem = new ExcemptionCard();
        // }
        // else{
        //     newItem = new PassingCard(robotW->getPoshead().getRow(), robotW->getPoshead().getCol());
        // }
        //
        // if(!this->bag->insert(newItem)) {
        //     delete newItem;
        // }

        this->bag->insert(robotW->getItem());

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            // delete vatphamsudung;
        }
        return true;
    }
    else{
        bool dungchua = false;
        BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
        if (vatphamsudung != nullptr){
            if (vatphamsudung->canUse(this, robotW)){
                vatphamsudung = this->bag->get(PASSING_CARD);
                vatphamsudung->use(this, robotW);
                dungchua = true;
                // delete vatphamsudung;
            } else dungchua = false;
        }
        if (dungchua == true){
            // BaseItem * newItem;
            // if (robotW->getItem()->getType() == MAGIC_BOOK){
            //     newItem = new MagicBook();
            // }
            // else if (robotW->getItem()->getType() == ENERGY_DRINK){
            //     newItem = new EnergyDrink();
            // }
            // else if (robotW->getItem()->getType() == FIRST_AID){
            //     newItem = new FirstAid();
            // }
            // else if (robotW->getItem()->getType() == EXCEMPTION_CARD){
            //     newItem = new ExcemptionCard();
            // }
            // else{
            //     newItem = new PassingCard(robotW->getPoshead().getRow(), robotW->getPoshead().getCol());
            // }
            //
            // if(!this->bag->insert(newItem)) {
            //     delete newItem;
            // }

            this->bag->insert(robotW->getItem());
        }
        if (dungchua == false) hp = ceil(hp * 0.95);
        vatphamsudung = this->bag->get();

        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            // delete vatphamsudung;
        }
        return false;
    }
    return true;
}
bool Watson::meet(RobotSW *robotSW)
{

    if (this->exp > 600 && this->hp > 165){
        bool dungchua = false;
        BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
        if (vatphamsudung != nullptr){
            if (vatphamsudung->canUse(this, robotSW)){
                vatphamsudung = this->bag->get(PASSING_CARD);
                vatphamsudung->use(this, robotSW);
                dungchua = true;
                // delete vatphamsudung;
            } else dungchua = false;
        }
        // BaseItem * newItem;
        // if (robotSW->getItem()->getType() == MAGIC_BOOK){
        //     newItem = new MagicBook();
        // }
        // else if (robotSW->getItem()->getType() == ENERGY_DRINK){
        //     newItem = new EnergyDrink();
        // }
        // else if (robotSW->getItem()->getType() == FIRST_AID){
        //     newItem = new FirstAid();
        // }
        // else if (robotSW->getItem()->getType() == EXCEMPTION_CARD){
        //     newItem = new ExcemptionCard();
        // }
        // else{
        //     newItem = new PassingCard(robotSW->getPoshead().getRow(), robotSW->getPoshead().getCol());
        // }
        //
        // if(!this->bag->insert(newItem)) {
        //     delete newItem;
        // }

        this->bag->insert(robotSW->getItem());

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            // delete vatphamsudung;
        }
        return true;
    }
    else{
        bool dungchua = false;
        BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
        if (vatphamsudung != nullptr){
            if (vatphamsudung->canUse(this, robotSW)){
                vatphamsudung = this->bag->get(PASSING_CARD);
                vatphamsudung->use(this, robotSW);
                dungchua = true;
                // delete vatphamsudung;
            } else dungchua = false;
        }
        if (dungchua == true){
            // BaseItem * newItem;
            // if (robotSW->getItem()->getType() == MAGIC_BOOK){
            //     newItem = new MagicBook();
            // }
            // else if (robotSW->getItem()->getType() == ENERGY_DRINK){
            //     newItem = new EnergyDrink();
            // }
            // else if (robotSW->getItem()->getType() == FIRST_AID){
            //     newItem = new FirstAid();
            // }
            // else if (robotSW->getItem()->getType() == EXCEMPTION_CARD){
            //     newItem = new ExcemptionCard();
            // }
            // else{
            //     newItem = new PassingCard(robotSW->getPoshead().getRow(), robotSW->getPoshead().getCol());
            // }
            //
            // if(!this->bag->insert(newItem)) {
            //     delete newItem;
            // }

            this->bag->insert(robotSW->getItem());
        }
        if (dungchua == false){
            hp = ceil(hp * 0.85);
            exp = ceil(exp * 0.85);
        }

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            // delete vatphamsudung;
        }
        return false;
    }
    return true;
}
bool Watson::meet(RobotC *robotC)
{
    bool dungchua = false;
    BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
    if (vatphamsudung != nullptr){
        if (vatphamsudung->canUse(this, robotC)){
            vatphamsudung = this->bag->get(PASSING_CARD);
            vatphamsudung->use(this, robotC);
            dungchua = true;
            // delete vatphamsudung;
        } else dungchua = false;
    }
    // BaseItem * newItem;
    // if (robotC->getItem()->getType() == MAGIC_BOOK){
    //     newItem = new MagicBook();
    // }
    // else if (robotC->getItem()->getType() == ENERGY_DRINK){
    //     newItem = new EnergyDrink();
    // }
    // else if (robotC->getItem()->getType() == FIRST_AID){
    //     newItem = new FirstAid();
    // }
    // else if (robotC->getItem()->getType() == EXCEMPTION_CARD){
    //     newItem = new ExcemptionCard();
    // }
    // else{
    //     newItem = new PassingCard(robotC->getPoshead().getRow(), robotC->getPoshead().getCol());
    // }
    //
    // if(!this->bag->insert(newItem)) {
    //     delete newItem;
    // }

    this->bag->insert(robotC->getItem());

    vatphamsudung = this->bag->get();
    if (vatphamsudung != nullptr) {
        vatphamsudung->use(this, NULL);
        // delete vatphamsudung;
    }
    return true;
}
bool Watson::meet(Sherlock *sherlock)
{

    if (!(this->bag->checkItem(EXCEMPTION_CARD) && sherlock->getBag()->checkItem(PASSING_CARD))) return false;

    BaseItem* vatphamchowatson = sherlock->getBag()->get(PASSING_CARD);
    BaseItem* vatphamchosherlock = this->bag->get(EXCEMPTION_CARD);
    if (vatphamchowatson == nullptr || vatphamchosherlock == nullptr) return false;

    //Sherlock

    this->bag->insert(vatphamchowatson);
    vatphamchowatson = sherlock->getBag()->get(PASSING_CARD);
    while(vatphamchowatson != nullptr){
        this->getBag()->insert(vatphamchowatson);
        vatphamchowatson = sherlock->getBag()->get(PASSING_CARD);
    }

    //Watson

    sherlock->getBag()->insert(vatphamchosherlock);
    vatphamchosherlock = this->bag->get(EXCEMPTION_CARD);
    while(vatphamchosherlock != nullptr){
        sherlock->getBag()->insert(vatphamchosherlock);
        vatphamchosherlock = this->bag->get(EXCEMPTION_CARD);
    }

    return true;
}

BaseBag *Sherlock::getBag() const
{
    return this->bag;
}
BaseBag *Watson::getBag() const
{
    return this->bag;
}

bool BaseBag::checkItem(ItemType itemType) {

    Node* temp = this->head;

    for (int i = 0; i < this->size; i++){
        if (temp->item->getType() == itemType){
            return true;
        }
        temp = temp->next;
    }
    return false;
}
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
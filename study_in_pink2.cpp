// TODO:
// Chỉnh lại di chuyển của RobotC (gợi ý: thực hiện hàm getPrevPosition cho Criminal)
// Mô tả về các meet thay đổi (đã được confirm 90%)
// File study_in_pink2.h những phần trước "addition" là gốc của đề (không thay đổi)
// Chỉnh tên thuộc tính hp và exp của Sherlock và Watson
// Position có nạp chồng 2 hàm isEqual
// isStop kiểm tra vị trí Sherlock, Watson với Criminal và hp của Sherlock, Watson
// Hàm run chú ý chỉnh từ hàm run() gốc (vị trí gọi printResult và printStep)
// Hàm move của Sherlock và Watson khi exp == 0 sẽ không thực hiện gì
// NOTE:
// chú ý các phần addition nên sửa đổi để tránh đạo code
// nộp Bkel cần xóa đổi lại 2 hàm printResult và printStep gốc, xóa thuộc tính outputFile
#include "study_in_pink2.h"

const Position Position::npos = Position(-1, -1);
/*
 * CLASS: MapElement
 */

MapElement::MapElement(ElementType in_type): type(in_type)
{
    // TODO: constructor

}

MapElement::~MapElement() {}

ElementType MapElement::getType() const
{
    // TODO: get
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
    // TODO: constructor
}
int FakeWall::getReqExp() const
{
    // TODO: get
    return req_exp;
}
/*
 * CLASS: Position
 */

Position::Position(int r, int c ) :r(r),c(c)
{
    // TODO: constructor
}
Position::Position(const string &str_pos)
{
    // TODO: constructor
    r = stoi(str_pos.substr(str_pos.find("(") + 1, str_pos.find(",")));
    c = stoi(str_pos.substr(str_pos.find(",") + 1, str_pos.find(")")));
}
int Position::getRow() const
{
    // TODO: get
    return r;
}
int Position::getCol() const
{
    // TODO: get
    return c;
}
void Position::setRow(int r)
{
    // TODO: set
    this -> r = r;
}
void Position::setCol(int c)
{
    // TODO: set
    this -> c = c;
}
string Position::str() const
{
    // TODO: trả về chuỗi "(<r>,<c>)"
    string tra = "(" + to_string(r)+ "," + to_string(c) + ")";
    return tra;
}
bool Position::isEqual(Position position) const
{
    // TODO: so sánh tọa độ với Position khác
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
    // TODO: constructor
}

MovingObject::~MovingObject(){
//    map = nullptr;
}

Position MovingObject::getCurrentPosition() const
{
    // TODO: get
    return Position(pos.getRow(),pos.getCol());

}
/*
 * CLASS: Character kế thừa class MovingObject
 */
Character::Character(int index, const Position pos, Map *map, const string &name)
        : MovingObject(index,pos,map,name
        // TODO: constructor class chapo
)
{
    // TODO: constructor
}
/*
 * CLASS: Robot kế thừa class MovingObject
 */
Robot::Robot(int index, const Position &pos, Map *map, Criminal *criminal, const string &name)
        : MovingObject(index, pos, map, "Robot"), criminal(criminal) //! khác
{
    // TODO: tính toán loại item
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

RobotType Robot::getType() {
    return this->robot_type;
}

/*
 * CLASS: Sherlock kế thừa class Character
 */
Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), hp(init_hp), exp(init_exp), index_moving_rule(0)
{
    // TODO: thêm thuộc tính bag
    index_moving_rule = 0;
    if (init_hp < 0){
        hp = 0;
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

    //SỬA
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
    //  TODO: trả về chuỗi "Sherlock[index=<index>;pos=<pos>;moving_rule=<moving_rule>]"
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
    // TODO: thêm thuộc tính bag
    index_moving_rule = 0;
    if (init_hp < 0){
        hp = 0;
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
    //Sửa
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
    //  TODO: trả về chuỗi "Watson[index=<index>;pos=<pos>;moving_rule=<moving_rule>]"
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
{

    //Sửa
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    //Sửa

    map = new MapElement**[num_rows];
    // tạo map với giá trị null
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
    for (int i = 0; i < num_rows; i++){
        for (int j = 0; j < num_cols; j++){
            delete map[i][j];
            map[i][j] = nullptr;
        }
    }

    for (int i = 0; i < num_rows; i++){
        delete [] map[i];
    }

    delete [] map;
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
    // TODO: get
    return map[i][j] -> getType();
}
bool Map::isValid(const Position pos, MovingObject *mv_obj) const
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
    // TODO: constructor
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
    // TODO: tính vị trí tiếp theo dựa theo nước đi kế tiếp

    //SỬA
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
    // TODO: di chuyển đến vị trí tiếp theo và cập nhật nước đi tiếp theo
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
    // TODO: trả về chuỗi "Watson[index=<index>;pos=<pos>]"
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
    // TODO: trả về đối tượng class kế thừa từ Robot phù hợp
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
    // TODO: constructor
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
// TODO implement các phương thức getNextPosition, move, str, getType, getDistance
Position RobotC::getNextPosition()
{
    // TODO: tìm vị trí liền sau của Criminal
    Position nextP = criminal->getPrevPosition();//getNextPosition();//getCurrentPosition();
    int vitrir=nextP.getRow();
    int vitric=nextP.getCol();
    return Position(vitrir,vitric);
}
void RobotC::move()
{
    // TODO: di chuyển theo Criminal
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
    // TODO: get
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
    // TODO: constructor
    this->robot_type = W;
    this->watson = watson;
}

Position RobotW::getNextPosition()
{
    // TODO: tìm vị trí tiếp theo gần Watson nhất
    int vitrir = pos.getRow();
    int vitric = pos.getCol();

    //SỬA

//    Sherlock*sherlock;
//    Watson*watson;

    //SỬA

    int ketquacuoicungr = -1;
    int ketquacuoicungc = -1;

    int kc=999999; //khoi tao

    //SỬA
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

    //SỬA
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
    // TODO: get
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
    // TODO: constructor
    this->robot_type = S;
    this->sherlock = sherlock;
}

Position RobotS::getNextPosition()
{
    // TODO: tìm vị trí tiếp theo gần Sherlock nhất
    int vitrir = pos.getRow();
    int vitric = pos.getCol();
    //SỬA

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

    //SỬA
    return Position(ketquacuoicungr,ketquacuoicungc);
}
void RobotS::move()
{
    // TODO: di chuyển về phía Sherlock
    Position vitritiep = getNextPosition();
    if (vitritiep == Position::npos){
        return;
    }
    pos.setRow(vitritiep.getRow());
    pos.setCol(vitritiep.getCol());
}

string RobotS::str() const
{
    // TODO: trả về chuỗi "RobotS[pos=<pos>;type=S;dist=<distance>]"
    string ketqua ="Robot[pos=" + pos.str() + ";type=S;dist=" + to_string(getDistance()) +"]" ;
    return ketqua;
}

RobotType RobotS::getType() const
{
    return S;
}

int RobotS::getDistance() const
{
    // TODO: get
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
    // TODO: constructor
    this->robot_type = SW;
    this->sherlock = sherlock;
    this->watson = watson;
}

// TODO implement các phương thức getNextPosition, move, str, getType, getDistance
Position RobotSW::getNextPosition()
{
    // TODO: tìm vị trí tổng giá trị khoảng cách Sherlock và Watson nhỏ nhất
    int vitric = pos.getCol();
    int vitrir = pos.getRow();

    //SỬA

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
    // TODO: trả về chuỗi "RobotS[pos=<pos>;type=S;dist=<distance>]"
    string ketqua ="Robot[pos=" + pos.str() + ";type=SW;dist=" + to_string(getDistance()) + "]" ;
    return ketqua;
}
RobotType RobotSW::getType() const
{
    return SW;
}
int RobotSW::getDistance() const
{
    // TODO: get tổng khoảng cách đến Sherlock và Watson
//    Sherlock*sherlock;
//    Watson*watson;
    int distance_sherlock = criminal->manhattanDistance(pos, criminal->getSherlock()->getCurrentPosition());
    int distance_watson = criminal->manhattanDistance(pos, criminal->getWatson()->getCurrentPosition());
    return distance_sherlock + distance_watson;
}
void RobotSW::move()
{
    // TODO: di chuyển đến gần cả Sherlock và Watson
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
    // TODO: constructor
    arr_mv_objs = new MovingObject * [capacity];
    for(int i = 0; i < capacity; i++){
        arr_mv_objs[i] = NULL;
    }
}
ArrayMovingObject::~ArrayMovingObject()
{
    // TODO: destructor
    for (int i = 0; i < count; i++){
        delete arr_mv_objs[i];
    }

    delete [] arr_mv_objs;
}
bool ArrayMovingObject::isFull() const
{
    // TODO: kiểm tra số lượng đối tượng đã đầy hay chưa
    if (count == capacity) return true;
    return false;
}
bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    // TODO: thêm đối tượng mới vào cuối mảng đối tượng
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
    // TODO: trả về đối tượng có index tương ứng
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
    // TODO: trả về chuỗi biểu diễn mảng
    //ArrayMovingObject[count=<count>;capacity=<capacity>;<MovingObject1>;...]
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
    //    TODO: constructor
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
    // TODO: destructor
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
    delete map;
    delete config;
    delete arr_mv_objs;
}

//void StudyPinkProgram::printMap(ofstream &OUTPUT) const
//{
//    for (int i = -1; i < config->map_num_cols; i++)
//    {
//        if (i == -1){
//            //OUTPUT << setw(6) << ""
//            //       << "|";
//        }
//
//        else
//            OUTPUT << setw(7) << i << "|";
//    }
//    OUTPUT << endl;
//    for (int i = 0; i < config->map_num_rows; i++)
//    {
//        //OUTPUT << setw(6) << i << "|";
//        for (int j = 0; j < config->map_num_cols; j++)
//        {
//            int idx = map->getElementType(i, j);
//            string nameElement[3] = {"     ", "IIIII", "-----"};
//            string nameChar[4] = {"S", "W", "C", "R"};
//            string robotName[4] = {"0", "1", "2", "3"};
//            string cellValue = nameElement[idx];
//            Position charPos(i, j);
//
////            if (i == 12 && j == 0){
////                cout << "Hello";
////            }
//
//
//            for (int k = 0; k < arr_mv_objs->size(); k++)
//            {
//                if (arr_mv_objs->get(k)->getCurrentPosition().isEqual(charPos))
//                {
//                    if (cellValue == "     " || cellValue == "-----" || cellValue == "IIIII")
//                        cellValue = "";
//                    idx = arr_mv_objs->get(k)->getObjectType();
//                    if (idx == 3)
//                    {
//                        MovingObject *temp = arr_mv_objs->get(k);
//                        while (cellValue[cellValue.length() - 1] == ' ')
//                        {
//                            cellValue = cellValue.substr(0, cellValue.length() - 1);
//                        }
//                        cellValue += robotName[dynamic_cast<Robot *>(temp)->getType()];
//                        continue;
//                    }
//                    cellValue += nameChar[idx];
//                }
//            }
//            if (!(cellValue == "     " || cellValue == "-----" || cellValue == "IIIII"))
//                cellValue = /*"(" +*/ cellValue /*+ ")"*/;
//            OUTPUT << setw(7) << cellValue << "|";
//        }
//        OUTPUT << endl;
//    }
//}
void StudyPinkProgram::run(bool verbose, ofstream &OUTPUT)
{
    if (!OUTPUT.is_open())
    {
        return;
    }
    bool isStop = arr_mv_objs->checkMeet(0) || sherlock->getHP() == 0 || watson->getHP() == 0;
    //OUTPUT << config->str() << endl;
    for (int istep = 0; istep < config->num_steps && !isStop; ++istep)
    {
        isStop = arr_mv_objs->checkMeet(0) || sherlock->getHP() == 0 || watson->getHP() == 0;
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


            if (istep == 13 && i == 2){
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
                    arr_mv_objs->add(robot);
                }
                else
                {
                    delete robot;
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
//            OUTPUT << "ROUND : " << istep << " - TURN : " << i << endl;
//
//            MovingObject *robot = nullptr;
//            if (arr_mv_objs->get(i)->getObjectType() == MovingObjectType::CRIMINAL)
//            {
//                robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
//            }
//            arr_mv_objs->get(i)->move();
//            if (robot != nullptr)
//            {
//                if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
//                {
//                    arr_mv_objs->add(robot);
//                }
//                else
//                {
//                    delete robot;
//                }
//            }
//            //printMap(OUTPUT);
//            stop = arr_mv_objs->checkMeet(i);
//            OUTPUT << "---------------" << endl
//                   << "LOG : " << endl
//                   << arr_mv_objs->str() << endl
//                   << "Sherlock HP_" << sherlock->getHP() << " EXP_" << sherlock->getEXP() << endl
//                   << "Watson HP_" << watson->getHP() << " EXP_" << watson->getEXP() << endl
//                   << "SherlockBag : " << sherlock->getBag()->str() << endl
//                   << "WatsonBag : " << watson->getBag()->str() << endl;
        }

    }
//    OUTPUT << "---------------" << endl
//           << "RESULT : ";
//
//    if (watson->getHP() == 0)
//        OUTPUT << "Watson can not continue the journey";
//    else if (sherlock->getHP() == 0)
//        OUTPUT << "Sherlock can not continue the journey";
//    else if (stop)
//        OUTPUT << "The Criminal was caught";
//    else
//        OUTPUT << "The Criminal escaped";
}

// *CLASS: MagicBook
ItemType MagicBook::getType() const
{
    // TODO: get (1 dòng)
    return MAGIC_BOOK;
}
string MagicBook::str() const
{
    // TODO: trả về chuỗi biểu diễn (1 dòng)
    return "MagicBook";
}
bool MagicBook::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Sau khi đấm Robot, EXP
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
    // TODO: tăng EXP
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
    // TODO: get (1 dòng)
    return ENERGY_DRINK;
}
string EnergyDrink::str() const
{
    // TODO: trả về chuỗi biển diễn (1 dòng)
    return "EnergyDrink";
}
bool EnergyDrink::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Sau khi đấm Robot, HP
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
    // TODO: tăng HP
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
    // TODO: get (1 dòng)
    return FIRST_AID;
}
string FirstAid::str() const
{
    // TODO: trả về chuỗi biểu diễn (1 dòng)
    return "FirstAid";
}
bool FirstAid::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Sau khi đấm Robot, exp || HP
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
    // TODO: tăng HP
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
    // TODO: get (1 dòng)
    return  EXCEMPTION_CARD;
}
string ExcemptionCard::str() const
{
    // TODO: trả về chuỗi biểu diễn (1 dòng)
    return "ExcemptionCard";
}
bool ExcemptionCard::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Trước khi đấm Robot, Sherlock, hp lẻ
    if (obj->getObjectType() == SHERLOCK && robot != nullptr){
        if (dynamic_cast<Sherlock*>(obj)->getHP() % 2 != 0){
            return true;
        }
    }
    return false;
}
void ExcemptionCard::use(Character *obj, Robot *robot)
{
    // TODO: sinh viên hiện thực theo tư duy code của mình (hàm có thể rỗng)
    if (canUse(obj, robot)){

    }
}
// *CLASS: PassingCard
PassingCard::PassingCard(int i, int j)
{
    // TODO: constructor gán giá trị cho thuộc tính challenge (i,j là tọa độ)
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
ItemType PassingCard::getType() const
{
    // TODO: get (1 dòng)
    return PASSING_CARD;
}
string PassingCard::str() const
{
    // TODO: trả về chuỗi biểu diễn (1 dòng)
    return "PassingCard";
}
bool PassingCard::canUse(Character *obj, Robot *robot)
{
    // TODO: điều kiện sử dụng
    // *Trước khi đấm Robot, Watson, hp chẵn
    if (obj->getObjectType() == WATSON && robot != nullptr){
        if (dynamic_cast<Watson*>(obj)->getHP() % 2 == 0){
            return true;
        }
    }
    return false;
}
void PassingCard::use(Character *obj, Robot *robot)
{
    // TODO: tương tự ExcemptionCard khi thuộc tính challenge thích hợp, ngược lại sẽ trừ EXP
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
    // TODO: constructor gán giá trị cho CÁC THUỘC TÍNH
    this->size = 0;
    this->capacity = capacity;
    this->head = nullptr;
}
BaseBag::~BaseBag()
{
    // TODO: destructor xóa các Node (Lưu ý phải xóa cả item trong Node đó)

    for (int i = 0; i < size; i++){
        Node* temp = head;
        head = head -> next;
        delete temp->item;
    }
}
bool BaseBag::insert(BaseItem *item)
{
    // TODO: thêm Node chứa item vào đầu Linked List
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
    // TODO: Tìm và trả về item tương ứng với itemType
    // *Đảo vị trí trong BaseBag (2 cách phổ biến: swap Node hoặc con trỏ item của Node)
    // *Sau đó xóa Node (lưu ý cập nhật con trỏ head)

    Node* temp = head;

    for (int i = 0; i < size; i++){
        if (temp->item->getType() == itemType){
            break;
        }
        temp = temp->next;
    }

    if (temp != nullptr){
        swap(temp->item, head->item);
        temp = head;
        head = head -> next;
        size -= 1;
        return temp->item;
    }

    //delete temp;

    return nullptr;
}
string BaseBag::str() const
{
    // TODO: trả về chuỗi biểu diễn
    // *"Bag[count=<thuộc tính size>;<danh sách tên các item cách nhau bởi dấu ,>]"
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
        // TODO: constructor class cha
        13
)
{
    // TODO: constructor class con
    sherlock = character;
}
BaseItem *SherlockBag::get()
{
    // TODO: tìm và trả về item SHERLOCK CÓ THỂ SỬ DỤNG gấn đầu túi nhất, đảo lên đầu và xóa khỏi Linked List (cập nhật head)
    Node* temp = head;
    for (int i = 0; i < size; i++){
        if (temp->item->canUse(this->sherlock, nullptr)){
            break;
        }
        temp = temp->next;
    }

    if (temp != nullptr){
        swap(temp->item, head->item);

        temp = head;
        head = head -> next;
        size -= 1;
        return temp->item;
    }

    //delete temp;
    return nullptr;

}
// *CLASS: WatsonBag
WatsonBag::WatsonBag(Watson *character)
        : BaseBag(
        // TODO: constructor class cha
        15
)
{
    // TODO: constructor class con
    watson = character;
}
BaseItem *WatsonBag::get()
{
    // TODO: tìm và trả về item WATSON CÓ THỂ SỬ DỤNG gấn đầu túi nhất, đảo lên đầu và xóa khỏi Linked List (cập nhật head)
    Node* temp = head;
    for (int i = 0; i < size; i++){
        if (temp->item->canUse(this->watson, nullptr)){
            break;
        }
        temp = temp->next;
    }

    if (temp != nullptr){
        swap(temp->item, head->item);

        temp = head;
        head = head -> next;
        size -= 1;
        return temp->item;
    }



    //delete temp;
    return nullptr;

}



// *------------------------------------------------------------------
// *
// *------------------------------------------------------------------
// !-----------------------------------
// ! Lưu ý về việc xét thông số khi tăng giảm
// ! Các thay đổi thông số là dựa trên thông số hiện tại
// ! Các thông số không phải số nguyên THỰC HIỆN LÀM TRÒN LÊN -> NHÂN VẬT CHỈ HI SINH KHI INIT hp = 0
// !-----------------------------------
// *CLASS: ArrayMovingObject
bool ArrayMovingObject::checkMeet(int index)
{
    // TODO: Xét va chạm của nhân vật (theo index) với các nhân vật khác trong array
    // TODO: Thực hiện xử lý các sự kiện xảy ra (thử thách, thêm item, bắt Criminal)

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
                        return false;
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
// ! Lưu ý: ExcemptionCard được dùng để BỎ QUA nếu THỬ THÁCH THẤT BẠI -> xem như không thực hiện thử thách -> không gọi get lần 2
// ! Thực hiện get từ bag sau khi insert item
bool Sherlock::meet(RobotS *robotS)
{
    // TODO: Xử lý khi gặp robot S

    if (this->exp > 400){
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotS)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotS);
            }
            else vatphamsudung = nullptr;
        }
        BaseItem * newItem;
        if (robotS->getItem()->getType() == MAGIC_BOOK){
            newItem = new MagicBook();
        }
        else if (robotS->getItem()->getType() == ENERGY_DRINK){
            newItem = new EnergyDrink();
        }
        else if (robotS->getItem()->getType() == FIRST_AID){
            newItem = new FirstAid();
        }
        else if (robotS->getItem()->getType() == EXCEMPTION_CARD){
            newItem = new ExcemptionCard();
        }
        else{
            newItem = new PassingCard(robotS->getPoshead().getRow(), robotS->getPoshead().getCol());
        }
        this->bag->insert(newItem);



        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            delete vatphamsudung;
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
            }
            else dungchua = false;
        }

        if (dungchua == false) exp = ceil(exp * 0.9);
        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr){
            if (vatphamsudung != nullptr) {
                vatphamsudung->use(this, NULL);
                delete vatphamsudung;
            }
            return false;
        }
    }
    return true;
}
bool Sherlock::meet(RobotW *robotW)
{
    // TODO: Xử lý khi gặp robot W
    BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
    if (vatphamsudung != nullptr){
        if(vatphamsudung->canUse(this, robotW)){
            vatphamsudung = this->bag->get(EXCEMPTION_CARD);
            vatphamsudung->use(this, robotW);
        }
        else vatphamsudung = nullptr;
    }

    BaseItem * newItem;
    if (robotW->getItem()->getType() == MAGIC_BOOK){
        newItem = new MagicBook();
    }
    else if (robotW->getItem()->getType() == ENERGY_DRINK){
        newItem = new EnergyDrink();
    }
    else if (robotW->getItem()->getType() == FIRST_AID){
        newItem = new FirstAid();
    }
    else if (robotW->getItem()->getType() == EXCEMPTION_CARD){
        newItem = new ExcemptionCard();
    }
    else{
        newItem = new PassingCard(robotW->getPoshead().getRow(), robotW->getPoshead().getCol());
    }

    this->bag->insert(newItem);

    vatphamsudung = this->bag->get();
    if (vatphamsudung != nullptr) {
        vatphamsudung->use(this, NULL);
        delete vatphamsudung;
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
            }
            else vatphamsudung = nullptr;
        }

        BaseItem * newItem;
        if (robotSW->getItem()->getType() == MAGIC_BOOK){
            newItem = new MagicBook();
        }
        else if (robotSW->getItem()->getType() == ENERGY_DRINK){
            newItem = new EnergyDrink();
        }
        else if (robotSW->getItem()->getType() == FIRST_AID){
            newItem = new FirstAid();
        }
        else if (robotSW->getItem()->getType() == EXCEMPTION_CARD){
            newItem = new ExcemptionCard();
        }
        else{
            newItem = new PassingCard(robotSW->getPoshead().getRow(), robotSW->getPoshead().getCol());
        }

        this->bag->insert(newItem);

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            delete vatphamsudung;
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
                delete vatphamsudung;
            }
            return false;
        }
    }
    return true;
}
bool Sherlock::meet(RobotC *robotC)
{
    // TODO: Xử lý khi gặp robot C

    if (this->exp > 500){
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotC)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotC);
            }
            else vatphamsudung = nullptr;
        }

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            delete vatphamsudung;
        }

        return true;
    }
    else{
        BaseItem* vatphamsudung = this->bag->find(EXCEMPTION_CARD);
        if (vatphamsudung != nullptr){
            if(vatphamsudung->canUse(this, robotC)){
                vatphamsudung = this->bag->get(EXCEMPTION_CARD);
                vatphamsudung->use(this, robotC);
            }
            else vatphamsudung = nullptr;
        }

        BaseItem * newItem;
        if (robotC->getItem()->getType() == MAGIC_BOOK){
            newItem = new MagicBook();
        }
        else if (robotC->getItem()->getType() == ENERGY_DRINK){
            newItem = new EnergyDrink();
        }
        else if (robotC->getItem()->getType() == FIRST_AID){
            newItem = new FirstAid();
        }
        else if (robotC->getItem()->getType() == EXCEMPTION_CARD){
            newItem = new ExcemptionCard();
        }
        else{
            newItem = new PassingCard(robotC->getPoshead().getRow(), robotC->getPoshead().getCol());
        }

        this->bag->insert(newItem);

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            delete vatphamsudung;
        }

        return false;
    }
    return true;
}
bool Sherlock::meet(Watson *watson)
{
    // TODO: Xử lý trao đổi thẻ ExcemptionCard
    // TODO: KHI CẢ 2 ĐỀU CÓ THỂ TRAO ĐỔI && ĐỔI TOÀN BỘ NẾU NHIỀU HƠN 1 (KỂ CẢ KHI ĐỐI PHƯƠNG)

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
// ! Lưu ý: PassingCard được dùng khi GẶP ROBOT để bỏ qua thử thách nếu đúng loại thẻ
// ! Thực hiện get từ bag sau khi insert item
bool Watson::meet(RobotS *robotS)
{
    // TODO: Xử lý trao đổi khi gặp robot S
    //BaseItem* vatphamsudung = this->bag->get(PASSING_CARD);
    BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
    if (vatphamsudung != nullptr) {
        if (vatphamsudung->canUse(this, robotS)) {
            vatphamsudung = this->bag->get(PASSING_CARD);
            vatphamsudung->use(this, robotS);
        } else {
            vatphamsudung = nullptr;
        }
    }

    vatphamsudung = this->bag->get();
    if (vatphamsudung != nullptr) {
        vatphamsudung->use(this, NULL);
        delete vatphamsudung;
    }

    return true;
}
bool Watson::meet(RobotW *robotW)
{
    // TODO: Xử lý trao đổi khi gặp robot W
    bool dungchua = false;
    BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
    if (vatphamsudung != nullptr){
        if (vatphamsudung->canUse(this, robotW)){
            vatphamsudung = this->bag->get(PASSING_CARD);
            vatphamsudung->use(this, robotW);
            dungchua = true;
        } else dungchua = false;
    }

    if (this->hp > 350){
        BaseItem * newItem;
        if (robotW->getItem()->getType() == MAGIC_BOOK){
            newItem = new MagicBook();
        }
        else if (robotW->getItem()->getType() == ENERGY_DRINK){
            newItem = new EnergyDrink();
        }
        else if (robotW->getItem()->getType() == FIRST_AID){
            newItem = new FirstAid();
        }
        else if (robotW->getItem()->getType() == EXCEMPTION_CARD){
            newItem = new ExcemptionCard();
        }
        else{
            newItem = new PassingCard(robotW->getPoshead().getRow(), robotW->getPoshead().getCol());
        }

        this->bag->insert(newItem);

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            delete vatphamsudung;
        }
        return true;
    }
    else{
        if (dungchua == false) hp = ceil(hp * 0.95);
        vatphamsudung = this->bag->get();

        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            delete vatphamsudung;
        }
        return false;
    }
    return true;
}
bool Watson::meet(RobotSW *robotSW)
{
    // TODO: Xử lý trao đổi khi gặp robot SW
    bool dungchua = false;
    BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
    if (vatphamsudung != nullptr){
        if (vatphamsudung->canUse(this, robotSW)){
            vatphamsudung = this->bag->get(PASSING_CARD);
            vatphamsudung->use(this, robotSW);
            dungchua = true;
        } else dungchua = false;
    }
    if (this->exp > 600 && this->hp > 165){
        BaseItem * newItem;
        if (robotSW->getItem()->getType() == MAGIC_BOOK){
            newItem = new MagicBook();
        }
        else if (robotSW->getItem()->getType() == ENERGY_DRINK){
            newItem = new EnergyDrink();
        }
        else if (robotSW->getItem()->getType() == FIRST_AID){
            newItem = new FirstAid();
        }
        else if (robotSW->getItem()->getType() == EXCEMPTION_CARD){
            newItem = new ExcemptionCard();
        }
        else{
            newItem = new PassingCard(robotSW->getPoshead().getRow(), robotSW->getPoshead().getCol());
        }

        this->bag->insert(newItem);

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            delete vatphamsudung;
        }
        return true;
    }
    else{
        if (dungchua == false){
            hp = ceil(hp * 0.85);
            exp = ceil(exp * 0.85);
        }

        vatphamsudung = this->bag->get();
        if (vatphamsudung != nullptr) {
            vatphamsudung->use(this, NULL);
            delete vatphamsudung;
        }
        return false;
    }
    return true;
}
bool Watson::meet(RobotC *robotC)
{
    // TODO: Xử lý trao đổi khi gặp robot C
    bool dungchua = false;
    BaseItem* vatphamsudung = this->bag->find(PASSING_CARD);
    if (vatphamsudung != nullptr){
        if (vatphamsudung->canUse(this, robotC)){
            vatphamsudung = this->bag->get(PASSING_CARD);
            vatphamsudung->use(this, robotC);
            dungchua = true;
        } else dungchua = false;
    }
    BaseItem * newItem;
    if (robotC->getItem()->getType() == MAGIC_BOOK){
        newItem = new MagicBook();
    }
    else if (robotC->getItem()->getType() == ENERGY_DRINK){
        newItem = new EnergyDrink();
    }
    else if (robotC->getItem()->getType() == FIRST_AID){
        newItem = new FirstAid();
    }
    else if (robotC->getItem()->getType() == EXCEMPTION_CARD){
        newItem = new ExcemptionCard();
    }
    else{
        newItem = new PassingCard(robotC->getPoshead().getRow(), robotC->getPoshead().getCol());
    }

    this->bag->insert(newItem);

    vatphamsudung = this->bag->get();
    if (vatphamsudung != nullptr) {
        vatphamsudung->use(this, NULL);
        delete vatphamsudung;
    }
    return true;
}
bool Watson::meet(Sherlock *sherlock)
{
    // TODO: Xử lý trao đổi khi gặp Sherlock

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
    // TODO: get bag
    return this->bag;
}
BaseBag *Watson::getBag() const
{
    // TODO: get bag
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
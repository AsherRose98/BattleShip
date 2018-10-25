#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

/******
Set Globals
******/

int const GridSize = 10;

char const EMPTY = '-';
char const HIT = 'X';
char const SUNK = '*';
char const MISS = '\\';

int NShotsFired = 0;
int NShotsHit = 0;
int NShotsMiss = 0;

enum BoatCheck {hit, miss, sunk};

char Grid[GridSize][GridSize];
bool RunGame = true;
bool RestartGame = false;
bool SolutionShown = false;
bool GameOver = false;

/*****
Create Classes
******/
class Boat{
    public:
        int n_squares,x,y = 0;
        bool vertical;
        bool sunk = false;
        char code;
        vector<vector<int>> coodinates;
        bool set_points(vector<Boat> &listOfBoats, int try_x, int try_y){
            set_vertical();
            //cout<<"debug: Start Boat Creation - "<<code<<" | "<<try_x<<" "<<try_y<<" "<<vertical<<endl;
        //Get Each Boat
            for(int boatCount=0;boatCount<listOfBoats.size();boatCount++){
            //cout<<"debug: BoatSize - "<<boatCount<<endl;
        //Get Each Set of points
                for(int cooCount=0;cooCount<=listOfBoats[boatCount].coodinates.size();cooCount++){
                //cout<<"debug: BoatCount - "<<cooCount<<endl;
        //Get Each Point
                    vector<vector<int>> cooList = listOfBoats[boatCount].coodinates;
                    coodinates.push_back({try_x,try_y});
                    for(int pointCount=0;pointCount<cooList.size();pointCount++){
                        //cout<<"debug: "<<pointCount<<endl;
                        int boat_x = cooList[pointCount][0];
                        int boat_y = cooList[pointCount][1];
                        //Parse through my new points
                        if(vertical){
                            for(int i=0; i<n_squares;i++){
                                int point_y = try_y-i;
                                //Return if matches point
                                if(point_y==boat_y&&try_x==boat_x){
                                    coodinates.clear();
                                    return false;
                                }
                            }
                        }else{
                            for(int i=0; i<n_squares;i++){
                                int point_x = try_x-i;
                                //Return if matches point
                                if(point_x==boat_x&&try_y==boat_y){
                                    coodinates.clear();
                                    //cout<<"Debug: Ignore Above"<<endl;
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
            for(int i=0; i<n_squares; i++){
                if(vertical){
                    int point_y = try_y-i;
                    coodinates.push_back({try_x,point_y});
                }else{
                    int point_x = try_x-i;
                    coodinates.push_back({point_x,try_y});
                }
                coodinates.resize(i+1);
            }
            /*cout<<"Debug: n_squares: "<<n_squares<<endl;
            cout<<"Debug: ___COODRINATES LIST______"<<endl;
            for(int i=0;i<coodinates.size();i++){
                 cout<<"Debug: "<<coodinates[i][0]<<" "<<coodinates[i][1]<<endl;
            }
            cout<<"Debug: coodinates_n: "<<coodinates.size()<<endl;//*/
            return true;
        }
        bool check_sunk(char checkGrid[GridSize][GridSize]){
            for(int i=0;i<coodinates.size();i++){
                int check_x = coodinates[i][0];
                int check_y = coodinates[i][1];
                //cout<<"DEBUG: ("<<check_x<<","<<check_y<<") = "<<checkGrid[check_x][check_y]<<endl;
                if(checkGrid[check_x][check_y]==EMPTY){
                    //cout<<"DEBUG: Returning false: "<<checkGrid[check_x][check_y]<<endl;
                    return false;
                }
            }
            return true;
        }
    protected:
        void set_n_squares(int n){
            n_squares = n;
        }
        void set_code(char c){
            code = c;
        }
        
        void set_vertical(){
            vertical =(rand()%2==0)?false: true;
        }
        
        void set_coord(int n1, int n2, bool ver){
            x = n1;
            y = n2;
            vertical = ver;
        }
};


class BoatSub : public Boat{
    public:
        BoatSub();
};

    BoatSub::BoatSub(void){
        set_code('S');
        set_n_squares(3);
    }
    
class BoatAircraft : public Boat{
    public:
        BoatAircraft();
};
    BoatAircraft::BoatAircraft(void){
        set_code('A');
        set_n_squares(5);
    }

class BoatBattleship : public Boat{
    public:
        BoatBattleship();
};
    BoatBattleship::BoatBattleship(void){
        set_code('B');
        set_n_squares(4);
    }
    
class BoatCruiser : public Boat{
    public:
        BoatCruiser();
};
    BoatCruiser::BoatCruiser(void){
        set_code('C');
        set_n_squares(3);
    }

class BoatPatrol : public Boat{
    public:
        BoatPatrol();
};
    BoatPatrol::BoatPatrol(void){
        set_code('P');
        set_n_squares(2);
    }


vector<Boat> BoatList;
    
/*******
 functions
 ******/
 
void initBoats(int n_aircraft, int n_battleship, int n_cruiser, int n_submarine, int n_patrol){
    BoatList.clear();
    //Create Aircrafts
    for(int i=0;i<n_aircraft;i++){
        BoatAircraft boat;
        while(!boat.set_points(BoatList,boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1),boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1)));
        BoatList.push_back(boat);
    }
    //Create Battleships
    for(int i=0;i<n_battleship;i++){
        BoatBattleship boat;
        while(!boat.set_points(BoatList,boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1),boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1)));
        BoatList.push_back(boat);
    }
    //Create Crusier
    for(int i=0;i<n_cruiser;i++){
        BoatCruiser boat;
        while(!boat.set_points(BoatList,boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1),boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1)));
        BoatList.push_back(boat);
    }
    //Create Sub
    for(int i=0;i<n_submarine;i++){
        BoatSub boat;
        while(!boat.set_points(BoatList,boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1),boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1)));
        BoatList.push_back(boat);
    }
    //Create Patrol
    for(int i=0;i<n_patrol;i++){
        BoatPatrol boat;
        while(!boat.set_points(BoatList,boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1),boat.n_squares-1 + rand() % (GridSize - boat.n_squares-1)));
        BoatList.push_back(boat);
    }
}


void initGrid(){
    for(int i=0;i<GridSize;i++){
        for(int j=0;j<GridSize;j++){
            Grid[i][j]=EMPTY;
        }
    }
}

string getSecondWord(const string &str){
    return str.substr(str.find(' ')+1,
                      str.length()
                      );
}

string getFirstWord(const string &str){
    return str.substr(0, str.find(' '));
}

BoatCheck shoot(int &input_x, int &input_y ){
    NShotsFired++;
    //cout<<"Debug: Shooting - Boats:"<<BoatList.size()<<endl;
    //Get Each Boat
    for(int boatCount=0;boatCount<BoatList.size();boatCount++){
        //cout<<"Debug: Boat"<<endl;
    //Get Each Set of points
        for(int cooCount=0;cooCount<BoatList[boatCount].coodinates.size();cooCount++){
        //cout<<"Debug: coordinate"<<endl;
    //Get Each Point
            vector<vector<int>> cooList = BoatList[boatCount].coodinates;
            for(int pointCount=0;pointCount<cooList.size();pointCount++){
                int boat_x = cooList[pointCount][0];
                int boat_y = cooList[pointCount][1];
                //cout<<"Boat X: "<<boat_x<<"|| Boat Y: "<<boat_y<<endl;
                if(boat_x==input_x && boat_y == input_y){
                    NShotsHit++;
                    Grid[input_x][input_y]='0';
                    if(BoatList[boatCount].check_sunk(Grid)){
                        vector<vector<int>> coord = BoatList[boatCount].coodinates;
                        for(int pointsN=0; pointsN<coord.size(); pointsN++){
                            Grid[coord[pointsN][0]][coord[pointsN][1]]= SUNK;
                        }
                        return sunk;
                    }
                    return hit;
                }
            }
        }
    }
    NShotsMiss++;
    return miss;
}

void draw_grid(){
    cout<<" ";
        for(int i=0; i<GridSize; i++){
            cout<<" "<<char(i+65);
        }
        cout<<endl;
        for(int i=0;i<GridSize;i++){
            cout<<i;
            for(int j=0;j<GridSize;j++){
                cout<<" "<<Grid[i][j];
            }
            cout<<endl;
        }
}

void getCommand(){
    string command;
    getline(cin,command);
    cout<<endl;
    if(command=="help"){
        cout<<"shoot <coordinate>: Simulate a shot against the specified square"<<endl<<
        "show grid: Show the actual grid of shots"<<endl<<
        "show solution: Show the solution"<<endl<<
        "show statistics: Show some statistics of the actual game"<<endl<<
        "start new: Force the end of the actual game and start a new game"<<endl<<
        "help: Display this help message"<<endl<<
        "quit: End the actual game and exit the program;"<<endl;
        
    }else if(getFirstWord(command)=="shoot"){
        if(!SolutionShown){
            string input = getSecondWord(command);
            int input_y = input[0]-65;
            int input_x = input[1]-49+1;
            if( Grid[input_x][input_y]==EMPTY){
                BoatCheck success = shoot(input_x, input_y);
                switch(success){
                    case(hit):
                        Grid[input_x][input_y] = HIT;
                        cout<<"HIT!";
                    break;
                    case(miss):
                        Grid[input_x][input_y] = MISS;
                        cout<<"Miss.";
                    break;
                    case(sunk):
                        Grid[input_x][input_y] = SUNK;
                        cout<<"Hit AND Sunk!!";
                    break;
                }
            }else{
                cout<<"You've already hit this area..."<<endl;
            }
        }else{
            cout<<"You cannot shoot after seeing the solution."<<endl<<
                  "You must restart the game or quit"<<endl;
        }
        
    }else if(command=="show grid"){
        draw_grid();
        
    }else if(command=="show solution"){
        SolutionShown = true;
        //Get Each Boat
        for(int boatCount=0;boatCount<BoatList.size();boatCount++){
        //Get Each Set of points
            for(int cooCount=0;cooCount<BoatList[boatCount].coodinates.size();cooCount++){
        //Get Each Point
                vector<vector<int>> cooList = BoatList[boatCount].coodinates;
                for(int pointCount=0;pointCount<cooList.size();pointCount++){
                    //cout<<"debug: "<<BoatList[boatCount].code<<" | "<<cooList[pointCount][0]<<" "<<cooList[pointCount][1]<<endl;
                    Grid[cooList[pointCount][0]][cooList[pointCount][1]] = BoatList[boatCount].code;
                }
            }
        }
        draw_grid();
        
    }else if(command=="show statistics"){
        cout<<"Shots Fired: "<<NShotsFired<<endl<<
              "Shots Hit: "<<NShotsHit<<endl<<
              "Shots Missed: "<<NShotsMiss<<endl;
        
    }else if(command=="start new"){
        RestartGame = true;
        
    }else if(command=="quit"){
        cout<<"Goodbye!!"<<endl;
        RestartGame = true;
        RunGame = false;
        
    }else{
        cout<<"UNKNOWN COMMAND";
    }
    cout<<endl;
}

void reset_stats(){
    NShotsFired = 0;
    NShotsHit = 0;
    NShotsMiss = 0;
    SolutionShown = false;
}

int main()
{
   srand(time(NULL));
   while(RunGame){
       RestartGame = false;
       
       initGrid();
       reset_stats();
       initBoats(1,1,2,2,3);
       
       cout<<"Welcome to Battleship\nPlease, enter your commands\n";
       
       while(!RestartGame){
           getCommand();
       }
   }
    return 0;
}
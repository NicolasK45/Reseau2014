#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class cases{

private:
	bool north;
	bool south;
	bool east;
	bool west;
	int occ;
public:
	cases(){
		occ=-1;
		if (rand()%2==0){
			north=true;
		}
		else {north=false;}

		if (rand()%2==0){
			south=true;
		}
		else {south=false;}

		if (rand()%2==0){
			east=true;
		}
		else {east=false;}

		if (rand()%2==0){
			west=true;
		}
		else {west=false;}
	}

	void destroy(string direction){
		if (direction=="north"){north=true;}
		else if (direction=="south"){south=true;}
		else if (direction=="east"){east=true;}
		else if (direction=="west"){west=true;}
	}

	bool open(string direction){
		if (direction=="north"){return north;}
		else if (direction=="south"){return south;}
		else if (direction=="east"){return east;}
		else if (direction=="west"){return west;}
	}
	int occupant(){
		return occ;
	}

};


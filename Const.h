//SETTING CONST
const byte numberOfCh = 5;
//--------------------buttons------------------------
const int canC[] = { 160, 194, 317, 225 };       //standard cancel
const int prOK[] = { 2, 194, 158, 225 };         //standard ok

//-----------------main screen----------------------
const int alaR[] = { 7, 195, 173, 219 };      //confirm alarm

//------------------menu----------------------------
const int tanD[] = { 2, 21, 158, 59 };        //time and date
const int temC[] = { 2, 61, 158, 99 };        //temp. settings
const int atoS[] = { 2, 101, 158, 139 };      //ATO settings
const int scrS[] = { 2, 141, 158, 179 };      //screen settings
const int ledW[] = { 160, 21, 317, 59 };      //white LEDs values settings
const int tesT[] = { 160, 61, 317, 99 };      //test LED
const int colM[] = { 160, 101, 317, 139 };    //Color mixer

//------------------Time and Date------------
const int houP[] = { 130, 22 };               //hour up
const int houM[] = { 130, 71 };               //hour down
const int minP[] = { 190, 22 };               //minute up
const int minM[] = { 190, 71 };               //minute down

const int dayU[] = { 120, 111 };              //day up
const int dayD[] = { 120, 160 };              //day down
const int monU[] = { 179, 111 };              //month up
const int monD[] = { 179, 160 };              //month down
const int yeaU[] = { 250, 111 };              //year up
const int yeaD[] = { 250, 160 };              //year down

//------------------Temperature Settings-----------------
const int temP[] = { 138, 28 };                //temp. plus
const int temM[] = { 138, 50 };                //temp. minus
const int offP[] = { 277, 28 };                //offset plus
const int offM[] = { 277, 50 };                //offset minus
const int hemP[] = { 118, 87 };             //Heatsink fans min temperature plus
const int hemM[] = { 118, 109 };           //heatsink fans min temperature minus
const int hetP[] = { 257, 87 };             //Heatsink fans max temperature plus
const int hetM[] = { 257, 109 };           //heatsink fans max temperature minus
const int hecP[] = { 162, 146 };               //LEDs cut off temperature plus
const int hecM[] = { 162, 168 };               //LEDs cut off temperature minus

//-----------------------------------ATO settings------------------
const int atoO[] = { 150, 30 };               //ATO on/off switch
const int atoP[] = { 176, 93 };                //ATO time plus
const int atoM[] = { 176, 115 };               //ATO time minus

//----------------------------------LEDs menu-------------------
const int ch1L[] = { 2, 21, 158, 59 };        //channel 1 light output
const int ch3L[] = { 2, 61, 158, 99 };        //channel 3 light output
const int ch5L[] = { 2, 101, 158, 139 };      //channel 5 light output
const int ch2L[] = { 160, 21, 317, 59 };      //channel 2 light output
const int ch4L[] = { 160, 61, 317, 99 };      //channel 4 light output
const int mooL[] = { 160, 141, 317, 179 };    //moonlight settings

//-----------------------------------test LEDs------------------
const int stsT[] = { 76, 158, 243, 191 };     //start/stop
const int tenM[] = { 2, 158, 74, 191 };       //-10s
const int tenP[] = { 245, 158, 317, 191 };    //+10s

//----------------------------------Moonlight Settings---------------
const int morO[] = { 170, 25 };               //moonrise/set real time on/off
const int morP[] = { 115, 74 };               //moonrise time plus
const int morM[] = { 115, 96 };               //moonrise time minus
const int mosP[] = { 268, 74 };               //moonset time plus
const int mosM[] = { 268, 96 };               //moonset time minus
const int nmlP[] = { 115, 143 };              //newmoon light value plus
const int nmlM[] = { 115, 165 };              //newmoon light value minus
const int fmlP[] = { 268, 143 };              //fullmoon light value plus
const int fmlM[] = { 268, 165 };              //fullmoon light value minus

//-------------------------------General settings------------------------
const int gseB[] = { 64, 39 };                //brightness bar
const int gseS[] = { 160, 60, 318, 90 };      //Save
const int gseL[] = { 160, 250, 318, 180 };    //Load

char *Day[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
		"Friday", "Saturday" };
char *Mon[] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
		"Sep", "Oct", "Nov", "Dec" };

int stringCenter(char *myString, boolean font = false) //returns half lenght of string in pixels
		{
	int chLen;

	if (font)                                   //large font
		chLen = (strlen(myString) * 8) - 1;
	else
		//small font
		chLen = (strlen(myString) * 4) - 1;
	return chLen;
}

//----------------------------------Garden Program Settings---------------
const int prgOnOff[] = { 250, 20, 40, 20 }; //  ON/OFF button parameter (x,y,Width,height)
const int prgSAVE[] = { 10, 196, 60, 20 };         //standard ok
const int prgCANC[] = { 230, 196, 60, 20 };         //standard ok

//-----------------SETTING---------------------------

boolean StationOnOff[] = { false, false, false, false, false, false }; //1=ON  0=OFF
unsigned int humThr[] = { 50, 50, 50, 50, 50, 50 }; //Threshold percent of Houmidity for S1...S6

//------------------BUTTONS--------------------------

//
boolean returnHomeGarden;

// button ZERO "G": MainScreen, button to set HomeGarden
int but_1G;
const int b1G[] = { 180, 30, 100, 20 }; //  ON/OFF button parameter (x,y,Width,height)

// buttons homeGardem
int but_1HG; //go to GardenProgram
int but_2HG; //go to GardenSetUp
int but_3HG; //Cancel
const int b1HG[] = { 180, 30, 100, 20 };
const int b2HG[] = { 180, 80, 100, 20 };
const int b3HG[] = { 180, 130, 100, 20 };

//-------------------------------------------
//----------   SETUP-GARDEN   ---------------
//-------------------------------------------

int but_0S;  //Station1 ON/OFF
int but_1S;  //Station2 ON/OFF
int but_2S;  //Station3 ON/OFF
int but_3S;  //Station4 ON/OFF
int but_4S; //Station5 ON/OFF
int but_5S; //Station6 ON/OFF
int but_6S;  //Up Humidity Threshold 1
int but_7S;  //Down Humidity Threshold 1
int but_8S;  //Up Humidity Threshold 2
int but_9S;  //Down Humidity Threshold 2
int but_10S;  //Up Humidity Threshold 3
int but_11S;  //Down Humidity Threshold 3
int but_12S;  //Up Humidity Threshold 4
int but_13S;  //Down Humidity Threshold 4
int but_14S;  //Up Humidity Threshold 5
int but_15S;  //Down Humidity Threshold 5
int but_16S;  //Up Humidity Threshold 6
int but_17S;  //Down Humidity Threshold 6

int but_18S;  //Save
int but_19S;  //Cancel
int posRifX1 = 10;
int posRifY1 = 25;

int posRifX2 = 100;
int posRifY2 = 25;

const int b0S[] = { posRifX1 + 20, posRifY1 + 25, 50, 20 };   //Button ON/OFF
const int b6S[] = { 140, 50, 20, 20 };   //Button +
const int b7S[] = { 170, 50, 20, 20 };   //Button -
const int b18S[] = { 230, 160, 80, 20 };    //Button "SAVE" POSITION
const int b19S[] = { 230, 200, 80, 20 };    //Button "CANCEL" POSITION

//Humidity percent
double humidity;


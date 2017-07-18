// ====================================
// TheCave.cpp
// An adventure game about exploring 
// and escaping a subterranean cave
// Author: Camille Hebert
// This program is entirely my own work
// ====================================

#include <iostream>
#include <string>
using namespace std;

// -------------------
// Function Prototypes
// -------------------
// The format for these prototypes is < purpose_rowNumber_columnNumber >
void DescribeRoom_0_0();
void DescribeRoom_0_1();
void DescribeRoom_0_2();
void DescribeRoom_0_3();
void DescribeRoom_1_0();
void DescribeRoom_1_1();
void DescribeRoom_1_2();
void DescribeRoom_1_3();
void DescribeRoom_2_0();
void DescribeRoom_2_1();
void DescribeRoom_2_2();
void DescribeRoom_2_3();
void DescribeRoom_3_0();
void DescribeRoom_3_1();
void DescribeRoom_3_2();
void DescribeRoom_3_3();
void DescribeRoom_4_0();
void DescribeRoom_4_1();
void DescribeRoom_4_2();
void DescribeRoom_4_3();

/*
void DescribeObject_Gloves();
void DescribeObject_Staff();
void DescribeObject_Rope();
void DescribeObject_Vial();
void DescribeObject_Bag();
void DescribeObject_Hat();
void DescribeObject_Coat();
void DescribeObject_Boots();
void DescribeObject_Ring();
void DescribeObject_Fish();
void DescribeObject_Geode();
void DescribeObject_Gold();
void DescribeObject_Diamond();
void DescribeObject_Skull();
void DescribeObject_Parchment();
*/

// Room Description Function Prototype
void DescribeRoomContents(int roomDescription, int row, int column);

// Object Description Function Prototype
void DescribeObject(string commandObject);

// Build Room Function Prototype
void BuildRoom(unsigned int rooms[][4]);

// Take Item Function Prototype
int TakeItem(unsigned int rooms[][4], int row, int column, string object);

// Define Doors
#define DOOR_NORTH	0x00000001
#define DOOR_EAST	0x00000002
#define DOOR_SOUTH	0x00000004
#define DOOR_WEST	0x00000008

// Define Treasure Objects
#define GLOVES		0x00000010
#define STAFF		0x00000020
#define ROPE		0x00000040
#define VIAL		0x00000080

// Define Other Objects
#define BAG			0x00000100
#define HAT			0x00000200
#define COAT		0x00000400
#define BOOTS		0x00000800
#define	RING		0x00001000
#define FISH		0x00002000
#define GEODE		0x00004000
#define GOLD		0x00008000
#define DIAMOND		0x00010000
#define SKULL		0x00020000
#define PARCHMENT	0x00040000

// Define Creatures
#define	SPIDER		0x00080000
#define BAT			0x00100000
#define SNAKE		0x00200000
#define CREATURE	0x00400000
#define BEAR		0x00800000
#define FROG		0x01000000
#define RAT			0x02000000

// Define Danger Levels
#define HARMLESS	0x04000000
#define CAUTION		0x08000000
#define DANGEROUS	0x10000000
#define DEADLY		0x20000000

// =====================================================================================================

// -------------
// Main Function
// -------------

int main()
{
	// ---------------------------------------
	// Declare and Initialize Global Variables
	// ---------------------------------------
	
	
	string commandVerb;
	string commandObject;
	int iRow;
	int iColumn;
	int iNumRows;
	int iNumColumns;
	int verbIndex;
	int objectIndex;
	bool endGame;
	unsigned int caveGrid[5][4];
	int iPlayer = 0;
	int endRow = 4;
	int endColumn = 3;

	int roomTest = 0xFFFFFFFF;
	
	// Player starts in bottom right corner of game grid
	// iRow and iColumn represent the player's current position
	iRow = 4;
	iColumn = 3;
	iNumRows = 4;
	iNumColumns = 3;

	// Set game grid to 0
	for (int row=0; row<5; row++)
		for (int column=0; column<4; column++)
			caveGrid[row][column]=0;

	// Build rooms
	BuildRoom(caveGrid);

	// --------------------
	// Introduction to Game
	// --------------------
	
	cout << "                                        _  ___" << endl;
	cout << "                                    /(oo__)_ _)oo \\" << endl;
	cout << "                                  ( (_(__)__)  )_) )_" << endl;
	cout << "             WELCOME TO          / (  )08888888(  ) _)" << endl;
	cout << "              THE CAVE          ( ( _))08888888(__)o _)" << endl;
	cout << "                               (_ (  )0888888888(o  ) _)" << endl;
	cout << "                             / ( (  o)08888888888(  o)__\\" << endl;
	cout << endl;
	cout << "Well, you've gotten yourself into quite a pickle! As a famous treasure hunter," << endl;
	cout << "you were off on one of your exploration adventures, exploring a rocky cliff," << endl;
	cout << "when you found a cave opening. Venturing slowly inside, you took one step too" << endl;
	cout << "far and found yourself tumbling down, deep into the depths of a long-abandoned" << endl;
	cout << "cave system. On the way down, you hit your head and were knocked unconscious." << endl;
	cout << endl;
	cout << "When you come to, you find yourself in a small cavern, dimly lit from tiny" << endl;
	cout << "shafts of sunlight from far above. Below you is a carpet of moss, which must" << endl;
	cout << "have broken your fall. You groan as you get up to look around. Behind you is" << endl;
	cout << "an opening which appears man-made, and beyond it you can see the shaft down" << endl;
	cout << "which you fell. However, as you step towards it, you trigger a pressure plate" << endl;
	cout << "in the floor which causes a heavy stone door to close, sealing you inside the" << endl;
	cout << "cave. Perhaps you can use things you find within the cave to get out!" << endl;
	cout << endl;
	cout << "As you look around the room, the notion appears in your head that you can" << endl;
	cout << "move with the command GO, such as GO WEST. You also reason that when you find" << endl;
	cout << "something in the cave, the command TAKE may be useful. You should be aware of" << endl;
	cout << "your surroundings, since you may come across hostile creatures. You never know" << endl;
	cout << "what you will find in a cave like this!" << endl;
	cout << "----------------------------------------------------------------------------------" << endl << endl;

	DescribeRoomContents(caveGrid[4][3], 4, 3);

	// ---------------
	// Start game loop
	// ---------------
	endGame = false;
	while (!endGame)
	{
		// Scans in player command
		cout << "What would you like to do?" << endl << endl;
		cin >> commandVerb >> commandObject;
		cout << endl;

		// Convert player command to all upper case
		for (verbIndex = 0; verbIndex < commandVerb.length(); verbIndex++)
		{
			commandVerb[verbIndex] = toupper(commandVerb[verbIndex]);
		}
		for (objectIndex = 0; objectIndex < commandObject.length(); objectIndex++)
		{
			commandObject[objectIndex] = toupper(commandObject[objectIndex]);
		}

		// Parse player command
		if (commandVerb == "GO")
		{
			if (commandObject == "NORTH")
			{
				if (caveGrid[iRow][iColumn] & DOOR_NORTH) 
				{
					iRow--;
					DescribeRoomContents(caveGrid[iRow][iColumn], iRow, iColumn);
					// cout << "Command is GO NORTH." << endl;
					// cout << "Location is: Row " << iRow << " Column " << iColumn << endl << endl;
				}
				else
				{
					cout << "You cannot go that way." << endl;
				}
			}
			else if (commandObject == "EAST")
			{
				if (caveGrid[iRow][iColumn] & DOOR_EAST)
				{
					iColumn++;
					DescribeRoomContents(caveGrid[iRow][iColumn], iRow, iColumn);
					// cout << "Command is GO EAST." << endl;
					// cout << "Location is: Row " << iRow << " Column " << iColumn << endl << endl;
				}
				else
				{
					cout << "You cannot go that way." << endl;
				}
			}
			else if (commandObject == "SOUTH")
			{
				if (caveGrid[iRow][iColumn] & DOOR_SOUTH)
				{
					iRow++;
					DescribeRoomContents(caveGrid[iRow][iColumn], iRow, iColumn);
					// cout << "Command is GO SOUTH." << endl;
					// cout << "Location is: Row " << iRow << " Column " << iColumn << endl << endl;
				}
				else
				{
					cout << "You cannot go that way." << endl;
				}
			}
			else if (commandObject == "WEST")
			{
				if (caveGrid[iRow][iColumn] & DOOR_WEST)
				{
					iColumn--;
					DescribeRoomContents(caveGrid[iRow][iColumn], iRow, iColumn);
					// cout << "Command is GO WEST." << endl;
					// cout << "Location is: Row " << iRow << " Column " << iColumn << endl << endl;
				}
				else
				{
					cout << "You cannot go that way." << endl;
				}
			}
			else
			{
				cout << "GO where?" << endl << endl;
			}
			if ((iRow == endRow) && (iColumn == endColumn))
			{
				if ((iPlayer & GLOVES) && (iPlayer & STAFF) && (iPlayer & ROPE) && (iPlayer & VIAL))
				{
					cout << endl << "Looking at the stone door and the objects you have collected, you begin to" << endl;
					cout << "formulate a plan to escape the cave. Holding the vial, you are able to see" << endl;
					cout << "the door very well, and you notice a small crevice on the bottom that you" << endl;
					cout << "could possibly grip. With the gloves of strength on your hands, you grasp and" << endl;
					cout << "lift the door, easily moving the stone that would normally be much too heavy" << endl;
					cout << "to budge." << endl << endl;
					cout << "As you lift the door above your head, you quickly position the staff underneath" << endl;
					cout << "it, holding it open. Advancing into the shaft that leads to the outside, you" << endl;
					cout << "tie a loop in the rope and throw it upward, hoping to catch it on something to" << endl;
					cout << "help you climb up. On your third try, you hook a rock on the ledge above, and" << endl;
					cout << "you climb the rope to the top." << endl << endl;
					cout << "As you step outside, you breathe in the fresh air, reveling in your freedom." << endl;
					cout << "You have successfully escaped the cave!" << endl << endl;
					cout << "YOU WON" << endl << endl;
					endGame = true;
				}
			}
		}
		else if (commandVerb == "TAKE")
		{
			// cout << "Command is TAKE " << commandObject << "." << endl;
			int takeVal = TakeItem(caveGrid, iRow, iColumn, commandObject);
			if (takeVal)
			{
				iPlayer |= takeVal;
				DescribeObject(commandObject);
				cout << "You now have the " << commandObject << "." << endl;
			}
			else
				cout << "You cannot take the " << commandObject << endl;
		}
		else if (commandVerb == "QUIT")
		{
			endGame = true;		// Break game loop
			// cout << "Command is QUIT " << commandObject << "." << endl;
			cout << "You decide that attempting to escape is futile. Beaten, you slump against" << endl;
			cout << "the wall. Perhaps some future explorer will find your remains someday, and" << endl;
			cout << "maybe even accomplish what you could not: escape the cave." << endl << endl;
			cout << "GAME OVER" << endl << endl;
		}
		else
		{
			// cout << "Command is " << commandVerb << " " << commandObject << "." << endl;
			cout << "Do what?" << endl << endl;
		}
	}
	
	// --------------------------
	// Room Description Functions
	// --------------------------
	
	/*
	DescribeRoom_0_0();
	cout << endl;
	system ("pause");

	DescribeRoom_0_1();
	cout << endl;
	system ("pause");

	DescribeRoom_0_2();
	cout << endl;
	system ("pause");

	DescribeRoom_0_3();
	cout << endl;
	system ("pause");

	DescribeRoom_1_0();
	cout << endl;
	system ("pause");

	DescribeRoom_1_1();
	cout << endl;
	system ("pause");

	DescribeRoom_1_2();
	cout << endl;
	system ("pause");

	DescribeRoom_1_3();
	cout << endl;
	system ("pause");

	DescribeRoom_2_0();
	cout << endl;
	system ("pause");

	DescribeRoom_2_1();
	cout << endl;
	system ("pause");

	DescribeRoom_2_2();
	cout << endl;
	system ("pause");

	DescribeRoom_2_3();
	cout << endl;
	system ("pause");

	DescribeRoom_3_0();
	cout << endl;
	system ("pause");

	DescribeRoom_3_1();
	cout << endl;
	system ("pause");

	DescribeRoom_3_2();
	cout << endl;
	system ("pause");

	DescribeRoom_3_3();
	cout << endl;
	system ("pause");

	DescribeRoom_4_0();
	cout << endl;
	system ("pause");

	DescribeRoom_4_1();
	cout << endl;
	system ("pause");

	DescribeRoom_4_2();
	cout << endl;
	system ("pause");

	DescribeRoom_4_3();
	cout << endl;
	*/
}						// END OF MAIN FUNCTION

// =====================================================================================================

// ---------------------------
// Functions to Describe Rooms
// ---------------------------

void DescribeRoom_0_0()
{
	cout << "You are in a rocky corridor. The ceiling is so low that you have to stoop to" << endl;
	cout << "keep from bumping your head on it. This tunnel is cold and dark, and you have" << endl;
	cout << "an odd sensation that the walls are pressing in upon you." << endl;
}

void DescribeRoom_0_1()
{
	cout << "You are in a rough-hewn cave. This cave's wall is particularly coarse and" << endl;
	cout << "rocky, as though it has been hastily carved out by some former occupant." << endl;
	cout << "Above you, a large web, barely visible, stretches from one wall to another," << endl;
	cout << "and strings of webbing hang from it, brushing against your face." << endl;
}

void DescribeRoom_0_2()
{
	cout << "You are in a cavern with a large underground lake. This cavern contains a" << endl;
	cout << "large pool of water, and you hear the faint sound of water lapping against the" << endl;
	cout << "rocky shore. The walls drip with moisture, and there is a faint smell of fish." << endl;
}

void DescribeRoom_0_3()
{
	cout << "You are in a cavern with a large underground lake. The large pool of water" << endl;
	cout << "dominating this room is mostly still, with small ripples occasionally making" << endl;
	cout << "their way to the shore. In the center of the lake is a large stone, protruding" << endl;
	cout << "up from the dark water." << endl;
}

void DescribeRoom_1_0()
{
	cout << "You are in a rocky corridor. The air in this dim tunnel is chilly, and the" << endl;
	cout << "crevices in the walls cause strangely shaped shadows that give you the creeps." << endl;
}

void DescribeRoom_1_1()
{
	cout << "You are in a small cavern. This low room is dry and cool, with several little" << endl;
	cout << "stones piled near the walls. A few stalactites hang from the ceiling. A small" << endl;
	cout << "ridge of green moss lines the wall." << endl;
}

void DescribeRoom_1_2()
{
	cout << "You are in a dank cave. This cave has a damp, mildewed smell, and the occasional" << endl;
	cout << "drop falls from the ceiling, the sound echoing through the room. Towards the" << endl;
	cout << "back of the cave is a dark corner, hidden in shadow." << endl;
}

void DescribeRoom_1_3()
{
	cout << "You are in a stone tunnel. This long tunnel has mostly smooth walls and floors," << endl;
	cout << "and small, crumbing rocks are scattered here and there. There is a small cavity" << endl;
	cout << "on one wall, and you can dimly see a few shiny stones protruding fom it." << endl;
}

void DescribeRoom_2_0()
{
	cout << "You are in a rocky alcove. This dry and sheltered alcove contains a flat rock," << endl;
	cout << "which appears to have been used as a sort of impromptu table. A burned-out torch" << endl;
	cout << "lies useless next to it." << endl;
}

void DescribeRoom_2_1()
{
	cout << "You are in the large central cavern of the cave system. This magnificent cavern" << endl;
	cout << "has high arches, and far above, shafts of sunlight pierce through the cracks of" << endl;
	cout << "the stony ceiling. The room resembles a dome, and the openness of the room is" << endl;
	cout << "oddly comforting so deep in the cave system." << endl;
}

void DescribeRoom_2_2()
{
	cout << "You are in a dim cavern. This dark room is largely concealed in shadow, and it's" << endl;
	cout << "hard to see the back walls from where you are. A large group of rocks is piled" << endl;
	cout << "up against the wall near the entrance." << endl;
}

void DescribeRoom_2_3()
{
	cout << "You are in a stone tunnel. This long tunnel has mostly smooth walls and floors," << endl;
	cout << "and small, crumbing rocks are scattered here and there. Near the wall, stalagmites" << endl;
	cout << "jut up from the floor." << endl;
}

void DescribeRoom_3_0()
{
	cout << "You are in a wet cave. This cave has a small pond in the corner, and a small" << endl;
	cout << "stream of water trickles down the back wall. You hear the occasional splash from" << endl;
	cout << "the water." << endl;
}

void DescribeRoom_3_1()
{
	cout << "You are in a large cavern. This open room has several large rocks in it; it looks" << endl;
	cout << "looks like a safe place to rest. One of the rocks even roughly resembles a chair," << endl;
	cout << "and you wonder if it has been carved to look that way by some former visitor of" << endl;
	cout << "the cave." << endl;
}

void DescribeRoom_3_2()
{
	cout << "You are in a tunnel junction. This dark tunnel splits in three directions. You" << endl;
	cout << "feel a slight draft. On one wall, you see that the rock has been chipped away," << endl;
	cout << "a definite sign that someone has been here before you." << endl;
}

void DescribeRoom_3_3()
{
	cout << "You are in a stony cave. This cave has a number of small pebbles that crunch" << endl;
	cout << "underfoot. The walls are bumpy but smooth, and the room is lit by a single shaft" << endl;
	cout << "of light from above." << endl;
}

void DescribeRoom_4_0()
{
	cout << "You are in a glimmering grotto. This large cavern glitters with minerals embedded" << endl;
	cout << "into the walls, lit by the shafts of light coming from above. The beauty of this" << endl;
	cout << "room is breathtaking, and for a minute, you can forget about your dire predicament" << endl;
	cout << "and just enjoy the moment." << endl;
}

void DescribeRoom_4_1()
{
	cout << "You are in a dark cave. As you enter this room, you feel a sense of unease. The" << endl;
	cout << "darkness seems to press in upon you, giving a distinctly creepy feel. There is a" << endl;
	cout << "musty, unpleasant smell in the air, making you grimace in disgust" << endl;
}

void DescribeRoom_4_2()
{
	cout << "You are in a shadowy tunnel. This tunnel is dim and dank, and echoes with distant" << endl;
	cout << "sounds. The floor is littered with scraps of cloth and other debris, which appear" << endl;
	cout << "to have been left behind by some previous explorer." << endl;
}

void DescribeRoom_4_3()
{
	cout << "You are in the cave entrance. This small cavern is where you landed when you fell" << endl;
	cout << "down here. You see a sealed stone door, and nearby is a carpet of moss, as well" << endl;
	cout << "as a triggered pressure plate." << endl;
}

void DescribeObject_Gloves()
{
	cout << "As you put these gloves on, you feel a great strength surge through you. You suddenly" << endl;
	cout << "feel the power to lift objects that might ordinarily be too heavy to move, and notice" << endl;
	cout << "the immense grip strength that they seem to grant you. You could say these gloves are..." << endl;
	cout << "pretty handy." << endl;
}
void DescribeObject_Staff()
{
	cout << "This staff feels quite heavy in your hands, and thrums with some unknown power." << endl;
	cout << "Perhaps it belonged to some wizard in times past. In any case, it feels sturdy" << endl;
	cout << "enough to act as a wedge or prop, should you need to use it as such." << endl;
}
void DescribeObject_Rope()
{
	cout << "This rope is long and thin, and shimmers with a faint metallic sheen. As supple as" << endl;
	cout << "it feels, it is unyielding in your hands, and you get the impression that it is" << endl;
	cout << "almost, if not entirely, unbreakable. This could prove a valuable resource," << endl;
	cout << "particularly if you need to climb something." << endl;
}
void DescribeObject_Vial()
{
	cout << "This vial emits a strange glow, and as you hold it, you see everything grow brighter." << endl;
	cout << "The effect only seems to occur when you hold it or have it on your person. This may" << endl;
	cout << "be useful for seeing any ways to open the door to the exit." << endl;
}
void DescribeObject_Bag()
{
	cout << "This canvas bag appears to be a remnant from some previous explorer's journey, left" << endl;
	cout << "behind on the floor of the cave. Though old, it seems strong and roomy enough to" << endl;
	cout << "carry any objects you may pick up as you explore." << endl;
}
void DescribeObject_Hat()
{
	cout << "This wool felt fedora reminds you of the hat of another famous adventurer, though" << endl;
	cout << "you can't remember his name. Illinois Smith? Ohio Williams? Maybe you'll think of" << endl; 
	cout << "it later... You put it on at a jaunty angle, looking dashing." << endl;
}
void DescribeObject_Coat()
{
	cout << "This brown leather coat is worn and faded, and the pockets are empty, but it fits" << endl;
	cout << "well. It also provides some warmth in this dank cavern, and it makes you look awesome." << endl;
}
void DescribeObject_Boots()
{
	cout << "These old boots fit surprisingly well. What are the odds that someone would leave" << endl;
	cout << "their boots down here, and that they would be just your size?" << endl;
}
void DescribeObject_Ring()
{
	cout << "This simple gold ring piques your interest. You look at it curiously before sliding" << endl;
	cout << "it onto your finger. You feel a little less visible, for some reason." << endl;
}
void DescribeObject_Fish()
{
	cout << "This silver fish flops a bit, then goes limp. Why would you want to take a fish? You" << endl;
	cout << "are baffled at your own odd decision." << endl;
}
void DescribeObject_Geode()
{
	cout << "This stone has been broken to reveal some purple crystals inside. It isn't worth" << endl;
	cout << "much, but it looks cool. It would make a nice paperweight." << endl;
}
void DescribeObject_Gold()
{
	cout << "These gold doubloons seem centuries old - there's no telling who left them here, but" << endl;
	cout << "they're definitely an interesting find!" << endl;
}
void DescribeObject_Diamond()
{
	cout << "This gemstone, while rough and uncut, still gleams in the low light of the cavern." << endl;
	cout << "Judging by its size, it could be worth a fortune!" << endl;
}
void DescribeObject_Skull()
{
	cout << "This oddly shaped skull looks like nothing you've seen before. What kind of creature" << endl;
	cout << "was this? You put it in your bag, eager to examine it more later." << endl;
}
void DescribeObject_Parchment()
{
	cout << "The inscription on this paper reads, \"This is the cord of the famed King Daronus. It" << endl;
	cout << "was woven by his finest craftsmen, and imbued with arcane magic to make it impervious" << endl;
	cout << "to all damage. Lucky is he who carries it, for it shall never fail.\"" << endl;
}

void DescribeRoomContents(int roomDescription, int row, int column)
{
	switch(row)
	{
		case 0:
			switch(column)
			{
				case 0:
					DescribeRoom_0_0();
					break;
				case 1:
					DescribeRoom_0_1();
					break;
				case 2:
					DescribeRoom_0_2();
					break;
				case 3:
					DescribeRoom_0_3();
					break;
			}
			break;
		case 1:
			switch(column)
			{
				case 0:
					DescribeRoom_1_0();
					break;
				case 1:
					DescribeRoom_1_1();
					break;
				case 2:
					DescribeRoom_1_2();
					break;
				case 3:
					DescribeRoom_1_3();
					break;
			}
			break;
		case 2:
			switch(column)
			{
				case 0:
					DescribeRoom_2_0();
					break;
				case 1:
					DescribeRoom_2_1();
					break;
				case 2:
					DescribeRoom_2_2();
					break;
				case 3:
					DescribeRoom_2_3();
					break;
			}
			break;
		case 3:
			switch(column)
			{
				case 0:
					DescribeRoom_3_0();
					break;
				case 1:
					DescribeRoom_3_1();
					break;
				case 2:
					DescribeRoom_3_2();
					break;
				case 3:
					DescribeRoom_3_3();
					break;
			}
			break;
		case 4:
			switch(column)
			{
				case 0:
					DescribeRoom_4_0();
					break;
				case 1:
					DescribeRoom_4_1();
					break;
				case 2:
					DescribeRoom_4_2();
					break;
				case 3:
					DescribeRoom_4_3();
					break;
			}
			break;
	}
	// Describe Creatures in Room
	if (roomDescription & SPIDER)
	{
		cout << "Looking up, you see a large, menacing-looking spider, perched on a web that" << endl;
		cout << "dominates an entire corner of the room. Its sharp-looking mandibles glisten" << endl;
		cout << "in the dim light." << endl;
	}
	if (roomDescription & BAT)
	{
		cout << "A small rustling sound alerts you to the presence of a small brown bat hanging" << endl;
		cout << "from the ceiling. It seems aware of your presence, but doesn't seem to mind." << endl;
	}
	if (roomDescription & SNAKE)
	{
		cout << "A sharp hiss causes you to look down. A few feet away, a large black snake is" << endl;
		cout << "curled up on the floor. Its head is raised, watching you warily, and it makes a" << endl;
		cout << "low warning sound." << endl;
	}
	if (roomDescription & CREATURE)
	{
		cout << "You see a strange creature perched on the damp boulder. Its pale skin and large," << endl;
		cout << "orblike eyes make you suspect that it's been living underground for some time now." << endl;
		cout << "It mutters to itself, occasionally making a strange coughing sound in its throat." << endl;
		cout << "It seems to be looking for something..." << endl;
	}
	if (roomDescription & BEAR)
	{
		cout << "From a dark corner of the room, you hear a deep rumbling sound. Peering closer," << endl;
		cout << "you see an enormous bear rise to its feet. It sniffs curiously at the air and" << endl;
		cout << "turns its head in your direction." << endl;
	}
	if (roomDescription & FROG)
	{
		cout << "On the damp floor, a small green frog croaks softly. As you approach, it hops" << endl;
		cout << "away towards a shadowy part of the room." << endl;
	}
	if (roomDescription & RAT)
	{
		cout << "On the edge of the room, a flurry of motion catches your eye. A dark grey rat" << endl;
		cout << "scurries along the wall, its fur matted and dirty. It looks like it hasn't eaten" << endl;
		cout << "in some time." << endl;
	}

	// State Danger Level of Creatures
	if (roomDescription & HARMLESS)
	{
		cout << "This creature is harmless, and bears no threat to you." << endl;
	}
	if (roomDescription & CAUTION)
	{
		cout << "This creature probably won't hurt you, but you should still be careful around it." << endl;
	}
	if (roomDescription & DANGEROUS)
	{
		cout << "This creature is dangerous. Be very careful, and get away from it as soon as possible." << endl;
	}
	if (roomDescription & DEADLY)
	{
		cout << "This creature is deadly. Get out of there!" << endl;
	}

	// Describe Treasure Items
	if (roomDescription & GLOVES)
	{
		cout << "You see an old pair of brown leather gloves lying on the floor. Though worn, they" << endl;
		cout << "appear sturdy, and they look as though they would fit you fairly well..." << endl;
	}
	if (roomDescription & STAFF)
	{
		cout << "In the back corner of the room, partially hidden by shadow, you see an old, gnarled" << endl;
		cout << "staff, rubbed smooth with use. Perhaps you should investigate it further..." << endl;
	}
	if (roomDescription & ROPE)
	{
		cout << "On the rock, you see a strange cord, coiled neatly. Its silvery color intrigues" << endl;
		cout << "you, and you get the impression that this is no ordinary rope..." << endl;
	}
	if (roomDescription & VIAL)
	{
		cout << "Nestled among the crystals in the wall is a strange, shining vial. It appears" << endl;
		cout << "to be filled with some strange substance, and you find its beauty alluring..." << endl;
	}

	// Describe Other Items
	if (roomDescription & BAG)
	{
		cout << "You see an old canvas bag on the cave floor." << endl;
	}
	if (roomDescription & HAT)
	{
		cout << "There is a felt fedora hanging from one of the stalagmites." << endl;
	}
	if (roomDescription & COAT)
	{
		cout << "There is a leather coat partially buried under some rocks." << endl;
	}
	if (roomDescription & BOOTS)
	{
		cout << "On the floor by the wall is a pair of black boots." << endl;
	}
	if (roomDescription & RING)
	{
		cout << "On the shore, a shiny gold ring catches your eye." << endl;
	}
	if (roomDescription & FISH)
	{
		cout << "In the shallows of the lake, a dull silver fish is floating near the shore." << endl;
	}
	if (roomDescription & GEODE)
	{
		cout << "Among the pebbles on the floor, you see a large geode." << endl;
	}
	if (roomDescription & GOLD)
	{
		cout << "There are some shiny gold coins scattered across the stony floor." << endl;
	}
	if (roomDescription & DIAMOND)
	{
		cout << "On the floor, a large diamond catches the light." << endl;
	}
	if (roomDescription & SKULL)
	{
		cout << "Near the entrance to the room, a strange skull rests on the floor." << endl;
	}
	if (roomDescription & PARCHMENT)
	{
		cout << "On the floor by the rock, there is a rolled-up piece of parchment." << endl;
	}

	// Describe Doors
	if (roomDescription & DOOR_NORTH)
	{
		cout << "There is an exit to the NORTH." << endl;
	}
	if (roomDescription & DOOR_EAST)
	{
		cout << "There is an exit to the EAST." << endl;
	}
	if (roomDescription & DOOR_SOUTH)
	{
		cout << "There is an exit to the SOUTH." << endl;
	}
	if (roomDescription & DOOR_WEST)
	{
		cout << "There is an exit to the WEST." << endl;
	}
}

void BuildRoom(unsigned int rooms[][4])
{
	rooms[0][0] = DOOR_EAST | DOOR_SOUTH;
	rooms[0][1] = DOOR_WEST | SPIDER | CAUTION | GLOVES;
	rooms[0][2] = DOOR_EAST | DOOR_SOUTH | FISH;
	rooms[0][3] = DOOR_WEST | CREATURE | DANGEROUS | RING;
	rooms[1][0] = DOOR_NORTH | DOOR_EAST | SNAKE | DANGEROUS | BOOTS;
	rooms[1][1] = DOOR_SOUTH | DOOR_WEST;
	rooms[1][2] = DOOR_NORTH | DOOR_EAST | STAFF;
	rooms[1][3] = DOOR_SOUTH | DOOR_WEST;
	rooms[2][0] = DOOR_EAST | ROPE | PARCHMENT;
	rooms[2][1] = DOOR_NORTH | DOOR_EAST | DOOR_SOUTH | DOOR_WEST | GOLD;
	rooms[2][2] = DOOR_WEST | BAT | HARMLESS | COAT;
	rooms[2][3] = DOOR_NORTH | DOOR_SOUTH | RAT | CAUTION | HAT;
	rooms[3][0] = DOOR_EAST | DOOR_SOUTH | FROG | HARMLESS;
	rooms[3][1] = DOOR_NORTH | DOOR_EAST | DOOR_WEST;
	rooms[3][2] = DOOR_EAST | DOOR_SOUTH | DOOR_WEST;
	rooms[3][3] = DOOR_NORTH | DOOR_WEST | GEODE;
	rooms[4][0] = DOOR_NORTH | DOOR_EAST | DIAMOND | VIAL;
	rooms[4][1] = DOOR_WEST | BEAR | DEADLY | SKULL;
	rooms[4][2] = DOOR_NORTH | DOOR_EAST | BAG;
	rooms[4][3] = DOOR_WEST;
}

void DescribeObject(string commandObject)
{
	if (commandObject == "GLOVES")
		DescribeObject_Gloves();
	else if (commandObject == "STAFF")
		DescribeObject_Staff();
	else if (commandObject == "ROPE")
		DescribeObject_Rope();
	else if (commandObject == "VIAL")
		DescribeObject_Vial();
	else if (commandObject == "BAG")
		DescribeObject_Bag();
	else if (commandObject == "HAT" || commandObject == "FEDORA")
		DescribeObject_Hat();
	else if (commandObject == "COAT")
		DescribeObject_Coat();
	else if (commandObject == "BOOTS")
		DescribeObject_Boots();
	else if (commandObject == "RING")
		DescribeObject_Ring();
	else if (commandObject == "FISH")
		DescribeObject_Fish();
	else if (commandObject == "GEODE")
		DescribeObject_Geode();
	else if (commandObject == "GOLD" || commandObject == "COINS")
		DescribeObject_Gold();
	else if (commandObject == "DIAMOND")
		DescribeObject_Diamond();
	else if (commandObject == "SKULL")
		DescribeObject_Skull();
	else if (commandObject == "PARCHMENT")
		DescribeObject_Parchment();
}

int TakeItem(unsigned int rooms[][4], int row, int column, string Object)
{
	if (Object == "GLOVES" && (rooms[row][column] & GLOVES))
	{
		rooms[row][column] ^= GLOVES;
		return GLOVES;
	}
	if (Object == "ROPE" && (rooms[row][column] & ROPE))
	{
		rooms[row][column] ^= ROPE;
		return ROPE;
	}
	if (Object == "STAFF" && (rooms[row][column] & STAFF))
	{
		rooms[row][column] ^= STAFF;
		return STAFF;
	}
	if (Object == "VIAL" && (rooms[row][column] & VIAL))
	{
		rooms[row][column] ^= VIAL;
		return VIAL;
	}
	if (Object == "BAG" && (rooms[row][column] & BAG))
	{
		rooms[row][column] ^= BAG;
		return BAG;
	}
	if ((Object == "HAT" || Object == "FEDORA") && (rooms[row][column] & HAT))
	{
		rooms[row][column] ^= HAT;
		return HAT;
	}
	if (Object == "COAT" && (rooms[row][column] & COAT))
	{
		rooms[row][column] ^= COAT;
		return COAT;
	}
	if (Object == "BOOTS" && (rooms[row][column] & BOOTS))
	{
		rooms[row][column] ^= BOOTS;
		return BOOTS;
	}
	if (Object == "RING" && (rooms[row][column] & RING))
	{
		rooms[row][column] ^= RING;
		return RING;
	}
	if (Object == "FISH" && (rooms[row][column] & FISH))
	{
		rooms[row][column] ^= FISH;
		return FISH;
	}
	if (Object == "GEODE" && (rooms[row][column] & GEODE))
	{
		rooms[row][column] ^= GEODE;
		return GEODE;
	}
	if ((Object == "GOLD" || Object == "COINS") && (rooms[row][column] & GOLD))
	{
		rooms[row][column] ^= GOLD;
		return GOLD;
	}
	if (Object == "DIAMOND" && (rooms[row][column] & DIAMOND))
	{
		rooms[row][column] ^= DIAMOND;
		return DIAMOND;
	}
	if (Object == "SKULL" && (rooms[row][column] & SKULL))
	{
		rooms[row][column] ^= SKULL;
		return SKULL;
	}
	if (Object == "PARCHMENT" && (rooms[row][column] & PARCHMENT))
	{
		rooms[row][column] ^= PARCHMENT;
		return PARCHMENT;
	}
	return 0;
}

//======================================================================================================
// ----------------
// Additional Notes
// ----------------

// For reference, a map of the game's rooms:
//      0      1      2      3
//   _____________________________
//   |             |             |
// 0 |             |             |
//   |       ______|       ______|
//   |             |             |
// 1 |             |             |
//   |_______      |_______      |
//   |                    |      |
// 2 |                    |      |
//   |_______       ______|      |
//   |                           |
// 3 |                           |
//   |       _______       ______|
//   |             |             |
// 4 |             |        Start|
//   |_____________|_____________|

// Changes made in this version:
// Added TAKE function to allow player to remove item from room and carry it
// Added object description functions to display when an item is taken
// Added endgame code

// Future plans:
// Add achievements
// Add use function
// Add more objects
// Add fight function
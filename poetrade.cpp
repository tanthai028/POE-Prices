#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include <limits>
using namespace std;

/*
Created by Tan 
7/8/2020
*/

vector<string> getCraft(vector<string> craft);
vector<string> resetStack(vector<string> craft);
int getPrice(vector<string> craft, int price);
void print(vector<string> craft, int price);


int main() {
	// init 

	char repeat = 'y';
	int price = 0;
	vector<string> craft;

	while(repeat == 'y') {
		// run
		craft = getCraft(craft);
		price = getPrice(craft, price);
    
    if(price == 0) {
      cout << "\nInvalid Craft\n";
      craft = resetStack(craft);
    }
		
    else {
      print(craft, price);

      cout << "Repeat (y/n): ";
      cin >> repeat;

      craft = resetStack(craft);
      price = 0;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
	}

	return 0;
}

vector<string> resetStack(vector<string> craft) {
	while (!craft.empty()) 
		craft.pop_back(); 

	return craft;
}


vector<string> getCraft(vector<string> craft) {
	string input;
	cout << "Craft: ";
	getline(cin, input);
	istringstream is(input);

	while(is >> input) 
		craft.push_back(input);
  
  if(craft.size() < 3)
    craft.push_back(" ");
	
	return craft;
}

int getPrice(vector<string> craft, int price) {
	int x;
	int y;

	// mapping strings to integers 
	if(craft[0] == "remove" && craft[1] == "add") x = 1;
	else if(craft[0] == "remove") x = 2;
	else if(craft[0] == "aug" || craft[0] == "augment") x = 3;
  else return 0;

	if(craft[1] == "life" || craft[2] == "life") y = 1;
	else if(craft[1] == "defense" || craft[2] == "defense") y = 2;
	else if(craft[1] == "attack" || craft[2] == "attack") y = 3;
	else if(craft[1] == "caster" || craft[2] == "caster") y = 4;
	else if(craft[1] == "phys" || craft[1] == "physical" || craft[2] == "phys" || craft[2] == "physical") y = 5;
	else if(craft[1] == "fire" || craft[2] == "fire") y = 6;
	else if(craft[1] == "cold" || craft[2] == "cold") y = 7;
	else if(craft[1] == "light" || craft[1] == "lightning" || craft[2] == "light" || craft[2] == "lightning") y = 8;
	else if(craft[1] == "chaos" || craft[2] == "chaos") y = 9;
	else if(craft[1] == "speed" || craft[2] == "speed") y = 10;
	else if(craft[1] == "crit" || craft[2] == "crit") y = 11;
  else return 0;

	switch (x) {
		case 1: price = 50; break;
		case 2: price = 50; break;
		case 3: price = 30; break;
    default: break;
	}

	switch (y) {
		case 1:
		case 2: price += 10; break;
		case 3:
		case 4:
		case 5:
			switch (x) {
				// Remove/add and Augment
				case 1:
				case 3:
					price -= 10; break;
				default: break;
			}
			break;

		case 6: 
		case 7:
		case 8: break;

		case 9:
			switch (x) {
				// Chaos remove/add and augment
				case 1: 
				case 3: price += 10; break;
				default: break;
			}
			break;
		case 10:
		case 11: price = 180; break;
	}

	return price;
}

void print(vector<string> craft, int price) {

	string temp = craft[0];
	temp[0] = toupper(temp[0]);
	craft[0] = temp;

	for(int i = 0; i < craft.size(); i++) {
    if(craft[i] == " ") break;
		cout << craft[i] << " ";
	}

	cout << price << "c\n\n";
}

// wip:
// if Remove add, price = 50
// if Remove, price = 30
// if Augment, price = 50
// if Reforge, price = 80
// if Sockets, price = 20
// if Misc, price = 0

// types:
// if life, price + 10
// if defense, price + 10
// if attack, if remove/add or augment, price - 10
// if caster, if remove/add or augment, price - 10
// if caster, if remove/add or augment, price - 10
// if any element, price doesn't change
// if chaos, price + 20
// if speed, price = 180
// if critical, price = 180

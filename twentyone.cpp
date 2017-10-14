/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Wei-Yu Yu
 * USC email: weiyuyu@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */

const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
	for(int i= NUM_CARDS-1; i>0; i--){
		int temp;
		int j = rand()%(i+1);
		temp = cards[i];
		cards[i]=cards[j];
		cards[j]= temp; 
	}

}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
	switch(id%13){
		case 0: 
			cout << "2-";
			break;
		case 1: 
			cout << "3-";
			break;
		case 2: 
			cout << "4-";
			break;
		case 3: 
			cout << "5-";
			break;
		case 4: 
			cout << "6-";
			break;
		case 5: 
			cout << "7-";
			break;
		case 6: 
			cout << "8-";
			break;
		case 7: 
			cout << "9-";
			break;
		case 8: 
			cout << "10-";
			break;
		case 9: 
			cout << "J-";
			break;
		case 10: 
			cout << "Q-";
			break;
		case 11: 
			cout << "K-";
			break;
		case 12: 
			cout << "A-";
			break;
		default: break;
	}

	switch(id/13){
		case 0: 
			cout << "H";
			break;
		case 1: 
			cout << "S";
			break;
		case 2: 
			cout << "D";
			break;
		case 3: 
			cout << "C";
			break;
		default: break;
	}

	cout << " ";
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
	int val = id%13;
	return value[val];

}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
 	for(int i=0; i<numCards; i++){
 		printCard(hand[i]);
 		cout << " ";
 	}

 	cout << "\n";
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
	int sum = 0;
	bool addedAce = false;
	int AcesAdded = 0;

	for(int i=0; i<numCards; i++){
		
		if((hand[i]%13==12)&&(sum+11>21))
			sum++;
		else
			sum+=value[hand[i]%13];
		
		if (hand[i]%13 == 12){
			addedAce = true;
			AcesAdded++;
		}
	}

	if(addedAce&&sum>21){
		sum = 0;
		for(int i=0; i<numCards; i++){
			if(hand[i]%13==12)
				sum++;
			else
				sum+=value[hand[i]%13];
		}
	}

	return sum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[]){
	//---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }

  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
 bool repeat = true;

  while(repeat){
  	
  	char choice;
  	int phandsize = 2, dhandsize = 2;

  	for(int i=0; i<NUM_CARDS;i++){
  		cards[i]=i;
  	}

  	shuffle(cards);

  	for(int i=0; i<2; i++){

  		phand[i] = cards[2*i];
  		dhand[i] = cards[2*i+1];
  	} // Deal starting hand

  	cout << "Dealer: " << "? " ; 
  	printCard(dhand[1]);
  	cout << endl;
  	cout << "Player: "; 
  	printHand(phand,phandsize);


  	while(getBestScore(phand,phandsize)<21){

  		cout << "Type 'h' to hit and 's' to stay: ";
  		cin >> choice;

  		if(choice == 'h'){

  			phand[phandsize] = cards[2+phandsize];
  			phandsize++;
  			cout << "Player: ";
  			printHand(phand,phandsize);
 
  		}

  		else 
  			break;

  	}

  		if(getBestScore(phand,phandsize)>21){
  			cout << "Player Busts!\n" << "Lose ";
  			cout << getBestScore(phand,phandsize) << " "; 
  			cout << getBestScore(dhand,dhandsize) << endl;
  		}

  		else if(getBestScore(phand,phandsize<=21)){
  			
  			while(getBestScore(dhand,dhandsize)<17){
  				dhand[dhandsize] = cards[dhandsize+phandsize];
  				dhandsize++;
  			}


  			cout << "Dealer: "; 
  			printHand(dhand,dhandsize);
  			cout << endl;

  			if(getBestScore(dhand,dhandsize)>21){

  				cout << "Dealer Busts!\n";
  				cout << "Win " << getBestScore(phand,phandsize); 
  				cout << " " << getBestScore(dhand,dhandsize);
  			}

  			else{

  				if(getBestScore(phand,phandsize)>getBestScore(dhand,dhandsize)){
  					cout << "Win " << getBestScore(phand,phandsize); 
  					cout << " " << getBestScore(dhand,dhandsize) << endl;
  				}

  				else if(getBestScore(phand,phandsize)<getBestScore(dhand,dhandsize)){
  					cout << "Lose " << getBestScore(phand,phandsize); 
  					cout << " " << getBestScore(dhand,dhandsize) << endl;
  				}

  				else{
  					cout << "Tie " << getBestScore(phand,phandsize); 
  					cout << " " << getBestScore(dhand,dhandsize) << endl;
  				}
  			}
  			
  		}
			
			cout << "\n";
			cout << "Play Again? y/n: ";
			cin >> choice;

		if(choice == 'y')
			repeat = true;
		

		else{
			repeat = false;
			break;
		}
  	}

  	return 0;

 }
  	
	


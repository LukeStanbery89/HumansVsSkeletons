#include <iostream>
#include <random>
#include <ctime>

using namespace std;

// Prototypes
int getNumHumans();
int getNumSkeletons();
void printResults(int numHumans, int numSkeletons, int startHumans, int startSkeletons);
void simulateBattle(int &numHumans, int &numSkeletons);

int main() {
	int numSkeletons;
	int startSkeletons;
	int numHumans;
	int startHumans;

	cout << "*** Skeletons vs. Humans ***\n";

	// Get the number of humans
	numHumans = getNumHumans();
	startHumans = numHumans;

	// Get the number of skeletons
	numSkeletons = getNumSkeletons();
	startSkeletons = numSkeletons;

	// FIGHT!!!
	simulateBattle(numHumans, numSkeletons);

	// Print the results of the battle
	printResults(numHumans, numSkeletons, startHumans, startSkeletons);

	system("PAUSE");
	return 0;
}

/// <summary>
/// Gets input from the user and returns the number of humans.
/// </summary>
int getNumHumans() {
	int numHumans;

	cout << "\nEnter the number of humans: ";
	cin >> numHumans;

	return numHumans;
}

/// <summary>
/// Gets input from the user and returns the number of skeletons.
/// </summary>
int getNumSkeletons() {
	int numSkeletons;

	cout << "\nEnter the number of skeletons: ";
	cin >> numSkeletons;

	return numSkeletons;
}

/// <summary>Print the results of the battle to the screen.</summary>
/// <param name="numHumans">Number of humans remaining after the battle.</param>
/// <param name="numSkeletons">Number of skeletons remaining after the battle.</param>
/// <param name="startHumans">Number of humans before the battle.</param>
/// <param name="startSkeletons">Number of skeletons before the battle.</param>
void printResults(int numHumans, int numSkeletons, int startHumans, int startSkeletons) {
	cout << "\nBattle is over!\n\n";

	if(numHumans > 0) {
		cout << "Humans win!\n";
		cout << "There are " << numHumans << " humans left.\n\n";
	} else {
		cout << "Skeletons win!\n";
		cout << "There are " << numSkeletons << " skeletons left.\n\n";
	}

	// Kill counter
	cout << startHumans - numHumans << " humans died.\n";
	cout << startSkeletons - numSkeletons << " skeletons died.\n";
}

/// <summary>Function to make the humans fight the skeletons.</summary>
void simulateBattle(int &numHumans, int &numSkeletons) {
	// Random Engine
	static default_random_engine randomEngine(time(NULL));
	uniform_real_distribution <float> attack(0.0f, 1.0f);

	// Human properties
	float humanAttack = 0.6f;
	float humanHealth = 250.0f;
	float humanDamage = 200.0f;
	float currentHumanHealth = humanHealth;

	// Skeleton properties
	float skeletonAttack = 0.2f;
	float skeletonHealth = 50.0f;
	float skeletonDamage = 40.0f;
	float currentSkeletonHealth = skeletonHealth;

	// For keeping track of whose turn it is
	char turn = 'H';

	float attackResult;

	cout << "\nBeginning combat!\n";

	while((numHumans > 0) && (numSkeletons > 0)) {

		// Get our attack result
		attackResult = attack(randomEngine);

		// Humans' turn
		if(turn == 'H') {

			// Check if attack is successful
			if(attackResult <= humanAttack) {
				currentSkeletonHealth -= humanDamage;

				if(currentSkeletonHealth <= 0) {
					numSkeletons--;
					currentSkeletonHealth = skeletonHealth;
				}
			}

			turn = 'S';
		} else {

			// Check if attack is successful
			if(attackResult <= skeletonAttack) {
				currentHumanHealth -= skeletonDamage;

				if(currentHumanHealth <= 0) {
					numHumans--;
					currentHumanHealth = humanHealth;
				}
			}

			turn = 'H';
		}
	}
}

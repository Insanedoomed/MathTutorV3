/*****************************************************************************************************************************************************
Program: MathTutorV3
Programmers: Joe Bracht and Brayden Tolle
Date: 10/12/2026
Section 3: 12:00
Github Repo: https://github.com/Insanedoomed/MathTutorV3
Description: A wizard/magic themed math tutor that displays the intro featuring
ASCII art and jokes, it then asks a simple math question which is checked for correctness
and then it outputs an end of program message.
****************************************************************************************************************************************************/
#include <iostream> //required for cout and cin
#include <cstdlib> // for srand and rand
#include <string> // for string data types
#include <ctime> // for time seeding
#include <limits> // for the use of numeric_limits

using namespace std; //sets standard namespace

//start of the main function; Joe is handling the variable documentation from Brayden's computer
int main() {
    srand(time(0)); // Seed first; used to randomize the numeric operator (+,-,*,/)
    const int MAX_ATTEMPTS = 3; // Our max attempts; stays the same throughout program
    const int LEVEL_RANGE = 10; // Starting range of 1-10; adds ten each level up

    //initializing variables

    string userInput = "?";
    double userAnswer; // The user's answer to the math question
    double correctAns; // The correct answer\

    int rightNum = 0; // the 2nd random number between 1 and level change
    int leftNum = 0; // the 1st random number between 1 and level change
    int temp = 0; // Uses to swap two values
    int questionNumber = 0; // Current question number
    int mathLevel = 1; // Current Math level
    int attempt = 0; // Current attempt number
    int LevelRange = LEVEL_RANGE; // Sent constant to 10 level range is a runnning total num.
    int totalIncorrect = 0; // Current number of incorrect questions; used later for leveling down
    int totalCorrect = 0; // Current number of Correct questions; used for later for leveling up
    char mathSymbol; // {+, -, *, /}
    string userName; // User's name

    //Display the program's header
    cout <<
            "(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]"
            << endl;
    cout << "                       {*} Welcome to the tower of the wizard of magical math tutoring! (V1) {*}" << endl;
    cout << R"(
,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`

                                                                                                                                 )"
            << endl;
    //Display the program's jokes
    cout <<
            "(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]"
            << endl;
    cout << R"(A wise wizards words:
        (*) What's a wizard's favorite school subject? spell-gebra!
        (*) Why did the sorcerer break his calculator? He wanted to do math-a-magics in his head!
        (*) What is a witch's favorite shape? A Hex-agon!
        (*) What do you call a snake that is 3.14 feet long? A Pi-thon!)" << endl << endl;

    cout <<
            "(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]"
            << endl;

    //obtaining user's name and welcoming the user
    cout << "What is your name young apprentice?" << endl;
    getline(cin, userName); // handle for spaces in a person's name
    cout << "" << endl;
    //math question and answer
    cout << "Ah... " << userName <<
            "! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls," <<
            endl;
    cout << " you must first prove your mind is sharp." << endl;
    // start of loop
do {
    questionNumber++; // each loop, it adds one to question each time the user responds yes
    enum MathType {MT_ADD=1 , MT_SUB=2 , MT_MUL=3 , MT_DIV=4}; // Our Enum for all the problems
    MathType mathType = MT_ADD; // sets MathType to a one
    mathType = static_cast<MathType>(rand() % 4 + 1); //Turning into random
    //Generate the random numbers between 1 and 10 for the question
    rightNum = ((rand() % LevelRange) + 1); // Value from 1-whatever level the user is
    leftNum = ((rand() % LevelRange) + 1); // Value from 1-whatever level the user is
    // Ensures that Left num is the larger number
    if (leftNum < rightNum) {
        temp = leftNum;
        leftNum = rightNum;
        rightNum = temp;
    }
    //Switch to calculate the correct answer and which math operator to display
    switch (mathType) {
        case MT_ADD: // addition
            correctAns = leftNum + rightNum;
            mathSymbol = '+';
            break;

        case MT_SUB: // subtraction
            // Ensure the left number is the bigger one to avoid negatives
            if (leftNum < rightNum) {
                temp = leftNum;
                leftNum = rightNum;
                rightNum = temp;
            }
            correctAns = leftNum - rightNum;
            mathSymbol = '-';
            break;

        case MT_MUL: // multiplication
            correctAns = leftNum * rightNum;
            mathSymbol = '*';
            break;

        case MT_DIV: // division
            // Build the dividend so the answer is always a whole number
            correctAns = leftNum;
            leftNum = leftNum * rightNum;
            mathSymbol = '/';
            break;

        default: //error handling - should never happen
            cout << "Invalid question type: " << mathType << endl;
            cout << "Program ended with an error -1" << endl;
            cout << "Please report this error to Brayden Tolle or Joe Bracht" << endl;
            return -1;
    } //End of the switch
    // Start of for loop
    for (int attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) { // If attempt is less than or equal to MAX_ATTEMPTS, it will add one attempt
        cout << "You're on question " << questionNumber << endl; // Question number
        cout << "out of level " << mathLevel << endl; // Level number
        cout << "and on " << attempt << " out of " << MAX_ATTEMPTS << " attempts" << endl; // Attempts left out of the attempts left
        cout << userName << " what is " << leftNum << mathSymbol << rightNum << "?" << endl; // Asks question
        //Start of Loop that loops until the user enters a valid input
        while (!(cin >> userAnswer)) {
            cin.clear(); // clears the cin error flag
            cin.ignore (numeric_limits<streamsize>::max(), '\n'); // ignores the max input, up to '\n'
            cout << "Invalid answer apprentice!" << endl;
            cout << "Please enter a number (like 1,2,3), Apprentice!" << endl;
            cout << userName << " what is " << leftNum << mathSymbol << rightNum << "?" << endl;
        } // end of loop that handles correct user data
        // if user right, then it adds one to total correct
        if (userAnswer == correctAns) {
            cout << "Good job! You Got The Question Right!" << endl;
            totalCorrect++;
            break;
        } else {
            totalIncorrect++;
            if (attempt < MAX_ATTEMPTS) { // IF wrong, your number of attempts goes up
                cout << "Not quite, apprentice!" << endl;
                cout << "You have " << MAX_ATTEMPTS - attempt << " attempets left" << endl;
            } else { // Runs if the user gets three incorrect
                cout << "I'm So Disappointed In You Apprentice..." << endl;
                cout << "The correct answer was " << correctAns << "." << endl;
                totalIncorrect++;
            }

        }
    } // End of For
    // Leveling up
    if (totalCorrect >= 3) {
        mathLevel++;
        LevelRange += LEVEL_RANGE;
        totalCorrect = 0;
        totalIncorrect = 0;
        cout << "You have leveled up to level " << mathLevel << "!" << endl;
        cout << "Numbers will now go up to " << LevelRange << "." << endl;
    } // leveling down
        else if (totalIncorrect >= 3) {
            if (LevelRange > LEVEL_RANGE) {
                mathLevel--;
                LevelRange -= LEVEL_RANGE;
                totalCorrect = 0;
                totalIncorrect = 0;
                cout << "You have leveled down to " << mathLevel << "!" << endl;
                cout << "Number will go down by "  << LevelRange << "!" << endl;
                cout << "The correct answer was " << correctAns << "." << endl;
            }
            totalCorrect = 0; // clears total correct
            totalIncorrect = 0; // clears total incorrect
        }



    getline(cin,userInput); // Clears user input
while (true)  { // asks the user if they want another question
    cout << "Would you like a other question Apprentice? (y=yes/n=no"<< endl;
    getline(cin,userInput);
    for (int i = 0; i < userInput.length(); i++) {
        userInput[i] = tolower(userInput[i]);
    } // user chooses yes or no
    if (userInput == "y" || userInput == "yes" ||
        userInput == "n" || userInput == "no") {
        break;
            }
    cout << "Please enter y, yes, n, no" << endl;
}





} while (userInput == "y" || userInput == "yes"); // User's answer to the yes or no

    cout << "Thank you this is all for now!" << endl;

    return 0;
}

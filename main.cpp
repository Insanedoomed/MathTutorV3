/*****************************************************************************************************************************************************
Program: MathTutorV3
Programmers: Joe Bracht and Brayden Tolle
Date: 10/12/2026
Section 3: 12:00
Github Repo: https://github.com/lashanna-werth250/MathTutorV2
Description: A wizard/magic themed math tutor that displays the intro featuring
ASCII art and jokes, it then asks a simple math question which is checked for correctness
and then it outputs an end of program message.
****************************************************************************************************************************************************/
#include <iostream> //required for cout and cin
#include <cstdlib> // for srand and rand
#include <string> // for string data types
#include <ctime> // for time seeding

using namespace std; //sets standard namespace

//start of the main function
int main() {
    //initializing variables
    double userAnswer; // The user's answer to the math question
    double correctAns; // The correct answer
    int randVar2 = 0; // the 2nd random number between 1 and 10
    int randVar1 = 0; // the 1st random number between 1 and 10
    int mathVar = 0; // Random number {1=add, 2=sub, 3=multi, 4=div}
    int temp = 0; // Uses to swap two values
    char mathSymbol; // {+, -, *, /}
    // Our range of random
    srand((time(0))); // seed the random method with the current time

    //Generate the random numbers between 1 and 10 for the question
    randVar2 = ((rand() % 10) + 1);
    randVar1 = ((rand() % 10) + 1);
    mathVar = ((rand() % 4) + 1);

    string userName;

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
    //Switch to calculate the correct answer and which math operator to display
    switch (mathVar) {
        case 1: //addition
            correctAns = randVar1 + randVar2;
            mathSymbol = '+';
            break;


        case 2: //subtraction

            // Ensures that the left number is greater than the right to avoid negative numbers
            if (randVar1 < randVar2) {
                temp = randVar1;
                randVar1 = randVar2;
                randVar2 = temp;
            }
            correctAns = randVar1 - randVar2;
            mathSymbol = '-';
            break;


        case 3: //Multiplication
            correctAns = randVar1 * randVar2;
            mathSymbol = '*';
            break;


        case 4: //Division
            //avoiding answers with fractions
            correctAns = randVar1;
            randVar1 *= randVar2;
            mathSymbol = '/';
            break;


        default: //error handling - should never happen
            cout << "Invalid question type: " << mathVar << endl;
            cout << "Program ended with an error -1" << endl;
            cout << "Please report this error to Brayden Tolle" << endl;
            return -1;
    } //End of the switch

    // Prompts the user to answer a random math question
    cout << userName << " what is " << randVar1 << mathSymbol << randVar2 << "?" << endl;

    cin >> userAnswer;
    // This should display if they got the answer correct
    //If not, it will display the correct answer
    if (userAnswer == correctAns) {
        cout << "Good job! You Got The Question Right!" << endl;
        cout << endl;
        // tells the user goodbye
        cout << "This is all for our program! I hope you had a fantastic time!!" << endl;
    } else {
        cout << "I'm So Disappointed In You Apprentice..." << endl;
        cout << "The correct answer was " << correctAns << "." << endl;
        cout << endl;
        cout << "Please try again, Apprentice!" << endl;
    }

    return 0;
}

<div align="center">

# 🧙 MathTutorV3
### The Tower of the Wizard of Magical Math Tutoring

*A wizard-themed, console-based math tutor written in C++ that adapts to how well you're doing.*

![Language](https://img.shields.io/badge/language-C%2B%2B-00599C?logo=cplusplus&logoColor=white)
![Standard](https://img.shields.io/badge/C%2B%2B-11%20or%20newer-blue)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey)
![Version](https://img.shields.io/badge/version-3.0-purple)

</div>

```
,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`
```

## Table of Contents

- [About](#about)
- [Features](#features)
- [How It Works](#how-it-works)
  - [A round of play](#a-round-of-play)
  - [Question generation](#question-generation)
  - [Why a random number from 1 to 4](#why-a-random-number-from-1-to-4)
  - [Leveling](#leveling)
- [Getting Started](#getting-started)
- [Console Output Testing](#console-output-testing)
- [Previous Versions (V1 and V2 Outputs)](#previous-versions-v1-and-v2-outputs)
- [Code Tour](#code-tour)
- [Concepts Used](#concepts-used)
- [Known Quirks & Roadmap](#known-quirks--roadmap)
- [Maintainers](#maintainers)

## About

MathTutorV3 is a console math tutor wrapped in a wizard theme. It greets you with ASCII art and a few terrible math puns, asks for your name, then quizzes you with randomly generated addition, subtraction, multiplication, and division problems.

Answer correctly and the numbers get bigger. Miss a question and the tower eases up on you. You keep going for as long as you like.

> **Course project:** CSC150 (Section 3), built as a pair project by Joe Bracht and Brayden Tolle.

## Features

| | |
|---|---|
| 🎲 **Random operations** | Each question randomly picks `+`, `-`, `*`, or `/` using an `enum` |
| 📈 **Adaptive difficulty** | Number range grows by 10 each level up and drops by 10 each level down |
| 🔁 **Three attempts per question** | Wrong answers are met with encouragement (and mild wizard disappointment) |
| 🛡️ **Input validation** | Typing letters instead of a number re-prompts instead of crashing |
| ➗ **Clean division** | Division problems are built backwards so the answer is always a whole number |
| ➖ **No negative answers** | Subtraction always puts the larger number first |
| 📋 **Status box** | Every attempt shows your question number, attempt count, and level |
| 🧾 **Flexible replay prompt** | Accepts `y`, `yes`, `n`, `no` in any capitalization |
| 🧙 **Full theme** | ASCII-art banner, wizard jokes, and in-character feedback |

## How It Works

### A round of play

1. The program shows the banner and four wizard jokes.
2. You enter your name (spaces are fine).
3. A random question is generated for your current level.
4. You get up to **3 attempts** to answer it.
5. The program checks whether you should level up or down.
6. You choose whether to continue with another question.

### Question generation

| Operation | How it's built |
|---|---|
| Addition | `left + right` |
| Subtraction | The larger number goes on the left, so the answer is never negative |
| Multiplication | `left * right` |
| Division | The answer is picked first, then the dividend is `answer * divisor`, so it always divides evenly |

Both numbers are drawn from `1` to the current **number range**.

### Why a random number from 1 to 4

The program has exactly four kinds of problems, and each one is a value of the `MathType` enum:

| Enum value | Number | Operation |
|---|---|---|
| `MT_ADD` | 1 | addition |
| `MT_SUB` | 2 | subtraction |
| `MT_MUL` | 3 | multiplication |
| `MT_DIV` | 4 | division |

The logic is one line:

```cpp
mathType = static_cast<MathType>(rand() % 4 + 1);
```

1. `rand()` returns a large non-negative integer.
2. `% 4` keeps only the remainder after dividing by 4, so the result is always **0, 1, 2, or 3** (four possible values, one per operation).
3. `+ 1` shifts that to **1, 2, 3, or 4**, which lines up with the enum values above.
4. `static_cast<MathType>(...)` converts the plain `int` into a `MathType`, since C++ does not do that conversion automatically.

Why 1 to 4 and not 0 to 3? The enum is numbered starting at 1 so the first operation is "number 1", which reads naturally. The `switch` also has a `default` case that catches any value outside 1 to 4, so if someone edits the range by mistake the program reports it (see [Test 10](#test-10-invalid-question-type)) instead of quietly doing nothing.

The same trick is used for the operands: `rand() % LevelRange + 1` gives a number from **1 to `LevelRange`**. We start at 1 instead of 0 because a 0 would make multiplication trivial and a 0 divisor would crash division.

### Leveling

| Rule | Value |
|---|---|
| Starting level | 1 |
| Starting number range | 1 to 10 |
| Attempts per question | 3 |
| **Level up** | After **3 correct answers** at the current level: the level goes up by 1 and the range grows by 10 |
| **Level down** | After **1 missed question** (all 3 attempts used) while above level 1: the level goes down by 1 and the range goes down by 10 |
| Level 1 misses | No level box is shown and the level stays at 1; you can't go below level 1 |
| On any level change | Correct/missed counters and the question counter reset to 0 |

So level 1 uses numbers up to 10, level 2 up to 20, level 3 up to 30, and so on.

`totalIncorrect` is only incremented in **one place**: at the moment the user runs out of attempts on a question. A wrong answer with attempts still remaining does not count against the level.

## Getting Started

### Requirements

- A C++ compiler with **C++11** support or newer (GCC, Clang, or MSVC). The raw string literals used for the ASCII art need C++11.
- A terminal. A wide window (about 125 columns) keeps the banner from wrapping.

### Build and run

Using `g++` or `clang++` (replace `main.cpp` with your source file's name):

```bash
g++ -std=c++11 -Wall -o MathTutorV3 main.cpp
./MathTutorV3          # on Windows: MathTutorV3.exe
```

Using an IDE (CLion, Visual Studio, Code::Blocks): create a new C++ project, add the source file, and press Run.

### Get the code

```bash
git clone https://github.com/Insanedoomed/MathTutorV3.git
cd MathTutorV3
```

## Console Output Testing

Each test below is collapsed. Click **Click to view the console output** under a test to open it, or use the table to jump straight to the one you want. The outputs match the current code, including the boxed status display. The blank line after each answer is how CLion shows typed input.

| # | Test (click to jump) | What it shows |
|---|---|---|
| 1 | [Correct answer on the first try](#test-1-correct-answer-on-the-first-try) | The happy path: the user answers right on attempt 1 and then chooses to stop |
| 2 | [Wrong answer then right answer](#test-2-wrong-answer-then-right-answer) | A wrong first attempt gets encouragement and the attempt counter in the box goes from 1 to 2 |
| 3 | [Out of attempts](#test-3-out-of-attempts) | Three wrong answers in a row |
| 4 | [Invalid input](#test-4-invalid-input) | The user types a letter instead of a number |
| 5 | [Replay prompt validation](#test-5-replay-prompt-validation) | The replay prompt rejects anything that is not y, yes, n, or no, and ignores capitalization (`YES`, `No`) |
| 6 | [Level up](#test-6-level-up) | Three correct answers at level 1 (one needed a retry) move the user to level 2 |
| 7 | [Level down from level 3](#test-7-level-down-from-level-3) | The user is at level 3 (range 30) and misses one question by using all 3 attempts |
| 8 | [Level down from level 2](#test-8-level-down-from-level-2) | Same rule one level lower: a miss at level 2 drops the user to level 1 and the range goes from 20 to 10 |
| 9 | [No level down at level 1](#test-9-no-level-down-at-level-1) | Missing a question at level 1 does not show a level box: there is no lower level |
| 10 | [Invalid question type](#test-10-invalid-question-type) | The error path in the `default` case of the `switch` |

### Test 1 Correct answer on the first try

The happy path: the user answers right on attempt 1 and then chooses to stop. Shows the full intro (banner, jokes, name prompt), the status box, and the goodbye.

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V3) {*}

,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`



(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

A wise wizards words:
        (*) What's a wizard's favorite school subject? spell-gebra!
        (*) Why did the sorcerer break his calculator? He wanted to do math-a-magics in his head!
        (*) What is a witch's favorite shape? A Hex-agon!
        (*) What do you call a snake that is 3.14 feet long? A Pi-thon!

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
bray


Ah... bray! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 9-4?

5

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
no

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 2 Wrong answer then right answer

A wrong first attempt gets encouragement and the attempt counter in the box goes from 1 to 2.

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V3) {*}

[ ASCII-art banner and wizard jokes: shown in full in Test 1 ]

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
bray


Ah... bray! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 9+2?

1

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 2 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 9+2?

11

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
n

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 3 Out of attempts

Three wrong answers in a row. The wizard is disappointed and a box shows the correct answer.

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V3) {*}

[ ASCII-art banner and wizard jokes: shown in full in Test 1 ]

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
bray


Ah... bray! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 4+8?

2

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 2 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 4+8?

5

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 3 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 4+8?

7

I'm So Disappointed In You Apprentice...
You should've gotten that right...
 |----------------------------------|
 | CorrectAnswer: 12                |
 |----------------------------------|

Would you like a other question Apprentice? (y=yes/n=no
n

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 4 Invalid input

The user types a letter instead of a number. The program re-asks the same question without using up an attempt.

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V3) {*}

[ ASCII-art banner and wizard jokes: shown in full in Test 1 ]

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
bray


Ah... bray! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 1+1?

w

Invalid answer apprentice!
Please enter a number (like 1,2,3), Apprentice!
bray what is 1+1?
2

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
n

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 5 Replay prompt validation

The replay prompt rejects anything that is not y, yes, n, or no, and ignores capitalization (`YES`, `No`). The second question also shows the question counter going to 2.

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V3) {*}

[ ASCII-art banner and wizard jokes: shown in full in Test 1 ]

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
bray


Ah... bray! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 7*3?

21

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
maybe

Please enter y, yes, n, no
Would you like a other question Apprentice? (y=yes/n=no
YES

 |----------------------------------|
 | Question: 2                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 6/2?

3

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
No

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 6 Level up

Three correct answers at level 1 (one needed a retry) move the user to level 2. The number range grows from 10 to 20 and the question counter resets to 1.

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V3) {*}

[ ASCII-art banner and wizard jokes: shown in full in Test 1 ]

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
bray


Ah... bray! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 10-5?

5

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
y

 |----------------------------------|
 | Question: 2                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 9+2?

1

Not quite, apprentice!

 |----------------------------------|
 | Question: 2                      |
 | Attempts: 2 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 9+2?

11

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
y

 |----------------------------------|
 | Question: 3                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 24/3?

8

Good job! You Got The Question Right!

You have Advanced to the next level
 |----------------------------------|
 | NumUp: 20                        |
 | LevelUp: 2                       |
 |----------------------------------|

Would you like a other question Apprentice? (y=yes/n=no
y

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 2                     |
 |----------------------------------|

bray, what is 280/14?

20

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
n

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 7 Level down from level 3

The user is at level 3 (range 30) and misses one question by using all 3 attempts. They drop to level 2 and the range goes down by 10, from 30 to 20. The question counter resets.

<details>
<summary><b>Click to view the console output</b></summary>

```text
[ ...intro, then the user is at level 3... ]

 |----------------------------------|
 | Question: 5                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 3                     |
 |----------------------------------|

bray, what is 23+19?

1

Not quite, apprentice!

 |----------------------------------|
 | Question: 5                      |
 | Attempts: 2 out of 3             |
 | MathLevel: 3                     |
 |----------------------------------|

bray, what is 23+19?

2

Not quite, apprentice!

 |----------------------------------|
 | Question: 5                      |
 | Attempts: 3 out of 3             |
 | MathLevel: 3                     |
 |----------------------------------|

bray, what is 23+19?

3

I'm So Disappointed In You Apprentice...
You should've gotten that right...
 |----------------------------------|
 | CorrectAnswer: 42                |
 |----------------------------------|

You have Advanced down a level
 |----------------------------------|
 | NumDown: 20                      |
 | LevelDown: 2                     |
 |----------------------------------|

Would you like a other question Apprentice? (y=yes/n=no
y

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 2                     |
 |----------------------------------|

bray, what is 14*9?

126

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
n

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 8 Level down from level 2

Same rule one level lower: a miss at level 2 drops the user to level 1 and the range goes from 20 to 10.

<details>
<summary><b>Click to view the console output</b></summary>

```text
[ ...intro, then the user is at level 2... ]

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 2                     |
 |----------------------------------|

bray, what is 280/14?

2

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 2 out of 3             |
 | MathLevel: 2                     |
 |----------------------------------|

bray, what is 280/14?

3

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 3 out of 3             |
 | MathLevel: 2                     |
 |----------------------------------|

bray, what is 280/14?

4

I'm So Disappointed In You Apprentice...
You should've gotten that right...
 |----------------------------------|
 | CorrectAnswer: 20                |
 |----------------------------------|

You have Advanced down a level
 |----------------------------------|
 | NumDown: 10                      |
 | LevelDown: 1                     |
 |----------------------------------|

Would you like a other question Apprentice? (y=yes/n=no
n

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 9 No level down at level 1

Missing a question at level 1 does not show a level box: there is no lower level. The question counter keeps counting (question 2 next) and the level stays 1.

<details>
<summary><b>Click to view the console output</b></summary>

```text
[ ...intro... ]

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 4+8?

2

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 2 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 4+8?

5

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 3 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 4+8?

7

I'm So Disappointed In You Apprentice...
You should've gotten that right...
 |----------------------------------|
 | CorrectAnswer: 12                |
 |----------------------------------|

Would you like a other question Apprentice? (y=yes/n=no
y

 |----------------------------------|
 | Question: 2                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 6+5?

11

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
n

This is MathTutorV3, thanks for playing!
Thank you this is all for now!
```

</details>

[Back to the test list](#console-output-testing)

### Test 10 Invalid question type

The error path in the `default` case of the `switch`. With the current `rand() % 4 + 1` this cannot happen, so to see it, temporarily change that line to `rand() % 5 + 1` and run until a 5 comes up. (The last line is printed by the IDE, not the program.)

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V3) {*}

[ ASCII-art banner and wizard jokes: shown in full in Test 1 ]

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
bray


Ah... bray! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.

Invalid question type: 5
Program ended with an error -1
Please report this error to Brayden Tolle or Joe Bracht

Process finished with exit code -1
```

</details>

[Back to the test list](#console-output-testing)


## Previous Versions (V1 and V2 Outputs)

These are the console outputs from earlier versions of the program, kept as they were. The text and layout are different from the current boxed display, so they are kept here for history. Click any entry to open it.

| Version | Output (click to jump) | What it shows |
|---|---|---|
| V1 | [Right answer](#v1-right-answer) | The first version asked a single question and said goodbye |
| V1 | [Wrong answer](#v1-wrong-answer) | A wrong answer ended the question with the correct answer and "Please try again" |
| V1 | [Invalid question type](#v1-invalid-question-type) | The early error path |
| V2 | [Status lines and leveling snippets](#v2-status-lines-and-leveling-snippets) | Version 2 added the question, level, and attempts text (before the boxes), the replay prompt, and leveling |
| V2 | [Full session](#v2-full-session) | A complete V2 run: a retry, a level up to level 2, three misses that level the user down, and the goodbye |
| V2 | [Invalid input](#v2-invalid-input) | The user types a letter instead of a number |
| V2 | [Invalid question type](#v2-invalid-question-type) | The error path with both maintainers named |
| V3 early build | [Real session from CLion](#v3-early-build-real-session-from-clion) | A run from the V3 build before the level-down rule changed |

### V1 Right answer

The first version asked a single question and said goodbye. The banner in these early runs says (V1).

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V1) {*}

,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`



(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

A wise wizards words:
        (*) What's a wizard's favorite school subject? spell-gebra!
        (*) Why did the sorcerer break his calculator? He wanted to do math-a-magics in his head!
        (*) What is a witch's favorite shape? A Hex-agon!
        (*) What do you call a snake that is 3.14 feet long? A Pi-thon!

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
Brayden Tolle


Ah... Brayden Tolle! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.
Brayden Tolle what is 4-4?
0

Good job! You Got The Question Right!

This is all for our program! I hope you had a fantastic time!!
```

</details>

[Back to the previous versions list](#previous-versions-v1-and-v2-outputs)

### V1 Wrong answer

A wrong answer ended the question with the correct answer and "Please try again".

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V1) {*}

,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`



(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

A wise wizards words:
        (*) What's a wizard's favorite school subject? spell-gebra!
        (*) Why did the sorcerer break his calculator? He wanted to do math-a-magics in his head!
        (*) What is a witch's favorite shape? A Hex-agon!
        (*) What do you call a snake that is 3.14 feet long? A Pi-thon!

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
 Brayden Tolle


Ah...  Brayden Tolle! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.
 Brayden Tolle what is 4+8?
2

I'm So Disappointed In You Apprentice...
The correct answer was 12.

Please try again, Apprentice!
```

</details>

[Back to the previous versions list](#previous-versions-v1-and-v2-outputs)

### V1 Invalid question type

The early error path. The message only named one maintainer at this point.

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V1) {*}

,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`



(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

A wise wizards words:
        (*) What's a wizard's favorite school subject? spell-gebra!
        (*) Why did the sorcerer break his calculator? He wanted to do math-a-magics in his head!
        (*) What is a witch's favorite shape? A Hex-agon!
        (*) What do you call a snake that is 3.14 feet long? A Pi-thon!

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
 lashanan werth


Ah...  lashanan werth! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.
Invalid question type: 5
Program ended with an error -1
Please report this error to Brayden Tolle

Process finished with exit code -1
```

</details>

[Back to the previous versions list](#previous-versions-v1-and-v2-outputs)

### V2 Status lines and leveling snippets

Version 2 added the question, level, and attempts text (before the boxes), the replay prompt, and leveling. These are the short snippets from the original README, including the level up and level down messages.

<details>
<summary><b>Click to view the console output</b></summary>

```text
// Displaying Level, Question, and attempts left.

Ah... Brayden! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.
You're on question 1
out of level 1
and on 1 out of 3 attempts
Brayden what is 10-5?

// Answer right then do you want a other question
Ah... Brayden! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.
You're on question 1
out of level 1
and on 1 out of 3 attempts
Brayden what is 10-5?
5

Good job! You Got The Question Right!
Would you like a other question Apprentice? (y=yes/n=no

//if yes it will move onto a new question.
Would you like a other question Apprentice? (y=yes/n=no
y

You're on question 2
out of level 1
and on 1 out of 3 attempts
Brayden what is 9+2?


// Answer wrong then updates attempts then asks the question to you get it right
You're on question 2
out of level 1
and on 1 out of 3 attempts
Brayden what is 9+2?
 1

Not quite, apprentice!
You have 2 attempets left
You're on question 2
out of level 1
and on 2 out of 3 attempts
Brayden what is 9+2?

// Leveling up

Good job! You Got The Question Right!
You have leveled up to level 2!
Numbers will now go up to 20.
Would you like a other question Apprentice? (y=yes/n=no

// Leveling down, Then states the correct answer. Then moves down by 10.

Good job! You Got The Question Right!
You have leveled up to level 2!
Numbers will now go up to 20.
Would you like a other question Apprentice? (y=yes/n=no
y

You're on question 4
out of level 2
and on 1 out of 3 attempts
Brayden what is 280/14?
2

Not quite, apprentice!
You have 2 attempets left
You're on question 4
out of level 2
and on 2 out of 3 attempts
Brayden what is 280/14?
2

Not quite, apprentice!
You have 1 attempets left
You're on question 4
out of level 2
and on 3 out of 3 attempts
Brayden what is 280/14?
2

I'm So Disappointed In You Apprentice...
The correct answer was 20.
You have leveled down to 1!
Number will go down by 10!
The correct answer was 20.
Would you like a other question Apprentice? (y=yes/n=no
```

</details>

[Back to the previous versions list](#previous-versions-v1-and-v2-outputs)

### V2 Full session

A complete V2 run: a retry, a level up to level 2, three misses that level the user down, and the goodbye.

<details>
<summary><b>Click to view the console output</b></summary>

```text
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V1) {*}

,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`



(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

A wise wizards words:
        (*) What's a wizard's favorite school subject? spell-gebra!
        (*) Why did the sorcerer break his calculator? He wanted to do math-a-magics in his head!
        (*) What is a witch's favorite shape? A Hex-agon!
        (*) What do you call a snake that is 3.14 feet long? A Pi-thon!

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
Brayden


Ah... Brayden! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.
You're on question 1
out of level 1
and on 1 out of 3 attempts
Brayden what is 10-5?
5

Good job! You Got The Question Right!
Would you like a other question Apprentice? (y=yes/n=no
y

You're on question 2
out of level 1
and on 1 out of 3 attempts
Brayden what is 9+2?
 1

Not quite, apprentice!
You have 2 attempets left
You're on question 2
out of level 1
and on 2 out of 3 attempts
Brayden what is 9+2?
11]

Good job! You Got The Question Right!
Would you like a other question Apprentice? (y=yes/n=no
y

You're on question 3
out of level 1
and on 1 out of 3 attempts
Brayden what is 24/3?
6

Not quite, apprentice!
You have 2 attempets left
You're on question 3
out of level 1
and on 2 out of 3 attempts
Brayden what is 24/3?
12

Not quite, apprentice!
You have 1 attempets left
You're on question 3
out of level 1
and on 3 out of 3 attempts
Brayden what is 24/3?
8

Good job! You Got The Question Right!
You have leveled up to level 2!
Numbers will now go up to 20.
Would you like a other question Apprentice? (y=yes/n=no
y

You're on question 4
out of level 2
and on 1 out of 3 attempts
Brayden what is 280/14?
2

Not quite, apprentice!
You have 2 attempets left
You're on question 4
out of level 2
and on 2 out of 3 attempts
Brayden what is 280/14?
2

Not quite, apprentice!
You have 1 attempets left
You're on question 4
out of level 2
and on 3 out of 3 attempts
Brayden what is 280/14?
2

I'm So Disappointed In You Apprentice...
The correct answer was 20.
You have leveled down to 1!
Number will go down by 10!
The correct answer was 20.
Would you like a other question Apprentice? (y=yes/n=no
no

Thank you this is all for now!
```

</details>

[Back to the previous versions list](#previous-versions-v1-and-v2-outputs)

### V2 Invalid input

The user types a letter instead of a number.

<details>
<summary><b>Click to view the console output</b></summary>

```text
Ah... Brayden! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.
You're on question 1
out of level 1
and on 1 out of 3 attempts
Brayden what is 1+1?
w

Invalid answer apprentice!
Please enter a number (like 1,2,3), Apprentice!
Brayden what is 1+1?
Process finished with exit code 0
```

</details>

[Back to the previous versions list](#previous-versions-v1-and-v2-outputs)

### V2 Invalid question type

The error path with both maintainers named.

<details>
<summary><b>Click to view the console output</b></summary>

```text
    {*} Welcome to the tower of the wizard of magical math tutoring! (V1) {*}

,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`



(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

A wise wizards words:
        (*) What's a wizard's favorite school subject? spell-gebra!
        (*) Why did the sorcerer break his calculator? He wanted to do math-a-magics in his head!
        (*) What is a witch's favorite shape? A Hex-agon!
        (*) What do you call a snake that is 3.14 feet long? A Pi-thon!

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
w


Ah... w! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.
Invalid question type: 5
Program ended with an error -1
Please report this error to Brayden Tolle or Joe Bracht

Process finished with exit code -1
```

</details>

[Back to the previous versions list](#previous-versions-v1-and-v2-outputs)

### V3 early build Real session from CLion

A run from the V3 build before the level-down rule changed. At that time it took 3 failed questions to level down, so the miss at the end did not drop the level. The first line is the path of the built program. (It was stopped at the replay prompt.)

<details>
<summary><b>Click to view the console output</b></summary>

```text
C:\Users\trsdo\CLionProjects\MathTutorV3_\cmake-build-debug\MathTutorV3_.exe
(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

                       {*} Welcome to the tower of the wizard of magical math tutoring! (V3) {*}

,---.    ,---.   ____   ,---------. .---.  .---.    .--.      .--..-./`)  ____..--'   ____    .-------.     ______
|    \  /    | .'  __ `.\          \|   |  |_ _|    |  |_     |  |\ .-.')|        | .'  __ `. |  _ _   \   |    _ `''.
|  ,  \/  ,  |/   '  \  \`--.  ,---'|   |  ( ' )    | _( )_   |  |/ `-' \|   .-'  '/   '  \  \| ( ' )  |   | _ | ) _  \
|  |\_   /|  ||___|  /  |   |   \   |   '-(_{;}_)   |(_ o _)  |  | `-'`"`|.-'.'   /|___|  /  ||(_ o _) /   |( ''_'  ) |
|  _( )_/ |  |   _.-`   |   :_ _:   |      (_,_)    | (_,_) \ |  | .---.    /   _/    _.-`   || (_,_).' __ | . (_) `. |
| (_ o _) |  |.'   _    |   (_I_)   | _ _--.   |    |  |/    \|  | |   |  .'._( )_ .'   _    ||  |\ \  |  ||(_    ._) '
|  (_,_)  |  ||  _( )_  |  (_(=)_)  |( ' ) |   |    |  '  /\  `  | |   |.'  (_'o._)|  _( )_  ||  | \ `'   /|  (_.\.' /
|  |      |  |\ (_ o _) /   (_I_)   (_{;}_)|   |    |    /  \    | |   ||    (_,_)|\ (_ o _) /|  |  \    / |       .'
'--'      '--' '.(_,_).'    '---'   '(_,_) '---'    `---'    `---` '---'|_________| '.(_,_).' ''-'   `'-'  '-----'`



(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

A wise wizards words:
        (*) What's a wizard's favorite school subject? spell-gebra!
        (*) Why did the sorcerer break his calculator? He wanted to do math-a-magics in his head!
        (*) What is a witch's favorite shape? A Hex-agon!
        (*) What do you call a snake that is 3.14 feet long? A Pi-thon!

(*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*](*)[*]{*}[*]

What is your name young apprentice?
bray


Ah... bray! So you have finally found me. If you truly seek the knowledge hidden within these ancient halls,
 you must first prove your mind is sharp.

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 10*8?

80

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
y

 |----------------------------------|
 | Question: 2                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 10+1?

11

Good job! You Got The Question Right!

Would you like a other question Apprentice? (y=yes/n=no
y

 |----------------------------------|
 | Question: 3                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 45/5?

5

Not quite, apprentice!

 |----------------------------------|
 | Question: 3                      |
 | Attempts: 2 out of 3             |
 | MathLevel: 1                     |
 |----------------------------------|

bray, what is 45/5?

9

Good job! You Got The Question Right!

You have Advanced to the next level
 |----------------------------------|
 | NumUp: 20                        |
 | LevelUp: 2                       |
 |----------------------------------|

Would you like a other question Apprentice? (y=yes/n=no
y

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 1 out of 3             |
 | MathLevel: 2                     |
 |----------------------------------|

bray, what is 16+6?

2

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 2 out of 3             |
 | MathLevel: 2                     |
 |----------------------------------|

bray, what is 16+6?

2

Not quite, apprentice!

 |----------------------------------|
 | Question: 1                      |
 | Attempts: 3 out of 3             |
 | MathLevel: 2                     |
 |----------------------------------|

bray, what is 16+6?

2

I'm So Disappointed In You Apprentice...
You should've gotten that right...
 |----------------------------------|
 | CorrectAnswer: 22                |
 |----------------------------------|

Would you like a other question Apprentice? (y=yes/n=no
```

</details>

[Back to the previous versions list](#previous-versions-v1-and-v2-outputs)


## Code Tour

Everything lives in a single `main()` function. The constants and variables are declared at the top of `main`, followed by the program logic. The `MathType` enum is declared inside the question loop.

| Section | What it does |
|---|---|
| **Constants** | `MAX_ATTEMPTS = 3` and `LEVEL_RANGE = 10` |
| **Variables** | Every variable used by the program (the `MathType` enum is declared in the question loop) |
| **Setup** | Seeds `rand()` with `time(0)` before anything else |
| **Intro** | Prints the banner and jokes, then reads the user's name with `getline` |
| **Outer `do/while`** | One pass per question; repeats while the user answers `y` or `yes` |
| **Random question** | `rand() % 4 + 1` picks the operation; `rand() % LevelRange + 1` picks each number |
| **`switch`** | Computes the correct answer and picks the operator symbol; the `default` case is a safety net that exits with error `-1` |
| **Attempt `for` loop** | Up to 3 tries; draws the status box, validates input with `while (!(cin >> userAnswer))`, and checks the answer. `totalIncorrect` goes up only when attempts run out |
| **Level logic** | `totalCorrect` and `totalIncorrect` decide whether to level up or down |
| **Replay prompt** | Inner `while (true)` loop lowercases the input with `tolower` until it's `y`, `yes`, `n`, or `no` |

`<iomanip>` (`setw`) keeps the right edge of the status boxes lined up.

## Concepts Used

- `do/while`, `while`, and `for` loops (nested)
- `enum` with `static_cast` from a random integer
- `switch` statements with a `default` error path
- Input validation using `cin.clear()` and `cin.ignore(numeric_limits<streamsize>::max(), '\n')`
- Constants vs. variables (`const int` settings and a mutable `LevelRange`)
- Pseudo-random numbers with `srand`/`rand` and the modulo operator
- Output formatting with `setw` and `left`
- Raw string literals (`R"( ... )"`) for the ASCII art

## Known Quirks & Roadmap

- [ ] **Wording.** The replay prompt reads "a other" and is missing its closing `)`, and the level-down message says "Advanced down a level".
- [ ] **Variables.** The `MathType` enum and the loop counters (`attempt` in the `for`, `i` in the lowercase loop) are declared inside the code instead of at the top of `main`. The `for` loop's `attempt` also hides the outer `attempt`.
- [ ] **Stray backslash.** One line ends in a `\` (after the `correctAns` comment). It compiles but should be removed.
- [ ] **Header.** `<ctype.h>` would be `<cctype>` in C++.
- [ ] **Decimal answers.** The answer is read as a `double` and compared with `==`. That is fine for whole-number answers but would need care if questions ever had decimals.
- [ ] **Unreachable default.** The `default` case in the `switch` can't trigger while the range is `rand() % 4 + 1`. It is there as a safety net.
- [ ] **Ideas.** Track a final score, set a maximum level, add difficulty modes, and move question generation into its own function.

## Maintainers

| Name | GitHub |
|---|---|
| Brayden Tolle | [@Insanedoomed](https://github.com/Insanedoomed) |
| Joe Bracht | [@JoeBracht](https://github.com/JoeBracht) |

Found a bug? Please report it to either maintainer.

<div align="center">

*Thanks for playing, apprentice!* ✨

[Back to Top](#-mathtutorv3)

</div>

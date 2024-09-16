/************************************************************/
/*  Name:Nikola Rabljenovic/Aditya Bhati   Date: 27/11/2023 */
/*  Seat:  00    File:  SDP                                 */
/*  Instructor: K.Kecskemety 08:00am                        */
/************************************************************/
#include "FEHUtility.h"
#include "FEHLCD.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <FEHRandom.h>
#include <FEHImages.h>
using namespace std;

//constants
#define TRUE 1
#define FALSE 0

//Function prototypes
void viewCredits();
void viewHowToPlay();
int pauseMenu(int);
void createTargetsFirstLevel();
void drawCannon();
void drawPauseButton();
int displayTime(int);
void drawBackGround();
void drawOptionScreen(int t);
int viewLeaderBoard(int a, int b);

//Class
class Player
{   //Private members
    private:
        int highScore = 0;
        int highID = 0;
        int totalScore = 0;
        int id = 0;
        int test;
        int test2 = FALSE;
        float startTime = 0;
        int rate = 0;
    //Public members
    public:
        void playGame();
        int IDGenerator();
        void firstLevel();
        int pauseButtonPress(int x, int y);
        void drawID();
        void displayScore();
        int getRate();
        void getHighScore();
        void viewLeaderBoard();
};

//Class for menu
class menu
{   //Private members

    private:
        //Variable declarations
        char title[30] = "Gig 'em  Buckeye!";
        char play[10] = "Play!";
        char tutorial[15] = "How to play";
        char leaderboard[15] = "Leaderboard";
        char credits[15] = "Credits";
    //Public members
    public:
        void drawMainMenu();
        void drawMenuOptions();
};

//Main class
int main() {
  //Instance of menu
  menu play;
  int x, y;

 do {
    //Main Menu
    LCD.Clear();

    //Calls functions to draw menu
    play.drawMainMenu();
    play.drawMenuOptions();

    //Instance of player
    Player p1;

    //Main Menu navigation
    while (!LCD.Touch(&x, &y)) {}
        //loop that starts when a touch is detected
        while(LCD.Touch(&x, &y)) {
            if (((60.0 < x)&&(x< 160.0) && (45.0 < y) && (y< 75.0))) {
                //Option to play game
                LCD.SetBackgroundColor(TAN);
                Sleep(100);
                p1.playGame();
                p1.viewLeaderBoard();
            }
            else if (((60.0 < x) && (x < 210.0)) && ((80.0 < y) && (y < 110.0))) {
                //Option to see instructions
                Sleep(100);
                viewHowToPlay();
            }
            else if (((60.0 < x) && (x < 210.0)) && ((115.0 < y) && (y < 145.0))) {
                //Option to see leaderboard
                Sleep(100);
                p1.viewLeaderBoard();
            }
            else if (((60.0 < x) && (x < 210.0)) && ((150.0 < y) && (y < 180.0))) {
                //Option to view the credits
                Sleep(100);
                viewCredits();
}
            LCD.ClearBuffer();
        }
} while(1);

while (1) {
        LCD.Update();
} return 0;
}
//Function definition for play game
void Player::playGame()
{
    //Variable declarations
    int test = 1;
    float x_pos, y_pos;
    //Clears previous screen
    LCD.Clear();
    drawBackGround();
    //generates a random number
    IDGenerator();
    //Draws pause at the top left corner
    drawPauseButton();
    drawCannon();
   //Loop that runs until the first level function is over
    while(test == TRUE)
    {
        firstLevel();
        test = FALSE;
    }
}
//Function that randomly generates a user id
int Player::IDGenerator()
{
    //Gnerates a number number and returns it
    id = Random.RandInt();
    return id;
}
//Function definition for tutorial
void viewHowToPlay()
{
    //Declares local variables
    int test = 1;
    float x_pos, y_pos;
    //Clears previous screen
    LCD.Clear();
    //Present Backgorund
    FEHImage background;
    background.Open("PlayGamebackgroundFEH.pic");
    background.Draw(0, 0);
    background.Close();
    //Displays the tutorial
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Tutorial", 50, 20);
    LCD.WriteAt("1.) Use your mouse to aim", 10, 50);
    LCD.WriteAt("2.) Click to fire", 10, 85);
    LCD.WriteAt("3.) Repeat until you are", 10, 120);

    LCD.WriteAt("done, you have 30",10,155);
    LCD.WriteAt("seconds ", 10,185);
    while(test == TRUE)
    {
        //Displays return button
        LCD.SetFontColor(ORANGE);
        LCD.FillRectangle(60, 200, 100, 30);
        LCD.SetFontColor(WHITE);
        LCD.WriteAt("Return", 65, 205 );
        //If the user clicks the return
        if(LCD.Touch(&x_pos, &y_pos )== true)
        {
            Sleep(100);
            if(((60.0 < x_pos) && (x_pos < 160.0)) && ((200.0 < y_pos) && (y_pos <
230.0)))
{
                test = FALSE;
            }
} }
}
//Function definition for the leaderboard/Statistics
void Player::viewLeaderBoard()
{   //local variables
    int test = 1;
    float x_pos, y_pos;
    //Clears previous screen
    LCD.Clear();
    while(test == TRUE)
    {
    LCD.Clear();
    //Draws return button in the top left corner
    LCD.SetFontColor(ORANGE);
    LCD.FillRectangle(0,0,110,30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Return", 5, 5);
    //Draws leaderboard
    LCD.WriteAt("Player ID", 20, 50);
    LCD.WriteAt("High Score:", 5, 80 );
    LCD.WriteAt("Previous:", 5, 140 );
    LCD.WriteAt("Player score", 150, 50);
    LCD.DrawVerticalLine(140, 10, 210);
    LCD.Update();
    getHighScore();
    LCD.WriteAt(highScore, 150, 100);
    LCD.WriteAt(totalScore, 150, 160);
    LCD.WriteAt(highID, 5, 100);
    LCD.WriteAt(id, 5, 160);
    //If the return button is selected
    if(LCD.Touch(&x_pos, &y_pos)==true)

        {
        Sleep(100);
        if(((0 < x_pos) && (x_pos < 110.0)) && ((0 < y_pos) && (y_pos < 30.0)))
            {
            test = FALSE;
            }
} }
}
//Function definition
void viewCredits()
{
    //Clears previous screen
    LCD.Clear();
    /* Setting background image */
    FEHImage background;
    background.Open("PlayGamebackgroundFEH.pic");
    background.Draw(0, 0);
    background.Close();
    //Declaration of local variables
    char creditBox[30] = "Created by Aditya Bhati";
    char creditBox2[30] = "and Nikola Rabljenovic";
    float x_pos,y_pos;
    int test = TRUE;
    //Draws credits screen
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Credits Page", 50, 20);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt(creditBox, 20, 50 );
    LCD.WriteAt(creditBox2, 20, 65 );
    LCD.SetFontColor(ORANGE);
    LCD.FillRectangle(60, 150, 100, 30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Return", 65, 155 );
    while(test == TRUE){
        //Returns to main menu if true
        if(LCD.Touch(&x_pos, &y_pos) == true)
        {
            Sleep(1000);
            if(((60.0 < x_pos) && (x_pos < 160.0)) && ((150.0 < y_pos) && (y_pos <
180.0)))
{
                test = FALSE;
            }
} }
}
void Player::firstLevel() {

//Local variables
int stillTargets = 200;
int x, y;
float x1 = 160, y1 = 206;
float timeDiff = 0;
float slope = 0;
int rateReturn = 0;
//member variable
test = TRUE;
//Draws the screen
displayScore();
createTargetsFirstLevel();
//Starts a timer
startTime = TimeNow();
//While loop that checks if pause has been clicked or if the time is up
while((timeDiff < 30) && (test == TRUE)) {
    while (!LCD.Touch(&x, &y)) {}
    while(timeDiff < 30)
    {
        //Constantly displays time
        timeDiff = displayTime(startTime);
        while ((LCD.Touch(&x, &y)) && (test == TRUE)) {
is incremented
decremented
while (((y1 - 20) >= y) && (test == TRUE)) {
    //bullet origin(circle)
    LCD.SetFontColor(BLACK);
    LCD.FillCircle(x1, y1, 10);
    //Compute slope, which is used to "shoot" a cannon
    slope = (float)(y - y1)/(x - x1);
    //Makes bullet go to target
    LCD.SetFontColor(ORANGE);
    LCD.FillCircle(x1, y1, 10);
    //Changes color of bullet
    LCD.SetFontColor(BLACK);
    //If the click is to the right of the cannon, the x component
if (x > 160)
{
x1++;
y1 += slope; }
    //If the click is to the left of the cannon, the x component is
    else if (x < 160)
    {
x1--;
y1 -= slope; }
    //
    LCD.FillCircle(x1, y1, 10);
    LCD.Update();
}
//Clears the entire screen , then redraws the screen
LCD.Clear();
x1 = 160;
y1 = 206;

drawBackGround();
displayTime(startTime);
drawPauseButton();
drawID();
drawCannon();
createTargetsFirstLevel();
LCD.SetFontColor(BLACK);
LCD.FillCircle(160, 206, 10);
//Checks if click is on target
if (((25 < x) && (x < 55)) && ((50 < y) && (y < 80))) {
    LCD.SetFontColor(TAN);
    LCD.DrawRectangle(25, 50, 30, 30);
    LCD.FillRectangle(25, 50, 30, 30);
    LCD.Update();
    //Updates the users score
    totalScore += stillTargets;
    //Draws box after a certain time
    rateReturn = getRate();
    Sleep(rateReturn);
    //Redraws the box
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(25, 50, 30, 30);
    LCD.FillRectangle(25, 50, 30, 30);
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(30, 55, 20, 20);
    LCD.FillRectangle(30, 55, 20, 20);
    LCD.SetFontColor(BLUE);
    LCD.DrawRectangle(35, 60, 10, 10);
    LCD.FillRectangle(35, 60, 10, 10);
    LCD.Update();
    //Tests input to see if pause was pressed
    test = pauseButtonPress(x, y);
}
if (((125 < x) && (x < 155)) && ((50 < y) && (y < 80))) {
    //Draws over box
    LCD.SetFontColor(TAN);
    LCD.DrawRectangle(125, 50, 30, 30);
    LCD.FillRectangle(125, 50, 30, 30);
    LCD.Update();
    //updates users score
    totalScore += stillTargets;
    //Redraws after a certain time, which is generated by function
    rateReturn = getRate();
    Sleep(rateReturn);
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(125, 50, 30, 30);
    LCD.FillRectangle(125, 50, 30, 30);
LCD.SetFontColor(RED);

                LCD.DrawRectangle(130, 55, 20, 20);
                LCD.FillRectangle(130, 55, 20, 20);
                LCD.SetFontColor(BLUE);
                LCD.DrawRectangle(135, 60, 10, 10);
                LCD.FillRectangle(135, 60, 10, 10);
                LCD.Update();
            }
            if (((225 < x) && (x < 255)) && ((50 < y) && (y < 80))) {
                LCD.SetFontColor(TAN);
                LCD.DrawRectangle(225, 50, 30, 30);
                LCD.FillRectangle(225, 50, 30, 30);
                LCD.Update();
                //Updates user scores
                totalScore += stillTargets;
                //Updates screen after a certain time
                rateReturn = getRate();
                Sleep(rateReturn);
                LCD.SetFontColor(WHITE);
                LCD.DrawRectangle(225, 50, 30, 30);
                LCD.FillRectangle(225, 50, 30, 30);
                LCD.SetFontColor(RED);
                LCD.DrawRectangle(230, 55, 20, 20);
                LCD.FillRectangle(230, 55, 20, 20);
                LCD.SetFontColor(BLUE);
                LCD.DrawRectangle(235, 60, 10, 10);
                LCD.FillRectangle(235, 60, 10, 10);
                LCD.Update();
            }
            LCD.ClearBuffer();
            LCD.Update();
            //Displays the score using a function call
            displayScore();
} }
}
//After game conclusion,
drawOptionScreen(totalScore);
//
while (!LCD.Touch(&x, &y)) {}
while (LCD.Touch(&x, &y))
{
   if(((x > 60) && (x < 150)) && ((y > 115) && (y < 145)))
   {
        LCD.ClearBuffer();
        test = FALSE;
   }
   if(((x > 60) && (x < 150)) && ((y > 155) && (y < 185)))
   {
        LCD.ClearBuffer();
test2 = TRUE;
        test = FALSE;
   }

} }
void Player::getHighScore() {
    highScore = 3800;
    highID = 13459;
}
//Function that draws a pause button when its called
void drawPauseButton()
{
        //Draws pause button in the top left corner
        LCD.SetFontColor(WHITE);
        LCD.FillRectangle(0, 0, 10, 10);
        LCD.SetFontColor(RED);
        LCD.DrawVerticalLine(4, 2, 8);
        LCD.DrawVerticalLine(6, 2,8);
        LCD.Update();
}
//Function that returns a value if pause button area is called
int Player::pauseButtonPress(int x, int y)
{
    int x_pos=x;
    int y_pos=y;
    //If pause button is pressed
    if(((0 < x_pos) && (x_pos < 10)) && ((0 < y_pos)&&(y_pos < 10)))
        {
            test = FALSE;
        }
    return test;
}
//Displays time in the bottom left
int displayTime(int t)
{   //local variables
    float startTime = t, timeDiff;
    //Creates a black rectangle with time
    LCD.SetFontColor(BLACK);
    LCD.FillRectangle(245, 190, 75, 30);
    LCD.SetFontColor(WHITE);
    timeDiff = TimeNow() - startTime;
    LCD.WriteAt(timeDiff, 245, 195);
    LCD.Update();
    //returns a value for the difference in time
    return timeDiff;
}
//Function that draws a cannon
void drawCannon()
{
    //Uses MATLAB to convert an image
    FEHImage canon;
    canon.Open("cannonFEH.pic");
    canon.Draw(144, 216);
    canon.Close();
}
//Draws menu
void menu::drawMainMenu()
{
    LCD.Clear();

    /* Setting background image */
    FEHImage background;
    background.Open("backgroundFEH.pic");
    background.Draw(0, 0);
    background.Close();
    drawMenuOptions();
}
//After game concludes, this function is called
//Takes in the score as a parameter so it can be displayed
void drawOptionScreen(int t)
{
    int totalScore = t;
    //Clears screen
    LCD.Clear();
    /* Setting background image */
    FEHImage background;
    background.Open("backgroundFEH.pic");
    background.Draw(0, 0);
    background.Close();
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("BE SAFE WITH GUNS", 50, 10);
    LCD.WriteAt("Round Over", 50, 50);
    //Gives users options
    LCD.FillRectangle(60, 115, 150, 30);
    LCD.FillRectangle(60, 150, 150, 30);
    LCD.SetFontColor(ORANGE);
    LCD.WriteAt("Leaderboard", 65, 120);
    LCD.WriteAt("Score:", 65, 155);
    LCD.WriteAt(totalScore, 160, 155);
}
//Displays the players ID
void Player::drawID()
{
    LCD.SetFontColor(WHITE);
    LCD.WriteAt(id, 0, 220);
}
//Draws the main menu
void menu::drawMenuOptions()
{
    //Uses LCD functions to draw menu
    LCD.SetFontColor(BROWN);
    LCD.WriteAt(title, 50, 20);
    LCD.SetFontColor(ORANGE);
    LCD.DrawRectangle(60, 45, 100, 30);
    LCD.FillRectangle(60, 45, 100, 30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt(play, 65, 50);
    LCD.SetFontColor(ORANGE);
    LCD.DrawRectangle(60, 80, 150, 30);
    LCD.FillRectangle(60, 80, 150, 30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt(tutorial, 65, 85);
LCD.SetFontColor(ORANGE);

    LCD.DrawRectangle(60, 115, 150, 30);
    LCD.FillRectangle(60, 115, 150, 30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt(leaderboard, 65, 120);
    LCD.SetFontColor(ORANGE);
    LCD.DrawRectangle(60, 150, 150, 30);
    LCD.FillRectangle(60, 150, 150, 30);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt(credits, 65, 155);
}
//displays score
void Player::displayScore()
{
    //Uses member funciton of Player class and displays that at the top right
corner
    LCD.SetFontColor(WHITE);
    LCD.WriteAt(totalScore, 240, 0);
}
//Function that draws image from web
void drawBackGround()
{
    /* Setting background image */
    FEHImage background;
    background.Open("backgroundFEH.pic");
    background.Draw(0, 0);
    background.Close();
}
//generates a random value to change player's ability to achieve a higher score
int Player::getRate()
{
    int localTest = TRUE;
    //Endless loop to see if the value is within the set bounds
    while(localTest == TRUE)
    {
        //generates the number and checks if its within bounds
        rate = Random.RandInt();
        if((rate > 500) && (rate < 2000))
        {
            //returns a value if the conditions are true
            return rate;
            localTest = FALSE;
} }
}
//Creates targets for the game
void createTargetsFirstLevel()
{
    // Creating first target for first level
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(25, 50, 30, 30);
    LCD.FillRectangle(25, 50, 30, 30);
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(30, 55, 20, 20);
    LCD.FillRectangle(30, 55, 20, 20);
    LCD.SetFontColor(BLUE);
    LCD.DrawRectangle(35, 60, 10, 10);

LCD.FillRectangle(35, 60, 10, 10);
    // Creating second target for first level
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(125, 50, 30, 30);
    LCD.FillRectangle(125, 50, 30, 30);
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(130, 55, 20, 20);
    LCD.FillRectangle(130, 55, 20, 20);
    LCD.SetFontColor(BLUE);
    LCD.DrawRectangle(135, 60, 10, 10);
    LCD.FillRectangle(135, 60, 10, 10);
    // Creating the third target for first level
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(225, 50, 30, 30);
    LCD.FillRectangle(225, 50, 30, 30);
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(230, 55, 20, 20);
    LCD.FillRectangle(230, 55, 20, 20);
    LCD.SetFontColor(BLUE);
    LCD.DrawRectangle(235, 60, 10, 10);
    LCD.FillRectangle(235, 60, 10, 10);
}

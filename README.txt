The led which is lit determines which game is active at which time, the game that is active can be changed by the press of a button.
The led nearest the lcd touch screen corresponds to the touch screen game. The led directly beside the lcd screen led corresponds to the orange,red, and green switch game.
the led directly to the right of the analog stick is corresponding to the analog stick game. The led farthest to the right is corresponding to the potentiometer game.
the potentiometer game is a frequency based game you will be given a frequency from one speaker and you will have to match the tone by turning your potentiometer.
when playing the game you will have to start on the switches then you will tell your teammate what the combination of switches are and they will have the information that will allow you to finish the rest of the games.
he will have a code that you will have to input on the lcd screen and a combination of up,down,left,or right to input on the analog stick. the speaker is not randomized it will be the same prequency everytime.
after completeing each game there will be a success sound and after completeing all 4 games a final victory sound will come and that is saying you win. Or after failing 3 times on the games a fail sound will play that c.learly means you failed.
as you power the game on the lcd screen will as for a difficulty or an amount of attempts. the manifesto to our game is the following all of the firsts are one game all the seconds are one game and all the 3rds are a game

const String Code[3] = {"666*420", "#3825968", "8675309*"};
const int switches[3][3] = {{LOW, LOW, HIGH},{LOW, HIGH, LOW}, {LOW, LOW, LOW}};
const String combo[3] = {"uuddlrlr", "uuddllrr", "ulrlludr"}; //note combo must be 8 digits
const int note[3] = {440, 587, 261};

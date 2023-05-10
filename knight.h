#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

const int MADBEAR = 1;
const int BANDIT = 2;
const int EVENT_SIZE = 100;
const int MAX_CHARACTER_EACH_LINE = 250;
const int maxDF = 20;
const int maxlv = 10;
const int maxgd = 500;
const float bDam[5] = {1,2.5,5.5,7.5,9.5};
const int rewd[5] = {10,20,30,40,50};

struct knight
{
   int HP;
   int DF;
   int level;
   int remedy;
   int gold;
   int phoenixdown;
};

// read data from input file to corresponding variables
// return 1 if successfully done, otherwise return 0
int levelO(int i){
	int b = i%10;
	return i>6? (b>5? b:5):b;
}
void winBot(knight& theKnight, int bot){
 	    theKnight.level++; theKnight.DF++; theKnight.gold += rewd[bot];
        if (theKnight.level > maxlv) theKnight.level = maxlv;
        if (theKnight.DF > maxDF) theKnight.DF = maxDF;
        if (theKnight.gold > maxgd) theKnight.gold = maxgd;
    return;
}
void loseBot(knight& theKnight, int index, int bot){

		int dam = bDam[bot]*levelO(index)*10;
		theKnight.HP -= dam;
		if (dam > theKnight.DF) theKnight.HP += theKnight.DF;
	return;
}
void winWitch(knight& theKnight){
		theKnight.level+=2; theKnight.DF+=2;
        if (theKnight.level > maxlv) theKnight.level = maxlv;
        if (theKnight.DF > maxDF) theKnight.DF = maxDF;
    return;
}
void noTiny(knight& theKnight, int maxHP, int& tiny){
	if (tiny > 0){
		theKnight.HP *= 5;
		if (theKnight.HP > maxHP) theKnight.HP = maxHP;	
		tiny = 0;
	}
}
void noFrog(knight& theKnight, int froglv, int& frog){
	if (frog > 0){
		theKnight.level = froglv;
		if (theKnight.level > maxlv) theKnight.level = maxlv;	
		frog = 0;
	}
}
int sumofDivs(int num){
	int s = 0;
	for (int i = 1; i <= num; i++){
		if (num%i == 0) s += i;
	}
	return s;
}
bool friendlynums(int x, int y){
	return (double(sumofDivs(x))/x == double(sumofDivs(y))/y);
}
string str(int i){
	string s;
	s = s + char(i%10 + '0');
	i /= 10;
	while (i >= 1){
		s = s + char(i%10 + '0');
		i /= 10;
	}
	int l = s.length(); 
	for (int j = 0; j<l/2; j++){
		char sw = s[j];
		s[j] = s[l-j-1];
		s[l-j-1] = sw;
	}
	return s;
}
bool prime(int hp){
	bool check = 1;
	for (int i = 2; i < hp/2; i++){
		if (hp%i == 0) {
			check = 0;
			break;
		}
	}
	return check;
}
bool Pythagore(int n){
	bool check = 0;
	for (int a = 1; a < n/2; a++){
		int b = (n*n - 2*a*n)/(2*(n - a));
		int c = n - a - b;
		if (a*a + b*b == c*c && c>0) {
			check = 1;
			//cout << a << b << c << endl; //Bug check
			break;
		}
	}
	return check;
}
int checkKnight(knight theKnight){
	if (theKnight.HP == 999) return 1; //Arthur
	else if (theKnight.HP == 888) return 2; //Lancelot
	else if (prime(theKnight.HP)) return 3; //Paladin
	else if (Pythagore(theKnight.HP)) return 4; //Dragon Knight
	else return 0; //Ordinary Knight
} 
int startJourney(knight theKnight, int nEvent, int *arrEvent){
	int maxHP = theKnight.HP, tiny, frog, froglv, myth, time = -1, Odin;
	bool success, die, exbur, expor, guine, checkOdin, drag;
	tiny = frog = froglv = myth = Odin = 0;
	success = die = exbur = expor = guine = checkOdin = drag = 0; 
	string pw;
 	int k = checkKnight(theKnight);
	for (int i = 0; i < nEvent; i++)
    {
        int theEvent = arrEvent[i];
        switch (theEvent){	
			case 0:	//Bowser surrender
        		success = 1;
        		break;
            case 1: case 2: case 3: case 4: case 5: 
                //deal with MadBear,Bandit,LordLupin,Elf,Troll 
                if (k == 1 || (k == 2 && theKnight.level%2 != 0) || k == 3 || drag || (exbur && tiny == 0 && frog == 0) || Odin > 0) 
					winBot(theKnight, theEvent-1);
                else {
                	if ((theKnight.level > levelO(i+1)) && !expor) winBot(theKnight, theEvent-1);
                	else if ((theKnight.level < levelO(i+1)) || expor)
						if (myth <= 2) loseBot(theKnight, i+1, theEvent-1);
            	}
                break;
			case 6:
				//deal with Shaman
				if (tiny == 0 && frog == 0){
					if (k == 1 || (k == 2 && theKnight.level%2 != 0) || k == 3 || drag || ((theKnight.level > levelO(i+1)) && !expor) || Odin > 0) 
						winWitch(theKnight);	
					else if ((theKnight.level < levelO(i+1)) || expor){
							theKnight.HP /= 5;
							if (theKnight.HP < 5) theKnight.HP = 1;
							tiny = 4;
					}
				}
				break;
			case 7:
				//deal with siren Vajsh
				if (tiny == 0 && frog == 0){
					if (k == 1 || (k == 2 && theKnight.level%2 != 0) || k == 3 || drag || ((theKnight.level > levelO(i+1)) && !expor) || Odin > 0) 
						winWitch(theKnight);	
					else if ((theKnight.level < levelO(i+1)) || expor){
							froglv = theKnight.level;
							theKnight.level = 1;
							frog = 4;
						}
				}
				break;
			case 8: //Excalibur
				exbur = 1;
				break;		
			case 9: //Mythril
				if(myth == 0) myth = 8;
				break;	
			case 10: //Excalipoor
				if (!(k == 1 || (k == 2 && theKnight.level%2 != 0) || k == 3 || k == 4)){
					if (theKnight.level < 5 && Odin == 0){
						expor = 1;
						exbur = 0;
					}
				}
				break;
			case 11: //mushMario
				theKnight.HP += 50;
				if (theKnight.HP > maxHP) theKnight.HP = maxHP;
				break;
			case 12:{ //mushFib
				int fibo[50] = {1,1};
				int i = 2;
				while (fibo[i - 1] < theKnight.HP){
					fibo[i] = fibo[i-1] + fibo[i-2];
					i++;
				}
				theKnight.HP += fibo[i-2];
				if (theKnight.HP > maxHP) theKnight.HP = maxHP;
				}
				break;
			case 13: //mushGhost
				if (Odin == 0 && k != 3 && !drag){
					if (theKnight.HP < 51) theKnight.HP = 1;
					else theKnight.HP -= 50;
					if (theKnight.DF < 6) theKnight.DF = 1; 
					else theKnight.DF -= 5;
				}
				break;
			case 14: //mushKnight
				maxHP += 50;
				if (maxHP > 999) maxHP = 999;
				theKnight.HP = maxHP;
				break;
			case 15: //remedy
				theKnight.remedy++;
				if (theKnight.remedy > 99) theKnight.remedy = 99;
				break;
			case 16: //phoenixdown
				theKnight.phoenixdown++;
				if (theKnight.phoenixdown > 99) theKnight.phoenixdown = 99;
				break;
			case 17: //Merlin
				noTiny(theKnight, maxHP, tiny);
				noFrog(theKnight, froglv, frog);
				theKnight.level++;
				if (theKnight.level > maxlv) theKnight.level = maxlv; 	
				theKnight.HP = maxHP;				
        		break;
        	case 18:{ //Nina de Rings
        		bool check = friendlynums(theKnight.HP,theKnight.gold);
        		if (theKnight.gold >= 50 || check){
        			if (!check && (tiny > 0 || frog > 0)) theKnight.gold -= 50;
					noTiny(theKnight, maxHP, tiny);
					noFrog(theKnight, froglv, frog);
					if (check) theKnight.HP = maxHP;        		
					else{
						theKnight.gold -= (maxHP - theKnight.HP);
						if (theKnight.gold < 0){ 
							theKnight.HP = maxHP + theKnight.gold;
							theKnight.gold = 0;
						}
						else theKnight.HP = maxHP;
					}
				}
			 }
				break;
			case 19: //Abyss
				if (theKnight.level < 7 && Odin == 0 && !drag){
					if (theKnight.gold >= 50) theKnight.gold -= 50;
					else {
						string code;
						pw = pw + str(theKnight.HP) + str(theKnight.DF) + str(theKnight.level) + str(theKnight.remedy) + str(theKnight.gold) + str(theKnight.phoenixdown);
						//cout << pw << endl;		//bug check
						int len = pw.length(), s = 0;
						for (int x = 0; x < len; x++){
							bool repeat = 0;
							for (int y = 0; y <len; y++){
								if (y != x && pw[x] == pw[y]){
									repeat = 1;
									break;
								} 
							}
							if (!repeat){
								code = code + pw[x];
							}
						}
						//cout << code << endl; //bug check
						int lc = code.length();
						for (int a = 0; a < lc; a++){
							s += (code[a] - '0');
						}
						//cout << s <<endl; 	//Bug check
						if (s <= 15) die = 1;
					}
				}
				break;
			case 20:	//Time gate
				time = i;
				break;
			case 21:	//Guinevere
				for (int j = 1; j <= i; j++){
					arrEvent[i+j] = arrEvent[i-j];
					//cout << arrEvent[i+j] << endl; //bugcheck
				}
				guine = 1; 
				nEvent = 2*i + 1;
				//for (int j = 0; j<nEvent; j++) cout << arrEvent[j] << endl; //Bug check
				break; 
			case 22:	//Lightwing
				for (int j = i; j <= i+3; j++){
					switch(arrEvent[j]){
						case 0: case 21: 
							success = 1;
							break;
					}
					if (success) break;
				} 	
				if (!success){
					i += 3;
				}
				break;
			case 23: 	//Odin
				if (!checkOdin){
					checkOdin = 1;
					Odin = 4; 
				} 
				break;
			case 24: 	//Dragon Sword
				if (k == 4) drag = 1;
				break;
			case 99: 	//Bowser
				if (Odin > 0) theKnight.level = 10;
				else {
					switch(k){
						case 1: case 2: 
							theKnight.level = 10;
							break;
						case 3: 
							if (theKnight.level >= 8) 
								theKnight.level = 10;
							else die = 1;
							break;
						case 0: case 4:
							if (drag) theKnight.level = 10;
							else if (theKnight.level < 10) die = 1;
							break;
					}
				}
				break; 
		}
        //Bug check
        //cout << i+1 <<" index," << theEvent << ": " << theKnight.HP <<" "<< theKnight.DF <<" "<< theKnight.level <<" "<< theKnight.remedy <<" "<< theKnight.gold <<" "<< theKnight.phoenixdown <<endl; //Check bug
		//Loop checking
        if (theKnight.HP <= 0){
			if (theKnight.phoenixdown == 0) {die = 1;}
			else {
				theKnight.HP = maxHP;
				theKnight.phoenixdown--;
				noTiny(theKnight, maxHP, tiny);
				noFrog(theKnight, froglv, frog);
				if (time >= 0) i = time;
				}
		}
		if (success || die || (i >= 99 && !guine)) break;
		if (theKnight.remedy > 0){
			if (frog > 0 || tiny > 0) theKnight.remedy--;
			noTiny(theKnight, maxHP, tiny);
			noFrog(theKnight, froglv, frog);
		}
		//Loop updating
		pw = pw + str(theEvent);
		if (tiny == 1) noTiny(theKnight, maxHP, tiny);
		if (frog == 1) noFrog(theKnight, froglv, frog);
		if (tiny > 0) tiny--;
		if (frog > 0) frog--;
		if (myth > 0) myth--;		
		if (Odin > 0) Odin--;
    }
	if (die) return -1;
    else 
    return (theKnight.HP + theKnight.DF + theKnight.level + theKnight.remedy + theKnight.gold + theKnight.phoenixdown);
}


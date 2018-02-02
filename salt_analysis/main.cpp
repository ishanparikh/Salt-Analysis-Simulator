//
//  main.cpp
//  salt_analysis
//
//  Created by Ishan Parikh on 19/04/17.
//  Copyright © 2017 Ishan Parikh. All rights reserved.
//

#include <iostream>

#include <stdio.h>
#include <fstream>

#include <iomanip>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>


using namespace std;


int a = 0;

char msg[300];
struct Chemical
{
    char reagVal[50];
    Chemical *link;
    
    /*
     Holds integer value correlating to const value for specific reagent
     */
};

void confirm(char out[])
{
    cout<<endl<<out;
}

class Salt
{
private:
    static int n_Anion;
    static int n_Cation;
    
public:
    
    static char CATION[12][20];
    static char ANION[11][10];
    
    static int GenerateRandomAnion();
    static int GenerateRandomCation();
    static char* getAnion(int);
    static char* getCation(int);
    
    /*
     1. Abstract class
     2. Stores all cation and anions
     */
};

char Salt::CATION[12][20] = {"Aluminium","Ammonium","Barium","Calcium","Copper","Ferric","Lead","Magnesium","Manganese","Nickel","Strontium","Zinc"};
char Salt::ANION[11][10] = {"Nitrate","Phosphate","Acetate","Bromide","Chloride","Sulphate","Oxalate","Carbonate","Iodide","Sulphide","Sulphite"};

char* Salt::getAnion(int ANIONS)
{
    return ANION[ANIONS];
}

char* Salt::getCation(int CATIONS)
{
    return CATION[CATIONS];
}

int Salt::GenerateRandomAnion()
{
    srand(time(NULL));
    return rand() % (n_Anion);
}

int Salt::GenerateRandomCation()
{
    srand(time(NULL));
    return rand() % (n_Cation);
}

int Salt::n_Cation = 12;
int Salt::n_Anion = 10;

class ReagentQueue : public Salt
{
private:
    char ctr[10];
    Chemical *rear;
    //Chemical *rev;
    Chemical *link;
    
public:
    int num;
    Chemical *front;
    Chemical *trav;
    
    ReagentQueue()
    {
        front = NULL;
        rear = NULL;
        trav = NULL;
        num = 0;
    }
    
    void add();
    Chemical* getFront();
    void add(char[][100], int);
    void del();
    void ClearQueue();
    char* traverse();
    void display(Chemical *a);
    /*
     1. Consists of general implementation of linked list queue with operations such as add, delete and traverse.
     2. It is used to hold a list of type 'Chemical' which serves as a list of reagents.
     */
};

Chemical* ReagentQueue::getFront()
{
    return front;
}

void input(Chemical *a)
{
    cout<<"Enter data (chemical formula or name [eg: Copper Turnings], as specified in manual): ";
    cin.ignore();
    cin.getline(a->reagVal, 50, '\n');
    cout<<'\n';
}

void ReagentQueue::add()
{
    Chemical *np = new Chemical();
    
    if(np==NULL)
    {
        cout<<"No memory";
        exit(0);
    }
    
    np->link=NULL;
    input(np);
    
    if(front==NULL)
    {
        front = np;
        rear = np;
        trav = np;
    }
    else
    {
        rear->link=np;
        rear=np;
    }
    
    cout << "Reagent has been added!";
    
    num++;
}

void ReagentQueue::add(char Reag[][100], int n = 1)
{
    for(int i = 0; i < n; i++)
    {
        Chemical *np = new Chemical();
        
        if(np==NULL)
        {
            cout<<"No memory";
            exit(0);
        }
        
        np->link=NULL;
        strcpy(np->reagVal, Reag[i]);
        
        if(front==NULL)
        {
            front=np;
            rear=np;
            trav = np;
        }
        
        else
        {
            rear->link=np;
            rear=np;
        }
        num++;
    }
}

void ReagentQueue::del()
{
    Chemical *temp = front;
    
    if(front == rear)
        front = rear = NULL;
    else
        front = front -> link;
    delete temp;
}

char* ReagentQueue::traverse()
{
    //Chemical*temp=front;
    
    
    trav=front;                             //EDIT
    
    trav = trav -> link;
    return trav -> reagVal;
}

void ReagentQueue::display(Chemical *a)
{
    cout<<a->reagVal<<" ";
}

void ReagentQueue::ClearQueue()
{
    while(front != NULL)
    {
        Chemical *temp = front;
        
        if(front == rear)
            front = rear = NULL;
        else
            front = front -> link;
        delete temp;
    }
}

int CompareReagent(ReagentQueue userQ, ReagentQueue testQ)//funtion to match the 2 reagent queues
{
    
    //int i = 0;
    int count  = 0;
    char* userQVal = NULL;
    char* testQVal = NULL;
    
    int flag = 0;
    
    if(userQ.num == testQ.num)
    {
        
        count = userQ.num;
        
        Chemical* np1 = NULL;
        Chemical* np2 = NULL;
        
        np1 = testQ.getFront();
        np2 = userQ.getFront();
        while(np1 != NULL)
        {
            (testQVal = np1 -> reagVal);
            (userQVal = np2 -> reagVal);
            
            if(strcmp(testQVal, userQVal) != 0)
            {
                flag = 1;
                break;
            }
            
            np1 = np1 -> link;
            np2 = np2 -> link;
        }
        
        if (flag == 1)
            return 0;
        
        else
            return 1;
    }
    else
        return 0;
}

class UserModel
{
public:
    ReagentQueue curr;
    int ANION, CATION;
    char observations[300][300];
    int a;
    
    UserModel()
    {
        generate();
        a = 0;
    }
    void generate();
    void addReagent();
    void viewQueue();
    void removeReagent();
    void displaySalt();
};

void UserModel::generate()
{
    ANION = Salt::GenerateRandomAnion();
    CATION = Salt::GenerateRandomCation();
}

void UserModel::addReagent()
{
    curr.add();
}

void UserModel::removeReagent()
{
    curr.del();
}

void UserModel::viewQueue()
{
    Chemical *np =  new Chemical();
    np = curr.getFront();
    while(np != NULL)
    {
        curr.display(np);
        np = np->link;
    }
}

void UserModel::displaySalt()
{
    //system("cls");
    cout<<"Salt:\nAnion: "<<Salt::getAnion(ANION)<<"\nCation: "<<Salt::getCation(CATION)<<'\n';
    //getch();
}



void prelims(UserModel &VirtUser)
{
    cout<<"Execute preliminary tests\n";
    if((VirtUser.CATION +  1)==5||(VirtUser.CATION +  1)==6||(VirtUser.CATION +  1)==9||(VirtUser.CATION +  1)==10)
    {
        if((VirtUser.CATION +  1)==5)
            strcpy(VirtUser.observations[VirtUser.a++],"Colour: Blue");
        
        else if((VirtUser.CATION +  1)==6)
            strcpy(VirtUser.observations[VirtUser.a++],"Colour: Brown");
        
        else if((VirtUser.CATION +  1)==9)
            strcpy(VirtUser.observations[VirtUser.a++],"Colour: Pink");
        
        else if((VirtUser.CATION +  1)==10)
            strcpy(VirtUser.observations[VirtUser.a++],"Colour: Green");
    }
    else
        strcpy(VirtUser.observations[VirtUser.a++],"Colourless");
    
    if((VirtUser.CATION +  1)==2||(VirtUser.ANION + 1) ==3||(VirtUser.ANION + 1) ==10)
    {
        if((VirtUser.CATION +  1)==2)
            strcpy(VirtUser.observations[VirtUser.a++],"Smell: Ammonical");
        
        else if((VirtUser.ANION + 1) ==3)
            strcpy(VirtUser.observations[VirtUser.a++],"Smell: Vinegar");
        
        else if((VirtUser.ANION + 1) ==10)
            strcpy(VirtUser.observations[VirtUser.a++],"Smell: Rotten Eggs");
    }
    else
        strcpy(VirtUser.observations[VirtUser.a++],"Odourless");
    
    
    if(!((VirtUser.CATION +  1)==7))
    {
        if(!((VirtUser.CATION +  1)==7))              //edit
        {
            strcpy(VirtUser.observations[VirtUser.a++],"Insoluble in Water");
            strcpy(VirtUser.observations[VirtUser.a++],"Insoluble in HCL");
        }
    }
    else
    {
        strcpy(VirtUser.observations[VirtUser.a++],"Soluble in Water");
        strcpy(VirtUser.observations[VirtUser.a++],"Soluble in HCl");
    }
    
   // if((VirtUser.CATION +  1)==7)
    
    
    
    if((VirtUser.CATION +  1)==3||(VirtUser.CATION +  1)==4||(VirtUser.CATION +  1)==5||(VirtUser.CATION +  1)==6||(VirtUser.CATION +  1)==11)
    {
        if((VirtUser.CATION +  1)==3)
            strcpy(VirtUser.observations[VirtUser.a++],"Apple Green Flame");
        
        else if((VirtUser.CATION +  1)==4)
            strcpy(VirtUser.observations[VirtUser.a++],"Brick Red Flame");
        
        else if((VirtUser.CATION +  1)==5)
            strcpy(VirtUser.observations[VirtUser.a++],"Blue Green Flame");
        
        else if((VirtUser.CATION +  1)==11)
            strcpy(VirtUser.observations[VirtUser.a++],"Crimson Red Flame");
    }
    else
        strcpy(VirtUser.observations[VirtUser.a++],"No Characteristic flame");
}


void DilAcid(UserModel &VirtUser)
{
    cout<<"Execute Dilute Acid Test\n";
    if((VirtUser.ANION + 1) ==6||(VirtUser.ANION + 1) ==8||(VirtUser.ANION + 1) ==10)
    {
        if((VirtUser.ANION + 1) ==6)
            strcpy(VirtUser.observations[VirtUser.a++],"Colourless gas,smell like that of burning sulphur,turns acidified pot dichromate paper green.");
        
        else if((VirtUser.ANION + 1) ==8)
            strcpy(VirtUser.observations[VirtUser.a++],"Brisk effervescence is noted.A colourless odourless gas turning lime water milky is evolved.");
        
        else if((VirtUser.ANION + 1) ==10)
            strcpy(VirtUser.observations[VirtUser.a++],"Colourless gas with the smell of rotten eggs.Turns lead acetate paper black.");
    }
    else
        strcpy(VirtUser.observations[VirtUser.a++],"Absence of Carbonate,Sulphide,Sulphate ions");
}


void ConcAcid(UserModel &VirtUser)
{
    cout<<"Execute Conc Acid Test\n";
    if((VirtUser.ANION + 1) ==1||(VirtUser.ANION + 1) ==3||(VirtUser.ANION + 1) ==4||(VirtUser.ANION + 1) ==5||(VirtUser.ANION + 1) ==7||(VirtUser.ANION + 1) ==9||(VirtUser.ANION + 1) ==8)
    {
        if((VirtUser.ANION + 1) ==1)
        {
            strcpy(VirtUser.observations[VirtUser.a++],"Slight brown fumes turning FeSO4 solution black");
            //strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
            //confirm(msg);
        }
        
        else if((VirtUser.ANION + 1) ==3){
            strcpy(VirtUser.observations[VirtUser.a++],"Colourless gas with a smell of vinegar which turns moist blue litmus paper red is evolved");
            //strcpy(msg,"Colourless gas with a smell of vinegar which turns moist blue litmus paper red is evolved");

            
        }
        else if((VirtUser.ANION + 1) ==8)
        {
            strcpy(VirtUser.observations[VirtUser.a++],"Carbonate is confirmed ");
        }
            
        
        
        else if((VirtUser.ANION + 1) ==4){
            strcpy(VirtUser.observations[VirtUser.a++],"Reddish brown gas which turns moist starch Iodide paper blue");
            //strcpy(msg,"Reddish brown gas which turns moist starch Iodide paper blue");

            
        }
        
        else if((VirtUser.ANION + 1) ==5){
            strcpy(VirtUser.observations[VirtUser.a++],"Colourless gas with a irritating smell which gives dense white fumes when a glass rod dipped in Ammonium Hydroxide is introduced");
            //strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
            //confirm(msg);
        }
        
        
        else if((VirtUser.ANION + 1) ==7){
            strcpy(VirtUser.observations[VirtUser.a++],"Colourless gas which turns lime water milky");
            //strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
            //confirm(msg);
        }
        
        else if((VirtUser.ANION + 1) ==9){
            strcpy(VirtUser.observations[VirtUser.a++],"Violet vapours which turn moist starch paper blue black");
            //strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
            //confirm(msg);
        }
        
    }
    else{
        strcpy(VirtUser.observations[VirtUser.a++],"Absence of Chloride,Bromide,Iodide,Oxalate,Nitrate,Acetate ions");
        //strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
        //confirm(msg);
        
    }
    
}

void ConfirmAcidRadical(UserModel &VirtUser)// work here
{
    ReagentQueue reag = ReagentQueue();
    strcpy(VirtUser.observations[VirtUser.a++]," ");
    
    cout<<"Execute Confirmatory Tests For Acid Radical\n";
    
    if((VirtUser.ANION + 1) ==1||(VirtUser.ANION + 1) ==2||(VirtUser.ANION + 1) ==3||(VirtUser.ANION + 1) ==4||(VirtUser.ANION + 1) ==5||(VirtUser.ANION + 1) ==6||(VirtUser.ANION + 1) ==7||(VirtUser.ANION + 1) ==9||(VirtUser.ANION + 1) ==10||(VirtUser.ANION + 1) ==11)
    {
        if((VirtUser.ANION + 1) == 1)
        {
            reag.ClearQueue();
            reag.add(new char[2][100]{"H2SO4","Copper Turnings"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"The solution turns green and there is profuse evolution of brown fumes which turn FeSO4 sol black");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"H2SO4","Paper Pellets"}, 2);
            if(CompareReagent(VirtUser.curr, reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"Profuse evolution of brown fumes which turn FeSO4 sol black");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"FeSO4","Conc H2SO4"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"A brown ring is formed at the junction of two liquids");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
        }
        
        else if((VirtUser.ANION + 1) ==2)
        {
            reag.ClearQueue();
            reag.add(new char[2][100]{"Conc HNO3","Ammonium Molybdate"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"Canary yellow ppt is formed");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
            
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"Magnesia Mixture"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"White ppt is obtained");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
        }
        
        else if((VirtUser.ANION + 1) ==3)
        {
            reag.ClearQueue();
            reag.add(new char[2][100]{"Conc H2SO4","C2H5OH"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"A pleasent fruity smell of ester is got");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"Neutral FeCl3"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"Red colour is formed");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
        }
        
        else if((VirtUser.ANION + 1) ==4)
        {
            reag.ClearQueue();
            reag.add(new char[2][100]{"MnO2","H2SO4"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"Reddish brown vapours turning moist starch paper yellow and moist starch iodide paper blue is evolved");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"Chlorine Water","CCl4"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"Orange brown organic layer is formed");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);}
            
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"AgNO3"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1){
                strcpy(VirtUser.observations[VirtUser.a++],"Straw coloured ppt formed which is partly soluble in NH4OH");
                strcpy(msg,"Slight brown fumes turning FeSO4 solution black");
                confirm(msg);
            }
        }
        
        else if((VirtUser.ANION + 1) ==5)
        {
            reag.ClearQueue();
            reag.add(new char[4][100]{"Potassium Dichromate","Conc H2SO4","CH3COOH","(CH3COO)2Pb"}, 4);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Yellow ppt is obtained");
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"AgNO3"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Curdy white ppt fully soluble in excess of NH4OH");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"MnO2","Conc H2SO4"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Greenish yellow gas is evolved");
        }
        
        else if((VirtUser.ANION + 1) ==6)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"BaCl2"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"A white ppt insoluble in conc HCL is obtained");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"CH3COOH","(CH3COO)2Pb"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"White ppt soluble in excess of (CH3COO)NH4 is formed");
        }
        
        else if((VirtUser.ANION + 1) ==7)
        {
            reag.ClearQueue();
            reag.add(new char[2][100]{"CH3COOH","CaCl2"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"White ppt is obtained");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"Dil H2SO4","KMnO4"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Pink colour of KMnO4 is decolourised and CO2 is evolved");
        }
        
        else if((VirtUser.ANION + 1) ==9)
        {
            reag.ClearQueue();
            reag.add(new char[2][100]{"MnO2","H2SO4"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Violet vapours which turn moist starch paper blue is obtained");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"Chlorine Water","CCl4"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Pink organic layer is obtained");
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"AgNO3"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Yellow ppt completely insoluble in NH4OH is got");
        }
        
        else if((VirtUser.ANION + 1) ==10)
        {
            reag.ClearQueue();
            reag.add(new char[2][100]{"CH3COOH","(CH3COO)2Pb"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Black ppt is formed");
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"Sodium Nitroprusside"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Purple colour is obtained");
        }
        
        else if((VirtUser.ANION + 1) ==11)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"BaCl2"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"White ppt is obtained");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"K2Cr2O7","Dil H2SO4"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Green colourisation is obtained");
        }
    }
    else if(strcmp(VirtUser.observations[VirtUser.a++]," '")==0)
        strcpy(VirtUser.observations[VirtUser.a++],"Absence of Anion! Tests Done Wrong.");
}


void ConfirmBasicRadical(UserModel &VirtUser)//WORK IN PROGRESS
{
    ReagentQueue reag = ReagentQueue();
    
    cout<<"Execute Confirmatory Tests For Basic Radical\n";
    
    strcpy(VirtUser.observations[VirtUser.a++]," ");
    
    if((VirtUser.CATION +  1)==2)
    {
        if((VirtUser.CATION +  1)==2)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"NaOH"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Colourless gas with a pungent smell giving dense white fumes with a rod dipped in conc HCL");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"NaOH","Nesslers Reagent"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Red brown ppt is formed");
        }
        else
            strcpy(VirtUser.observations[VirtUser.a++],"Absence of Zero group!");
    }
    
    if((VirtUser.CATION +  1)==1||(VirtUser.CATION +  1)==3||(VirtUser.CATION +  1)==4||(VirtUser.CATION +  1)==5||(VirtUser.CATION +  1)==6||(VirtUser.CATION +  1)==7||(VirtUser.CATION +  1)==8||(VirtUser.CATION +  1)==9||(VirtUser.CATION +  1)==10||(VirtUser.CATION +  1)==11||(VirtUser.CATION +  1)==12)
    {
        if((VirtUser.CATION +  1)==1)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"NaOH"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Gelatinous white ppt is obtained");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"Blue litmus","NH4OH"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Blue lake is formed");
        }
        
        else if((VirtUser.CATION +  1)==3)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"K2CrO4"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Yellow ppt is obtained");
        }
        
        else if((VirtUser.CATION +  1)==4)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"(NH4)2C2O4"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"White ppt is obtained");
        }
        
        else if((VirtUser.CATION +  1)==5)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"NH4OH"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"A light blue ppt dissolving in excess to give a deep blue solution");
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"K4[Fe(CN)6]"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Chocolate brown ppt is formed");
        }
        
        else if((VirtUser.CATION +  1)==6)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"K4[Fe(CN)6]"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Prussian blue colour is formed");
            
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"Dil HCL","KCNS"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Blood red colour is formed");
        }
        
        else if((VirtUser.CATION +  1)==7)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"K2CrO4"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Yellow ppt is obtained");
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"KI"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Yellow ppt which is soluble when heated and reappears as golden spangles");
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"H2SO4"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"White ppt soluble in (CH3COOH)NH4");
        }
        
        else if((VirtUser.CATION +  1)==8)
        {
            reag.ClearQueue();
            reag.add(new char[3][100]{"NH4Cl","NH4OH","Na2HPO4"}, 3);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"White ppt is obtained");
            
            reag.ClearQueue();
            reag.add(new char[4][100]{"NH4Cl","NH4OH","Na2HPO4","Co(NO3)2"}, 4);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Pink ash is obtained");
        }
        
        else if((VirtUser.CATION +  1)==9)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"NaOH"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"A white ppt which turns brown and finally black on long standing");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"Conc HNO3","PbO2"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Pinkish purple colour is obtained");
        }
        
        else if((VirtUser.CATION +  1)==10)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"NaOH"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Apple green ppt is formed");
            
            reag.ClearQueue();
            reag.add(new char[2][100]{"Dimethyl glyoxime","NH4OH"}, 2);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Cherry red ppt is formed");
        }
        
        else if((VirtUser.CATION +  1)==11)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"(NH4)2SO4"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"White ppt is formed");
        }
        
        else if((VirtUser.CATION +  1)==12)
        {
            reag.ClearQueue();
            reag.add(new char[1][100]{"NaOH"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"A white ppt soluble in excess is obtained");
            
            reag.ClearQueue();
            reag.add(new char[1][100]{"K4[Fe(CN)6]"}, 1);
            if(CompareReagent(VirtUser.curr,reag) == 1)
                strcpy(VirtUser.observations[VirtUser.a++],"Greenish white ppt is formed");
        }
    }
    else if(strcmp(VirtUser.observations[VirtUser.a++]," '")==0)
        strcpy(VirtUser.observations[VirtUser.a++],"Absence of Cation! Tests Done Wrong");
}


void execute(UserModel &VirtUser)
{
    int g;
    cout<<"enter 1 for acid radicle and 2 for basic radicle:  ";
    cin>>g;
    if(g==1)
    {
        
        //strcpy(VirtUser.observations[VirtUser.a++]," ");
        ConfirmAcidRadical(VirtUser);
    }
    else if (g==2)
    {
        //strcpy(VirtUser.observations[VirtUser.a++]," ");
        ConfirmBasicRadical(VirtUser);
    }
    
}



void DisplayUI(UserModel &user)
{
    //system("cls");
    cout<<"-------------------------------------------------------------------------------\n";
    cout<<"\t\t\t    Salt Anaysis Simulator 1.0\n";
    cout<<"-------------------------------------------------------------------------------\n";
    cout<<"Tests/Observations:\n\n";
    
    for(int i = 0; i < user.a; i++)
        cout<<(i + 1)<<". "<<user.observations[i]<<"\n";
    
    cout<<"-------------------------------------------------------------------------------\n\n";
    cout<<"1. Add reagent to queue\n";
    cout<<"2. Remove reagent from queue\n";
    cout<<"3. View reagent queue\n";
    cout<<"4. Run Prelims\n";
    cout<<"5. Dilute Acid Test\n";
    cout<<"6. Concentrated Acid Test\n";
    cout<<"7. Execute test\n";
    cout<<"8. View answer\n";
    cout<<"9. Exit\n\n";
    cout<<"Enter choice: ";
}

int main()
{
    UserModel user = UserModel();
    int choice = 0;
    while(1 == 1)
    {
        DisplayUI(user);
        cin>>choice;
        
        switch(choice)
        {
            case 1:
                user.addReagent();
                //getch();
                break;
                
            case 2:
                user.removeReagent();
                //getch();
                break;
                
            case 3:
                user.viewQueue();
                //getch();
                break;
                
            case 4:
                prelims(user);
                //getch();
                break;
                
            case 5:
                DilAcid(user);
                //getch();
                break;
                
            case 6:
                ConcAcid(user);
                //getch();
                break;
                
            case 7:
                execute(user);
                //getch();
                break;
                
            case 8:
                user.displaySalt();
                //getch();
                break;
                
            case 9:
                 exit(0);
                //getch();
                break;
            
                
            default:
                cout<<"Please enter a valid choice!\n";
        }
    }
    return 0;
}


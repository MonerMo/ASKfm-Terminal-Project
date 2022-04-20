#include <bits/stdc++.h>
#include <conio.h>

using namespace std ;


//--------------------------------------------------------
//Welcome structure main two functions is signup and login
//Welcome.login and Welcome.signup
//It will save in users login file
const int PASSLENGTH = 5;
const int NAMELENGTH = 20;
const int TEXTLENGTH = 70;

struct UserInfo{
    char username[NAMELENGTH] ;
    char email[NAMELENGTH] ;
    char pass[PASSLENGTH] ;
    char gender ;
};

UserInfo USERinput ;
UserInfo USERcheck ;

struct Login{
    char username[NAMELENGTH];
    char pass[PASSLENGTH];
};

struct retstatus{
    int userid ;
    int status ;
};

struct question{
    char username[NAMELENGTH];
    char text[TEXTLENGTH];
};

Login LOGinput ;
retstatus STATUS ; //status and userid

   //checker function for the username signup
   int checker(char holder[] ){

       int holdercnt = 0 ;
       for(int i = 0 ; i < NAMELENGTH ; i++){
           if( ( holder[i] >= 'a' && holder[i] <= 'z' ) || ( holder[i] >= 'A' && holder[i] <= 'Z' ) )
               holdercnt++;
       }

       /*for(int i = 0 ; i < NAMELENGTH ; i++) {
           cout << holder[i] ;
       }
       cout << endl;*/

       fstream checkercounter("userdata.txt", ios::binary | ios::out | ios::app);
       checkercounter.seekp(0L ,ios::end);
       int userid = checkercounter.tellp() / sizeof(USERinput) ;
       //cout << "userid : " << userid << endl;
       checkercounter.close() ;

       int statusret = 0 ;
       long pos = 0;
       for(int userindex = 0 ; userindex < userid ; userindex++){

           fstream streamchecker("userdata.txt" , ios::binary | ios::in);
           //cout << "userindex : " << userindex << endl;
           pos = ( userindex * sizeof(USERcheck) ) ;
           //cout << "pos : " << pos << endl;
           streamchecker.seekg(pos,ios::beg);
           streamchecker.read(reinterpret_cast<char*>(&USERcheck) , sizeof(USERcheck));
           streamchecker.close();
           //cout << "name : " << USERcheck.username << endl;

           //bring the length of holder and bring the length of USERcheck.username
           int checkcnt = 0 ;
           for(int i = 0 ; i < NAMELENGTH ; i++){
               if( ( USERcheck.username[i] >= 'a' && USERcheck.username[i] <= 'z' ) || ( USERcheck.username[i] >= 'A' && USERcheck.username[i] <= 'Z' ) )
                   checkcnt++ ;
           }

           //cout << "holder : " << holdercnt << " user check : " << checkcnt << endl;
           //if equal length and equal characters equal to the number of the characters then return 1
           int finalcnt = 0 ;
           if(checkcnt == holdercnt){
               for(int i = 0 ; i < checkcnt ; i++){
                   if(holder[i] == USERcheck.username[i]){
                       finalcnt++;
                   }
               }
           }
           //cout << "final cnt : " << finalcnt << endl;
           if(checkcnt == finalcnt){
               return 1 ;
           }
       }
    return 2 ;
   }


   //checker function for the username signup

   int logchecker(char holder[] , char passholder[]){

       int holdercnt = 0 ;
       for(int i = 0 ; i < NAMELENGTH ; i++){
           if( ( holder[i] >= 'a' && holder[i] <= 'z' ) || ( holder[i] >= 'A' && holder[i] <= 'Z' ) )
               holdercnt++;
       }

      /* for(int i = 0 ; i < NAMELENGTH ; i++) {
           cout << holder[i] ;
       }
       cout << endl;*/

       fstream checkercounter("userdata.txt", ios::binary | ios::out | ios::app);
       checkercounter.seekp(0L ,ios::end);
       int userid = checkercounter.tellp() / sizeof(USERinput) ;
       //cout << "userid : " << userid << endl;
       checkercounter.close() ;


       for(int userindex = 0 ; userindex < userid ; userindex++){

           fstream streamchecker("userdata.txt" , ios::binary | ios::in);
           //cout << "userindex : " << userindex << endl;
           long pos = 0;
           pos = ( userindex * sizeof(USERcheck) ) ;
           //cout << "pos : " << pos << endl;
           streamchecker.seekg(pos,ios::beg);
           streamchecker.read(reinterpret_cast<char*>(&USERcheck) , sizeof(USERcheck));
           streamchecker.close();
           //cout << "name : " << USERcheck.username << endl;


           //bring the length of holder and bring the length of USERcheck.username
           int checkcnt = 0 ;
           for(int i = 0 ; i < NAMELENGTH ; i++){
               if( ( USERcheck.username[i] >= 'a' && USERcheck.username[i] <= 'z' ) || ( USERcheck.username[i] >= 'A' && USERcheck.username[i] <= 'Z' ) )
                   checkcnt++ ;
           }

           //cout << "holder : " << holdercnt << " user check : " << checkcnt << endl;
           //if equal length and equal characters equal to the number of the characters then return 1
           int finalcnt = 0 ;
           if(checkcnt == holdercnt){
               for(int i = 0 ; i < checkcnt ; i++){
                   if(holder[i] == USERcheck.username[i]){
                       finalcnt++;
                   }
               }
           }

           int passstate = 0 ;
           for(int i = 0 ; i < PASSLENGTH ; i++){
               if(passholder[i] != USERcheck.pass[i]){
                   passstate = 1 ;
                   break ;
               }
           }


           //cout << "final cnt : " << finalcnt << endl;
           if( ( checkcnt == finalcnt ) && ( passstate == 0 ) ){
               return 3;
           }
       }
       return 4 ;
   }



struct Welcome{

    int signup(){

        fstream userdatastream ;


        cout << "Enter your Username         : " ;
        cin.getline(USERinput.username,15);
        int status = checker(USERinput.username);
        if(status == 1){
            cout << "USER NAME IS ALREADY USED" << endl;
            cout << "BACK TO STARTUP" << endl;
            cout << "SIGN UP FAILED" << endl;
            return status; //signup have and error return to main menu
        }else{
            cout << "\n" ;
            cout << "USER NAME IS NOT USED" << endl;
            cout << "\n" ;
        }

        //email
        cout << "Enter your email address    : " ;
        cin.getline(USERinput.email,15);

        //pass
        cout << "Enter your password         : " ;
        for(int i = 0 ; i < PASSLENGTH ; i++){
            USERinput.pass[i] = _getch(); _putch('*');
        }
        cout << endl;

        //gender
        cout << "Gender - Male-M , Female-F  : " ;
        USERinput.gender = getchar();
        cin.ignore();

        //writing it in bianry form in text file as records (structures) ;
        userdatastream.open("userdata.txt" , ios::binary|ios::out|ios::app);
        userdatastream.write(reinterpret_cast<char*>(&USERinput),sizeof(USERinput));
        userdatastream.close();
        cout << "SIGN UP DONE COMPLETELY" << endl;
         //signup done completely
        return 2 ;

        cout << "------------------------------------------------" << endl;
    }


    int login(){
        cout << "------ LOG IN PAGE ------" << endl;
        cout << "USERNAME : " ;
        cin.getline(LOGinput.username , NAMELENGTH);
        cout << "PASSWORD : " ;
        for(int i = 0 ; i < PASSLENGTH ; i++){
            LOGinput.pass[i] = _getch(); _putch('*');
        }
        cout << endl;

        int status = logchecker(LOGinput.username , LOGinput.pass);
        if(status == 3){
            cout << "login done completely" << endl;
            return 3 ;
        }else if(status == 4){
            cout << "wrong either in username or password" << endl;
            return 4 ;
        }
    }
};
Welcome Session ;


int startup(){
    char MMCHOICE ;

    cout << "--------------Welcome to neighbours forum--------------" << "\n \n" ;
    cout << "1:SIGN UP" << "\n" << "2:LOG IN" << "\n" ;
    cout << "Enter 1 or 2 depend on your choice : " ;
    cin.get(MMCHOICE);
    cin.ignore();

    while( ( MMCHOICE != '1' ) && ( MMCHOICE != '2') ){
        cout << "Please Enter a valid input : " ;
        cin.get(MMCHOICE);
        cin.ignore();
    }

    int MMstatus  ;
    switch(MMCHOICE){
        case('2'):
            system("cls");
            cout << "~TAKING YOU TO LOG IN PAGE ~\n" ;
            MMstatus = Session.login();
            break;
        case('1'):
            system("cls");
            cout << "~ TAKING YOU TO SIGN UP PAGE ~ \n";
            MMstatus = Session.signup();
            break;
    }
    return MMstatus ;
}




int main(){

int status ;
//1.sign up failed   ,  2.sign up success , 3.login success , 4.login failed
do{
    status = startup();
}while( ( status !=  3) );
//if signup is done then go to main menu until it return login signal








}

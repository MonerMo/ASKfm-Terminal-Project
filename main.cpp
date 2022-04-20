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

//LOGIN OPTIONS PROTOTYPES
int LOG1(char owner[]) ;

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
    long userid ;
    int status ;
};

struct question{
    char username[NAMELENGTH];
    char text[TEXTLENGTH];
};

Login LOGinput ;
retstatus STATUS ; //status and userid
question QUES ;

   //checker function for the username signup
   retstatus checker(char holder[] ){

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
               STATUS.status = 1;
               STATUS.userid = pos ;
               return STATUS ;
           }
       }
    STATUS.status = 2 ;
    STATUS.userid = pos ;
    return STATUS ;
   }


   //checker function for the username signup

   retstatus logchecker(char holder[] , char passholder[]){

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

           int passstate = 0 ;
           for(int i = 0 ; i < PASSLENGTH ; i++){
               if(passholder[i] != USERcheck.pass[i]){
                   passstate = 1 ;
                   break ;
               }
           }


           //cout << "final cnt : " << finalcnt << endl;
           if( ( checkcnt == finalcnt ) && ( passstate == 0 ) ){
               STATUS.status = 3 ;
               STATUS.userid = pos ;
               return STATUS;
           }
       }
       STATUS.status = 4 ;
       STATUS.userid = pos ;
       return STATUS ;
   }



struct Welcome{

    retstatus signup(){

        fstream userdatastream ;


        cout << "Enter your Username         : " ;
        cin.getline(USERinput.username,NAMELENGTH);
        retstatus status = checker(USERinput.username);
        if(status.status == 1){
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
        status.status = 2 ;
        return status ;

        cout << "------------------------------------------------" << endl;
    }


    retstatus login(){
        cout << "------ LOG IN PAGE ------" << endl;
        cout << "USERNAME : " ;
        cin.getline(LOGinput.username , NAMELENGTH);
        cout << "PASSWORD : " ;
        for(int i = 0 ; i < PASSLENGTH ; i++){
            LOGinput.pass[i] = _getch(); _putch('*');
        }
        cout << endl;

        retstatus status = logchecker(LOGinput.username , LOGinput.pass);
        if(status.status == 3){
            cout << "login done completely" << endl;
            status.status = 3 ;
            return status ;
        }else if(status.status == 4){
            cout << "wrong either in username or password" << endl;
            status.status = 4 ;
            return status ;
        }
    }
};
Welcome Session ;


retstatus startup(){
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

    retstatus MMstatus  ;
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


int LOGmenu(retstatus LOGstruct){
    system("cls");
    //LOGstream will bring the name of the user that is logged in rn ;
    fstream LOGstream("userdata.txt" , ios::binary | ios::in) ;
    LOGstream.seekg(LOGstruct.userid,ios::beg);
    LOGstream.read(reinterpret_cast<char*>(&USERcheck), sizeof(USERcheck));
    cout << "Welcom,Mr." << USERcheck.username << endl;
    LOGstream.close();
    cout << "CHOOSE THE OPERATION YOU WANT TO MAKE" << endl;
    cout << "1 : ASK A QUESTION TO USER\n"
         << "2 : ANSWER QUESTIONS ASKED TO ME\n"
         << "3 : DELETE A QUESTION YOU ASKED\n" ;

    char LOGMMCHOICE ;
    LOGMMCHOICE = cin.get();
    cin.ignore();

    switch(LOGMMCHOICE){
        case('1'):
            system("cls");
            cout << "~ ASKING A QUESTION MENU ~" << endl;
            int status = LOG1(USERcheck.username);
            if(status == 2){
                cout << "USER NOT FOUND." << endl;
                return 1;
            }

            break ;
    }

}

retstatus LOG1struct;
int LOG1(char owner[]){

    //now make a string called ownerQUES.txt
    string ownerques = owner ;
    ownerques += "ques.txt" ;

    char ownerraw[NAMELENGTH] ;
    for(int i = 0 ; i < NAMELENGTH ; i++){
        ownerraw[i] = owner[i] ;
    }

    //it will take the user name of the user we want to ask
    //and check if this user exists or not
    cout << "ENTER THE USERNAME OF THE USER YOU WANT TO ASK AND AFTER THAT THE QUESTION" << endl;
    cout << "USERNAME : " ;

    cin.getline(QUES.username,NAMELENGTH);
    LOG1struct = checker(QUES.username);
    if(LOG1struct.status == 2){
        return 2; // this means that when asking question the username is not found
    }
    cout << "QUESTION : " ;
    cin.getline(QUES.text,TEXTLENGTH);

    //first we want to bring the name of the user asked to
    fstream LOG1("datasource.txt" , ios::binary | ios::in);
    LOG1.seekg(LOG1struct.userid,ios::beg);
    LOG1.read(reinterpret_cast<char*>(&USERcheck),sizeof(USERcheck));
    LOG1.close();

    //now make a string called askedtoASK.txt
    string askedto = USERcheck.username ;
    askedto += "ask.txt" ;


    //we want to output in the ownerques file the name of the user asked to and the question
    LOG1.open(ownerques, ios::binary | ios::out | ios::app);
    LOG1.write(reinterpret_cast<char*>(&QUES),sizeof(QUES));
    LOG1.close();

    //we want to output in the askedtoASK file the name of the user asked and the question
    for(int i = 0 ; i < NAMELENGTH ; i++){
        QUES.username[i] = ownerraw[i] ;
    }
    LOG1.open(askedto, ios::binary | ios::out | ios::app);
    LOG1.write(reinterpret_cast<char*>(&QUES),sizeof(QUES));
    LOG1.close() ;
}




int main(){

retstatus status ;
//1.sign up failed   ,  2.sign up success , 3.login success , 4.login failed
do{
    status = startup();
}while( ( status.status !=  3) );
//if signup is done then go to main menu until it return login signal

int LOGsignal ;
LOGsignal = LOGmenu(status);






}

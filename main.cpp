#include <bits/stdc++.h>
#include <conio.h>
#include <cstdio>

using namespace std ;


//--------------------------------------------------------
//Welcome structure main two functions is signup and login
//Welcome.login and Welcome.signup
//It will save in users login file
const int PASSLENGTH = 5;
const int NAMELENGTH = 20;
const int TEXTLENGTH = 70;
const int OLDFILESIZE = 100;

//LOGIN OPTIONS PROTOTYPES
static bool firstlogin ;
int LOG1(char owner[]) ;
int LOG2(char owner[]) ;
int LOG3(char owner[]) ;

struct UserInfo{
    char username[NAMELENGTH] ;
    char email[NAMELENGTH] ;
    char pass[PASSLENGTH] ;
    char gender ;
    char anonymousacc ; //if 'n' means the user won't take anonymous question
    //if 'y' in this case we will give the users to ask anonymous question or not
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
    char anonymousstatus ;
};

struct question{
    char username[NAMELENGTH];
    char text[TEXTLENGTH];
    char anonymous ; //this is the state of the question if anonymous or not
    bool answered ; // to tell if the question is answered or not
    int quesID ;
};

Login LOGinput ;
retstatus STATUS ; //status and userid
question QUES ;

   //checker function for the username signup
   retstatus checker(char holder[]){

       string HOLDER = holder ;
       /*int holdercnt = 0 ;
       for(int i = 0 ; i < NAMELENGTH ; i++){
           if( ( holder[i] >= 'a' && holder[i] <= 'z' ) || ( holder[i] >= 'A' && holder[i] <= 'Z' ) )
               holdercnt++;
       }*/

       /*for(int i = 0 ; i < NAMELENGTH ; i++) {
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
           /*for(int i = 0 ; i < NAMELENGTH ; i++){
               if( ( USERcheck.username[i] >= 'a' && USERcheck.username[i] <= 'z' ) || ( USERcheck.username[i] >= 'A' && USERcheck.username[i] <= 'Z' ) )
                   checkcnt++ ;
           }*/

           //cout << "holder : " << holdercnt << " user check : " << checkcnt << endl;
           //if equal length and equal characters equal to the number of the characters then return 1
           int finalcnt = 0 ;

           /*if(checkcnt == holdercnt){
               for(int i = 0 ; i < checkcnt ; i++){
                   if(holder[i] == USERcheck.username[i]){
                       finalcnt++;
                   }
               }
           }*/

           //cout << "final cnt : " << finalcnt << endl;
           string COMPARE = USERcheck.username;
           if(HOLDER == COMPARE){
               STATUS.status = 1;
               STATUS.userid = pos ;
               STATUS.anonymousstatus = USERcheck.anonymousacc ;
               return STATUS ;
           }
       }
    STATUS.status = 2 ;
    STATUS.userid = pos ;
    STATUS.anonymousstatus = USERcheck.anonymousacc ;
    return STATUS ;
   }


   //checker function for the username signup

   retstatus logchecker(char holder[] , char passholder[]){


       /*for(int i = 0 ; i < holdercnt ; i++) {
           cout << holder[i] ;
       }
       cout << endl;*/

       fstream checkercounter("userdata.txt", ios::binary | ios::out | ios::app);
       checkercounter.seekp(0L ,ios::end);
       int userid = checkercounter.tellp() / sizeof(USERinput) ;
       //cout << "userid : " << userid << endl;
       checkercounter.close() ;
       string HOLDER = holder ;


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

           /*int checkcnt = 0 ;
           for(int i = 0 ; i < NAMELENGTH ; i++){
               if( ( USERcheck.username[i] >= 'a' && USERcheck.username[i] <= 'z' ) || ( USERcheck.username[i] >= 'A' && USERcheck.username[i] <= 'Z' ) )
                   checkcnt++ ;
           }*/

           //cout << "holder : " << holdercnt << " user check : " << checkcnt << endl;
           //if equal length and equal characters equal to the number of the characters then return 1
           int finalcnt = 0 ;
          /* if(checkcnt == (holdercnt)){
               for(int i = 0 ; i < checkcnt ; i++){
                   if(holder[i] == USERcheck.username[i]){
                       finalcnt++;
                   }
               }
           }*/

           int passstate = 0 ;
           for(int i = 0 ; i < PASSLENGTH ; i++){
               if(passholder[i] != USERcheck.pass[i]){
                   passstate = 1 ;
                   break ;
               }
           }
           string COMPARE = USERcheck.username ;
           if(HOLDER == COMPARE){
               finalcnt = 1 ;
           }

           //cout << "final cnt : " << finalcnt << endl;
           if( ( finalcnt == 1 ) && ( passstate == 0 ) ){
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

        retstatus status ;
        cout << "[0]Back to main menu." << endl;
        cout << "----------------------" << endl;
        cout << "Enter your Username         : " ;
        cin.getline(USERinput.username,NAMELENGTH);
        //we want to make a back choice here
        //we will make the user input 0 and return 99 as a back signal
        if(USERinput.username[0] == '0'){
            status.status = 9 ;
            return  status ;
        }
        status = checker(USERinput.username);
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

        //get user acceptance of anonymous questions
        cout << "Accept anonymous questions ('y' for yes , 'n' for no). : " ;
        USERinput.anonymousacc = getchar();
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
        retstatus status ;
        cout << "------ LOG IN PAGE ------" << endl;
        cout << "[0]Back to main menu." << endl;
        cout << "-------------------------" << endl;
        cout << "USERNAME : " ;
        cin.getline(LOGinput.username , NAMELENGTH);
        if(LOGinput.username[0] == '0'){
            status.status = 9 ;
            return status ;
        }
        cout << "PASSWORD : " ;
        for(int i = 0 ; i < PASSLENGTH ; i++){
            LOGinput.pass[i] = _getch(); _putch('*');
        }
        cout << endl;

        status = logchecker(LOGinput.username , LOGinput.pass);
        if(status.status == 3){
            cout << "login done completely" << endl;
            firstlogin = true ;
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
    cout << "1:SIGN UP" << "\n" << "2:LOG IN" << "\n" << "3:TERMINATE PROGRAM" << "\n" ;
    cout << "Enter 1 , 2 or 3 depend on your choice : " ;
    cin.get(MMCHOICE);
    cin.ignore(100,'\n');

    while( ( MMCHOICE != '1' ) && ( MMCHOICE != '2') && ( MMCHOICE != '3' )){
        cout << "Please Enter a valid input : " ;
        cin.get(MMCHOICE);
        cin.ignore(100 , '\n');
    }

    retstatus MMstatus  ;
    switch(MMCHOICE){
        case('3'):
            exit(0);
            break;
        case('2'):
            system("cls");
            cout << "~ TAKING YOU TO LOG IN PAGE ~\n" ;
            MMstatus = Session.login();
            break;
        case('1'):
            system("cls");
            cout << "~ TAKING YOU TO SIGN UP PAGE ~\n";
            MMstatus = Session.signup();
            break;
    }
    return MMstatus ;
}


int LOGmenu(retstatus LOGstruct){
    //system("cls");
    //LOGstream will bring the name of the user that is logged in rn ;
    fstream LOGstream("userdata.txt" , ios::binary | ios::in) ;
    LOGstream.seekg(LOGstruct.userid,ios::beg);
    LOGstream.read(reinterpret_cast<char*>(&USERcheck), sizeof(USERcheck));
    LOGstream.close();
    //cout << "Welcom,Mr." << USERcheck.username << endl;
    char usernameholder[NAMELENGTH] ;
    if(firstlogin){
        firstlogin = false ;
        for(int i = 0 ; i < NAMELENGTH ; i++){
            usernameholder[i] = USERcheck.username[i] ;
        }
    }
    cout << "CHOOSE THE OPERATION YOU WANT TO MAKE" << endl;
    cout << "0 : LOG OUT.\n"
         << "1 : ASK A QUESTION TO USER.\n"
         << "2 : ANSWER QUESTIONS ASKED TO ME.\n"
         << "3 : DELETE A QUESTION YOU ASKED.\n" ;

    int signal ;
    char LOGMMCHOICE ;
    LOGMMCHOICE = cin.get();
    cin.ignore(100,'\n');
    while( (LOGMMCHOICE != '0') && (LOGMMCHOICE != '1') && (LOGMMCHOICE != '2') && (LOGMMCHOICE != '3')){
        cout << "PLEASE ENTER A VALID INPUT : " ;
        LOGMMCHOICE = cin.get();
        cin.ignore(100,'\n');
    }

    //we want to add log out and back to main menu here
    switch(LOGMMCHOICE){
        case('3'):
            system("cls");
            cout << "~ DELETING QUESTION MENU ~" << endl;
            signal = LOG3(USERcheck.username);
            return signal ;
            break;

        case('0'):
            system("cls");
            cout << "~ LOGGING OUT AND BACK TO MAIN MENU ~" << endl;
            return 9 ;
            break;

        case('2'):
            system("cls");
            cout << "~ ANSWERING QUESTIONS MENU ~" << endl;
            //if the return signal is 22 then we will move back to the question answer menu
            do{
                signal = LOG2(USERcheck.username);
            }while(signal == 22);

            if(signal == 20){
                cout << "BACK TO OPERATION MENU." << endl;
                return signal ;
            }else if(signal == 21){
                cout << "NO QUESTIONS FOUND." << endl;
                return signal ;
            }else if(signal == 23){
                cout << "ANSWERING DONE COMPLETELY." << endl;
                return signal ;
            }

        case('1'):
            system("cls");
            cout << "~ ASKING A QUESTION MENU ~" << endl;
            signal = LOG1(usernameholder);
            if(signal == 10){
                cout << "BACK TO OPERATION MENU." << endl;
                return signal ;
            }else if(signal == 11){
                cout << "USER YOU ARE ASKING NOT FOUND." << endl;
                return signal ;
            }else if(signal == 12){
                cout << "QUESTION ASKED COMPLETE." << endl;
                return signal ;
            }
            break ;
    }

}

retstatus LOG1struct;
int LOG1(char owner[]){

    //now make a string called ownerQUES.txt
    string ownerques = owner ;
    ownerques += "ques.txt" ;


    //it will take the user name of the user we want to ask
    //and check if this user exists or not
    cout << "[0]Back to operation menu." << endl;
    cout << "--------------------------" << endl;
    cout << "ENTER THE USERNAME OF THE USER YOU WANT TO ASK AND AFTER THAT THE QUESTION" << endl;
    cout << "USERNAME : " ;
    cin.getline(QUES.username,NAMELENGTH);

    //give the option if the user want to go back to the operation menu
    if(QUES.username[0] == '0'){
        return 10;
    }

    LOG1struct = checker(QUES.username);
    if(LOG1struct.status == 2){
        return 11; // this means that when asking question the username is not found
    }

    //after getting the username, and it exists in the text file
    //we want to know that the user we asked accepts anonymous questions or not.
    if(LOG1struct.anonymousstatus == 'y' || LOG1struct.anonymousstatus == 'Y'){
        cout << "USER ACCEPTS ANONYMOUS QUESTIONS." << endl;
        cout << "DO YOU WANT TO SEND ANONYMOUS QUESTION ( 'y' for yes , 'n' for no ) : " ;
        QUES.anonymous = getchar();
        cin.ignore();
    }else if(LOG1struct.anonymousstatus == 'n' || LOG1struct.anonymousstatus == 'N'){
        cout << "USER DOESN'T ACCEPT ANONYMOUS QUESTIONS." << endl;
        QUES.anonymous = 'n' ;
    }
    //so when we want to show a question we will check the anonymous char
    //if it is 1 we will output Anonymous : question content . if 0 we will output the username



    cout << "QUESTION : " ;
    cin.getline(QUES.text,TEXTLENGTH);

    //making question ID
    fstream ID("quesID.txt",ios::in);
    ID >> QUES.quesID ;
    QUES.quesID += 1 ;
    ID.close();
    ID.open("quesID.txt",ios::out);
    ID << QUES.quesID ;
    ID.close();

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
        QUES.username[i] = owner[i] ;
    }
    LOG1.open(askedto, ios::binary | ios::out | ios::app);
    LOG1.write(reinterpret_cast<char*>(&QUES),sizeof(QUES));
    LOG1.close() ;
    return 12;
}


int LOG2(char owner[]){
    // this function will show the questions to the user first
    //first we want to open the file of the questions for the owner
    string forshow = owner ;
    string ownerques = owner ;
    ownerques += "ask.txt" ;
    fstream LOG2(ownerques , ios::binary | ios::in);
    //we want to calculate the number of the questions
    int quescounter = 0 ;
    LOG2.seekg(0L , ios::end) ;
    quescounter = LOG2.tellg() / sizeof(QUES) ;

    int sizechecker = LOG2.tellg();

    if(sizechecker == -1){
        cout << "NO QUESTIONS FOUND." << endl;
        return 21 ;
    }

    //cout << "quescounter : " << quescounter << endl;

    //this will show the questions first
    LOG2.seekg(0L , ios::beg);
    cout << "--------------------------" << endl;
    for(int i = 0 ; i < quescounter ; i++){
            long pos = ( i * (sizeof(QUES)) ) ;
            LOG2.seekg(pos , ios::beg);
            LOG2.read(reinterpret_cast<char*>(&QUES),sizeof(QUES));
            //check anonymous
            //cout << "anon : " << QUES.anonymous << endl;
            if(QUES.anonymous == 'y' || QUES.anonymous == 'Y'){
                cout << "Question ID:" << QUES.quesID << endl;
                cout << "Asked By:Anonymous to " << forshow << endl;
            }else{
                cout << "Question ID:" << QUES.quesID << endl;
                cout << "Asked By:" << QUES.username << " to " << forshow << endl;
            }
            cout << i << ")Question:" << QUES.text << endl;
            cout << "--------------------------" << endl;
    }

    //after that the user will choose the number of the question he wants to answer
    //adding a back button here for 99 value (in the future)
    cout << "------- [B]ack to operation menu or [C]ontinue -------" << endl;
    cout << "------------------------------------------------------" << endl;
    char flow = cin.get();
    cin.ignore(100 , '\n');

    while((flow != 'b') && ( flow != 'B') && (flow != 'c' ) && ( flow != 'C')){
        cout << "ENTER A VALID INPUT : " ;
        flow = cin.get();
        cin.ignore(100 , '\n') ;
    }

    if(flow == 'b' || flow == 'B'){
        return 20;
    }else if(flow == 'c' || flow == 'C'){

        cout << "Enter the number of the question you want to answer : " ;
        int quesNUM ;
        cin >> quesNUM ;
        cin.ignore(100,'\n');
        while(quesNUM >= quescounter || quesNUM < 0){
            cout << "ENTER A VALID INPUT : " ;
            cin >> quesNUM ;
            cin.ignore(100,'\n');
        }
        //now after knowing the number of the question we will get it again on the screen and let him put the answer

        system("cls");
        cout << "[0] Back to questions menu." << endl;
        cout << "-------------------------" << endl;
        long pos = ( quesNUM * (sizeof(QUES)) ) ;
        LOG2.seekg(pos ,ios::beg);
        LOG2.read(reinterpret_cast<char*>(&QUES) ,sizeof(QUES));
        if(QUES.anonymous == 'y' || QUES.anonymous == 'Y'){
            cout << "Asked By:Anonymous" << endl;
        }else{
            cout << "Asked By:" << QUES.username << endl;
        }
        cout << quesNUM << ")Question:" << QUES.text << endl;
        LOG2.close();

        //answer file name : quesIDans.txt ;
        int quesID = QUES.quesID;

        int counter = 0 ;
        //number of characters of the quesID
        for(;quesID > 0;){
            quesID % 10 ;
            quesID /= 10 ;
            counter ++ ;
        }

        quesID = QUES.quesID ;
        char ID[counter] ;
        //getting the quesID but in characters
        for(int i = 0 ; i < counter ; i++){
            ID[i] = '0' + int(quesID % 10);
            quesID /= 10 ;
        }

        //reverse the array
        for(int i = 0 ; i < counter ; i++){
            char holder ;
            holder = ID[i] ;
            ID[i] = ID[counter-1-i] ;
            ID[counter - 1 - i] = holder ;
            if(i == (counter-1-i))
                break;
        }
        string answerfile ;
        for(int i = 0 ; i < counter ; i++){
            answerfile += ID[i] ;
        }

        answerfile += "ans.txt" ;

        //taking and outputting the answer
        cout << "Answer:" ;
        string answer ;
        getline(cin , answer);
        if(answer[0] == '0'){
            return 22;
        }

        LOG2.open(answerfile, ios::out | ios::app);
        LOG2 << answer << endl;
        LOG2.close();

        //setting the answered bit to true ( ANSWERED )
        LOG2.open(ownerques , ios::binary | ios::out | ios::app);
        LOG2.seekg(pos,ios::beg);
        QUES.answered = true ;
        LOG2.write(reinterpret_cast<char*>(&QUES),sizeof(QUES));
        LOG2.close();
        return 23;
    }
}


int LOG3(char owner[]){
    //we will open the file of the questions asked by the user
    //ownerques.txt file
    //after that show all the questions
    //we should check the number of the questions to limit the input of the user
    //then let the user enter the number of the question he wants to delete
    //first we will make a temporary file for all the question we have except the question he wants to delete
    //after that delete the old file
    //then rename the new temporary file with the same old name

    cout << "--------------------------" << endl;
    string OWNER = owner ;
    int ownersize = OWNER.length();
    string forshow = owner ;
    OWNER += "ques.txt" ;

    fstream LOG3(OWNER,ios::binary | ios::in);

    int quescounter = 0 ; //number of questions
    LOG3.seekg(0L , ios::end) ;
    quescounter = LOG3.tellg() / sizeof(QUES) ;
    int filesize = LOG3.tellg();
    cout << "file size : " << filesize << endl;
    if(filesize == -1 || filesize == 0){//this means that there are no questions
        return 31 ;
    }

    //showing all questions.
    LOG3.seekg(0L , ios::beg);
    cout << "--------------------------" << endl;
    for(int i = 0 ; i < quescounter ; i++){
        long pos = ( i * (sizeof(QUES)) ) ;
        LOG3.seekg(pos , ios::beg);
        LOG3.read(reinterpret_cast<char*>(&QUES),sizeof(QUES));
        //check anonymous
        //cout << "anon : " << QUES.anonymous << endl;
        if(QUES.anonymous == 'y' || QUES.anonymous == 'Y'){
            cout << "Question ID:" << QUES.quesID << endl;
            cout << "Asked By:Anonymous to " << QUES.username << endl;
        }else{
            cout << "Question ID:" << QUES.quesID << endl;
            cout << "Asked By:" << forshow << " to " << QUES.username << endl;
        }
        cout << i << ")Question:" << QUES.text << endl;
        cout << "--------------------------" << endl;
    }
    LOG3.close();


    //after that the user choose either to go back or input number
    cout << "[-1] To go back to operations menu." << endl;
    cout << "Enter the number of the question you want to delete : " ;
    int choice ;
    cin >> choice ;
    cin.ignore(100,'\n');
    while( (choice >= quescounter ) || ( (choice < 0) && (choice != -1) ) ){
        cout << "ENTER A VALID INPUT : " ;
        cin >> choice ;
        cin.ignore(100,'\n');
    }

    if(choice == -1){
        return 30;
    }else{
        //first we will make two stream objects one to input the data and the other to ouput it
        string outfilename = "temp.txt" ;
        char OUTFILENAME[] = "temp.txt" ;
        fstream INPUT(OWNER, ios::binary | ios::in);
        fstream OUTPUT(outfilename , ios::binary | ios::out | ios::app );

        for(int i = 0 ; i < quescounter ; i++){
            //we want to skip the question we want to delete
            if(i == choice)
                continue ;
            long pos ;
            pos = (i * (sizeof(QUES)));
            INPUT.seekg(pos , ios::beg);
            INPUT.read(reinterpret_cast<char*>(&QUES),sizeof(QUES));
            OUTPUT.write(reinterpret_cast<char*>(&QUES),sizeof(QUES));
        }
        INPUT.close();
        OUTPUT.close();

        //then remove the old file
        //the name of the old file should be an array
        char OLDFILENAME[OLDFILESIZE] ;
        for(int i = 0 ; i < ownersize ; i++){
            OLDFILENAME[i] = OWNER[i] ;
        }
        OLDFILENAME[ownersize] = 'q';
        OLDFILENAME[ownersize+1] = 'u';
        OLDFILENAME[ownersize+2] = 'e';
        OLDFILENAME[ownersize+3] = 's';
        OLDFILENAME[ownersize+4] = '.';
        OLDFILENAME[ownersize+5] = 't';
        OLDFILENAME[ownersize+6] = 'x';
        OLDFILENAME[ownersize+7] = 't';

        remove(OLDFILENAME);
        rename(OUTFILENAME,OLDFILENAME);
    }
    return 32;
}



int main(){

//the flow signals

retstatus status ;
//1.sign up failed   ,  2.sign up success , 3.login success , 4.login failed

for(;;){
    do{
        status = startup();
    }while( ( status.status != 3 ) ) ;

    int LOGsignal ;
    do{
        LOGsignal = LOGmenu(status);
    }while( (LOGsignal != 9) ) ;
}









}

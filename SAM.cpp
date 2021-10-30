//By Francisco Montalvo and Alberto Perez
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

//We tried our best here professor but it turned out to be more confusing then expected -Francisco
//We know this was doomed from the start -Alberto
//This code will probably not work but hopefully we get some points for it :)

//G = (T,N,S,R)

//T =  +, -, *, /, (, ),id, =, int, bool, string, float
//N = E, Q,T ,X, F, I, S, A, D, Y
//S = E
//R = Below

//E = Expression, Q = Expression Prime, T = Term, X = Term Prime, F = Factor, I = ID, S = Statement, A = Assignment, D = Declarative, Y = Type

// E -> TQ | T
// Q -> +TQ | -TQ | epsilon
// T -> FX | F
// X -> *FX | /FX | epsilon
// F -> (E) | I
// I -> id
// S -> A | D
// A -> I = E
// D -> Y I
// Y -> int | bool | string | float




int main()
{
    string empty="";
    vector<string> charray;       //vector to store all lines from input file
    ofstream writefile;          // used to write to file
    writefile.open("output.txt");     //opens output.txt
    ifstream readfile;          //  used to read from file
    string table[11][14];       // our parsing table
    for(int i=0;i<11;i++){
      for(int j=0;j<14;j++){
        table[i][j]="";
      }
    }
    table[1][0] = "E";         // this line and the lines below are to fill in the parsing table
    table[2][0] = "Q";
    table[3][0] = "T";
    table[4][0] = "X";
    table[5][0] = "F";
    table[6][0] = "I";
    table[7][0] = "S";
    table[8][0] = "A";
    table[9][0] = "D";
    table[10][0] = "Y";

    table[0][1] = "+";
    table[0][2] = "-";
    table[0][3] = "*";
    table[0][4] = "/";
    table[0][5] = "(";
    table[0][6] = ")";
    table[0][7] = "id";
    table[0][8] = "=";
    table[0][9] = "int";
    table[0][10] = "bool";
    table[0][11] = "string";
    table[0][12] = "float";
    table[0][13] = "$";

    table[1][5] = "TQ";
    table[1][7] = "TQ";

    table[2][1] = "+TQ";
    table[2][2] = "-TQ";
    table[2][6] = "ε";
    table[2][13] = "ε";

    table[3][5] = "FX";
    table[3][7] = "FX";

    table[4][1] = "ε";
    table[4][2] = "ε";
    table[4][3] = "*FX";
    table[4][4] = "/FX";
    table[4][6] = "ε";
    table[4][13] = "ε";

    table[5][5] = "(E)";
    table[5][7] = "I";

    table[6][7] = "id";

    table[7][7] = "A";
    table[7][9] = "D";
    table[7][10] = "D";
    table[7][11] = "D";
    table[7][12] = "D";

    table[8][7] = "I=E";

    table[9][9] = "YI";
    table[9][10] = "YI";
    table[9][11] = "YI";
    table[9][12] = "YI";

    table[10][9] = "int";
    table[10][10] = "bool";
    table[10][11] = "string";
    table[10][12] = "float";

    stack <char> s;        //stack to use along side parsing table
    s.push('$');          //push Terminal Symbol
    s.push('E');         //push first Symbol

    string filename;   //used to store filename received from user;
    cout << "Please enter a filename: ";
    cin >> filename;

    bool comment = false;
    string temp;    //temp variable to store line from file
    string red;
    readfile.open(filename);                                //reads from a file
    while(getline(readfile,red))         //while a line exists to be gotten
    {

      int counter = 0;    //counter used to iterate through the vector charray of lines from input file
      if (red[red.size()-1] == '!' && comment == true){                                        //checking for end of comment
          comment = false;
          continue;
        }
      else if (red[0] == '!'){                                                          //checking for start of comment
          comment = true;
          continue;
        }
      else if (comment == true){                                                   //checking for comment content
          continue;
        }
      temp = red;
      temp = temp + '$';                  //append $ to end of line
      charray.push_back(temp);            //store in charray

      do                                //do while
      {
        char to = s.top();             //set to top of stack
        char iz = temp[counter];       //set to first char in line
        string t;
        t.push_back(to);
        string i;
        i.push_back(iz);
        int p = 0;
        int q = 0;
        if(to == '$')                  //if top of stack is equal $
        {
          if(t == i)                //if top of stack is equal to i
          {
              if(t == "E")
              {
                writefile << "<Expression> -> <Term> <Expression Prime> | <Term>" << endl;
                writefile << "<Factor> -> (<Expression>) | <ID>" << endl;
                writefile << "<Assignment> -> <ID> = <Expression>" << endl;
              }

              if(t == "Q")
              {
                writefile << "<Expression Prime> -> +<Term> <Expression Prime> | -<Term><Expression Prime> | ε " << endl;
                writefile << "<Expression> -> <Term> <Expression Prime> | <Term>" << endl;
              }

              if(t == "T")
              {
                writefile << "<Term> -> <Factor> <Term Prime> | <Factor>" << endl;
                writefile << "<Expression> -> <Term> <Expression Prime> | <Term>" << endl;
                writefile << "<Expression Prime> -> +<Term> <Expression Prime> | -<Term><Expression Prime> | ε " << endl;
              }

              if(t == "X")
              {
                writefile << "<Term Prime> -> *<Factor><Term Prime> | /<Factor><Term Prime> | ε" << endl;
                writefile << "<Term> -> <Factor> <Term Prime> | <Factor>" << endl;
              }

              if(t ==  "F")
              {
                writefile << "<Factor> -> (<Expression>) | <ID>" << endl;
                writefile << "<Term> -> <Factor> <Term Prime> | <Factor>" << endl;
                writefile << "<Term Prime> -> *<Factor><Term Prime> | /<Factor><Term Prime> | ε" << endl;
              }

              if(t == "ID")
                writefile << "<ID> -> id" << endl;

              if(t == "S")
                writefile << "<Statement> -> <Assignment> | <Declaration>" << endl;

              if(t == "A")
              {
                writefile << "<Assignment> -> <ID> = <Expression>" << endl;
                writefile << "<Statement> -> <Assignment> | <Declaration>" << endl;
              }

              if(t == "D")
              {
                writefile << "<Declarative> -> <Type> <ID>" << endl;
                writefile << "<Statement> -> <Assignment> | <Declaration>" << endl;
              }

              if(t == "Y")
                writefile << "<Type> -> int | bool | string | float" << endl;


              if(t == "+")
                writefile << "<Expression Prime> -> +<Term> <Expression Prime> | -<Term><Expression Prime> | ε" << endl;


              if(t == "-")
                writefile << "<Expression Prime> -> +<Term> <Expression Prime> | -<Term><Expression Prime> | ε" << endl;


              if(t == "*")
                writefile << "<Term Prime> -> *<Factor><Term Prime> | /<Factor><Term Prime> | ε" << endl;


              if(t == "/")
                writefile << "<Term Prime> -> *<Factor><Term Prime> | /<Factor><Term Prime> | ε" << endl;


              if(t == "(")
                writefile << "<Factor> -> (<Expression>) | <ID>" << endl;


              if(t == ")")
                writefile << "<Factor> -> (<Expression>) | <ID>" << endl;


              if(t == "id")
                writefile << "<ID> -> id" << endl;


              if(t == "=")
                writefile << "<Assignment> -> <ID> = <Expression>" << endl;


              if(t == "int")
                writefile << "<Type> -> int | bool | string | float" << endl;


              if(t == "bool")
                writefile << "<Type> -> int | bool | string | float" << endl;


              if(t == "string")
                writefile << "<Type> -> int | bool | string | float" << endl;


              if(t == "float")
                writefile << "<Type> -> int | bool | string | float" << endl;


            s.pop();                //pop top of stack
            counter++;              //move to next iteration
          }
          else
            cout << "An error has occurred" << endl;
        }
        else
          {
            if(t=="E")
              p=1;
            if(t=="Q")
              p=2;
            if(t=="T")
              p=3;
            if(t=="X")
              p=4;
            if(t=="F")
              p=5;
            if(t=="I")
              p=6;
            if(t=="S")
              p=7;
            if(t=="A")
              p=8;
            if(t=="D")
              p=9;
            if(t=="Y")
              p=10;

            if(t=="+")
              q=1;
            if(t=="-")
              q=2;
            if(t=="*")
              q=3;
            if(t=="/")
              q=4;
            if(t=="(")
              q=5;
            if(t==")")
              q=6;
            if(t=="id")
              q=7;
            if(t=="=")
              q=8;
            if(t=="int")
              q=9;
            if(t=="bool")
              q=10;
            if(t=="string")
              q=11;
            if(t=="float")
              q=12;
            if(t=="$")
              q=13;

            if(i=="E")
              p=1;
            if(i=="Q")
              p=2;
            if(i=="T")
              p=3;
            if(i=="X")
              p=4;
            if(i=="F")
              p=5;
            if(i=="I")
              p=6;
            if(i=="S")
              p=7;
            if(i=="A")
              p=8;
            if(i=="D")
              p=9;
            if(i=="Y")
              p=10;

            if(i=="+")
              q=1;
            if(i=="-")
              q=2;
            if(i=="*")
              q=3;
            if(i=="/")
              q=4;
            if(i=="(")
              q=5;
            if(i==")")
              q=6;
            if(i=="id")
              q=7;
            if(i=="=")
              q=8;
            if(i=="int")
              q=9;
            if(i=="bool")
              q=10;
            if(i=="string")
              q=11;
            if(i=="float")
              q=12;
            if(i=="$")
              q=13;

            if(table[p][q] != empty)             //if theres something in table[t,i]
            {
              s.pop();                                  //pop TOS
              string tmp = table[p][q];                  //get string in tabel[t,i]
              for(int w = (tmp.size())-1; w >= 0; --w)      //iterate from back to front
              {
                char k=tmp[w];
                s.push(k);                        //push i onto stack
              }
            }
            else
              cout << "An Error has occurred"<< endl;
          }
        } while(s.empty() != true );                 //all while stack is not empty
      }

    writefile.close();                              //close file

  return 0;
}

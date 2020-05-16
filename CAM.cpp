#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Symbol_table
{
  private:
    string identifer;
    int memloc;
    string type;
  public:
    void init(string i,int m,string t)
    {
      identifer = i;
      memloc = m;
      type = t;
    }

    void print()
    {
      cout << identifer << "   " << memloc << "   " << type << endl;
    }
}

stack<int> jumpstack;

Symbol_table array[1000];
int instr_address = 0;
string token;
int index=0;
string id;

void A ()
{
  if (token[index] == id)
  {
    string save = token;
    lexer();
    if (token[index] == "=")
    {
      lexer();
      E();
      get_instr ("POPM", get_address(save));
    }
    else
      error_message("= expected");
  }
  else
    error_massage("id expected");
}

void E ()
{
  T();
  Q();
}

void Q()
{
  if (token[index] == "+")
  {
    lexer();
    T();
    gen_instr("ADD", 0000);
    Q();
  }
};

void T()
{
  F();
  Y();
}

void Y()
{
  if (token[index] == "*")
  {
    lexer();
    F();
    gen_instr("MUL", 0000);
    Y();
  }
}

void F()
{
  if (token[index] == id)
  {
    gen_instr("PUSHM", get_address(token));
    lexer();
  }
else
  error_message("id expected");
};

void gen_instr(op, oprnd)
{
/* instr_address  shows the current insturction address is global */
  instr_table[instr_address].address = inst_address;
  instr_table[instr_address].op = op;
  instr_table[instr_address].oprnd = oprnd;
  instr_address++;
};

void while_statement()
{
  if (token[index] == "while")
  {
    addr = instr_address;
    gen_instr("LABEL", 0000);
    lexer();
    if (token[index] == "(")
    {
      lexer();
      C();
      if (token[index] == ")")
      {
        lexer();
        S();
        gen_instr(JUMP, addr);
        back_patch (instr_address);
        if (token[index] == “whileend”)
        {
          lexer();
        }
        else
        {
          error_message (“whileend expected”);
        }
      }
      else
      {
        error_message (“ ) expected”);
      }
    }
    else
    {
      error_message (“( expected”);
    }
    }
  else
  {
    error_message (“while expected”);
  }
}

void C()
{
  E();
  if (token in R)
  {
    op = token;
    lexer();
    E();
    case op of
    < : gen_instr (LES, nil);
    push_jumpstack(instr_address);/* another stack need */
    gen_instr (JUMPZ, nil);
    >      :/* you need to do other operators*/
    ==:
    ^=:
    etc.
  }case
  else
  {
    error_message (“ R token expected”);
  }
}

void back_patch (jump_addr)
{
  addr = pop_jumpstack();
  Instr_table[addr].oprn = jump_addr;
}

void I ()
{
  if (token[index] ==”if”)
  {
    addr= instr_address();
    lexer();
    if (token[index] ==”(“)
    {
      lexer();
      C();
      if (token[index] == “)”)
      {
        lexer();
        S();
        back_patch(instr_address);
        if (token[index] == “ifend”)
        {
          lexer();
        }
        else
        {
          error_messgage (“ifendexpected “);
        }
      }
      else
      {
        error_message (“) expected “);
      }
    }
    else{
      error_message (“(expected”);
    }
  }
  else
  {
    error_message (“if  expected”);
  }
}

void lexer(){
  index++;
}

int main()
{
  string msg = "! this is comment for this sample code\n for assignment 3 !\n int i, max, sum; \n sum = 0; \n i = 1; \n input ( max); \n while (i < max) { \n sum = sum + i; \n i = i + 1; \n } \n output (sum + max);"
  cout << msg << endl;

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

  return 0;
}

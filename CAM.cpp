#include <iostream>
using namespace std;

void A (){
  if (token == id){
    save = token;
    lexer();
    if (token == “=”){
      lexer();
      E();
      get_instr (POPM,get_address (save) );
    }
    else
      error_message (“= expected”);
  }
  else
    error_massage (“ id expected”);
}

void E (){
  T();
  Q();
}

void Q(){
  if (token == “+”){
    lexer();
    T();
    gen_instr(ADD, nil);
    Q();
  }
};

void T(){
  F();
  Y();
}

void Y(){
  if (token == “*”){
    lexer();
    F();
    gen_instr(MUL, nil);
    Y();
  }
}

void F(){
  if (token == id){
    gen_instr(PUSHM, get_address (token));
    lexer();
  }
else
  error_message(“id expected”);
};

void gen_instr(op, oprnd){
/* instr_address  shows the current insturction address is global */
  Instr_table [instr_address].address = inst_address;
  Instr_table [instr_address].op = op;
  Instr_table [instr_address].oprnd = oprnd;
  Instr_address++;
};

void while_statement(){
  if (token == “while”){
    addr= instr_address;
    gen_instr(“LABEL”, nil);
    lexer();
    if (token == “(“){
      lexer();
      C();
      if (token == “)”){
        lexer();
        S();
        gen_instr(JUMP, addr);
        back_patch (instr_address);
        if (token == “whileend”){
          lexer();
        }
        else{
          error_message (“whileend expected”);
        }
      }
      else{
        error_message (“ ) expected”);
      }
    }
    else{
      error_message (“( expected”);
    }
    }
  else{
    error_message (“while expected”);
  }
}

void C(){
  E();
  if (token in R){
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
  else{
    error_message (“ R token expected”);
  }
}

void back_patch (jump_addr){
  addr = pop_jumpstack();
  Instr_table[addr].oprn = jump_addr;
}

void I (){
  if (token ==”if”){
    addr= instr_address();
    lexer();
    if (token ==”(“){
      lexer();
      C();
      if (token == “)”){
        lexer();
        S();
        back_patch(instr_address);
        if (token == “ifend”){
          lexer();
        }
        else{
          error_messgage (“ifendexpected “);
        }
      }
      else{
        error_message (“) expected “);
      }
    }
    else{
      error_message (“(expected”);
    }
  }
  else{
    error_message (“if  expected”);
  }
}

int main(){



return 0;
}

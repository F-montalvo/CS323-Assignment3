#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""

@author: Alberto Perez and Francisco Montalvo

"""
import keyword                                                                  #allows for a list of keywords to be used

temp =''                                                                        #holds the parsed words
lex={}                                                                          #holds the completed list of tokens and lexemes
comment = False                                                                 #keeps track of if the word is a part of a comment 

with open('test.txt', 'r') as f:                                                #reads from a file 
    while True:
        c = f.read(1)
        if c == ',' or c == ';' or c == '(' or c == ')' or c == '{' or c == '}':            #checking for separators 
             if keyword.iskeyword(temp):
                lex[temp] = 'KEYWORD'
                temp = ''
             elif temp.isnumeric():
                lex[temp] = 'NUMBER'
                temp = ''
             else:
                lex[temp] = 'IDENTIFIER'
                temp = ''
             temp = c
             lex[temp] = 'SEPARATOR'
             temp = ''
             continue
        if c == ' ' or c== '\n' or  c== '\t':
            if keyword.iskeyword(temp) or temp == 'int' or temp == 'string' or temp == 'float' or temp == 'bool': #checking for keywords
                lex[temp] = 'KEYWORD'
                temp = ''
                continue
            if temp.isnumeric():
                lex[temp] = 'NUMBER'
                temp = ''
                continue
            if temp == '':
                continue
            lex[temp] = 'IDENTIFIER'
            temp = ''
            continue
        if c == '*' or c == '+' or c == '-' or c == '=' or c == '/' or c == '>' or c == '<' or c == '%':
            lex[c] = 'OPERATOR'
            continue
        if not c:                                                               #checking for end of input 
            break
        if c == '!' and comment == True:                                        #checking for end of comment
            comment = False
            continue
        elif c == '!':                                                          #checking for start of comment
            comment = True
            continue
        elif comment == True:                                                   #checking for comment content
            continue   
        temp= temp + c

f.close()

file = open('output.txt', 'w')                                                  #opens/creates output.txt

file.write('Token:          ')                                                  #writing and formatting 
file.write('Lexemes:' + '\n')                                                   #writing and formatting 
for n in lex:                                                                   #loop and write everything in lex
    tmp = (f'{lex[n]:15} {n:5}') + '\n'                                         #format the text before writing
    file.write(tmp)                                                             #write to file
    
file.close()

print("Lexical Analysis Completed")
print("Press Enter to Continue")
input()
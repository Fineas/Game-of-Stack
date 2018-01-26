#!/usr/bin/env python2.7

from collections import deque, namedtuple
from prettytable import PrettyTable
import time

stack = deque()
t = PrettyTable(['Address', 'Value'])
#f = open("data_in")
#g = open("data_out", 'w')
#data = f.read()
#data = data.split()
option = counter = 0;
addr = 0x0
READ = 1;DUP = 2;ADD = 3;MUL = 4;WRITE = 5;PRINT = 6;EXIT = 7;

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass
    return False

def welcome():
    print '=================================='
    print '=    WELCOME TO GAME OF STACK    ='
    print '=================================='

def menu():
    print '= [1]READ'
    print '= [2]DUP'
    print '= [3]ADD'
    print '= [4]MUL'
    print '= [5]WRITE'
    print '= [6]PRINT STACK'
    print '= [7]EXIT'

if __name__ == "__main__":
    #start_time = time.time()
    welcome()

    while True:
        menu()
        option = raw_input(">>")
        #option = data[counter]
        #counter += 1
        if len(option) == 0:
            print '\n= [*]Unknown option, enter on of the above.\n'
            continue
        option = int(option, 10)

        # PUSH <integer> pushes <integer> on the stack;
        if option == READ:
            value = raw_input("\n= [*]Enter a value: ")
            #value = data[counter]
            #counter += 1
            print '\n'
            if not is_number(value ):
                print '\n= [*]Please enter a valid integer\n'
                continue
            else:
                stack.append(int(value, 10))
                addr += 1
                t.add_row([hex(addr), value])

        # DUP pushes a copy of the stack head on the stack;
        elif option == DUP:
                if addr < 1:
                    print '\n[*]Not enough elements on the stack to perform this action\n'
                else:
                    stack.append(stack[addr-1])
                    addr += 1
                    t.add_row([hex(addr), stack[addr-2]])

        # ADD pops two elements from the stack and pushes their sum on the stack
        elif option == ADD:
            if addr < 2:
                print '\n[*]Not enough elements on the stack to perform this action\n'
            else:
                temp_sum = stack.pop()
                temp_sum += stack.pop()
                addr -= 1
                stack.append(temp_sum)
                t.del_row(addr)
                t.del_row(addr-1)
                t.add_row([hex(addr), temp_sum])

        # MUL pops two elements from the stack and pushes their product on the stack
        elif option == MUL:
            if addr < 2:
                print '\n[*]Not enough elements on the stack to perform this action\n'
            else:
                temp_product = stack.pop()
                temp_product *= stack.pop()
                addr -= 1
                stack.append(temp_product)
                t.del_row(addr)
                t.del_row(addr-1)
                t.add_row([hex(addr), temp_product])

        # WRITE pops an integer value from the stack and prints it on stdout
        elif option == WRITE:
            if addr < 1:
                print '\n[*]Not enough elements on the stack to perform this action\n'
            else:
                temp_num = stack.pop()
                addr -= 1
                t.del_row(addr)
                print '\n[*]POPed element',temp_num,'\n'

        # PRINT STACK
        elif option == PRINT:
            print '\n',t,'\n'

        # EXIT
        elif option == EXIT:

            #g.write("--- %s seconds ---" % (time.time() - start_time))
            print '\n= [*]Bye-Bye!\n'
            break

        else:
            print '\n= [*]Unknown option, enter on of the above.\n'

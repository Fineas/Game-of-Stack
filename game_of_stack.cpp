#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct stack_CHUNK{
    stack_CHUNK *FD;
    size_t value;
} *stack_baddr, *stack_pointer; // Pointer to the beg of the list & to the end of the list (margins)

size_t option;
size_t num_of_elements;

// Initiate Global variables
void init(){
    stack_baddr = stack_pointer = nullptr;
    option = num_of_elements = 0;
}

// Because the Stack is LIFO, only at the end can be concatenated a new element
void create_stack_element(int content){
  stack_CHUNK *aux;
  // Yet, no elements in the list
  if(stack_baddr == nullptr){
    stack_baddr = new stack_CHUNK;
    (*stack_baddr).value = content;
    (*stack_baddr).FD = nullptr;
    stack_pointer = stack_baddr;
    num_of_elements++;
  }
  // Concatenate new element to the list
  else{
    aux = new stack_CHUNK;
    (*aux).value = content;
    (*aux).FD = nullptr;
    (*stack_pointer).FD = aux;
    stack_pointer = aux;
    num_of_elements++;
  }
}

// Iterate trough the list
static stack_CHUNK* get_penultimate_stack_element(){
  stack_CHUNK *aux;
  for(aux = stack_baddr; aux != nullptr; aux = (*aux).FD){
    if((*(*aux).FD).FD == nullptr){
      return aux;
    }
  }
}

// Because the Stack is LIFO, only the last element can be removed
static void api_pop(){
  if(stack_pointer == nullptr){
    cout << "[*] The Stack is empty" << endl;
  }
  // If there is just one element in the stack
  else if(stack_pointer == stack_baddr){
    delete stack_pointer;
    stack_pointer = stack_baddr = nullptr;
  }
  else{
    stack_CHUNK *aux = get_penultimate_stack_element();
    (*aux).FD = nullptr;
    delete stack_pointer;
    stack_pointer = aux;
  }
}

void stk_print(){
  // The list is empty
  if(stack_pointer == nullptr){
    cout << endl << "[*] Empty Stack" << endl << endl;
  }
  else{
    stack_CHUNK *aux;
    cout << endl << "=========" << endl;
    cout << "THE STACK" << endl;
    for(aux = stack_baddr; aux != nullptr; aux = (*aux).FD){
      cout << (*aux).value << endl;
    }
    cout << "=========" << endl << endl;
  }
}

// Display the interactive MENU
void interactive_menu(){
    cout << "[1] READ" << endl;
    cout << "[2] DUP"<< endl;
    cout << "[3] ADD"<< endl;
    cout << "[4] MUL"<< endl;
    cout << "[5] WRITE"<< endl;
    cout << "[6] PRINT STACK"<< endl;
    cout << "[7] EXIT"<< endl;

    cout << ">> ";cin >> option;
}

// 1. PUSH <integer> pushes <integer> on the stack;
static void api_push(int content){
    create_stack_element(content);
}

 // 2. DUP pushes a copy of the stack head on the stack;
void stk_dup(){
  if(stack_baddr == nullptr){
    cout << endl << "[*] The Stack is empty." << endl << endl;
  }
  else{
    stack_CHUNK *aux;
    aux = new stack_CHUNK;
    (*aux).value = (*stack_pointer).value;
    (*aux).FD = nullptr;
    (*stack_pointer).FD = aux;
    stack_pointer = aux;
    num_of_elements++;
  }
}

 // 3. ADD pops two elements from the stack and pushes their sum on the stack
void stk_add(){
  if(stack_baddr == nullptr || stack_pointer == stack_baddr){
    cout << endl << "[*] There aren't at least 2 elements on the stack" << endl << endl;
  }
  else{
    size_t sum = 0;
    stack_CHUNK *aux = get_penultimate_stack_element();
    sum += (*aux).value + (*(*aux).FD).value;
    api_pop();
    api_pop();
    cout << endl << "[*] The sum is " << sum << endl << endl;
    create_stack_element(sum);
  }
}

// 4. MUL pops two elements from the stack and pushes their product on the stack
void stk_mul(){
  if(stack_baddr == nullptr || stack_pointer == stack_baddr){
    cout << endl << "[*] There aren't at least 2 elements on the stack"<< endl << endl;
  }
  else{
    size_t product = 0;
    stack_CHUNK *aux = get_penultimate_stack_element();
    product += (*aux).value * (*(*aux).FD).value;
    api_pop();
    api_pop();
    cout << endl << "[*] The product is " << product << endl << endl;
    create_stack_element(product);
  }
}

// 5. READ reads an integer from stdin and pushes this value on the stack
void stk_read(){
  size_t aux;
  cout << endl << "[*] Enter the value to push to stak: ";cin >> aux;
  create_stack_element(aux);
}

// 6. WRITE pops an integer value from the stack and prints it on stdout
void stk_write(){
  if(stack_baddr == nullptr){
    cout << endl << "[*] The Stack is empty" << endl << endl;
  }
  else if(stack_baddr == stack_pointer){
    cout << endl << "[*] The poped value from the stack was " << (*stack_pointer).value << endl << endl;
    api_pop();
  }
  else{
    stack_CHUNK *aux = get_penultimate_stack_element();
    cout << endl << "[*] The poped value from the stack was " << (*(*aux).FD).value << endl << endl;
    api_pop();
  }
}

int main(){
    init();
    size_t aux;
    // Take action
    while(true){
        interactive_menu();
        switch(option){
            case 1:
                stk_read();
                break;
            case 2:
                stk_dup();
                break;
            case 3:
                stk_add();
                break;
            case 4:
                stk_mul();
                break;
            case 5:
                stk_write();
                break;
            case 6:
                stk_print();
                break;
            case 7:
                cout << "[*] Good-Bye!" << endl;
                exit(0);
                break;
            default:
                cout << "Unknown option" << endl;
                break;
        }
        // PRINT STACK
        //print_stack();
    }

}

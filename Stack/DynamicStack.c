#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct ElementStack* PtrElementStack;

typedef struct ElementStack{
    int value;
    PtrElementStack next;
} ElementStack;

typedef struct DynamicStack {
    int size;
    PtrElementStack top;
};

int size( const DynamicStack* stack ){
    return stack->size;
}

bool isEmpty( const DynamicStack* stack ){
    return stack->size == 0;
}

void init( DynamicStack* stack ){
    stack->size = 0;
    stack->top = NULL;
}

void push( DynamicStack* stack, const int value ){

    PtrElementStack newElement = ( PtrElementStack )malloc( sizeof( ElementStack ) );
    newElement->value = value;
    newElement->next = stack->top;
    stack->top = newElement;
    stack->size++;

}

int pop( DynamicStack* stack ){

    if( isEmpty( stack ) ){
        printf("The stack is Empty!");
        return -1;
    }

    PtrElementStack aux = stack->top;
    stack->top = stack->top->next;
    stack->size--;

    const int valueRemoved = aux->value;
    free( aux );
    return valueRemoved;

}

int top( const DynamicStack* stack ) {

    if( isEmpty( stack ) ){
        printf("The stack is Empty!");
        return -1;
    }

    return stack->top->value;

}

bool hasValue( const DynamicStack* stack, const int value ){

    if( isEmpty( stack ) ){
        printf("The stack is Empty!");
        return false;
    }

    PtrElementStack aux = stack->top;

    while( aux ){

        if( aux->value == value ){
            return true;
        }

        aux = aux->next;
    }

    return false;

}

int main() {

    DynamicStack stack;
    init(&stack);

    push( &stack, 2 );
    assert( top( &stack ) == 2 );

    push( &stack, 4 );
    assert( top( &stack ) == 4 );

    assert( pop( &stack ) == 4 );

    assert( size( &stack ) == 1 );

    assert( hasValue( &stack, 2 ) == true );

    assert( pop( &stack ) == 2 );

    push( &stack, 8 );
    assert( top( &stack ) == 8 );

    push( &stack, 5 );
    assert( top( &stack ) == 5 );

    push( &stack, 9 );
    assert( top( &stack ) == 9 );

    return 0;
}

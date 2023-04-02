#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define NR_SIZE_PILHA 3

typedef struct StaticStack {
    int vector[NR_SIZE_PILHA];
    int top;
} StaticStack;

void init( StaticStack* stack ){
    stack->top = 0;
}

bool isEmpty( const StaticStack* stack ){
    return stack->top == 0;
}

bool isFull( const StaticStack* stack ){
    return stack->top == NR_SIZE_PILHA;
}

int length( const StaticStack* stack ){
    return stack->top;
}

void push( StaticStack* stack, const int value ){

    if( isFull( stack ) ){
        printf("The stack is full!");
        return;
    }

    stack->vector[stack->top] = value;
    stack->top++;
}

int pop( StaticStack* stack ){

    if( isEmpty( stack ) ){
        printf("The stack is empty!");
        return -1;
    }

    const int value = stack->vector[ stack->top - 1 ];
    stack->top--;
    return value;
}

int top( const StaticStack* stack ){

    if( isEmpty( stack ) ){
        printf("The stack is empty!");
        return -1;
    }

    return stack->vector[ stack->top - 1 ];
}

bool hasValue( StaticStack* stack, const int value ){

    for( int index = 0; index < stack->top; index++ ){
        if( stack->vector[index] == value ){
            return true;
        }
    }

    return false;
}

int main() {

    StaticStack stack;
    init(&stack);

    push( &stack, 2 );
    assert( top( &stack ) == 2 );

    push( &stack, 4 );
    assert( top( &stack ) == 4 );

    assert( pop( &stack ) == 4 );

    assert( length( &stack ) == 1 );

    assert( hasValue( &stack, 2 ) == true );

    assert( pop( &stack ) == 2 );

    push( &stack, 8 );
    assert( top( &stack ) == 8 );

    push( &stack, 5 );
    assert( top( &stack ) == 5 );

    push( &stack, 9 );
    assert( top( &stack ) == 9 );

    assert( isFull( &stack ) == true );

    return 0;
}

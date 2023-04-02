#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct ElementQueue* PtrElementQueue;

typedef struct ElementQueue{
    int value;
    PtrElementQueue next;
} ElementQueue;

typedef struct {
    PtrElementQueue first;
    PtrElementQueue last;
    int size;
} DynamicQueue;

void init( DynamicQueue* queue ){
    queue->first = NULL;
    queue->last = NULL;
    queue->size = 0;
}

bool isEmpty( const DynamicQueue* queue ){
    return queue->size == 0;
}

int size( const DynamicQueue* queue ){
    return queue->size;
}

void push( DynamicQueue* queue, const int value ){

    PtrElementQueue newElement = ( PtrElementQueue )malloc( sizeof( ElementQueue ) );
    newElement->next = NULL;
    newElement->value = value;

    if( isEmpty( queue ) ){
        queue->first = newElement;
    } else {
        queue->last->next = newElement;
    }

    queue->last = newElement;
    queue->size++;

}

int pop( DynamicQueue* queue ){

    if( isEmpty( queue ) ){
        printf("The queue is Empty!");
        return -1;
    }

    PtrElementQueue aux = queue->first;
    queue->first = aux->next;
    queue->size--;

    int removeValue = aux->value;
    free( aux );

    return removeValue;

}

int firstValue( const DynamicQueue* queue ){

    if( isEmpty( queue ) ){
        printf("The queue is Empty!");
        return -1;
    }

    return queue->first->value;

}

int lastValue( const DynamicQueue* queue ){

    if( isEmpty( queue ) ){
        printf("The queue is Empty!");
        return -1;
    }

    return queue->last->value;

}

int find( const DynamicQueue* queue, const int value, bool* hasValue ){

    if( isEmpty( queue ) ){
        printf("The queue is Empty!");
        *hasValue = false;
        return -1;
    }

    PtrElementQueue aux = queue->first;

    while( aux ){

        if( aux->value == value ){
            *hasValue = true;
            return value;
        }

        aux = aux->next;
    }

    *hasValue = false;
    return -1;

}


int main(){

    DynamicQueue queue;
    init( &queue );

    assert( isEmpty( &queue ) == true );

    push( &queue, 10 );
    assert( firstValue( &queue ) == 10 );
    assert( lastValue( &queue ) == 10 );

    push( &queue, 9 );
    assert( firstValue( &queue ) == 10 );
    assert( lastValue( &queue ) == 9 );

    push( &queue, 8 );
    assert( firstValue( &queue ) == 10 );
    assert( lastValue( &queue ) == 8 );

    push( &queue, 7 );
    assert( firstValue( &queue ) == 10 );
    assert( lastValue( &queue ) == 7 );

    push( &queue, 6 );
    assert( firstValue( &queue ) == 10 );
    assert( lastValue( &queue ) == 6 );

    assert( isEmpty( &queue ) == false );

    assert( pop( &queue ) == 10 );
    assert( firstValue( &queue ) == 9 );

    assert( pop( &queue ) == 9 );
    assert( firstValue( &queue ) == 8 );

    assert( pop( &queue ) == 8 );
    assert( firstValue( &queue ) == 7 );

    push( &queue, 10 );
    assert( firstValue( &queue ) == 7 );
    assert( lastValue( &queue ) == 10 );

    bool hasValue = false;

    assert( find( &queue, 10, &hasValue ) == 10 );
    assert( hasValue == true );

    assert( find( &queue, 25, &hasValue ) == -1 );
    assert( hasValue == false );

    return 0;
}

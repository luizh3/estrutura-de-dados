#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define NR_SIZE_QUEUE 5

typedef struct {
    int vector[NR_SIZE_QUEUE];
    int nrIndexFirst;
    int nrIndexEnd;
    int size;
} StaticQueue;

void init( StaticQueue* queue ){
    queue->nrIndexFirst = 0;
    queue->nrIndexEnd = -1;
    queue->size = 0;
}

bool isEmpty( const StaticQueue* queue ){
    return queue->size == 0;
}

bool isFull( const StaticQueue* queue ){
    return queue->size == NR_SIZE_QUEUE;
}

int size( const StaticQueue* queue ){
    return queue->size;
}

int firstValue( const StaticQueue* queue ){
    return queue->vector[ queue->nrIndexFirst ];
}

int lastValue( const StaticQueue* queue ){
    return queue->vector[ queue->nrIndexEnd ];
}

int nextIndex( const int nrActualIndex ){

    if( nrActualIndex == ( NR_SIZE_QUEUE - 1 ) ){
        return 0;
    }

    return nrActualIndex + 1;
}

void push( StaticQueue* queue, const int value ){

    if( isFull( queue ) ){
        printf("The queue is full!");
        return;
    }

    const int nrIndexNextEnd = nextIndex( queue->nrIndexEnd );
    queue->nrIndexEnd = nrIndexNextEnd;

    queue->vector[nrIndexNextEnd] = value;
    queue->size++;

}

int pop( StaticQueue* queue ){

    if( isEmpty( queue ) ){
        printf("The queue is Empty");
        return -1;
    }

    int valueRemoved = queue->vector[queue->nrIndexFirst];
    queue->nrIndexFirst = nextIndex( queue->nrIndexFirst );
    queue->size--;

    return valueRemoved;
}

int find( const StaticQueue* queue, const int value, bool* hasValue ) {

    int index = queue->nrIndexFirst;

    while( index != queue->nrIndexEnd ){

        if( value == queue->vector[index] ){
            *hasValue = true;
            return value;
        }

        index++;
    }

    *hasValue = false;
    return -1;
}

int main(){

    StaticQueue queue;
    init( &queue );

    assert( isEmpty( &queue ) == true );
    assert( isFull( &queue ) == false );

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

    assert( isFull( &queue ) == true );
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

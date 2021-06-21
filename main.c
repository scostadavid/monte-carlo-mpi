#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
 
int main (int argc, char* argv[]) {

    pid_t rank;
    int size;

    MPI_Init (&argc, &argv);      /* starts MPI */
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
    MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
    printf( "Hello world from process %d of %d\n", rank, size );
    MPI_Finalize();
    
    return 0;
}
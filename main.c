#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#define SERVER_RANK 0

int foo(int n) {
    return n*n;
}

void main (int argc, char* argv[]) {

    pid_t process_rank;
    int src_rank;

    int number_of_processes, msg_tag;
    MPI_Status status;

    int buffer = 0;
    
    int n = 2;
    int sum = 0;

    MPI_Init (&argc, &argv);

    MPI_Comm_size (MPI_COMM_WORLD, &number_of_processes);
    MPI_Comm_rank (MPI_COMM_WORLD, &process_rank);

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (process_rank == SERVER_RANK) {
        for (src_rank = 1; src_rank < number_of_processes; src_rank++) {
            msg_tag = 0;
            MPI_Recv(&buffer, 1, MPI_INT, src_rank, msg_tag, MPI_COMM_WORLD, &status);
            sum += buffer;
        }
    } 
    else { //clients
        msg_tag = 0;
        int ret = foo(n);
        MPI_Send(&ret, 1, MPI_INT, SERVER_RANK, msg_tag, MPI_COMM_WORLD);
    }
        
    if(process_rank == SERVER_RANK) {

        printf("\nsoma: %d\n", sum);
    }
    MPI_Finalize();
}

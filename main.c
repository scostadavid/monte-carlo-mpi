#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include "src/montecarlo.h"
#include <unistd.h>

#define SERVER_RANK 0

int main (int argc, char* argv[]) {

    MPI_Status status;
    
    pid_t process_rank;
    int src_rank;
    int number_of_processes;
    int msg_tag;
    int n = 100000;

    double buffer = 0;
    double pi = 0;
    double sum = 0;
    
    srand(time(NULL));
    MPI_Init (&argc, &argv);

    MPI_Comm_size (MPI_COMM_WORLD, &number_of_processes);
    MPI_Comm_rank (MPI_COMM_WORLD, &process_rank);

    // Server broadcast
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (process_rank == SERVER_RANK) {
        for (src_rank = 1; src_rank < number_of_processes; src_rank++) {
            msg_tag = 0;
            MPI_Recv(&buffer, 1, MPI_DOUBLE, src_rank, msg_tag, MPI_COMM_WORLD, &status);
            sum += buffer;
        }
    } 
    else { //clients
        msg_tag = 0;
        pi = monte_carlo_pi(n);
        MPI_Send(&pi, 1, MPI_DOUBLE, SERVER_RANK, msg_tag, MPI_COMM_WORLD);
    }
        
    if(process_rank == SERVER_RANK) {
        printf("\nsoma: %lf\n", sum / (number_of_processes - 1));
    }

    MPI_Finalize();

    return 0;
}

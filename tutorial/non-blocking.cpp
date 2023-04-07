#include <iostream>
#include <mpi.h>
#include <cstdlib>
#include <ostream>
#include <unistd.h>

int main(int argc, char **argv) {

  MPI_Init(&argc,&argv);
  MPI_Request request,request2;
  MPI_Status  status,status2;
  int request_finished = 0,request_finished2=0;

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int buffer_count=10;
  int buffer[buffer_count];

  // Initialising buffer :
  for (int i=0; i < buffer_count; ++i)
    buffer[i] = (rank == 0 ? i*2 : 0);

  MPI_Barrier(MPI_COMM_WORLD);
  // Starting the chronometer
  double time = -MPI_Wtime(); // This command helps us measure time. We will see more about it later on !

  
  ////////// You should not modify anything BEFORE this point //////////
 
  if (rank == 0) {
    sleep(3);

    // 1- Initialise the non-blocking send to process 1
    MPI_Isend(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);

    double time_left = 6000.0;
    while (time_left > 0.0) {
      usleep(1000); // We work for 1ms

      // 2- Test if the request is finished (only if not already finished)
      if (!request_finished)
        MPI_Test(&request, &request_finished, &status);

      // 1ms left to work
      time_left -= 1000.0;
    }

    // 3- If the request is not yet complete, wait here.
    if (!request_finished)
      MPI_Wait(&request, &status);
  
    // Modifying the buffer for second step
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = -i;

    // 4- Prepare another request for process 1 with a different tag
    MPI_Isend(buffer, buffer_count, MPI_INT, 1, 5, MPI_COMM_WORLD, &request2);
    
    time_left = 3000.0;
    while (time_left > 0.0) {
      usleep(1000); // We work for 1ms

      // 5- Test if the request is finished (only if not already finished)
      if(!request_finished2)
        MPI_Test(&request2, &request_finished2, &status2);

      // 1ms left to work
      time_left -= 1000.0;
    }
    // 6- Wait for it to finish
    if(!request_finished2)
      MPI_Wait(&request, &status2);
    
  }
  else {
    // Work for 5 seconds
    sleep(5);

    // 7- Initialise the non-blocking receive from process 0
    MPI_Irecv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

    // 8- Wait here for the request to be completed
    MPI_Wait(&request, &status);

    std::cout<<"Buffer is ";
    for (int i=0;i<buffer_count;i++){
      std::cout<<buffer[i]<<" ";
    }
    std::cout<<std::endl;
    
    // Work for 3 seconds
    sleep(3);

    // 9- Initialise another non-blocking receive
    MPI_Irecv(buffer, buffer_count, MPI_INT,0, 5, MPI_COMM_WORLD, &request2);
    
    // 10- Wait for it to be completed
    MPI_Wait(&request2, &status2);

    std::cout << "Buffer is ";
    for (int i=0; i<buffer_count; i++) {
      std::cout<<buffer[i]<<" ";
        }
    std::cout<<std::endl;
  }
  ////////// should not modify anything AFTER this point //////////

  // Stopping the chronometer
  time += MPI_Wtime();

  // This line gives us the maximum time elapsed on each process.
  // We will see about reduction later on !
  double final_time;
  MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  
  if (rank == 0)
    std::cout << "Total time for non-blocking scenario : " << final_time << "s" << std::endl;

  MPI_Finalize();
}

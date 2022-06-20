#include <string>
#include <mpi.h>
#include <assert.h>
#include "randomizer.hpp"
#include <bits/stdc++.h>
#include<chrono>
using namespace std;
using namespace std::chrono;


bool sortmypairs(pair<int, int> &a, pair<int, int> &b){
    return ((a.second != b.second) ? (a.second > b.second) : (a.first < b.first));
}

int main(int argc, char *argv[]){

    auto start = high_resolution_clock::now();
    assert(argc > 8);
    std::string graph_file = argv[1];
    int num_nodes = std::stoi(argv[2]);
    int num_edges = std::stoi(argv[3]);
    float restart_prob = std::stof(argv[4]);
    int num_steps = std::stoi(argv[5]);
    int num_walks = std::stoi(argv[6]);
    int num_rec = std::stoi(argv[7]);
    int seed = std::stoi(argv[8]);

    vector<int> gr[num_nodes]; // initializing vector of vector
    // for (int i = 0; i < num_nodes; i++){
    //     vector<int> node_info;
    //     gr.push_back(node_info);
    // }

    FILE *f_reader;
    int rep;
    unsigned char source[4], destination[4]; // forming the buffers for storing the value of the two integers
    f_reader = fopen((const char *)graph_file.c_str(),"rb");
    //int count =0;
    while (feof(f_reader) == 0){
        fread(&source, 1, 4, f_reader);
        fread(&destination, 1, 4, f_reader);
         int s1 = (int)source[3];
         int d1 = (int)destination[3];
         int s2 = ((int)source[2]) << 8;
         int d2 = ((int)destination[2]) << 8;
         int s3 = ((int)source[1]) << 16;
         int d3 = ((int)destination[1]) << 16;
         int s4 = ((int)source[0]) << 24;
         int d4 = ((int)destination[0]) << 24; // defining values to read bigindian // putting the values in our graph
        gr[(s1 | s2 | s3 | s4)].push_back(d1 | d2 | d3 | d4);
        rep = s1 | s2 | s3 | s4; // cout<<(s1|s2|s3|s4)<<" "<<(d1|d2|d3|d4)<<"\n";
      //  count++;
    }
    gr[rep].pop_back();
    // for (int i : gr[8716]){
    //     cout<<i<<" ";
    // }
    fclose(f_reader);
   // cout<<count;
    // Starting MPI pipeline
    MPI_Init(NULL, NULL);
    // Only one randomizer object should be used per MPI rank, and all should have same seed
    Randomizer random_generator(seed, num_nodes, restart_prob);
    int rank, size;
    // //Only one randomizer object should be used per MPI rank, and all should have same seed
    // Randomizer random_generator(seed, num_nodes, restart_prob);
    // int rank, size;
    // Starting MPI pipeline
    //  MPI_Init(NULL, NULL);
    // Extracting Rank and Processor Count
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    vector<int> startthread;
    for (int nt = 0; nt < size; nt++){
        startthread.push_back(nt *(int)(num_nodes / size));
    }
    vector<int> endthread;
    for (int nt = 0; nt < size; nt++){
        if (nt != size - 1){
            endthread.push_back(((nt + 1) *(int)(num_nodes / size) )-1 );
        }
        else{
            endthread.push_back(num_nodes-1);
        }
    }
    int mat_res[num_nodes][num_nodes];
    memset(mat_res, 0, sizeof(mat_res));
    for (int i = startthread[rank]; i <= endthread[rank]; i++){
        vector<int> adj = gr[i];
        for (int neighbor : adj){
            for (int j = 0; j < num_walks; j++){
                int ns = 0;
                int new_n = neighbor;
                while (ns < num_steps){
                    if (gr[new_n].size() > 0){
                        int next_one = random_generator.get_random_value(i);
                        if (next_one < 0){
                            new_n = neighbor;
                            ns++;
                        }
                        else{
                            int pw_index = (next_one) % gr[new_n].size();
                            new_n = gr[new_n][pw_index];
                            if (std::count(adj.begin(), adj.end(), new_n) == 0 && new_n != i)
                                mat_res[i][new_n]++;
                            ns++;
                        }
                    }
                    else{
                        new_n = neighbor;
                        ns++;
                    }
                }
            }
        }
    }
    // if (rank==3){
    //     for (int j =0; j<8717; j++){
    //         cout<<mat_res[8716][j]<<",";
    //     }
    // }
  //  vector<pair<int, int>> wtf[num_nodes];
    vector<int> wtf1[num_nodes];
    vector<int> wtf2[num_nodes];
    for (int i = startthread[rank]; i <= endthread[rank]; i++){
        vector<pair<int, int>> tres;
        for (int j = 0; j < num_nodes; j++){
            if (mat_res[i][j] != 0){
                tres.push_back(make_pair(j, mat_res[i][j]));
            }
        }
        sort(tres.begin(), tres.end(), sortmypairs);// wtf[i] = tres;
        int sz = tres.size();
        for (int o = 0; o < num_rec; o++){
          //  wtf[i].push_back(tres[o]);
          if(o<sz){
            wtf1[i].push_back(tres[o].first);
            wtf2[i].push_back(tres[o].second);

          }
          else{
            wtf1[i].push_back(-1);
            wtf2[i].push_back(-1);
            }
        }
    }
    if (rank != 0){
        for (int x = startthread[rank]; x <= endthread[rank]; x++){
            // cout<<x<<">>>>";
            // for(int i =0; i<wtf1[x].size(); i++){
            //      cout<<wtf1[x][i]<<","<<wtf2[x][i]<<" ";

            // }
            // cout<<"\n";
         //   MPI_Send(&wtf[x], sizeof(pair<int, int>) * wtf[x].size(), MPI_BYTE, 0, x, MPI_COMM_WORLD);
            //   if(x==8716){
            //      for(int i =0; i<wtf1[x].size(); i++)
            //           cout<<wtf1[x][i]<<" "<<wtf2[x][i]<<" ";
            //  }
            int num1 = wtf1[x].size();
            int num2 = wtf2[x].size();
           // int buffer[num_rec],buffer1[num_rec] ;
            MPI_Send(&wtf1[x][0], num_rec, MPI_INT, 0, x, MPI_COMM_WORLD);
            MPI_Send(&wtf2[x][0],num_rec, MPI_INT, 0, x, MPI_COMM_WORLD);
        }
    }
    if (rank == 0){
        for (int i = 1; i < size; i++){
            for (int k = startthread[i]; k <= endthread[i]; k++){// vector<pair<int, int>> buff;
              //  cout << k << " ";
               // MPI_Recv(&wtf[k], num_rec*sizeof(pair<int, int>), MPI_BYTE, i, k, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
               int buffer[num_rec],buffer1[num_rec] ;
                MPI_Recv(buffer, num_rec, MPI_INT, i, k, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(buffer1, num_rec, MPI_INT, i, k, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int p =0; p<num_rec; p++){
                    wtf1[k].push_back(buffer[p]);
                    wtf2[k].push_back(buffer1[p]);

                }
                // if(k==startthread[i]){
                //     for(int p =0; p<wtf1[k].size();p++){
                //         cout<<wtf1[k][p]<<" ";
                //     }
                // }

               // cout << "4"<< ",";// wtf[k] = buff;
            //    for(int p =0; p<wtf[k].size(); p++){
            //        cout<<wtf[k][p].first<<" "<<wtf[k][p].second;
            //    }
            //    cout<<"\n";
            }
          //  cout << "\n";
        }
       // cout<<"All recieved";
       string filename = "output.dat";
        const char *fs = filename.c_str();
        FILE* f_writer;
        f_writer = fopen(fs, "wb");//  cout<<"Hello";
        unsigned char source_writing[4], destination_writing[4];
        unsigned char null_source_writing[4], null_destination_writing[4];
        unsigned char size_writing[4];
        for (int n = 0; n < num_nodes; n++){// int num_gh  = gr[n].size();
            int recomm = wtf1[n].size();//  cout<<n<< " >>>>>";
           // if(n==0 || n==800 || n==2000|| n==2700 || n==5726 || n==7675){
            // cout<<n<<">>>>>>>";
            // for(int p =0; p<num_rec; p++){
            //     cout<<wtf1[n][p]<<" "<<wtf2[n][p]<<",";
            // }
            // cout<<"\n";
         //   }
            size_writing[3] = (gr[n].size() & 0xFF);
            size_writing[2] = (((gr[n].size()) >> 8) & 0xFF);
            size_writing[1] = (((gr[n].size()) >> 16) & 0xFF);
            size_writing[0] = (((gr[n].size()) >> 24) & 0xFF);
            fwrite(&size_writing, 1, 4, f_writer); 
            for (int i = 0; i < num_rec; i++){
               if (wtf1[n][i]!=-1){
                    // for(int i =0; i<recomm; i++){
                    //   cout<<wtf[n][i].first<<","<<wtf[n][i].second<<" ";
                    //    }
                    source_writing[3] = ((wtf1[n][i]) & 0xFF);
                    source_writing[2] = (((wtf1[n][i]) >> 8) & 0xFF);
                    source_writing[1] = (((wtf1[n][i]) >> 16) & 0xFF);
                    source_writing[0] = (((wtf1[n][i]) >> 24) & 0xFF);
                    fwrite(&source_writing, 1, 4, f_writer);
                    destination_writing[3] = ((wtf2[n][i]) & 0xFF);
                    destination_writing[2] = (((wtf2[n][i]) >> 8) & 0xFF);
                    destination_writing[1] = (((wtf2[n][i]) >> 16) & 0xFF);
                    destination_writing[0] = (((wtf2[n][i]) >> 24) & 0xFF);
                    fwrite(&destination_writing, 1, 4, f_writer);
                }
               else{// cout<<"NULL"<<","<<"NULL"<<" ";
                    null_source_writing[3] = 'L';
                    null_source_writing[2] = 'L';
                    null_source_writing[1] = 'U';
                    null_source_writing[0] = 'N';
                    fwrite(&null_source_writing, 1, 4, f_writer);
                    null_destination_writing[3] = 'L';
                    null_destination_writing[2] = 'L';
                    null_destination_writing[1] = 'U';
                    null_destination_writing[0] = 'N';
                    fwrite(&null_destination_writing, 1, 4, f_writer);
                }
            }// cout<<"\n";
        }
        fclose(f_writer);
    }
    MPI_Finalize();
    auto stop = high_resolution_clock::now();
  //  return 0;
    auto duration = duration_cast<seconds>(stop-start);
    cout<<"Total time taken by function is : "<< duration.count()<<" seconds";
}
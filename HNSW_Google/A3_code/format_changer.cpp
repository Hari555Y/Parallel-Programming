#include <iostream>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>
#include <string>
//#include <mpi.h>
#include <assert.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main(int argc, char * argv[])
{
    auto start_time = high_resolution_clock::now();
   // string dataset_up_sh = argv[0];
    string in_path = argv[1];
    string out_path = argv[2];

    string max_level_txt = in_path + "/max_level.txt";
    string max_level_dat = out_path + "/max_level.dat";
    int max_level;
    ifstream input_max_level_file;
    input_max_level_file.open(max_level_txt);
    string max_l_str;
    getline(input_max_level_file, max_l_str);
    max_level = stoi(max_l_str);
    input_max_level_file.close();
    vector<vector<double>> user;

    ofstream output_max_level_file;
    output_max_level_file.open(max_level_dat);
    unsigned char buff[4];
    buff[0] = (max_level >> 0) & 0xFF;
    buff[1] = (max_level >> 8) & 0xFF;
    buff[2] = (max_level >> 16) & 0xFF;
    buff[3] = (max_level >> 24) & 0xFF;
    output_max_level_file << buff[0] << buff[1] << buff[2] << buff[3];
    output_max_level_file.close();

    string ep_txt = in_path + "/ep.txt";
    string ep_dat = out_path + "/ep.dat";
    int ep;
    ifstream input_ep_file;
    input_ep_file.open(ep_txt);
    string ep_str;
    getline(input_ep_file, ep_str);
    ep = stoi(ep_str);
    input_ep_file.close();

    ofstream output_ep_file;
    output_ep_file.open(ep_dat);
    unsigned char buff1[4];
    buff1[0] = (ep >> 0) & 0xFF;
    buff1[1] = (ep >> 8) & 0xFF;
    buff1[2] = (ep >> 16) & 0xFF;
    buff1[3] = (ep >> 24) & 0xFF;
    output_ep_file << buff1[0] << buff1[1] << buff1[2] << buff1[3];
    output_ep_file.close();

    string level_txt = in_path + "/level.txt";
    string level_dat = out_path + "/level.dat";
    vector<int> level;
    ifstream input_level_file;
    input_level_file.open(level_txt);
    string level_str;
    while (getline(input_level_file, level_str))
    {
        if ( level_str != "")
        {
            level.push_back(stoi(level_str));
        }
    }
    input_level_file.close();

    unsigned char buff2[4];
    ofstream output_level_file;
    output_level_file.open(level_dat);
    for (int p = 0; p < level.size(); p++)
    {
        buff2[0] = (level[p] >> 0) & 0xFF;
        buff2[1] = (level[p] >> 8) & 0xFF;
        buff2[2] = (level[p] >> 16) & 0xFF;
        buff2[3] = (level[p] >> 24) & 0xFF;
        output_level_file << buff2[0] << buff2[1] << buff2[2] << buff2[3];
    }
    output_level_file.close();

    string index_txt = in_path + "/index.txt";
    string index_dat = out_path + "/index.dat";
    vector<int> index;
    ifstream input_index_file;
    input_index_file.open(index_txt);
    string index_str;
    while (getline(input_index_file, index_str))
    {
        if ( index_str != "")
        {
            index.push_back(stoi(index_str));
        }
    }
    input_index_file.close();

    ofstream output_index_file;
    output_index_file.open(index_dat);
    unsigned char buff10[4];
    for (int p = 0; p < index.size(); p++)
    {
        buff10[0] = (index[p] >> 0) & 0xFF;
        buff10[1] = (index[p] >> 8) & 0xFF;
        buff10[2] = (index[p] >> 16) & 0xFF;
        buff10[3] = (index[p] >> 24) & 0xFF;
        output_index_file << buff10[0] << buff10[1] << buff10[2] << buff10[3];
    }
    output_index_file.close();

    string indptr_txt = in_path + "/indptr.txt";
    string indptr_dat = out_path + "/indptr.dat";
    vector<int> indptr;
    ifstream input_indptr_file;
    input_indptr_file.open(indptr_txt);
    string indptr_str;
    while (getline(input_indptr_file, indptr_str))
    {
        if ( indptr_str != "")
        {
            indptr.push_back(stoi(indptr_str));
        }
    }
    input_indptr_file.close();

    ofstream output_indptr_file;
    output_indptr_file.open(indptr_dat);
    unsigned char buff4[4];
    for (int p = 0; p < indptr.size(); p++)
    {
        buff4[0] = (indptr[p] >> 0) & 0xFF;
        buff4[1] = (indptr[p] >> 8) & 0xFF;
        buff4[2] = (indptr[p] >> 16) & 0xFF;
        buff4[3] = (indptr[p] >> 24) & 0xFF;
        output_indptr_file << buff4[0] << buff4[1] << buff4[2] << buff4[3];
    }
    output_indptr_file.close();

    string level_offset_txt = in_path + "/level_offset.txt";
    string level_offset_dat = out_path + "/level_offset.dat";
    vector<int> level_offset;
    ifstream input_level_offset_file;
    input_level_offset_file.open(level_offset_txt);
    string level_offset_str;
    while (getline(input_level_offset_file, level_offset_str))
    {
        if ( level_offset_str != "")
        {
            level_offset.push_back(stoi(level_offset_str));
        }
    }
    input_level_offset_file.close();

    ofstream output_level_offset_file;
    output_level_offset_file.open(level_offset_dat);
    unsigned char buff3[4];
    for (int p = 0; p < level_offset.size(); p++)
    {
        buff3[0] = (level_offset[p] >> 0) & 0xFF;
        buff3[1] = (level_offset[p] >> 8) & 0xFF;
        buff3[2] = (level_offset[p] >> 16) & 0xFF;
        buff3[3] = (level_offset[p] >> 24) & 0xFF;
        output_level_offset_file << buff3[0] << buff3[1] << buff3[2] << buff3[3];
    }
    output_level_offset_file.close();

    string vect_txt = in_path + "/vect.txt";
    string vect_dat = out_path + "/vect.dat";
    vector<vector<double>> vect;
     ifstream input_vect_file;
     input_vect_file.open(vect_txt);
     string line = "";
     while (getline(input_vect_file, line)){
        stringstream ststm(line);
        string letters;
        vector<double> one_line;
        while(ststm>>letters){
            one_line.push_back(stod(letters));
        }
        vect.push_back(one_line);
     }
     input_vect_file.close();
    // string temp_line = "";
    // if (input_vect_file.is_open())
    // {
    //     int a = 0;
    //     while (getline(input_vect_file, line))
    //     {
    //         if (line != "")
    //         {
    //             vector<double> new_arr;
    //             vect.push_back(new_arr);
    //             line = line + ",";
    //             for (int i = 0; i < line.length(); i++)
    //             {
    //                 if (line[i] != ' ' && line[i] != ',')
    //                 {
    //                     temp_line += line[i];
    //                 }
    //                 else
    //                 {
    //                     vect[a].push_back(stod(temp_line));
    //                     temp_line = "";
    //                 }
    //             }
    //         }
    //     }
    //     a++;
    // }
    // input_vect_file.close();

    ofstream output_vect_file;
    output_vect_file.open(vect_dat, ios::out | ios::binary);
     int m = vect.size();
     int n = vect[0].size();
     unsigned char buf1[4];
     unsigned char buf2[4];
     buf1[0] = (m >> 0) & 0xFF;
     buf1[1] = (m >> 8) & 0xFF;
     buf1[2] = (m >> 16) & 0xFF;
     buf1[3] = (m >> 24) & 0xFF;
     output_vect_file << buf1[0] << buf1[1] << buf1[2] << buf1[3];
     buf2[0] = (n >> 0) & 0xFF;
     buf2[1] = (n >> 8) & 0xFF;
     buf2[2] = (n >> 16) & 0xFF;
     buf2[3] = (n >> 24) & 0xFF;
     output_vect_file << buf2[0] << buf2[1] << buf2[2] << buf2[3];
     for (int a = 0; a < vect.size(); a++)
     {
         for (int b = 0; b < vect[0].size(); b++)
         {
             output_vect_file.write((char *)&vect[a][b], sizeof(double));
         }
     }
     output_vect_file.close();

    auto final_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(final_time - start_time);
    cout << "Total time taken by the change of the format is : " << duration.count() << " milliseconds";\
    return 1;
}
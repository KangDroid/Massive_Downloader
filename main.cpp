#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>
#include "ContainerQueue.h"

using namespace std;

void download_function(ContainerQueue* data, char* save_directory) {
    string dir = string(save_directory);
    for (int i = 0; i < data->head; i++) {
        Container t = data->pop();
        string command = "wget -O "+ dir + t.file_name + ".jpg " + t.url_dir + " >> /dev/null";
        system(command.c_str());
    }
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: program_name file_path save_path" << endl;
        cout << "Where program name is compiled program and file path is FULL path to txt file, and save_path is full path to save directory" << endl;
        cout << "eg: ./a.out \"/Users/kangdroid/test.txt\" \"/Users/kangdroid/Desktop/folder/\" "<< endl;
        return 0;
    } 
    const int thread_ctr = std::thread::hardware_concurrency();
    ifstream ctr(argv[1]);
    ifstream ifs(argv[1]);
    string tmp;
    int container_max = 0;
    ContainerQueue thread_queue[thread_ctr];

    // Get length of file
    while (getline(ctr, tmp)) {
        container_max++;
    }

    // Each queue have length but what?
    int each_length = container_max / thread_ctr;
    if (container_max % thread_ctr > 0) {
        each_length++;
    }

    // Fully init queue
    for (int i = 0; i < thread_ctr; i++) {
        thread_queue[i].init(each_length);
    }

    int count = 0;
    while (getline(ifs, tmp)) {
        int loc = tmp.find('\t');
        if (loc != string::npos) {
            count %= thread_ctr;
            string num = tmp.substr(0, loc);
            string link = tmp.substr(loc+1, tmp.length());
            Container ctr(num, link);
            thread_queue[count++].push(ctr);
        }
    }

    for (int i = 0; i < thread_ctr; i++) {
        pid_t t_f = fork();
        if (t_f == 0) {
            download_function(&thread_queue[i], argv[2]);
            //sleep(5);
            exit(0);
        }
    }
    for(int i=0;i<thread_ctr;i++) // loop will run n times (n=5) 
        wait(NULL); 
    return 0;
}
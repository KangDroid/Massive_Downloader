#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>

using namespace std;

class Container {
public:
    string file_name;
    string url_dir;
    Container(string fn, string url) {
        this->file_name = fn;
        this->url_dir = url;
    }
    Container() {}
};

class ContainerQueue {
public:
    Container* ctr;
    int max_val;
    int head;
    int tail;
    ContainerQueue() {}
    ~ContainerQueue() {
        delete[] ctr;
    }
    void init(int max) {
        this->head = 0;
        this->tail = 0;
        this->max_val = max;
        this->ctr = new Container[max];
    }

    void push(Container& cont_val) {
        this->ctr[head++] = cont_val;
    }

    Container pop() {
        return this->ctr[tail++];
    }
};

void download_function(ContainerQueue* data) {
    for (int i = 0; i < data->head; i++) {
        Container t = data->pop();
        string command = "wget -O ./folder/" + t.file_name + ".jpg " + t.url_dir + " >> /dev/null";
        system(command.c_str());
    }
}

int main(void) {
    const int thread_ctr = std::thread::hardware_concurrency();
    ifstream ctr("test.txt");
    ifstream ifs("test.txt");
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
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            download_function(&thread_queue[i]);
            //sleep(5);
            exit(0);
        }
    }
    for(int i=0;i<thread_ctr;i++) // loop will run n times (n=5) 
        wait(NULL); 
    return 0;
}
#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <iostream>

using namespace std;

class Container {
public:
    string file_name;
    string url_dir;
    Container(string fn, string url);
    Container();
};
#endif // __CONTAINER_H__
#include <bits/stdc++.h>
using namespace std;

int ascFileRead(const char *file,char **buff) {

    FILE *pFile;
    long lSize;

    size_t result;

    pFile = fopen(file, "rb");
    if (pFile == NULL)
    {
        fputs("File error", stderr);
        exit(1);
    }

    // obtain file size:
    fseek(pFile, 0, SEEK_END);
    lSize = ftell(pFile);
    rewind(pFile);

    // allocate memory to contain the whole file:
    *buff = (char *)malloc(sizeof(char) * (lSize+1));
    if (*buff == NULL)
    {
        fputs("Memory error", stderr);
        exit(2);
    }

    // copy the file into the buffer:
    result = fread(*buff, sizeof(char), lSize, pFile);

    (*buff)[lSize] = 0;
    if (result != lSize)
    {
        fputs("Reading error", stderr);
        exit(3);
    }

    /* the whole file is now loaded in the memory buffer. */
    // terminate
    fclose(pFile);

    return 0;
}

int ascFileWrite(const char *file,const char *buf){

    FILE *pFile = fopen(file, "wb");
    fwrite(buf, sizeof(char), strlen(buf), pFile);
    fclose(pFile);
    return 0;
}
string modify(const string &a){
    string ret;
    int i = 0 ;
    while (!isprint(a[i++])){}
    ret = a.c_str()+i;
    while (!isprint(ret.back())){
        ret.pop_back();
    }
    return ret;
}
void addPath(const string &str1,const string & con,const string &str2){

    printf("%s-->|%s|%s\n",str1.c_str(),con.c_str(),str2.c_str());
}

int main(int argc,char **argv) {
    char *buf;
    if(argc==1){
        return 0;
    }
    ascFileRead(argv[1],&buf);
    //puts(buf);
    vector<string>info;
    char *buff;
    if(argc==2){
        ascFileRead("config",&buff);
    }else{
        ascFileRead(argv[2],&buff);
    }
    {
        stringstream s(buff);
        string temp;
        while (getline(s,temp) ){
            info.push_back(temp);
        }
    }
    vector<string>header;
    stringstream s(buf);

    string temp;
    string last;
    while (getline(s,temp)){
        if(temp.empty())continue;
        int cnt = count(temp.begin(),temp.end(),'{');

        stringstream ss(temp);
        string beginner;
        ss >> beginner;
        if(cnt) {
            {
                if (beginner[0] == '{'){
                    header.emplace_back("[[]]");
                }
                else {
                    auto it = find(temp.begin(), temp.end(), '{');
                    header.emplace_back(string(temp.begin(), it));
                }
            }
        }else{
            /*
             state = 123
             */
            if(beginner==info[1]){
                ss>>beginner;
                ss>>beginner;

                addPath(header[0],header.back(),beginner);
            }
        }

        last = temp;
        cnt = count(temp.begin(),temp.end(),'}');
        if(cnt){
            if(!header.empty()){
                header.pop_back();
            }else{
                cout<<"error\n";
            }
        }
    }


    return 0;
}

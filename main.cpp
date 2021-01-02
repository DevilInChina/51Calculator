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
void MODIFY(string &a){
    replace(a.begin(),a.end(),'(',' ');
    replace(a.begin(),a.end(),')',' ');
    replace(a.begin(),a.end(),'~','q');
    replace(a.begin(),a.end(),'|','o');

}
int fromLen;
void addPath(const string &str1,const string & con,const string &str2){
    string from;
    stringstream frombuf(str1);
    frombuf>>from;
    frombuf>>from;
    from = string(from.begin()+fromLen-1,from.end()-2);
    string cons(con);
    MODIFY(cons);
    int beg = 0;
    int ends = cons.length()-1;
    while (isblank(cons[beg++]));

    cons = string(cons.begin()+beg-1,cons.end()+ends);
    printf("%s-->|%s|%s\n",from.c_str(),cons.c_str(),str2.c_str());
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
    fromLen = info[0].length();
    string temp;
    string last;
    cout << "```mermaid"<<endl<<
            "graph LR;"<<endl;
    while (getline(s,temp)) {
        if(temp.empty())continue;
        //cout<<temp<<endl;
        auto left = find(temp.begin(), temp.end(), '{');
        auto right = find(temp.begin(), temp.end(), '}');
        if(left == right){/// both are end
            stringstream ss(temp);
            string cur;
            ss>>cur;
            if(cur==info[1]){
                ss>>cur;
                ss>>cur;
                addPath(header[0],header.back(),cur);

            }

        }else if(right != temp.end() && left != temp.end() && right < left){
            header.pop_back();
            header.emplace_back(right + 1, left);
        }else if(right!=temp.end() && left==temp.end()) {
            header.pop_back();
        }else if(left!=temp.end()){
            stringstream ss(temp);
            string cur;
            ss>>cur;
            if(cur[0]=='{') {
                if(last.back()=='\n')last.pop_back();
                header.emplace_back(last);
            }
            else header.emplace_back(temp.begin(),left);
        }

        if(right != temp.end()){
            last = string(right+1,temp.end());
        }else{
            last = temp;
        }
    }
    cout<<"```\n";
    return 0;
}

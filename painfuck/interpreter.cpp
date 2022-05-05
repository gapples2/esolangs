#include <iostream>
#include <string>
#include <random>
#include <charconv>
#include <functional>

std::string before = "pysrlijouavbtkzhwqdec";
char after[] = {'e','u','o','p','d','h','z','b','c','l','k','q','s','j','w','a','r','i','y','v','t'};

std::string decrypt(std::string str){
    for(int x=0;x<str.length();x++){
        int f = before.find(str[x]);
        if(f!=std::string::npos&&x>0){
            char c = f;
            for(int y=1;y<x;y++){
                c = before.find(after[c]);
            }
            str[x] = after[c];
        }
    }
    return str;
}

void run(std::string program){
    unsigned int tape[65536] = {};
    int pointer = 0;
    int len = program.length();
    int ip = 0;
    std::function<void(char)> instruction = [&](char i){
        switch(i){
            case 'p':{
                tape[pointer]+=2;
                break;
            }case 's':{
                tape[pointer]--;
                break;
            }case 'r':{
                pointer=(pointer+2)%65536;
                break;
            }case 'l':{
                pointer--;
                if(pointer<0)pointer=65535;
                break;
            }case 'i':{
                std::string in;
                std::cin>>in;
                int num;
                std::from_chars(in.data(),in.data()+in.size(),num);
                tape[pointer]=num;
                break;
            }case 'j':{
                char in;
                std::cin>>in;
                tape[pointer]=in;
                break;
            }case 'o':{
                std::cout<<tape[pointer];
                break;
            }case 'u':{
                std::cout<<(char)tape[pointer];
                break;
            }case 'a':{
                while(program[ip]!='b'&&ip<len)ip++;
                break;
            }case 'b':{
                while(program[ip]!='a'&&ip>0)ip--;
                break;
            }case 'k':{
                tape[pointer]*=tape[pointer];
                break;
            }case 'z':{
                tape[pointer]=0;
                break;
            }case 'h':{
                tape[pointer]/=2;
                break;
            }case 'w':{
                if(pointer==65535)tape[0]=tape[pointer];
                else tape[pointer+1]=tape[pointer];
                break;
            }case 'q':{
                if(pointer==0)tape[65535]=tape[pointer];
                else tape[pointer-1]=tape[pointer];
                break;
            }case 'c':{
                int nip = ip+1;
                if(ip==len-1)nip=0;
                for(int x=0;x<6;x++)instruction(program[nip]);
                break;
            }case 'y':{
                std::random_device r;
                std::default_random_engine e1(r());
                std::uniform_int_distribution<int> uniform_dist(0, 1);
                int num = uniform_dist(e1);
                if(num==1)instruction(program[ip+1]);
                break;
            }case 'e':{
                ip=len;
                break;
            }case 'v':{
                if(tape[pointer]!=0)ip++;
                break;
            }case 'd':{
                pointer=0;
                break;
            }case 't':{
                int nip = ip-1;
                if(nip==-1)nip=len-1;
                for(int x=0;x<3;x++)instruction(program[nip]);
                break;
            }
        }
    };
    while(ip<len){
        instruction(program[ip]);
        ip++;
    }
}

int main(){
    std::cout<<"Input your program.\n";
    std::string input;
    std::cin>>input;
    run(decrypt(input));
    return 0;
}

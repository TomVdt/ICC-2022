#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

enum class EC{S,I};

template<typename T> EC c(T c,int&v){ofstream o("h");if(!o){cerr<<"E:Uo'h'";return EC::I;}if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u'){o<<c<<" v."<<endl;o<<"Sqrt A "<<c<<" "<<sqrt(static_cast<double>(c))<<endl;v++;return EC::S;}else{o<<c<<" c."<<endl;return EC::S;}return EC::I;}int main(){ifstream i("i");if(!i){cerr<<"E:Ui'i'";return 1;}string input;i>>input;int v=0;for(int i=0;i<input.length();i++){if(c(input.at(i),v)==EC::I){ofstream o("h");if(!o){cerr<<"E:Uo'h'";return 1;}o<<"E:Ii"<<endl;o.close();}}ofstream o("h");if(!o){cerr<<"E:Uo'h'";return 1;}o<<"V: "<<v<<endl;o.close();return 0;}
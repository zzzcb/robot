#include <iostream>
#include <map>

using namespace std;

int main(){
    map<string,int> word_cnt;

    word_cnt.insert({"hello",33});
    word_cnt.insert({"world",22});
    word_cnt.insert({"my",11});
    //word_cnt.insert({"hello",11}); // 会覆盖 第一个 




    // 访问 [] / .at()
    int cnt = word_cnt["hello"];
    //int cnt = word_cnt.at("hello");
    cout << cnt<<endl;

    // 删除 .erase() 
    word_cnt.erase("my");


    // 遍历 
    cout << "======================" <<endl;
    for(auto i = word_cnt.begin();i!=word_cnt.end();i++){
        cout << i->first << " : " << i->second<<endl;;
    }


    // 容量查询(是否为空，获取大小，是否存在某个key)
    cout << word_cnt.empty() << endl;
    cout << word_cnt.size() << endl;
    cout << word_cnt.count("my") << endl; // 通过统计 来判断是否存在某个key

    return 0;

}


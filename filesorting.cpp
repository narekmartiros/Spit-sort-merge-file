#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

const int number_count=1000000;
const int elements_in_raw=10;
const int split_count=10;
const char* filename="file-";

void create_numbers_file();
void split_file();
void sort_file();
void read_file_to_container(std::vector<int> & temp, std::string filename);
void merge_files();

int main(){
    create_numbers_file();
    split_file();
    sort_file();
    merge_files();
}

void create_numbers_file(){
    int raw_count=number_count/elements_in_raw;
    std::ofstream file1;
    file1.open("unsorted.txt");
    for(int i=0;i<number_count;++i){
        if(i%elements_in_raw==0&&i>0){
            file1<<std::endl;
        }
        file1<<rand()<<" "; 
    }
    file1.close();
}

void split_file(){
    int raw_count=number_count/elements_in_raw;
    std::ifstream split;
    split.open("unsorted.txt");
    int i=0;
    int j=0;
    std::vector<std::string> v;
    std::string file_name;
    while(!split.eof()){
        int small_file_size=raw_count/split_count;;
        std::ofstream temp;
        std::string temp_str;
        std::getline(split,temp_str);
        if(i%small_file_size==0&&i>0){
            std::string file_name="file-"+std::to_string(j);
            temp.open(file_name.c_str());
          for(auto& x:v){
              temp<<x;
              temp<<'\n';
          }
            temp.close();
            v.clear();
            ++j;
        }
        v.push_back(temp_str);
         ++i;
    }
    std::ofstream temp2;
    file_name="file-"+std::to_string(j);
    temp2.open(file_name.c_str());
    for(auto& x:v){
              temp2<<x;
              temp2<<'\n';
          }
    temp2.close();
    split.close();
}

void sort_file(){
    std::vector<int> temp;
    std::string filename1;
    for(int i=0;i<split_count; ++i){
    filename1=filename+std::to_string(i);
    read_file_to_container(temp, filename1);
    std::sort(temp.begin(),temp.end());
    std::ofstream file2;
    std::string sorted_file_name="sorted " + filename1;
    file2.open(sorted_file_name);
    for(int i=0;i<temp.size();++i){
        if(i%elements_in_raw==0&&i>0){
            file2<<std::endl;
        }
        file2<<temp[i]<<" "; 
    }
    file2.close();
    }
}

void read_file_to_container(std::vector<int> & temp, std::string filename){
    std::string temp_s;
    std::ifstream file1;
    file1.open(filename);
    while (!file1.eof()){
        std::string m;
		std::getline(file1,temp_s);
		std::istringstream ss(temp_s);
		while(ss>>m){
            std::string s=m;
            int m=std::stoi(s);
			temp.push_back(m);
		}
	}
    file1.close();
}

void merge_files(){
    std::cout<<"sds";
    std::vector<std::vector<int>> vec(split_count);
    std::string filename;
    for(int i=0; i<split_count;++i){
        filename="sorted file-"+std::to_string(i);
        read_file_to_container(vec[i],filename);
    }
    std::multimap<int,bool> mp;
    for(int i=0;i<vec.size();++i){
        for(int j=0;j<vec[0].size();++j){
            mp.emplace(vec[i][j],true);
        }
    }
    std::ofstream file1;
    file1.open("merged_sorted");
    int i=0;
    for(auto& x: mp){
        if(i%elements_in_raw==0&&i>0){
            file1<<std::endl;
        }
        ++i;
        file1<<x.first<<" ";
    }
    file1.close();
}
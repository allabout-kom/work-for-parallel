#include "PCFG.h"
#include <chrono>
#include <fstream>
#include "md5.h"
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace chrono;

// 编译指令如下
// g++ main.cpp train.cpp guessing.cpp md5.cpp -o main
// g++ main.cpp train.cpp guessing.cpp md5.cpp -o main -O1
//g++ train.cpp guessing.cpp main.cpp md5.cpp -o main -O2

int main()
{
    
    double time_hash1 = 0;  // 用于MD5哈希的时间
    double time_hash2 = 0;  // 用于MD5哈希的时间
    double time_hash3 = 0;  // 用于MD5哈希的时间
    double time_hash4 = 0;  // 用于MD5哈希的时间
    double time_hash5 = 0;  // 用于MD5哈希的时间
    double time_hash6 = 0;  // 用于MD5哈希的时间
    double time_hash7 = 0;  // 用于MD5哈希的时间
    double time_guess = 0; // 哈希和猜测的总时长
    double time_train = 0; // 模型训练的总时长
    PriorityQueue q;
    auto start_train = system_clock::now();
    q.m.train("/guessdata/Rockyou-singleLined-full.txt");
    q.m.order();
    auto end_train = system_clock::now();
    auto duration_train = duration_cast<microseconds>(end_train - start_train);
    time_train = double(duration_train.count()) * microseconds::period::num / microseconds::period::den;

    q.init();
    cout << "here" << endl;
    int curr_num = 0;
    auto start = system_clock::now();
    // 由于需要定期清空内存，我们在这里记录已生成的猜测总数
    int history = 0;
    // std::ofstream a("./output/results.txt");
    int r,s;
    while (!q.priority.empty())
    {
        q.PopNext();
        q.total_guesses = q.guesses.size();
        if (q.total_guesses - curr_num >= 100000)
        {
            //cout << "Guesses generated: " <<history + q.total_guesses << endl;
            curr_num = q.total_guesses;

            // 在此处更改实验生成的猜测上限
            int generate_n=10000000;
            if (history + q.total_guesses > 10000000)
            {
                auto end = system_clock::now();
                auto duration = duration_cast<microseconds>(end - start);
                time_guess = double(duration.count()) * microseconds::period::num / microseconds::period::den;
                //cout << "Guess time:" << time_guess - time_hash3 << "seconds"<< endl;
                cout << "Hash time1:" << time_hash1 << "seconds"<<endl;
                // cout << "Hash time2:" << time_hash2 << "seconds"<<endl;
                // cout << "Hash time3:" << time_hash3 << "seconds"<<endl;
                cout << "Hash time4:" << time_hash4 << "seconds"<<endl;
                // cout << "Hash time5:" << time_hash5 << "seconds"<<endl;
                // cout << "Hash time6:" << time_hash6 << "seconds"<<endl;
                // cout << "Hash time7:" << time_hash7 << "seconds"<<endl;
                
                //cout << "Train time:" << time_train <<"seconds"<<endl;
                break;
            }
        }
        // 为了避免内存超限，我们在q.guesses中口令达到一定数目时，将其中的所有口令取出并且进行哈希
        // 然后，q.guesses将会被清空。为了有效记录已经生成的口令总数，维护一个history变量来进行记录
        if (curr_num > 1000000)
        {
            auto start_hash1 = system_clock::now();
            bit32 state[4];
            //对于o是4.另一个是current_n
            
            for (string pw : q.guesses)
                // TODO：对于SIMD实验，将这里替换成你的SIMD MD5函数
                MD5Hash(pw, state);
            auto end_hash1 = system_clock::now();
           

            // auto start_hash2 = system_clock::now();  
            // bit32**states=new bit32*[curr_num];
            // for(int i=0;i<curr_num;i++)
            //     states[i]=new bit32[4];
            // SIMD_MD5o(q.guesses, curr_num, states,0);
            // auto end_hash2 = system_clock::now();

            
            // auto start_hash3 = system_clock::now();  
            // int r,s;
            // r=curr_num%4;
            // s=(curr_num)>>2;
            // bit32**states1=new bit32*[4];
            // for(int i=0;i<4;i++)
            //     states1[i]=new bit32[4];
            // for(int i=0;i<s;i++) 
            //     SIMD_MD5o(q.guesses, 4, states1,i<<2);//7/4=1；3
            // if(r)
            //     SIMD_MD5o(q.guesses, r, states1,curr_num-r);
            // auto end_hash3 = system_clock::now();



            auto start_hash4 = system_clock::now();  
            
            r=curr_num%16;
            s=(curr_num)>>4;
            bit32**states2=new bit32*[16];
            for(int i=0;i<16;i++)
                states2[i]=new bit32[4];
            for(int i=0;i<s;i++) 
                SIMD_MD5o(q.guesses, 16, states2,i<<4);//7/4=1；3
            if(r)
                SIMD_MD5o(q.guesses, r, states2,curr_num-r);
            auto end_hash4 = system_clock::now();

           
            // auto start_hash5 = system_clock::now();  
            // //int r,s;
            // r=curr_num%64;
            // s=(curr_num)>>6;
            // bit32**states3=new bit32*[64];
            // for(int i=0;i<64;i++)
            //     states3[i]=new bit32[4];
            // for(int i=0;i<s;i++) 
            //     SIMD_MD5o(q.guesses, 64, states3,i<<6);//7/4=1；3
            // if(s)
            //     SIMD_MD5o(q.guesses, r, states3,curr_num-r);
            // auto end_hash5 = system_clock::now();

            


            // auto start_hash6 = system_clock::now();  
            
            // r=curr_num%128;
            // s=(curr_num)>>7;
            // bit32**states4=new bit32*[128];
            // for(int i=0;i<128;i++)
            //     states4[i]=new bit32[4];
            // for(int i=0;i<s;i++) 
            //     SIMD_MD5o(q.guesses, 128, states4,i<<7);//7/4=1；3
            // if(r)
            //     SIMD_MD5o(q.guesses, r, states4,curr_num-r);
            // auto end_hash6 = system_clock::now();



            // auto start_hash7 = system_clock::now();  
            
            // r=curr_num%256;
            // s=(curr_num)>>8;
            // bit32**states5=new bit32*[256];
            // for(int i=0;i<256;i++)
            //     states5[i]=new bit32[4];
            // for(int i=0;i<s;i++) 
            //     SIMD_MD5o(q.guesses,256, states5,i<<8);//7/4=1；3
            // if(r)
            //     SIMD_MD5o(q.guesses, r, states5,curr_num-r);
            // auto end_hash7 = system_clock::now();


            auto duration1 = duration_cast<microseconds>(end_hash1 - start_hash1);
            time_hash1 += double(duration1.count()) * microseconds::period::num / microseconds::period::den;
            
            // auto duration2 = duration_cast<microseconds>(end_hash2 - start_hash2);
            // time_hash2 += double(duration2.count()) * microseconds::period::num / microseconds::period::den;


            // auto duration3 = duration_cast<microseconds>(end_hash3 - start_hash3);
            // time_hash3 += double(duration3.count()) * microseconds::period::num / microseconds::period::den;

            auto duration4 = duration_cast<microseconds>(end_hash4 - start_hash4);
            time_hash4 += double(duration4.count()) * microseconds::period::num / microseconds::period::den;

            // auto duration5 = duration_cast<microseconds>(end_hash5 - start_hash5);
            // time_hash5 += double(duration5.count()) * microseconds::period::num / microseconds::period::den;


            // auto duration6 = duration_cast<microseconds>(end_hash6 - start_hash6);
            // time_hash6 += double(duration6.count()) * microseconds::period::num / microseconds::period::den;

            // auto duration7 = duration_cast<microseconds>(end_hash7 - start_hash7);
            // time_hash7 += double(duration7.count()) * microseconds::period::num / microseconds::period::den;


                //cout<<"下面是"<<std::setfill('0') << hex << states[0][3]<<endl;
                // 以下注释部分用于输出猜测和哈希，但是由于自动测试系统不太能写文件，所以这里你可以改成cout
                // a<<pw<<"\t";
                // for (int i1 = 0; i1 < 4; i1 += 1)
                // {
                //     a << std::setw(8) << std::setfill('0') << hex << state[i1];
                // }
                // a << endl;
            // 记录已经生成的口令总数
            history += curr_num;
            curr_num = 0;
            q.guesses.clear();
        }
    }
}
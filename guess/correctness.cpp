#include "PCFG.h"
#include <chrono>
#include <fstream>
#include "md5.h"
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
using namespace chrono;

// 编译指令如下：
// g++ train.cpp guessing.cpp md5.cpp correctness.cpp -o main


// 通过这个函数，你可以验证你实现的SIMD哈希函数的正确性
int main()
{
    bit32 state[4];
    bit32**states;
    states=new bit32*[1];
    states[0]=new bit32[4];
    std::string a="bvaisdbjasdkafkasdfnavkjnakdjfejfanjsdnfkajdfkajdfjkwanfdjaknsvjkanbjbjadfajwefajksdfakdnsvjadfasjdvabvaisdbjasdkafkasdfnavkjnakdjfejfanjsdnfkajdfkajdfjkwanfdjaknsvjkanbjbjadfajwefajksdfakdnsvjadfasjdvabvaisdbjasdkafkasdfnavkjnakdjfejfanjsdnfkajdfkajdfjkwanfdjaknsvjkanbjbjadfajwefajksdfakdnsvjadfasjdvabvaisdbjasdkafkasdfnavkjnakdjfejfanjsdnfkajdfkajdfjkwanfdjaknsvjkanbjbjadfajwefajksdfakdnsvjadfasjdva";
    std::vector<std::string> inputs;
    inputs.push_back(a);
    MD5Hash("bvaisdbjasdkafkasdfnavkjnakdjfejfanjsdnfkajdfkajdfjkwanfdjaknsvjkanbjbjadfajwefajksdfakdnsvjadfasjdvabvaisdbjasdkafkasdfnavkjnakdjfejfanjsdnfkajdfkajdfjkwanfdjaknsvjkanbjbjadfajwefajksdfakdnsvjadfasjdvabvaisdbjasdkafkasdfnavkjnakdjfejfanjsdnfkajdfkajdfjkwanfdjaknsvjkanbjbjadfajwefajksdfakdnsvjadfasjdvabvaisdbjasdkafkasdfnavkjnakdjfejfanjsdnfkajdfkajdfjkwanfdjaknsvjkanbjbjadfajwefajksdfakdnsvjadfasjdva", state);
    SIMD_MD5o(inputs, 1,states,0);
    for (int i1 = 0; i1 < 4; i1 ++)
    {
        cout << std::setw(8) << std::setfill('0') << hex << state[i1];
    }
    cout << endl;
    for (int i1 = 0; i1 < 4; i1 ++)
    {
        cout << std::setw(8) << std::setfill('0') << hex << states[0][i1];
    }
    cout << endl;
}
#include <cstdio>
#include <gtest/gtest.h>
#include <support/functionals.hpp>
#include <support/arguments_vector.hpp>
#include <algorithm>

struct stringable{
    int a = 1;
    int b =2;
    std::string to_string(){
        return "a=" + std::to_string(a) + " b=" + std::to_string(b);
    }
};


TEST(TestSupport, test_string_unpack){
    auto vec = as_string_vector(1,2,3,1.0,"alter", stringable());
    for(int i = 0; i < vec.size(); i++){
        printf("%s\n",vec[i].c_str());
    }
}

TEST(TestSupport,test_arg_vector){
    ArgumentVector vec{};
    vec.add_argument("--port",4444);
    vec.add_argument("--cipher", "ae256");
    auto res = vec.argv();
    ASSERT_EQ(res[0], "--port 4444 ");
    ASSERT_EQ(res[1], "--cipher ae256 ");
}

TEST(TestSupport, test_multi_arg_vector){
    ArgumentVector vec{};
    vec.add_argument("--host",true,"localhost","127.0.0.1");
    ASSERT_EQ(vec.argv()[0], "--host localhost --host 127.0.0.1 ");
}
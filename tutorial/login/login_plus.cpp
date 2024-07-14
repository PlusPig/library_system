//
// Created by maitao on 7/13/2024.
//
#include "../global.h"

#define BUF_SIZE 1024
char buf[BUF_SIZE];

// 初始版登录注册
bool login_or_register(bool is_login) {
    system("cls");
    printf("please input username and password\n");

    string username, password;
    printf("username:");
    cin >> username;
    printf("password:");
    cin >> password;
    FILE* file = fopen("tutorial/user.txt", "a+");

    if (file == nullptr) {
        printf("打开文件失败\n");
        return false;
    }

    bool res = false;

    string w = username+"\n"+password+"\n";
    if (is_login) {
        fread(buf, 1, BUF_SIZE, file);
        if (strcmp(w.c_str(), buf) == 0) {
            res = true;
        }
    } else {
        fwrite(w.c_str(), 1, w.size(), file);
        res = true;
    }

    fclose(file);
    return res;
}

/*
 * @brief C++风格的登录注册验证函数，只用于验证没有界面，方便测试
 * @param[in] is_login: true为登录,false为注册
 * @param[in] username 用户名
 * @param[in] password 密码
 * @return 验证成功返回true，否则false
 * */
bool login_or_register_plus(bool is_login, const string& username, const string& password) {
    fstream fs;
    fs.open("../tutorial/login/user_plus.txt", ios::in | ios::out | ios::app);
    assert(fs.is_open());

    string uname, pwd;
    bool res = false;

    if (is_login) {
        while (!fs.eof()) {
            getline(fs, uname);
            // 因为写入是两行两行写入的，所以这里不会读到末尾，不用在这里判定eof
            getline(fs, pwd);
            if (uname == username) {
                if (pwd == password) {
                    res = true;
                }
                break;
            }
        }
    } else {
        bool is_exist = false;
        while (!fs.eof()) {
            getline(fs, uname);
            getline(fs, pwd);
            if (uname == username) {
                is_exist = true;
                break;
            }
        }
        if (!is_exist) {
            string s = username + "\n" + password + "\n";

            // 读到eof时会设置failbit，导致写入失败，需要clear()清除该标志
            fs.clear();
            fs.write(s.c_str(), s.size());
            res = true;
        }
    }

    fs.close();
    return res;
}

namespace Test {
    struct User {
        string username;
        string password;
    };
}

Test::User get_username_and_password() {
    int username_len = rand() % 5 + 5;   // 5-9的随机用户名长度
    int password_len = rand() % 10 + 10; // 10-19的随机密码长度

    string username, password;
    for (int j = 0; j < username_len; j++) {
        username.push_back('a' + rand() % 26);
    }
    for (int j = 0; j < password_len; j++) {
        password.push_back('a' + rand() % 26);
    }
    return {username, password};
}

// 测试改进版登录
void test_login_plus() {
    // 生成1000个用户名和密码，再去重
    const int test_size = 1000;
    unordered_map<string, string> umap;
    for (int i = 0; i < test_size; i++) {
        Test::User user = get_username_and_password();
        umap[user.username] = user.password;
    }

    // 创建或者清空文件
    fstream fs("../tutorial/login/user_plus.txt", ios::out);
    fs.close();

    // 测试正常注册
    for (auto& [username, password] : umap) {
        assert(login_or_register_plus(false, username, password));
    }

    printf("Test1 Pass\n");
    // 测试重名注册
    for (auto& [username, password] : umap) {
        assert(!login_or_register_plus(false, username, password));
    }
    printf("Test2 Pass\n");

    // 测试正常登录
    for (auto& [username, password] : umap) {
        assert(login_or_register_plus(true, username, password));
    }
    printf("Test3 Pass\n");

    // 测试密码错误
    for (auto& [username, password] : umap) {
        assert(!login_or_register_plus(true, username, "123456"));
    }
    printf("Test4 Pass\n");
    printf("All Test Pass\n");
}
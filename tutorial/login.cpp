#include <iostream>
#include <cstring>

using namespace std;

char buf[1024];

bool login_or_register(bool is_login) {
    system("cls");
    printf("please input username and password\n");

    string username, password;
    printf("username:");
    cin >> username;
    printf("password:");
    cin >> password;

    FILE* file = fopen("user.txt", "a+");
    if (file == nullptr) {
        printf("打开文件失败\n");
        return false;
    }

    bool res = false;

    string w = username+"\n"+password+"\n";
    if (is_login) {
        fread(buf, 1, 1024, file);
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


// 单用户登录注册示例代码，很多细节没有完善
int main() {
    bool quit = false;
    while (!quit) {
        system("cls");
        printf("welcome\n"
               "login or register?\n"
               "please input your choice\n"
               "<a>login <b>register <q>quit\n");
        char c;
        cin >> c;
        switch (c) {
            case 'a':
                if (login_or_register(true)) {
                    printf("login success\n");
                } else {
                    printf("login fail\n");
                }
                quit = true;
                break;
            case 'b':
                if (login_or_register(false)) {
                    printf("register success\n");
                } else {
                    printf("register fail\n");
                }
                quit = true;
                break;
            case 'q':
                quit = true;
                break;
            default:
                break;
        }
    }
    system("pause");
}
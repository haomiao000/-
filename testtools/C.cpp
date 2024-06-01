#include <iostream>
#include <random>
#include <string>

// �������Ӣ����
std::string GenerateRandomName() {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);
    std::string name;
    for (int i = 0; i < 5; ++i) { // ���� 5 λӢ����
        name += chars[dis(gen)];
    }
    return name;
}

// ��������Ա� "0" �� "1"
std::string GenerateRandomSex() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    return std::to_string(dis(gen));
}

// �������רҵ�������Ӣ���ַ�����
std::string GenerateRandomMajor() {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);
    std::string major;
    for (int i = 0; i < 6; ++i) { // ���� 6 λӢ����Ϊרҵ��
        major += chars[dis(gen)];
    }
    return major;
}

// ������������ַ��� "18" �� "22"
std::string GenerateRandomAge() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(18, 22);
    return std::to_string(dis(gen));
}

// ������������ַ������������Ϊ 3 �� 6 ��Ӣ���ַ�����
std::string GenerateRandomEthnic() {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> lengthDis(3, 6); // �������Ϊ 3 �� 6
    std::uniform_int_distribution<> charDis(0, chars.size() - 1);
    std::string ethnic;
    int length = lengthDis(gen); // ���������ַ����ĳ���
    for (int i = 0; i < length; ++i) {
        ethnic += chars[charDis(gen)];
    }
    return ethnic;
}

// �������ѧ����ţ�10λ�����ַ�����
std::string GenerateRandomStudentId() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(1000000000, 9999999999);
    return std::to_string(dis(gen));
}

// ���� SQL ������䣬������uid��Ϊ����
std::string GenerateInsertStatement(int uid) {
    std::string name = GenerateRandomName();
    std::string sex = GenerateRandomSex();
    std::string major = GenerateRandomMajor();
    std::string age = GenerateRandomAge();
    std::string ethnic = GenerateRandomEthnic();
    std::string studentId = GenerateRandomStudentId();

    std::string sql = "INSERT INTO user_base_infos (uid, name, sex, major, age, ethnic, studentnumber, home, sychronizedSchedule, spendingResponsibility, interests) VALUES (" +
                      std::to_string(uid) + ", '" + name + "', '" + sex + "', '" + major + "', '" + age +
                      "', '" + ethnic + "', '" + studentId +
                      "', '�����,�Ӷ���', '0', '���ֻ', '����ѧϰ');";
    return sql;
}

int main() {
    freopen("datasheet2.txt","w",stdout);
    for (int uid = 2; uid <= 201; uid++) {
        std::string sqlStatement = GenerateInsertStatement(uid);
        std::cout << sqlStatement << std::endl;
    }
    return 0;
}

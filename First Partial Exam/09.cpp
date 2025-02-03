/*
 Потребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен податочен систем.
 Во класата File треба да се чуваат следниве податоци:
    •	Име на датотеката (динамички алоцирана низа од знаци)
    •	Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
    •	Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
    •	Големина на датотеката (цел број на мегабајти)
 Дополнително, во класата потребно е да се напишат и:
    •	Конструктор без параметри
    •  	Конструктор со параметри
    •	Конструктор за копирање
    •	Деструктор
    •	Преоптоварување на операторот =
    •	Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
    •	Метод за проверка на еднаквост помеѓу две датотеки со потпис bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
    •	Метод за споредба на типот помеѓу две датотеки со потпис bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија

 Во класата Folder треба да се чуваат следниве податоци:
    •	Име на директориумот (динамички алоцирана низа од знаци)
    •	Број на датотеки во него (на почеток директориумот е празен)
    •	Динамички алоцирана низа од датотеки, објекти од класата File
 Дополнително, во класата потребно е да се напишат и:
    •	Конструктор со потпис Folder(const char* name)
    •	Деструктор
    •	Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
    •	Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот
    •	Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумот
 Не го менувајте почетниот код.
*/

#include <iostream>
#include <cstring>

using namespace std;

enum Extension {
    pdf = 0, txt = 1, exe = 2
};

class File {
private:
    char *name;
    Extension extension;
    char *admin;
    int size;

    void copy(const File &f) {
        this->name = new char[strlen(f.name) + 1];
        this->admin = new char[strlen(f.admin) + 1];
        strcpy(this->name, f.name);
        strcpy(this->admin, f.admin);
        this->size = f.size;
        this->extension = f.extension;
    }

public:
    File(char *name = "", char *admin = "", int size = 0, Extension extension = pdf) {
        this->name = new char[strlen(name) + 1];
        this->admin = new char[strlen(admin) + 1];
        strcpy(this->name, name);
        strcpy(this->admin, admin);
        this->size = size;
        this->extension = extension;
    }

    File(const File &f) {
        copy(f);
    }

    ~File() {
        delete[] name;
        delete[] admin;
    }

    File &operator=(const File &f) {
        if (this != &f) {
            delete[] name;
            delete[] admin;
            copy(f);
        }
        return *this;
    }

    void print() {
        cout << "File name: " << name << ".";
        if (extension == 0)
            cout << "pdf" << endl;
        else if (extension == 1)
            cout << "txt" << endl;
        else
            cout << "exe" << endl;
        cout << "File owner: " << admin << endl;
        cout << "File size: " << size << endl;
    }

    bool equals(const File &that) {
        return (!strcmp(this->name, that.name) && !strcmp(this->admin, that.admin)) &&
               this->extension == that.extension;
    }

    bool equalsType(const File &that) {
        return this->extension == that.extension && !(strcmp(this->name, that.name));
    }
};

class Folder {
private:
    char *name;
    int n;
    File *files;

    void copy(const Folder &f) {
        this->n = f.n;
        this->name = new char[strlen(f.name) + 1];
        this->files = new File[n];
        strcpy(this->name, f.name);
    }

public:
    Folder(const char *name = "") {
        this->n = 0;
        this->name = new char[strlen(name) + 1];
        this->files = new File[n];
        strcpy(this->name, name);
    }

    Folder(const Folder &f) {
        copy(f);
    }

    ~Folder() {
        delete[] name;
        delete[] files;
    }

    Folder &operator=(const Folder &f) {
        if (this != &f) {
            delete[] name;
            delete[] files;
            copy(f);
        }
        return *this;
    }

    void print() {
        cout << "Folder name: " << name << endl;
        for (int i = 0; i < n; i++) {
            files[i].print();
        }
    }

    void remove(const File &file) {
        int index = -1;
        for (int i = 0; i < n; i++) {
            if (files[i].equals(file)) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            File *temp = new File[n - 1];
            for (int i = 0, j = 0; i < n; i++) {
                if (i != index) {
                    temp[j] = files[i];
                    j++; // Increment index only if file is not removed
                }
            }
            n--;
            delete[] files;
            files = temp;
        }
    }

    void add(const File &file) {
        File *temp = new File[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = files[i];
        }
        temp[n] = file;
        n++;
        delete[] files;
        files = temp;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    } else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    } else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    } else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    } else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
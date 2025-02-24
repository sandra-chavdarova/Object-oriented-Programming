/*
 Да се креира класа која претставува слика (Image) во рамките на еден компјутер. За секоја датотека се чуваат (5 поени):
 •	име на сликата (дин. алоцирана низа од знаци). Предефинирано поставено на untitled.
 •	име на корисникот кој е сопственик на датотеката (низа од макс. 50 знаци). Предефинирано поставено на unknown.
 •	димензии на сликата (2 цели броеви кои претставуваат ширина и висина во пиксели). Предефинирано поставени на 800.

 Од класата Imageда се изведе класата TransparentImage, која претставува слика која содржи поддржува транспарентност.
 За транспарентна слика дополнително се чува:
 •	дали поддржува нивоа на транспарентност (bool променлива, предефинирано не поддржува транспарентност).

 За класите Image и TransparentImage да биде достапна метода (fileSize)за пресметка на големината на сликата (во бајти).
 Големината се пресметува на сл. начин (5 поени):
 •	за објектите од класата Image, големината на датотеката е еднаква на:висината * ширината * 3.
 •	за TransparentImage, доколку поддржува нивоа на транспарентност, големината на датотеката е еднаква на ширина * висина * 4.
    Доколку не поддржува транспарентност, големината на сликата се пресметува како ширина * висина + бр._на_пиксели_присутни_во_сликата / 8.

 За класите Image и TransparentImage да се преоптоварат следниве оператори (5 поени):
 •	оператор << кој ги печати податоците од датотеката во сл. формат:
 •	ime_fajl avtor golemina_na_fajlot_vo_bajti
 •	оператор > кој ги споредува сликите според нивната големина.

 Да се дефинира класа Folder, што репрезентира директориум во кој може да се поставуваат слики.
 За секој фолдер се чува (5 поени):
 •	име на фолдерот (низа од макс 255 знаци)
 •	име на корисникот кој е сопственик на фолдерот (низа од макс. 50 знаци). Предефинирано поставено на unknown.
 •	низа од покажувачи кон Image објекти (макс. 100 во рамките на еден фолдер).

 Да се имплементираат следниве методи (5 поени):
 •	метода за пресметка на големината на фолдерот (folderSize).
    Големината на фолдерот е сума од големините од сите слики во рамките на фолдерот.
 •	метода за пронаоѓање на наголемата слика во рамките на фолдерот (getMaxFile).
    Методата враќа покажувач кон најголемата слика во фолдерот (сметано во бајти).

За класата Folder да се имплементира и оператор += кој додава објекти од типот Image/TransparentImage во рамките на фолдерот (5 поени).

Да се креираат следниве функционалности за класите (5 поени):
 •	operator << - со кој се печатат податоците за фолдерот во формат (5 поени):
    ime_folder sopstvenik --
    imeslika avtor goleminanafajlotvo_bajti
    imeslika avtor goleminanafajlotvobajti -- goleminanafoldervo_bajti
 •	operator [] - кој враќа покажувач кон соодветната слика во фолдерот.
    Доколку не постои слика на тој индекс, треба да се врати NULL (5 поени).

 Да се креира и глобална функција max_folder_size која го прима низа од објекти од типот Folder
 и го враќа фолдерот кој има зафаќа најмногу простор (во бајти). (5 поени)

 Да се овозможи правилно функционирање на класите (потребни set или get методи/оператори/конструктори/деструктори)
 според изворниот код кој е веќе зададен. Сите податочни членови на класите се protected. (5 поени)

 Input:
 4
 folder
 user
 1
 2
 image1
 u1
 100 100
 1
 1
 2
 image1
 u1
 100 100
 0
 0

 Result:
 folder user
 --
 image1 u1 40000
 image1 u1 11250
 --
 Folder size: 51250
*/

#include <iostream>
#include <cstring>

using namespace std;

class Image {
protected:
    char *name;
    char owner[60];
    int height;
    int width;
public:
    Image(const char *name = "untitled", const char *owner = "unknown", int width = 800, int height = 800) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->owner, owner);
        this->width = width;
        this->height = height;
    }

    ~Image() {
        delete[] name;
    }

    Image(const Image &i) {
        this->name = new char[strlen(i.name) + 1];
        strcpy(this->name, i.name);
        strcpy(this->owner, i.owner);
        this->width = i.width;
        this->height = i.height;
    }

    Image &operator=(const Image &i) {
        if (this != &i) {
            delete[] name;
            this->name = new char[strlen(i.name) + 1];
            strcpy(this->name, i.name);
            strcpy(this->owner, i.owner);
            this->width = i.width;
            this->height = i.height;
        }
        return *this;
    }

    virtual int fileSize() {
        return width * height * 3;
    }

    friend ostream &operator<<(ostream &out, Image &i) {
        out << i.name << " " << i.owner << " " << i.fileSize() << endl;
        return out;
    }

    bool operator>(Image &i) {
        return fileSize() > i.fileSize();
    }
};

class TransparentImage : public Image {
protected:
    bool trasparency;
public:
    TransparentImage(const char *name = "untitled", const char *owner = "unknown", int width = 800, int height = 800,
                     bool trasparency = true) : Image(name, owner, width, height) {
        this->trasparency = trasparency;
    }

//    TransparentImage(const TransparentImage &t) : Image(t) {
//        this->trasparency = t.trasparency;
//    }

    int fileSize() {
        if (trasparency)
            return width * height * 4;
        else
            return width * height + (width * height) / 8;
    }
};

class Folder {
protected:
    char name[256];
    char owner[51];
    Image *images[100];
    int n;

public:
    Folder(const char *name = "", const char *owner = "unknown") {
        strcpy(this->name, name);
        strcpy(this->owner, owner);
        this->n = 0;
    }

    ~Folder() {
        for (int i = 0; i < n; ++i) {
            delete images[i];
        }
    }

    Folder &operator+=(Image &i) {
        if (n < 100) {
            images[n++] = &i;
        }
        return *this;
    }

    Image *operator[](int a) {
        if (a < 0 || a >= n)
            return NULL;
        else
            return images[a];
    }

    int folderSize() {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += images[i]->fileSize();
        }
        return sum;
    }

    friend ostream &operator<<(ostream &out, Folder &f) {
        out << f.name << " " << f.owner << endl << "--" << endl;
        for (int i = 0; i < f.n; ++i) {
            out << *f.images[i];
        }
        out << "--" << endl;
        out << "Folder size: " << f.folderSize() << endl;
        return out;
    }

    Image *getMaxFile() {
        int index = 0;
        for (int i = 1; i < n; ++i) {
            if (images[i]->fileSize() > images[index]->fileSize())
                index = i;
        }
        return images[index];
    }
};

Folder &max_folder_size(Folder *folders, int n) {
    int index = 0;
    for (int i = 1; i < n; ++i) {
        if (folders[i].folderSize() > folders[index].folderSize())
            index = i;
    }
    return folders[index];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc == 1) {
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout << f1;

        Image f2(name);
        cout << f2;

        Image f3(name, user_name);
        cout << f3;

        Image f4(name, user_name, w, h);
        cout << f4;
    } else if (tc == 2) {
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout << tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout << tf4;
    } else if (tc == 3) {
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout << f3;
    } else if (tc == 4) {
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << dir;
    } else if (tc == 5) {
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout << *(dir.getMaxFile());
    } else if (tc == 6) {
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image *f;
        TransparentImage *tf;

        int sub, fileType;

        while (1) {
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >> fileType;
            if (fileType == 1) { // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name, user_name, w, h);
                dir += *f;
            } else if (fileType == 2) {
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name, user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout << *dir[sub];
    } else if (tc == 7) {
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i = 0; i < folders_num; ++i) {
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image *f;
            TransparentImage *tf;

            int sub, fileType;

            while (1) {
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >> fileType;
                if (fileType == 1) { // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name, user_name, w, h);
                    dir += *f;
                } else if (fileType == 2) {
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name, user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }
        cout << max_folder_size(dir_list, folders_num);
    }
    return 0;
}
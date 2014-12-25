#include "gost_r.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << endl << "ERROR usage: ./gost_r file_in" << endl << endl;

        return -1;
    }
    else
    {
        Gost_r hash;

        if (hash.read_file(argv[1]))
        {
            hash.gost_r();

            hash.Show_hash();
        }
        else
            cout << "Ошибка чтения файла!" << endl << endl;
    }

    return 0;
}

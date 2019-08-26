#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct dados
{
    int cod;          // Primary key
    int codMunicipio; // Pode se repetir
    char municipio[30];
    char munFronteira[30];
    float distancia;
};

void inicializar(dados data[], int sizeArray);
char menu();
void cadastrar(dados data[], int sizeArray);
void listar(dados data[], int count);
void listar(int pos, dados data[]);
int hashFunc(int key, int sizeArray);
void insert(dados item, dados hashArray[], int arraySize);
void loadFile(dados vetor[], string file, int sizeArray, int &count);
void gerarHash(dados base[], dados hashArray[], int sizeArray);
int search(dados hashArray[], int sizeArray, int key);
bool update(dados hashArray[], int sizeArray, int key);
void gerarBaseHaskell(dados data[], string file, int count);
void abrirGhci();

void inicializar(dados data[], int sizeArray)
{
    for (int i = 0; i < sizeArray; i++)
    {
        data[i].cod = 0;
    }
}

int hashFunc(int key, int sizeArray)
{
    return (key % sizeArray);
}

char menu()
{
    char opc;
    cout << "----CADASTRO BASE PARA GPS----\n"
         << " C -> CADASTRAR\n"
         << " A -> ATUALIZAR\n"
         << " L -> LISTAR\n"
         << " O -> ORDENAR\n"
         << " G -> GERAR T.HASH\n"
         << " D -> DELETAR\n"
         << " S -> IR PARA O \"GPS\"\n"
         << " X -> SAIR\n"
         << "Eescolher: ";
    cin >> opc;
    return toupper(opc);
}

bool verify(dados data[], int count, int cod)
{
    for (int i = 0; i < count; i++)
    {
        if (cod == data[i].cod)
            return true;
    }
    return false;
}

void cadastrar(dados data[], int sizeArray)
{
    char go, buffer;
    int count = 0;
    dados auxData;
    do
    {
        listar(data, sizeArray);
        cout << "\n---CADASTRO---\n";
        cout << "Para cancelar digite -1 nos campos de codigo\n";
        cout << "Chave primaria: ";
        cin >> auxData.cod;

        if (auxData.cod == -1)
            return;

        while (verify(data, sizeArray, auxData.cod))
        {
            cout << "Ja existe, try again: ";
            cin >> auxData.cod;
        }

        scanf("%c", &buffer);
        cout << "Codigo para o municipio: ";
        cin >> auxData.codMunicipio;

        if (auxData.codMunicipio == -1)
            return;

        scanf("%c", &buffer);
        cout << "Nome do municipio: ";
        cin.getline(auxData.municipio, 30);
        cout << "Municipio que faz limite com " << auxData.municipio << ": ";
        cin.getline(auxData.munFronteira, 30);
        cout << "Distancia entre " << auxData.municipio << " e " << auxData.munFronteira << " (km): ";
        cin >> auxData.distancia;
        scanf("%c", &buffer);
        while (data[count].cod != 0 && data[count].cod != -1)
            count++;
        data[count] = auxData;
        //insert(auxData, data, sizeArray); // insere no vetor na posicao dada pele hashFunc
        cout << "Proseguir cadastrando (s / n): ";
        cin >> go;
        system("clear || cls");
    } while (toupper(go) == 'S');
}

void listar(dados data[], int count)
{
    cout << "\t\t\tCADASTROS\n\n";
    cout << setiosflags(ios::left)
         << setw(4) << "POS"
         << setw(8) << "|KEY"
         << setw(10) << "|COD. MUN"
         << setw(25) << "|MUNICIPIO"
         << setw(11) << "|DISTANCIA"
         << "|MUN. LIMITE" << endl;
    cout << "____|_______|_________|________________________|__________|________________________\n";
    for (int i = 0; i < count; i++)
    {
        if (data[i].cod != 0 && data[i].cod != -1)
            cout << setiosflags(ios::left)
                 << setw(4) << i << "|"
                 << setw(7) << data[i].cod << "|"
                 << setw(9) << data[i].codMunicipio << "|"
                 << setw(24) << data[i].municipio << "|"
                 << setw(7) << data[i].distancia << "KM "
                 << "|"
                 << data[i].munFronteira << endl;
    }
}

void insert(dados item, dados hashArray[], int arraySize) // insere um DataItem
{                                                         // Assume tabela nao cheia
    int key = item.cod;                                   // pega a chave
    int hashVal = hashFunc(key, arraySize);               // converte a chave
    //cout << "\nVALOR HASH: " << hashVal << endl;
    // ate a celula vazia ou -1
    while (hashArray[hashVal].cod != 0 && hashArray[hashVal].cod != -1)
    {
        ++hashVal;            // vai para a proxima celula
        hashVal %= arraySize; // da a volta se necessario
    }
    hashArray[hashVal] = item; // insere item
} // fim insert()

void loadFile(dados vetor[], string file, int sizeArray, int &count)
{
    dados mun;
    int indice = 0;
    fstream inFile;
    inFile.open(file, ios::binary | ios::in);

    if (!inFile.is_open())
    {
        inFile.open(file, ios::binary | ios::out);
        inFile.close();
        inicializar(vetor, sizeArray);
        return;
    }

    inFile.read((char *)(&mun), sizeof(dados));
    while (inFile && !inFile.eof() && indice < sizeArray)
    {
        if (mun.cod != 0 && mun.cod != -1)
            count++;

        vetor[indice] = mun;
        indice++;
        inFile.read((char *)(&mun), sizeof(dados));
    }
    inFile.close();
}

void saveFile(dados rotas[], string file, int count)
{
    ofstream outFile;
    outFile.open(file, ios::binary | ios::out | ios::trunc);

    if (outFile.fail())
    {
        cout << "Deu ruim amigo...";
        exit(1);
    }

    for (int i = 0; i < count; i++)
        outFile.write((const char *)(&rotas[i]), sizeof(dados));
    outFile.close();
}

void gerarHash(dados base[], dados hashArray[], int sizeArray)
{
    inicializar(hashArray, sizeArray);
    int hashVal;
    for (int i = 0; i < sizeArray; i++)
    {
        if (base[i].cod != 0 && base[i].cod != -1)
        {
            insert(base[i], hashArray, sizeArray);
        }
    }
}

char menuSecun()
{
    char choice;
    cout << "\n\t\t\tATUALIZAR\n\n";
    cout << "1 - Codigo da rota\n"
         << "2 - Nome do municipio\n"
         << "3 - Nome do municipio limite\n"
         << "4 - Distancia entre eles\n"
         << "0 - Voltar ao menu principal\n"
         << "Escolha: ";
    cin >> choice;
    return choice;
}

bool update(dados hashArray[], int sizeArray, int key)
{
    dados temp;
    char choice, buffer;
    bool ocorreu = false;
    int posicao = search(hashArray, sizeArray, key);
    temp = hashArray[posicao];
    listar(posicao, hashArray);

    while ((choice = menuSecun()) != '0')
    {
        system("clear || cls");
        listar(posicao, hashArray);
        switch (choice)
        {
            case '1':
                scanf("%c", &buffer);
                cout << "\nCodigo para o municipio de " << temp.municipio << ": ";
                cin >> temp.codMunicipio;
                ocorreu = true;
                break;

            case '2':
                scanf("%c", &buffer);
                cout << "\nNome do municipio: ";
                cin.getline(temp.municipio, 30);
                ocorreu = true;
                break;

            case '3':
                cout << "\nMunicipio que faz limite com " << temp.municipio << ": ";
                cin.getline(temp.munFronteira, 30);
                ocorreu = true;
                break;

            case '4':
                cout << "\nDistancia entre " << temp.municipio << " e " << temp.munFronteira << " (km): ";
                cin >> temp.distancia;
                scanf("%c", &buffer);
                ocorreu = true;
                break;

            default:
                getchar();
                cout << "\nOpcao invalida!\n";
                getchar();
                break;
        }
        system("clear || cls");
        hashArray[posicao] = temp;
        listar(posicao, hashArray);
    }
    return ocorreu;
}

void deleta(dados hashArray[], int sizeArray, int cod)
{
    int posicao = search(hashArray, sizeArray, cod);
    if (posicao == -1)
    {
        cout << "Dado não encontrado!\n";
        return;
    }
    else
    {
        cout << "\n\t\t\tEXCLUIDO\n\n";
        listar(posicao, hashArray);
        hashArray[posicao].cod = -1;
    }
}

int search(dados hashArray[], int sizeArray, int key)
{
    int hashVal = hashFunc(key, sizeArray); // converte a chave
    while (hashArray[hashVal].cod != 0)     // ate a celula vazia
    {                                       // encontrou a chave?
        if (hashArray[hashVal].cod == key)
            return hashVal;

        ++hashVal;
        hashVal %= sizeArray;
    }
    return -1;
}

void listar(int pos, dados data[])
{
    cout << "\t\t\tCADASTROS\n\n";
    cout << setiosflags(ios::left)
         << setw(4) << "POS"
         << setw(8) << "|KEY"
         << setw(10) << "|COD. MUN"
         << setw(25) << "|MUNICIPIO"
         << setw(11) << "|DISTANCIA"
         << "|MUN. LIMITE" << endl;
    cout << "____|_______|_________|________________________|__________|________________________\n";

    cout << setiosflags(ios::left)
         << setw(4) << pos << "|"
         << setw(7) << data[pos].cod << "|"
         << setw(9) << data[pos].codMunicipio << "|"
         << setw(24) << data[pos].municipio << "|"
         << setw(7) << data[pos].distancia << "KM "
         << "|"
         << data[pos].munFronteira << endl;
}

void gerarBaseHaskell(dados data[], string file, int count)
{
    ofstream arqHask;
    arqHask.open("dbHaskell.txt" ,ios::trunc);

    for (int i = 0; i < count; i++)
    {
        if (data[i].cod != 0 && data[i].cod != -1)
        {
            arqHask << data[i].municipio << ";";
            arqHask << data[i].munFronteira << ";";
            arqHask << data[i].distancia << "\n";
        }
    }
    arqHask.close();
}

void abrirGhci()
{
    system("runhaskell haskellCode.hs");
    cout << "\nCarregando...\n";
}

#endif
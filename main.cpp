#include "functions.h"
//#include <QString>

int main(){

    /// Compressão ----------------------------------------

    // Contagem de ocorrências -----------------------------

    int bytes[256] = {0};
    QString nameFile, nameFileOut;
    nameFile.append("file.txt");
    nameFileOut.append("file.huff");

    countBytes(nameFile,bytes);


    // Montagem da árvore ----------------------------------

    Tree* tree = new Tree();
    tree->buildTree(bytes);
    tree->show(tree->getRoot(),0);


    // Representação da árvore -----------------------------

    tree->buildRepresentation(tree->getRoot());

    // Codificação do arquivo  ----------------------------

    tree->codification(tree->getRoot(),nameFile);


    // Arquivo codificado ---------------------------------
    compress(nameFile,nameFileOut,tree);

    /// Descompressão ----------------------------------------

    // Tamanho do lixo  --------------------------------------
    decompress(nameFileOut);


    return 0;
}

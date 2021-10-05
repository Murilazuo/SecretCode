/* PLANEJAMENTO
    Um ladino está invadiu a fortaleza de um nobre e deve roubar as moedas de ouro desse nobre sem alertar os guardas e sem gastar todas as suas gazuas

    dividido em duas situações:
    VILA - pode gastar o ouro para comprar mais gazuas. Sempre que completa um desafio, o jogador vai para a vila
    FORTALEZA - deve destrancar as portas e baus da fortaleza. Sempre que erra o puzzle o nivel de alerta dos guardas aumenta e uma de suas gazuas quebra.
    Caso o nivel dos guardas chegue no maximo, o jogador perde o jogo.
    Ao completar o puzzle, ele ganha uma qunatidade de ouro e avança para a próxima fase.
*/

#include <iostream>
using namespace std;


int main()
{
    srand(time(0));

    //inicialização das variaveis
    int debugMode = 0;

    int gold = 10, gazua = 5; //itens do jogador
    int level = 0;
    int alert = 0; // valor de aleta dos guardas
    int reward = 0; // recompensa do fim da fase

    int secret[3] = { 0,0,0 };
    int answerPlayer = 0;
    int soma, multy; // dicas do desafio
    int idScret = 0;

    bool inLevel = true; // se o jogador esta em um desafio
    bool gameplay = true; // se o jogador esta jogando
    bool win = false;
    bool shop = false;
    bool canReward = false;
    bool noGazua = false;


    string texts[6];

    texts[0] = "\nVoce e um ladino e esta em uma missao para roubar o castelo de um nobre.\nAdentrando o local, voce encontra seu primeiro desafio, uma porta de \nmadeira trancada. Para abrir a porta, voce deve descobrir os tres \nnumero secretos seguindo a dica.";
    texts[1] = "\nVoce consegui adentrar o castelo, mas ainda nao chegou no tesouro do nobre.\nPara avancar voce precisara destrancar uma porta de madeira robusta.\n";
    texts[2] = "\nFinalmente voce consegue chegar no cofre do castelo, entre voce e a fortuna\ndo nobre so existe mais uma porta de metal, e voce tera que destrancar ela.\n";
    //texto recompenças
    texts[3] = "\nVoce destrancou uma porta a porta de madeira e entrou na cozinha do castelo.\nVasulhando um pouco voce encontra algumas moedas soltas no balcao.\n";
    texts[4] = "\nAbrindo a porta de  madeira robusta, voce entra no salao principal do castelo.\nAqui voce encontra algumas joias em mostruarios e moedas soltas.\n";
    texts[5] = "\nFinalemnte voce esta dentro do cofre do nobre, voce pegua o maximo de moedas\ne itens valiosos que consegue carregar.\n";


    cout << "digite 0 para iniciar o jogo: ";
    cin >> debugMode;

    if (debugMode == 1) {
        cout << "Debug mode on.\n";
    }
    if (debugMode == 2) {
        cout << "Debug mode on.(+itens)\n";
        gold = 999999;
        gazua = 10;
    }

    //variaveis da quest
    int maxNumberQuest = 2; // numero maximo do numero secreto
    int maxReward = 5;
    int minReward = 1;

    //gameplay
    do {
            inLevel = true;
            idScret = 0;
            noGazua = false;
            
            cout << texts[level] << endl;

            //sorteia os numeros secretos
            for (int i = 0; i < 3;i++) {
                secret[i] = rand() % maxNumberQuest + 1;
                if (debugMode == 1) {
                    cout << endl << secret[i] << " ";
                }
            }

            //dica
            soma = secret[0] + secret[1] + secret[2];
            multy = secret[0] * secret[1] * secret[2];
            cout << endl << "A soma dos numeros secretos e " << soma << " e a sua multiplicacao e " << multy << "." << endl;

            //desafio
            while (inLevel) {
                cout << "\nO nivel de alerta dos guardas e de: " << alert << ". (maximo de 10)\n";
                cout << "\nGazuas: " << gazua << endl;

                if (gazua < 1) {
                    cout << "\nVoce gastou todas as suas gazuas e teve que sair do castelo.\n";
                    canReward = false;
                    inLevel = false;
                    noGazua = true;
                }
                else {
                cout << "Indique a senha:\n";
                cin >> answerPlayer;

                    if (answerPlayer == secret[idScret]) {
                        cout << "Voce destrancou uma parte da tranca.\n";
                        idScret++;
                    }
                    else
                    {
                        cout << "\nSenha errada\n";

                        alert++;
                        gazua--;

                        cout << endl << "alert + 1";
                        cout << endl << "gazua - 1";
                    }

                        if (alert >= 10) { //game over
                            gameplay = false;
                            win = false;
                            shop = false;
                            canReward = false;
                            inLevel = false;
                        }
                    }

                if (idScret >= 3) {
                    //Se todas as respostas estão corretas
                    inLevel = false;
                    shop = true;
                    canReward = true;
                }
              
            }

            //recompença
            if (canReward == true) {
            reward = (rand() % maxReward) + minReward;
            gold += reward;
            cout << texts[level+3] << "moedas + " << reward << "\nVoce possui " << gold << " moedas de ouro.\n\n";
            }


            if (level == 2) {   // checa se o jogador completou a ultima fase
                gameplay = false;
                win = true;
            }


            //shop
            if (gameplay != false) {
                cout << "Voce retornou para a vila e se encontra com o seu Contrabandista.\n";
                do {
                    cout <<"\nContrabandista: Quantas gazuas voce quer comprar? 5 moedas de ouro cada uma.( gazuas atuais " << gazua << ", moedas atuais "<<gold << ")." << endl;
                    int gazuasToBuy = 0;
                    cout << "\nVoce: Vou querer "; cin >> gazuasToBuy;

                    if ((gazuasToBuy * 5) > gold) {
                    cout << "\nVoce nao possui moedas o suficiente. Insira um valor valido\n";
                    }
                    else
                    {
                    cout << endl << "gazuas + " << gazuasToBuy;
                    gazua += gazuasToBuy;

                    cout << endl << "moedas - " << gazuasToBuy * 5;
                    gold -= gazuasToBuy * 5;
                    shop = false;
                    }

                } while (shop == true);

                alert -= 4;
                if (alert < 1) {
                    alert = 0;
                }
            }
         
            if (noGazua == false) {
            maxNumberQuest *= 2; 
            maxReward *= 5;
            minReward *= 5;
            level++;
            }
    } while (gameplay == true);

    if (win) {
        cout << endl <<
            "Voce escapou com vida e conseguiu furtar " << gold << " moedas de ouro do nobre.";
    }
    else {
        cout << endl <<
            "Voce foi capturado pelos guardas e vai passar o resto de sua vida apodrecendo na prisao da fortaleza.";
    }

    return 0;
}



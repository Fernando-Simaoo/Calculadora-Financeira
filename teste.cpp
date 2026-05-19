#include <iostream>
#include <cmath>
//Compilar: g++ teste.cpp -o teste.exe
//Executar: .\teste.exe
//Compilar + Executar: g++ teste.cpp -o teste.exe && .\teste.exe
using namespace std;

struct DadosInput {
    double valor = 0;
    int unidade = 2; // Padrão: 2 (Mês)
};

void insersao_juros_simples(bool pedir_C, bool pedir_i, bool pedir_n, bool pedir_M, bool pedir_J,
     DadosInput &C, DadosInput &i, DadosInput &n, DadosInput &M, DadosInput &J) {

        if(pedir_C) {
            cout << "Digite o valor do Capital (VP): ";
            cin >> C.valor;
        }

        if(pedir_J) {
            cout << "Digite o valor do Juros (J): ";
            cin >> J.valor;
        }

        if(pedir_i) {
            cout << "Digite a taxa de juros (i) em porcentagem: ";
            cin >> i.valor;
            cout << "Unidade da taxa de juros (1- Dia, 2- Mês, 3- Ano): ";
            cin >> i.unidade;
        }

        if(pedir_n) {
            cout << "Digite o tempo (n): ";
            cin >> n.valor;
            cout << "Unidade do tempo (1- Dia, 2- Mês, 3- Ano): ";
            cin >> n.unidade;
        }

        if(pedir_M) {
            cout << "Digite o valor do Montante (VF): ";
            cin >> M.valor;
        }
}

double conversao_para_dias(double valor, int unidade, bool eh_taxa) {
    switch(unidade) {
        case 1: // Dia
            return valor; // Já está em dias
        case 2: // Mês
            return eh_taxa ? (valor / 30.0) : (valor * 30.0); // Mês comercial tem 30 dias
        case 3: // Ano
            return eh_taxa ? (valor / 360.0) : (valor * 360.0); // Ano comercial tem 360 dias
        default:
           return valor;
    }
}

void menu_juros_simples() {
    int op = -1;
    
    do {
        cout << "\n--- Menu Juros Simples ---" << endl;
        cout << "0 - Voltar ao menu principal" << endl;
        cout << "1 - Calcular Montante (M)" << endl;
        cout << "2 - Calcular Capital (C)" << endl;
        cout << "3 - Calcular Taxa de Juros (i)" << endl;
        cout << "4 - Calcular Tempo (t)" << endl;
        cout << "Selecione uma opção: ";
        cin >> op;

        // Resetando as estruturas a cada iteração do menu
        DadosInput C, i, n, M, J;
        double i_diario = 0.0, n_diario = 0.0;

        switch(op) {
            case 0:
                cout << "Voltando ao menu principal..." << endl;
                break;
                
            case 1: { // <-- Abre chaves para isolar o escopo do case
                cout << "\n[Calculando Montante (M)...]" << endl;
                insersao_juros_simples(true, true, true, false, false, C, i, n, M, J);

                // Divide por 100 para converter a taxa percentual em decimal (ex: 5% -> 0.05)
                i_diario = conversao_para_dias(i.valor / 100.0, i.unidade, true);
                n_diario = conversao_para_dias(n.valor, n.unidade, false);

                // M = C * (1 + i * n)
                M.valor = C.valor * (1.0 + (i_diario * n_diario));
                cout << "O Montante (M) é: " << M.valor << endl;
                break;
            } // <-- Fecha chaves

            case 2: {
                cout << "\n[Calculando Capital (C)...]" << endl;
                insersao_juros_simples(false, true, true, true, false, C, i, n, M, J);
                
                i_diario = conversao_para_dias(i.valor / 100.0, i.unidade, true);
                n_diario = conversao_para_dias(n.valor, n.unidade, false);
                
                // C = M / (1 + i * n)
                C.valor = M.valor / (1.0 + (i_diario * n_diario));
                cout << "O Capital (C) é: " << C.valor << endl;
                break;
            }

            case 3: {
                cout << "\n[Calculando Taxa de Juros (i)...]" << endl;
                insersao_juros_simples(true, false, true, true, false, C, i, n, M, J);
                
                n_diario = conversao_para_dias(n.valor, n.unidade, false);
                
                // i = (M - C) / (C * n) -> Resultado em taxa diária decimal
                i_diario = (M.valor - C.valor) / (C.valor * n_diario);
                
                // Exibe o resultado. Multiplicamos por 100 para voltar a ser porcentagem
                cout << "A Taxa de Juros diária obtida é: " << (i_diario * 100.0) << "% ao dia." << endl;
                cout << "Nota: Você pode multiplicar por 30 para obter ao mês (" << (i_diario * 100.0 * 30) << "% a.m.)." << endl;
                break;
            }

            case 4: {
                cout << "\n[Calculando Tempo (t)...]" << endl;
                insersao_juros_simples(true, true, false, true, false, C, i, n, M, J);
                
                i_diario = conversao_para_dias(i.valor / 100.0, i.unidade, true);
                
                // t = (M - C) / (C * i) -> Resultado em dias
                n.valor = (M.valor - C.valor) / (C.valor * i_diario);
                cout << "O Tempo necessário é: " << n.valor << " dias." << endl;
                break;
            }

            default:
                cout << "Opção inválida. Por favor, selecione uma opção válida." << endl;
        }
    } while(op != 0);
}

int main() {
    int option = -1;
    do {
        cout << "\n====================================" << endl;
        cout << "Bem vindo a calculadora financeira!" << endl;
        cout << "Selecione o tipo de calculo que deseja realizar: " << endl;
        cout << "1 - Juros Simples" << endl;
        cout << "2 - Juros Compostos" << endl;
        cout << "0 - Sair" << endl;
        cout << "Selecione uma opção: ";
        cin >> option;

        switch(option) {
            case 0:
                cout << "Saindo da calculadora financeira..." << endl;
                break;
            case 1:
                menu_juros_simples();
                break;
            case 2:
                cout << "Menu de Juros Compostos ainda não implementado." << endl;
                break;
            default:
                cout << "Opção inválida. Por favor, selecione uma opção válida." << endl;
        }

    } while(option != 0);
    return 0;
}
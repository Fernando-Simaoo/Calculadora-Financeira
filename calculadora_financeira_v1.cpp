#include <iostream>
#include <cmath>

using namespace std;

enum class Periodo {
    Dia = 1,
    Mes = 2,
    Ano = 3

};

// Encapsulamento: Os dados sabem como se converter

struct Monetario {
    double valor = 0.0;
    Periodo unidade = Periodo::Mes; // Padrão: Mês

    // Duvida: métodos dentro de structs?
    double obter_valor_diario(bool eh_taxa) const {
        //Dúvida: O que é esse const aqui?
        double v = eh_taxa ? (valor/100.0) : valor;
        // condicao ? valor_se_verdadeiro : valor_se_falso
        switch (unidade) {
            case Periodo::Dia: return v;
            case Periodo::Mes: return eh_taxa ? (v / 30.0) : (v * 30.0);
            case Periodo::Ano: return eh_taxa ? (v / 360.0) : (v * 360.0);
            default: return v;
        }
    }
};

// Classe controladora para isolar a lógica de negócios do console
class CalculadoraFinanceira {
    public:
        static double simples_calcular_montante(const Monetario& capital, const Monetario& taxa, const Monetario& tempo) {
            double i = taxa.obter_valor_diario(true);
            double t = tempo.obter_valor_diario(false);
            return capital.valor * (1.0 + (i * t));
        }

        static double simples_calcular_capital(const Monetario& montante, const Monetario& taxa, const Monetario& tempo) {
            double i = taxa.obter_valor_diario(true);
            double t = tempo.obter_valor_diario(false);
            return montante.valor / (1.0 + (i * t));
        }

        static double simples_calcular_taxa(const Monetario& montante, const Monetario& capital, const Monetario& tempo) {
            double t = tempo.obter_valor_diario(false);
            // Retorna em taxa diária decimal
            return (montante.valor - capital.valor) / (capital.valor * t);
        }

        static double simples_calcular_tempo(const Monetario& montante, const Monetario& capital, const Monetario& taxa) {
            double i = taxa.obter_valor_diario(true);
            // Retorna o tempo em dias
            return (montante.valor - capital.valor) / (capital.valor * i);
        }

        static double simples_calcular_juros(const Monetario& capital, const Monetario& taxa, const Monetario& tempo) {
            double i = taxa.obter_valor_diario(true);
            double t = tempo.obter_valor_diario(false);
            return capital.valor * i * t;
        }

        static double simples_calcular_taxa_efetiva(const Monetario& taxa_desconto, const Monetario& tempo) {
            double ic = taxa_desconto.obter_valor_diario(true);
            double t = tempo.obter_valor_diario(false);
            // Fórmula da Taxa Efetiva a partir do Desconto Comercial
            return ic / (1.0 - (ic * t)); 
        }

        static double simples_calcular_taxa_desconto(const Monetario& taxa_efetiva, const Monetario& tempo) {
            double i = taxa_efetiva.obter_valor_diario(true);
            double t = tempo.obter_valor_diario(false);
            // O caminho inverso (Taxa de Desconto a partir da Efetiva)
            return i / (1.0 + (i * t));
        }
};

//Input dinâmico especializado e limpo
Monetario solicitar_entrada(const string& nome_campo, bool need_time = false){
    Monetario m;
    cout << "Digite o valor para " << nome_campo << ": ";
    cin >> m.valor;


    //Acho que faltou um caso IF pra saber se é necessário pedir o tempo
    if(need_time) {
        int op;
        cout << "Escolha a unidade de tempo (1-Dia, 2-Mes, 3-Ano): ";
        cin >> op;
        m.unidade = static_cast<Periodo>(op);
        //Dúvida: o que é esse "static_cast" aqui?
    }

    return m;
}

void menu_juros_simples() {
    int op = -1;
    cout << "Menu de Juros Simples" << endl;
    do{
        //Menu aqui
        cout << "1. Calcular Montante" << endl;
        cout << "2. Calcular Capital" << endl;
        cout << "3. Calcular Taxa" << endl;
        cout << "4. Calcular Tempo" << endl;
        cout << "5. Calcular Juros" << endl;
        cout << "6. Converter Taxa Nominal" << endl;
        cout << "7. Converter Taxa Efetiva" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> op;

switch(op) {
            case 1: {
                cout << "\n[ Calculando Montante ]" << endl;
                Monetario c = solicitar_entrada("Capital", false);
                Monetario i = solicitar_entrada("Taxa", true);
                Monetario t = solicitar_entrada("Tempo", true);
                cout << "-> Montante Final: R$ " << CalculadoraFinanceira::simples_calcular_montante(c, i, t) << endl;
                break;
            }
            case 2: {
                cout << "\n[ Calculando Capital ]" << endl;
                Monetario m = solicitar_entrada("Montante", false);
                Monetario i = solicitar_entrada("Taxa", true);
                Monetario t = solicitar_entrada("Tempo", true);
                cout << "-> Capital Inicial: R$ " << CalculadoraFinanceira::simples_calcular_capital(m, i, t) << endl;
                break;
            }
            case 3: {
                cout << "\n[ Calculando Taxa ]" << endl;
                Monetario m = solicitar_entrada("Montante", false);
                Monetario c = solicitar_entrada("Capital", false);
                Monetario t = solicitar_entrada("Tempo", true);
                double resultado_i = CalculadoraFinanceira::simples_calcular_taxa(m, c, t);
                cout << "-> Taxa Encontrada: " << (resultado_i * 100.0) << "% ao dia" << endl;
                break;
            }
            case 4: {
                cout << "\n[ Calculando Tempo ]" << endl;
                Monetario m = solicitar_entrada("Montante", false);
                Monetario c = solicitar_entrada("Capital", false);
                Monetario i = solicitar_entrada("Taxa", true);
                cout << "-> Tempo Necessário: " << CalculadoraFinanceira::simples_calcular_tempo(m, c, i) << " dias" << endl;
                break;
            }
            case 5: {
                cout << "\n[ Calculando Juros ]" << endl;
                Monetario c = solicitar_entrada("Capital", false);
                Monetario i = solicitar_entrada("Taxa", true);
                Monetario t = solicitar_entrada("Tempo", true);
                cout << "-> Juros Acumulados: R$ " << CalculadoraFinanceira::simples_calcular_juros(c, i, t) << endl;
                break;
            }
            case 6: {
                cout << "\n[ Convertendo Taxa Efetiva -> Taxa de Desconto ]" << endl;
                Monetario i = solicitar_entrada("Taxa Efetiva", true);
                Monetario t = solicitar_entrada("Tempo de Antecipação", true);
                double desc = CalculadoraFinanceira::simples_calcular_taxa_desconto(i, t);
                cout << "-> Taxa de Desconto Comercial: " << (desc * 100.0) << "% ao dia" << endl;
                break;
            }
            case 7: {
                cout << "\n[ Convertendo Taxa de Desconto -> Taxa Efetiva ]" << endl;
                Monetario ic = solicitar_entrada("Taxa de Desconto", true);
                Monetario t = solicitar_entrada("Tempo de Antecipação", true);
                double efetiva = CalculadoraFinanceira::simples_calcular_taxa_efetiva(ic, t);
                cout << "-> Taxa Efetiva: " << (efetiva * 100.0) << "% ao dia" << endl;
                break;
            }
            case 0:
                cout << "Saindo do Menu de Juros Simples..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    }while(op != 0);
}





int main() {
    cout << "Calculadora Financeira" << endl;
/*

Monetario c = solicitar_entrada("Capital");
Monetario i = solicitar_entrada("Taxa (i)", true);
Monetario t = solicitar_entrada("Tempo (t)", true);

*/

    //Menu Geral
    int opcao = -1;
    do{
        cout << "Bem Vindo A Calculadora Financeira!!!" << endl;
        cout << "1. Juros Simples" << endl;
        cout << "2. Juros Compostos" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch(opcao) {
            case 1:
                menu_juros_simples();
                break;
            case 2:
                // Menu para juros compostos
                break;
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    }while(opcao != 0); 
}
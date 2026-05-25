#include <iostream>
#include <cmath>

using namespace std;

// 1. Uso de Strongly Typed Enums (Evita números mágicos como 1, 2, 3)
enum class Periodo {
    Dia = 1,
    Mes = 2,
    Ano = 3
};

// 2. Encapsulamento real: Os dados sabem como se converter
struct Monetario {
    double valor = 0.0;
    Periodo unidade = Periodo::Mes;

    // O próprio dado limpa e normaliza a si mesmo
    double obter_valor_diario(bool eh_taxa) const {
        double v = eh_taxa ? (valor / 100.0) : valor; // Trata a porcentagem implicitamente
        switch (unidade) {
            case Periodo::Dia: return v;
            case Periodo::Mes: return eh_taxa ? (v / 30.0) : (v * 30.0);
            case Periodo::Ano: return eh_taxa ? (v / 360.0) : (v * 360.0);
            default:           return v;
        }
    }
};

// 3. Uma classe controladora isola a lógica de negócios da interface (Console)
class CalculadoraFinanceira {
public:
    static double calcular_montante(const Monetario& capital, const Monetario& taxa, const Monetario& tempo) {
        double i = taxa.obter_valor_diario(true);
        double n = tempo.obter_valor_diario(false);
        return capital.valor * (1.0 + (i * n));
    }
    // Outros métodos: calcular_capital, calcular_taxa...
};

// 4. Input dinâmico especializado e limpo
Monetario solicitar_entrada(const string& nome_campo, bool eh_taxa = false) {
    Monetario m;
    cout << "Digite o valor para " << nome_campo << ": ";
    cin >> m.valor;
    
    int op;
    cout << "Unidade (1-Dia, 2-Mes, 3-Ano): ";
    cin >> op;
    m.unidade = static_cast<Periodo>(op);
    
    return m;
}

int main() {
    // Na Main, o código sênior se torna absurdamente expressivo e legível
    cout << "--- Modo Sênior: Calcular Montante ---" << endl;
    
    Monetario c = solicitar_entrada("Capital");
    Monetario i = solicitar_entrada("Taxa (i)", true);
    Monetario n = solicitar_entrada("Tempo (n)");

    double resultado = CalculadoraFinanceira::calcular_montante(c, i, n);
    
    cout << "\nO Montante Final calculado é: R$ " << resultado << endl;
    return 0;
}
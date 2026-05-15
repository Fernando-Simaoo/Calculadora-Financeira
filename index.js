function calcularJuros() {
    // 1. Captura os valores digitados no HTML
    const capitalStr = document.getElementById('capital').value;
    const taxaStr = document.getElementById('taxa').value;
    const tempoStr = document.getElementById('tempo').value;
    const visorResultado = document.getElementById('resultado');

    // 2. Converte as strings para números
    const capital = parseFloat(capitalStr);
    const taxa = parseFloat(taxaStr) / 100; // Divide por 100 para aplicar a porcentagem
    const tempo = parseInt(tempoStr, 10);

    // 3. Validação extra de segurança
    if (isNaN(capital) || isNaN(taxa) || isNaN(tempo)) {
        visorResultado.textContent = "Erro nos dados";
        visorResultado.style.color = "#cb2431"; // Vermelho para erro
        return;
    }

    // 4. Aplica a fórmula matemática dos Juros Compostos: M = C * (1 + i)^t
    const montante = capital * Math.pow((1 + taxa), tempo);

    // 5. Formata a resposta para Real brasileiro (R$) e exibe na tela
    visorResultado.style.color = "#0366d6"; // Volta para o azul padrão
    visorResultado.textContent = montante.toLocaleString('pt-BR', { style: 'currency', currency: 'BRL' });
}

function limparVisor() {
    // Restaura o visor para o estado original quando o botão "Limpar" for clicado
    const visorResultado = document.getElementById('resultado');
    visorResultado.style.color = "#0366d6";
    visorResultado.textContent = "R$ 0,00";
}
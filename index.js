alert("Arquivo conectado!");


function inserir(id) {
    var calc_buffer = document.getElementById("tela");

    var char = document.getElementById(id).innerHTML;
    calc_buffer.textContent += char;
}

function backspace() {
    var calc_buffer = document.getElementById("tela");
    calc_buffer.textContent = calc_buffer.textContent.slice(0, -1);
}

function limpar() {
    var calc_buffer = document.getElementById("tela");
    calc_buffer.textContent = "";
}

function calcular() {
    var calc_buffer = document.getElementById("tela");
    calc_buffer.textContent = eval(calc_buffer.textContent);
}
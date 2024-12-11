<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Controle de Estoque</title>
    <style>
        table {
            width: 100%;
            border-collapse: collapse;
        }
        table, th, td {
            border: 1px solid black;
        }
        th, td {
            padding: 8px;
            text-align: left;
        }
        #btnSalvar {
            margin-top: 10px;
            padding: 10px 15px;
            background-color: green;
            color: white;
            border: none;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <h1>Produto</h1>
    <table id="tabela">
        <thead>
            <tr>
                <th>Modelo</th>
                <th>Preço</th>
                <th>Volume</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td contenteditable="true"></td>
                <td contenteditable="true"></td>
                <td contenteditable="true"></td>
            </tr>
        </tbody>
    </table>
    <button id="btnSalvar">Salvar</button>

    <script>
        document.getElementById('btnSalvar').addEventListener('click', () => {
            const tabela = document.querySelector('#tabela tbody');
            const linhas = tabela.querySelectorAll('tr');

            const dados = Array.from(linhas).map(linha => {
                const colunas = linha.querySelectorAll('td');
                return {
                    uid: colunas[0].textContent.trim(),
                    descricao: colunas[1].textContent.trim(),
                    quantidade: colunas[2].textContent.trim()
                };
            });

            // Verificar se os campos não estão vazios antes de enviar os dados
            const dadosValidos = dados.filter(item => item.uid && item.descricao && item.quantidade);
            if (dadosValidos.length > 0) {
                fetch('salvar_dados.php', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify(dadosValidos),
                })
                .then(response => response.json())
                .then(data => {
                    alert(data.message);
                    // Opcional: Após salvar, recarregar a página ou exibir dados salvos
                    window.location.reload(); // ou faça uma chamada para exibir os dados salvos
                })
                .catch(error => {
                    console.error('Erro:', error);
                });
            } else {
                alert('Por favor, preencha todos os campos.');
            }
        });
    </script>
</body>
</html>

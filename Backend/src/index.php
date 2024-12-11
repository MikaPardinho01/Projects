<?php
    include_once './BancoDeDados.php';
?>

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
            padding: 5px 5px;
            background-color: green;
            color: white;
            border: none;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <?php
        //$page = isset($_GET['page']) && is_numeric($_GET['page']) ? (int)$_GET['page'] : 1;
        //$perPage = 10;
        //$offset = ($page - 1) * $perPage;

        $pdo = (new BancoDeDados())->iniciarConexao();
        $stmt = $pdo->prepare('SELECT * FROM mika.produto ORDER BY id DESC');
        $stmt->execute();
        //$stmt = $pdo->prepare('SELECT * FROM mika.produto LIMIT :perPage OFFSET :offset');
        //$stmt->execute([':perPage' => $perPage, ':offset' => $offset]);
        $products = $stmt->fetchAll();
        //$totalStmt = $pdo->query('SELECT COUNT(*) FROM mika.produto');
        //$totalRows = $totalStmt->fetchColumn();
        //$totalPages = ceil($totalRows / $perPage);
    ?>
    <h1>Produto</h1>
    <table id="tabela">
        <thead>
            <tr>
                <th>ID Externo</th>
                <th>Modelo</th>
                <th>Preço</th>
                <th>Volume</th>
                <th>Ação</th>
            </tr>
        </thead>
        <tbody>
            <?php
                foreach ($products as $product) {
                    echo '<tr>';
                        echo '<td id="idExterno_' . $product['id_externo'] . '">' . $product['id_externo'] . '</td>';
                        echo '<td id="modelo_' . $product['modelo'] . '">' . $product['modelo'] . '</td>';
                        echo '<td id="preco_' . $product['preco'] . '">' . $product['preco'] . '</td>';
                        echo '<td id="volume_' . $product['volume'] . '">' . $product['volume'] . '</td>';
                        echo "<td onClick='excluirProduto(`$product[id_externo]`)'><a href='#'>Excluir</a></td>";
                    echo '</tr>';
                }
            ?>
        </tbody>
        <tbody>
            <tr>
                <td>
                    <input type="text" id="novoIdExterno" />
                </td>
                <td>
                    <input type="text" id="novoModelo" />
                </td>
                <td>
                    <input type="number" id="novoPreco" />
                </td>
                <td>
                    <input type="number" id="novoVolume" />
                </td>
                <td>
                    <button id="btnSalvar">Salvar</button>
                </td>
            </tr>
        </tbody>
    </table>
    

    <script>

       function excluirProduto(id_externo) {
            fetch('excluir_dados.php', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({ id_externo }),
            })
            .then(() => {
                alert('Dados excluídos');
                window.location.reload(); // ou faça uma chamada para exibir os dados salvos
            })
            .catch(error => {
                console.error('Erro ao excluir os dados:', error);
            });
        }

        document.getElementById('btnSalvar').addEventListener('click', async () => {
            const produto = {
                id_externo: document.getElementById('novoIdExterno').value,
                modelo: document.getElementById('novoModelo').value,
                preco: document.getElementById('novoPreco').value,
                volume: document.getElementById('novoVolume').value
            };
            
            if (! produto.id_externo || ! produto.modelo || ! produto.preco || ! produto.volume) {
                alert('Por favor, preencha todos os campos.');
                return;
            }

             await fetch('salvar_dados.php', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(produto),
            })
            .then(() => {
                alert('Dados salvos');
                window.location.reload(); // ou faça uma chamada para exibir os dados salvos
            })
            .catch(error => {
                console.error('Erro ao salvar os dados:', error);
            });
        });

        
    </script>
</body>
</html>

<?php

include_once './BancoDeDados.php'; // Inclui a classe de conexão ao banco de dados

// Conectar ao banco de dados
$db = new BancoDeDados();
$conexao = $db->iniciarConexao();

// Buscar os dados dos produtos cadastrados
$query = "SELECT * FROM produto";
$stmt = $conexao->prepare($query);
$stmt->execute();
$produtos = $stmt->fetchAll(PDO::FETCH_ASSOC);
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
        .btn-novo-produto {
            margin-top: 10px;
            padding: 10px 15px;
            background-color: blue;
            color: white;
            border: none;
            cursor: pointer;
            text-decoration: none;
            display: inline-block;
        }
    </style>
</head>
<body>
    <h1>Controle de Estoque</h1>

    <!-- Tabela para exibir os produtos cadastrados -->
    <table>
        <thead>
            <tr>
                <th>UID</th>
                <th>Descrição</th>
                <th>Quantidade</th>
            </tr>
        </thead>
        <tbody>
            <?php if (count($produtos) > 0): ?>
                <?php foreach ($produtos as $produto): ?>
                    <tr>
                        <td><?php echo htmlspecialchars($produto['uid']); ?></td>
                        <td><?php echo htmlspecialchars($produto['descricao']); ?></td>
                        <td><?php echo htmlspecialchars($produto['quantidade']); ?></td>
                    </tr>
                <?php endforeach; ?>
            <?php else: ?>
                <tr>
                    <td colspan="3">Nenhum produto cadastrado.</td>
                </tr>
            <?php endif; ?>
        </tbody>
    </table>

    <!-- Botão para redirecionar ao formulário de cadastro -->
    <a href="index.html" class="btn-novo-produto">Adicionar Novo Produto</a>
</body>
</html>

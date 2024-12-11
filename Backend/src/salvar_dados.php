<?php
include_once './BancoDeDados.php';

// Recebe os dados JSON via POST
$data = json_decode(file_get_contents('php://input'), true);

// Verifica se há dados
if (!empty($data)) {
    // Conectar ao banco de dados
    $db = new BancoDeDados();
    $conexao = $db->iniciarConexao();

    // Prepara e executa as consultas para salvar os dados
    foreach ($data as $item) {
        if (!empty($item['uid']) && !empty($item['descricao']) && !empty($item['quantidade'])) {
            $query = "INSERT INTO produto (uid, descricao, quantidade) VALUES (:uid, :descricao, :quantidade)";
            $stmt = $conexao->prepare($query);
            $stmt->bindParam(':uid', $item['uid']);
            $stmt->bindParam(':descricao', $item['descricao']);
            $stmt->bindParam(':quantidade', $item['quantidade']);
            $stmt->execute();
        }
    }

    // Responde com uma mensagem de sucesso
    echo json_encode(['success' => true, 'message' => 'Dados salvos com sucesso!']);
} else {
    echo json_encode(['success' => false, 'message' => 'Nenhum dado foi recebido.']);
}

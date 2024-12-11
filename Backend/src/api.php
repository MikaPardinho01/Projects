<?php

include_once './BancoDeDados.php';

// Verifica se o método da requisição é POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    // Captura o UID enviado no corpo da requisição
    $uid = $_POST['uid'] ?? null;

    // Verifica se o UID não está vazio
    if (!empty($uid)) {
        $db = new BancoDeDados();
        $conexao = $db->iniciarConexao();

        // Verifica se o UID já existe no banco
        $queryCheck = "SELECT COUNT(*) FROM produto WHERE uid = :uid";
        $stmtCheck = $conexao->prepare($queryCheck);
        $stmtCheck->bindParam(':uid', $uid);
        $stmtCheck->execute();

        if ($stmtCheck->fetchColumn() > 0) {
            echo json_encode(['success' => false, 'message' => 'UID já existe no banco.']);
            exit;
        }

        // Insere o UID no banco de dados
        $queryInsert = "INSERT INTO produto (uid) VALUES (:uid)";
        $stmtInsert = $conexao->prepare($queryInsert);
        $stmtInsert->bindParam(':uid', $uid);

        if ($stmtInsert->execute()) {
            echo json_encode(['success' => true, 'message' => 'UID salvo com sucesso.']);
        } else {
            echo json_encode(['success' => false, 'message' => 'Erro ao salvar o UID.']);
        }
    } else {
        // UID vazio
        echo json_encode(['success' => false, 'message' => 'UID não pode estar vazio.']);
    }
} else {
    // Método não permitido
    echo json_encode(['success' => false, 'message' => 'Método não permitido.']);
}

